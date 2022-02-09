#pragma once
#include "events/event.h"

namespace NC
{
	enum class RendererAPI {
		None = 0,
		OpenGL = 1,
	};

	class NC_API Renderer {
	public:
		inline static RendererAPI GetAPI(){ return s_renderer_api; }
	private:
		static RendererAPI s_renderer_api;
	};

}
