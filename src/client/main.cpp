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

#include <iostream>

#include <Graphics.hpp>
#include <common.hpp>

using namespace NetPanzer;

int main()
{
	Graphics::Init("NetPanzer v" VERSION, 1280, 720);
	while (Graphics::IsWindowOpen())
	{
		Graphics::HandleEvents();
		Graphics::Clear();
		Graphics::Present();
	}
	Graphics::Quit();

	return 0;
}
