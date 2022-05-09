#pragma once
#include <string>
#include <GL\glew.h>
#include "transform.h"
#include "Camera.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace glm;

class Shader
{
public:
	Shader();

	void Bind(); //Set gpu to use our shaders
	void Update(const Transform& transform, const Camera& camera);
	void init(const string& vertFile, const string& fragFile); 
	void initGeo();


	string Shader::LoadShader(const string& fileName);
	void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage);
	GLuint Shader::CreateShader(const string& text, unsigned int type);

    ~Shader();

	// ------------------------------------------------------------------------
	void setBool(const string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			cerr << "Unable to load shader: " << name.c_str() << endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			cerr << "Unable to load shader: " << name.c_str() << endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setFloat(const string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setVec2(const string& name, const vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			cerr << "Unable to load shader: " << name.c_str() << endl;
			__debugbreak();
		}
	}
	void setVec2(const string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(shaderID, name.c_str()), x, y);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			cerr << "Unable to load shader: " << name.c_str() << endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setVec3(const string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			cerr << "Unable to load shader: " << name.c_str() << endl;
			__debugbreak();
		}
	}
	void setVec3(const string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(shaderID, name.c_str()), x, y, z);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			cerr << "Unable to load shader: " << name.c_str() << endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setVec4(const string& name, const vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			cerr << "Unable to load shader: " << name.c_str() << endl;
			__debugbreak();
		}
	}
	void setVec4(const string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(shaderID, name.c_str()), x, y, z, w);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			cerr << "Unable to load shader: " << name.c_str() << endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setMat2(const string& name, const mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			cerr << "Unable to load shader: " << name.c_str() << endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setMat3(const string& name, const mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			cerr << "Unable to load shader: " << name.c_str() << endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setMat4(const string& name, const mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			cerr << "Unable to load shader: " << name.c_str() << endl;
			__debugbreak();
		}
	}


protected:
private:
	static const unsigned int NUM_SHADERS = 2; // number of shaders

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint shaderID; // Track the shader program
	GLuint shaders[NUM_SHADERS]; //array of shaders
	GLuint shaders1[3];
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables
	GLuint textureHandler;
};
