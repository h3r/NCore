
-- Project Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["stb_image"] = "%{wks.location}/NCore/vendor/stb_image"
IncludeDir["yaml_cpp"] = "%{wks.location}/NCore/vendor/yaml-cpp/include"
IncludeDir["glfw"] = "%{wks.location}/NCore/vendor/glfw/include"
IncludeDir["glad"] = "%{wks.location}/NCore/vendor/glad/include"
IncludeDir["imgui"] = "%{wks.location}/NCore/vendor/imgui"
IncludeDir["imguizmo"] = "%{wks.location}/NCore/vendor/imguizmo"
IncludeDir["glm"] = "%{wks.location}/NCore/vendor/glm"
IncludeDir["entt"] = "%{wks.location}/NCore/vendor/entt/single_include"
IncludeDir["shaderc"] = "%{wks.location}/NCore/vendor/shaderc/include"
IncludeDir["spirv_cross"] = "%{wks.location}/NCore/vendor/spirv_cross"
IncludeDir["json"] = "%{wks.location}/NCore/vendor/nlohmann/include"
IncludeDir["vulkansdk"] = "%{VULKAN_SDK}/Include"


LibraryDir = {}

LibraryDir["vulkansdk"] = "%{VULKAN_SDK}/Lib"
LibraryDir["vulkansdk_debug"] = "%{wks.location}/NCore/vendor/vulkansdk/Lib"
LibraryDir["vulkansdk_debugdll"] = "%{wks.location}/NCore/vendor/vulkansdk/Bin"

Library = {}
Library["vulkan"] = "%{LibraryDir.vulkansdk}/vulkan-1.lib"
Library["vulkanutils"] = "%{LibraryDir.vulkansdk}/VkLayer_utils.lib"

Library["shaderc_debug"] = "%{LibraryDir.vulkansdk_debug}/shaderc_sharedd.lib"
Library["spirv_cross_debug"] = "%{LibraryDir.vulkansdk_debug}/spirv-cross-cored.lib"
Library["spirv_cross_glsl_debug"] = "%{LibraryDir.vulkansdk_debug}/spirv-cross-glsld.lib"
Library["spirv_tools_debug"] = "%{LibraryDir.vulkansdk_debug}/SPIRV-Toolsd.lib"

Library["shaderc_release"] = "%{LibraryDir.vulkansdk}/shaderc_shared.lib"
Library["spirv_cross_release"] = "%{LibraryDir.vulkansdk}/spirv-cross-core.lib"
Library["spirv_cross_glsl_release"] = "%{LibraryDir.vulkansdk}/spirv-cross-glsl.lib"