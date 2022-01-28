#include "ncpch.h"
#include "context.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace NC {

	OpenGLContext::OpenGLContext(GLFWwindow* _handle) 
		: m_handle( _handle )
	{
		nc_assert(m_handle, "Handle is null");
	}

	void OpenGLContext::Init() {
		//Create the OpenGL context
		glfwMakeContextCurrent(m_handle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		nc_assert(status, std::string("Failed to create OpenGL context with Glad!"));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_handle);
	}

}
