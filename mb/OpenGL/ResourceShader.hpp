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

#ifndef __MB_RESOURCE_SHADER__
#define __MB_RESOURCE_SHADER__

#include <mb/api.h>

#include <unordered_map>
#include <fstream>
#include <sstream>

namespace mb
{
  class ResourceShader
  {
  public:
    static const std::string& get(const std::string& key);
    static bool exist(const std::string& key);
  public:
    MB_API
    static void loadShader(const std::string& alias, const std::string& filePath);
    MB_API
    static void loadShaderFromText(const std::string& alias, const std::string& src);
  protected:
    static void add(const std::string& key, const std::string& value);
    static void remove(const std::string& key);
    static void clear();

    static std::unordered_map<std::string, std::string> _files;
  };
}

#endif /* __MB_RESOURCE_SHADER__ */
