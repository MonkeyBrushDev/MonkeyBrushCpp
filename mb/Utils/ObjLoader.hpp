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
    static void loadObj( const std::string fileName )
    {
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

          }
        }
      }

      // GENERATE FINAL GEOMETRY

      bool hasNormals = !_normals.empty( );
      bool hasTextureCoords = !_texCoords.empty( );
      bool hasTangents = hasNormals && hasTextureCoords;

      std::vector< unsigned short > indexData;

      mb::Vector3 p0, p1, p2;
      mb::Vector3 n0, n1, n2;
      mb::Vector2 uv0, uv1, uv2;
      mb::Vector3 tangent;
      for ( unsigned int i = 0, size = _faces.size( ); i < size; i += 3 )
      {
        std::vector< int > v0 = StringUtils::split<int>( _faces[ i ], '/' );
        std::vector< int > v1 = StringUtils::split<int>( _faces[ i ], '/' );
        std::vector< int > v2 = StringUtils::split<int>( _faces[ i ], '/' );

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

        std::cout << "POS: " << p0;
        if ( hasNormals )       std::cout << " - NORMAL: " << n0;
        if ( hasTextureCoords ) std::cout << " - UV: " << uv0;
        if ( hasTangents )      std::cout << " - TG: " << tangent;
        std::cout << std::endl;

        std::cout << "POS: " << p1;
        if ( hasNormals )       std::cout << " - NORMAL: " << n1;
        if ( hasTextureCoords ) std::cout << " - UV: " << uv1;
        if ( hasTangents )      std::cout << " - TG: " << tangent;
        std::cout << std::endl;

        std::cout << "POS: " << p2;
        if ( hasNormals )       std::cout << " - NORMAL: " << n2;
        if ( hasTextureCoords ) std::cout << " - UV: " << uv2;
        if ( hasTangents )      std::cout << " - TG: " << tangent;
        std::cout << std::endl;
      }
      unsigned int numIndices = _faces.size( );
      for ( unsigned int i = 0; i < numIndices; ++i )
      {
        indexData.push_back( i );
      }

      std::cout << "END" << std::endl;
    }
  };
}

#endif /* __MB_OBJ_LOADER__ */
