#ifndef __MB_PICKING_VISITOR__
#define __MB_PICKING_VISITOR__

#include "Visitor.hpp"
#include <functional>
#include <algorithm>
#include <vector>
#include "../maths/Ray.hpp"

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
      Results( void ) {}
      ~Results( void ) {}
      void reset( void )
      {
        _candidates.clear( );
      }
      void sortCandidates( std::function< bool( Node *, Node * ) > cb )
      {
        std::sort( _candidates.begin( ), _candidates.end( ), cb );
      }
      void addCandidate( Node *candidate )
      {
        _candidates.push_back( candidate );
      }
      void eachCandidate( std::function< void( Node * ) > cb )
      {
        auto cs = _candidates;
        for ( auto c : cs )
        {
          cb( c );
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
    PickingVisitor( const Ray& ray,
      Results &results, FilterType filter );
    virtual ~PickingVisitor( );
    virtual void traverse( Node *node ) override;

    virtual void visitNode( Node *node ) override;
    virtual void visitGroup( Group *node ) override;
  private:
    Ray _ray;
    Results &_results;
    FilterType _filter;
  };
}

#endif /* __MB_PICKING_VISITOR__ */
