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

#define MAXPOINTS 500		// Change this to increment num of points
#define RANDOM_POINT 0.02

std::vector< mb::Vector3 > createPoints( void )
{
  srand( time( NULL ) );
  std::vector< mb::Vector3 > points( MAXPOINTS );
  for ( int i = 0; i < MAXPOINTS; ++i )
  {
    points[ i ].x( ) = ( ( float ) ( std::rand( ) % 1000 ) ) * RANDOM_POINT;
    points[ i ].y( ) = -5.0f;
    points[ i ].z( ) = ( ( float ) ( std::rand( ) % 1000 ) ) * RANDOM_POINT;
  }


  return points;
}

class TimeUpdaterComponent : public mb::Component
{
  IMPLEMENT_COMPONENT( TimeUpdaterComponent )
public:
  virtual void update( const mb::Clock& clock )
  {
    mb::MaterialComponent* mc = node( )->getComponent<mb::MaterialComponent>( );

    auto mat = mc->first( );

    mat->uniform( "time" )->value( ( float ) clock.getAccumTime( ) );
  }
};

std::shared_ptr<mb::Program> createProgram( std::shared_ptr<mb::Program> program )
{
  program->loadVertexShaderFromText( R"(
    #version 330
    layout( location = 0 ) in vec3 inPos;

    void main( void )
    {
      gl_Position = vec4( inPos, 1.0 );
    })" );
  program->loadGeometryShaderFromText( R"(
    #version 330

    layout(points) in;
    layout(triangle_strip) out;
    layout(max_vertices = 12) out;

    out vec2 texCoord;

    uniform mat4 MB_MATRIXM;
    uniform mat4 MB_MATRIXV;
    uniform mat4 MB_MATRIXP;

    mat4 rotationMatrix(vec3 axis, float angle)
    {
      axis = normalize(axis);
      float s = sin(angle);
      float c = cos(angle);
      float oc = 1.0 - c;

      float x = axis.x;
      float y = axis.y;
      float z = axis.z;
    
      return mat4(
              oc * x * x + c,  oc * x * y - z * s,  oc * z * x + y * s,  0.0,
          oc * x * y + z * s,      oc * y * y + c,  oc * y * z - x * s,  0.0,
          oc * z * x - y * s,  oc * y * z + x * s,      oc * z * z + c,  0.0,
                          0.0,                 0.0,                 0.0,  1.0
      );
    }

    const float GrassPatchSize = 3.0;
    const float GrassPatchHeight = 1.5;
	  const float WindStrength = 1.0;
	  const vec3 WindDirection = vec3(1.0, 0.0, 1.0);

    uniform float time;

    void main( void )
    {
      mat4 mvp = MB_MATRIXP * MB_MATRIXV * MB_MATRIXM;
    
      vec3 grassFieldPos = gl_in[0].gl_Position.xyz;

      const float rad = radians( 45.0 );
      const float sin45 = sin( rad );
      const float cos45 = cos( rad );

      const vec3 baseDir[3]=vec3[3](
        vec3(1.0, 0.0, 0.0),
        vec3(float(cos45), 0.0f, float(sin45)),
        vec3(float(cos45), 0.0f, float(sin45))
      );

      for(int i = 0; i < 3; ++i)
      {
        // Grass patch top left vertex
        vec3 baseDirRotated = (
           rotationMatrix(
              vec3(0.0, 1.0, 0.0), sin(time * 0.7) * 0.1) 
          * vec4(baseDir[i], 1.0)).xyz;
        
        float WindPower = 0.5 + 
          sin(grassFieldPos.x / 30.0 +
          grassFieldPos.z / 30.0 +
          time * (1.2 + WindStrength / 20.0) );
        if( WindPower < 0.0 )
        {
          WindPower = WindPower * 0.2;
        }
        else
        {
          WindPower = WindPower * 0.3;
        }
		
        WindPower *= WindStrength;

        vec3 grassTL = grassFieldPos - baseDirRotated * GrassPatchSize * 0.5 
          + WindDirection * WindPower;
        grassTL.y += GrassPatchHeight;   
        gl_Position = mvp * vec4(grassTL, 1.0);
        texCoord = vec2(0.0, 1.0);
        EmitVertex();
        
        // Grass patch bottom left vertex
        vec3 grassBL = grassFieldPos - baseDir[i] * GrassPatchSize * 0.5;  
        gl_Position = mvp * vec4(grassBL, 1.0);
        texCoord = vec2(0.0, 0.0);
        EmitVertex();
                                       
        // Grass patch top right vertex
        vec3 grassTR = grassFieldPos + baseDirRotated * GrassPatchSize * 0.5  
          + WindDirection * WindPower;
        grassTR.y += GrassPatchHeight;  
        gl_Position = mvp * vec4(grassTR, 1.0);
        texCoord = vec2(1.0, 1.0);
        EmitVertex();
        
        // Grass patch bottom right vertex
        vec3 grassBR = grassFieldPos + baseDir[i] * GrassPatchSize * 0.5;  
        gl_Position = mvp * vec4(grassBR, 1.0);
        texCoord = vec2(1.0, 0.0);
        EmitVertex();
        
        EndPrimitive();
      }
    })" );
  program->loadFragmentShaderFromText( R"(
    #version 330
    in vec2 texCoord;

    out vec4 fragColor;

    uniform sampler2D grassTex;

    const float fAlphaTest = 0.25;
    const float fAlphaMultiplier = 1.5;

    void main( void )
    {
      vec4 vTexColor = texture(grassTex, texCoord);
      float fNewAlpha = vTexColor.a * fAlphaMultiplier;    
           
      if(fNewAlpha < fAlphaTest) discard;
	
      if(fNewAlpha > 1.0f)
      fNewAlpha = 1.0f;	
		
      fragColor = vec4(vTexColor.xyz, fNewAlpha);
    })" );
  program->compileAndLink( );
  program->autocatching( );

  return program;
}

mb::Geometry* generateGeom( const mb::Color& )
{
  auto geom = new mb::Geometry( );

  geom->addPrimitive( new mb::PointCloudPrimitive( createPoints( ) ) );

  mb::Material* customMaterial = new mb::Material( );
  customMaterial->program = createProgram( customMaterial->program );
  customMaterial->addUniform( MB_PROJ_MATRIX,
    std::make_shared< mb::Matrix4Uniform >( ) );
  customMaterial->addUniform( MB_VIEW_MATRIX,
    std::make_shared< mb::Matrix4Uniform >( ) );
  customMaterial->addUniform( MB_MODEL_MATRIX,
    std::make_shared< mb::Matrix4Uniform >( ) );
  customMaterial->addUniform( "time",
    std::make_shared< mb::FloatUniform >( ) );

  mb::Texture2D* TexDiffuse = mb::Texture2D::loadFromImage( "grass.png" );
  customMaterial->addUniform( "grassTex",
    std::make_shared< mb::TextureUniform >( TexDiffuse ) );

  //customMaterial->state( ).culling( ).setEnabled( false );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  geom->addComponent( new TimeUpdaterComponent( ) );

  return geom;
}

mb::Group* createScene( void )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 60.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 7.05f, 0.0f, 30.0f );

  auto node = generateGeom( mb::Color::GREY );

  scene->addChild( node );

  camera->addComponent( new mb::FreeCameraComponent( ) );
  scene->addChild( camera );

  return scene;
}

int main( void )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );
  window->setTitle( "Earth" );

  glEnable( GL_DEPTH_TEST );

  glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );

  glEnable( GL_DEPTH_TEST );

  mb::Application app;

  app.setSceneNode( createScene( ) );

  while ( window->isRunning( ) )
  {
    window->pollEvents( );

    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Esc ) )
    {
      window->close( );
      break;
    }

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    app.update( );

    window->swapBuffers( );
  }
  return 0;
}
