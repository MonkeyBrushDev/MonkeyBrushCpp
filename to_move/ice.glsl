TRANSPARENT
struct Input {
    float3 worldNormal;
        float3 viewDir;
};
fixed4 _MainColor;

void surf (Input IN, inout SurfaceOutputStandard o) {
  o.Albedo = _MainColor;
  float alpha = 1 - (abs(dot(IN.viewDir, IN.worldNormal)));
          o.Alpha =  alpha*1.5f;
}
