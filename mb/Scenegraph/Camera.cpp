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
  }
}
