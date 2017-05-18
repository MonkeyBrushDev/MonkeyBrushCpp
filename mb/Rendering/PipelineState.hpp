#ifndef __MB_PIPELINE_STATE__
#define __MB_PIPELINE_STATE__

namespace mb
{
  class PipelineState
  {
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
    class BlendingState : public RenderState
    {
    public:
      enum class SourceFunc
      {
        ZERO,
        ONE,
        SRC_COLOR,
        ONE_MINUS_SRC_COLOR,
        SRC_ALPHA,
        // ...
      };
      enum class DstFunc
      {
        ZERO,
        ONE,
        SRC_COLOR,
        ONE_MINUS_SRC_COLOR,
        SRC_ALPHA,
        ONE_MINUS_SRC_ALPHA,
        // ...
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
    class CullingState : public RenderState
    {
    public:
      enum Mode
      {
        FRONT,
        BACK,
        FRONT_AND_BACK
      };
      CullingState( bool enabled = true, CullingState::Mode mode = CullingState::Mode::BACK )
        : RenderState( enabled )
      {
      }
      CullingState::Mode getCullFaceMode( void ) const
      {
        return _cullMode;
      }
      void setCullFaceMode( CullingState::Mode value )
      {
        _cullMode = value;
      }
    protected:
      CullingState::Mode _cullMode;
    };
  public:
    // TODO: Similar to GlobalState in original MonkeyBrush
    CullingState culling( void ) { return _cullingState; }
  protected:
    CullingState _cullingState;
  };
}

#endif /* __MB_PIPELINE_STATE__ */
