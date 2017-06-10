#ifndef __SHADER_COOK_TORRANCE_SPECULAR__
#define __SHADER_COOK_TORRANCE_SPECULAR__

// https://github.com/stackgl/glsl-specular-cook-torrance/blob/master/index.glsl
float BeckmannDistribution(float x, float roughness) {
    float NdotH = max(x, 0.0001);
    float cos2Alpha = NdotH * NdotH;
    float tan2Alpha = (cos2Alpha - 1.0) / cos2Alpha;
    float roughness2 = max(roughness * roughness, 0.0001);
    float denom = 3.141592653589793 * roughness2 * cos2Alpha * cos2Alpha;
    return exp(tan2Alpha / roughness2) / denom;
}

// https://github.com/stackgl/glsl-specular-cook-torrance
float CookTorranceSpecular(vec3 lightDirection, vec3 viewDirection, vec3 surfaceNormal, float roughness){
    float VdotN = max(dot(viewDirection, surfaceNormal), 0.0);
    float LdotN = max(dot(lightDirection, surfaceNormal), 0.0);

    //Half angle vector
    vec3 H = normalize(lightDirection + viewDirection);

    //Geometric term
    float NdotH = max(dot(surfaceNormal, H), 0.0);
    float VdotH = max(dot(viewDirection, H), 0.000001);
    float LdotH = max(dot(lightDirection, H), 0.000001);
    float G1 = (2.0 * NdotH * VdotN) / VdotH;
    float G2 = (2.0 * NdotH * LdotN) / LdotH;
    float G = min(1.0, min(G1, G2));

    //Distribution term
    float D = BeckmannDistribution(NdotH, roughness);

    //Fresnel term
    float F = pow(1.0 - VdotN, 0.02);

    //Multiply terms and done
    return  G * F * D / max(3.14159265 * VdotN, 0.000001);
}

#endif
