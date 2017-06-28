#ifndef __MATCAP_GLSL__
#define __MATCAP_GLSL__

vec2 matcap(vec3 _eye_, vec3 _normal_)
{
  vec3 _reflected_ = reflect(_eye_, _normal_);

  float _m_ = 2.0 * sqrt(
    pow(_reflected_.x, 2.0) +
    pow(_reflected_.y, 2.0) +
    pow(_reflected_.z + 1.0, 2.0)
  );

  return _reflected_.xy / _m_ + 0.5;
}

#endif
