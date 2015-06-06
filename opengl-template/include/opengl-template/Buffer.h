/**
 * @file opengl-template/Buffer.h
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

#pragma once

#include <cassert>
#include <vector>
#include <opengl-template/GL.h>

namespace OpenGLTemplate
{
	enum class BufferType
	{
		Index  = GL_ELEMENT_ARRAY_BUFFER,
		Vertex = GL_ARRAY_BUFFER
	};

	enum class BufferUsage
	{
		DrawDynamic = GL_DYNAMIC_DRAW,
		DrawStatic	= GL_STATIC_DRAW,
		DrawStream	= GL_STREAM_DRAW
	};

	class Buffer final
	{
	public:

		Buffer(const unsigned int elementCount, const unsigned int elementSize, const BufferType& type,
			const BufferUsage& usage);

		~Buffer();

		void apply() const;

		unsigned int elementCount() const;

		template<typename T>
		void setData(const std::vector<T>& data, const unsigned int elementOffset = 0u);

		void unapply() const;

	private:

		unsigned int _buffer;
		unsigned int _elementCount;
		unsigned int _elementSize;
		BufferType _type;

		Buffer(const Buffer& buffer) = delete;
		Buffer(Buffer&& buffer) = delete;

		void createBuffer();
		void initialiseStorage(const BufferUsage& usage) const;
		void apply(const unsigned int buffer) const;
		
		Buffer& operator =(const Buffer& buffer) = delete;
		Buffer& operator =(Buffer&& buffer) = delete;
	};

	template<typename T>
	void Buffer::setData(const std::vector<T>& data, const unsigned int elementOffset)
	{
		const unsigned int dataSize = sizeof(T) * data.size();
		const unsigned int offset = sizeof(T) * elementOffset;
		assert(offset + dataSize <= _elementSize * _elementCount);

		apply();
		glBufferSubData(static_cast<GLenum>(_type), offset, dataSize, data.data());
		OGLT_ASSERT_GL();
		unapply();
	}
}
