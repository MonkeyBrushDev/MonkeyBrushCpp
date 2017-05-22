#ifndef __MB_CAMERA__
#define __MB_CAMERA__

#include "Node.hpp"
#include "../Maths/Frustum.hpp"
#include "../Maths/Ray.hpp"
#include "../Maths/Rect.hpp"
#include <mb/api.h>

/*
  TODO: Set projection type (Perspective/Orthographic)
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
    static void mainCamera( Camera *camera )
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
    RenderingPass* renderPass( );

    /*MB_API
    Ray& getRay( float px, float py ) const
    {
      float x = 2.0f * px - 1.0f;
      float y = 1.0f - 2.0f * py;

      Vector4 rayClip( x, y, -1.0f, 1.0f );

      Vector4 rayEye = getProjection( ).getInverse( ).getTranspose( ) * rayClip;
      rayEye = Vector4f( rayEye.x( ), rayEye.y( ), -1.0f, 0.0f );

      Vector4 rayW = getWorld( ).computeModel( ).getTranspose( ) * rayEye;

      Vector3 rayDir( rayW.x( ), rayW.y( ), rayW.z( ) );
      rayDir.normalize( );

      return Ray( getWorld( ).translate( ), rayDir );
    }*/
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
    const Viewport& getViewport( ) const
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
    void setFrustum( const Frustum& frustum )
    {
      _frustum = frustum;
      // TODO: Regenerate ortho and proj matrix
    }

    // TODO const Matrix4& getProjection( void ) const;
    // TODO void setProjection( const Matrix4& proj );

    // TODO const Matrix4& getOrthographic( void ) const;
    // TODO void setOrthographic( const Matrix4& ortho );

    // TODO const Matrix4& getView( void );
    // TODO void setView( const Matrix4 &view );

  private:
    bool _isMainCamera = false;
  protected:
    Frustum _frustum;
    RenderingPass* _renderPass;
    Viewport _viewport;

  public:
    void computeCullingPlanes( void )
    {
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

    bool culled( /*const BoundingVolume* v*/ ) const
    {
      if( !isCullingEnabled( ) )
      {
        return false;
      }
      /*for( auto& plane: _cullingPlanes )
      {
        if ( plane->inside( v ) )
        {
          return true;
        }
      }*/
      return false;
    }

  private:
    bool _cullingEnabled = true;
    // std::array< Plane, 6 > _cullingPlanes;
  };
}

#endif /* __MB_CAMERA__ */
