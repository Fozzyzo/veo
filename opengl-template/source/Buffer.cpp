/**
 * @file opengl-template/Buffer.cpp
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

#include <opengl-template/Buffer.h>

using namespace OpenGLTemplate;
using namespace std;

// Public

Buffer::Buffer(const unsigned int elementCount, const unsigned int elementSize, const BufferType& type,
	const BufferUsage& usage)
	: _buffer(0u),
	  _elementCount(elementCount),
	  _elementSize(elementSize),
	  _type(type)
{
	createBuffer();
	initialiseStorage(usage);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &_buffer);
	OGLT_ASSERT_GL();
}

void Buffer::apply() const
{
	apply(_buffer);
}

unsigned int Buffer::elementCount() const
{
	return _elementCount;
}

void Buffer::unapply() const
{
	apply(0u);
}

// Private

void Buffer::createBuffer()
{
	glGenBuffers(1, &_buffer);
	OGLT_ASSERT_GL();
}

void Buffer::initialiseStorage(const BufferUsage& usage) const
{
	apply();
	const unsigned int size = _elementSize * _elementCount;
	glBufferData(static_cast<GLenum>(_type), size, nullptr, static_cast<GLenum>(usage));
	OGLT_ASSERT_GL();
	unapply();
}

void Buffer::apply(const unsigned int buffer) const
{
	glBindBuffer(static_cast<GLenum>(_type), buffer);
	OGLT_ASSERT_GL();
}
