#pragma once
#include <cstdint>
#include <cstdlib>
#include <iostream>

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"


#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")


#define WINDOW_TITLE "OpenGL V2"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLCheckError(#x, __FILE__, __LINE__))

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float float32;
typedef double float64;

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
};


struct Material {
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 emissive;
	float32 shine;
};


static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLCheckError(const char* funtionName, const char* fileName, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "OpenGL Error [" << error << "]";
		std::cout << " in function " << funtionName;
		std::cout << " (file: " << fileName;
		std::cout << " , line: " << line << ")" << std::endl;

		return false;
	}
	return true;
}

