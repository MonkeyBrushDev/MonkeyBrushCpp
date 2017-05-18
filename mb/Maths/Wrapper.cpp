#include "Wrapper.hpp"

namespace mb
{
    Wrapper::Wrapper( void )
    {
      static const float _ident[] = {
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f,
                };
      std::vector<float> I = std::vector<float>( _ident, _ident + sizeof(_ident)
                                                 / sizeof(float));
      _values = glm::vec3( I.at(0), I.at(1), I.at(2) );

    }

}

