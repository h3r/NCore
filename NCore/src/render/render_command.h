#pragma once
#include "render/render_api.h"

namespace NC {

	class RenderCommand {
	public:
		inline static void Clear() { m_api->Clear(); }
		inline static void SetClearColor(const glm::vec4 _color) { m_api->SetClearColor(_color); }
		inline static void DrawIndexed(const Ref<VertexArray> _vertex_array) { m_api->DrawIndexed(_vertex_array); }
	private:
		static RenderAPI* m_api;
	
	};
}

