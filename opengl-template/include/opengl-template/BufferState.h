/**
 * @file opengl-template/BufferState.h
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

#include <vector>
#include <opengl-template/Buffer.h>
#include <opengl-template/GL.h>
#include <opengl-template/GLM.h>

namespace OpenGLTemplate
{
	enum class VertexElementType
	{
		Float32			   = GL_FLOAT,
		Float64			   = GL_DOUBLE,
		Int2_10_10_10_Rev  = GL_INT_2_10_10_10_REV,
		Int8			   = GL_BYTE,
		Int16			   = GL_SHORT,
		Int32			   = GL_INT,
		Uint2_10_10_10_Rev = GL_UNSIGNED_INT_2_10_10_10_REV,
		Uint8			   = GL_UNSIGNED_BYTE,
		Uint16			   = GL_UNSIGNED_SHORT,
		Uint32			   = GL_UNSIGNED_INT
	};

	struct VertexElement final
	{
		unsigned int index;
		unsigned int size;
		VertexElementType type;
		GLboolean isNormalised;
	};

	using VertexFormat = std::vector<VertexElement>;

	class BufferState final
	{
	public:

		BufferState();

		~BufferState();

		void apply() const;

		void initialise(const VertexFormat& vertexFormat, Buffer* vertexBuffer, Buffer* indexBuffer = nullptr);

		void setVertexAttribute(const unsigned int index, const float value) const;

		void setVertexAttribute(const unsigned int index, const glm::vec2& value) const;

		void setVertexAttribute(const unsigned int index, const glm::vec3& value) const;

		void setVertexAttribute(const unsigned int index, const glm::vec4& value) const;

		void unapply() const;

	private:

		unsigned int _vertexArray;
		bool _isInitialised;
		
		BufferState(const BufferState& drawState) = delete;
		BufferState(BufferState&& drawState) = delete;

		void createVertexArray();
		void initialiseVertexArray(const VertexFormat& vertexFormat);
		void apply(const unsigned int vertexArray) const;
		
		BufferState& operator =(const BufferState& drawState) = delete;
		BufferState& operator =(BufferState&& drawState) = delete;
		
		static unsigned int calculateVertexSize(const VertexFormat& vertexFormat);
		static unsigned int getVertexElementTypeSize(const VertexElementType type);
	};
}
