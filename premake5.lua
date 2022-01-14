workspace "RayX"
	architecture "x86"
	startproject "RayXViewer"

	configurations{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "ogl/vendor/glfw/include"
IncludeDir["Glad"] = "ogl/vendor/Glad/include"
IncludeDir["glm"] = "ogl/vendor/glm"
IncludeDir["ImGui"] = "ogl/vendor/imgui"
IncludeDir["ImPlot"] = "ogl/vendor/implot"

include "ogl/vendor/GLFW"
include "ogl/vendor/Glad"
include "ogl/vendor/imgui"
include "ogl/vendor/implot"

project "RayXCore"
	location "RayXCore"
	kind "StaticLib"
	cppdialect "C++20"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .."/")
	objdir ("bin/intermediates/" .. outputdir .."/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp"
	}

	includedirs {
		"%{prj.name}/include"
	}


	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "RAYX_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "RAYX_RELEASE"
		optimize "on"



project "RayXViewer"
	location "RayXViewer"
	kind "ConsoleApp"
	cppdialect "C++17"
	language "C++"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .."/")
	objdir ("bin/intermediates/" .. outputdir .."/%{prj.name}")
	
	
	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp",
		"./ogl/ogl-core/**.c",
		"./ogl/ogl-core/**.cpp",
		"./ogl/ogl-core/**.h",
		"./ogl/ogl-core/**.hpp"
	}

	excludes {
		"./ogl/ogl-core/ModelImporter.cpp",
		"./ogl/ogl-core/NodeEditor/NodeEditor.cpp"
	}
	includedirs {
		"./ogl/ogl-core",
		"./ogl/vendor",
		"./RayXCore/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImPlot}"
	}
	
	links {
		"opengl32",
		"gdi32",
		"GLFW",
		"Glad",
		"ImGui",
		"ImPlot",
		"RayXCore"
	}
	
	filter "system:windows"
		staticruntime "On"
		systemversion "latest"
	
	filter "configurations:Debug"
		defines "RAYX_DEBUG"
		symbols "on"
	
	filter "configurations:Release"
		defines "RAYX_RELEASE"
		optimize "on"	