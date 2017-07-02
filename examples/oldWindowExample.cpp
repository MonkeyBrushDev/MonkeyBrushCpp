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

unsigned int createVAO( )
{
  // Set up vertex data (and buffer(s)) and attribute pointers
  float vertices[] = {
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f, -1.0f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, -1.0f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
     1.0f,  1.0f, -1.0f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
    -1.0f,  1.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,

    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  0.0f, 0.0f,  1.0f,  1.0f, 1.0f,
     1.0f,  1.0f,  1.0f,  0.0f, 0.0f,  1.0f,  1.0f, 1.0f,
    -1.0f,  1.0f,  1.0f,  0.0f, 0.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  1.0f,  0.0f, 0.0f,

    -1.0f,  1.0f,  1.0f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, -1.0f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  1.0f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
    -1.0f,  1.0f,  1.0f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

     1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
     1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
     1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
     1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f,

    -1.0f, -1.0f, -1.0f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
     1.0f, -1.0f, -1.0f,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
     1.0f, -1.0f,  1.0f,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
     1.0f, -1.0f,  1.0f,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -1.0f, -1.0f,  1.0f,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0.0,   0.0f, 1.0f,
     1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0.0,   1.0f, 1.0f,
     1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 0.0,   1.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 0.0,   1.0f, 0.0f,
    -1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 0.0,   0.0f, 0.0f,
    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0.0,   0.0f, 1.0f
  };
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  // Normal attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  // TexCoord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0); // Unbind VAO

  return VAO;
}

mb::Program* quadProgram( )
{
  mb::Program* program = new mb::Program( );
  program->loadVertexShaderFromText(R"(
    #version 330 core
    layout (location = 0) in vec3 position;
    out vec2 TexCoord;
    void main( )
    {
      gl_Position = vec4(position, 1.0);
      TexCoord = vec2(position.xy * 0.5) + vec2(0.5);
    }
  )");
  program->loadFragmentShaderFromText(R"(
    #version 330 core
    in vec2 TexCoord;
    out vec4 fragColor;
    uniform sampler2D tex;
    void main( )
    {
      fragColor = vec4(TexCoord, 0.0, 1.0);
      fragColor = texture(tex, TexCoord);

      float f = fragColor.r + fragColor.g + fragColor.b;
      f /= 3.0f;

      if ( f > 0.5 ) discard;
    }
  )");
  program->compileAndLink( );
  program->autocatching();

  return program;
}

mb::Program* initProgram( )
{
  mb::Program* program = new mb::Program( );
  program->loadVertexShaderFromText(R"(
    #version 330 core
    layout (location = 0) in vec3 position;
    layout (location = 2) in vec2 texCoord;

    out vec2 TexCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
      gl_Position = projection * view * model * vec4(position, 1.0f);
      TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
    })");
  program->loadFragmentShaderFromText(R"(
    #version 330 core
    in vec2 TexCoord;

    out vec4 fragColor;

    uniform sampler2D myTexture;
    uniform vec3 color;

    void main()
    {
      fragColor = vec4( TexCoord, 0.0, 1.0 );
      fragColor = texture( myTexture, TexCoord );
      fragColor *= vec4(color, 1.0);
    })");
  program->compileAndLink( );
  program->autocatching();

  return program;
}
mb::Program* initProgramNoTex( )
{
  mb::Program* program = new mb::Program( );
  program->loadVertexShaderFromText(R"(
    #version 330 core
    layout (location = 0) in vec3 position;
    layout (location = 2) in vec2 texCoord;

    out vec2 TexCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
      gl_Position = projection * view * model * vec4(position, 1.0f);
      TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
    })");
  program->loadFragmentShaderFromText(R"(
    #version 330 core
    in vec2 TexCoord;

    out vec4 fragColor;

    uniform vec3 color;

    void main()
    {
      fragColor = vec4( TexCoord, 0.0, 1.0 );
      fragColor *= vec4(color, 1.0);
    })");
  program->compileAndLink( );
  program->autocatching();

  return program;
}

class ToggleDepthTest : public mb::Component
{
  IMPLEMENT_COMPONENT( ToggleDepthTest )
public:
  virtual void update( const mb::Clock& ) override
  {
    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Plus ) )
    {
      std::cout << "ENABLE" << std::endl;
      glEnable(GL_DEPTH_TEST);
    } else  if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Minus ) )
    {
      glDisable(GL_DEPTH_TEST);
      std::cout << "DISABLE" << std::endl;
    }
    // std::cout << mb::Input::MouseX( ) << ", " << mb::Input::MouseY( ) << std::endl;
  }
};

unsigned int vao;

mb::Group* createScene( void )
{
  vao = createVAO( );

  mb::Material customPPMaterial;
  customPPMaterial.addUniform("tex",
        std::make_shared< mb::Uniform >(mb::UniformType::Integer, 0 ));
  customPPMaterial.program = quadProgram( );


  mb::StandardMaterial* customMaterial = new mb::StandardMaterial( ); /* = new mb::Material;
  customMaterial->program = initProgram( );
  customMaterial->addUniform("projection",
        std::make_shared< mb::Uniform >( mb::UniformType::Matrix4 ) );
  customMaterial->addUniform("view",
        std::make_shared< mb::Uniform >( mb::UniformType::Matrix4 ) );
  customMaterial->addUniform("model",
        std::make_shared< mb::Uniform >( mb::UniformType::Matrix4 ) );
  customMaterial->addUniform("myTexture",
        std::make_shared< mb::Uniform >( mb::UniformType::TextureSampler ) );
  customMaterial->addUniform("color",
        std::make_shared< mb::Uniform >( mb::UniformType::Vector3, mb::Vector3(
                                             1.0f, 0.0f, 0.0f) ) );*/


  mb::StandardMaterial2* customMaterial2 = new mb::StandardMaterial2( ); /*new mb::Material;
  customMaterial2->program = initProgramNoTex();
  customMaterial2->addUniform("projection",
        std::make_shared< mb::Uniform >( mb::UniformType::Matrix4 ) );
  customMaterial2->addUniform("view",
        std::make_shared< mb::Uniform >( mb::UniformType::Matrix4 ) );
  customMaterial2->addUniform("model",
        std::make_shared< mb::Uniform >( mb::UniformType::Matrix4 ) );
  customMaterial2->addUniform("color",
        std::make_shared< mb::Uniform >( mb::UniformType::Vector3, mb::Vector3(
                                             0.0f, 1.0f, 0.0f) ) );*/

  auto scene = new mb::Group( "scene" );
  auto camera = new mb::Camera( 45.0f, 500/500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 8.0f );

  camera->addComponent( new mb::FreeCameraComponent( ) );
  camera->addComponent( new ToggleDepthTest( ) );

  scene->addChild( camera );

  auto cubes = new mb::Group( "Cubes" );
  mb::Group* g1 = new mb::Group("MyGroup1");
  mb::Group* g2 = new mb::Group("MyGroup2");

  std::vector< mb::Vector3 > cubePositions = {
    mb::Vector3(  2.0f,  5.0f, -15.0f ),
    mb::Vector3(  0.0f,  0.0f,   0.0f ),
    mb::Vector3( -1.5f, -2.2f,  -2.5f ),
    mb::Vector3( -3.8f, -2.0f, -12.3f ),
    mb::Vector3(  2.4f, -0.4f,  -3.5f ),
    mb::Vector3( -1.7f,  3.0f,  -7.5f ),
    mb::Vector3(  1.3f, -2.0f,  -2.5f ),
    mb::Vector3(  1.5f,  2.0f,  -2.5f ),
    mb::Vector3(  1.5f,  0.2f,  -1.5f ),
    mb::Vector3( -1.3f,  1.0f,  -1.5f )
  };


  mb::Texture2D* normalTex = mb::Texture2D::loadFromImage( "NormalMap.png" );
  mb::Texture* tex = mb::Texture2D::loadFromImage( "texture.jpg" );
  mb::Texture* tex2 = mb::Texture2D::loadFromImage( "tex_metal_005_t.jpg" );
  mb::Texture2D* tex4 = mb::Texture2D::loadFromImage( "crate.jpg" );

  mb::Texture2D* chesterDiffuse = mb::Texture2D::loadFromImage( "chesterfieldDiffuseMap.png" );
  mb::Texture2D* chesterDNormal = mb::Texture2D::loadFromImage( "chesterfieldNormalMap.png" );
  mb::Texture2D* bumpTex = mb::Texture2D::loadFromImage( "DisplacementMap.png" );

  unsigned int WW = 50, HH = 50;
  unsigned char * tex_data = new unsigned char[ 4 * WW * HH ];

  mb::Random r;

  for ( unsigned int j = 0; j < WW * HH; ++j )
  {
    float v = r.nextInt( 0, 255 );
    tex_data[ j * 4 + 0 ] = v;
    tex_data[ j * 4 + 1 ] = v;
    tex_data[ j * 4 + 2 ] = v;
    tex_data[ j * 4 + 3 ] = v;
  }

  mb::Texture2D* tex3 = new mb::Texture2D( WW, HH,
                                           mb::Texture::FormatTexture::RGBA, true );
  tex3->loadRawTexture( tex_data );
  tex3->apply( );
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  //customMaterial->uniform("DiffuseTexture")->value(tex3);
  //customMaterial2->uniform("DiffuseTexture")->value(tex3);
  customMaterial->setColorMap( chesterDiffuse );
  customMaterial->setNormalMap( chesterDNormal );
  customMaterial->setColor( mb::Color::GREEN );

  customMaterial2->setColorMap( tex4 );
  customMaterial2->setBumpMap( bumpTex );
  customMaterial2->setColor( mb::Color::GOLD );

  size_t numCubes = cubePositions.size( );
  size_t middleCubes = numCubes / 2;

  for ( unsigned int i = 0; i < middleCubes; ++i )
  {
    auto geom = new mb::Geometry( std::string( "CubeGeom" ) + std::to_string( i + 1 ) );
    //geom->local( ).setPosition( cubePositions[ i ] );
    geom->local( ).position( ) = cubePositions[ i ];
    geom->local( ).setScale( mb::Vector3( 0.5f ) );

    mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>();

    if ( i % 2 == 0 )
    {
      mc->addMaterial( mb::MaterialPtr( customMaterial ) );
    }
    else
    {
      mc->addMaterial( mb::MaterialPtr( customMaterial2 ) );
    }

    // TODO: HARDCODED
    if ( i % 3 == 0 ) { geom->setCastShadows( false ); }

    geom->addComponent( new mb::RotateComponent( mb::Vector3( -1.0f, -1.0f,  0.0f ), 0.1f ) );

    geom->layer( ).set( i );

    g1->addChild( geom );
  }
  cubes->addChild( g1 );
  for ( unsigned int i = middleCubes; i < numCubes; ++i )
  {
    auto geom = new mb::Geometry( std::string( "CubeGeom" ) + std::to_string( i + 1 ) );
    geom->local( ).setPosition( cubePositions[ i ] );
    geom->local( ).setScale( mb::Vector3( 0.5f ) );

    mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>();

    if ( i % 2 == 0 )
    {
      mc->addMaterial( mb::MaterialPtr( customMaterial ) );
    }
    else
    {
      mc->addMaterial( mb::MaterialPtr( customMaterial2 ) );
    }

    // if ( i % 3 == 0 ) { 0.0f, 1.0f, 0.0,   geom->setCastShadows( false ); } // TODO: HARDCODED

    geom->addComponent( new mb::RotateComponent( mb::Vector3( -1.0f, -1.0f,  0.0f ) * -1.0f, 0.1f ) );

    geom->layer( ).set( i );

    g2->addChild( geom );
  }
  cubes->addChild( g2 );
  std::cout << (g1->getNumChildren( ) + g2->getNumChildren( )) << std::endl;

  /*auto geom = new mb::Geometry( std::string( "CubeGeom" ) );
  geom->local( ).setPosition( mb::Vector3::ZERO );
  //geom->local( ).setRotation( mb::Vector3( -1.0f, -1.0f, 0.0f ), mb::Mathf::degToRad( 260.0f ) );
  geom->local( ).setScale( mb::Vector3( 0.5f ) );

  std::cout << geom->local( ).getRotation( ) << std::endl;

  geom->addComponent( new mb::RotateComponent( mb::Vector3( -1.0f, -1.0f,  0.0f ) * -1.0f, 0.1f ) );

  g2->addChild( geom );*/

  scene->addChild( cubes );

  return scene;
}

#include <routes.h>

int main( )
{
  mb::FileSystem::getInstance()->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );

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

  while( window->isRunning( ) )
  {
    window->pollEvents( );

    if (mb::Input::isKeyPressed(mb::Keyboard::Key::Esc))
    {
      window->close( );
      break;
    }

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    clockTime.tick( );

    _scene->perform( mb::UpdateComponents( clockTime ) );

    _scene->perform( mb::UpdateWorldState( ) );

    std::vector< mb::BatchQueuePtr > bqCollection;

    for( mb::Camera* c: _cameras)
    {
      if ( c != nullptr && c->isEnabled( ) )
      {
        mb::BatchQueuePtr bq = std::make_shared< mb::BatchQueue >( );
        mb::ComputeBatchQueue cbq( c, bq );
        _scene->perform( cbq );
        bqCollection.push_back( bq );
      }
    };

    if (!bqCollection.empty())
    {
      mb::BatchQueuePtr mainQueue = nullptr;
      std::for_each( bqCollection.begin(), bqCollection.end(), [&](mb::BatchQueuePtr bq)
      {
        if (bq->getCamera( ) != mb::Camera::getMainCamera( ))
        {
          std::cout << "OUTSCREEN" << std::endl;
        }
        else
        {
          mainQueue = bq;
        }
      });

      if(mainQueue.get() != nullptr)
      {
        auto renderables = mainQueue->renderables( mb::BatchQueue::RenderableType::OPAQUE );
        if ( !renderables.empty( ) )
        {
          for ( mb::Renderable& renderable : renderables )
          {
            //std::cout << "ZDIST: " << renderable->zDistance << std::endl;

            mb::MaterialComponent* mc = renderable.geometry->getComponent<mb::MaterialComponent>();

            auto mat = mc->first();

            mat->uniform("projection")->value(mainQueue->getProjectionMatrix());
            mat->uniform("view")->value(mainQueue->getViewMatrix());
            mat->uniform("model")->value(renderable.modelTransform);
            mat->use( );

            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);

            mat->unuse( );
          }
        }
      }
    }


    //glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //tex2->bind( 0 );
    //mb::Renderer::drawScreenQuad(&customPPMaterial);


    window->swapBuffers( );
  }
  return 0;
}