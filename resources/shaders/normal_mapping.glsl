#ifndef __NORMAL_MAPPING_INCLUDED__
#define __NORMAL_MAPPING_INCLUDED__

vec3 perturb_normal(vec3 p, vec3 n)
{
  vec3 dp1 = dFdx(p);
  vec3 dp2 = dFdy(p);
  vec2 duv1 = dFdx(TexCoord);
  vec2 duv2 = dFdy(TexCoord);
  vec3 S = normalize(dp1 * duv2.t - dp2 * duv1.t);
  vec3 T = normalize(-dp1 * duv2.s + dp2 * duv1.s);
  vec3 N = normalize(n);
  vec3 mapN = texture(normalCustomTexture, TexCoord).xyz * 2.0 - 1.0;
  mapN.xy = normalScale * mapN.xy;
  mat3 tsn = mat3(S, T, N);
  return normalize(tsn * mapN);
}

#endif
