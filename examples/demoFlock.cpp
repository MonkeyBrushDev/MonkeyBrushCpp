#include <mb/mb.h>
#include <routes.h>

int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );
  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 512, 512 ) );
  window->init( );

  mb::PostProcessMaterial pp(R"(
#version 430
in vec2 uv;
out vec4 fragColor;
uniform sampler2D targetTex;
void main( )
{
  fragColor = vec4( texture( targetTex, uv ).rgb, 1.0 );
})");

  mb::Material* m = new mb::Material( );
  m->program = std::make_shared< mb::Program >( );
  m->program->loadVertexShaderFromText( R"(
#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

layout (location = 2) in vec3 bird_position;
layout (location = 3) in vec3 bird_velocity;

out VS_OUT
{
    flat vec3 color;
} vs_out;

uniform mat4 MB_MATRIXP;
uniform mat4 MB_MATRIXV;
uniform mat4 MB_MATRIXM;

mat4 make_lookat(vec3 forward, vec3 up)
{
    vec3 side = cross(forward, up);
    vec3 u_frame = cross(side, forward);

    return mat4(vec4(side, 0.0),
                vec4(u_frame, 0.0),
                vec4(forward, 0.0),
                vec4(0.0, 0.0, 0.0, 1.0));
}

vec3 choose_color(float f)
{
    float R = sin(f * 6.2831853);
    float G = sin((f + 0.3333) * 6.2831853);
    float B = sin((f + 0.6666) * 6.2831853);

    return vec3(R, G, B) * 0.25 + vec3(0.75);
}

void main(void)
{
    mat4 lookat = make_lookat(normalize(bird_velocity), vec3(0.0, 1.0, 0.0));
    vec4 obj_coord = lookat * vec4(position.xyz, 1.0);
    gl_Position = MB_MATRIXP * MB_MATRIXV * MB_MATRIXM 
      * (obj_coord + vec4(bird_position, 0.0));

    vec3 N = mat3(lookat) * normal;
    vec3 C = choose_color(fract(float(gl_InstanceID / float(1237.0))));

    vs_out.color = mix(C * 0.2, C, smoothstep(0.0, 0.8, abs(N).z));
})" );
  m->program->loadFragmentShaderFromText( R"(
#version 430 core

layout (location = 0) out vec4 color;

in VS_OUT
{
    flat vec3 color;
} fs_in;

void main(void)
{
    color = vec4(fs_in.color.rgb, 1.0);
})" );
  m->program->compileAndLink( );
  m->program->autocatching( );
  m->addStandardUniforms( );

  mb::compute::ComputeShader cs( R"(
#version 430 core

layout (local_size_x = 256) in;

uniform float closest_allowed_dist = 50.0;
uniform float rule1_weight = 0.18;
uniform float rule2_weight = 0.05;
uniform float rule3_weight = 0.17;
uniform float rule4_weight = 0.02;
uniform vec3 goal = vec3(0.0);
uniform float timestep = 0.4;

struct flock_member
{
    vec3 position;
    vec3 velocity;
};

layout (std430, binding = 0) readonly buffer members_in
{
    flock_member member[];
} input_data;

layout (std430, binding = 1) buffer members_out
{
    flock_member member[];
} output_data;

shared flock_member shared_member[gl_WorkGroupSize.x];

vec3 rule1(vec3 my_position, vec3 my_velocity, vec3 their_position, vec3 their_velocity)
{
    vec3 d = my_position - their_position;
    if (dot(d, d) < closest_allowed_dist)
        return d;
    return vec3(0.0);
}

vec3 rule2(vec3 my_position, vec3 my_velocity, vec3 their_position, vec3 their_velocity)
{
     vec3 d = their_position - my_position;
     vec3 dv = their_velocity - my_velocity;
     return dv / (dot(d, d) + 10.0);
}

void main(void)
{
    uint i, j;
    int global_id = int(gl_GlobalInvocationID.x);
    int local_id  = int(gl_LocalInvocationID.x);

    flock_member me = input_data.member[global_id];
    flock_member new_me;
    vec3 accelleration = vec3(0.0);
    vec3 flock_center = vec3(0.0);

    for (i = 0; i < gl_NumWorkGroups.x; i++)
    {
        flock_member them =
            input_data.member[i * gl_WorkGroupSize.x +
                              local_id];
        shared_member[local_id] = them;
        memoryBarrierShared();
        barrier();
        for (j = 0; j < gl_WorkGroupSize.x; j++)
        {
            them = shared_member[j];
            flock_center += them.position;
            if (i * gl_WorkGroupSize.x + j != global_id)
            {
                accelleration += rule1(me.position,
                                       me.velocity,
                                       them.position,
                                       them.velocity) * rule1_weight;
                accelleration += rule2(me.position,
                                       me.velocity,
                                       them.position,
                                       them.velocity) * rule2_weight;
            }
        }
        barrier();
    }

    flock_center /= float(gl_NumWorkGroups.x * gl_WorkGroupSize.x);
    new_me.position = me.position + me.velocity * timestep;
    accelleration += normalize(goal - me.position) * rule3_weight;
    accelleration += normalize(flock_center - me.position) * rule4_weight;
    new_me.velocity = me.velocity + accelleration * timestep;
    if (length(new_me.velocity) > 10.0)
        new_me.velocity = normalize(new_me.velocity) * 10.0;
    new_me.velocity = mix(me.velocity, new_me.velocity, 0.4);
    output_data.member[global_id] = new_me;
})" );

  mb::Texture2D* t = mb::Texture2D::loadFromImage( "earth/earth_diffuse.jpg" );


  static const mb::Vector3 geometry[ ] =
  {
    // Positions
    mb::Vector3( -5.0f, 1.0f, 0.0f ),
    mb::Vector3( -1.0f, 1.5f, 0.0f ),
    mb::Vector3( -1.0f, 1.5f, 7.0f ),
    mb::Vector3( 0.0f, 0.0f, 0.0f ),
    mb::Vector3( 0.0f, 0.0f, 10.0f ),
    mb::Vector3( 1.0f, 1.5f, 0.0f ),
    mb::Vector3( 1.0f, 1.5f, 7.0f ),
    mb::Vector3( 5.0f, 1.0f, 0.0f ),

    // Normals
    mb::Vector3( 0.0f ),
    mb::Vector3( 0.0f ),
    mb::Vector3( 0.107f, -0.859f, 0.00f ),
    mb::Vector3( 0.832f, 0.554f, 0.00f ),
    mb::Vector3( -0.59f, -0.395f, 0.00f ),
    mb::Vector3( -0.832f, 0.554f, 0.00f ),
    mb::Vector3( 0.295f, -0.196f, 0.00f ),
    mb::Vector3( 0.124f, 0.992f, 0.00f ),
  };

  GLuint      flock_buffer[ 2 ];
  GLuint      flock_render_vao[ 2 ];
  GLuint      geometry_buffer;

  enum
  {
    WORKGROUP_SIZE = 256,
    NUM_WORKGROUPS = 64,
    FLOCK_SIZE = ( NUM_WORKGROUPS * WORKGROUP_SIZE )
  };
  
  struct flock_member
  {
    mb::Vector3 position;
    unsigned int : 32;
    mb::Vector3 velocity;
    unsigned int : 32;
  };

  glGenBuffers( 2, flock_buffer );
  glBindBuffer( GL_SHADER_STORAGE_BUFFER, flock_buffer[ 0 ] );
  glBufferData( GL_SHADER_STORAGE_BUFFER, FLOCK_SIZE * sizeof( flock_member ), NULL, GL_DYNAMIC_COPY );
  glBindBuffer( GL_SHADER_STORAGE_BUFFER, flock_buffer[ 1 ] );
  glBufferData( GL_SHADER_STORAGE_BUFFER, FLOCK_SIZE * sizeof( flock_member ), NULL, GL_DYNAMIC_COPY );

  int i;

  glGenBuffers( 1, &geometry_buffer );
  glBindBuffer( GL_ARRAY_BUFFER, geometry_buffer );
  glBufferData( GL_ARRAY_BUFFER, sizeof( geometry ), geometry, GL_STATIC_DRAW );

  glGenVertexArrays( 2, flock_render_vao );

  for ( i = 0; i < 2; i++ )
  {
    glBindVertexArray( flock_render_vao[ i ] );
    glBindBuffer( GL_ARRAY_BUFFER, geometry_buffer );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, ( void * ) ( 8 * sizeof( mb::Vector3 ) ) );

    glBindBuffer( GL_ARRAY_BUFFER, flock_buffer[ i ] );
    glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, sizeof( flock_member ), NULL );
    glVertexAttribPointer( 3, 3, GL_FLOAT, GL_FALSE, sizeof( flock_member ), ( void * )sizeof( mb::Vector4 ) );
    glVertexAttribDivisor( 2, 1 );
    glVertexAttribDivisor( 3, 1 );

    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );
    glEnableVertexAttribArray( 3 );
  }

  glBindBuffer( GL_ARRAY_BUFFER, flock_buffer[ 0 ] );
  flock_member * ptr = reinterpret_cast<flock_member *>( glMapBufferRange( GL_ARRAY_BUFFER, 0, FLOCK_SIZE * sizeof( flock_member ), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT ) );

  mb::Random r;
  for ( i = 0; i < FLOCK_SIZE; i++ )
  {
    ptr[ i ].position = ( mb::Vector3( r.next( ), r.next( ), r.next( ) ) - mb::Vector3( 0.5f ) ) * 300.0f;
    ptr[ i ].velocity = ( mb::Vector3( r.next( ), r.next( ), r.next( ) ) - mb::Vector3( 0.5f ) );
  }

  glUnmapBuffer( GL_ARRAY_BUFFER );


  GLuint frame_index = 0;


  mb::Application app;
  app.setSceneNode( new mb::Group( "" ) );

  mb::Clock clockTime;
  clockTime.reset( );

  pp.addUniform( "targetTex", std::make_shared< mb::TextureUniform >( t ) );

  while ( window->isRunning( ) )
  {
    window->pollEvents( );

    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Esc ) )
    {
      window->close( );
      break;
    }

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    clockTime.tick( );

    /*pp.use( );

    app.getRenderer( )->drawScreenQuad( );*/

    float t = ( float ) clockTime.getDeltaTime( );
    static const float black[ ] = { 0.0f, 0.0f, 0.0f, 1.0f };
    static const float one = 1.0f;

    cs.program->use( );

    mb::Vector3 goal( sinf( t * 0.34f ),
      cosf( t * 0.29f ),
      sinf( t * 0.12f ) * cosf( t * 0.5f ) );

    goal = goal * mb::Vector3( 35.0f, 25.0f, 60.0f );

    glUniform3fv( uniforms.update.goal, 1, goal );

    glBindBufferBase( GL_SHADER_STORAGE_BUFFER, 0, flock_buffer[ frame_index ] );
    glBindBufferBase( GL_SHADER_STORAGE_BUFFER, 1, flock_buffer[ frame_index ^ 1 ] );

    glDispatchCompute( NUM_WORKGROUPS, 1, 1 );

    glViewport( 0, 0, 512, 512 );
    glClearBufferfv( GL_COLOR, 0, black );
    glClearBufferfv( GL_DEPTH, 0, &one );

    m->program->use( );

    mb::Matrix4 mv_matrix = vmath::lookat( vmath::vec3( 0.0f, 0.0f, -400.0f ),
      vmath::vec3( 0.0f, 0.0f, 0.0f ),
      vmath::vec3( 0.0f, 1.0f, 0.0f ) );
    vmath::mat4 proj_matrix = vmath::perspective( 60.0f,
      ( float ) info.windowWidth / ( float ) info.windowHeight,
      0.1f,
      3000.0f );
    vmath::mat4 mvp = proj_matrix * mv_matrix;

    glUniformMatrix4fv( uniforms.render.mvp, 1, GL_FALSE, mvp );

    glBindVertexArray( flock_render_vao[ frame_index ] );

    glDrawArraysInstanced( GL_TRIANGLE_STRIP, 0, 8, FLOCK_SIZE );

    window->swapBuffers( );
  }

  return 0;
}
