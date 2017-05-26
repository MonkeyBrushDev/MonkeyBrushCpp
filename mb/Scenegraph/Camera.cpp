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
    if ( Camera::getMainCamera( ) == this )
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

    Vector3 rayDir = Vector3(
                getWorld( ).computeModel( ).getTranspose( ) * rayEye )
            .getNormalized( );

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

  const Matrix4& Camera::getView( void )
  {
    _viewMatrix = getWorld().computeModel();
    // TODO _viewMatrix.makeInverse();
    return _viewMatrix;
  }

  void Camera::setView( const Matrix4& view )
  {
    _viewMatrix = view;
    // world().fromMatrix( view.getInverse() );
    //_viewMatrix = view.getInverse();
  }

  void Camera::computeCullingPlanes( void )
  {
    Vector3 position = getWorld( ).getPosition( );
    Vector3 direction = getWorld( ).computeDirection( ).getNormalized( );
    Vector3 up = getWorld().getUp().getNormalized();
    Vector3 right = getWorld().getRight().getNormalized();

    //std::cout << "Computing near plane at _cullingPlanes[0]" << std::endl;
    _cullingPlanes[ 0 ] = Plane( direction, position + getFrustum().getDMin() * direction );

    //std::cout << "Computing far plane at _cullingPlanes[1]" << std::endl;
    _cullingPlanes[ 1 ] = Plane( -direction, position + getFrustum().getDMax() * direction );

    //std::cout << "Computing top plane at _cullingPlanes[2]" << std::endl;
    float invLengthTop = 1.0f / sqrtf(
                getFrustum().getDMin( ) * getFrustum( ).getDMin( ) +
                getFrustum().getUMax( ) * getFrustum( ).getUMax( ) );
    Vector3 normal = ( -getFrustum( ).getDMin() * up +
                       getFrustum( ).getUMax() * direction  ) * invLengthTop;
    float distance = normal * position;
    _cullingPlanes[ 2 ] = Plane( normal, distance );

    //std::cout << "Computing bottom plane at _cullingPlanes[3]" << std::endl;
    float invLengthBottom = 1.0f / sqrtf(
                getFrustum().getDMin( ) * getFrustum( ).getDMin( ) +
                getFrustum().getUMin( ) * getFrustum( ).getUMin( ) );
    normal = ( getFrustum().getDMin( ) * up -
               getFrustum( ).getUMin( ) * direction ) * invLengthBottom;
    distance = normal * position;
    _cullingPlanes[ 3 ] = Plane( normal, distance );

    //std::cout << "Computing left plane at _cullingPlanes[4]" << std::endl;
    float invLengthLeft = 1.0f / sqrtf(
                getFrustum().getDMin( ) * getFrustum().getDMin( ) +
                getFrustum().getRMin( ) * getFrustum().getRMin( ) );
    normal = ( getFrustum().getDMin( ) * right -
               getFrustum( ).getRMin( ) * direction ) * invLengthLeft;
    distance = normal * position;
    _cullingPlanes[ 4 ] = Plane( normal, distance );

    //std::cout << "Computing right plane at _cullingPlanes[5]" << std::endl;
    float invLengthRight = 1.0f / sqrtf(
                getFrustum().getDMin( ) * getFrustum( ).getDMin() +
                getFrustum().getRMax( ) * getFrustum( ).getRMax() );
    normal = ( -getFrustum().getDMin( ) * right +
               getFrustum( ).getRMax( ) * direction ) * invLengthRight;
    distance = normal * position;
    _cullingPlanes[ 5 ] = Plane( normal, distance );
  }
}
