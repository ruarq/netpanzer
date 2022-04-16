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

#ifndef NP_PLATFORM_HPP
#define NP_PLATFORM_HPP

#if defined(__APPLE__)
	#define NP_OS_MACOSX
#elif defined(__linux__)
	#define NP_OS_LINUX
#elif defined(_WIN32)
	#define NP_OS_WINDOWS
#else
	#error "Your platform is not supported."
#endif

#endif
