#ifndef __BILLBOARD_INCLUDED__
#define __BILLBOARD_INCLUDED__

vec3 getScale( const in mat4 m ) {
  // Only working with positive scales.
  float xs = m[0][0] * m[0][1] * m[0][2] * m[0][3] < 0.0 ? -1.0 : 1.0;
  float ys = m[1][0] * m[1][1] * m[1][2] * m[1][3] < 0.0 ? -1.0 : 1.0;
  float zs = m[2][0] * m[2][1] * m[2][2] * m[2][3] < 0.0 ? -1.0 : 1.0;
  vec3 scale;
  scale.x = xs * sqrt( m[0][0] * m[0][0] + m[0][1] * m[0][1] + m[0][2] * m[0][2]);
  scale.y = ys * sqrt( m[1][0] * m[1][0] + m[1][1] * m[1][1] + m[1][2] * m[1][2]);
  scale.z = zs * sqrt( m[2][0] * m[2][0] + m[2][1] * m[2][1] + m[2][2] * m[2][2]);
  return scale;
}

vec4 billboard( const in vec3 posi, const in mat4 mvMatrix, const in mat4 pMatrix ) {
  vec3 scale = getScale( mvMatrix );
  return pMatrix * (
    vec4( scale * posi, 1.0 ) + vec4( mvMatrix[ 3 ].xyz, 0.0 ) );
}

#endif
