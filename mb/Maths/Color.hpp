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
    const static Color Aqua;
    MB_API
    const static Color Beige;
    MB_API
    const static Color Black;
    MB_API
    const static Color Blue;
    MB_API
    const static Color Brown;
    MB_API
    const static Color Cyan;
    MB_API
    const static Color Gold;
    MB_API
    const static Color Green;
    MB_API
    const static Color Indigo;
    MB_API
    const static Color Lavender;
    MB_API
    const static Color Orange;
    MB_API
    const static Color Pink;
    MB_API
    const static Color Purple;
    MB_API
    const static Color Red;
    MB_API
    const static Color Yellow;
    MB_API
    const static Color White;

    Color linear( void )
    {
      return Color(
        Mathf::gammaToLinearSpace( r ),
        Mathf::gammaToLinearSpace( g ),
        Mathf::gammaToLinearSpace( b ), a );
    }
    Color gamma( void )
    {
      return Color(
        Mathf::linearToGammaSpace( r ),
        Mathf::linearToGammaSpace( g ),
        Mathf::linearToGammaSpace( b ), a );
    }
    float grayscale( ) const
    {
      return 0.299f * this->r + 0.587f * this->g + 0.114f * this->b;
    }
    float maxColorComponent( ) const
    {
      return std::max( std::max( r, g ), a );
    }
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
    static Color lerp( const Color& a, const Color& b, float t )
    {
      t = Mathf::clamp01( t );
      return Color( a.r + ( b.r - a.r ) * t, a.g + ( b.g - a.g ) * t, a.b + ( b.b - a.b ) * t, a.a + ( b.a - a.a ) * t );
    }
    static Color LerpUnclamped( const Color& a, const Color& b, float t )
    {
      return Color( a.r + ( b.r - a.r ) * t, a.g + ( b.g - a.g ) * t, a.b + ( b.b - a.b ) * t, a.a + ( b.a - a.a ) * t );
    }
    Color& RGBMultiplied( float multiplier )
    {
      this->r *= multiplier;
      this->g *= multiplier;
      this->b *= multiplier;
      return *this;
    }
    Color& AlphaMultiplied( float multiplier )
    {
      this->a *= multiplier;
      return *this;
    }

    Color& RGBMultiplied( Color multiplier )
    {
      this->r *= multiplier.r;
      this->g *= multiplier.g;
      this->b *= multiplier.b;
      return *this;
    }
    static void RGBToHSV( const Color& rgbColor, float& h, float& s, float& v )
    {
      if ( rgbColor.b > rgbColor.g && rgbColor.b > rgbColor.r )
      {
        Color::RGBToHSVHelper( 4.0f, rgbColor.b, rgbColor.r, rgbColor.g, h, s, v );
      }
      else if ( rgbColor.g > rgbColor.r )
      {
        Color::RGBToHSVHelper( 2.0f, rgbColor.g, rgbColor.b, rgbColor.r, h, s, v );
      }
      else
      {
        Color::RGBToHSVHelper( 0.0f, rgbColor.r, rgbColor.g, rgbColor.b, h, s, v );
      }
    }
  private:
    static void RGBToHSVHelper( float offset, float dominantcolor, float colorone, float colortwo, float& H, float& S, float& V )
    {
      V = dominantcolor;
      if ( V != 0.0f )
      {
        float num;
        if ( colorone > colortwo )
        {
          num = colortwo;
        }
        else
        {
          num = colorone;
        }
        float num2 = V - num;
        if ( num2 != 0.0f )
        {
          S = num2 / V;
          H = offset + ( colorone - colortwo ) / num2;
        }
        else
        {
          S = 0.0f;
          H = offset + ( colorone - colortwo );
        }
        H /= 6.0f;
        if ( H < 0.0f )
        {
          H += 1.0f;
        }
      }
      else
      {
        S = 0.0f;
        H = 0.0f;
      }
    }
  public:
    static Color HSVToRGB( float H, float S, float V )
    {
      return Color::HSVToRGB( H, S, V, true );
    }
    static Color HSVToRGB( float H, float S, float V, bool hdr )
    {
      Color white = Color::White;
      if ( S == 0.0f )
      {
        white.r = V;
        white.g = V;
        white.b = V;
      }
      else if ( V == 0.0f )
      {
        white.r = 0.0f;
        white.g = 0.0f;
        white.b = 0.0f;
      }
      else
      {
        white.r = 0.0f;
        white.g = 0.0f;
        white.b = 0.0f;
        float num = H * 6.0f;
        int num2 = ( int ) std::floor( num );
        float num3 = num - ( float ) num2;
        float num4 = V * ( 1.0f - S );
        float num5 = V * ( 1.0f - S * num3 );
        float num6 = V * ( 1.0f - S * ( 1.0f - num3 ) );
        switch ( num2 + 1 )
        {
        case 0:
          white.r = V;
          white.g = num4;
          white.b = num5;
          break;
        case 1:
          white.r = V;
          white.g = num6;
          white.b = num4;
          break;
        case 2:
          white.r = num5;
          white.g = V;
          white.b = num4;
          break;
        case 3:
          white.r = num4;
          white.g = V;
          white.b = num6;
          break;
        case 4:
          white.r = num4;
          white.g = num5;
          white.b = V;
          break;
        case 5:
          white.r = num6;
          white.g = num4;
          white.b = V;
          break;
        case 6:
          white.r = V;
          white.g = num4;
          white.b = num5;
          break;
        case 7:
          white.r = V;
          white.g = num6;
          white.b = num4;
          break;
        }
        if ( !hdr )
        {
          white.r = Mathf::clamp( white.r, 0.0f, 1.0f );
          white.g = Mathf::clamp( white.g, 0.0f, 1.0f );
          white.b = Mathf::clamp( white.b, 0.0f, 1.0f );
        }
      }
      return white;
    }
    MB_API
    static Color createFromHex( int hex )
    {
      return Color (
        (float)(hex >> 16 & 255) / 255.0f,
        (float)(hex >> 8 & 255) / 255.0f,
        (float)(hex & 255) / 255.0f
      );
    }
  };
}

#endif /* __MB_COLOR__ */
