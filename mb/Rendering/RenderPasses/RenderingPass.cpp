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

#include "RenderingPass.hpp"

#include "../Renderer.hpp"
#include "../BatchQueue.hpp"
#include "../ImageEffects/ImageEffect.hpp"
#include "../../Scenegraph/Camera.hpp"

namespace mb
{
  void RenderingPass::applyImageEffects( Renderer *renderer, Camera *camera )
  {
    for ( auto& ie : _imageEffects )
    {
      unsigned int fbo = 0;
      ie->compute( renderer, camera );

      renderer->bindFBO( fbo );
      ie->apply( renderer, camera );
      renderer->unbindFBO( fbo );
      // Swap FBO?
      swapBuffers( renderer );
    }
  }

  void RenderingPass::swapBuffers( Renderer* )
  {
    //auto source = 1;
    //auto destination = 2;

    std::cout << "Set source buffer with destination texture" << std::endl;
    //renderer->setFBO(SOURCE, destination);
    std::cout << "Set destination buffer with source texture" << std::endl;
    //renderer->setFBO(DESTINATION, source);
  }
}
