class Component : public std::enable_shared_from_this<Component> {

class ComponentRenderable : public Component
{
public:
  ComponentRenderable(GameObject *gameObject)
  : Component(gameObject) {
  }

  virtual void render( ... ) = 0;

  // return render order
  // 0-999: Background. Mainly for skyboxes etc
  // 1000-1999 Opaque geometry (default)
  // 2000-2999 Transparent. This queue is sorted in a back to front order before rendering.
  // 3000-3999 Overlay
  virtual int renderOrder() = 0;
};

class Skybox: public ComponentRenderable
{
  int renderOrder( ) { return 1999; }
}

// Default renderOrder with material is 1000
