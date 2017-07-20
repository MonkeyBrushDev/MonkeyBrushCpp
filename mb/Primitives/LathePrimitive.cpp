#include "LathePrimitive.hpp"

namespace mb
{
    LathePrimitive::LathePrimitive( std::vector<Vector3> points,
                                    unsigned int segments,
                                    float phiInit, float phiRadius,
                                    Primitive::Type type,
                                    Primitive::TDrawType typeDraw )
    : Primitive( type, typeDraw )
    {

        segments = floor( segments );

        const float inverseSegments = 1.0f / (float)segments;

//        int UV = 0;
//        texCoords.reserve( (segments + 1) * points.size() * 2 );

        int i, j, base, a, b, c, d, size;
        for( i = 0; i <= segments; ++i )
        {
            const float phi = phiInit + i * inverseSegments * phiRadius;

            const float sn = sin(phi);
            const float cs = cos(phi);

            for( j = 0, size = points.size() - 1; j <= size; ++j )
            {
                Vector3 point = points.at(j);
                vertices.push_back( Vector3( sn * point.x(),
                                             points[j].y(),
                                             cs * points[j].x() ));

                texCoords.push_back( Vector2( i / (float)segments,
                                           j / (float)(points.size() - 1)));
            }
        }

        for( i = 0; i < segments; ++i )
            for( j = 0; j < (points.size() - 1); ++j )
            {
                base = j + i * points.size();

                // indices
                a = base;
                b = base + points.size();
                c = base + points.size() + 1;
                d = base + 1;

                // face one
                indices.push_back(a); indices.push_back(b); indices.push_back(d);

                // face two
                indices.push_back(b); indices.push_back(c); indices.push_back(d);
            }

         for (i = 0; i < vertices.size(); ++i)
         {
           normals.push_back(Vector3());
         }

         for( i = 0; i < indices.size(); ++i )
         {
             const Vector3 ia = vertices[ indices.at(i) ];
             const Vector3 ib = vertices[ indices.at(i) + 1 ];
             const Vector3 ic = vertices[ indices.at(i) + 2 ];

             const Vector3 e1 = (ia - ib);
             const Vector3 e2 = (ic - ib);
             const Vector3 no = Vector3::cross(e1, e2);

             normals[ indices.at(i) ]     = normals[ indices.at(i) ] + no;
             normals[ indices.at(i) + 1 ] = normals[ indices.at(i) + 1] + no;
             normals[ indices.at(i) + 2 ] = normals[ indices.at(i) + 2] + no;
         }

         for (i = 0; i < normals.size(); ++i)
         {
             normals[i] = normals[i].normalize();
         }

         std::vector<Vector3> vertices2;
         for( i = 0; i < vertices.size(); ++i )
         {
           vertices2.push_back( Vector3( vertices[i].x(), vertices[i].y(), vertices[i].z() ));
         }
         vertices = vertices2;

         std::vector<Vector3> normals2;
         for( i = 0; i < normals.size(); ++i )
         {
           normals2.push_back( Vector3( normals[i].x(), normals[i].y(), normals[i].z() ));
         }
         normals = normals2;

         std::vector<short> indices2;
         for( i = 0; i < indices.size(); ++i )
         {
            indices2.push_back( indices.at(i) );
         }
         indices = indices2;

         // if geometry closed, check average along the seam
         if (phiRadius == Mathf::PI * 2)
         {
             Vector3 n1, n2, n;

             base = segments * points.size() * 3;
             for( i = 0, j = 0, size = points.size(); i < size; ++i, j += 3 )
             {
                 // select normal int the first line
                 n1 = normals.at(j);

                 // select normal of last line
                 n2 = normals.at(base + j);

                 n = ( n + ( n1 + n2 )).normalize();

                 normals[base + j] = n;
                 normals[j] = n;
             }
         }

         MAXPOINTS = vertices.size();

    }

}//NS
