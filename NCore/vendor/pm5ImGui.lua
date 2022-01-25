project "imgui"
kind "StaticLib"
language "C++"

location "imgui"
targetdir "%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}"
objdir    "%{wks.location}/build/%{cfg.buildcfg}/%{prj.name}"

defines {
    "IMGUI_IMPL_OPENGL_LOADER_GLAD"
}

includedirs {
    "%{prj.location}"
}

files {
    "%{prj.location}/*.h",
    "%{prj.location}/*.cpp",
}

filter "system:windows"
    systemversion "latest"
    cppdialect "C++17"
    staticruntime "On"

filter "system:linux"
    pic "On"
    systemversion "latest"
    cppdialect "C++17"
    staticruntime "On"

filter "configurations:Debug"
    runtime "Debug"
    symbols "on"

filter "configurations:Release"
    runtime "Release"
    optimize "on"