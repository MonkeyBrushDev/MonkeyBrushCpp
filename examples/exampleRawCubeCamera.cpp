#include <iostream>

#include <vector>
#include <iostream>

#define GLM_FORCE_RADIANS

template <class T>
void wrapArrayInVector( T *sourceArray, size_t arraySize, std::vector<T, std::allocator<T> > &targetVector ) {
  typename std::_Vector_base<T, std::allocator<T> >::_Vector_impl *vectorPtr =
    (typename std::_Vector_base<T, std::allocator<T> >::_Vector_impl *)((void *) &targetVector);
  vectorPtr->_M_start = sourceArray;
  vectorPtr->_M_finish = vectorPtr->_M_end_of_storage = vectorPtr->_M_start + arraySize;
}

template <class T>
void releaseVectorWrapper( std::vector<T, std::allocator<T> > &targetVector ) {
  typename std::_Vector_base<T, std::allocator<T> >::_Vector_impl *vectorPtr =
        (typename std::_Vector_base<T, std::allocator<T> >::_Vector_impl *)((void *) &targetVector);
  vectorPtr->_M_start = vectorPtr->_M_finish = vectorPtr->_M_end_of_storage = NULL;
}

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions

// Shaders
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 model;
layout (std140) uniform Matrices
{
  mat4 projection;
  mat4 view;
};

void main()
{
  gl_Position = projection * view * model * vec4(position, 1.0f);
  TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
} 
)";
const char* fragmentShaderSource = R"(
#version 330 core
in vec2 TexCoord;

out vec4 color;

uniform sampler2D myTexture;

void main()
{
  color = vec4( TexCoord, 0.0, 1.0 );
  color = texture( myTexture, TexCoord );
})";
#include <mb/mb.h>

using namespace mb;

mb::Program program;

mb::Switch* sw;
bool glmEnabled = false;

class GroupExplode : public mb::Component
{
  IMPLEMENT_COMPONENT( GroupExplode )
public:
  virtual void update(const float &dt_) override
  {
    time += dt_;
    float dt = std::sin(time);
    node()->local().setScale(Vector3((std::sin(dt) + 1.0f) * 0.5f));
    //node()->local().setRotation(mb::Quaternion::createFromAxisAngle(mb::Vector3(1.0f, 1.0f, 0.0f), angle));
  }
protected:
  float time;
};
mb::Camera* camera;
mb::Group* cubes;
int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* window = glfwCreateWindow(500, 500, "LearnOpenGL", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glewExperimental = GL_TRUE;
  glewInit();

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  glEnable(GL_DEPTH_TEST);

  program.loadVertexShaderFromText(vertexShaderSource);
  program.loadFragmentShaderFromText(fragmentShaderSource);
  program.compileAndLink();

  // Set up vertex data (and buffer(s)) and attribute pointers
  float vertices[] = {
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f,

    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
    -1.0f,  1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,

    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

     1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
     1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
     1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
     1.0f, -1.0f, -1.0f,  1.0f, 1.0f,
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,

    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f
  };
  GLuint VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  // TexCoord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0); // Unbind VAO

  glm::vec3 cubePositions[] = {
      glm::vec3( 2.0f,  5.0f, -15.0f),
      glm::vec3( 0.0f,  0.0f,  0.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3( 2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f,  3.0f, -7.5f),
      glm::vec3( 1.3f, -2.0f, -2.5f),
      glm::vec3( 1.5f,  2.0f, -2.5f),
      glm::vec3( 1.5f,  0.2f, -1.5f),
      glm::vec3(-1.3f,  1.0f, -1.5f)
  };

  camera = new mb::Camera();
  camera->local().translate( 0.0f, 0.0f, -6.0f);
  //mb::Transform cameraTransform;
  //cameraTransform.setPosition( 0.0f, 0.0f, -6.0f );
  //cameraTransform.lookAt( mb::Vector3::ZERO, mb::Vector3::UP );

  //camera->setView( cameraTransform.computeModel( ) );
  camera->setProjection( mb::Matrix4::perspective( 70.0f, 1.0f, 0.01f, 1000.0f ));

  std::cout << "VIEW:\n" << camera->getView( ) << std::endl;
  //std::cout << "PROJECTION:\n" << camera->getProjection( ) << std::endl;

  auto camProj = camera->getProjection( ).values( );

  int projLoc = glGetUniformLocation(program.program( ), "projection");
  int viewLoc = glGetUniformLocation(program.program( ), "view");
  int modelLoc = glGetUniformLocation(program.program( ), "model");
  int texLoc = glGetUniformLocation(program.program( ), "myTexture");

  mb::Texture* tex = new mb::Texture( "/home/maldicion069/Imágenes/unnamed (1).jpg" );

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  mb::Group* scene = new mb::Group("Scene");
  scene->addChild( camera );

  cubes = new mb::Group("Cubes");

  sw = new mb::Switch("Switch");

  mb::Group* g1 = new mb::Group("MyGroup1");
  mb::Group* g2 = new mb::Group("MyGroup2");

  for ( unsigned int i = 0; i < 5; ++i)
  {
    auto group = new mb::Group(std::string("Cube") + std::to_string(i+1));
    auto geom = new mb::Geometry(std::string("CubeGeom") + std::to_string(i + 1));
    geom->local().setPosition(cubePositions[i].x, cubePositions[i].y, cubePositions[i].z);
    geom->local().setScale(mb::Vector3(0.5f));

    geom->layer().set(i);

    geom->addComponent(new RotateComponent( mb::Vector3(1.0f, 1.0f,  0.0f), 0.1f ));

    group->addChild(geom);
    g1->addChild(group);
  }
  sw->addChild(g1);
  for ( unsigned int i = 5; i < 10; ++i)
  {
    auto group = new mb::Group(std::string("Cube") + std::to_string(i+1));
    auto geom = new mb::Geometry(std::string("CubeGeom") + std::to_string(i + 1));
    geom->local().setPosition(cubePositions[i].x, cubePositions[i].y, cubePositions[i].z);
    geom->local().setScale(mb::Vector3(0.5f));

    geom->layer().set(i);

    geom->addComponent(new RotateComponent( mb::Vector3(-1.0f, -1.0f,  0.0f), 0.1f ));

    group->addChild(geom);
    g2->addChild(group);
  }
  sw->addChild(g2);

  sw->setCurrentNodeIndex(1);

  cubes->addChild(sw);

  //cubes->addComponent(new GroupExplode( ));

  scene->addChild(cubes);


  mb::Group* _scene = scene;

  std::vector<Camera*> _cameras;

  FetchCameras fetchCameras;
  _scene->perform( fetchCameras );
  fetchCameras.forEachCamera( [ &] ( Camera* c )
  {
    if ( Camera::getMainCamera( ) == nullptr || c->isMainCamera( ) )
    {
      Camera::setMainCamera( c );
    }
    _cameras.push_back( c );
  } );

  _scene->perform( StartComponents( ) );

  // Deltatime
  GLfloat dt = 0.0f;	// Time between current frame and last frame
  GLfloat lastFrame = 0.0f;  	// Time of last frame



  GLuint uniformBlockIndexRed = glGetUniformBlockIndex(program.program( ), "Matrices");
  glUniformBlockBinding(program.program( ), uniformBlockIndexRed, 0);

  GLuint uboMatrices;
  glGenBuffers(1, &uboMatrices);
  glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
  glBufferData(GL_UNIFORM_BUFFER, 2 * 16 * sizeof(float), nullptr, GL_STATIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
  // Define the range of the buffer that links to a uniform binding point
  glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * 16 * sizeof(float) );



  // Game loop
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program.use();
    glBindVertexArray( VAO );

    GLfloat currentFrame = glfwGetTime();
    dt = currentFrame - lastFrame;
    lastFrame = currentFrame;

    _scene->perform(UpdateComponents( dt ));

    _scene->perform( UpdateWorldState( ) );

    std::vector< BatchQueuePtr > bqCollection;

    for( Camera* c: _cameras)
    {
      if ( c != nullptr && c->isEnabled( ) )
      {
        BatchQueuePtr bq = std::make_shared<BatchQueue>( );
        ComputeBatchQueue cbq( c, bq );
        _scene->perform( cbq );
        bqCollection.push_back( bq );
      }
    };

    if (!bqCollection.empty())
    {
      BatchQueuePtr mainQueue = nullptr;
      std::for_each( bqCollection.begin(), bqCollection.end(), [&](BatchQueuePtr bq)
      {
        if (bq->camera() != Camera::getMainCamera())
        {
          std::cout << "OUTSCREEN" << std::endl;
        }
        else
        {
          mainQueue = bq;
        }
      });

      if(mainQueue.get() != nullptr)
      {
        auto renderables = mainQueue->renderables( BatchQueue::RenderableType::OPAQUE );
        if ( !renderables.empty( ) )
        {

          // Store the projection matrix (we only have to do this once) (note: we're not using zoom anymore by changing the FoV. We only create the projection matrix once now)
          glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
          glBufferSubData(GL_UNIFORM_BUFFER, 0, 16 * sizeof(float), mainQueue->getProjectionMatrix().values( ).data( ) );
          glBufferSubData(GL_UNIFORM_BUFFER, 16 * sizeof(float), 16 * sizeof(float), mainQueue->getViewMatrix().values( ).data( ));
          glBindBuffer(GL_UNIFORM_BUFFER, 0);


          for ( Renderable*& renderable : renderables )
          {

            //glUniformMatrix4fv(projLoc, 1, GL_FALSE, mainQueue->getProjectionMatrix().values( ).data( ) );
            //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, mainQueue->getViewMatrix().values( ).data( ) );

            tex->bind( 0 );
            glUniform1i(texLoc, 0);

            glBindVertexArray(VAO);
            //renderable->geom->local().setRotation(mb::Quaternion::createFromAxisAngle(mb::Vector3(1.0f, 1.0f, 0.0f), angle));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, renderable->geom->world().computeModel().values( ).data( ) );
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
          }
        }
      }
    }
    glfwSwapBuffers(window);
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glfwTerminate();
  return 0;
}

float xx = 0.0f;
float yy = 0.0f;
float zz = -6.0f;

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int, int action, int)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
  if (action == GLFW_PRESS)
  {
    if ( key == GLFW_KEY_G)
    {
      glmEnabled = true;
      std::cout << "GLM ON" << std::endl;
    }
    if ( key == GLFW_KEY_H)
    {
      glmEnabled = false;
      std::cout << "GLM OFF" << std::endl;
    }
  }
  if (action == GLFW_PRESS)
  {
    if (key == GLFW_KEY_A)
    {
      xx += 0.5f;
      cubes->local().translate( 0.5f, 0.0f, 0.0f );
    }
    else if (key == GLFW_KEY_D)
    {
      xx -= 0.5f;
      cubes->local().translate( -0.5f, 0.0f, 0.0f );
    } else if (key == GLFW_KEY_W)
    {
      yy += 0.5f;
      cubes->local().translate( 0.50, 0.5f, 0.0f );
    }
    else if (key == GLFW_KEY_S)
    {
      yy -= 0.5f;
      cubes->local().translate( 0.5f, -0.5f, 0.0f );
    } else if (key == GLFW_KEY_E)
    {
      zz += 0.5f;
      cubes->local().translate( 0.50, 0.0f, 0.5f );
    }
    else if (key == GLFW_KEY_Q)
    {
      zz -= 0.5f;
      cubes->local().translate( 0.5f, 0.0f, -0.5f );
    }

    if (key == GLFW_KEY_0)
    {
      camera->layer().toggle(0);
    } else if (key == GLFW_KEY_1)
    {
      camera->layer().toggle(1);
    } else if (key == GLFW_KEY_2)
    {
      camera->layer().toggle(2);
    } else if (key == GLFW_KEY_3)
    {
      camera->layer().toggle(3);
    } else if (key == GLFW_KEY_4)
    {
      camera->layer().toggle(4);
    } else if (key == GLFW_KEY_5)
    {
      camera->layer().toggle(5);
    } else if (key == GLFW_KEY_6)
    {
      camera->layer().toggle(6);
    } else if (key == GLFW_KEY_7)
    {
      camera->layer().toggle(7);
    } else if (key == GLFW_KEY_8)
    {
      camera->layer().toggle(8);
    } else if (key == GLFW_KEY_9)
    {
      camera->layer().toggle(9);
    }

    if( key == GLFW_KEY_N)
    {
      sw->setCurrentNodeIndex(0);
    }
    else if( key == GLFW_KEY_M)
    {
      sw->setCurrentNodeIndex(1);
    }
  }
}
