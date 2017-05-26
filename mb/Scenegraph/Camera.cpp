#include "Camera.hpp"

#include "../Rendering/RenderPasses/StandardRenderingPass.hpp"

namespace mb
{
  Camera* Camera::_mainCamera = nullptr;

  Camera::Camera( )
    : Camera( 45.0f, 1.0f, 0.1f, 1000.0f )
  {
  }

  Camera:: Camera( const float& fov, const float& ar,
    const float& near, const float& far )
    : _frustum( fov, ar, near, far )
    , _viewport( 0.0f, 0.0f, 1.0f, 1.0f )
    , _renderPass( new StandardRenderingPass( ) )
  {
    for ( unsigned int i = 0; i < 32; ++i )
    {
      this->layer( ).enable( i );
    }
    _projectionMatrix = _frustum.computeProjMatrix( );
    _orthographicMatrix = _frustum.computeOthoMatrix( );
    _viewMatrix.makeIdentity( );
  }

  Camera::~Camera( )
  {
    if ( Camera::mainCamera( ) == this )
    {
      setMainCamera( nullptr );
    }
  }

  void Camera::accept( Visitor& v )
  {
    v.visitCamera( this );
  }

  void Camera::renderPass( RenderingPass* rp )
  {
    _renderPass = rp;
  }
  
  RenderingPass* Camera::renderPass( )
  {
    return _renderPass;
  }

  Ray Camera::getRay( float px, float py ) const
  {
    float x = 2.0f * px - 1.0f;
    float y = 1.0f - 2.0f * py;

    Vector4 rayClip( x, y, -1.0f, 1.0f );

    Vector4 rayEye = getProjection( ).getInverse( ).getTranspose( ) * rayClip;
    rayEye = Vector4( rayEye.x( ), rayEye.y( ), -1.0f, 0.0f );

    Vector4 rayW = getWorld( ).computeModel( ).getTranspose( ) * rayEye;

    Vector3 rayDir( rayW );
    rayDir.normalize( );

    return Ray( getWorld( ).getPosition( ), rayDir );
  }

  void Camera::setFrustum( const Frustum& frustum )
  {
    _frustum = frustum;
    _projectionMatrix = _frustum.computeProjMatrix( );
    _orthographicMatrix = _frustum.computeOthoMatrix( );
  }

  void Camera::setProjection( const Matrix4& proj )
  {
    _projectionMatrix = proj;
  }

  void Camera::setOrthographic( const Matrix4& ortho )
  {
    _orthographicMatrix = ortho;
  }

  void Camera::setView( const Matrix4& view )
  {
    _viewMatrix = view;
    // world().fromMatrix( view.getInverse() );
    //_viewMatrix = view.getInverse();
  }
}
