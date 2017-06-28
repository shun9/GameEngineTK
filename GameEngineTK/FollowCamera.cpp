//************************************************/
//* @file  :FollowCamera.cpp
//* @brief :���@�ɒǏ]����J�����𐧌䂷��N���X
//* @date  :2017/05/15
//* @author:S.Katou
//************************************************/
#include "FollowCamera.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;

//�J�����Ǝ��@�̋���
const float FollowCamera::CAMERA_DISTANSE = 5.0f;
const bool FollowCamera::FPS = true;
const bool FollowCamera::TPS = false;

FollowCamera::FollowCamera(int w, int h):
	Camera(w, h),
	m_targetPos(Vector3::Zero),
	m_targetAngle(0.0f),
	m_keyboard(nullptr),
	m_cameraMode(TPS)
{
	InitiallizeTPS();
}

FollowCamera::~FollowCamera()
{
}

void FollowCamera::InitiallizeTPS()
{
	//���@�̏��
	Vector3 refPos = m_targetPos + Vector3(0.0f, 1.5f, 0.0f);

	//�Q�Ɠ_���王�_�ւ̍���
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANSE);

	//���@�̌��ɉ�荞�ނ��߂̉�]
	Matrix rot = Matrix::CreateRotationY(XMConvertToRadians(m_targetAngle));
	cameraV = Vector3::TransformNormal(cameraV, rot);
	Vector3 eyePos = refPos + cameraV;

	m_eyePos = eyePos;
	m_refPos = refPos;
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�X�V����
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void FollowCamera::Update()
{
	//�L�[�{�[�h�̏�Ԃ��擾
	DirectX::Keyboard::State keyState= m_keyboard->GetState();
	m_keyTracker.Update(keyState);

	//C�L�[����������J�����̏�Ԃ�؂�ւ���
	if (m_keyTracker.IsKeyPressed(Keyboard::Keyboard::Q))
	{
		//�t���O�ؑ�
		m_cameraMode = !m_cameraMode;

		if (m_cameraMode == TPS)
		{
			InitiallizeTPS();
		}
	}

	/*--�S���R�J����--*/
	if (m_cameraMode == TPS)
	{
		//���@�̏��
		Vector3 refPos = m_targetPos + Vector3(0.0f, 2.5f, 0.0f);

		//�Q�Ɠ_���王�_�ւ̍���
		Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANSE);

		//���@�̌��ɉ�荞�ނ��߂̉�]
		Matrix rot = Matrix::CreateRotationY(XMConvertToRadians(m_targetAngle));
		cameraV = Vector3::TransformNormal(cameraV, rot);
		Vector3 eyePos = refPos + cameraV;

		m_eyePos = m_eyePos + (eyePos - m_eyePos)*0.05f;
		m_refPos = m_refPos + (refPos - m_refPos)*0.2f;
	}

	/*--FPS�J����--*/
	if (m_cameraMode == FPS)
	{
		//���@�̏��
		Vector3 eyePos = m_targetPos + Vector3(0.0f, 0.2f, 0.0f);

		Vector3 cameraV(0.0f, 0.0f, -CAMERA_DISTANSE);

		//���@�̌��ɉ�荞�ނ��߂̉�]
		Matrix rot = Matrix::CreateRotationY(XMConvertToRadians(m_targetAngle));
		cameraV = Vector3::TransformNormal(cameraV, rot);

		Vector3 refPos = eyePos + cameraV;

		m_refPos = refPos;
		m_eyePos = eyePos + cameraV*0.1f;
	}

	Camera::Update();
}
