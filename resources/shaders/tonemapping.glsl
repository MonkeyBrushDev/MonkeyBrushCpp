// http://filmicworlds.com/blog/filmic-tonemapping-operators/

#define saturate(a) clamp( a, 0.0, 1.0 ) 
vec3 reinhardToneMapping( in vec3 color )
{
    return saturate( color / vec3( 1.0 ) + color );
}

#define Uncharted2TM( x ) ((x * (0.15 * x + 0.1 * 0.5) + 0.2 * 0.02) / (x * (0.15 * x + 0.5) + 0.2 * 0.3)) - 0.02 / 0.3

vec3 uncharted2ToneMapping( in vec3 color )
{
    vec3 curr = Uncharted2TM( color );
    vec3 white = vec3(1.0) / Uncharted2TM(vec3(11.2));
    return curr * white;
}

vec3 filmicToneMapping( in vec3 color )
{
    vec3 cc = max( vec3(0.0), color - vec3(0.004));
    return (cc * (6.2 * cc + .5)) / (cc * (6.2 * cc + 1.7) + 0.06);
}