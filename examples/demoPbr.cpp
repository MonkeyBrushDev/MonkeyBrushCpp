/**
 * Copyright (c) 2017, Monkey Brush
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#include <iostream>
#include <string>

#include <mb/mb.h>
#include <routes.h>

mb::Material* createMaterial( )
{
  mb::Material* customMaterial = new mb::Material( );

  customMaterial->program = std::make_shared< mb::Program >( );
  customMaterial->program->loadVertexShaderFromText( R"(
        #version 430
        layout(location = 0) in vec3 position;
        layout(location = 1) in vec3 normal;
        layout(location = 2) in vec2 uv;
        out vec3 outPosition;
        out vec3 outNormal;
        out vec2 outUV;

        uniform mat4 MB_MATRIXP;
        uniform mat4 MB_MATRIXV;
        uniform mat4 MB_MATRIXM;

        void main( void )
        {
          outPosition = vec3(MB_MATRIXM * vec4(position, 1.0));
          gl_Position = MB_MATRIXP * MB_MATRIXV * vec4(outPosition, 1.0);
          mat3 normalMatrix = mat3(inverse(transpose(MB_MATRIXM)));
          outNormal = normalize(normalMatrix * normal);
          outUV = uv;
        }
      )" );
  customMaterial->program->loadFragmentShaderFromText( R"(
        #version 430
        out vec4 fragColor;
        in vec3 outPos;
        in vec3 outNorm;
        in vec2 outUV;

        vec3 albedo = vec3(0.5, 0.0, 0.0);
        float metallic = 1.0;
        float roughness = 1.0;
        float ao = 1.0;

        const float PI = 3.14159265359;

        vec3 lightPositions[4];
        vec3 lightColors[4];

        uniform mat4 MB_MATRIXV;

        // ----------------------------------------------------------------------------
        float DistributionGGX(vec3 N, vec3 H, float roughness)
        {
          float a = roughness*roughness;
          float a2 = a*a;
          float NdotH = max(dot(N, H), 0.0);
          float NdotH2 = NdotH*NdotH;

          float nom   = a2;
          float denom = (NdotH2 * (a2 - 1.0) + 1.0);
          denom = PI * denom * denom;

          return nom / denom;
        }
        // ----------------------------------------------------------------------------
        float GeometrySchlickGGX(float NdotV, float roughness)
        {
          float r = (roughness + 1.0);
          float k = (r*r) / 8.0;

          float nom   = NdotV;
          float denom = NdotV * (1.0 - k) + k;

          return nom / denom;
        }
        // ----------------------------------------------------------------------------
        float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
        {
          float NdotV = max(dot(N, V), 0.0);
          float NdotL = max(dot(N, L), 0.0);
          float ggx2 = GeometrySchlickGGX(NdotV, roughness);
          float ggx1 = GeometrySchlickGGX(NdotL, roughness);

          return ggx1 * ggx2;
        }
        // ----------------------------------------------------------------------------
        vec3 fresnelSchlick(float cosTheta, vec3 F0)
        {
          return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
        }
        // ----------------------------------------------------------------------------

        void main( void )
        {
          lightPositions[0] = vec3(-10.0,  10.0, 10.0);
          lightPositions[1] = vec3( 10.0,  10.0, 10.0);
          lightPositions[2] = vec3(-10.0, -10.0, 10.0);
          lightPositions[3] = vec3(-10.0, -10.0, 10.0);

          lightColors[0] = vec3(1.0, 1.0, 1.0);
          lightColors[1] = vec3(1.0, 0.0, 0.0);
          lightColors[2] = vec3(0.0, 1.0, 0.0);
          lightColors[3] = vec3(0.0, 0.0, 1.0);


          vec3 viewPos = -transpose(mat3(MB_MATRIXV)) * MB_MATRIXV[3].xyz;


          vec3 N = normalize(outNorm);
          vec3 V = normalize(viewPos - outPos);
          vec3 R = reflect(-V, N);

          // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0
          // of 0.04 and if it's a metal, use their albedo color as F0 (metallic workflow)
          vec3 F0 = vec3(0.04);
          F0 = mix(F0, albedo, metallic);

          // reflectance equation
          vec3 Lo = vec3(0.0);
          for(int i = 0; i < 4; ++i)
          {
            // calculate per-light radiance
            vec3 L = normalize(lightPositions[i] - outPos);
            vec3 H = normalize(V + L);
            float distance = length(lightPositions[i] - outPos);
            float attenuation = 1.0 / (distance * distance);
            vec3 radiance = lightColors[i] * attenuation;

            // Cook-Torrance BRDF
            float NDF = DistributionGGX(N, H, roughness);
            float G   = GeometrySmith(N, V, L, roughness);
            vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);

            vec3 nominator    = NDF * G * F;
            float denominator = 4 * max(dot(V, N), 0.0) * max(dot(L, N), 0.0) + 0.001; // 0.001 to prevent divide by zero.
            vec3 brdf = nominator / denominator;

            // kS is equal to Fresnel
            vec3 kS = F;
            // for energy conservation, the diffuse and specular light can't
            // be above 1.0 (unless the surface emits light); to preserve this
            // relationship the diffuse component (kD) should equal 1.0 - kS.
            vec3 kD = vec3(1.0) - kS;
            // multiply kD by the inverse metalness such that only non-metals
            // have diffuse lighting, or a linear blend if partly metal (pure metals
            // have no diffuse light).
            kD *= 1.0 - metallic;

            // scale light by NdotL
            float NdotL = max(dot(N, L), 0.0);

            // add to outgoing radiance Lo
            Lo += (kD * albedo / PI + brdf) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
          }

          // ambient lighting (note that the next IBL tutorial will replace
          // this ambient lighting with environment lighting).
          vec3 ambient = vec3(0.03) * albedo * ao;

          vec3 color = ambient + Lo;

          // HDR tonemapping
          color = color / (color + vec3(1.0));
          // gamma correct
          color = pow(color, vec3(1.0/2.2));

          fragColor = vec4(color, 1.0);
        })" );
  customMaterial->program->compileAndLink( );
  customMaterial->program->autocatching( );

  customMaterial->addStandardUniforms( );

  customMaterial->state( ).culling( ).setEnabled( false );

  return customMaterial;
}

mb::Geometry* generateGeom( const mb::Color& )
{
  auto geom = new mb::Geometry( );

  geom->addPrimitive( new mb::SpherePrimitive( 5.0f, 15, 15,
                                               mb::Primitive::Type::TRIANGLES,
                                               mb::Primitive::DRAW_ELEMENTS ) );

  mb::Material* customMaterial = createMaterial( );

  mb::MaterialComponent* mc = geom->getComponent<mb::MaterialComponent>( );
  mc->addMaterial( mb::MaterialPtr( customMaterial ) );

  geom->addComponent( new mb::RotateComponent( mb::Vector3::ONE, 0.15f ) );

  return geom;
}

mb::Group* createScene( void )
{
  auto scene = new mb::Group( "scene" );

  auto camera = new mb::Camera( 45.0f, 500 / 500, 0.01f, 1000.0f );
  camera->local( ).translate( 0.0f, 0.0f, 15.0f );

  auto node = generateGeom( mb::Color::GREY );

  scene->addChild( node );

  camera->addComponent( new mb::FreeCameraComponent( ) );
  scene->addChild( camera );

  return scene;
}

int main( )
{
  mb::FileSystem::getInstance( )->setBaseDirectory( MB_EXAMPLES_RESOURCES_ROUTE );

  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 500, 500 ) );
  window->init( );
  window->setTitle( "Fog Demo" );

  mb::Application app;

  app.setSceneNode( createScene( ) );

  app.init( ); // initialize settings to render the scene...

  while ( window->isRunning( ) )
  {
    window->pollEvents( );

    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Esc ) )
    {
      window->close( );
      break;
    }

    app.update( );

    window->swapBuffers( );
  }
  return 0;
}
