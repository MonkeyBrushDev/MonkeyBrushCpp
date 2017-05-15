/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus
 * <https://github.com/maldicion069/monkeybrushplusplus>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef __MB_PROGRAM__
#define __MB_PROGRAM__

#include <mb/api.h>

#include <map>
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <regex>

namespace mb
{
	class Program
	{
	public:
    MB_API
    void autocatching( bool attributes = true, bool uniforms = true );

    MB_API
    Program( void );
		MB_API
    ~Program( void );
		/**
		* Method to load and add a vertex and fragment shaders from file
		* @param source: Vertex shader file source
		* @param source: Fragment shader source
		* @return Shader loaded
		*/
    MB_API
    bool load( const std::string& vsFile, const std::string& fsFile );
		/**
		* Method to load and add a vertex shader from file
		* @param source: Shader file source
		* @return Shader loaded
		*/
    MB_API
    bool loadVertexShader( const std::string& file );
		/**
		* Method to load and add a fragment shader from file
		* @param source: Shader file source
		* @return Shader loaded
		*/
		MB_API
    bool loadFragmentShader( const std::string& file );
#ifdef MB_GEOMETRY_SHADERS
		/**
		* Method to load and add a geometry shader from file
		* @param source: Shader file source
		* @return Shader loaded
		*/
    MB_API
    bool loadGeometryShader(const std::string& file);
#endif
#ifdef MB_TESSELATION_SHADERS
		/**
		* Method to load and add a tesselation evaluation shader from file
		* @param source: Shader file source
		* @return Shader loaded
		*/
    MB_API
    bool loadTesselationEvaluationShader(const std::string& file);
		/**
		* Method to load and add a tesselation control shader from file
		* @param source: Shader file source
		* @return Shader loaded
		*/
    MB_API
    bool loadTesselationControlShader(const std::string& file);
#endif
#ifdef MB_COMPUTE_SHADERS
		/**
		* Method to load and add a computer shader from file
		* @param source: Shader file source
		* @return Shader loaded
		*/
    MB_API
    bool loadComputeShader(const std::string& file);

		/**
		* Maximum global work group (total work in a dispatch)
		*/
    MB_API
    static void getMaximumGlobalWorkGroup(unsigned int& maxX, 
      unsigned int& maxY, unsigned int& maxZ);
		/**
		* Maximum local work group (one shader's slice)
		*/
    MB_API
    static void getMaximumLocalWorkGroup(unsigned int& maxX, 
      unsigned int& maxY, unsigned int& maxZ);
		/**
		* Maximum compute shader invocations (x * y * z)
		*/
    MB_API
    static int getMaximumComputeShaderInvocations( void );
#endif
		/**
		* Method to load and add a vertex and fragment shaders from text
		* @param source: Vertex shader source
		* @param source: Fragment shader source
		* @return Shader loaded
		*/
    MB_API
    bool loadFromText( const std::string& vsSource, const std::string& fsSource );
		/**
		* Method to load and add a vertex shader from text
		* @param source: Shader source
		* @return Shader loaded
		*/
    MB_API
    bool loadVertexShaderFromText( const std::string& source );
		/**
		* Method to load and add a fragment shader from text
		* @param source: Shader source
		* @return Shader loaded
		*/
    MB_API
    bool loadFragmentShaderFromText( const std::string& source );
#ifdef MB_GEOMETRY_SHADERS
		/**
		* Method to load and add a geometry shader from text
		* @param source: Shader source
		* @return Shader loaded
		*/
		MB_API
		bool loadGeometryShaderFromText(const std::string& source);
#endif
#ifdef MB_TESSELATION_SHADERS
		/**
		* Method to load and add a tesselation evaluation shader from text
		* @param source: Shader source
		* @return Shader loaded
		*/
		MB_API
		bool loadTesselationEvaluationShaderFromText(const std::string& source);
		/**
		* Method to load and add a tesselation control shader from text
		* @param source: Shader source
		* @return Shader loaded
		*/
		MB_API
		bool loadTesselationControlShaderFromText(const std::string& source);
#endif
#ifdef MB_COMPUTE_SHADERS
		/**
		* Method to load and add a computer shader from text
		* @param source: Shader source
		* @return Shader loaded
		*/
		MB_API
		bool loadComputeShaderFromText(const std::string& source);
#endif
		/**
		* Method to compile a program
		* @return If program compile and link OK
		*/
		MB_API
		bool compileAndLink(void);
		/**
		* Method to get Program id
		* @return program identifier.
		*/
		MB_API
		unsigned int program(void) const;
		/**
		* Method to enable a program
		*/
		MB_API
		void use(void);
		/**
		* Method to disable a program (not necessary)
		*/
		MB_API
		void unuse(void);
		/**
		* Method to catching an attribute value of a vertex shader
		* @param attr: Attribute name
		*/
		MB_API
		void addAttribute(const std::string& attr);
		/**
		* Method to catching an array of attribute values of a vertex shader
		* @param attrs: Attribute vector names
		*/
		MB_API
		void addAttributes(const std::vector<char*> attrs);
		/**
		* Method to bind a specific index to a attribute value
		* @param attr: Attribute name
		* @param index: Attribute index
		*/
		MB_API
		void bindAttribute(const std::string& attr, unsigned int index);
		/**
		* Method to catching an uniform value.
		* @param uniform: Uniform name
		*/
		MB_API
		void addUniform(const std::string& uniform);
		/**
		* Method to catching an array of uniform values.
		* @param uniforms: Uniform vector names
		*/
		MB_API
		void addUniforms(const std::vector<char*> uniforms);
		/**
		* Method to bind a specific index to a uniform value
		* @param uniform: Uniform name
		* @param index: Uniform index
		*/
		MB_API
		void bindUniform(const std::string& uniform, unsigned int index);
		/**
		* Method to catching an uniform buffer object
		* @param _ubo: Uniform Buffer Object name
		*/
		MB_API
		void addUbo(const std::string& _ubo);
#ifdef MB_SUBPROGRAMS
		/**
		* Method to cathing a subprogram in a specific kind of shader
		* @param name: Subprogram name
		* @param shaderType: OpenGL Shader type
		*/
		MB_API
		void addSubroutine(const std::string& name, int shaderType);
#endif
		/**
		* Method to get a attribute index in cache
		* @param _attr: Attribute name
		* @return Attribute index
		*/
		MB_API
		int attribute(const std::string& _attr);
		/**
		* Method to get a uniform index in cache
		* @param _unif: Uniform name
		* @return Uniform index
		*/
		MB_API
		int uniform(const std::string& _unif);
		/**
		* Method to get a Uniform Buffer Object index in cache
		* @param _ubo: Uniform Buffer Object name
		* @return Uniform Buffer Object index
		*/
		MB_API
		int ubo(const std::string& _ubo);
		/**
		* Method to get a subprogram index of a specific kind of shader
		*    in cache
		* @param name: Subprogram name
		* @param shaderType: OpenGL Shader type
		* @return Subprogram index
		*/
		MB_API
		unsigned int subprogram(const std::string& name, int shaderType);
		/**
		* Method to get a attribute index in cache
		* @param _attr: Attribute name
		* @return Attribute index
		*/
		MB_API
		int operator( )(const std::string& _attr);
		/**
		* Method to get a uniform index in cache
		* @param _unif: Uniform name
		* @return Uniform index
		*/
		MB_API
		int operator[](const std::string& _unif);
		/**
		* Method to send a boolean
		* @param uniform: Uniform name
		* @param val: Boolean data
		*/
		MB_API
		void sendUniformb(const std::string& uniform, bool val);
		/**
		* Method to send an integer
		* @param uniform: Uniform name
		* @param v: Int data
		*/
		MB_API
		void sendUniformi(const std::string& uniform, int val);
		/**
		* Method to send an unsigned integer
		* @param uniform: Uniform name
		* @param val: Unsigned integer data
		*/
		MB_API
		void sendUniformu(const std::string& uniform, unsigned int val);
		/**
		* Method to send a float
		* @param uniform: Uniform name
		* @param val: Float data
		*/
		MB_API
		void sendUniformf(const std::string& uniform, float val);
		/**
		* Method to send a vec3 with separated data
		* @param uniform: Uniform name
		* @param x: First element
		* @param y: Second element
		* @param z: Third element
		*/
		MB_API
		void sendUniform(const std::string& uniform, float x, float y, float z);
		/**
		* Method to send a vec2
		* @param uniform: Uniform name
		* @param data: Data
		*/
		MB_API
		void sendUniform2v(const std::string& uniform, const std::vector< float > & data);
		/**
		* Method to send a vec2
		* @param uniform: Uniform name
		* @param data: Data
		*/
		MB_API
		void sendUniform2v(const std::string& uniform, const float* data);
		/**
		* Method to send a vec3
		* @param uniform: Uniform name
		* @param data: Data
		*/
		MB_API
		void sendUniform3v(const std::string& uniform, const std::vector< float > & data);
		/**
		* Method to send a vec3
		* @param uniform: Uniform name
		* @param data: Data
		*/
		MB_API
		void sendUniform3v(const std::string& uniform, const float* data);
		/**
		* Method to send a vec4
		* @param uniform: Uniform name
		* @param data: Data
		*/
		MB_API
		void sendUniform4v(const std::string& uniform, const std::vector< float > & data);
		/**
		* Method to send a vec4
		* @param uniform: Uniform name
		* @param data: Data
		*/
		MB_API
		void sendUniform4v(const std::string& uniform, const float* data);

    /**
     * Method to send a ivec2
     * @param uniform: Uniform name
     * @param data: Data
     */
    MB_API
    void sendUniform2iv( const std::string& uniformName,
      const unsigned int* data );
    /**
     * Method to send a ivec2
     * @param uniform: Uniform name
     * @param data: Data
     */
    MB_API
    void sendUniform2iv( const std::string& uniformName,
      const std::vector< unsigned int > & data );
    /**
     * Method to send a ivec3
     * @param uniform: Uniform name
     * @param data: Data
     */
    MB_API
    void sendUniform3iv( const std::string& uniformName,
      const unsigned int* data );
    /**
     * Method to send a ivec3
     * @param uniform: Uniform name
     * @param data: Data
     */
    MB_API
    void sendUniform3iv( const std::string& uniformName,
      const std::vector< unsigned int > & data );
    /**
     * Method to send a ivec4
     * @param uniform: Uniform name
     * @param data: Data
     */
    MB_API
    void sendUniform4iv( const std::string& uniformName,
      const unsigned int* data );
    /**
     * Method to send a ivec4
     * @param uniform: Uniform name
     * @param data: Data
     */
    MB_API
    void sendUniform4iv( const std::string& uniformName,
      const std::vector< unsigned int > & data );
    /**
     * Method to send a mat2
     * @param uniform: Uniform name
     * @param data: Data
     */
    MB_API
    void sendUniform2m( const std::string& uniform,
                        const std::vector< float > & data );
    /**
     * Method to send a mat2
     * @param uniform: Uniform name
     * @param data: Data
     */
    MB_API
    void sendUniform2m( const std::string& uniform,
                      const float* data );
		/**
		* Method to send a mat3
		* @param uniform: Uniform name
		* @param data: Data
		*/
		MB_API
		void sendUniform3m(const std::string& uniform, const std::vector< float > & data);
		/**
		* Method to send a mat3
		* @param uniform: Uniform name
		* @param data: Data
		*/
		MB_API
		void sendUniform3m(const std::string& uniform, const float* data);
		/**
		* Method to send a mat4
		* @param uniform: Uniform name
		* @param data: Data
		* @param inverse: Specifies whether to transpose
		*    the matrix as the values are loaded into the uniform variable
		*/
		MB_API
		void sendUniform4m(const std::string& uniform,
			const std::vector< float > & m, bool inverse = false);
		/**
		* Method to send a mat4
		* @param uniform: Uniform name
		* @param data: Data
		* @param inverse: Specifies whether to transpose
		*    the matrix as the values are loaded into the uniform variable
		*/
		MB_API
		void sendUniform4m(const std::string& uniform,
			const float* m, bool inverse = false);

#ifdef MB_SUBPROGRAMS
		/**
		* Method to active a subprogram in a specific shader
		* @param name: Subprogram name
		* @param shaderType: OpenGL Shader type
		*/
		MB_API
		void activeSubprogram(const std::string& name, int shaderType);
#endif

#ifdef MB_OCC_QUERY
		/**
		* Method to check if object is visible in frustrum
		* @return object is visible
		*/
		MB_API
		bool occlusionQuery(std::function<void()> renderFunc);
#endif

#ifdef MB_COMPUTE_SHADERS
		/**
		* Method to launch one or more compute work groups.
		* @param numGroupX: The number of work groups to be launched
		*                   in the X dimension.
		* @param numGroupY: The number of work groups to be launched
		*                   in the Y dimension.
		* @param numGroupZ: The number of work groups to be launched
		*                   in the Z dimension.
		*/
		MB_API
		void launchComputeWork(unsigned int numGroupX, unsigned int numGroupY,
			unsigned int numGroupZ);
#endif
#ifdef MB_TESSELATION_SHADERS
		/**
		* Method to get patch vertices.
		* @return Num of patches
		*/
		MB_API
		unsigned int getPatchVertices(void);
		/**
		* Method to get inner tesselation level.
		* @return Inner level
		*/
		MB_API
		float getInnerLevel(void);
		/**
		* Method to get outer tesselation level.
		* @return Outer level
		*/
		MB_API
		float getOuterLevel(void);
		/**
		* Method to set patch vertices.
		* @param numPatches: Num of patches
		*/
		MB_API
		void setPatchVertices(unsigned int numPatches);
		/**
		* Method to set inner tesselation level.
		* @param level: Inner level
		*/
		MB_API
		void setInnerLevel(float level);
		/**
		* Method to set outer tesselation level.
		* @param level: Outer level
		*/
		MB_API
		void setOuterLevel(float level);
#endif
#ifdef MB_GEOMETRY_SHADERS
		/**
		* Method to get max output vertices.
		* @return int: Máx. num of vertices
		*/
		MB_API
		int getGeometryMaxOutput(void);
		/**
		* Method to get max input geometry type.
		* @return int: Input geometry type
		*/
		MB_API
		int getGeometryInputType(void);
		/**
		* Method to get output geometry type.
		* @return int: Output geometry type
		*/
		MB_API
		int getGeometryOutputType(void);
		/**
		* Method to set max output vertices.
		* @param maxValue: Max. num of vertices
		*/
		MB_API
		void setGeometryMaxOutput(unsigned int maxValue);
		/**
		* Method to set input geometry type.
		* @param inputValue: Input geometry type
		*/
		MB_API
		void setGeometryInputType(unsigned int inputValue);
		/**
		* Method to set output geometry type.
		* @param outputType: Output geometry type
		*/
		MB_API
		void setGeometryOutputType(unsigned int outputType);
#endif
		/**
		* Method to create program and attach all shaders
		*/
		MB_API
		void create(void);
		/**
		* Method to link program and check status
		*/
		MB_API
		bool link(void);

		MB_API
		std::map<std::string, unsigned int> uniforms() const
		{
			return this->_uniformList;
		}

		MB_API
		std::map<std::string, unsigned int> attributes() const
		{
			return this->_attrsList;
		}
	protected:
		void _destroy();
		bool _load(const std::string& file, int type);
		bool _loadFromText(const std::string& source, int type);

		unsigned int _program;
		std::map<std::string, unsigned int> _attrsList;
		std::map<std::string, unsigned int> _uniformList;
		std::map<std::string, unsigned int> _uboList;

#ifdef MB_SUBPROGRAMS
		typedef struct SubProgram
		{
			const char* name;
			unsigned int index;
			SubProgram(const char* n, unsigned int i)
			{
				this->name = n;
				this->index = i;
			}
		} SubProgram;
		std::multimap<int, SubProgram> _subprograms;
#endif
		std::vector<unsigned int> _shaders;

#ifdef MB_OCC_QUERY
		unsigned int _occQuery;
#endif
	};
}

#endif /* __MB_PROGRAM__ */
