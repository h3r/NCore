#include "ncpch.h"
#include "render_command.h"
#include "platform/opengl/opengl_api.h"

namespace NC {

	RenderAPI* RenderCommand::m_api = new OpenGLRenderAPI;

}

