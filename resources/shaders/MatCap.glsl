#ifndef __MATCAP_GLSL__
#define __MATCAP_GLSL__

vec2 matcap(vec3 __eye, vec3 __normal)
{
  vec3 __reflected = reflect(__eye, __normal);

  float __m = 2.0 * sqrt(
    pow(__reflected.x, 2.0) +
    pow(__reflected.y, 2.0) +
    pow(__reflected.z + 1.0, 2.0)
  );

  return __reflected.xy / __m + 0.5;
}

#endif
