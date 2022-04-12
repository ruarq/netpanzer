workspace "netpanzer"
	configurations { "debug", "release" }

-- Global settings
language "C++"
cppdialect "C++17"

filter { "configurations:debug" }
    symbols "On"
    defines "DEBUG"

filter { "configurations:release" }
    optimize "Speed"

project "np_core"
	kind "StaticLib"
	files { "src/core/**.hpp", "src/core/**.cpp" }

project "np_client"
    kind "ConsoleApp"

    files { "src/client/**.hpp", "src/client/**.cpp" }

    includedirs { "src/core" }
    links { "np_core" }

project "np_server"
    kind "ConsoleApp"

    files { "src/server/**.hpp", "src/server/**.cpp" }

    includedirs { "src/core" }
    links { "np_core" }
