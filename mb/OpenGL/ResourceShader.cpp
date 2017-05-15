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
