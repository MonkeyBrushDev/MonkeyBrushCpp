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

  customMaterial->program->loadVertexShaderFromText( R"(
    #version 430
    layout(location = 0) in vec3 position;
    out vec3 outPosition;

    uniform mat4 MB_MATRIXP;
    uniform mat4 MB_MATRIXV;
    uniform mat4 MB_MATRIXM;

    void main( void )
    {
      outPosition = vec3(MB_MATRIXV * MB_MATRIXM * vec4(position, 1.0));
      gl_Position = MB_MATRIXP * vec4(outPosition, 1.0);
    })" );
  customMaterial->program->loadFragmentShaderFromText( R"(
    #version 430
    out vec4 fragColor;

    in vec3 outPosition;

    uniform sampler3D tex3d;

    void main( void )
    {
      fragColor = vec4( outPosition, 1.0 );
      fragColor = texture( tex3d, outPosition );
    })" );
  customMaterial->program->compileAndLink( );
  customMaterial->program->autocatching( );

  customMaterial->addStandardUniforms( );

  customMaterial->state( ).culling( ).setEnabled( false );

  return customMaterial;
}

mb::Geometry* generateGeom( const mb::Color& )
{
  auto geom = new mb::Geometry( );

  geom->addPrimitive( new mb::CubePrimitive( 2.0f ) );

  mb::Material* customMaterial = createMaterial( );

  std::mt19937_64 rng;
  // initialize the random number generator with time-dependent seed
  uint64_t timeSeed = std::chrono::high_resolution_clock::now( ).time_since_epoch( ).count( );
  std::seed_seq ss { uint32_t( timeSeed & 0xffffffff ), uint32_t( timeSeed >> 32 ) };
  rng.seed( ss );
  // initialize a uniform distribution between 0 and 1
  std::uniform_real_distribution<float> unif( 0.0f, 1.0f );

  unsigned int size = 32;
  std::vector<float> data( size * size * size * 4 );
  for ( unsigned int k = 0; k < size; ++k )
  {
    for ( unsigned int j = 0; j < size; ++j )
    {
      for ( unsigned int i = 0; i < size; ++i )
      {
        unsigned int index = ( ( k*size*size ) + ( j*size ) + i ) * 4;
        data[ index + 0 ] = unif( rng );
        data[ index + 1 ] = unif( rng );
        data[ index + 2 ] = unif( rng );
        data[ index + 3 ] = 1.0f;
      }
    }
  }

  // Move to R8 (internalFormat), RED(format) UNSIGNED_BYTE(TYPE)
  mb::Texture3D* t = new mb::Texture3D( size, size, size, mb::Texture::FormatTexture::RGBA32F, true );
  t->loadRawTexture( data.data( ) );
  t->apply( );

  customMaterial->addUniform( "tex3d", std::make_shared< mb::TextureUniform>( t ) );

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

int main( void )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );
  window->setTitle( "Fog Demo" );

  mb::Application app;

  app.setSceneNode( createScene( ) );

  app.init( ); // initialize settings to render the scene...

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
