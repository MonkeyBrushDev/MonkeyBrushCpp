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

#include "ResourceShader.hpp"

namespace mb
{
  std::unordered_map<std::string, std::string> ResourceShader::_files;

  void ResourceShader::add(const std::string& key, const std::string& value)
  {
    ResourceShader::_files[key] = value;
  }
  const std::string& ResourceShader::get(const std::string& key)
  {
    return ResourceShader::_files[key];
  }
  bool ResourceShader::exist(const std::string& key)
  {
    return ResourceShader::_files.find(key) != ResourceShader::_files.end();
  }
  void ResourceShader::remove(const std::string& key)
  {
    ResourceShader::_files.erase(key);
  }
  void ResourceShader::clear()
  {
    ResourceShader::_files.clear();
  }
  void ResourceShader::loadShader(const std::string& alias, const std::string& filePath)
  {
    // TODO: USE FILESYSTEM
    std::ifstream file(filePath);
    if (!file.is_open())
    {
      throw "File " + std::string(filePath) + " undefined";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    const std::string& src = buffer.str();
    ResourceShader::loadShaderFromText(alias, src);
  }
  void ResourceShader::loadShaderFromText(const std::string& alias, const std::string& shaderSource)
  {
    ResourceShader::add(alias, shaderSource);
  }
}
