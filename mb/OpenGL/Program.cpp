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

#include "Program.hpp"
#include <fstream>
#include <iostream>

#include "../Includes.hpp"

#include "ResourceShader.hpp"
#include "../Utils/StringUtils.hpp"

#include <limits>       // std::numeric_limits

#define MACRO_SP_WARNING(name, type) std::cerr << "WARNING: '" << name << \
  "' " << type << " doesn't exist or appears unused." << std::endl;


namespace mb
{
	void Program::autocatching(bool attributes, bool uniforms)
	{
		int count;

		int size; // Variable size
		GLenum type; // Variable type (float, vecX, matX, ...)

		const GLsizei bufSize = 32;
		char name[bufSize]; // GLSL variable name
		int length; // Name length

		if (attributes)
		{
			glGetProgramiv(this->_program, GL_ACTIVE_ATTRIBUTES, &count);
			//printf("Active Attributes: %d\n", count);

			for (auto i = 0; i < count; ++i)
			{
				glGetActiveAttrib(this->_program, (GLuint)i, bufSize, &length,
					&size, &type, name);

				this->addAttribute(name);

				//printf("Attribute #%d Type: %u Name: %s\n", i, type, name);
			}
		}

		if (uniforms)
		{
			glGetProgramiv(this->_program, GL_ACTIVE_UNIFORMS, &count);
			//printf("Active Uniforms: %d\n", count);

			for (auto i = 0; i < count; ++i)
			{
				glGetActiveUniform(this->_program, (GLuint)i, bufSize, &length,
					&size, &type, name);

				this->addUniform(name);

				//printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
			}

		}
	}

	Program::Program(void)
	{
		_program = -1;
		_attrsList.clear();
		_uniformList.clear();
		_uboList.clear();
#ifdef MB_SUBPROGRAMS
		_subprograms.clear();
#endif
		_shaders.clear();

#ifdef MB_OCC_QUERY
		// Occlusion query object
		// TODO: You need to call this after OpenGL context creation
		//glGenQueries(1, &_occQuery);
#endif
	}

	Program::~Program(void)
	{
		_destroy();
	}

	bool Program::loadFromText(const std::string& vsSource,
		const std::string& fsSource)
	{
		return (_loadFromText(vsSource, GL_VERTEX_SHADER) &&
			_loadFromText(fsSource, GL_FRAGMENT_SHADER));
	}

  unsigned int matchSize( const std::smatch& match )
  {
    unsigned int i = 0;
    unsigned int j = 0;
    bool existLast = true;
    for ( const auto& m : match )
    {
      if ( m.length( ) > 0 ) {
        ++i; existLast = true;
      }
      else {
        ++j; existLast = false;
      }
    }
    if ( existLast ) {
      i += j;
    }
    return i;
  }

  std::string trim( std::string const& str )
  {
    if ( str.empty( ) )
      return str;

    std::size_t firstScan = str.find_first_not_of( ' ' );
    std::size_t first = firstScan == std::string::npos ? str.length( ) : firstScan;
    std::size_t last = str.find_last_not_of( ' ' );
    return str.substr( first, last - first + 1 );
  }

  std::string __processShader( std::string sourceCode )
  {
    static std::regex rgx( "#import<(.+)>(\\[(.*)\\])*(\\((.*)\\))*" );

    std::smatch match;
    std::string returnValue = std::string( sourceCode );
    while ( std::regex_search( returnValue, match, rgx ) )
    {
      std::string includeFile = match[ 1 ];

      unsigned int size = matchSize( match );

      if ( mb::ResourceShader::exist( includeFile ) )
      {
        std::string includeContent = mb::ResourceShader::get( includeFile );
        if ( size == 4 )
        {
          std::string indexString = match[ 3 ];
          std::string::size_type loc = indexString.find( ".." );
          if ( loc != std::string::npos )
          {
            auto indexSplits = StringUtils::split_str( indexString, ".." );
            unsigned int minIndex = std::stoi( indexSplits[ 0 ] );
            unsigned int maxIndex = std::stoi( indexSplits[ 1 ] );

            std::string sourceIncludeContent( includeContent );
            includeContent = "";

            for ( unsigned int i = minIndex; i < maxIndex; ++i )
            {
              includeContent += std::regex_replace( sourceIncludeContent,
                std::regex( "\\{N\\}" ), std::to_string( i ) );
            }
          }
        }
        if ( size == 6 )
        {
          auto splits = StringUtils::split_str( match[ 5 ], "," );
          for ( unsigned int index = 0; index < splits.size( ); ++index )
          {
            auto outerSplit = StringUtils::split_str( trim( splits[ index ] ), "=" );
            auto source = std::regex( trim( outerSplit[ 0 ] ) );
            auto dest = trim( outerSplit[ 1 ] );

            includeContent = std::regex_replace( includeContent,
              std::regex( source ), dest );
          }
        }
        std::string match0 = match[ 0 ].str( );
        std::string proccStr = __processShader( includeContent );
        returnValue = StringUtils::replace( returnValue, match0,
          proccStr );
      }
      else
      {
        // TODO: Load from file
        //mb::ResourceShader::loadShader( )
        return __processShader( returnValue );
      }
    }
    return returnValue;
  }



	bool Program::_loadFromText(const std::string& source, int type)
	{
		// Create and compile shader
		unsigned int shader;
		shader = glCreateShader(type);

    std::string str = __processShader( std::string( source ) );
		const char* cStr = str.c_str();
		glShaderSource(shader, 1, &cStr, nullptr);

		int status;
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			int infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar* infoLog = new GLchar[infoLogLength];
			glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog);
			std::cerr << "Compile log: " << infoLog << std::endl;
			delete[] infoLog;
			return false;
		}

		// Add to shaders in use
		_shaders.push_back(shader);
		return true;
	}

	bool Program::loadVertexShaderFromText(const std::string& source)
	{
		return _loadFromText(source, GL_VERTEX_SHADER);
	}

	bool Program::loadFragmentShaderFromText(const std::string& source)
	{
		return _loadFromText(source, GL_FRAGMENT_SHADER);
	}

#ifdef MB_GEOMETRY_SHADERS
	bool Program::loadGeometryShaderFromText(const std::string& source)
	{
		return _loadFromText(source, GL_GEOMETRY_SHADER);
	}
#endif

#ifdef MB_TESSELATION_SHADERS
	bool Program::loadTesselationEvaluationShaderFromText(
		const std::string& source)
	{
		return _loadFromText(source, GL_TESS_EVALUATION_SHADER);
	}

	bool Program::loadTesselationControlShaderFromText(
		const std::string& source)
	{
		return _loadFromText(source, GL_TESS_CONTROL_SHADER);
	}
#endif

#ifdef MB_COMPUTE_SHADERS
	bool Program::loadComputeShaderFromText(const std::string& source)
	{
		return _loadFromText(source, GL_COMPUTE_SHADER);
	}
#endif

	bool Program::_load(const std::string& fileName, int type)
	{
		unsigned int fileLen;

		// Load file
		std::ifstream file;
		file.open(fileName.c_str(), std::ios::in);
		if (!file)
		{
			std::cout << "File " << fileName << " not found" << std::endl;
			return false;
		}

		// File length
		file.seekg(0, std::ios::end);
		fileLen = int(file.tellg());
		file.seekg(std::ios::beg);

		// Read the file
		char* source = new char[fileLen + 1];

		int i = 0;
		while (file.good())
		{
			source[i] = char(file.get());
			if (!file.eof()) i++;
			else fileLen = i;
		}
		source[fileLen] = '\0';
		file.close();

		// Create and compile shader
		unsigned int shader;
		shader = glCreateShader(type);
		glShaderSource(shader, 1, (const GLchar**)&source,
			(const int*)&fileLen);

		int status;
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			int infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar *infoLog = new GLchar[infoLogLength];
			glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog);
			std::cerr << "Compile log (" << fileName << "): " << infoLog << std::endl;
			delete[] infoLog;
			return false;
		}
		delete source;

		// Add to shaders in use
		_shaders.push_back(shader);
		return true;
	}

	bool Program::load(const std::string& vsFile, const std::string& fsFile)
	{
		return (_load(vsFile, GL_VERTEX_SHADER) &&
			_load(fsFile, GL_FRAGMENT_SHADER));
	}

	bool Program::loadVertexShader(const std::string& file)
	{
		return _load(file, GL_VERTEX_SHADER);
	}

	bool Program::loadFragmentShader(const std::string& file)
	{
		return _load(file, GL_FRAGMENT_SHADER);
	}

#ifdef MB_GEOMETRY_SHADERS
	bool Program::loadGeometryShader(const std::string& file)
	{
		return _load(file, GL_GEOMETRY_SHADER);
	}
#endif

#ifdef MB_TESSELATION_SHADERS
	bool Program::loadTesselationEvaluationShader(
		const std::string& file)
	{
		return _load(file, GL_TESS_EVALUATION_SHADER);
	}

	bool Program::loadTesselationControlShader(const std::string& file)
	{
		return _load(file, GL_TESS_CONTROL_SHADER);
	}
#endif

#ifdef MB_COMPUTE_SHADERS
	bool Program::loadComputeShader(const std::string& file)
	{
		return _load(file, GL_COMPUTE_SHADER);
	}
	void Program::getMaximumGlobalWorkGroup(unsigned int& maxX,
    unsigned int& maxY, unsigned int& maxZ)
	{
		int work_grp_size[3];
		// maximum global work group (total work in a dispatch)
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_grp_size[0]);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &work_grp_size[1]);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &work_grp_size[2]);

		maxX = work_grp_size[0];
		maxY = work_grp_size[1];
		maxZ = work_grp_size[2];
		printf("max global (total) work group size x:%i y:%i z:%i\n",
			work_grp_size[0], work_grp_size[1], work_grp_size[2]);
	}
	void Program::getMaximumLocalWorkGroup(unsigned int& maxX,
    unsigned int& maxY, unsigned int& maxZ)
	{
		int work_grp_size[3];
		// maximum global work group (total work in a dispatch)
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_grp_size[0]);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_grp_size[1]);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_grp_size[2]);

		maxX = work_grp_size[0];
		maxY = work_grp_size[1];
		maxZ = work_grp_size[2];
		printf("max local (in one shader) work group sizes x:%i y:%i z:%i\n",
			work_grp_size[0], work_grp_size[1], work_grp_size[2]);
	}
	int Program::getMaximumComputeShaderInvocations()
	{
		int work_grp_inv;
		glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &work_grp_inv);
		printf("max computer shader invocations %i\n", work_grp_inv);

		return work_grp_inv;
	}
#endif

	void Program::_destroy(void)
	{
		_program = -1;
		_attrsList.clear();
		_uniformList.clear();
		_uboList.clear();

#ifdef MB_SUBPROGRAMS
		_subprograms.clear();
#endif
		_shaders.clear();
		size_t size = _shaders.size();
		for (size_t i = 0; i < size; ++i)
		{
			if (_shaders[i] != 0)
			{
				glDetachShader(_program, _shaders[i]);
			}
		}
		glDeleteProgram(_program);
	}

	void Program::create(void)
	{
		_program = glCreateProgram();
		size_t size = _shaders.size();
		for (size_t i = 0; i < size; i++)
		{
			if (_shaders[i] != 0)
			{
				glAttachShader(_program, _shaders[i]);
			}
		}
	}

	bool Program::link(void)
	{
		// link and check whether the program links fine
		int status;
		glLinkProgram(_program);
		glGetProgramiv(_program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			int infoLogLength;

			glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar* infoLog = new GLchar[infoLogLength];
			glGetProgramInfoLog(_program, infoLogLength, nullptr, infoLog);
			std::cerr << "Link log: " << infoLog << std::endl;
			delete[] infoLog;
			return false;
		}
		return true;
	}

	void Program::use(void)
	{
		glUseProgram(_program);
	}

	void Program::unuse(void)
	{
		glUseProgram(-1);
	}

	bool Program::compileAndLink(void)
	{
		create();
		return link();
	}

	unsigned int Program::program(void) const
	{
		return _program;
	}

	void Program::addAttribute(const std::string& attr)
	{
		unsigned int index = glGetAttribLocation(_program, attr.c_str());
		if (index != std::numeric_limits< unsigned int >::max())
		{
			_attrsList[attr] = index;
		}
		else
		{
			MACRO_SP_WARNING(attr, "attribute")
		}
	}

	void Program::addAttributes(const std::vector<char*> attrs)
	{
		for (auto& a : attrs)
		{
			addAttribute(a);
		}
	}

	void Program::addUniform(const std::string& uniformName)
	{
		unsigned int index = glGetUniformLocation(_program, uniformName.c_str());
		if (index != std::numeric_limits<unsigned int>::max())
		{
			_uniformList[uniformName] = index;
		}
		else
		{
			MACRO_SP_WARNING(uniformName, "uniform");
		}
	}

	void Program::addUniforms(const std::vector<char*> uniforms)
	{
		for (auto& u : uniforms)
		{
			addUniform(u);
		}
	}

	void Program::addUbo(const std::string& uboName)
	{
		unsigned int index = glGetUniformBlockIndex(_program, uboName.c_str());
		if (index != std::numeric_limits< unsigned int >::max())
		{
			_uboList[uboName] = index;
		}
		else
		{
			MACRO_SP_WARNING(uboName, "ubo");
		}
	}

#ifdef MB_SUBPROGRAMS
	void Program::addSubroutine(const std::string& name,
		int shaderType)
	{
		unsigned int idx = glGetSubroutineIndex(_program, shaderType, name.c_str());
		if (idx != std::numeric_limits< unsigned int >::max())
		{
			auto sub = SubProgram(name.c_str(), idx);
			_subprograms.insert(std::pair< int, SubProgram >(shaderType, sub));
		}
		else
		{
			MACRO_SP_WARNING(name, "subprogram");
		}
	}
#endif

	void Program::bindAttribute(const std::string& attr, unsigned int index)
	{
		glBindAttribLocation(_program, index, attr.c_str());
	}

	int Program::attribute(const std::string& attr)
	{
		auto it = _attrsList.find(attr);
		if (it != _attrsList.end())
		{
			return it->second;
		}
		else
		{
			return -1;
		}
	}

	int Program::operator( )(const std::string& attr)
	{
		return  attribute(attr);
	}

	int Program::uniform(const std::string& uniformName)
	{
		auto it = _uniformList.find(uniformName);
		if (it != _uniformList.end())
		{
			return it->second;
		}
		else
		{
			return -1;
		}
	}

	int Program::operator[ ](const std::string& attr)
	{
		return  uniform(attr);
	}

	int Program::ubo(const std::string& _ubo)
	{
		auto it = _uboList.find(_ubo);
		if (it != _uboList.end())
		{
			return it->second;
		}
		else
		{
			return -1;
		}
	}

#ifdef MB_SUBPROGRAMS
	unsigned int Program::subprogram(const std::string& name,
		int shaderType)
	{
		std::pair<std::multimap<int, SubProgram>::iterator,
			std::multimap<int, SubProgram>::iterator> ret;
		ret = _subprograms.equal_range(shaderType);
		for (std::multimap<int, SubProgram>::iterator it = ret.first;
			it != ret.second; it++)
		{
			if (it->second.name == name)
			{
				return it->second.index;
			}
		}
		std::cerr << "Subroutine not found" << std::endl;
		return -1;
	}
#endif

	void Program::bindUniform(const std::string& unif,
		unsigned int idx)
	{
		if (_uniformList.find(unif) == _uniformList.end())
		{
			_uniformList[unif] = idx;
		}
		else
		{
			std::cerr << "Uniform exist" << std::endl;
		}
	}

	void Program::sendUniform(const std::string& uniformName,
		float x, float y, float z)
	{
		int loc = uniform(uniformName);
		glUniform3f(loc, x, y, z);
	}

	void Program::sendUniform2v(const std::string& uniformName,
		const std::vector< float >& data)
	{
		int loc = uniform(uniformName);
		glUniform2fv(loc, 1, data.data());
	}

	void Program::sendUniform2v(const std::string& uniformName,
		const float* data)
	{
		int loc = uniform(uniformName);
		glUniform2fv(loc, 1, data);
	}

	void Program::sendUniform3v(const std::string& uniformName,
		const std::vector< float >& data)
	{
		int loc = uniform(uniformName);
		glUniform3fv(loc, 1, data.data());
	}

	void Program::sendUniform3v(const std::string& uniformName,
		const float* data)
	{
		int loc = uniform(uniformName);
		glUniform3fv(loc, 1, data);
	}

	void Program::sendUniform4v(const std::string& uniformName,
		const std::vector< float >& data)
	{
		int loc = uniform(uniformName);
		glUniform4fv(loc, 1, data.data());
	}

	void Program::sendUniform4v(const std::string& uniformName,
		const float* data)
	{
		int loc = uniform(uniformName);
		glUniform4fv(loc, 1, data);
	}
  void Program::sendUniform2iv( const std::string& uniformName,
                                      const unsigned int* data )
  {
    int loc = uniform( uniformName );
    if (loc >= 0) glUniform2i( loc, data[0], data[1]);
  }

  void Program::sendUniform2iv( const std::string& uniformName,
                                      const std::vector< unsigned int > & data )
  {
    int loc = uniform( uniformName );
    if (loc >= 0) glUniform2i( loc, data[0], data[1]);
  }

  void Program::sendUniform3iv( const std::string& uniformName,
                                      const unsigned int* data )
  {
    int loc = uniform( uniformName );
    if (loc >= 0) glUniform3i( loc, data[0], data[1], data[2]);
  }

  void Program::sendUniform3iv( const std::string& uniformName,
                                      const std::vector< unsigned int > & data )
  {
    int loc = uniform( uniformName );
    if (loc >= 0) glUniform3i( loc, data[0], data[1], data[2]);
  }

  void Program::sendUniform4iv( const std::string& uniformName,
                                      const unsigned int* data )
  {
    int loc = uniform( uniformName );
    if (loc >= 0) glUniform4i( loc, data[0], data[1], data[2], data[3]);
  }

  void Program::sendUniform4iv( const std::string& uniformName,
                                      const std::vector< unsigned int > & data )
  {
    int loc = uniform( uniformName );
    if (loc >= 0) glUniform4i( loc, data[0], data[1], data[2], data[3]);
  }
	void Program::sendUniform4m(const std::string& uniformName,
		const std::vector< float > & data, bool inverse)
	{
		int loc = uniform(uniformName);
		glUniformMatrix4fv(loc, 1, inverse, data.data());
	}
	void Program::sendUniform4m(const std::string& uniformName,
		const float* data, bool inverse)
	{
		int loc = uniform(uniformName);
		glUniformMatrix4fv(loc, 1, inverse, data);
	}

	void Program::sendUniform3m(const std::string& uniformName,
		const std::vector< float > & data)
	{
		int loc = uniform(uniformName);
		glUniformMatrix3fv(loc, 1, GL_FALSE, data.data());
	}

	void Program::sendUniform3m(const std::string& uniformName,
		const float* data)
	{
		int loc = uniform(uniformName);
		glUniformMatrix3fv(loc, 1, GL_FALSE, data);
	}

	void Program::sendUniform2m(const std::string& uniformName,
		const std::vector< float > & data)
	{
		int loc = uniform(uniformName);
		glUniformMatrix2fv(loc, 1, GL_FALSE, data.data());
	}

	void Program::sendUniform2m(const std::string& uniformName,
		const float* data)
	{
		int loc = uniform(uniformName);
		glUniformMatrix2fv(loc, 1, GL_FALSE, data);
	}

	void Program::sendUniformf(const std::string& uniformName,
		float val)
	{
		int loc = uniform(uniformName);
		glUniform1f(loc, val);
	}

	void Program::sendUniformi(const std::string& uniformName, int val)
	{
		int loc = uniform(uniformName);
		glUniform1i(loc, val);
	}

	void Program::sendUniformb(const std::string& uniformName,
		bool val)
	{
		int loc = uniform(uniformName);
		glUniform1i(loc, val);
	}

	void Program::sendUniformu(const std::string& uniformName, unsigned int val)
	{
		int loc = uniform(uniformName);
		glUniform1ui(loc, val);
	}

#ifdef MB_SUBPROGRAMS
	void Program::activeSubprogram(const std::string& name,
		int shaderType)
	{
		std::pair<std::multimap<int, SubProgram>::iterator,
			std::multimap<int, SubProgram>::iterator> ret;
		ret = _subprograms.equal_range(shaderType);
		for (std::multimap<int, SubProgram>::iterator it = ret.first;
			it != ret.second; it++)
		{
			if (it->second.name == name)
			{
				glUniformSubroutinesuiv(shaderType, 1, &it->second.index);
				return;
			}
		}
		std::cerr << "Subroutine not found" << std::endl;
	}
#endif

#ifdef MB_COMPUTE_SHADERS
	void Program::launchComputeWork(unsigned int numGroupX, unsigned int numGroupY,
		unsigned int numGroupZ)
	{
		glDispatchCompute(numGroupX, numGroupY, numGroupZ);
	}
#endif

#ifdef MB_TESSELATION_SHADERS

	unsigned int Program::getPatchVertices(void)
	{
		int n;
		glGetIntegerv(GL_PATCH_VERTICES, &n);
		return n;
	}
	float Program::getInnerLevel(void)
	{
		float l;
		glGetFloatv(GL_PATCH_DEFAULT_INNER_LEVEL, &l);
		return l;
	}
	float Program::getOuterLevel(void)
	{
		float l;
		glGetFloatv(GL_PATCH_DEFAULT_OUTER_LEVEL, &l);
		return l;
	}

	void Program::setPatchVertices(unsigned int n)
	{
		glPatchParameteri(GL_PATCH_VERTICES, n);
	}
	void Program::setInnerLevel(float level)
	{
		glPatchParameterfv(GL_PATCH_DEFAULT_INNER_LEVEL, &level);
	}
	void Program::setOuterLevel(float level)
	{
		glPatchParameterfv(GL_PATCH_DEFAULT_OUTER_LEVEL, &level);
	}
#endif

#ifdef MB_OCC_QUERY
	bool Program::occlusionQuery(std::function<void()> renderFunc)
	{
		// Disable writing to the color buffer and depth buffer.
		// We just wanna check if they would be rendered, not actually render them
		glColorMask(false, false, false, false);
		glDepthMask(GL_FALSE);
		glBeginQuery(GL_SAMPLES_PASSED, _occQuery);
		renderFunc();
		glEndQuery(GL_SAMPLES_PASSED);
		int samplesPassed = 0;
		glGetQueryObjectiv(_occQuery, GL_QUERY_RESULT, &samplesPassed);
		// Re-enable writing to color buffer and depth buffer
		glColorMask(true, true, true, true);
		glDepthMask(GL_TRUE);
		return samplesPassed > 0;
	}
#endif

#ifdef MB_GEOMETRY_SHADERS
	void Program::setGeometryMaxOutput(unsigned int maxOutput)
	{
		glProgramParameteri(_program, GL_GEOMETRY_VERTICES_OUT, maxOutput);
	}
	void Program::setGeometryInputType(unsigned int inputType)
	{
		glProgramParameteri(_program, GL_GEOMETRY_INPUT_TYPE, inputType);
	}
	void Program::setGeometryOutputType(unsigned int outputType)
	{
		glProgramParameteri(_program, GL_GEOMETRY_OUTPUT_TYPE, outputType);
	}

	int Program::getGeometryMaxOutput(void)
	{
		int maxOutput;
		glGetProgramiv(_program, GL_GEOMETRY_VERTICES_OUT, &maxOutput);
		return maxOutput;
	}

	int Program::getGeometryInputType(void)
	{
		int inputType;
		glGetProgramiv(_program, GL_GEOMETRY_INPUT_TYPE, &inputType);
		return inputType;
	}

	int Program::getGeometryOutputType(void)
	{
		int outputType;
		glGetProgramiv(_program, GL_GEOMETRY_OUTPUT_TYPE, &outputType);
		return outputType;
	}
#endif
}
