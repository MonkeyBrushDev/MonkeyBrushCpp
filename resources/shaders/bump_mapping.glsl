vec2 dHdxy_fwd()
{
  vec2 TexDx = dFdx( TexCoord );
  vec2 TexDy = dFdy( TexCoord );

  float Hll = bumpScale * texture2D( bumpMap, TexCoord ).x;
  float dBx = bumpScale * texture2D( bumpMap, TexCoord + TexDx ).x - Hll;
  float dBy = bumpScale * texture2D( bumpMap, TexCoord + TexDy ).x - Hll;

  return vec2( dBx, dBy );
}

vec3 perturbNormalArb( vec3 surf_pos, vec3 surf_norm )
{
  vec2 dHdxy = dHdxy_fwd( );

  vec3 vSigmaX = vec3( dFdx( surf_pos.x ), dFdx( surf_pos.y ), dFdx( surf_pos.z ) );
  vec3 vSigmaY = vec3( dFdy( surf_pos.x ), dFdy( surf_pos.y ), dFdy( surf_pos.z ) );
  vec3 vN = surf_norm;    // normalized

  vec3 R1 = cross( vSigmaY, vN );
  vec3 R2 = cross( vN, vSigmaX );

  float fDet = dot( vSigmaX, R1 );

  vec3 vGrad = sign( fDet ) * ( dHdxy.x * R1 + dHdxy.y * R2 );
  return normalize( abs( fDet ) * surf_norm - vGrad );
}
