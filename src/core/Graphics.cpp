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

#include "Graphics.hpp"

namespace NetPanzer
{

SDL_Window *Graphics::window = nullptr;
SDL_Renderer *Graphics::renderer = nullptr;

void Graphics::Init(const char *windowTitle, const int width, const int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		// TODO(ruarq): Something went wrong
	}

	window = SDL_CreateWindow(windowTitle,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_SHOWN);
	if (!window)
	{
		// TODO(ruarq): Something went wrong
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		// TODO(ruarq): Something went wrong
	}
}

void Graphics::Quit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	renderer = nullptr;
	window = nullptr;
}

}
