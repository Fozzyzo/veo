/**
 * @file opengl-template/Texture.h
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

#include <memory>
#include <string>
#include <vector>
#include <opengl-template/GL.h>

namespace OpenGLTemplate
{
	enum class TextureType
	{
		Texture2D = GL_TEXTURE_2D,
		TextureCubeMap = GL_TEXTURE_CUBE_MAP
	};

	enum class CubeSide
	{
		POSX = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		POSY = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		POSZ = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		NEGX = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		NEGY = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		NEGZ = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	enum class TextureFiltering
	{
		Linear = GL_LINEAR,
		LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR,
		LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
		Nearest = GL_NEAREST,
		NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
		NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST
	};

	class Texture final
	{
	public:

		~Texture();

		void apply() const;

		unsigned int height() const;

		void setMagnificationFilter(const TextureFiltering& value) const;
		
		void setMinificationFilter(const TextureFiltering& value) const;

		void unapply() const;

		unsigned int width() const;

		static std::shared_ptr<Texture> load(const TextureType& type, const std::string& filepath);

		void addCubeSides(CubeSide side, const std::string& filepath);

	private:

		unsigned int _texture;
		TextureType _type;
		unsigned int _width;
		unsigned int _height;

		std::vector<std::shared_ptr<Texture>> cubeSides;

		Texture(const TextureType& type, const unsigned int width, const unsigned int height,
			const std::vector<unsigned char>& data);

		Texture(const Texture& texture) = delete;
		Texture(Texture&& texture) = delete;
		
		void apply(const unsigned int texture) const;
		void setParameter(const GLenum parameterName, const GLenum value) const;
		void initialiseStorage(const std::vector<unsigned char>& data);
		
		Texture& operator =(const Texture& texture) = delete;
		Texture& operator =(Texture&& texture) = delete;
	};
}
