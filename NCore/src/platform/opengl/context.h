#include "render/context.h"
struct GLFWwindow;

namespace NC {
	
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* _handle);
		void Init() override ;
		void SwapBuffers() override;

	private: 
		GLFWwindow* m_handle;
	};

}
