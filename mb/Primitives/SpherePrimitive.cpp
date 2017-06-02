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

#include "SpherePrimitive.hpp"

namespace mb
{
	SpherePrimitive::SpherePrimitive(
	float radius,
    unsigned int width, 
    unsigned int height )
    : Primitive(Primitive::Type::TRIANGLES),
    _radius(radius),
    _width(width),
    _height(height)
	{
		// -- Creating geometry of the sphere -- //
		unsigned int faces = (1 + _height) * (1 + _width);
		unsigned int nv = 3 * _height * _width * 2;

		// Generating the vertex data...
		unsigned int NVIDX = 0;
		unsigned int NNIDX = 0;
		unsigned int NTIDX = 0;
		unsigned int IDX = 0;

		std::vector< std::vector< unsigned int > > grid;
		float u, v;
		Vector3 vertex;

		for( unsigned int i = 0; i <= _height; ++i )
		{
			std::vector< unsigned int> idxs;
			v = (float)i/(float)_height;

			for( unsigned int j = 0; j <= _width; ++j )
			{
				u = (float)j/(float)_width;

				float x = (-radius * cos(u * Mathf::TWO_PI) * sin(v * Mathf::TWO_PI));
				float y = (radius * cos(v * Mathf::TWO_PI));
				float z = (radius * sin(u * Mathf::TWO_PI) * sin(v * Mathf::TWO_PI));

	            vertex = Vector3( x, y, z );
				vertices.push_back( vertex );

				vertex.normalize();
				normals.push_back( vertex );

                texCoords.push_back( Vector2( u, 1.0f - v )); // (u,v)

				idxs.push_back( IDX++ );
			}
			grid.push_back( idxs );
	    }

	    //Sorting of indices...(for triangles-strip)
	    for (unsigned int i = 0; i < _height; ++i )
		{
			for (unsigned int j = 0; j < _width; ++j )
			{
				unsigned int a = grid[i][j + 1];
				unsigned int b = grid[i][j];
				unsigned int c = grid[i + 1][j];
				unsigned int d = grid[i + 1][j + 1];

				indices.push_back(a);
				indices.push_back(b);
				indices.push_back(d);

				indices.push_back(b);
				indices.push_back(c);
				indices.push_back(d);
			}
		}

	    for( unsigned int i = 0; i < vertices.size(); ++i )
	    {
            color.push_back(Vector3(0.0f, 0.2f, 0.0f));
	    }
	}

}//NS
