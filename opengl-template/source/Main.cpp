/**
 * @file opengl-template/Main.cpp
 *
 * OpenGL Template
 * Copyright 2015 Eetu 'Devenec' Oinasmaa
 *
 * OpenGL Template is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <cassert>
#include <iostream>
#include <SDL/SDL.h>
#include <opengl-template/Application.h>
#include <opengl-template/GL.h>

using namespace OpenGLTemplate;
using namespace std;

struct SDLContext final
{
	SDL_Window* window;
	SDL_GLContext graphicsContext;
};

static SDLContext initialiseSDL();
static void initialiseGLEW();
static void logGraphicsInfo();
static void loop(SDLContext sdlContext);
static void deinitialiseSDL(SDLContext sdlContext);

int main()
{
	SDLContext sdlContext = initialiseSDL();
	initialiseGLEW();
	logGraphicsInfo();
	loop(sdlContext);
	deinitialiseSDL(sdlContext);

	return 0;
}

static SDLContext initialiseSDL()
{
	const int result = SDL_Init(SDL_INIT_VIDEO);
	assert(result == 0);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,		  SDL_GL_CONTEXT_DEBUG_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,  SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,			  24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,		  1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,	  1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,	  Config::MULTISAMPLING_SAMPLES);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,			  8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,			  8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,			  8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,			  8);

	SDLContext sdlContext;

	sdlContext.window = SDL_CreateWindow("OpenGL Template", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

	assert(sdlContext.window != nullptr);
	sdlContext.graphicsContext = SDL_GL_CreateContext(sdlContext.window);
	assert(sdlContext.graphicsContext != nullptr);

	return sdlContext;
}

static void initialiseGLEW()
{
	glewExperimental = GL_TRUE; // Required for some OpenGL features to be available
	const GLenum glewResult = glewInit();
	assert(glewResult == GLEW_OK);
	glGetError(); // For some reason, an OpenGL error is emitted by calling glewInit()
}

static void logGraphicsInfo()
{
	int versionMajor = 0;
	int versionMinor = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
	glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
	cout << "[OpenGL Template] OpenGL context version: " << versionMajor << '.' << versionMinor << '\n';

	int parameter;
	glGetIntegerv(GL_SAMPLES, &parameter);
	cout << "[OpenGL Template] Multisampling samples: " << parameter << '\n';
}

static void loop(SDLContext sdlContext)
{
	bool exit = false;
	SDL_Event event;
	Application application;

	while(!exit)
	{
		while(SDL_PollEvent(&event) == 1)
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				exit = true;
		}

		application.update();
		SDL_GL_SwapWindow(sdlContext.window);
	}
}

static void deinitialiseSDL(SDLContext sdlContext)
{
	SDL_GL_DeleteContext(sdlContext.graphicsContext);
	SDL_DestroyWindow(sdlContext.window);
	SDL_Quit();
}
