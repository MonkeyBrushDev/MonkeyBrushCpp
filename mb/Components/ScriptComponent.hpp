#ifndef __MB_SCRIPT_COMPONENT__
#define __MB_SCRIPT_COMPONENT__

// TODO: #include <boost/python.hpp>

#include <mb/api.h>
#include "Component.hpp"

namespace mb
{
	class ScriptComponent: public Component
  {
    IMPLEMENT_COMPONENT( ScriptComponent )
	public:
		MB_API
    ScriptComponent( const std::string &scriptFile );
		MB_API
		virtual void onAttach( void ) override;
	protected:
		std::string _scriptFile;
  };
}

#endif /* __MB_SCRIPT_COMPONENT__ */