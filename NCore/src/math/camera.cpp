#include "ncpch.h"
#include "camera.h"

namespace NC
{

	OrthoGraphicCamera::OrthoGraphicCamera(float _left, float _right, float _bottom, float _top)
		: m_proj(glm::ortho(_left, _right, _bottom, _top, -1.f, 1.f))
		, m_position({ 0,0,0 })
		, m_rotation({ 0,0,0,1 })
	{
		ComputeMatrices();
	}

	void OrthoGraphicCamera::ComputeMatrices()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.f), m_position) * glm::mat4(m_rotation);
		m_view = glm::inverse(transform);
		m_view_proj = m_proj * m_view; //column major
	}
}
