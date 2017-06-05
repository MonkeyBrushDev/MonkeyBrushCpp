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

#include "Renderer.hpp"
#include "RenderPasses/RenderingPass.hpp"
#include "BatchQueue.hpp"
#include "../Scenegraph/Camera.hpp"

#include "../Includes.hpp"

namespace mb
{
  Renderer::Renderer( )
  {
  }

  Renderer::~Renderer( )
  {
  }

  void Renderer::beginRender( void )
  {
    std::cout << "Set viewport" << std::endl;
  }

  void Renderer::render( BatchQueuePtr bq, RenderingPass* rp )
  {
    rp->render( this, bq, bq->getCamera( ) );
  }

  void Renderer::endRender( void )
  {
    // Clear data
    std::cout << "unbind renderer" << std::endl;
  }

  void Renderer::drawScreenQuad( Material* m )
  {
    static unsigned VAO = 666;
    static unsigned VBO = 666;
    if (VAO == 666)
    {
      float quadVertices[] = {
        -1.0f,  1.0f,  0.0f,
        -1.0f, -1.0f,  0.0f,
         1.0f,  1.0f,  0.0f,
         1.0f, -1.0f,  0.0f
      };
      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
      glBindVertexArray(VAO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    }

    //std::cout << "VAO: " << VAO << " - VBO: " << VBO << std::endl;

    m->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    m->unuse();
  }
}
