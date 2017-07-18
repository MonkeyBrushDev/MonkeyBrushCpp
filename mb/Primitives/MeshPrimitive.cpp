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

#include "MeshPrimitive.hpp"

#include "../Includes.hpp"
#include "../Utils/ObjLoader.hpp"

namespace mb
{
  MeshPrimitive::MeshPrimitive(const std::string& fileName , Type type,
                               TDrawType typeDraw )
  : Primitive( type, typeDraw )
  {
    mb::ObjLoader::loadObj( fileName );

    // Vertices
    vertices = mb::ObjLoader::vertices;
    // Normals
    normals = mb::ObjLoader::normals;
    // TexCoords
    texCoords = mb::ObjLoader::texCoords;
    // Indices
    indices = mb::ObjLoader::indexData;

    MAXPOINTS = vertices.size();
  }
}
