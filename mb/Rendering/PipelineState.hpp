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
        , _bEnabled( gEnabled )
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
      BlendingState( bool enabled = true,
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
        bool writable = true )
        : RenderState( enabled )
      {
      }
      // TODO: Getter and setter for CompareFunc and writable
    };
  public:
    // TODO: Complete
    CullFaceState culling( void ) { return _cullingState; }
  protected:
    CullFaceState _cullingState;
  };
}

#endif /* __MB_PIPELINE_STATE__ */
