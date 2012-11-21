#pragma once

#include <string>

class Shader
{
public:
	Shader(void);
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~Shader(void);

public:
	void loadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	int getProgram() { return program; }

	int getAttribLocation(const std::string& name);
	int getUniformLocation(const std::string& name);

private:
	int createShader(int shaderType, const char* source);
	int createProgram(int vShader, int fShader);

private:
	int program;
};

