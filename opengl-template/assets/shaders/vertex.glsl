/**
 * @file assets/shaders/vertex.glsl
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

#version 330

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec2 inTextureCoords;
layout(location = 2) in vec3 inNormal;

uniform mat4 unifProjectionTransform;
uniform mat4 unifViewTransform;
uniform mat4 unifWorldTransform;

out vec3 textureCoords;

void main()
{
	textureCoords = vec3(inPosition.xyz);

	mat4 viewWorldTransform = unifViewTransform * unifWorldTransform;
	vec4 position = viewWorldTransform * inPosition;
	
	gl_Position = unifProjectionTransform * position;
}
