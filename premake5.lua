require "tools/premake5"
require "dependencies"

workspace "NCore"
	architecture "x86_64"
	startproject "NCEdit"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	include "NCore"
	include "NCEdit"
	include "Sandbox"