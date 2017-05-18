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
        , _cullMode( mode )
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
