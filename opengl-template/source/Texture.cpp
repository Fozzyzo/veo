/**
 * @file opengl-template/Texture.cpp
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
#include <utility>
#include <lodepng.h>
#include <opengl-template/Texture.h>

using namespace OpenGLTemplate;
using namespace std;

// Public

Texture::~Texture()
{
	glDeleteTextures(1, &_texture);
	OGLT_ASSERT_GL();
}

void Texture::apply() const
{
	apply(_texture);
}

unsigned int Texture::height() const
{
	return _height;
}

void Texture::setMagnificationFilter(const TextureFiltering& value) const
{
	apply();
	setParameter(GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(value));
	unapply();
}
		
void Texture::setMinificationFilter(const TextureFiltering& value) const
{
	apply();
	setParameter(GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(value));
	unapply();
}

void Texture::unapply() const
{
	apply(0u);
}

unsigned int Texture::width() const
{
	return _width;
}

// Static

shared_ptr<Texture> Texture::load(const TextureType& type, const string& filepath)
{
	using ImageData = vector<unsigned char>;

	unsigned int width;
	unsigned int height;
	ImageData data;
	const unsigned int result = lodepng::decode(data, width, height, filepath);
	assert(result == 0u);
	
	ImageData inverseData;
	inverseData.reserve(data.size());
	const unsigned int lineByteCount = 4 * width;

	for(ImageData::const_reverse_iterator i = data.rbegin(), end = data.rend(); i != end; i += lineByteCount)
		inverseData.insert(inverseData.end(), (i + lineByteCount).base(), i.base());

	Texture* texture = new Texture(type, width, height, inverseData);
	return shared_ptr<Texture>(texture);
}

// Private

Texture::Texture(const TextureType& type, const unsigned int width, const unsigned int height,
	const vector<unsigned char>& data)
	: _texture(0u),
	  _type(type),
	  _width(width),
	  _height(height)
{
	glGenTextures(1, &_texture);
	OGLT_ASSERT_GL();
	initialiseStorage(data);
}

void Texture::apply(const unsigned int texture) const
{
	glBindTexture(static_cast<GLenum>(_type), texture);
	OGLT_ASSERT_GL();
}

void Texture::setParameter(const GLenum parameterName, const GLenum value) const
{
	glTexParameteri(static_cast<GLenum>(_type), parameterName, value);
	OGLT_ASSERT_GL();
}

void Texture::initialiseStorage(const vector<unsigned char>& data)
{
	apply();

	if (_type == TextureType::Texture2D)
	{
		glTexImage2D(static_cast<GLenum>(_type), 0, GL_COMPRESSED_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			data.data());
	}

	else if (_type == TextureType::TextureCubeMap)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_COMPRESSED_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			data.data());
	}

	OGLT_ASSERT_GL();
	unapply();

	setMagnificationFilter(TextureFiltering::Linear);
	setMinificationFilter(TextureFiltering::Linear);
}

void Texture::addCubeSides(CubeSide side, const std::string& filepath)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);
	using ImageData = vector<unsigned char>;

	unsigned int width;
	unsigned int height;
	ImageData data;
	const unsigned int result = lodepng::decode(data, width, height, filepath);
	assert(result == 0u);

	ImageData inverseData;
	inverseData.reserve(data.size());
	const unsigned int lineByteCount = 4 * width;

	for (ImageData::const_reverse_iterator i = data.rbegin(), end = data.rend(); i != end; i += lineByteCount)
		inverseData.insert(inverseData.end(), (i + lineByteCount).base(), i.base());

	glTexImage2D(static_cast<GLenum>(side), 0, GL_COMPRESSED_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		inverseData.data());
}


