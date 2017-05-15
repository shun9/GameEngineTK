//************************************************/
//* @file  :Camera.cpp
//* @brief :�J�����𐧌䂷��N���X
//* @date  :2017/05/11
//* @author:S.Katou
//************************************************/
#include "pch.h"
#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Camera::Camera(int w, int h)
	: m_eyePos((0.0f, 0.0f, 3.0f))
	, m_refPos((0.0f, 0.0f, 0.0f))
	, m_fovY(XMConvertToRadians(60.0f))
	, m_aspect(static_cast<float>(w / h))
	, m_nearClip(0.1f)
	, m_farClip(1000.0f)
{
	m_view = Matrix::CreateLookAt(m_eyePos, m_refPos, Vector3::UnitY);

	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);
}

Camera::~Camera()
{
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�X�V����
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Camera::Update()
{
	m_view = Matrix::CreateLookAt(m_eyePos, m_refPos, Vector3::UnitY);

	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearClip, m_farClip);
}
