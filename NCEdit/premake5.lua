--[[

	███╗   ██╗ ██████╗███████╗██████╗ ██╗████████╗
	████╗  ██║██╔════╝██╔════╝██╔══██╗██║╚══██╔══╝
	██╔██╗ ██║██║     █████╗  ██║  ██║██║   ██║
	██║╚██╗██║██║     ██╔══╝  ██║  ██║██║   ██║
	██║ ╚████║╚██████╗███████╗██████╔╝██║   ██║
	╚═╝  ╚═══╝ ╚═════╝╚══════╝╚═════╝ ╚═╝   ╚═╝

]]

project "NCEdit"
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
		"%{wks.location}/NCore/vendor/spdlog/include",
		"%{wks.location}/NCore/src",
		"%{wks.location}/NCore/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.imgui}",
		--"%{IncludeDir.imguizmo}",
		"%{IncludeDir.json}",
	}

	links
	{
		"NCore"
	}

	--filter "files:vendor/ImGuizmo/**.cpp"
	--flags { "NoPCH" }

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

		links
		{
			--"%{Library.ShaderC_Debug}",
			--"%{Library.SPIRV_Cross_Debug}",
			--"%{Library.SPIRV_Cross_GLSL_Debug}"
		}

	filter "configurations:Release"
		defines "NC_RELEASE"
		runtime "Release"
		optimize "on"

		links
		{
			--"%{Library.ShaderC_Release}",
			--"%{Library.SPIRV_Cross_Release}",
			--"%{Library.SPIRV_Cross_GLSL_Release}"
		}

	filter "configurations:Dist"
		defines "NC_DIST"
		runtime "Release"
		optimize "on"

		links
		{
			--"%{Library.ShaderC_Release}",
			--"%{Library.SPIRV_Cross_Release}",
			--"%{Library.SPIRV_Cross_GLSL_Release}"
		}
