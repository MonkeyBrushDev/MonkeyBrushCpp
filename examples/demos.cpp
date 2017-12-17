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

#include <mb/mb.h>
#include <routes.h>

class GBuffer : public mb::pp::RenderTarget
{
public:
  GBuffer( void )
  : mb::pp::RenderTarget( )
  {
    const mb::Texture::FormatTexture formats[ 4 ] = {
      mb::Texture::FormatTexture::RGBA32F,
      mb::Texture::FormatTexture::RGBA32F,
      mb::Texture::FormatTexture::RGBA32F,
      mb::Texture::FormatTexture::RGBA32F // TODO: USE D32F
    };
    const mb::pp::RenderTargetOutput::AttachmentsPoint attachmentPoints[ 4 ] =
    {
      mb::pp::RenderTargetOutput::Color0,
      mb::pp::RenderTargetOutput::Color1,
      mb::pp::RenderTargetOutput::Color2,
      mb::pp::RenderTargetOutput::Depth
    };
    for ( unsigned int i = 0; i < 4; ++i )
    {
      mb::pp::RenderTargetOutputRef o = std::make_shared<mb::pp::RenderTargetOutput>( );

      _textures[ i ] = new mb::Texture2D( 512, 512, formats[ i ], true );
      _textures[ i ]->setWrapMode( mb::Texture::WrapMode::CLAMP_TO_EDGE );
      o->setTexture( _textures[ i ] );
      o->setAttachmentPoint( attachmentPoints[ i ] );
      addOutput( o );
    }
  }
  mb::Texture* colorTexture( void ) const
  {
    return _textures[ Color ];
  }

  mb::Texture* positionTexture( void ) const
  {
    return _textures[ Position ];
  }

  mb::Texture* normalTexture( void ) const
  {
    return _textures[ Normal ];
  }

  mb::Texture* depthTexture( void ) const
  {
    return _textures[ Depth ];
  }
  enum Attachments
  {
    Color = 0,
    Position,
    Normal,
    Depth,
    AttachmentsCount
  };
protected:
  mb::Texture* _textures[ 4 ];
};

int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );
  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 512, 512 ) );
  window->init( );

  GBuffer gb;

  /*mb::PostProcessMaterial pp( R"(
#version 430
in vec2 uv;
out vec4 fragColor;
uniform sampler2D targetTex;
void main( )
{
  fragColor = vec4( texture( targetTex, uv ).rgb, 1.0 );
})" );*/
  mb::ColorCorrectionPPMaterial pp;

  mb::Texture2D* t = mb::Texture2D::loadFromImage( "rubymatcap.jpg" );
  mb::Texture2D* t2 = mb::Texture2D::loadFromImage( "posterize_lut.png" );

  mb::Application app;
  app.setSceneNode( new mb::Group( "" ) );

  mb::Clock clockTime;
  clockTime.reset( );

  pp.uniform( "targetTex" )->value( t );
  pp.uniform( "colorTable" )->value( t2 );

  /*// Sepia kernel
  std::array<float, 16> arr = {
    0.393f, 0.349f, 0.272f, 0.0f,
    0.769f, 0.686f, 0.534f, 0.0f,
    0.189f, 0.168f, 0.131f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f
  };

  pp.uniform( "kernelMatrix" )->value( mb::Matrix4( arr ) );*/

  if ( window->isRunning( ) )
  {
    window->pollEvents( );

    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Esc ) )
    {
      window->close( );
      //break;
    }

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    clockTime.tick( );

    pp.use( );

    app.getRenderer( )->drawScreenQuad( );

    window->saveToImage( "C:/Users/maldicion069/Music/MonkeyBrushProject/MonkeyBrushCpp/foo.bmp" );
    
    window->swapBuffers( );
  }

  

  return 0;
}
