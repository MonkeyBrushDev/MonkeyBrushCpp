#ifndef __MB_PICKING_VISITOR__
#define __MB_PICKING_VISITOR__

#include "Visitor.hpp"
#include <functional>
#include <algorithm>
#include <vector>
#include "../Maths/Ray.hpp"

// TODO: Rewrite this code using FindNodes visitor extension.

namespace mb
{
  class Node;
  class PickingVisitor :
    public Visitor
  {
  private:
    typedef std::function< bool( Node* )> FilterType;
  public:
    class Results
    {
    public:
      void reset( void )
      {
        _candidates.clear( );
      }
      void sort( std::function< bool( Node *, Node * ) > callback )
      {
        std::sort( _candidates.begin( ), _candidates.end( ), callback );
      }
      void push( Node *candidate )
      {
        _candidates.push_back( candidate );
      }
      void forEachCandidate( std::function< void( Node * ) > callback )
      {
        auto cs = _candidates;
        for ( auto c : cs )
        {
          callback( c );
        }
      }
      bool hasResults( void )
      {
        return !_candidates.empty( );
      }
      Node *getBestCandidate( void )
      {
        if ( !hasResults( ) )
        {
          return nullptr;
        }
        return _candidates.front( );
      }
    private:
      std::vector< Node* > _candidates;
    };
    MB_API
    PickingVisitor( const Ray& ray, Results &results, FilterType filter );
    MB_API
    virtual void traverse( Node *node ) override;
    MB_API
    virtual void visitNode( Node *node ) override;
    MB_API
    virtual void visitGroup( Group *node ) override;
  private:
    Ray _ray;
    Results &_results;
    FilterType _filter;
  };
}

#endif /* __MB_PICKING_VISITOR__ */
