#include <mb/mb.h>

class TimeComponent : public mb::Component
{
  IMPLEMENT_COMPONENT( TimeComponent )
public:
  TimeComponent( void )
    : _time( 0.0f )
  { }
  virtual void start( void )
  {
    const char* shader_str = R"(
#version 430
layout (local_size_x = 32, local_size_y = 32, local_size_z = 1) in;
layout (rgba16f, binding = 0) uniform image2D img_output;
layout (rgba16f, binding = 1) uniform image2D img_output2;

uniform float time;

void main () {
  vec4 pixel = vec4 (0.0, 0.0, 0.0, 1.0);
  ivec2 pixel_coords = ivec2 (gl_GlobalInvocationID.xy);

  float max_x = 5.0;
  float max_y = 5.0;
  ivec2 dims = imageSize (img_output);
  float x = (float(pixel_coords.x * 2 - dims.x) / dims.x);
  float y = (float(pixel_coords.y * 2 - dims.y) / dims.y);
  vec3 ray_o = vec3 (x * max_x, y * max_y, 0.0);
  vec3 ray_d = vec3 (0.0, 0.0, -1.0); // ortho

  vec3 sphere_c = vec3 (0.0, sin(time), -10.0);
  float sphere_r = 1.0;

  vec3 omc = ray_o - sphere_c;
  float b = dot (ray_d, omc);
  float c = dot (omc, omc) - sphere_r * sphere_r;
  float bsqmc = b * b - c;
  float t = 10000.0;
  // hit one or both sides
  if (bsqmc >= 0.0) {
    pixel = vec4 (0.4, 0.4, 1.0, 1.0);
  }

  imageStore (img_output, pixel_coords, pixel);
  pixel = vec4( gl_WorkGroupID / vec3 ( gl_NumWorkGroups ), 1.0 );
  imageStore (img_output2, pixel_coords, pixel);
})";

    computeShader = new mb::compute::ComputeShader( shader_str );
    computeShader->addUniform( "time", std::make_shared< mb::FloatUniform >( 0.0f ) );
  }
  virtual void update( const mb::Clock& clock )
  {
    _time += clock.getDeltaTime( );

    computeShader->uniform( "time" )->value( _time );
    
    computeShader->dispatch( 16, 16, 1 );
  }
protected:
  mb::compute::ComputeShader* computeShader;
  float _time;
};

int main( )
{
  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 512, 512 ) );
  window->init( );

  // texture handle and dimensions
  int tex_w = 512, tex_h = 512;
  mb::Texture2D* tt = new mb::Texture2D( tex_w, tex_h,
    mb::Texture::FormatTexture::RGBA16F, true );
  {
    tt->bind( );
    tt->apply( );
    tt->bindToImageUnit( 0, GL_WRITE_ONLY, GL_RGBA16F );
  }

  mb::Texture2D* tt2 = new mb::Texture2D( tex_w, tex_h,
    mb::Texture::FormatTexture::RGBA16F, true );
  {
    tt2->bind( );
    tt2->apply( );
    tt2->bindToImageUnit( 1, GL_WRITE_ONLY, GL_RGBA16F );
  }

  mb::PostProcessMaterial ppm(R"(
#version 430
in vec2 uv;

out vec4 fragColor;

uniform sampler2D targetTex;
uniform sampler2D targetTex2;

void main( )
{
  fragColor = vec4( texture( targetTex, uv ).rgb, 1.0 );

  float x = gl_FragCoord.x/512.0;
  if (x < 0.5 )
  {
    fragColor = vec4( texture( targetTex2, uv ).rgb, 1.0 );
  }
  //fragColor = vec4( uv, 0.0, 1.0 );
})");

  ppm.addUniform( "targetTex", std::make_shared< mb::TextureUniform >( tt ) );
  ppm.addUniform( "targetTex2", std::make_shared< mb::TextureUniform >( tt2 ) );

  mb::Group* scene = new mb::Group( "Scene" );
  scene->addComponent( new TimeComponent( ) );

  mb::Application app;
  app.setSceneNode( scene );

  mb::Clock clockTime;
  clockTime.reset( );

  float time = 0.0f;

  while ( window->isRunning( ) )
  {
    window->pollEvents( );

    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Esc ) )
    {
      window->close( );
      break;
    }
    
    clockTime.tick( );

    app.update( );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    ppm.use( );

    app.getRenderer( )->drawScreenQuad( );

    window->swapBuffers( );
  }

  return 0;
}
