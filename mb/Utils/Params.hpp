#ifndef __MB_PARAMS__
#define __MB_PARAMS__

#include <map>

namespace mb
{
    class Params
    {
    private:
        static std::map< std::string, std::string > values;
    public:
        static float getFloat( const std::string& key );
        static float setFloat( const std::string& key, const float& v );
        static bool getBool( const std::string& key );
        static bool setBool( const std::string& key, const bool& v );
        static std::string get( const std::string& key );
        static std::string set( const std::string& key, const std::string& v );
        static bool existsKey( const std::string& key);
    };
}

namespace mb
{

    std::map<std::string, std::string> Params::values;
    float Params::getFloat(std::string key)
    {
        std::map<std::string, std::string>::iterator it = values.find(key);
        if (it == values.end())
        {
            std::string message = "No value found for key: " + key + " so using default of 0";
            return 0.0f;
        }
        else
        {
            return atof(it->second.c_str());
        }
    }
    bool Params::getBool(string key)
    {
        std::string value = Get(key);
        std::transform(value.begin(), value.end(), value.begin(), ::toupper);
        return (value == "TRUE");
    }

    std::string Params::get( const std::string& key)
    {
        return values.at(key);
    }

    void Params::setFloat( const std::string& key, const float& value)
    {
        std::stringstream valueS;
        valueS << value;
        values[key] = "" + valueS.str();
    }

    void Params::setBool( const std::string& key, const bool& value)
    {
        values[key] = "" + (value) ? true : false;
    }

    std::string set( const std::string& key, const std::string& v )
    {

    }

    bool Params::ExistsKey( const std::string& key)
    {
        return (values.find(key) != values.end());
    }
}

#endif /* __MB_PARAMS__ */
