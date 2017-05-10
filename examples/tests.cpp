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

int main( )
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
  group->forEachNode( [ &] ( Node* n )
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


  //		node0
  //		/   \
    //	node1	node2
  //			  /	\
    //		node3	node4

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

  return 0;
}