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

FollowCamera::FollowCamera(int w, int h):
	Camera(w, h),
	m_targetPos(Vector3::Zero),
	m_targetAngle(0.0f)
{

}

FollowCamera::~FollowCamera()
{
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�X�V����
//�b����  :�Ȃ�(void)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void FollowCamera::Update()
{
	//���@�̏��
	m_refPos = m_targetPos + Vector3(0.0f, 2.0f, 0.0f);

	//�Q�Ɠ_���王�_�ւ̍���
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANSE);

	//���@�̌��ɉ�荞�ނ��߂̉�]
	Matrix rot = Matrix::CreateRotationY(m_targetAngle);
	cameraV = Vector3::TransformNormal(cameraV, rot);
	m_eyePos = m_refPos + cameraV;


	Camera::Update();
}
