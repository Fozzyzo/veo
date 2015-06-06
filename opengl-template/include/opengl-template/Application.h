/**
 * @file opengl-template/Application.h
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
#include <opengl-template/Buffer.h>
#include <opengl-template/BufferState.h>
#include <opengl-template/Effect.h>
#include <opengl-template/GL.h>
#include <opengl-template/GLM.h>
#include <opengl-template/Mesh.h>
#include <opengl-template/Texture.h>

namespace Config
{
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;
	const int MULTISAMPLING_SAMPLES = 16; // 0 = disabled
}

namespace OpenGLTemplate
{
	class Application
	{
	public:

		Application();

		~Application();

		void update();

	private:

		std::shared_ptr<Effect> _skyBoxEffect;
		std::shared_ptr<Effect> _modelEffect;
		std::shared_ptr<Mesh> _skybox;
		std::shared_ptr<Mesh> _ball;
		float _meshRotation;
		unsigned int _worldTransformLocation;
		unsigned int _modelLocation;

		Application(const Application& application) = delete;
		Application(Application&& application) = delete;
		
		Application& operator =(const Application& application) = delete;
		Application& operator =(Application&& application) = delete;
	};
}
