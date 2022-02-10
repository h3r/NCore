#pragma once
#include "core/core.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
//mat4 camera(float _translate, vec2 const& rotate)
//{
//  mat4 projection = glm::perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
//  mat4 view = translate(mat4(1.0f), vec3(0.0f, 0.0f, -_translate)) *
//     rotate(mat4(1.0f), radians(rotate.x), vec3(1.0f, 0.0f, 0.0f)) *
//     rotate(mat4(1.0f), radians(rotate.y), vec3(0.0f, 1.0f, 0.0f));
//  mat4 model = scale(mat4(1.0f), vec3(0.5f));
//  return projection * view * model;
//}


namespace NC
{
	struct NC_API OrthoGraphicCamera {
		OrthoGraphicCamera() {}
		OrthoGraphicCamera(float _left, float _right, float _bottom, float _top);
		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(const glm::vec3& _position) { m_position = _position; ComputeMatrices(); }
		const glm::quat& GetRotation() const { return m_rotation; }
		void SetRotation(const glm::quat& _rotation) { m_rotation = _rotation; ComputeMatrices(); }

		const glm::mat4& GetProjMatrix()	   const { return m_proj; }
		const glm::mat4& GetViewMatrix()		 const { return m_view; }
		const glm::mat4& GetViewProjMatrix() const { return m_view_proj; }
	
	private:
		void ComputeMatrices();

	private:
		glm::mat4 m_view;
		glm::mat4 m_proj;
		glm::mat4 m_view_proj;
		glm::vec3 m_position;
		glm::quat m_rotation;
	};

	struct NC_API PerspectiveCamera {
		PerspectiveCamera(float fov, float aspect, float near, float far) {}
	};

}
