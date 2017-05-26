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

#ifndef __MB_MATHF__
#define __MB_MATHF__

#include <mb/api.h>

#include <cmath>
#include <algorithm>
#include <string>

namespace mb
{
	class Mathf
	{
	public:
    /**
    * Linear interpolation.
    * @param  {float} x   [description]
    * @param  {float} x1  [description]
    * @param  {float} x2  [description]
    * @param  {float} q00 [description]
    * @param  {float} q01 [description]
    * @return {float}     [description]
    */
    MB_API
    static float lerp(float x, float x1, float x2, float q00, float q01);
    /**
    * Bilinear interpolation
    * @param  {number} x   [description]
    * @param  {number} y   [description]
    * @param  {number} q11 [description]
    * @param  {number} q12 [description]
    * @param  {number} q21 [description]
    * @param  {number} q22 [description]
    * @param  {number} x1  [description]
    * @param  {number} x2  [description]
    * @param  {number} y1  [description]
    * @param  {number} y2  [description]
    * @return {number}     [description]
    */
    MB_API
    static float biLerp(float x, float y, float q11, float q12, float q21,
      float q22, float x1, float x2, float y1, float y2);
    /**
    * Trilinear interpolation.
    * @param  {number} x    [description]
    * @param  {number} y    [description]
    * @param  {number} z    [description]
    * @param  {number} q000 [description]
    * @param  {number} q001 [description]
    * @param  {number} q010 [description]
    * @param  {number} q011 [description]
    * @param  {number} q100 [description]
    * @param  {number} q101 [description]
    * @param  {number} q110 [description]
    * @param  {number} q111 [description]
    * @param  {number} x1   [description]
    * @param  {number} x2   [description]
    * @param  {number} y1   [description]
    * @param  {number} y2   [description]
    * @param  {number} z1   [description]
    * @param  {number} z2   [description]
    * @return {number}      [description]
    */
    MB_API
    static float triLerp(float x, float y, float z, float q000,
        float q001, float q010, float q011, float q100, float q101,
        float q110, float q111, float x1, float x2, float y1, float y2,
        float z1, float z2);
    /**
    * Converts degrees angle to radians angle.
    * @param  {number} degs Degrees angle
    * @return {number}      Radians angle
    */
    MB_API
    static float degToRad(float degs);
    /**
    * Converts radians angle to degrees angle.
    * @param  {number} degs Radians angle
    * @return {number}      Degrees angle
    */
    MB_API
    static float radToDeg(float rads);
    /**
    * Returns true if the value is power of two.
    * @param  {number} v Integer value.
    * @return {boolean}
    */
    MB_API
    static bool isPOT(unsigned int v);
    /**
    * Returns the next power of two value.
    * @param  {number} v Integer value.
    * @return {number}
    */
    MB_API
    static unsigned int nearestPOT(unsigned int v);
    /**
    * Clamps a value to be between a minimum and maximum value.
    * @param  {number} v   Value to clamp.
    * @param  {number} min Minimum value.
    * @param  {number} max Maximum value
    * @return {number}
    */
    MB_API
    static float clamp(float v, float min, float max);
    /**
    * Clamps value between 0 and 1 and returns value.
    * @param  {number} v Value to clamp.
    * @return {number}
    */
    MB_API
    static float clamp01(float v);
    /**
    * Return 1 when is a positive number. -1 otherwise.
    * @param  {number} v [description]
    * @return {number}   [description]
    */
    MB_API
    static int sign(int v);
    /**
    * Normalizes radians angle between [0, 2π].
    * @param  {number} radAngle Radian angle.
    * @return {number}          Normalizated radian angle.
    */
    MB_API
    static float normalizeAngle(float radAngle);
    /**
    * Interpolates between min and max with smoothing at the limits.
    * @param  {number}     x   Value to interpolate.
    * @param  {number = 0} min Minimum value.
    * @param  {number = 1} max Maximum value.
    * @return {number}         Interpolated value
    */
    MB_API
    static float smoothstep(float x, float min = 0.0f, float max = 1.0f);
    /**
    * Interpolates between min and max with more smoothing at the limits thatn smoothstep.
    * @param  {number}     x   Value to interpolate.
    * @param  {number = 0} min Minimum value.
    * @param  {number = 1} max Maximum value.
    * @return {number}         Interpolated value
    */
    MB_API
    static float smootherstep(float x, float min, float max);
    /**
    * Convert number to hexadecimal.
    * @param  {number} n Number value.
    * @return {string}   Hexadecimal representation.
    */
    MB_API
    static std::string toHex( int n );

    /**
    * Convert current color from gamma to linear range.
    */
    MB_API
    static float gammaToLinearSpace( const float& v, const float& gammaFactor = 2.2f )
    {
      return std::pow( v, gammaFactor );
    }
    /**
    * Convert current color from linear to gamma range.
    */
    MB_API
    static float linearToGammaSpace( const float& v, const float& gammaFactor = 2.2f )
    {
      float invGamma = ( gammaFactor > 0.0f ) ? ( 1.0f / gammaFactor ) : 1.0f;
      return std::pow( v, invGamma );
    }

    MB_API
    static bool approximately( float a, float b )
    {
      /*return std::abs(b - a) < Mathf.Max(1e-06f * std::max(std::abs(a), std::abs(b)),
        0.00001 * 8f);*/
      return std::fabs(a - b) < 0.00001f;
    }

    MB_API
    static unsigned int euclideanModulo(int /*m*/, unsigned int /*n*/);
    MB_API
    static const float PI_2;
    MB_API
    static const float PI;
    MB_API
    static const float TWO_PI;
    MB_API
    static const float Deg2Rad;
    MB_API
    static const float Rad2Deg;
	};
}

#endif /* __MB_MATHF__ */
