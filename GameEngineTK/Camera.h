//************************************************/
//* @file  :Camera.h
//* @brief :�J�����𐧌䂷��N���X
//* @date  :2017/05/11
//* @author:S.Katou
//************************************************/
#pragma once
#include <SimpleMath.h>

class Camera
{
protected:
	//�r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	//�J�����ʒu
	DirectX::SimpleMath::Vector3 m_eyePos;

	//�����_
	DirectX::SimpleMath::Vector3 m_targetPos;

	//�ˉe�s��
	DirectX::SimpleMath::Matrix m_proj;
	//������������p
	float m_fovY;

	//��ʂ̉����Əc���̔䗦
	float m_aspect;

	//��O�̕\�����E����
	float m_nearClip;

	//���̕\�����E����
	float m_farClip;

public:
	Camera();
	virtual ~Camera();

	//�X�V����
	void Update();

	//���擾
	DirectX::SimpleMath::Matrix GetView() { return m_view; }
	DirectX::SimpleMath::Matrix GetProj() { return m_proj; }

	//���Z�b�g
	void SetEyePos(const DirectX::SimpleMath::Vector3& eye) { m_eyePos = eye; }
	void SetTargetPos(const DirectX::SimpleMath::Vector3& target) { m_targetPos = target; }
	void SetAspect(float aspect) { m_aspect = aspect; }
	void SetNearClip(float nearClip) { m_nearClip = nearClip; }
	void SetFarClip(float  farClip) { m_farClip = farClip; }
};