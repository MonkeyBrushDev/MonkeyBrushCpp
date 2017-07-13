// Vertex
vec2 matcap(vec3 eye, vec3 normal) {
    vec3 reflected = reflect(eye, normal);

    float m = 2.0 * sqrt(
        pow(reflected.x, 2.0) +
        pow(reflected.y, 2.0) +
        pow(reflected.z + 1.0, 2.0)
    );

    return reflected.xy / m + 0.5;
}
void main( )
{
    ...
    mat3 normalMatrix = mat3(inverse(transpose(view * model)));
    uvCap = matcap(viewPos, normalize(normalMatrix * normal));
}
// Fragment
...
void main( )
{
    ...
    fragColor = texture(capTex, uvCap);
}