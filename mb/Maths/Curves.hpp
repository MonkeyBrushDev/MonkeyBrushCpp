/*
* Copyright (c) 2016 maldicion069
*
* Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
*
* This file is part of MonkeyBrushPlusPlus <https://github.com/maldicion069/monkeybrushplusplus>
*
* This library is free software; you can redistribute it and/or modify it under
* the terms of the GNU Lesser General Public License version 3.0 as published
* by the Free Software Foundation.
*
* This library is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
* details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
*/

#ifndef __MB_CURVES__
#define __MB_CURVES__

#include <mb/api.h>

#include "Vect2.hpp"
#include "Vect3.hpp"
#include "Mathf.hpp"
#include <vector>

namespace mb
{
	namespace curves
	{
		class Curve2D
		{
		public:
			MB_API
			virtual ~Curve2D() {}
			MB_API
			virtual Vect2 evaluate(const float t) = 0;
		};
		class Curve3D
		{
		public:
			MB_API
			virtual ~Curve3D() {}
			MB_API
			virtual Vect3 evaluate(const float t) = 0;
		};

		/**
		* Ellipse class.
		* @class Ellipse
		* Create an ellipse to the path which is centered at (x, y)
		* position with the radius starting at startAngle and ending
		* at endAngle going in the given direction by anticlockwise.
		*/
		class Ellipse : public Curve2D
		{
		public:
			/**
			* Ellipse constructor
			* @param {Vect2}   center      The center of the ellipse.
			* @param {Vect2}   radius      Ellipse major and minux radius.
			* @param {number}  startAngle  [description]
			* @param {number}  endAngle    [description]
			* @param {boolean} isClockwise if true, draws the ellipse
			*                              anticlockwise (counter-clockwise),
			*                              otherwise in a clockwise direction.
			*/
			MB_API
			Ellipse(const Vect2& center, const Vect2& radius, float startAngle, float endAngle, bool isClockwise);
			virtual ~Ellipse() {}
			/**
			* Return interpolate position based on ellipse definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vect2}    A new Vect2 interpolated position.
			*/
			MB_API
			virtual Vect2 evaluate(const float t);
		protected:
			Vect2 _center;
			Vect2 _radius;
			float _startAngle;
			float _endAngle;
			bool _isClockwise;
		};
		/**
		* LineCurve2D class.
		* @class LineCurve2D
		* Create an line from first 2D point to second.
		*/
		class Line2D: public Curve2D
		{
		public:
			/**
			* Line2D constructor.
			* @param {Vect2} x Minimum point.
			* @param {Vect2} y Maximum point.
			*/
			MB_API
			Line2D(const Vect2& x, const Vect2& y);
			virtual ~Line2D() {}
			/**
			* Return interpolate position based on 2D line definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vect2}    A new Vect2 interpolated position.
			*/
			MB_API
			virtual Vect2 evaluate(const float t);
		protected:
			Vect2 _p1;
			Vect2 _p2;
		};
		/**
		* LineCurve3D class.
		* @class LineCurve3D
		* Create an line from first 3D point to second.
		*/
		class Line3D: public Curve3D
		{
		public:
			/**
			* Line3D constructor.
			* @param {Vect3} x Minimum point.
			* @param {Vect3} y Maximum point.
			*/
			MB_API
			Line3D(const Vect3& x, const Vect3& y);
			virtual ~Line3D() {}
			/**
			* Return interpolate position based on 3D line definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vect3}    A new Vect3 interpolated position.
			*/
			MB_API
			virtual Vect3 evaluate(const float t);
		protected:
			Vect3 _p1;
			Vect3 _p2;
		};
		/**
		* BezierCurve class
		* @class BezierCurve
		*
		* Create a cubic Bézier curve to the path. It requires
		* three points. The first two points are control points
		* and the third one is the end point.
		*/
		class CubicBezier: public Curve2D
		{
			/**
			* CubicBezier constructor
			* @param {Vect2} cpi  Starting point
			* @param {Vect2} cpp1 First control point
			* @param {Vect2} cpp2 Second control point
			* @param {Vect2} cpe  Ending point
			*/
			MB_API
			CubicBezier(const Vect2& cpi, const Vect2& cpp1, const Vect2& cpp2, const Vect2& cpe);
			virtual ~CubicBezier() {}
			/**
			* Return interpolate position based on cubic bezier definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vect2}    A new Vect2 interpolated position.
			*/
			MB_API
			virtual Vect2 evaluate(const float t);
		protected:
			std::vector<Vect2> _list;
			float bezierCurveInterpolation(const float p0, const float p1,
				const float p2, const float p3, const float t);
		};
		class CubicBezier3D: public Curve3D
		{
		public:
			/**
			* CubicBezier constructor
			* @param {Vect3} cpi  Starting point
			* @param {Vect3} cpp1 First control point
			* @param {Vect3} cpp2 Second control point
			* @param {Vect3} cpe  Ending point
			*/
			MB_API
			CubicBezier3D(const Vect3& cpi, const Vect3& cpp1, const Vect3& cpp2, const Vect3& cpe);
			MB_API
			virtual ~CubicBezier3D() {}
			/**
			* Return interpolate position based on cubic bezier definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vect3}    A new Vect3 interpolated position.
			*/
			MB_API
			virtual Vect3 evaluate(const float t);
		protected:
			std::vector<Vect3> _list;

			float bezierCurveInterpolation(const float p0, const float p1, 
				const float p2, const float p3, const float t);
		};
		/**
		* QuadraticBezier class
		* @class QuadraticBezier
		*
		* Create a quadratic Bézier curve to the path.
		* It requires two points. The first point is a
		* control point and the second one is the end point.
		*/
		class QuadraticBezier2D: public Curve2D
		{
			/**
			* QuadraticBezier constructor.
			* @param {Vect2} cpi  Starting point.
			* @param {Vect2} cpp  Middle control point.
			* @param {Vect2} cpe  Ending point.
			*/
			MB_API
			QuadraticBezier2D(const Vect2& cpi, const Vect2& cpp, const Vect2& cpe);
			MB_API
			virtual ~QuadraticBezier2D() {}
			/**
			* Return interpolate position based on cubic bezier definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vect2}    A new Vect2 interpolated position.
			*/
			MB_API
			virtual Vect2 evaluate(const float t);
		protected:
			std::vector<Vect2> _list;

			float bezierCurveInterpolation(const float p0, const float p1, const float p2, const float t);
		};
		class QuadraticBezier3D: public Curve3D
		{
			/**
			* QuadraticBezier constructor.
			* @param {Vect3} cpi  Starting point.
			* @param {Vect3} cpp  Middle control point.
			* @param {Vect3} cpe  Ending point.
			*/
			MB_API
			QuadraticBezier3D(const Vect3& cpi, const Vect3& cpp, const Vect3& cpe);
			MB_API
			virtual ~QuadraticBezier3D() {}
			/**
			* Return interpolate position based on cubic bezier definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vect3}    A new Vect3 interpolated position.
			*/
			MB_API
			virtual Vect3 evaluate(const float t);
		protected:
			std::vector<Vect3> _list;

			float bezierCurveInterpolation(const float p0, const float p1, const float p2, const float t);
		};
	}
}

#endif /* __MB_CURVES__ */
