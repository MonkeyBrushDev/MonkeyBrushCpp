#include "PrintNameVisitor.hpp"
#include <iostream>
#include <string>
#include "../Scenegraph/Node.hpp"

namespace mb
{
  PrintNameVisitor::PrintNameVisitor( )
  : LambdaVisitor( [] ( Node*n ){
    std::cout << n->name( ) << std::endl;
  } )
  {
  }

  PrintNameVisitor::~PrintNameVisitor( )
  {
  }
}
