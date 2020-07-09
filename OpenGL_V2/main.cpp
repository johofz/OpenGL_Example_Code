#include "defines.h"

#include <iostream>
#include <random>

#include <GL/glew.h>
#include <SDL.h>

#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Shape.h"
#include "Cube.h"
#include "FPSCamera.h"


void GLAPIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam)
{
	std::cout << "OpenGL Error: " << message << std::endl;
}


int main(int argc, char** argv)
{
	SDL_Window* window;
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	SDL_SetRelativeMouseMode(SDL_TRUE);

#ifdef _DEBUG
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	uint32 flags = SDL_WINDOW_OPENGL;
	uint32 screenWidth = 800;
	uint32 screenHeigth = 600;
#else
	uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP;
	uint32 screenWidth = 3000;
	uint32 screenHeigth = 2000;
#endif // DEBUG

	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeigth, flags);
	SDL_GLContext context = SDL_GL_CreateContext(window);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		std::cin.get();
		return -1;
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	GLCall(glEnable(GL_DEBUG_OUTPUT));
	GLCall(glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS));
	GLCall(glDebugMessageCallback(glDebugCallback, 0));

	Shader shader("LightingShader.shader");
	shader.Bind();

	glm::vec3 lightDirection = glm::vec3(-1.0f);
	glm::vec3 lightDiffuseColor = glm::vec3(1.0f);
	glm::vec3 lightSpecularColor = lightDiffuseColor;
	glm::vec3 lightAmbientColor = lightDiffuseColor * 0.2f;

	shader.SetUniform(shader.GetUniformLoc("u_directionalLight.direction"), lightDirection);
	shader.SetUniform(shader.GetUniformLoc("u_directionalLight.diffuse"), lightDiffuseColor);
	shader.SetUniform(shader.GetUniformLoc("u_directionalLight.specular"), lightSpecularColor);
	shader.SetUniform(shader.GetUniformLoc("u_directionalLight.ambient"), lightAmbientColor);
	
	FPSCamera camera(90.0f, (float32)screenWidth, (float32)screenHeigth);
	camera.Translate(glm::vec3(0.0f, 0.0f, 3.0f));

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 modelViewProjection;

	
	Cube cube(glm::vec3(0.0f), 1.0f);
	

	VertexArray vertexArray;
	VertexBuffer vertexBuffer(vertecies, numVerts);
	VertexBufferLayout layout;
	layout.Insert<float32>(numVerts);
	layout.Insert<float32>(numVerts);
	vertexArray.InsertBuffer(vertexBuffer, layout);

	IndexBuffer indexBuffer(indicies, numIndicies, sizeof(indicies[0]));

	GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glFrontFace(GL_CW));
	GLCall(glCullFace(GL_BACK));
	GLCall(glEnable(GL_DEPTH_TEST));

	uint64 clockFrequency = SDL_GetPerformanceFrequency();
	uint64 lastCounter = SDL_GetPerformanceCounter();
	float32 dt = 0.0f;
	float32 time = 0.0f;
	float32 step = dt * 50.0f;

	bool buttonW = false;
	bool buttonA = false;
	bool buttonS = false;
	bool buttonD = false;
	bool buttonSpace = false;
	bool buttonShift = false;


	bool closed = false;

	while (!closed) 
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			if (event.type == SDL_QUIT) 
			{
				closed = true;
			}
			else if (event.type == SDL_KEYDOWN) 
			{
				switch (event.key.keysym.sym) 
				{
				case SDLK_w:
					buttonW = true;
					break;
				case SDLK_a:
					buttonA = true;
					break;
				case SDLK_s:
					buttonS = true;
					break;
				case SDLK_d:
					buttonD = true;
					break;
				case SDLK_SPACE:
					buttonSpace = true;
					break;
				case SDLK_LSHIFT:
					buttonShift = true;
					break;
				case SDLK_ESCAPE:
					SDL_SetRelativeMouseMode(SDL_FALSE);
					break;
				}
			}
			else if (event.type == SDL_KEYUP) 
			{
				switch (event.key.keysym.sym) 
				{
				case SDLK_w:
					buttonW = false;
					break;
				case SDLK_a:
					buttonA = false;
					break;
				case SDLK_s:
					buttonS = false;
					break;
				case SDLK_d:
					buttonD = false;
					break;
				case SDLK_SPACE:
					buttonSpace = false;
					break;
				case SDLK_LSHIFT:
					buttonShift = false;
					break;
				}
			}
			else if (event.type == SDL_MOUSEMOTION) 
			{
				if (SDL_GetRelativeMouseMode())
				{
					camera.GetLineOfSight(event.motion.xrel, event.motion.yrel);
				}
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					SDL_SetRelativeMouseMode(SDL_TRUE);
				}
			}
		}

		if (buttonW)
		{
			camera.MoveFront(dt);
		}
		if (buttonS)
		{
			camera.MoveFront(-dt);
		}
		if (buttonD) 
		{
			camera.MoveSideways(dt);
		}
		if (buttonA)
		{
			camera.MoveSideways(-dt);
		}
		if (buttonSpace)
		{
			camera.MoveUp(dt);
		}
		if (buttonShift)
		{
			camera.MoveUp(-dt);
		}

		camera.Update();

		glm::mat4 modelView = camera.GetView() * model;
		glm::mat4 invModelView = glm::transpose(glm::inverse(modelView));

		modelViewProjection = camera.GetViewProjection() * model;

		shader.SetUniform("u_modelProjection", modelViewProjection);
		shader.SetUniform("u_modelView", modelView);
		shader.SetUniform("u_invModelView", invModelView);

		glm::vec4 transLightDirection = glm::transpose(glm::inverse(camera.GetView())) * glm::vec4(lightDirection, 1.0f);

		shader.SetUniform(shader.GetUniformLoc("u_directionalLight.direction"), glm::vec3(transLightDirection));

		GLCall(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT));

		vertexArray.Bind();
		indexBuffer.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.GetNumIndices(), GL_UNSIGNED_INT, 0));


		SDL_GL_SwapWindow(window);

		uint64 endCounter = SDL_GetPerformanceCounter();
		uint64 elapsed = endCounter - lastCounter;
		dt = ((float32)elapsed) / (float32)clockFrequency;
		uint32 FPS = (uint32)((float32)clockFrequency / (float32)elapsed);
		time += dt;
		lastCounter = endCounter;
	}

	return 0;
}