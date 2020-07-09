#pragma once
#include "defines.h"
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

struct ShaderSource
{
	std::string vertexShader;
	std::string fragmentShader;
	uint32 count;
};

class Shader
{
public:
	Shader(const char* fName);
	~Shader();

	void Bind() const;
	void Unbind() const;

	GLuint GetShaderID();

	void SetUniform(const std::string& name, const glm::vec3& data);
	void SetUniform(const std::string& name, const glm::vec4& data);
	void SetUniform(const std::string& name, const glm::mat3& data);
	void SetUniform(const std::string& name, const glm::mat4& data);

	void SetUniform(const int& location, const glm::vec3& data);
	void SetUniform(const int& location, const glm::vec4& data);
	void SetUniform(const int& location, const glm::mat3& data);
	void SetUniform(const int& location, const glm::mat4& data);

	int GetUniformLoc(const std::string& name);

private:
	GLuint Compile(std::string shaderSource, GLenum type);
	ShaderSource Parse(const char* fName);
	GLuint CreateShader(const char* fName);


	std::vector<std::string> uniformNames;
	std::unordered_map<std::string, int> uniformLocCache;
	GLuint shaderID;
};
