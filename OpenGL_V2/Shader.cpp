#include "Shader.h"


Shader::Shader(const char* fName)
{
	shaderID = CreateShader(fName);

	for (std::string name : uniformNames)
	{
		GetUniformLoc(name);
	}
}

Shader::~Shader() 
{
	GLCall(glDeleteProgram(shaderID));
}

GLuint Shader::CreateShader(const char* fName)
{
	ShaderSource source = Parse(fName);
	
	GLCall(GLuint program = glCreateProgram());
	GLuint vertShader = Compile(source.vertexShader, GL_VERTEX_SHADER);
	GLuint fragShader = Compile(source.fragmentShader, GL_FRAGMENT_SHADER);

	GLCall(glAttachShader(program, vertShader));
	GLCall(glAttachShader(program, fragShader));
	GLCall(glLinkProgram(program));

	return program;
}

ShaderSource Shader::Parse(const char* fName)
{
	std::ifstream ifs(fName);
	
	int shaderType = -1;
	ShaderSource source;
	source.count = 0;
	std::stringstream ss[2];

	std::string currentLine;
	while (getline(ifs, currentLine))
	{
		if (currentLine.find("#shader") != std::string::npos)
		{ 
			if (currentLine.find("VERTEX") != std::string::npos)
			{
				shaderType = 0;
				source.count++;
			}
			else if (currentLine.find("FRAGMENT") != std::string::npos)
			{
				shaderType = 1;
				source.count++;
			}
		}
		else
		{	
			ASSERT(shaderType != -1);
			ss[shaderType] << currentLine << "\n";

			if (currentLine.find("uniform") != std::string::npos)
			{
				if (currentLine.find("u_") != std::string::npos)
				{
					std::size_t start = currentLine.find("u_");
					std::size_t length = currentLine.find(";") - start;
					std::string uniformName = currentLine.substr(start, length);
					uniformNames.push_back(uniformName);
				}
			}
		}
	}

	source.vertexShader = ss[0].str();
	source.fragmentShader = ss[1].str();

	return source;
}

GLuint Shader::Compile(std::string shaderSource, GLenum type)
{
	GLCall(GLuint id = glCreateShader(type));
	const char* src = shaderSource.c_str();
	GLCall(glShaderSource(id, 1, &src, 0));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result != GL_TRUE)
	{
		int length = 0;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = new char[length];
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Shader Compilation Error: " << message << std::endl;
		delete[] message;
		return 0;
	}
	return id;
}

void Shader::Bind() const
{
	GLCall(glUseProgram(shaderID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

GLuint Shader::GetShaderID()
{
	return this->shaderID;
}

void Shader::SetUniform(const std::string& name, const glm::vec3& data)
{
	int location = GetUniformLoc(name);
	ASSERT(location != -1);
	GLCall(glUniform3fv(location, 1, &data.x));
}

void Shader::SetUniform(const std::string& name, const glm::vec4& data)
{
	int location = GetUniformLoc(name);
	ASSERT(location != -1);
	GLCall(glUniform4fv(location, 1, &data.x));
}

void Shader::SetUniform(const std::string& name, const glm::mat3& data)
{
	int location = GetUniformLoc(name);
	ASSERT(location != -1);
	GLCall(glUniformMatrix3fv(location, 1, GL_FALSE, &data[0][0]));
}

void Shader::SetUniform(const std::string& name, const glm::mat4& data)
{
	int location = GetUniformLoc(name);
	ASSERT(location != -1);
	GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &data[0][0]));
}


void Shader::SetUniform(const int& location, const glm::vec3& data)
{
	ASSERT(location != -1);
	GLCall(glUniform3fv(location, 1, &data.x));
}

void Shader::SetUniform(const int& location, const glm::vec4& data)
{
	ASSERT(location != -1);
	GLCall(glUniform4fv(location, 1, &data.x));
}

void Shader::SetUniform(const int& location, const glm::mat3& data)
{
	ASSERT(location != -1);
	GLCall(glUniformMatrix3fv(location, 1, GL_FALSE, &data[0][0]));
}

void Shader::SetUniform(const int& location, const glm::mat4& data)
{
	ASSERT(location != -1);
	GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &data[0][0]));
}

int Shader::GetUniformLoc(const std::string& name)
{
	if (uniformLocCache.find(name) != uniformLocCache.end())
		return uniformLocCache[name];

	GLCall(int location = glGetUniformLocation(shaderID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: Uniform with name " << name << " has an ivalid initial location!" << std::endl;
	uniformLocCache[name] = location;
	return location;
}
