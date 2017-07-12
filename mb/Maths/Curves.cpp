#include "Curves.hpp"

namespace mb
{
  namespace curves
  {
    Ellipse::Ellipse( const Vector2& center, const Vector2& radius, 
      float startAngle, float endAngle, bool isClockwise )
      : Curve2D( )
      , _center( center )
      , _radius( radius )
      , _startAngle( startAngle )
      , _endAngle( endAngle )
      , _isClockwise( isClockwise )
    { }
    Vector2 Ellipse::evaluate( const float& t )
    {
      float deltaAngle = this->_endAngle - this->_startAngle;
      if ( deltaAngle < 0.0f ) deltaAngle += Mathf::TWO_PI;
      if ( deltaAngle > Mathf::TWO_PI ) deltaAngle -= Mathf::TWO_PI;
      float angle = this->_isClockwise ? this->_endAngle + ( 1.0f - t ) *
        ( Mathf::TWO_PI - deltaAngle ) : this->_startAngle + t * deltaAngle;

      float tx = this->_center.x( ) + this->_radius.x( ) * std::cos( angle );
      float ty = this->_center.y( ) + this->_radius.y( ) * std::sin( angle );
      return Vector2( tx, ty );
    }
    Line2D::Line2D( const Vector2& x, const Vector2& y )
      : Curve2D( )
    {
      this->_p1 = x;
      this->_p2 = y;
    }
    Vector2 Line2D::evaluate( const float& t )
    {
      return ( ( _p2 - _p1 ) * t ) + _p1;
    }
    Line3D::Line3D( const Vector3& x, const Vector3& y )
      : Curve3D( )
    {
      this->_p1 = x;
      this->_p2 = y;
    }
    Vector3 Line3D::evaluate( const float& t )
    {
      return ( ( _p2 - _p1 ) * t ) + _p1;
    }
    CubicBezier::CubicBezier( const Vector2& cpi, const Vector2& cpp1, 
      const Vector2& cpp2, const Vector2& cpe )
      : Curve2D( )
    {
      this->_list.push_back( cpi );
      this->_list.push_back( cpp1 );
      this->_list.push_back( cpp2 );
      this->_list.push_back( cpe );
    }
    Vector2 CubicBezier::evaluate( const float& t )
    {
      return Vector2(
        this->bezierCurveInterpolation(
        this->_list[ 0 ].x( ), this->_list[ 1 ].x( ),
        this->_list[ 2 ].x( ), this->_list[ 3 ].x( ), t ),
        this->bezierCurveInterpolation(
        this->_list[ 0 ].y( ), this->_list[ 1 ].y( ),
        this->_list[ 2 ].y( ), this->_list[ 3 ].y( ), t )
        );
    }
    float CubicBezier::bezierCurveInterpolation( const float& p0, const float& p1,
      const float& p2, const float& p3, const float& t )
    {
      return ( p0 * std::pow( 1.0f - t, 3.0f ) ) +
        ( 3.0f * p1 * std::pow( 1.0f - t, 2.0f ) * t ) +
        ( 3.0f * p2 * t * t * ( 1.0f - t ) ) +
        ( p3 * t * t * t );
    }
    CubicBezier3D::CubicBezier3D( const Vector3& cpi, const Vector3& cpp1, 
      const Vector3& cpp2, const Vector3& cpe )
      : Curve3D( )
    {
      this->_list.push_back( cpi );
      this->_list.push_back( cpp1 );
      this->_list.push_back( cpp2 );
      this->_list.push_back( cpe );
    }
    Vector3 CubicBezier3D::evaluate( const float& t )
    {
      return Vector3(
        this->bezierCurveInterpolation(
        this->_list[ 0 ].x( ), this->_list[ 1 ].x( ), this->_list[ 2 ].x( ), 
          this->_list[ 3 ].x( ), t ),
        this->bezierCurveInterpolation(
        this->_list[ 0 ].y( ), this->_list[ 1 ].y( ), this->_list[ 2 ].y( ), 
          this->_list[ 3 ].y( ), t ),
        this->bezierCurveInterpolation(
        this->_list[ 0 ].z( ), this->_list[ 1 ].z( ), this->_list[ 2 ].z( ), 
          this->_list[ 3 ].z( ), t )
        );
    }
    float CubicBezier3D::bezierCurveInterpolation( const float& p0, const float& p1,
      const float& p2, const float& p3, const float& t )
    {
      return ( p0 * std::pow( 1.0 - t, 3.0f ) ) +
        ( 3.0f * p1 * std::pow( 1.0f - t, 2.0f ) * t ) +
        ( 3.0f * p2 * t * t * ( 1.0f - t ) ) +
        ( p3 * t * t * t );
    }
    QuadraticBezier2D::QuadraticBezier2D( const Vector2& cpi,
      const Vector2& cpp, const Vector2& cpe )
      : Curve2D( )
    {
      this->_list.push_back( cpi );
      this->_list.push_back( cpp );
      this->_list.push_back( cpe );
    }
    Vector2 QuadraticBezier2D::evaluate( const float& t )
    {
      return Vector2(
        this->bezierCurveInterpolation(
        this->_list[ 0 ].x( ), this->_list[ 1 ].x( ), 
          this->_list[ 2 ].x( ), t ),
        this->bezierCurveInterpolation(
        this->_list[ 0 ].y( ), this->_list[ 1 ].y( ), 
          this->_list[ 2 ].y( ), t )
        );
    }
    float QuadraticBezier2D::bezierCurveInterpolation( const float& p0,
      const float& p1, const float& p2, const float& t )
    {
      return  ( p0 * std::pow( ( 1.0f - t ), 2.0f ) ) +
        ( 2.0f * p1 * ( 1.0f - t ) * t ) +
        ( p2 * std::pow( t, 2.0f ) );
    }
    QuadraticBezier3D::QuadraticBezier3D( const Vector3& cpi,
      const Vector3& cpp, const Vector3& cpe )
      : Curve3D( )
    {
      this->_list.push_back( cpi );
      this->_list.push_back( cpp );
      this->_list.push_back( cpe );
    }
    Vector3 QuadraticBezier3D::evaluate( const float& t )
    {
      return Vector3(
        this->bezierCurveInterpolation(
        this->_list[ 0 ].x( ), this->_list[ 1 ].x( ), 
          this->_list[ 2 ].x( ), t ),
        this->bezierCurveInterpolation(
        this->_list[ 0 ].y( ), this->_list[ 1 ].y( ), 
          this->_list[ 2 ].y( ), t ),
        this->bezierCurveInterpolation(
        this->_list[ 0 ].z( ), this->_list[ 1 ].z( ), 
          this->_list[ 2 ].z( ), t )
        );
    }
    float QuadraticBezier3D::bezierCurveInterpolation( const float& p0,
      const float& p1, const float& p2, const float& t )
    {
      return  ( p0 * std::pow( ( 1.0f - t ), 2.0f ) ) +
        ( 2.0f * p1 * ( 1.0f - t ) * t ) +
        ( p2 * std::pow( t, 2.0f ) );
    }
  }
}
