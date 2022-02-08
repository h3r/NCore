--[[

	███████╗ █████╗ ███╗   ██╗██████╗ ██████╗  ██████╗ ██╗  ██╗
	██╔════╝██╔══██╗████╗  ██║██╔══██╗██╔══██╗██╔═══██╗╚██╗██╔╝
	███████╗███████║██╔██╗ ██║██║  ██║██████╔╝██║   ██║ ╚███╔╝
	╚════██║██╔══██║██║╚██╗██║██║  ██║██╔══██╗██║   ██║ ██╔██╗
	███████║██║  ██║██║ ╚████║██████╔╝██████╔╝╚██████╔╝██╔╝ ██╗
	╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝

]]

project "Sandbox"
	kind          "ConsoleApp"
	language      "C++"
	cppdialect    "C++17"
	staticruntime "off"

	targetdir "%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}"
	objdir    "%{wks.location}/build/%{cfg.buildcfg}/%{prj.name}"

	files
	{
    "src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
		"src",
		"%{wks.location}/NCore/vendor/spdlog/include",
		"%{wks.location}/NCore/src",
		"%{wks.location}/NCore/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.json}",
		"%{IncludeDir.imgui}",

	}

	links
	{
		"NCore"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "NC_DEBUG"
		runtime "Debug"
		symbols "on"
		
		postbuildcommands
		{
			"{COPYDIR} \"%{LibraryDir.vulkansdk_debugdll}\" \"%{cfg.targetdir}\""
		}

	filter "configurations:Release"
		defines "NC_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "NC_DIST"
		runtime "Release"
		optimize "on"
