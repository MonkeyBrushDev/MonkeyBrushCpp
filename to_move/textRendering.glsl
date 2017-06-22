#version 330 core
in vec3 position;
in vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 outTexCoord;

void main( )
{
    outTexCoord = texCoord;
    gl_Position = projection * view * model * vec4( position, 1.0 );
}


#version 330 core

in vec2 outTexCoord;
uniform sampler2D colorMap;
uniform vec4 diffuse;

void main( )
{
    fragColor = diffuse>
    float c = texture2D( colorMap, outTexCoord ).r;
    fragColor *= vec4( c );
    if ( fragColor.a < 0.1 ) discard;
}