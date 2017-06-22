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

#ifndef __MB_CAMERA__
#define __MB_CAMERA__

#include "Node.hpp"
#include "../Maths/Frustum.hpp"
#include "../Maths/Plane.hpp"
#include "../Maths/Ray.hpp"
#include "../Maths/Rect.hpp"
#include "../Maths/Color.hpp"
#include <mb/api.h>

#include "../Maths/Vector3.hpp"
#include "../Maths/Matrix4.hpp"

namespace mb
{
  class RenderingPass;

  class Camera:
    public Node
  {
  public:
    MB_API
    static Camera *getMainCamera( void )
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

    MB_API
    const Matrix4& getProjection( void ) const { return _projectionMatrix; }
    MB_API
    void setProjection( const Matrix4& proj );

    MB_API
    const Matrix4& getOrthographic( void ) const { return _orthographicMatrix; }
    MB_API
    void setOrthographic( const Matrix4& ortho );

    MB_API
    const Matrix4& getView( void );
    MB_API
    void setView( const Matrix4& view );

    /*MB_API
    void setAspectRatio( float )
    {
      //auto& old_f = getFrustum( );
      //setFrustum( Frustum( -ar * old_f.getUMax(), ar * old_f.getUMax(), old_f.getUMin(), old_f.getUMax(), old_f.getDMin(), old_f.getDMax() ) );
    }
    MB_API
    void setFieldOfView( float fov )
    {
      auto& old_f = getFrustum( );
      old_f.setFieldOfView( fov );
      setFrustum( old_f );
    }*/
    MB_API
    const mb::Color& getClearColor( void ) const
    {
      return this->_clearColor;
    }
    MB_API
    void setClearColor( const mb::Color& color )
    {
      this->_clearColor = color;
    }
  private:
    bool _isMainCamera = false;
  protected:
    Frustum _frustum;
    Viewport _viewport;
    RenderingPass* _renderPass;

    Matrix4 _projectionMatrix;
    Matrix4 _orthographicMatrix;
    Matrix4 _viewMatrix;
    mb::Color _clearColor;
  public:
    void computeCullingPlanes( void );

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
  typedef std::shared_ptr< mb::Camera > CameraPtr;
}

#endif /* __MB_CAMERA__ */
