/**
 * @file opengl-template/GL.h
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

#include <iostream>
#include <cstdlib>
#include <GL/glew.h>

#define OGLT_ASSERT_GL() \
	OpenGLTemplate::assertGLError(__FILE__, __LINE__);

namespace OpenGLTemplate
{
	inline void assertGLError(const char* file, const unsigned int line)
	{
		const GLenum error = glGetError();

		if(error != GL_NO_ERROR)
		{
			std::cout << "OpenGL assertion failed @ " << file << " on line " << line << " with error " << std::hex <<
				error << std::dec << std::endl;

			std::abort();
		}
	}
}
