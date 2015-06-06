/**
 * @file opengl-template/EffectSource.cpp
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
#include <fstream>
#include <iostream>
#include <opengl-template/EffectSource.h>

using namespace OpenGLTemplate;
using namespace std;

// Public

bool EffectSource::hasGeometryShaderSource() const
{
	return _sources[static_cast<int>(ShaderType::Geometry)].length() != 0u;
}

void EffectSource::load(const ShaderType& shaderType, const string& filepath)
{
	_sources[static_cast<int>(shaderType)] = loadFile(filepath);
	cout << "[EffectSource] Loaded shader source '" << filepath << "\'\n";
}

// Private

string EffectSource::loadFile(const string& filepath) const
{
	ifstream fileStream(filepath, ios::binary);
	assert(fileStream.is_open());
	string source;
	fileStream.seekg(0u, ios::end);
	source.reserve(static_cast<unsigned int>(fileStream.tellg()));
	fileStream.seekg(0u, ios::beg);
	source.assign(istreambuf_iterator<char>(fileStream), istreambuf_iterator<char>());

	return source;
}
