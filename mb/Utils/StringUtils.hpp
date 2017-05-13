/*
 * Copyright (c) 2017 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus
 * <https://github.com/maldicion069/monkeybrushplusplus>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef __MB_STRING_UTILS__
#define __MB_STRING_UTILS__

#include <mb/api.h>

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

namespace mb
{
	class StringUtils
	{
	public:
		template< typename E >
		static void toValue( std::string input, E& out )
		{
			std::stringstream ss;
			ss << input;
			ss >> out;
		}

		template< typename E>
		static std::vector< E > split( std::string entryStr, char delim )
		{
			std::vector< E > res;
			std::istringstream iss( entryStr );
			while( !iss.eof( ) )
			{
				std::string str;
				getline( iss, str, delim );
				E v;
				toValue< E >( str, v);
				res.push_back( v );
			}
			return res;
		}

        MB_API
		static std::string replaceAll( std::string str, std::string from, std::string to ) 
		{
		    if ( from.empty( ) )
		    {
		        return str;
		    }

		    size_t start_pos = 0;
		    while ( ( start_pos = str.find( from, start_pos ) ) != std::string::npos )
		    {
		        str.replace( start_pos, from.length(), to );
		        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
		    }

		    return str;
		}

		static std::string getFileExtension( std::string path ) 
		{
			auto pos = path.find_last_of( "." );
			if ( pos == std::string::npos )
			{
				return "";
			}

			return path.substr( pos );
		}
		
		static std::string splitLines( std::string input, int charsPerLine )
		{
			std::stringstream out;
            
            std::stringstream ss( input );
            std::string buffer;
            std::vector< std::string > lines;
            while ( std::getline( ss, buffer, '\n' ) )
            {
                lines.push_back( buffer );
            }
            
            for ( auto line : lines )
            {
                std::stringstream str;
                str << line;
                
                int charCount = 0;
                while ( !str.eof( ) )
                {
                    std::string temp;
                    str >> temp;
                    charCount += temp.length() + 1;
                    if ( charCount >= charsPerLine )
                    {
                        out << "\n";
                        charCount = 0;
                    }
                    
                    out << temp << " ";
                }
                out << "\n";
            }

			return out.str();
		}
		
        static std::string toUpper( const std::string &str )
        {
            std::string result( str );
            std::transform( result.begin( ), result.end( ), result.begin( ), ::toupper );
            return result;
        }
		
        static std::string toLower( const std::string &str )
        {
            std::string result( str );
            std::transform( result.begin( ), result.end( ), result.begin( ), ::tolower );
            return result;
        }

        template< typename ... Args >
        static std::string toString( Args &&... args )
        {
            std::stringstream ss;
            ( void ) std::initializer_list< int >
            {
                (
					ss << args,
					0
				)...
            };
            
            return ss.str();
        }
	};
}

#endif /* __MB_STRING_UTILS__ __ */
