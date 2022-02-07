--[[

  ███╗   ██╗ ██████╗ ██████╗ ██████╗ ███████╗
  ████╗  ██║██╔════╝██╔═══██╗██╔══██╗██╔════╝
  ██╔██╗ ██║██║     ██║   ██║██████╔╝█████╗
  ██║╚██╗██║██║     ██║   ██║██╔══██╗██╔══╝
  ██║ ╚████║╚██████╗╚██████╔╝██║  ██║███████╗
  ╚═╝  ╚═══╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝

]]


group "Dependencies"
	require "vendor/pm5GLFW"
	require "vendor/pm5GLAD"
	require "vendor/pm5ImGui"
group ""

project "NCore"
	kind          "SharedLib"
	language      "C++"
	cppdialect    "C++17"
	staticruntime "off"

	targetdir "%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}"
	objdir    "%{wks.location}/build/%{cfg.buildcfg}/%{prj.name}"

	pchheader "ncpch.h"
	pchsource "src/ncpch.cpp"

	files
	{
    "src/**.h",
		"src/**.cpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"NOMINMAX",
		"NC_DYNAMIC_LINK"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		--"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		--"%{IncludeDir.yaml_cpp}",
		--"%{IncludeDir.imguizmo}",
		--"%{IncludeDir.vulkansdk}",
		"%{IncludeDir.json}",
	}

	links
	{
		"glfw",
		"glad",
		"imgui",
		--"yaml-cpp",
		"opengl32.lib"
	}

	postbuildcommands {
		"{MKDIR} %{wks.location}/bin/%{cfg.buildcfg}/Sandbox",
		"{MKDIR} %{wks.location}/bin/%{cfg.buildcfg}/NCEdit",
		"{COPY} %{cfg.buildtarget.relpath} %{wks.location}/bin/%{cfg.buildcfg}/Sandbox",
		"{COPY} %{cfg.buildtarget.relpath} %{wks.location}/bin/%{cfg.buildcfg}/NCEdit",
	}

	--filter "files:vendor/ImGuizmo/**.cpp"
	--flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"
		defines "NC_BUILD_DLL"

	filter "configurations:Debug"
		defines "NC_DEBUG"
		runtime "Debug"
		symbols "on"

		postbuildcommands
		{
		-- "{COPYDIR} \"%{LibraryDir.VulkanSDK_DebugDLL}\" \"%{cfg.targetdir}\""
		}

	filter "configurations:Release"
		defines "NC_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "NC_DIST"
		runtime "Release"
		optimize "on"