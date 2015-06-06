/**
 * @file opengl-template/Application.cpp
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
#include <vector>
#include <opengl-template/Application.h>
#include <opengl-template/EffectSource.h>
#include "lodepng.h"

using namespace glm;
using namespace OpenGLTemplate;
using namespace std;

// Public

Application::Application()
	: _worldTransformLocation(0u),
	  _meshRotation(0.0f)
{
	// Initialisation
	GLuint frameBuffer;
	GLuint renderBuffer;

	EffectSource effectSource;
	effectSource.load(ShaderType::Vertex, "assets/shaders/vertex.glsl");
	effectSource.load(ShaderType::Fragment, "assets/shaders/fragment.glsl");
	_skyBoxEffect.reset(new Effect(effectSource));

	effectSource.load(ShaderType::Vertex, "assets/shaders/vertexModel.glsl");
	effectSource.load(ShaderType::Fragment, "assets/shaders/fragmentModel.glsl");
	_modelEffect.reset(new Effect(effectSource));
	// Uniforms

	_skyBoxEffect->apply();

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	mat4 transform = perspective(radians(90.0f),
		static_cast<GLfloat>(Config::WINDOW_WIDTH) / Config::WINDOW_HEIGHT, 0.01f, 1000.0f);

	//skybox attributes
	GLint location = _skyBoxEffect->getUniformLocation("unifProjectionTransform");
	assert(location != -1);
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(transform));
	OGLT_ASSERT_GL();

	transform = translate(vec3(0.0f, 10.0f, -20.0f)) * rotate(radians(180.0f), vec3(0.0f, 0.0f, 1.0f));
	location = _skyBoxEffect->getUniformLocation("unifViewTransform");
	assert(location != -1);
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(transform));
	OGLT_ASSERT_GL();

	location = _skyBoxEffect->getUniformLocation("unifWorldTransform");
	assert(location != -1);
	_worldTransformLocation = location;
	glUniformMatrix4fv(_worldTransformLocation, 1, GL_FALSE, value_ptr(mat4()));
	OGLT_ASSERT_GL();

	location = _skyBoxEffect->getUniformLocation("cubeSampler");
	assert(location != -1);
	glUniform1i(location, 0);
	OGLT_ASSERT_GL();

	_skyBoxEffect->unapply();

	//model attributes
	
	_modelEffect->apply();
	location = _modelEffect->getUniformLocation("unifProjectionTransform");
	assert(location != -1);
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(transform));
	OGLT_ASSERT_GL();

	location = _modelEffect->getUniformLocation("unifViewTransform");
	assert(location != -1);
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(transform));
	OGLT_ASSERT_GL();

	location = _modelEffect->getUniformLocation("unifWorldTransform");
	assert(location != -1);
	_worldTransformLocation = location;
	glUniformMatrix4fv(_worldTransformLocation, 1, GL_FALSE, value_ptr(mat4()));
	OGLT_ASSERT_GL();

	location = _modelEffect->getUniformLocation("cubeSampler");
	assert(location != -1);
	glUniform1i(location, 0);
	OGLT_ASSERT_GL();

	_modelEffect->unapply();
	// Textures and models

	std::shared_ptr<Texture> skyCube = Texture::load(TextureType::TextureCubeMap, "assets/textures/posx.png");
	std::shared_ptr<Texture> balltex = Texture::load(TextureType::Texture2D, "assets/textures/ball.png");

	skyCube->addCubeSides(CubeSide::POSY, "assets/textures/posy.png");
	skyCube->addCubeSides(CubeSide::POSZ, "assets/textures/posz.png");
	skyCube->addCubeSides(CubeSide::NEGX, "assets/textures/negx.png");
	skyCube->addCubeSides(CubeSide::NEGY, "assets/textures/negy.png");
	skyCube->addCubeSides(CubeSide::NEGZ, "assets/textures/negz.png");
	
	// Add a model file to the path below
	_skybox = Mesh::load("assets/models/cubeSamble.dae", _skyBoxEffect, skyCube);
	_ball = Mesh::load("assets/models/ball.dae", _modelEffect, balltex);
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

Application::~Application()
{
	// Deinitialisation
}

void Application::update()
{
	// Updating and drawing

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_skyBoxEffect->apply();
	_meshRotation += 0.25f * (1.0f / 60.0f);
	const mat4 worldTransform = rotate(_meshRotation, vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(_worldTransformLocation, 1, GL_FALSE, value_ptr(worldTransform));
	
	glDisable(GL_CULL_FACE);
	_skybox->draw();

	glEnable(GL_CULL_FACE);
	_skyBoxEffect->unapply();

	_modelEffect->apply();
	_ball->draw();
	_modelEffect->unapply();
}
