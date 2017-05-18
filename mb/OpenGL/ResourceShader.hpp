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
