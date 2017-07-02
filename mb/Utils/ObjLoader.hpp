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

#ifndef __MB_OBJ_LOADER__
#define __MB_OBJ_LOADER__

#include <mb/api.h>

#include <vector>
#include "../Maths/Vector2.hpp"
#include "../Maths/Vector3.hpp"
#include "FileSystem.hpp"
#include "StringUtils.hpp"

namespace mb
{
  class ObjLoader
  {
  protected:
    // https://gist.github.com/noonat/1131091
    static void readObj( )
    {

    }
  public:
    static void readMaterialFile( const std::string fileName )
    {
      std::string auxName = mb::FileSystem::getInstance( )->getPathForResource( fileName );

      std::ifstream file; 
      file.open( auxName.c_str( ) );
      if ( !file.is_open( ) )
      {
        throw;
      }
      std::string str;
      while ( std::getline( file, str ) )
      {
        std::stringstream line( str );

        std::string type;
        line >> type;

        if ( type != "" )
        {
          if ( type == "newmtl" )
          {
            std::string name;
            line >> name;
            std::cout << "Material name: " << name << std::endl;
          }
          else if ( type == "Ka" )
          {
            // Ambient color
            float r, g, b;
            line >> r >> g >> b;
            mb::Vector3 cc ( r, g, b );
            std::cout << "Ka: " << cc << std::endl;
          }
          else if ( type == "Kd" )
          {
            // Diffuse color
            float r, g, b;
            line >> r >> g >> b;
            mb::Vector3 cc( r, g, b );
            std::cout << "Kd: " << cc << std::endl;
          }
          else if ( type == "Ks" )
          {
            // Specular color
            float r, g, b;
            line >> r >> g >> b;
            mb::Vector3 cc( r, g, b );
            std::cout << "Ks: " << cc << std::endl;
          }
          else if ( type == "Ns" )
          {
            // Specular factor
            float ns;
            line >> ns;
            std::cout << "Ns: " << ns << std::endl;
          }
          else if ( type == "map_Kd" )
          {
            // Diffuse texture
            std::string texName;
            line >> texName;
            std::cout << "map_Kd: " << texName << std::endl;
          }
          else if ( type == "map_kS" )
          {
            // Specular texture
            std::string texName;
            line >> texName;
            std::cout << "map_kS: " << texName << std::endl;
          }
          else if ( type == "map_bump" )
          {
            // Normal texture
            std::string texName;
            line >> texName;
            std::cout << "map_bump: " << texName << std::endl;
          }
          else if ( type == "map_Ke" )
          {
            // Emissive texture
            std::string texName;
            line >> texName;
            std::cout << "map_Ke: " << texName << std::endl;
          }
          else if ( type == "illum" )
          {
            // Illum type
            int illumLevel;
            line >> illumLevel;

            if ( illumLevel == 0 )
            {
              // This is a constant color illumination model. The color is the specified Kd for the material. The formula is: 
              // color = Kd
              std::cout << "Illum: " << "Kd" << std::endl;
            }
            else if ( illumLevel == 1 )
            {
              // This is a diffuse illumination model using Lambertian shading.The color includes an ambient and diffuse shading terms for each light source.The formula is
              // color = KaIa + Kd { SUM j = 1..ls, ( N * Lj )Ij }
              std::cout << "Illum: " << "KaIa + Kd { SUM j = 1..ls, ( N * Lj )Ij }" << std::endl;
            }
            else if ( illumLevel == 2 )
            {
              // This is a diffuse and specular illumination model using Lambertian shading and Blinn's interpretation of Phong's specular illumination model( BLIN77 ).
              // The color includes an ambient constant term, and a diffuse and specular shading term for each light source.The formula is :
              // color = KaIa + Kd { SUM j = 1..ls, ( N*Lj )Ij } +Ks { SUM j = 1..ls, ( ( H*Hj ) ^ Ns )Ij }
              std::cout << "Illum: " << "KaIa + Kd { SUM j = 1..ls, ( N*Lj )Ij } +Ks { SUM j = 1..ls, ( ( H*Hj ) ^ Ns )Ij }" << std::endl;
            }
          }
        }
      }
    }
  public:
    static std::vector< Vector3 > vertices;
    static std::vector< Vector3 > normals;
    static std::vector< Vector2 > texCoords;
    static std::vector< short > indexData;

    static void loadObj( const std::string fileName )
    {
      vertices.clear( );
      normals.clear( );
      texCoords.clear( );
      indexData.clear( );

      std::vector< mb::Vector3 > _positions;
      std::vector< mb::Vector3 > _normals;
      std::vector< mb::Vector2 > _texCoords;
      std::vector< std::string > _faces;

      std::string auxName = mb::FileSystem::getInstance()->getPathForResource( fileName );

      std::ifstream file;
      file.open( auxName.c_str( ) );
      if( !file.is_open( ) )
      {
        throw;
      }
      std::string str;
      float x, y, z;
      std::string f0, f1, f2;
      while( std::getline(file, str) )
      {
        std::stringstream line( str );

        std::string type;
        line >> type;

        if( type != "" )
        {
          if ( type == "v" )
          {
            // Read object position
            line >> x >> y >> z;
            _positions.push_back( mb::Vector3( x, y, z ) );
          }
          else if ( type == "vn" )
          {
            // Read object normal
            line >> x >> y >> z;
            _normals.push_back( mb::Vector3( x, y, z ) );
          }
          else if ( type == "vt" )
          {
            // Read tex coord
            line >> x >> y;
            _texCoords.push_back( mb::Vector2( x, y ) );
          }
          else if ( type == "f" )
          {
            line >> f0 >> f1 >> f2;
            _faces.push_back( f0 );
            _faces.push_back( f1 );
            _faces.push_back( f2 );
          }
          else if ( type == "o" || type == "g" )
          {
            // TODO: Read another object
          }
          else if ( type == "usemtl" )
          {
            std::string name;
            line >> name;
            std::cout << "Object Material: " << name << std::endl;
          }
          else if ( type == "mtllib" )
          {
            std::string name;
            line >> name;
            std::cout << "Object MTL File: " << name << std::endl;
          }
        }
      }

      // GENERATE FINAL GEOMETRY

      bool hasNormals = !_normals.empty( );
      bool hasTextureCoords = !_texCoords.empty( );
      bool hasTangents = hasNormals && hasTextureCoords;

      //std::vector< unsigned short > indexData;

      mb::Vector3 p0, p1, p2;
      mb::Vector3 n0, n1, n2;
      mb::Vector2 uv0, uv1, uv2;
      mb::Vector3 tangent;
      for ( unsigned int i = 0, size = _faces.size( ); i < size; i += 3 )
      {
        std::vector< int > v0 = StringUtils::split<int>( _faces[ i ], '/' );
        std::vector< int > v1 = StringUtils::split<int>( _faces[ i + 1 ], '/' );
        std::vector< int > v2 = StringUtils::split<int>( _faces[ i + 2 ], '/' );

        p0 = _positions[ v0[ 0 ] - 1 ];
        p1 = _positions[ v1[ 0 ] - 1 ];
        p2 = _positions[ v2[ 0 ] - 1 ];

        if ( hasNormals )
        {
          n0 = _normals[ v0[ 2 ] - 1 ];
          n1 = _normals[ v1[ 2 ] - 1 ];
          n2 = _normals[ v2[ 2 ] - 1 ];
        }
        if ( hasTextureCoords )
        {
          uv0 = _texCoords[ v0[ 1 ] - 1 ];
          uv1 = _texCoords[ v1[ 1 ] - 1 ];
          uv2 = _texCoords[ v2[ 1 ] - 1 ];
        }
        if ( hasTangents )
        {
          mb::Vector3 dP1 = p1 - p0;
          mb::Vector3 dP2 = p2 - p0;
          mb::Vector2 dUV1 = uv1 - uv0;
          mb::Vector2 dUV2 = uv2 - uv0;

          float r = 1.0f / ( dUV1[ 0 ] * dUV2[ 1 ] - dUV1[ 1 ] * dUV2[ 0 ] );
          tangent = ( dP1 * dUV2[ 1 ] - dP2 * dUV1[ 1 ] ) * r;
        }

        //std::cout << "POS: " << p0;
        vertices.push_back( p0 );
        if ( hasNormals )
        {
          normals.push_back( n0 );
          //std::cout << " - NORMAL: " << n0;
        }
        if ( hasTextureCoords )
        {
          texCoords.push_back( uv0 );
          //std::cout << " - UV: " << uv0;
        }
        //if ( hasTangents )      std::cout << " - TG: " << tangent;
        //std::cout << std::endl;

        //std::cout << "POS: " << p1;
        vertices.push_back( p1 );
        if ( hasNormals )
        {
          normals.push_back( n1 );
          //std::cout << " - NORMAL: " << n1;
        }
        if ( hasTextureCoords )
        {
          texCoords.push_back( uv1 );
          //std::cout << " - UV: " << uv1;
        }
        //if ( hasTangents )      std::cout << " - TG: " << tangent;
        //std::cout << std::endl;

        //std::cout << "POS: " << p2;
        vertices.push_back( p2 );
        if ( hasNormals )
        {
          normals.push_back( n2 );
          //std::cout << " - NORMAL: " << n2;
        }
        if ( hasTextureCoords )
        {
          texCoords.push_back( uv2 );
          //std::cout << " - UV: " << uv2;
        }
        //if ( hasTangents )      std::cout << " - TG: " << tangent;
        //std::cout << std::endl;
      }
      unsigned int numIndices = _faces.size( );
      for ( unsigned int i = 0; i < numIndices; ++i )
      {
        indexData.push_back( i );
      }

      //std::cout << "END" << std::endl;
    }
  };
  std::vector< Vector3 > ObjLoader::vertices;
  std::vector< Vector3 > ObjLoader::normals;
  std::vector< Vector2 > ObjLoader::texCoords;
  std::vector< short > ObjLoader::indexData;
}

#endif /* __MB_OBJ_LOADER__ */
