#include <iostream>
#include <mb/mb.h>
#include <assert.h>
using namespace mb;

class ParentVisitorName : public Visitor
{
public:
  virtual void visitNode( Node* n ) override
  {
    if ( n->hasParent( ) )
    {
      n->name( n->parent( )->name( ) + "_" + n->name( ) );
    }
  }
  virtual void visitGroup( Group * g ) override
  {
    visitNode( g );
    Visitor::visitGroup( g );
  }
};

#include <thread>
#include <memory>

void debugBV( mb::BoundingVolume* bv )
{
  std::cout << "CENTER AT " << bv->getCenter( ) << " WITH RADIUS " 
    << bv->getRadius( ) << std::endl;
}

int main() 
{
  unsigned int triangles = 1;
  unsigned int instances = 65000;

  FloatBufferAttribute* ba = new mb::BufferAttribute<float>( 30, 3 );
  std::cout << 
    "SIZE: " << ba->getSize( ) << 
    ", COUNT: " << ba->getCount( ) << 
    ", X0: " << ba->getX<float>( 0 ) << 
    ", Y0: " << ba->getY<float>( 0 ) << 
    ", Z0: " << ba->getZ<float>( 0 ) << std::endl;
  std::vector<float> values;
  for(int i = 0; i < 90; ++i)
  {
    values.push_back( (i+1) * 1.5f );
  }
  FloatBufferAttribute* ba2 = new mb::BufferAttribute<float>(values, 3);
  std::cout << 
    "SIZE: " << ba2->getSize( ) << 
    ", COUNT: " << ba2->getCount( ) << 
    ", X0: " << ba2->getX<float>( 0 ) << 
    ", Y0: " << ba2->getY<float>( 0 ) << 
    ", Z0: " << ba2->getZ<float>( 0 ) << std::endl;

  ba->setXY<float>( 0, 21.3f, 15.9f );
  ba2->setXY<float>( 0, 21.3f, 15.9f );


  std::cout << 
    "SIZE: " << ba->getSize( ) << 
    ", COUNT: " << ba->getCount( ) << 
    ", X0: " << ba->getX<float>( 0 ) << 
    ", Y0: " << ba->getY<float>( 0 ) << 
    ", Z0: " << ba->getZ<float>( 0 ) << std::endl;
  std::cout << 
    "SIZE: " << ba2->getSize( ) << 
    ", COUNT: " << ba2->getCount( ) << 
    ", X0: " << ba2->getX<float>( 0 ) << 
    ", Y0: " << ba2->getY<float>( 0 ) << 
    ", Z0: " << ba2->getZ<float>( 0 ) << std::endl;
  system( "PAUSE" );
  return 0;
}

int main3( )
{
  /*mb::BoundingVolume* bv;// = new mb::SphereBoundingVolume( );

  debugBV( bv );
  bv->expand( Vector3( 2.0f, 0.0f, 0.0f ) );
  debugBV( bv );
  bv->expand( Vector3( -2.0f, 0.0f, 0.0f ) );
  debugBV( bv );*/

  system( "PAUSE" );
  return 0;
}

int main2( )
{
  auto group = new Group( "First group" );
  assert( group->name( ) == "First group" );
  assert( group->hasNodes( ) == false );

  auto lChild = new Group( "LChild" );
  assert( lChild->hasParent( ) == false );
  auto rChild = new Group( "RChild" );
  assert( rChild->hasParent( ) == false );

  group->addChild( lChild );
  assert( group->numChildren( ) == 1 );
  assert( group->hasParent( ) == false );
  assert( lChild->hasParent( ) == true );
  group->addChild( rChild );
  assert( group->numChildren( ) == 2 );
  assert( lChild->hasParent( ) == true );

  unsigned int count = 0;
  group->forEachNode( [ &] ( Node* )
  {
    ++count;
  } );
  assert( count == 2 );

  // Reattach
  assert( group->numChildren( ) == 2 );
  group->addChild( lChild );
  assert( group->numChildren( ) == 2 );

  // Detach
  group->removeChild( lChild );
  assert( group->numChildren( ) == 1 );
  group->addChild( lChild );
  assert( group->numChildren( ) == 2 );

  // Detach all mb
  assert( group->hasNodes( ) == true );
  group->removeChildren( );
  assert( group->hasNodes( ) == false );


  /*		node0
    		/   \
    	node1	node2
    			  /	\
    		node3	node4
  */

  {
    auto node0 = new Group( "node0" );
    auto node2 = new Group( "node2" );
    auto node1 = new Node( "node1" );
    auto node3 = new Node( "node3" );
    auto node4 = new Node( "node4" );

    node0->addChild( node1 );
    node0->addChild( node2 );
    node2->addChild( node3 );
    node2->addChild( node4 );

    node0->perform( ParentVisitorName( ) );

    assert( node0->name( ) == "node0" );
    assert( node1->name( ) == "node0_node1" );
    assert( node2->name( ) == "node0_node2" );
    assert( node3->name( ) == "node0_node2_node3" );
    assert( node4->name( ) == "node0_node2_node4" );
  }


  auto root = new Group( "Root" );
  auto node0 = new Group( "node0" );
  root->addChild( node0 );
  FetchLights fl;
  root->perform( fl );
  assert( fl.lights( ).size( ) == 0 );
  node0->addChild( new Light( ) );
  root->perform( fl );
  assert( fl.lights( ).size( ) == 1 );
  root->addChild( new Light( ) );
  root->perform( fl );
  assert( fl.lights( ).size( ) == 2 );

  system( "PAUSE" );
  return 0;
}