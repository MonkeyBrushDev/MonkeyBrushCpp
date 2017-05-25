#ifndef __MB_COLOR__
#define __MB_COLOR__

#include "Mathf.hpp"

namespace mb
{
  class Color
  {
  public:
    float r, g, b, a;
    Color( float r_, float g_, float b_, float a_ = 1.0f )
      : r( r_ )
      , g( g_ )
      , b( b_ )
      , a( a_ )
    {
    }

    MB_API
    const static Color AQUA;
    MB_API
    const static Color BEIGE;
    MB_API
    const static Color BLACK;
    MB_API
    const static Color BLUE;
    MB_API
    const static Color BROWN;
    MB_API
    const static Color CYAN;
    MB_API
    const static Color GOLD;
    MB_API
    const static Color GREEN;
    MB_API
    const static Color INDIGO;
    MB_API
    const static Color LAVENDER;
    MB_API
    const static Color ORANGE;
    MB_API
    const static Color PINK;
    MB_API
    const static Color PURPLE;
    MB_API
    const static Color RED;
    MB_API
    const static Color YELLOW;
    MB_API
    const static Color WHITE;

    MB_API
    Color linear( void );
    MB_API
    Color gamma( void );
    MB_API
    float grayscale( void ) const;
    MB_API
    float maxColorComponent( void ) const;
    friend Color operator+( Color& a, const Color& b )
    {
      return Color(
        a.r + b.r,
        a.g + b.g,
        a.b + b.b,
        a.a + b.a
      );
    }
    friend Color& operator+=( Color& a, const Color& b )
    {
      a.r += b.r;
      a.g += b.g;
      a.b += b.b;
      a.a += b.a;
      return a;
    }
    friend Color operator-( Color& a, const Color& b )
    {
      return Color(
        a.r - b.r,
        a.g - b.g,
        a.b - b.b,
        a.a - b.a
      );
    }
    friend Color& operator-=( Color& a, const Color& b )
    {
      a.r -= b.r;
      a.g -= b.g;
      a.b -= b.b;
      a.a -= b.a;
      return a;
    }
    friend Color operator*( Color& a, const Color& b )
    {
      return Color(
        a.r * b.r,
        a.g * b.g,
        a.b * b.b,
        a.a * b.a
      );
    }
    friend Color& operator*=( Color& a, const Color& b )
    {
      a.r *= b.r;
      a.g *= b.g;
      a.b *= b.b;
      a.a *= b.a;
      return a;
    }
    friend Color operator/( Color& a, const Color& b )
    {
      return Color(
        a.r / b.r,
        a.g / b.g,
        a.b / b.b,
        a.a / b.a
      );
    }
    friend Color& operator/=( Color& a, const Color& b )
    {
      a.r /= b.r;
      a.g /= b.g;
      a.b /= b.b;
      a.a /= b.a;
      return a;
    }
    bool operator==( const Color& c ) const
    {
      return
        ( this->r == c.r ) &&
        ( this->g == c.g ) &&
        ( this->b == c.b ) &&
        ( this->a == c.a );
    }
    bool operator !=( const Color& c ) const
    {
      return !( *this == c );
    }
    MB_API
    static Color lerp( const Color& a, const Color& b, float t );
    MB_API
    static Color LerpUnclamped( const Color& a, const Color& b, float t );
    MB_API
    Color& RGBMultiplied( float multiplier );
    MB_API
    Color& AlphaMultiplied( float multiplier );
    MB_API
    Color& RGBMultiplied( Color multiplier );
    MB_API
    static void RGBToHSV( const Color& rgbColor, float& h, float& s, float& v );
  private:
    static void RGBToHSVHelper( float offset, float dominantcolor, 
      float colorone, float colortwo, float& H, float& S, float& V );
  public:
    MB_API
    static Color HSVToRGB( float H, float S, float V );
    MB_API
    static Color HSVToRGB( float H, float S, float V, bool hdr );
    MB_API
    static Color createFromHex( int hex );
  };
}

#endif /* __MB_COLOR__ */
