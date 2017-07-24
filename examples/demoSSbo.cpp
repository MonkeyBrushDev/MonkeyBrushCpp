#include <mb/mb.h>

class SsboSortComponent : public mb::Component
{
  IMPLEMENT_COMPONENT( SsboSortComponent )
public:
  SsboSortComponent( void )
  { }
  virtual void start( void )
  {
    const char* shader_str = R"(
#version 430
layout (local_size_x = 1) in;
layout( std430, binding = 0 ) buffer Arr {
  float Values[];
};

void main ( )
{
  /*uint idx = gl_GlobalInvocationID.x;
  Values[idx] = float(idx);*/

  int fragCount = 10;
  int inc = fragCount / 2;
		int i, j;
		float tmp;
		while (inc > 0) {
			for (i = inc; i < fragCount; i++) {
				tmp = Values[i];
				j = i;
				while (j >= inc && Values[j - inc] < tmp) {
					Values[j] = Values[j - inc];
					j -= inc;
				}
				Values[j] = tmp;
			}
			inc = int(inc / 2.2 + 0.5);
		}
})";
    computeShader = new mb::compute::ComputeShader( shader_str );


    GLuint gssbo;
    glGenBuffers( 1, &gssbo );
    glBindBufferBase( GL_SHADER_STORAGE_BUFFER, 0, gssbo );

    std::vector<float> arr = { 2.0f, 4.0f, 6.0f, 8.0f, 0.0f, 1.0f, 3.0f, 5.0f, 7.0f, 9.0f };

    glBufferData( GL_SHADER_STORAGE_BUFFER, arr.size( ) * sizeof( float ), arr.data( ), GL_DYNAMIC_DRAW );

    //ssbo = new mb::Ssbo( 10, arr.data( ), GL_STATIC_DRAW );
    //ssbo->bindBase( 0 );
  }
  virtual void update( const mb::Clock& )
  {
    //computeShader->dispatch( 10, 1, 1 );
    computeShader->program->use( );
    glDispatchCompute( 1, 1, 1 );
    glMemoryBarrier( GL_SHADER_STORAGE_BARRIER_BIT );

    unsigned int numElems = 10;
    std::vector< float > arrBuffer( numElems );
    glGetBufferSubData( GL_SHADER_STORAGE_BUFFER, 0, sizeof( float ) * numElems, arrBuffer.data( ) );

    std::cout << "OK" << std::endl;
  }
protected:
  mb::Ssbo* ssbo;
  mb::compute::ComputeShader* computeShader;
};

int main( )
{
  mb::Window* window = new mb::GLFWWindow2( mb::WindowParams( 512, 512 ) );
  window->init( );

  mb::Group* scene = new mb::Group( "Scene" );
  scene->addComponent( new SsboSortComponent( ) );

  mb::Application app;
  app.setSceneNode( scene );

  mb::Clock clockTime;
  clockTime.reset( );

  while ( window->isRunning( ) )
  {
    window->pollEvents( );

    if ( mb::Input::isKeyPressed( mb::Keyboard::Key::Esc ) )
    {
      window->close( );
      break;
    }

    clockTime.tick( );

    app.update( );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    window->swapBuffers( );
  }

  return 0;
}
