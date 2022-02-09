#pragma once
#include "render/vertex_array.h"

namespace NC {

	class RenderAPI {
	public:
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& _color) = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& _vertex_array) = 0;
	};

}
