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

namespace mb
{
  class Capabilites: public NonCopyable
  {
  public:
    uint32_t maxNumberOfViewports;          // max number of viewports (always at least 1)
    uint32_t maxNumberOfSimultaneousRenderTargets;  // max number of simultaneous render targets (if <1 render to texture is not supported)
    uint32_t maxTextureDimension;         //  max texture dimension (usually 2048, 4096, 8192 or 16384)
    uint32_t maxNumberOf2DTextureArraySlices;   // max number of 2D texture array slices (usually 512 up to 8192, in case there's no support for 2D texture arrays it's 0)
    uint32_t maxUniformBufferSize;          // max uniform buffer (UBO) size in bytes (usually at least 4096 *16 bytes, in case there's no support for uniform buffer it's 0)
    uint32_t maxTextureBufferSize;          // max texture buffer (TBO) size in texel (>65536, typically much larger than that of one-dimensional texture, in case there's no support for texture buffer it's 0)
    uint32_t maxIndirectBufferSize;         // max indirect buffer size in bytes (in case there's no support for indirect buffer it's 0)
    uint8_t  maxNumberOfMultisamples;       // max number of multisamples (always at least 1, usually 8)
    uint8_t  maxAnisotropy;

    // Tessellation-control-shader (TCS) stage and tessellation-evaluation-shader (TES) stage
    uint32_t maxNumberOfPatchVertices;        ///< Maximum number of vertices per patch (usually 0 for no tessellation support or 32 which is the maximum number of supported vertices per patch)
    // Geometry-shader (GS) stage
    uint32_t maxNumberOfGsOutputVertices;     ///< Maximum number of vertices a geometry shader (GS) can emit (usually 0 for no geometry shader support or 1024)
    bool drawInstanced;
  }
}

namespace mb
{
  class IRenderer: public NonCopyable
  {
  public:
    virtual ~IRenderer( void );
    const Capabilites& getCapabilites( void ) const;
    virtual const char* getName( void ) const = 0;
    virtual bool isInitialized( void ) const = 0;
    virtual bool isDebugEnabled( void ) = 0;
    virtual IFramebuffer* createFramebuffer(
      uint32_t numColorAttachments,
      const FramebufferAttachment*
        depthStencilFBOAttachment = nullptr ) = 0;
    virtual ITextureManager* createTextureManager( void ) = 0;
    // Begin scene rendering
    virtual bool beginRender( void ) = 0;
    virtual void submitCommandBuffer( const CommandBuffer& cmdBuffer ) = 0;
    virtual void endRender( void ) = 0;
    // Force the execution of render commands in finite time (sync)
    virtual void flush( void ) = 0;
    // Force the execution of render commands in finite time
    //  and wait until it's done (sync)
    virtual void finish( void = 0);
  protected:
    IRenderer( void );
    Capabilites _capabilities;
  };

  IRenderer::~IRenderer( void ) { }

  const Capabilites& IRenderer::getCapabilites( void ) const;
  {
    return _capabilities;
  }
}

namespace mb
{
  class IndexBuffer: public Renderer::IIndexBuffer
  {
  public:
    IndexBuffer::IndexBuffer(OpenGLRenderer& openGLRenderer,
      Renderer::IndexBufferFormat::Enum indexBufferFormat)
      : IIndexBuffer(reinterpret_cast<Renderer::IRenderer&>(openGLRenderer))
      , _openGLElementArrayBuffer(0)
      , _openGLType(Mapping::getOpenGLType(indexBufferFormat))
      , _indexSizeInBytes(
        Renderer::IndexBufferFormat::getNumberOfBytesPerElement(indexBufferFormat))
    {
      // Nothing here
    }
    virtual ~IndexBuffer( void );
    uint32_t getOpenGLElemenArrayBuffer( void ) const
    {
      return _openGLElementArrayBuffer;
    }
    uint32_t getOpenGLType( void ) const
    {
      return _openGLType;
    }
    uint32_t getIndexSizeInBytes( void ) const
    {
      return _indexSizeInBytes;
    }
  protected:
    uint32_t _openGLElementArrayBuffer;
    uint32_t _openGLType;
    uint32_t _indexSizeInBytes;
  };
}

namespace mb
{
  class BufferManager: public Renderer::IBufferManager
  {
  public:
    explicit BufferManager( OpenGLRenderer& renderer )
      : IBufferManager( renderer )
      , _extensions( &renderer.getExtensions( ) )
    virtual ~BufferManager( void );
  public:
    virtual Renderer::IVertexBuffer* createVertexBuffer(uint32_t numBytes,
      const void* data = nullptr, Renderer::BufferUsage bufferUsage = Renderer::BufferUsage::DYNAMIC_DRAW) override;
    virtual Renderer::IIndexBuffer* createIndexBuffer(uint32_t numBytes,
      Renderer::IndexBufferFormat::Enum indexBufferFormat, const void* data = nullptr,
      Renderer::BufferUsage bufferUsage = Renderer::BufferUsage::DYNAMIC_DRAW) override;
    virtual Renderer::IVertexArray* createVertexArray(
      const Renderer::VertexAttributes& vertexAttributes, uint32_t numberOfVertexBuffers,
      const Renderer::VertexArrayVertexBuffer* vertexBuffers,
      Renderer::IIndexBuffer* indexBuffer = nullptr) override;
    virtual Renderer::IUniformBuffer* createUniformBuffer(uint32_t numBytes,
      const void* data = nullptr,
      Renderer::BufferUsage bufferUsage = Renderer::BufferUsage::DYNAMIC_DRAW) override;
    virtual Renderer::ITextureBuffer* createTextureBuffer(uint32_t numBytes,
      Renderer::TextureFormat::Enum textureFormat, const void* data = nullptr,
      Renderer::BufferUsage bufferUsage = Renderer::BufferUsage::DYNAMIC_DRAW) override;
    virtual Renderer::IIndirectBuffer* createIndirectBuffer(uint32_t numBytes,
      const void* data = nullptr,
      Renderer::BufferUsage bufferUsage = Renderer::BufferUsage::DYNAMIC_DRAW) override;
  };
  Renderer::IVertexBuffer* BufferManager::createVertexBuffer(uint32_t numberOfBytes,
    const void* data, Renderer::BufferUsage bufferUsage)
  {
    return nullptr;
  }
  Renderer::IIndexBuffer* BufferManager::createIndexBuffer(uint32_t numberOfBytes,
    Renderer::IndexBufferFormat::Enum indexBufferFormat, const void* data,
    Renderer::BufferUsage bufferUsage)
  {

  }
  Renderer::IVertexArray* BufferManager::createVertexArray(
    const Renderer::VertexAttributes& vertexAttributes, uint32_t numberOfVertexBuffers,
    const Renderer::VertexArrayVertexBuffer* vertexBuffers,
    Renderer::IIndexBuffer* indexBuffer)
  {

  }
  Renderer::IUniformBuffer* BufferManager::createUniformBuffer(uint32_t numberOfBytes,
    const void* data, Renderer::BufferUsage bufferUsage)
  {

  }
  Renderer::ITextureBuffer* BufferManager::createTextureBuffer(uint32_t numberOfBytes,
    Renderer::TextureFormat::Enum textureFormat, const void* data,
    Renderer::BufferUsage bufferUsage)
  {

  }
  Renderer::IIndirectBuffer* BufferManager::createIndirectBuffer(uint32_t numberOfBytes,
    const void* data, Renderer::BufferUsage bufferUsage)
  {

  }
  class IContext: public NonCopyable
  {
    virtual bool isInitialized( void ) const  = 0;
    virtual void makeCurrent( void ) const = 0;
  };
  class Extensions
  {

  };
  class OpenGLRenderer: public IRenderer
  {
  public:
    virtual const char* getName( void ) const
    {
      return "OpenGL";
    }
    virtual void flush( void )
    {
      glFlush( );
    }
    virtual void finish( void )
    {
      glFinish( );
    }
  private:
    void debugMessageCallback( uint32_t src, uint32_t type, uint32_t id,
      uint32_t severity, int, const char* msg, const void * )
    {
      // Source to string
      char debugSrc[ 20 + 1 ][ 0 ];
      switch( src )
      {
        case GL_DEBUG_SOURCE_API_ARB:
          strncpy(debugSrc, "OpenGL", 20);
          break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:
          strncpy(debugSrc, "Windows", 20);
          break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:
          strncpy(debugSrc, "Shader compiler", 20);
          break;

        case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:
          strncpy(debugSrc, "Third party", 20);
          break;

        case GL_DEBUG_SOURCE_APPLICATION_ARB:
          strncpy(debugSrc, "Application", 20);
          break;

        case GL_DEBUG_SOURCE_OTHER_ARB:
          strncpy(debugSrc, "Other", 20);
          break;

        default:
          strncpy(debugSrc, "?", 20);
          break;
      }
      // Debug type to string
    char debugType[25 + 1]{0};  // +1 for terminating zero
    switch (type)
    {
      case GL_DEBUG_TYPE_ERROR_ARB:
        strncpy(debugType, "Error", 25);
        break;

      case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB:
        strncpy(debugType, "Deprecated behavior", 25);
        break;

      case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:
        strncpy(debugType, "Undefined behavior", 25);
        break;

      case GL_DEBUG_TYPE_PORTABILITY_ARB:
        strncpy(debugType, "Portability", 25);
        break;

      case GL_DEBUG_TYPE_PERFORMANCE_ARB:
        strncpy(debugType, "Performance", 25);
        break;

      case GL_DEBUG_TYPE_OTHER_ARB:
        strncpy(debugType, "Other", 25);
        break;

      default:
        strncpy(debugType, "?", 25);
        break;
      }

      // Debug severity to string
      char debugSeverity[20 + 1]{0};  // +1 for terminating zero
      switch (severity)
      {
        case GL_DEBUG_SEVERITY_HIGH_ARB:
          strncpy(debugSeverity, "High", 20);
          break;

        case GL_DEBUG_SEVERITY_MEDIUM_ARB:
          strncpy(debugSeverity, "Medium", 20);
          break;

        case GL_DEBUG_SEVERITY_LOW_ARB:
          strncpy(debugSeverity, "Low", 20);
          break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
          strncpy(debugSeverity, "Notification", 20);
          break;

        default:
          strncpy(debugSeverity, "?", 20);
          break;
      }

      printf("OpenGL error: OpenGL debug message\tSource:\"%s\"\tType:\"%s\"\tID:\"%d\"\tSeverity:\"%s\"\tMessage:\"%s\"\n", debugSrc, debugType, id, debugSeverity, msg);
    }
    void initializeCapabilites( void )
    {
      _capabilities.maxNumberOfViewports = 1; // TODO: GL_ARB_viewport_array

      glGetIntegerv( GL_MAX_TEXTURE_SIZE, &v );
      _capabilities.maxTextureDimension = static_cast<uint32_t>( v );

      glGetIntegerv( GL_MAX_ARRAY_TEXTURE_LAYERS_EXT, &v );
      _capabilities.maxNumberOf2DTextureArraySlices = static_cast<uint32_t>( v );

      glGetIntegerv( GL_MAX_UNIFORM_BLOCK_SIZE, &v );
      _capabilities.maxUniformBufferSize = static_cast<uint32_t>( v );

      glGetIntegerv( GL_MAX_TEXTURE_BUFFER_SIZE_EXT, &v );
      _capabilities.maxTextureBufferSize = static_cast<uint32_t>( v );

      _capabilities.maxIndirectBufferSize = 64 * 1024; // 64 kib

      glGetIntegerv(GL_MAX_SAMPLES, &v);
      if (v > 8)
      {
        // Limit to known maximum we can test, even if e.g. GeForce 980m reports 32 here
        v = 8;
      }
      _capabilities.maxNumberOfMultisamples = static_cast<uint8_t>( v );

      glGetIntegerv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &v );
      _capabilities.maxAnisotropy = static_cast<uint8_t>( v );

      _capabilities.drawInstanced = true;

      glGetIntegerv( GL_MAX_PATCH_VERTICES, &v );
      _capabilities.maxNumberOfPatchVertices = static_cast<uint32_t>( v );

      glGetIntegerv( GL_MAX_GEOMETRY_OUTPUT_VERTICES, &v );
      _capabilities.maxNumberOfGsOutputVertices = static_cast<uint32_t>( v );
    }
  };
}
