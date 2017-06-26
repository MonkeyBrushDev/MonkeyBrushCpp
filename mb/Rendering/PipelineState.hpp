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

#ifndef __MB_PIPELINE_STATE__
#define __MB_PIPELINE_STATE__

namespace mb
{
  class PipelineState
  {
  public:
    class RenderState
    {
    public:
      bool isEnabled( void ) const
      {
        return _enabled;
      }
      void setEnabled( bool value )
      {
        _enabled = value;
      }
    protected:
      RenderState( bool enabled = true )
        : _enabled( enabled )
      {
      }
      bool _enabled;
    };
    class WireFrameState : public RenderState
    {
    public:
      WireFrameState( bool enabled = true )
        : RenderState( enabled )
      {
      }
    };

    class ColorMaskState : public RenderState
    {
    public:
      ColorMaskState( bool enabled = true,
        bool rEnabled = true,
        bool gEnabled = true,
        bool bEnabled = true,
        bool aEnabled = true )
        : RenderState( enabled )
        , _rEnabled( rEnabled )
        , _gEnabled( gEnabled )
        , _bEnabled( bEnabled )
        , _aEnabled( aEnabled )
      {
      }
      bool isRMask( ) const { return _rEnabled; }
      bool isGMask( ) const { return _gEnabled; }
      bool isBMask( ) const { return _bEnabled; }
      bool isAMask( ) const { return _aEnabled; }
      void setRMask( bool enable ) { _rEnabled = enable; }
      void setGMask( bool enable ) { _gEnabled = enable; }
      void setBMask( bool enable ) { _bEnabled = enable; }
      void setAMask( bool enable ) { _aEnabled = enable; }
    protected:
      bool _rEnabled;
      bool _gEnabled;
      bool _bEnabled;
      bool _aEnabled;
    };


    class BlendingState : public RenderState
    {
    public:
      enum class SourceFunc
      {
        ZERO,
        ONE,
        SRC_COLOR,
        ONE_MINUS_SRC_COLOR,
        DST_COLOR,
        ONE_MINUS_DST_COLOR,
        SRC_ALPHA,
        ONE_MINUS_SRC_ALPHA,
        DST_ALPHA,
        ONE_MINUS_DST_ALPHA,
        SRC_ALPHA_SATURATE
      };
      enum class DstFunc
      {
        ZERO,
        ONE,
        SRC_COLOR,
        ONE_MINUS_SRC_COLOR,
        SRC_ALPHA,
        ONE_MINUS_SRC_ALPHA,
        DST_ALPHA,
        ONE_MINUS_DST_ALPHA
      };
      BlendingState( bool enabled = false,
        SourceFunc srcFunc = SourceFunc::SRC_ALPHA,
        DstFunc dstFunc = DstFunc::ONE_MINUS_SRC_ALPHA )
        : RenderState( enabled )
        , _srcBlendFunc( srcFunc )
        , _dstBlendFunc( dstFunc )
      {
      }
		  SourceFunc getSourceFunc( void ) const { return _srcBlendFunc; }
		  void setSrcBlendFunc( SourceFunc value ) { _srcBlendFunc = value; }

		  DstFunc getDstFunc( void ) const { return _dstBlendFunc; }
		  void setDstBlendFunc( DstFunc value ) { _dstBlendFunc = value; }

	  protected:
      SourceFunc _srcBlendFunc;
      DstFunc _dstBlendFunc;
    };
    class CullFaceState : public RenderState
    {
    public:
      enum class Mode: short
      {
        FRONT,
        BACK,
        FRONT_AND_BACK
      };
      CullFaceState( bool enabled = true, CullFaceState::Mode mode = CullFaceState::Mode::BACK )
        : RenderState( enabled )
        , _cullMode( mode )
      {
      }
      CullFaceState::Mode getCullFaceMode( void ) const
      {
        return _cullMode;
      }
      void setCullFaceMode( CullFaceState::Mode value )
      {
        _cullMode = value;
      }
    protected:
      CullFaceState::Mode _cullMode;
    };
    class DepthState : public RenderState
    {
    public:
      enum class CompareFunc {
        NEVER,
        LESS,
        EQUAL,
        LEQUAL,
        GREATER,
        NOT_EQUAL,
        GEQUAL,
        ALWAYS
      };
      DepthState( bool enabled = true, CompareFunc cmp = CompareFunc::LESS,
        bool w = true )
        : RenderState( enabled )
        , compare( cmp )
        , writable( w )
      {
      }
      // TODO: Getter and setter for CompareFunc and writable
      CompareFunc compare;
      bool writable;
    protected:
      bool _writable;
      CompareFunc _compare;
    };
    class StencilState: public RenderState
    {
    public:
      enum class CompareMode
      {
        NEVER, LESS, EQUAL, LEQUAL, GREATER, NOT_EQUAL, GEQUAL, ALWAYS
      };
      enum class OperationType
      {
        KEEP, ZERO, REPLACE, INCREMTN, DECREMENT, INVERT
      };
      StencilState( bool enabled = true)
        : RenderState( enabled )
        , Compare( CompareMode::NEVER )
        , Reference( 0 )
        , Mask( 0xFFFFFFFF )
        , WriteMask( 0xFFFFFFFF )
        , OnFail( OperationType::KEEP )
        , OnZFail( OperationType::KEEP )
        , OnZPass( OperationType::KEEP )
      {
      }
      CompareMode Compare;
      unsigned int Reference;
      unsigned int Mask;
      unsigned int WriteMask;
      OperationType OnFail;
      OperationType OnZFail;
      OperationType OnZPass;
    };
  public:
    // TODO: Complete
    CullFaceState& culling( void ) { return _cullingState; }
    BlendingState& blending( void ) { return _blendingState; }
    DepthState& depth( void ) { return _depthState; }
    StencilState& stencil( void ) { return _stencilState; }
  protected:
    CullFaceState _cullingState;
    BlendingState _blendingState;
    DepthState _depthState;
    StencilState _stencilState;
  };
}

#endif /* __MB_PIPELINE_STATE__ */
