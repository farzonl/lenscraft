#include "Shader.hpp"

#include <Windows.h>

#include <GL/glew.h>
#include <GL/GL.h>

#include <fstream>

using std::string;
using std::ifstream;

Shader::Shader(void) : program(-1)
{

}

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) :
	program(-1)
{
	loadShaders(vertexShaderPath, fragmentShaderPath);
}

int Shader::getAttribLocation(const string& name)
{
	if (program == -1)
	{
		return -1;
	}

	glUseProgram(program);
	int attribute = glGetAttribLocation(program, name.c_str());
	glUseProgram(0);

	return attribute;
}

int Shader::getUniformLocation(const string& name)
{
	if (program == -1) 
	{
		return -1;
	}

	glUseProgram(program);
	int uniform = glGetUniformLocation(program, name.c_str());
	glUseProgram(0);

	return uniform;
}

void Shader::loadShaders(const string& vsPath, const string& fsPath)
{
	if (program != -1)
	{
		glDeleteProgram(program);
		program = -1;
	}

	ifstream vs(vsPath);
	if (!vs.good())
	{
		throw std::exception("Failed to open vertex shader");
	}

	ifstream fs(fsPath);
	if (!fs.good())
	{
		vs.close();
		throw std::exception("Failed to open fragment shader");
	}

	vs.seekg(0, std::ios::end);
	std::streamoff size = vs.tellg();
	vs.seekg(0, std::ios::beg);

	char* vertexSource = new char[size];
	memset(vertexSource, 0, size);
	vs.read(vertexSource, size);

	if (vs.bad())
	{
		throw std::exception("Error reading vertex shader source");
	}

	fs.seekg(0, std::ios::end);
	size = fs.tellg();
	fs.seekg(0, std::ios::beg);

	char* fragmentSource = new char[size];
	memset(fragmentSource, 0, size);
	fs.read(fragmentSource, size);

	if (fs.bad()) {
		throw std::exception("Error reading fragment shader source");
	}

	int vShaderId = createShader(GL_VERTEX_SHADER, vertexSource);
	int fShaderId = createShader(GL_FRAGMENT_SHADER, fragmentSource);

	program = createProgram(vShaderId, fShaderId);
}

int Shader::createShader(int shaderType, const char* source)
{
	// TODO check for errors
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE)
	{
		GLint infoLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
		char* log = new char[infoLength+1];
		glGetShaderInfoLog(shader, infoLength, NULL, log);

		string error = string(log);
		delete [] log;

		throw std::exception(error.c_str());
	}

	return shader;
}

int Shader::createProgram(int vShader, int fShader)
{
	// TODO check for errors
	int program = glCreateProgram();
	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);

	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE)
	{
		GLint infoLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);
		char* log = new char[infoLength+1];
		glGetProgramInfoLog(program, infoLength, NULL, log);

		string error = string(log);
		delete [] log;

		throw std::exception(error.c_str());
	}

	return program;
}

Shader::~Shader(void)
{
	if (program >= 0)
	{
		glDeleteProgram(program);
	}
}
