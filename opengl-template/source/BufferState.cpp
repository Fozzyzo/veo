/**
 * @file opengl-template/BufferState.cpp
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
#include <opengl-template/BufferState.h>

using namespace glm;
using namespace OpenGLTemplate;

BufferState::BufferState()
	: _vertexArray(0u),
	  _isInitialised(false) { }

BufferState::~BufferState()
{
	glDeleteVertexArrays(1, &_vertexArray);
	OGLT_ASSERT_GL();
}

void BufferState::apply() const
{
	assert(_isInitialised);
	apply(_vertexArray);
}

void BufferState::initialise(const VertexFormat& vertexFormat, Buffer* vertexBuffer, Buffer* indexBuffer)
{
	createVertexArray();
	_isInitialised = true;
	vertexBuffer->apply();
	apply();

	if(indexBuffer != nullptr)
		indexBuffer->apply();

	initialiseVertexArray(vertexFormat);

	unapply();
	vertexBuffer->unapply();
}

void BufferState::setVertexAttribute(const unsigned int index, const float value) const
{
	assert(_isInitialised);
	apply();
	glVertexAttrib1f(index, value);
	OGLT_ASSERT_GL();
	unapply();
}

void BufferState::setVertexAttribute(const unsigned int index, const vec2& value) const
{
	assert(_isInitialised);
	apply();
	glVertexAttrib2f(index, value.x, value.y);
	OGLT_ASSERT_GL();
	unapply();
}

void BufferState::setVertexAttribute(const unsigned int index, const vec3& value) const
{
	assert(_isInitialised);
	apply();
	glVertexAttrib3f(index, value.x, value.y, value.z);
	OGLT_ASSERT_GL();
	unapply();
}

void BufferState::setVertexAttribute(const unsigned int index, const vec4& value) const
{
	assert(_isInitialised);
	apply();
	glVertexAttrib4f(index, value.x, value.y, value.z, value.w);
	OGLT_ASSERT_GL();
	unapply();
}

void BufferState::unapply() const
{
	assert(_isInitialised);
	apply(0u);
}

// Private

void BufferState::createVertexArray()
{
	glGenVertexArrays(1, &_vertexArray);
	OGLT_ASSERT_GL();
}

void BufferState::initialiseVertexArray(const VertexFormat& vertexFormat)
{
	const unsigned int vertexSize = calculateVertexSize(vertexFormat);
	unsigned int offset = 0u;

	for(VertexFormat::const_iterator i = vertexFormat.begin(), end = vertexFormat.end(); i != end; ++i)
	{
		glEnableVertexAttribArray(i->index);

		glVertexAttribPointer(i->index, i->size, static_cast<GLenum>(i->type), i->isNormalised, vertexSize,
			reinterpret_cast<void*>(offset));

		offset += i->size * getVertexElementTypeSize(i->type);
	}
}

void BufferState::apply(const unsigned int vertexArray) const
{
	glBindVertexArray(vertexArray);
	OGLT_ASSERT_GL();
}

// Static

unsigned int BufferState::calculateVertexSize(const VertexFormat& vertexFormat)
{
	unsigned int size = 0u;

	if(vertexFormat.size() > 1u)
	{
		for(VertexFormat::const_iterator i = vertexFormat.begin(), end = vertexFormat.end(); i != end; ++i)
			size += i->size * getVertexElementTypeSize(i->type);
	}

	return size;
}

unsigned int BufferState::getVertexElementTypeSize(const VertexElementType type)
{
	switch(type)
	{
		case VertexElementType::Int8:
		case VertexElementType::Uint8:
			return 1u;

		case VertexElementType::Int16:
		case VertexElementType::Uint16:
			return 2u;
			
		case VertexElementType::Float32:
		case VertexElementType::Int32:
		case VertexElementType::Int2_10_10_10_Rev:
		case VertexElementType::Uint32:
		case VertexElementType::Uint2_10_10_10_Rev:
			return 4u;
			
		case VertexElementType::Float64:
			return 8u;
			
		default:
			assert(false);
			return 0u;
	}
}
