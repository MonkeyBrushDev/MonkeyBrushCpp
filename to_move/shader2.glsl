// Plain additive (transparente marcando los bordes)
Tags { "Queue"="Transparent" "IgnoreProjector"="True" "RenderType"="Transparent" }
Blend One OneMinusSrcColor
Cull Off
Lighting Off
ZWrite Off
// Fragment
float4 mc = tex2D(_MatCap, i.cap) * _Color * 2.0;

// AddBumpped
half2 capCoord = half2(dot(i.c0, normals), dot(i.c1, normals));
float4 mc = (tex + (tex2D(_MatCap, capCoord*0.5 + 0.5)*2.0) - 1.0);

// Toon shading
uniform sampler2D tex;

uniform vec3 viewPos;
uniform vec3 color;

uniform float levels; // = 5.0;

void main() {
    float scaleFactor = 1.0 / levels;
    vec3 n = normalize(outNormal);
    vec3 s = normalize( viewPos.xyz - outPosition.xyz );
    vec3 ambient = color * vec3(0.135, 0.2225, 0.1575);
    float cosine = dot( s, n );
    vec3 diffuse = color * floor( cosine * levels ) * scaleFactor;

    fragColor = vec4(vec3(ambient + diffuse), 1.0);
}

// MARBLE
const vec3 Color1 = vec3(0.2, 0.2, 0.4);
const vec3 Color2 = vec3(0.7, 0.7, 0.7);

uniform float base_freq;

#import<SimpleNoise3D>

void main() {
    vec4 noisevec;
    noisevec.x = snoise(outPosition * base_freq * 1.0) * 8.0;
    noisevec.y = snoise(outPosition * base_freq * 2.0) * 4.0;
    noisevec.z = snoise(outPosition * base_freq * 4.0) * 2.0;
    noisevec.w = snoise(outPosition * base_freq * 8.0) * 1.0;
    noisevec = noisevec / 8.0;

    float intensity = abs(noisevec[0] - 0.20) +
                      abs(noisevec[1] - 0.10) +
                      abs(noisevec[2] - 0.05) +
                      abs(noisevec[3] - 0.025);


    intensity = clamp(intensity * 1.4, 0.0, 1.0);

    vec3 color = mix(Color1, Color2, intensity);
}

// GRANITE
const vec3 Color1 = vec3(0.35, 0.3, 0.2);
const vec3 Color2 = vec3(0.7, 0.7, 0.7);

uniform float base_freq;

#import<SimpleNoise3D>

void main() {
    vec4 noisevec;
    noisevec.x = snoise(outPosition * base_freq*1.0) * 8.0;
    noisevec.y = snoise(outPosition * base_freq*2.0) * 4.0;
    noisevec.z = snoise(outPosition * base_freq*4.0) * 2.0;
    noisevec.w = snoise(outPosition * base_freq*8.0) * 1.0;
    noisevec = noisevec / 8.0;

    float intensity = min(1.0, noisevec[3] * 12.0);
    //float intensity = min(1.0, noisevec[2] * 12.0 + noisevec[3]*12.0);
    vec3 color = mix(Color1, Color2, intensity);
}

// GOOCH
const vec3 SurfaceColor = vec3(1.0, 1.0, 1.0);
const vec3 CoolColor = vec3(159.0/255., 148.0/255., 1.);
const vec3 WarmColor = vec3(1.0, 75.0/255., 75./255.);
const float DiffuseWarm = 0.5;
const float DiffuseCool = 0.5;

void main() {
    vec3 lightVec = normalize(viewPos - outPosition);
    ReflectVec = normalize(reflect(-lightVec, outPosition));
    ViewVec = normalize(-outPosition);
    NdotL = (dot(lightVec, outNormal) + 1.0) * 0.5;
    vec3 kcool    = min(CoolColor + DiffuseCool * SurfaceColor, 1.0);
    vec3 kwarm    = min(WarmColor + DiffuseWarm * SurfaceColor, 1.0);
    vec3 color   = mix(kcool, kwarm, NdotL);
}

// STRIPES
uniform float base_freq;
const vec3 Color1 = vec3(0.8, 0.8, 0.8);
const vec3 Color2 = vec3(0.1, 0.1, 0.15);

void main() {
    float sawtooth = fract(V * base_freq);
    float triangle = abs(2.0 * sawtooth - 1.0);
    float dp = length(vec2(dFdx(V), dFdy(V)));
    float edge = dp * base_freq * 2.0;
    float square = smoothstep(0.5 - edge, 0.5 + edge, triangle);

    vec3 color = mix(Color1, Color2, square);
}