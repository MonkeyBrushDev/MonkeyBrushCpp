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

#ifndef __MB_ORBIT_CAMERA__
#define __MB_ORBIT_CAMERA__

#include "Component.hpp"

namespace mb
{
  class OrbitCamera: public Component
  {
  public:
    MB_API
    OrbitCamera( )
    : Component( )
    {
    }
    MB_API
    virtual void update( const mb::Clock& ) override
    {
      /* if (left_mouse)
      {
        mouseOrigin = Input.mousePosition;
        isRotation = true;
      }
      if (center_mouse)
      {
        mouseOrigin = Input.mousePosition;
        isZooming = true;
      }
      if (right_mouse)
      {
        mouseOrigin = Input.mousePosition;
        isPanning = true;
      }

      if (!left_mouse)      isRotation = false;
      if (!center_mouse)    isZooming = false;
      if (!right_mouse)     isPanning = false;

      // http://webglfactory.blogspot.com.es/2011/05/how-to-convert-world-to-screen.html
      if (isRotating)
      {
        auto pos = Camera::mainCamera( )->screenToViewportPoint(Input.mousePosition - mouseOrigin);

        transform.RotateAround(transform.position, transform.right, -pos.y * turnSpeed);
        transform.RotateAround(transform.position, Vector3.up, pos.x * turnSpeed);
      }

      // Move the camera on it's XY plane
      if (isPanning)
      {
        auto pos = Camera::mainCamera( )->screenToViewportPoint(Input.mousePosition - mouseOrigin);

        auto move = new Vector3(pos.x * panSpeed, pos.y * panSpeed, 0);
        transform.Translate(move, Space.Self);
      }

      // Move the camera linearly along Z axis
      if (isZooming)
      {
        auto pos = Camera::mainCamera( )->screenToViewportPoint(Input.mousePosition - mouseOrigin);

        Vector3 move = pos.y * zoomSpeed * transform.forward;
        transform.Translate(move, Space.World);
      }*/
    }
  protected:
    float turnSpeed = 4.0f;     // Speed of camera turning when mouse moves in along an axis
    float panSpeed = 4.0f;      // Speed of the camera when being panned
    float zoomSpeed = 4.0f;     // Speed of the camera going back and forth

    //Vector3 mouseOrigin;  // Position of cursor when mouse dragging starts
    bool isPanning;   // Is the camera being panned?
    bool isRotating;  // Is the camera being rotated?
    bool isZooming;   // Is the camera zooming?
  };
}

#endif /* __MB_ORBIT_CAMERA__ */
