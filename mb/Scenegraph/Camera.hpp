#ifndef __MB_CAMERA__
#define __MB_CAMERA__

#include "Node.hpp"
#include "../Maths/Frustum.hpp"
#include "../Maths/Plane.hpp"
#include "../Maths/Ray.hpp"
#include "../Maths/Rect.hpp"
#include <mb/api.h>

#include "../Maths/Vector3.hpp"
#include "../Maths/Matrix4.hpp"

/*
  TODO: Change Field of View and clipping planes
*/

namespace mb
{
  class RenderingPass;

  class Camera:
    public Node
  {
  public:
    MB_API
    static Camera *mainCamera( void )
    {
      return _mainCamera;
    }
    MB_API
    static void setMainCamera( Camera *camera )
    {
      _mainCamera = camera;
    }
  private:
    static Camera *_mainCamera;
  public:
    MB_API
    explicit Camera( void );

    MB_API
    Camera( const float& fov, const float& ar,
      const float& near, const float& far );

    MB_API
    virtual ~Camera( void );
  public:
    MB_API
    virtual void accept( Visitor& v ) override;
  public:
    MB_API
    void renderPass( RenderingPass* rp );
    MB_API
    RenderingPass* renderPass( void );

    MB_API
    Ray getRay( float px, float py ) const;

    MB_API
    bool isMainCamera( void ) const
    {
      return _isMainCamera;
    }
    MB_API
    void setIsMainCamera( bool v )
    {
      _isMainCamera = v;
    }
    MB_API
    const Viewport& getViewport( void ) const
    {
      return _viewport;
    }
    MB_API
    void setViewport( const Viewport& v )
    {
      this->_viewport = v;
    }

    MB_API
    const Frustum& getFrustum( void ) const
    {
      return _frustum;
    }
    MB_API
    void setFrustum( const Frustum& frustum );

    const Matrix4& getProjection( void ) const { return _projectionMatrix; }
    void setProjection( const Matrix4& proj );

    const Matrix4& getOrthographic( void ) const { return _orthographicMatrix; }
    void setOrthographic( const Matrix4& ortho );

    const Matrix4& getView( void ) const { return _viewMatrix; }
    void setView( const Matrix4& view );

  private:
    bool _isMainCamera = false;
  protected:
    Frustum _frustum;
    Viewport _viewport;
    RenderingPass* _renderPass;

    Matrix4 _projectionMatrix;
    Matrix4 _orthographicMatrix;
    Matrix4 _viewMatrix;
  public:
    void computeCullingPlanes( void )
    {
      /*
      Vector3 normal;
      float constant;

      Vector3 position = getWorld( ).getPosition( );
      */
      std::cout << "Computing near plane at _cullingPlanes[0]" << std::endl;
      std::cout << "Computing far plane at _cullingPlanes[1]" << std::endl;
      std::cout << "Computing top plane at _cullingPlanes[2]" << std::endl;
      std::cout << "Computing bottom plane at _cullingPlanes[3]" << std::endl;
      std::cout << "Computing left plane at _cullingPlanes[4]" << std::endl;
      std::cout << "Computing right plane at _cullingPlanes[5]" << std::endl;
    }

    MB_API
    void setCullingEnabled( bool value ) { _cullingEnabled = value; }
    MB_API
    bool isCullingEnabled( void ) const { return _cullingEnabled; }

    bool culled( const BoundingVolume* v ) const
    {
      if( !isCullingEnabled( ) )
      {
        return false;
      }
      for( auto& plane: _cullingPlanes )
      {
        if ( v->intersectPlane( plane ) )
        {
          return true;
        }
      }
      return false;
    }

  private:
    bool _cullingEnabled = true;
    std::array< Plane, 6 > _cullingPlanes;
  };
}

#endif /* __MB_CAMERA__ */
