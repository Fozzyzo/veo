/**
 * @file opengl-template/Effect.cpp
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

#include <array>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <opengl-template/Effect.h>

using namespace OpenGLTemplate;
using namespace std;

// External

static const array<GLenum, 3u> SHADER_TYPES =
{
	GL_GEOMETRY_SHADER,
	GL_FRAGMENT_SHADER,
	GL_VERTEX_SHADER
};

// Public

Effect::Effect(const EffectSource& source)
	: _program(0u),
	  _vertexShader(0u),
	  _geometryShader(0u),
	  _fragmentShader(0u)
{
	createProgram();
	_vertexShader = createAndCompileShader(ShaderType::Vertex, source);
	_fragmentShader = createAndCompileShader(ShaderType::Fragment, source);

	if(source.hasGeometryShaderSource())
		_geometryShader = createAndCompileShader(ShaderType::Geometry, source);

	linkProgram();
}

Effect::~Effect()
{
	destroyShader(_geometryShader);
	destroyShader(_fragmentShader);
	destroyShader(_vertexShader);
	destroyProgram();
}

void Effect::apply() const
{
	apply(_program);
}

int Effect::getAttributeLocation(const std::string& attributeName) const
{
	const int location = glGetAttribLocation(_program, attributeName.c_str());
	OGLT_ASSERT_GL();

	return location;
}

int Effect::getUniformLocation(const std::string& uniformName) const
{
	const int location = glGetUniformLocation(_program, uniformName.c_str());
	OGLT_ASSERT_GL();

	return location;
}

void Effect::unapply() const
{
	apply(0u);
}

// Private

void Effect::createProgram()
{
	_program = glCreateProgram();
	assert(_program != 0u);
}

unsigned int Effect::createAndCompileShader(const ShaderType& type, const EffectSource& source) const
{
	const int sourceIndex = static_cast<int>(type);
	const unsigned int shader = createShader(SHADER_TYPES[sourceIndex]);
	compileShader(shader, source._sources[sourceIndex]);
	attachShader(shader);

	return shader;
}

void Effect::linkProgram() const
{
	glLinkProgram(_program);
	OGLT_ASSERT_GL();
	assertProgramLinkage();
}

void Effect::destroyShader(const unsigned int shader) const
{
	glDeleteShader(shader);
	OGLT_ASSERT_GL();
}

void Effect::destroyProgram() const
{
	glDeleteProgram(_program);
	OGLT_ASSERT_GL();
}

void Effect::apply(const unsigned int program) const
{
	glUseProgram(program);
	OGLT_ASSERT_GL();
}

unsigned int Effect::createShader(const GLenum type) const
{
	const unsigned int shader = glCreateShader(type);
	assert(shader != 0u);

	return shader;
}

void Effect::compileShader(const unsigned int shader, const string& source) const
{
	const char* sourceString = source.c_str();
	glShaderSource(shader, 1, &sourceString, nullptr);
	OGLT_ASSERT_GL();
	glCompileShader(shader);
	OGLT_ASSERT_GL();
	assertShaderCompilation(shader);
}

void Effect::attachShader(const unsigned int shader) const
{
	glAttachShader(_program, shader);
	OGLT_ASSERT_GL();
}

void Effect::assertShaderCompilation(const unsigned int shader) const
{
	int parameter;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &parameter);
	OGLT_ASSERT_GL();

	if(parameter == GL_FALSE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &parameter);
		OGLT_ASSERT_GL();

		if(parameter > 0)
		{
			vector<char> buffer(parameter);
			glGetShaderInfoLog(shader, buffer.size(), nullptr, buffer.data());
			OGLT_ASSERT_GL();
			cout << "[Effect] Failed to compile a shader: " << buffer.data() << endl;
			abort();
		}
	}
}

void Effect::assertProgramLinkage() const
{
	int parameter;
	glGetProgramiv(_program, GL_LINK_STATUS, &parameter);
	OGLT_ASSERT_GL();

	if(parameter == GL_FALSE)
	{
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &parameter);
		OGLT_ASSERT_GL();

		if(parameter > 0)
		{
			vector<char> buffer(parameter);
			glGetProgramInfoLog(_program, buffer.size(), nullptr, buffer.data());
			OGLT_ASSERT_GL();
			cout << "[Effect] Failed to link the program: " << buffer.data() << endl;
			abort();
		}
	}
}
