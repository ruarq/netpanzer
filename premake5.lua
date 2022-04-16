function sh(cmd)
	local handle = io.popen(cmd)
	local result = handle:read("*a")
	handle:close()
	return result
end

function add_package(pkg)
	if (pkg == "SDL2") then
		buildoptions { sh("sdl2-config --cflags") }
		linkoptions { sh("sdl2-config --libs") }
	else
		buildoptions { sh("pkg-config " .. pkg .. " --cflags") }
		linkoptions { sh("pkg-config " .. pkg ..  " --libs") }
	end
end

---------------------------------------------------------------

workspace "netpanzer"
	configurations { "debug", "release" }

-- Global settings --------------------------------------------

language "C++"
cppdialect "C++17"

defines { "VERSION=\"0.0.1\"" }

filter { "configurations:debug" }
	symbols "On"
	defines "DEBUG"

filter { "configurations:release" }
	optimize "Speed"

filter {}

---------------------------------------------------------------

project "np_core"
	kind "StaticLib"
	files { "src/core/**.hpp", "src/core/**.cpp" }

project "np_client"
	kind "ConsoleApp"

	files { "src/client/**.hpp", "src/client/**.cpp" }

	includedirs { "src/core" }
	links { "np_core" }

	add_package("SDL2")

project "np_server"
	kind "ConsoleApp"

	files { "src/server/**.hpp", "src/server/**.cpp" }

	includedirs { "src/core" }
	links { "np_core" }
