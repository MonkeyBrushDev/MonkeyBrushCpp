/**
 * Copyright (c) 2017, Monkey Brush
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

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