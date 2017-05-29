#include "FramebufferObject.hpp"

namespace mb
{
  FramebufferObject::FramebufferObject( unsigned int w, unsigned int h )
    : _width( w )
    , _height( h )
    , _clearColor( mb::Color::BLACK )
  {
  }
  void FramebufferObject::resize( unsigned int w, unsigned int h )
  {
    _width = w;
    _height = h;
    // TODO: RESIZE RENDER TARGET
  }


  StandardFramebuffer::StandardFramebuffer( unsigned int w, unsigned int h )
    : FramebufferObject( w, h )
  {
    _renderTargets.insert(std::pair<std::string, RenderTarget>(
                            "color",
                            RenderTarget( w, h, RenderTarget::Type::RGBA, true ) ) );
  }

  StandardFramebuffer::~StandardFramebuffer( void )
  {

  }


  GBuffer::GBuffer( unsigned int w, unsigned int h )
    : FramebufferObject( w, h )
  {
    _renderTargets.insert(std::pair<std::string, RenderTarget>(
                            "position",
                            RenderTarget( w, h, RenderTarget::Type::RGBA, true ) ) );
    _renderTargets.insert(std::pair<std::string, RenderTarget>(
                            "normal",
                            RenderTarget( w, h, RenderTarget::Type::RGB, true ) ) );
    _renderTargets.insert(std::pair<std::string, RenderTarget>(
                            "color",
                            RenderTarget( w, h, RenderTarget::Type::RGBA, true ) ) );
  }

  GBuffer::~GBuffer( void )
  {

  }
}