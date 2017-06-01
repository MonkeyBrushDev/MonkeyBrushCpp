#include <iostream>
#include <mb/mb.h>
#include <string>
using namespace mb;

int main( )
{
    Material material;
    UniformPtr color = std::make_shared< mb::Uniform >(
                mb::UniformType::Vector3, mb::Vector3(1.0f, 0.0f, 0.0f) );
    material.addUniform("color", color);
    mb::Vector3 cc = material.uniform("color")->value().cast<mb::Vector3>();
    std::cout << cc << std::endl;

    Material* m2 = material.clone();
    m2->uniform("color")->value(mb::Vector3(0.0f, 1.0f, 0.0f) );
    mb::Vector3 cc2 = m2->uniform("color")->value().cast<mb::Vector3>();
    std::cout << cc2 << std::endl;
    return 0;
}
