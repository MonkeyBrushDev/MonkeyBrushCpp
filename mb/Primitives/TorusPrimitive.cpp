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

#include "TorusPrimitive.hpp"

#include "../Maths/Vector2.hpp"
#include "../Maths/Vector3.hpp"

namespace mb
{
  TorusPrimitive::TorusPrimitive( float outerRadius, float innerRadius,
  								  unsigned int sides, unsigned int rings)
  :Primitive(Primitive::Type::TRIANGLES),
  _outerRadius( outerRadius ),
  _innerRadius( innerRadius ),
  _sides( sides ),
  _rings( rings )
  {
  	unsigned int faces = _sides * _rings;
    unsigned int nv  = _sides * ( _rings + 1);   // One extra ring to duplicate first ring

//	BufferAttribute<float> verts(std::vector<float>(3 * nv), 3);
//	BufferAttribute<float> norms(std::vector<float>(3 * nv), 3);
//	BufferAttribute<float> texCoords(std::vector<float>(2 * nv), 2);

//	std::vector<unsigned int> cells(6 * faces);
    indices.reserve( 6 * faces );

	  // Generate the vertex data
    unsigned int NVIDX = 0;
    unsigned int NNIDX = 0;
    unsigned int NTIDX = 0;

    float ringFactor = Mathf::TWO_PI / _rings;
    float sideFactor = Mathf::TWO_PI / _sides;
    float norms_[3];
    for (unsigned int ring = 0; ring <= _rings; ++ring)
    {
      float u = ring * ringFactor;
      float cu = std::cos(u);
      float su = std::sin(u);
      for (unsigned int side = 0; side < _sides; ++side)
      {
        float v = side * sideFactor;
        float cv = std::cos(v);
        float sv = std::sin(v);
        float r = (_outerRadius + _innerRadius * cv);

			  norms_[0] = cv * cu * r;
			  norms_[1] = cv * su * r;
			  norms_[2] = sv * r;
        // Normalize
        float len = std::sqrt(
				norms_[0] * norms_[0] +
				norms_[1] * norms_[1] +
				norms_[2] * norms_[2]);
			  norms_[0] /= len;
			  norms_[1] /= len;
			  norms_[2] /= len;

        vertices.push_back(Vector3(r * cu, r * su, _innerRadius * sv));
        normals.push_back(Vector3( norms_[0], norms_[1], norms_[2]));
        texCoords.push_back(Vector2( u / Mathf::TWO_PI * 2.0, v / Mathf::TWO_PI * 2.0));
      }
    }

    unsigned int idx = 0;
    for (unsigned int ring = 0; ring < _rings; ++ring)
    {
      unsigned int ringStart = ring * _sides;
      unsigned int nextRingStart = (ring + 1) * _sides;
      for (unsigned int side = 0; side < _sides; ++side)
      {
        unsigned int nextSide = (side + 1) % sides;
        // The quad
        indices[idx] = (ringStart + side);
        indices[idx + 1] = (nextRingStart + side);
        indices[idx + 2] = (nextRingStart + nextSide);
        indices[idx + 3] = ringStart + side;
        indices[idx + 4] = nextRingStart + nextSide;
        indices[idx + 5] = (ringStart + nextSide);
        idx += 6;
      }
    }

//	  _numVertices = vertices.count();

  }

}//NS
