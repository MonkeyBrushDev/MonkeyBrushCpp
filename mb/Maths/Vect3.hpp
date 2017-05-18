#ifndef VECT3_H
#define VECT3_H

#include <mb/api.h>

#include <iostream>
#include <vector>
#include <cmath>


namespace mb
{
    class Vect3
    {
    public:
        MB_API
        static Vect3 xAxis;
        MB_API
        static Vect3 yAxis;
        MB_API
        static Vect3 zAxis;
        MB_API
        static Vect3 up;

        MB_API
        Vect3( float x = 0.0f, float y = 0.0f, float z = 0.0f );

        MB_API
        virtual ~Vect3( void ){}

        MB_API
        float x( void ) const;
        MB_API
        void x( const float& v );
        MB_API
        float y( void ) const;
        MB_API
        void y( const float& v );
        MB_API
        float z( void ) const;
        MB_API
        void z( const float& v );

        MB_API
        void set( float x_, float y_, float z_ );

    public:
        std::vector<float> _values;

    };
} //NS


#endif // VECT3_H
