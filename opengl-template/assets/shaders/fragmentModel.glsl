/**
 * @file assets/shaders/fragment.glsl
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

in vec3 textureCoords;
in vec3 eyeNormal;
in vec3 eyePosition;

uniform unifViewTransform;
uniform samplerCube cubeSampler;

out vec4 outColour;

void main()
{
	vec3 normal = normalize(eyeNormal);
	vec3 position = normalize(eyePosition);

	vec3 reflection = reflect(position, normal);

	reflection = vec3(inverse(unifViewTransform) * vec4(reflection, 1.0f));
	outColour = texture(cubeSampler, reflection); 
}
