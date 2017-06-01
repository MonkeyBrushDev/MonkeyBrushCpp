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

#include "OffscreenRenderingPass.hpp"
#include "StandardRenderingPass.hpp"
#include "../BatchQueue.hpp"

#include "../../Includes.hpp"

namespace mb
{
  OffscreenRenderingPass::OffscreenRenderingPass( unsigned int fbo )
    : OffscreenRenderingPass( fbo, new StandardRenderingPass( ) )
  {
  }

  OffscreenRenderingPass::OffscreenRenderingPass( unsigned int fbo, RenderingPass* sceneRenderingPass )
  : _fbo( fbo )
  , _sceneRenderingPass( sceneRenderingPass )
  {
  }

  void OffscreenRenderingPass::render( Renderer* renderer, BatchQueuePtr bq, Camera* cam )
  {
    std::cout << "Bind FBO" << std::endl;

    glBindFramebuffer( GL_FRAMEBUFFER, _fbo); // renderer->bindFBO( targetFBO );

    _sceneRenderingPass->render( renderer, bq, cam );
    glBindFramebuffer( GL_FRAMEBUFFER, 0); // renderer->unbindFBO( );
    std::cout << "Unbind FBO" << std::endl;
    applyImageEffects( renderer, cam );
  }
}
