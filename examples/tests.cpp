#include <iostream>
#include <mb/mb.h>
using namespace mb;
#include <string>

class RandomClass
{
  void hello2( )
  {

  }
  int hello;
  public:
  class {
    int value;
    public:
      int & operator = (const int &i) { return value = i; }
      operator int () const { return value; }
  } intAttr;

  public:
  class {
    float value;
    public:
    float & operator = (const float &f) { return value = f; }
    operator float () const
    {
      //hello();
      return value;
      //return value + hello;
    }
  } floatAttr;

  /*public:
  class {
    std::string value;
    public:
    std::string & operator = (const std::string &f) { return value = f; }
    operator std::string () const { return value; }
  } stringAttr;*/
};

#include <iostream>

/************************************************************
** This is where the magic goes
*************************************************************/

template <typename ClassT, typename TypeT, TypeT (ClassT::*Getter)() const>
class _Get
{
public:
  explicit _Get(ClassT const* self)
    : _this(self) {
  }
  inline operator TypeT() const
  {
    return (_this->*Getter)();
  }
private:
  TypeT operator=(TypeT value) const;
private:
  ClassT const* _this;
};
template <typename ClassT, typename TypeT, void (ClassT::*Setter)(TypeT)>
class _Set
{
public:
  explicit _Set(ClassT* self)
    : _this(self) {
  }
  inline TypeT operator=(TypeT value) const
  {
    (_this->*Setter)(value);
    return value;
  }
private:
  operator TypeT() const;
private:
  ClassT* _this;
};
template <typename ClassT, typename TypeT, TypeT (ClassT::*Getter)() const, void (ClassT::*Setter)(TypeT)>
class _GetSet
{
public:
  explicit _GetSet(ClassT* self)
    : _this(self) {
  }
  inline operator TypeT() const
  {
    return (_this->*Getter)();
  }
  inline TypeT operator=(TypeT value) const
  {
    (_this->*Setter)(value);
    return value;
  }
private:
  ClassT* _this;
};

#define GET(CLASS, TYPE, NAME, CODE)         \
  inline TYPE get##NAME() const CODE         \
  _Get<CLASS, TYPE, &CLASS::get##NAME> NAME;

#define SET(CLASS, TYPE, NAME, CODE)         \
  inline void set##NAME(TYPE value) CODE     \
  _Set<CLASS, TYPE, &CLASS::set##NAME> NAME;

#define GETSET(CLASS, TYPE, NAME, GET, SET)  \
  inline TYPE get##NAME() const GET          \
  inline void set##NAME(TYPE value) SET      \
  _GetSet<CLASS, TYPE, &CLASS::get##NAME, &CLASS::set##NAME> NAME;

/************************************************************
** End of magic, now demo!
*************************************************************/

class MyClass
{
private:
  int _attribute;

public:
  GET(MyClass, int, readOnlyProperty, {
    std::clog << "Getting attribute equals to " << _attribute << std::endl;
    return _attribute;
  })

  SET(MyClass, int, writeOnlyProperty, {
    std::clog << "Setting attribute to " << value << std::endl;
    _attribute = value;
  })

  GETSET(MyClass, int, readWriteProperty, {
    std::clog << "Getting attribute equals to " << _attribute << std::endl;
    return _attribute;
  },{
    std::clog << "Setting attribute to " << value << std::endl;
    _attribute = value;
  })

  MyClass()
    : _attribute(0),
      readOnlyProperty(this),
      writeOnlyProperty(this),
      readWriteProperty(this) {
  }
};

int main()
{
  MyClass myVar;

  // Read only
  std::cout << myVar.readOnlyProperty << std::endl; // OK
  //myVar.readOnlyProperty = 42; // Will fail

  // Write only
  //std::cout << myVar.writeOnlyProperty << std::endl; // Will fail
  myVar.writeOnlyProperty = 42; // OK
  std::cout << myVar.readOnlyProperty << std::endl;

  // Read write
  std::cout << myVar.readWriteProperty << std::endl; // OK
  myVar.readWriteProperty = 42; // OK
}
int main0( void )
{
  RandomClass foo;
  std::cout << foo.intAttr << std::endl;
  std::cout << foo.floatAttr << std::endl;
  //std::cout << foo.stringAttr << std::endl;
  foo.intAttr = 5;
  foo.floatAttr = 1.0f;
  //foo.stringAttr = "hola";
  std::cout << foo.intAttr << std::endl;
  std::cout << foo.floatAttr << std::endl;
  //std::cout << foo.stringAttr << std::endl;
  foo.intAttr = 5;
  std::cout << foo.intAttr << std::endl;
  std::cout << foo.floatAttr << std::endl;
  //std::cout << foo.stringAttr << std::endl;
  return 0;
}

int main2( void )
{
  mb::Transform ttf;

  //ttf.setPosition( mb::Vector3(2.0f, 4.0f, 6.0f));
  //ttf.setScale( mb::Vector3( 1.5f, 2.5f, 3.5f));

  ttf.setPosition( mb::Vector3::ZERO);
  ttf.setRotation( mb::Vector3( -1.0f, -1.0f, 0.0f ), mb::Mathf::degToRad(60.0f ) );
  ttf.setScale( mb::Vector3( 0.5f ) );


  auto model = ttf.computeModel( );
  /*auto vv = model.data( );
  std::cout << std::setiosflags( std::ios::fixed | std::ios::showpoint  )
        << std::setprecision( 2 ) << "("  << std::endl
  << vv[ 0 ] << ", " << vv[ 4 ] << ", " << vv[ 8 ]  << ", " << vv[ 12 ] << std::endl
  << vv[ 1 ] << ", " << vv[ 5 ] << ", " << vv[ 9 ]  << ", " << vv[ 13 ] << std::endl
  << vv[ 2 ] << ", " << vv[ 6 ] << ", " << vv[ 10 ]  << ", " << vv[ 14 ] << std::endl
  << vv[ 3 ] << ", " << vv[ 7 ] << ", " << vv[ 11 ]  << ", " << vv[ 15 ] << std::endl
  << ")"  << std::endl;*/
  std::cout << ttf.getRotation( ) << std::endl;
  ttf.setRotation( mb::Vector3( -1.0f, -1.0f, 0.0f ), mb::Mathf::degToRad(160.0f ) );
  std::cout << ttf.getRotation( ) << std::endl;
  ttf.setRotation( mb::Vector3( -1.0f, -1.0f, 0.0f ), mb::Mathf::degToRad(260.0f ) );
  std::cout << ttf.getRotation( ) << std::endl;
  ttf.setRotation( mb::Vector3( -1.0f, -1.0f, 0.0f ), mb::Mathf::degToRad(360.0f ) );
  std::cout << ttf.getRotation( ) << std::endl;
  ttf.setRotation( mb::Vector3( -1.0f, -1.0f, 0.0f ), mb::Mathf::degToRad(460.0f ) );
  std::cout << ttf.getRotation( ) << std::endl;
  return 0;
}
