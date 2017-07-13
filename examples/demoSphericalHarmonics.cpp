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

mb::Material* createMaterial( )
{
  mb::Material* customMaterial = new mb::Material( );

  customMaterial->program = std::make_shared< mb::Program >( );
  customMaterial->program->loadVertexShaderFromText( R"(
        #version 430
        layout(location = 0) in vec3 position;
        layout(location = 1) in vec3 normal;
        out vec3 outPosition;
        flat out vec3 outNormal;

        uniform mat4 MB_MATRIXP;
        uniform mat4 MB_MATRIXV;
        uniform mat4 MB_MATRIXM;

        void main( void )
        {
          outPosition = vec3(MB_MATRIXM * vec4(position, 1.0));
          gl_Position = MB_MATRIXP * MB_MATRIXV * vec4(outPosition, 1.0);
          mat3 normalMatrix = mat3(inverse(transpose(MB_MATRIXM)));
          outNormal = normalize(normalMatrix * normal);
        }
      )" );
  customMaterial->program->loadFragmentShaderFromText( R"(
        #version 430
        in vec3 outPosition;
        flat in vec3 outNormal;
        out vec4 fragColor;
        const float invGamma = 1.0/2.2;
        const mat4 mSH_R = mat4(
          0.0151426,  0.0441249, -0.0200723, 0.040842,
          0.0441249, -0.0151426,  0.0147908, 0.161876, -
          0.0200723,  0.0147908,  0.0476559, 0.016715,
          0.040842,   0.161876,   0.016715,  0.394388
        );
        const mat4 mSH_G = mat4(
            0.0158047, -0.0553513, -0.0183098, -0.0649404,
          -0.0553513, -0.0158047,  0.0294534,  0.147578,
          -0.0183098,  0.0294534, -0.0211293,  0.030445,
          -0.0649404,  0.147578,   0.030445,   0.381122
        );
        const mat4 mSH_B = mat4(
          -0.00060538, -0.143711,   -0.0279153, -0.15276,
          -0.143711,    0.00060538,  0.0364631,  0.183909,
          -0.0279153,   0.0364631,  -0.0566425,  0.0386598,
          -0.15276,     0.183909,    0.0386598,  0.419227
        );
        void main( void )
        {
          vec4 nor = vec4(normalize(outNormal),1.0);
          vec3 col = vec3(
            dot(nor, (mSH_R * nor)),
            dot(nor, (mSH_G * nor)),
            dot(nor, (mSH_B * nor))
          );
          //Gamma correction
          fragColor = vec4(pow(col.xyz, vec3(invGamma)),1.0);
        }
      )" );
  customMaterial->program->compileAndLink( );
  customMaterial->program->autocatching( );

  customMaterial->addStandardUniforms( );

  customMaterial->state( ).culling( ).setEnabled( false );

  return customMaterial;
}

mb::Geometry* generateGeom( const mb::Color& )
{
  auto geom = new mb::Geometry( );

  geom->addPrimitive( new mb::SpherePrimitive( 5.0f, 15, 15 ) );

  mb::Material* customMaterial = createMaterial( );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  geom->addComponent( new mb::RotateComponent( mb::Vector3::ONE, 0.15f ) );

  return geom;
}

mb::Group* createScene( void )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 45.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 15.0f );

  auto node = generateGeom( mb::Color::GREY );

  scene->addChild( node );

  camera->addComponent( new mb::FreeCameraComponent( ) );
  scene->addChild( camera );

  return scene;
}

int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );
  window->setTitle( "Fog Demo" );

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

    app.update( );

    window->swapBuffers( );
  }
  return 0;
}
