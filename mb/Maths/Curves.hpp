#ifndef __MB_CURVES__
#define __MB_CURVES__

#include <mb/api.h>

#include "Vector2.hpp"
#include "Vector3.hpp"
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
			virtual ~Curve2D( void ) { }
			MB_API
			virtual Vector2 evaluate( const float& t ) = 0;
		};
		class Curve3D
		{
		public:
			MB_API
			virtual ~Curve3D( void ) { }
			MB_API
			virtual Vector3 evaluate( const float& t ) = 0;
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
			* @param {Vector2}   center      The center of the ellipse.
			* @param {Vector2}   radius      Ellipse major and minux radius.
			* @param {number}  startAngle  [description]
			* @param {number}  endAngle    [description]
			* @param {boolean} isClockwise if true, draws the ellipse
			*                              anticlockwise (counter-clockwise),
			*                              otherwise in a clockwise direction.
			*/
			MB_API
			Ellipse( const Vector2& center, const Vector2& radius, 
        float startAngle, float endAngle, bool isClockwise );
			virtual ~Ellipse( void ) { }
			/**
			* Return interpolate position based on ellipse definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vector2}    A new Vector2 interpolated position.
			*/
			MB_API
			virtual Vector2 evaluate( const float& t );
		protected:
			Vector2 _center;
			Vector2 _radius;
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
			* @param {Vector2} x Minimum point.
			* @param {Vector2} y Maximum point.
			*/
			MB_API
			Line2D( const Vector2& x, const Vector2& y );
			virtual ~Line2D( void ) { }
			/**
			* Return interpolate position based on 2D line definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vector2}    A new Vector2 interpolated position.
			*/
			MB_API
			virtual Vector2 evaluate( const float& t );
		protected:
			Vector2 _p1;
			Vector2 _p2;
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
			* @param {Vector3} x Minimum point.
			* @param {Vector3} y Maximum point.
			*/
			MB_API
			Line3D( const Vector3& x, const Vector3& y );
			virtual ~Line3D( void ) { }
			/**
			* Return interpolate position based on 3D line definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vector3}    A new Vector3 interpolated position.
			*/
			MB_API
			virtual Vector3 evaluate( const float& t );
		protected:
			Vector3 _p1;
			Vector3 _p2;
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
			* @param {Vector2} cpi  Starting point
			* @param {Vector2} cpp1 First control point
			* @param {Vector2} cpp2 Second control point
			* @param {Vector2} cpe  Ending point
			*/
			MB_API
			CubicBezier( const Vector2& cpi, const Vector2& cpp1, 
        const Vector2& cpp2, const Vector2& cpe );
			virtual ~CubicBezier( void ) { }
			/**
			* Return interpolate position based on cubic bezier definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vector2}    A new Vector2 interpolated position.
			*/
			MB_API
			virtual Vector2 evaluate( const float& t );
		protected:
			std::vector< Vector2 > _list;
			float bezierCurveInterpolation( const float& p0, const float& p1,
				const float& p2, const float& p3, const float& t );
		};
		class CubicBezier3D: public Curve3D
		{
		public:
			/**
			* CubicBezier constructor
			* @param {Vector3} cpi  Starting point
			* @param {Vector3} cpp1 First control point
			* @param {Vector3} cpp2 Second control point
			* @param {Vector3} cpe  Ending point
			*/
			MB_API
			CubicBezier3D( const Vector3& cpi, const Vector3& cpp1, 
        const Vector3& cpp2, const Vector3& cpe );
			MB_API
			virtual ~CubicBezier3D( void ) { }
			/**
			* Return interpolate position based on cubic bezier definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vector3}    A new Vector3 interpolated position.
			*/
			MB_API
			virtual Vector3 evaluate( const float& t );
		protected:
			std::vector< Vector3 > _list;

			float bezierCurveInterpolation( const float& p0, const float& p1,
				const float& p2, const float& p3, const float& t );
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
			* @param {Vector2} cpi  Starting point.
			* @param {Vector2} cpp  Middle control point.
			* @param {Vector2} cpe  Ending point.
			*/
			MB_API
			QuadraticBezier2D( const Vector2& cpi, const Vector2& cpp, 
        const Vector2& cpe );
			MB_API
			virtual ~QuadraticBezier2D( void ) { }
			/**
			* Return interpolate position based on cubic bezier definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vector2}    A new Vector2 interpolated position.
			*/
			MB_API
			virtual Vector2 evaluate( const float& t );
		protected:
			std::vector< Vector2 > _list;

			float bezierCurveInterpolation( const float& p0, const float& p1, 
        const float& p2, const float& t );
		};
		class QuadraticBezier3D: public Curve3D
		{
			/**
			* QuadraticBezier constructor.
			* @param {Vector3} cpi  Starting point.
			* @param {Vector3} cpp  Middle control point.
			* @param {Vector3} cpe  Ending point.
			*/
			MB_API
			QuadraticBezier3D( const Vector3& cpi, const Vector3& cpp, 
        const Vector3& cpe );
			MB_API
			virtual ~QuadraticBezier3D( void ) { }
			/**
			* Return interpolate position based on cubic bezier definition.
			* @param  {number} t Interpolation value [0, 1].
			* @return {Vector3}    A new Vector3 interpolated position.
			*/
			MB_API
			virtual Vector3 evaluate( const float& t );
		protected:
			std::vector< Vector3 > _list;

			float bezierCurveInterpolation( const float& p0, const float& p1, 
        const float& p2, const float& t );
		};
	}
}

#endif /* __MB_CURVES__ */
