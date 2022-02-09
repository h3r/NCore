#pragma once
#include "ncpch.h"
#include "opengl_api.h"
#include <glad/glad.h>

namespace NC {

	void OpenGLRenderAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void OpenGLRenderAPI::SetClearColor(const glm::vec4& _color) {
		glClearColor(_color.r, _color.g, _color.b, _color.a);
	}

	void OpenGLRenderAPI::DrawIndexed(const Ref<VertexArray>& _vertex_array) {
		glDrawElements(GL_TRIANGLES, _vertex_array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	};

}
