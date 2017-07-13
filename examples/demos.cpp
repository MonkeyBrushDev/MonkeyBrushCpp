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

  mb::Texture2D* t = mb::Texture2D::loadFromImage( "earth/earth_diffuse.jpg" );

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

    pp.use( );

    app.getRenderer( )->drawScreenQuad( );

    window->swapBuffers( );
  }

  return 0;
}
