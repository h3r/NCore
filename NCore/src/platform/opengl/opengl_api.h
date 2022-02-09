#pragma once
#include "render/render_api.h"

namespace NC {

	class OpenGLRenderAPI : public RenderAPI {
	public:
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& _color) override;
		virtual void DrawIndexed(const Ref<VertexArray>& _vertex_array) override;
	};

}
