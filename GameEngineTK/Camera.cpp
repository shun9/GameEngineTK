//************************************************/
//* @file  :Camera.cpp
//* @brief :ÉJÉÅÉâÇêßå‰Ç∑ÇÈÉNÉâÉX
//* @date  :2017/05/11
//* @author:S.Katou
//************************************************/
#include "pch.h"
#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Camera::Camera()
	: m_eyePos((0.0f, 0.0f, 3.0f))
	, m_targetPos((0.0f, 0.0f, 0.0f))
	, m_fovY(XMConvertToRadians(60.0f))
	, m_aspect(800.0f / 600.0f)
	, m_nearClip(0.1f)
	, m_farClip(1000.0f)
{
	m_view = Matrix::CreateLookAt(m_eyePos, m_targetPos, Vector3::UnitY);

	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	m_view = Matrix::CreateLookAt(m_eyePos, m_targetPos, Vector3::UnitY);

	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);
}
