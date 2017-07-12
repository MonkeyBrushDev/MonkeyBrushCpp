#include <mb/mb.h>

int main( )
{
  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 512, 512 ) );
  window->init( );

  mb::compute::ComputeShader computeShader(R"(
#version 430
uniform float FrameTime;
uniform writeonly image2D targetTex;
layout (local_size_x = 16, local_size_y = 16) in;
void main( )
{
  ivec2 storePos = ivec2(gl_GlobalInvocationID.xy);
  float coeffcient = 0.5*sin(float(gl_WorkGroupID.x +
    gl_WorkGroupID.y)*0.1 + FrameTime);
  coeffcient *= length(vec2(ivec2(gl_LocalInvocationID.xy) - ivec2(8)) /
    vec2(8.0));
  //imageStore(targetTex, storePos, vec4(1.0-coeffcient, 0.0, 0.0, 0.0));
    imageStore( targetTex, storePos, vec4( 1.0, 0.0, 0.0, 1.0));
})");

  mb::PostProcessMaterial pp;

  mb::PostProcessMaterial pp2(R"(
#version 430
in vec2 uv;

out vec4 fragColor;

uniform sampler2D targetTex;

void main( )
{
  fragColor = vec4( texture( targetTex, uv ).rgb, 1.0 );
})");

  mb::Texture2D* t = new mb::Texture2D( 512, 512 );

  mb::Renderer* r = new mb::OpenGLRenderer( );

  mb::Clock clockTime;
  clockTime.reset( );

  pp2.addUniform( "targetTex", std::make_shared< mb::TextureUniform >( t ) );

  while ( window->isRunning( ) )
  {
    window->pollEvents( );

    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Esc ) )
    {
      window->close( );
      break;
    }

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    clockTime.tick( );

    computeShader._program->sendUniformf( "FrameTime",
      ( float ) clockTime.getAccumTime( ) );
    computeShader._program->sendUniformi( "targetTex", 0 );

    t->bind( 0 );

    computeShader.dispatch( 512 / 16, 512 / 16, 1 );


    pp2.use( );

    r->drawScreenQuad( );

    window->swapBuffers( );
  }

  return 0;
}
