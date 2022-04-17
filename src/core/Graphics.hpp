// Copyright (C) 2022  ruarq <https://github.com/ruarq>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SDL.h>

#include "common.hpp"

namespace NetPanzer
{

class Graphics
{
public:
	static void Init(const char *windowTitle, int width, int height);
	static void Quit();

	NP_NODISCARD static bool IsWindowOpen();
	static void CloseWindow();

	static void Clear();
	static void Present();

	static void HandleEvents();

public:
	static SDL_Window *window;
	static SDL_Renderer *renderer;
	static bool isWindowOpen;
};

}

#endif
