/**
 * Copyright (c) 2017, Monkey Brush
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#include <iostream>
#include <string>

#include <mb/mb.h>
#include <routes.h>

unsigned int vao;
unsigned int createVAO( )
{
  // Set up vertex data (and buffer(s)) and attribute pointers
  float vertices[ ] = {
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

    -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

    -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

    -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0, 0.0f, 1.0f,
    1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0, 1.0f, 0.0f,
    -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0, 0.0f, 0.0f,
    -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0, 0.0f, 1.0f
  };
  unsigned int VBO, VAO;
  glGenVertexArrays( 1, &VAO );
  glGenBuffers( 1, &VBO );

  glBindVertexArray( VAO );

  glBindBuffer( GL_ARRAY_BUFFER, VBO );
  glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

  // Position attribute
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid* ) 0 );
  glEnableVertexAttribArray( 0 );
  // Normal attribute
  glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid* ) ( 3 * sizeof( GLfloat ) ) );
  glEnableVertexAttribArray( 1 );
  // TexCoord attribute
  glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid* ) ( 6 * sizeof( GLfloat ) ) );
  glEnableVertexAttribArray( 2 );

  glBindVertexArray( 0 ); // Unbind VAO

  return VAO;
}

mb::Program* createProgram( )
{
  mb::Program* program = new mb::Program( );
  program->loadVertexShaderFromText( R"(
    #version 330 core
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 normal;
    layout (location = 2) in vec2 texCoord;

    uniform mat4 mb_MatrixM;
    uniform mat4 mb_MatrixV;
    uniform mat4 mb_MatrixP;

    out vec3 outPosition;
    out vec3 Normal;
        out vec2 TexCoord;

    void main()
    {
      gl_Position = mb_MatrixP * mb_MatrixV * mb_MatrixM * vec4(position, 1.0);
      mat3 normalMatrix = mat3(transpose(inverse( mb_MatrixM )));
      Normal = normalMatrix * normal;
      outPosition = vec3( mb_MatrixM * vec4( position, 1.0 ) );
      TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
    })" );
  program->loadFragmentShaderFromText( R"(
    #version 330 core
    out vec4 fragColor;

    in vec3 outPosition;
    in vec3 Normal;
    in vec2 TexCoord;

    uniform sampler2D _MainTex;

    uniform int mb_NumLights;

    #define MAX_LIGHTS 5

    // view-space vertex light positions (position,1),
    //    or (-direction,0) for directional lights.
    uniform vec4 mb_LightPosition[ MAX_LIGHTS ];

    uniform vec3 mb_LightColor[ MAX_LIGHTS ];

    // x = cos(spotAngle/2) or -1 for non-spot
    // y = 1/cos(spotAngle/4) or 1 for non-spot
    // z = quadratic attenuation
    // w = range*range
    uniform vec4 mb_LightAtt[ MAX_LIGHTS ];

    struct SurfaceOutput
    {
      vec3 Albedo;
      vec3 Normal;
      vec3 Emissiton;
      float Specular;
      float Gloss;
      float Alpha;
    };

    uniform mat4 mb_MatrixV;

    void surf( out SurfaceOutput s );

    //const vec3 _LightColor0 = vec3( 0.0, 1.0, 0.8 );
    //const vec3 _LightPos0 = vec3( 2.0, 15.0, 15.0 );

    vec4 LightingPhong( in SurfaceOutput s, in vec3 _LightPos0, in vec3 _LightColor0 )
    {
      vec3 lightPosition = _LightPos0;
      vec3 viewPos = -transpose(mat3(mb_MatrixV)) * mb_MatrixV[3].xyz;

      // Ambient
      vec3 ambient = vec3(0.4);

      // Diffuse
      vec3 lightDir = normalize( lightPosition - outPosition );
      float diff = max( dot( s.Normal, lightDir ), 0.0 );
      vec3 diffuse = diff * _LightColor0;

      // Specular
      vec3 viewDir = normalize( viewPos - outPosition );
      vec3 h = normalize( lightDir + viewDir );

      vec3 reflectDir = reflect(-lightDir, s.Normal);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
      vec3 specular = vec3(0.3) * spec;

#ifdef RIM_LIGHTING // TODO
  // Rim Lighting
  //vec3 rim = pow( 1.0 - saturate( dot( viewDirection, normalDirection ) ), _RimPower );
  //vec3 rimLighting = att * _LightColor0.rgb * saturate( dot( normalDirection, lightDir ) ) * rim * _RimColor.rgb;
#endif
  // TODO (CRISTIAN) https://gist.github.com/patriciogonzalezvivo/3a81453a24a542aabc63

      return vec4(
        ( ambient + diffuse + specular ) * s.Albedo,
        1.0
      );
    }

    /*vec4 LightingBlinnPhong( in SurfaceOutput s )
    {
      vec3 _LightPos0 = mb_LightPosition[ 0 ].xyz;
      vec3 lightPosition = _LightPos0;
      vec3 viewPos = -transpose(mat3(mb_MatrixV)) * mb_MatrixV[3].xyz;

      // Ambient
      vec3 ambient = vec3(0.4);

      // Diffuse
      vec3 lightDir = normalize( lightPosition - outPosition );
      float diff = max( dot( s.Normal, lightDir ), 0.0 );
      vec3 diffuse = diff * _LightColor0;

      // Specular
      vec3 viewDir = normalize( viewPos - outPosition );
      vec3 h = normalize( lightDir + viewDir );
      float spec = pow(max(dot(s.Normal, h), 0.0), 32.0);
      vec3 specular = vec3(0.3) * spec;

      return vec4(
        ( ambient + diffuse + specular ) * s.Albedo,
        1.0
      );
    }

    vec4 LightingLambert( in SurfaceOutput s )
    {
      vec3 _LightPos0 = mb_LightPosition[ 0 ].xyz;
      vec3 lightPosition = _LightPos0;
      vec3 viewPos = -transpose(mat3(mb_MatrixV)) * mb_MatrixV[3].xyz;

      vec3 lightDir = normalize(lightPosition - outPosition);

      vec3 ambient = vec3(0.4);

      float diff = max( dot( s.Normal, lightDir ), 0.0 );
      vec3 diffuse = diff * _LightColor0;

      return vec4(
        ( ambient + diffuse ) * s.Albedo,
        1.0
      );
    }*/

    void main( )
    {
      SurfaceOutput s;
      surf( s );
      fragColor = vec4( vec3( 0.0 ), 1.0 );
      for (int i = 0; i < MAX_LIGHTS; ++i )
      {
        if ( i >= mb_NumLights ) break;

        if ( mb_LightPosition[ i ].w == 0.0 )
        {
          // DirectionalLight( mb_LightPosition[ i ].xyz, )
        } else
        {
          // PointLight
        }
        //fragColor.rgb += mb_LightColor[ i ].rgb;
        fragColor += LightingPhong( s, mb_LightPosition[ i ].xyz, mb_LightColor[ i ].rgb );
      }
    }

    const vec3 color = vec3( 1.0, 0.5, 0.9 );

    void surf( out SurfaceOutput s )
    {
      s.Albedo = texture(_MainTex, TexCoord).rgb; //color;
      s.Normal = Normal;
    })" );
  program->compileAndLink( );
  program->autocatching( );

  return program;
}

mb::Geometry* generateGeom( const mb::Color& c, const std::string& tex )
{
  auto geom = new mb::Geometry( );

  mb::ColorMaterial* customMaterial = new mb::ColorMaterial( );
  customMaterial->setColor( c );

  mb::Texture2D* TexDiffuse = mb::Texture2D::loadFromImage( tex );
  customMaterial->setColorMap( TexDiffuse );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  //geom->addComponent( new mb::RotateComponent( mb::Vector3::ONE, 0.15f ) );

  return geom;
}

class RotationComponent : public mb::Component
{
  IMPLEMENT_COMPONENT( RotationComponent )
public:
  RotationComponent( float speed )
    : _speed( speed )
    , _time( 0.0f )
  { }
  virtual void update( const mb::Clock& clock )
  {
    node( )->local( ).rotate( ).fromAxisAngle(
      mb::Vector3::Y_AXIS, _time * mb::Mathf::TWO_PI );
    _time += _speed *clock.getDeltaTime( );
  }
protected:
  float _speed;
  float _time;
};

mb::Group* createScene( void )
{
  vao = createVAO( );
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 60.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 10.0f );
  camera->addComponent( new mb::FreeCameraComponent( ) );
  scene->addChild( camera );

  float rotationSpeed = 0.02f;

  auto node = generateGeom( mb::Color::WHITE, "earth/earth_diffuse.jpg" );
  scene->addChild( node );
  node->addComponent( new RotationComponent( rotationSpeed ) );

  auto node2 = generateGeom( mb::Color::WHITE, "earth/earth_clouds.png" );
  node2->getComponent<mb::MaterialComponent>( )->
    first( )->state().blending().setEnabled(true);
  node2->local( ).setScale( 1.005f );
  node2->addComponent( new RotationComponent( 1.25f * rotationSpeed ) );
  scene->addChild( node2 );

  return scene;
}

int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );

  glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );

  mb::Group* _scene = createScene( );

  _scene->perform( mb::UpdateWorldState( ) );

  std::vector< mb::Camera* > _cameras;

  mb::FetchCameras fetchCameras;
  _scene->perform( fetchCameras );
  fetchCameras.forEachCameras( [ &] ( mb::Camera* c )
  {
    if ( mb::Camera::getMainCamera( ) == nullptr || c->isMainCamera( ) )
    {
      mb::Camera::setMainCamera( c );
    }
    _cameras.push_back( c );
  } );

  _scene->perform( mb::StartComponents( ) );

  glEnable( GL_DEPTH_TEST );

  mb::Clock clockTime;
  clockTime.reset( );

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

    _scene->perform( mb::UpdateComponents( clockTime ) );
    _scene->perform( mb::UpdateWorldState( ) );
    std::vector< mb::BatchQueuePtr > bqCollection;

    std::vector< mb::Light* > lights;
    mb::FetchLights fl;
    _scene->perform( fl );
    lights = fl.lights( );

    for ( mb::Camera* c : _cameras )
    {
      if ( c != nullptr && c->isEnabled( ) )
      {
        mb::BatchQueuePtr bq = std::make_shared< mb::BatchQueue >( );
        mb::ComputeBatchQueue cbq( c, bq );
        _scene->perform( cbq );
        bqCollection.push_back( bq );
      }
    };

    if ( !bqCollection.empty( ) )
    {
      mb::BatchQueuePtr mainQueue = nullptr;
      std::for_each( bqCollection.begin( ), bqCollection.end( ), [ &] ( mb::BatchQueuePtr bq )
      {
        if ( bq->getCamera( ) != mb::Camera::getMainCamera( ) )
        {
          std::cout << "OUTSCREEN" << std::endl;
        }
        else
        {
          mainQueue = bq;
        }
      } );

      if ( mainQueue != nullptr )
      {
        unsigned int numLights = lights.size( );
        auto renderables = mainQueue->renderables( mb::BatchQueue::RenderableType::OPAQUE );
        if ( !renderables.empty( ) )
        {
          for ( mb::Renderable& renderable : renderables )
          {
            //std::cout << "ZDIST: " << renderable.zDistance << std::endl;

            //if ( renderable.zDistance > 128.0f ) continue;

            mb::MaterialComponent* mc = renderable.geometry->getComponent<mb::MaterialComponent>( );

            auto mat = mc->first( );

            mat->uniform( MB_PROJ_MATRIX )->value( mainQueue->getProjectionMatrix( ) );
            mat->uniform( MB_VIEW_MATRIX )->value( mainQueue->getViewMatrix( ) );
            mat->uniform( MB_MODEL_MATRIX )->value( renderable.modelTransform );

            mat->use( );

            glBindVertexArray( vao );
            glDrawArrays( GL_TRIANGLES, 0, 36 );
            glBindVertexArray( 0 );

            mat->unuse( );
          }
          //std::cout << std::endl << std::endl << " -------------------------- " << std::endl << std::endl;
        }
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        renderables = mainQueue->renderables( mb::BatchQueue::RenderableType::TRANSPARENT );
        if ( !renderables.empty( ) )
        {
          for ( mb::Renderable& renderable : renderables )
          {
            //std::cout << "ZDIST: " << renderable.zDistance << std::endl;

            //if ( renderable.zDistance > 128.0f ) continue;

            mb::MaterialComponent* mc = renderable.geometry->getComponent<mb::MaterialComponent>( );

            auto mat = mc->first( );

            mat->uniform( MB_PROJ_MATRIX )->value( mainQueue->getProjectionMatrix( ) );
            mat->uniform( MB_VIEW_MATRIX )->value( mainQueue->getViewMatrix( ) );
            mat->uniform( MB_MODEL_MATRIX )->value( renderable.modelTransform );

            mat->use( );

            glBindVertexArray( vao );
            glDrawArrays( GL_TRIANGLES, 0, 36 );
            glBindVertexArray( 0 );

            mat->unuse( );
          }
          //std::cout << std::endl << std::endl << " -------------------------- " << std::endl << std::endl;
        }
        glDisable(GL_BLEND);
      }
    }

    window->swapBuffers( );
  }

  delete _scene;

  return 0;
}
