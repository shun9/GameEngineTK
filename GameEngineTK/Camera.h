//************************************************/
//* @file  :Camera.h
//* @brief :�J�����𐧌䂷��N���X
//* @date  :2017/05/11
//* @author:S.Katou
//************************************************/
#pragma once
#include <d3d11.h>
#include <SimpleMath.h>

class Camera
{
protected:
	//�r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	//�J�����ʒu
	DirectX::SimpleMath::Vector3 m_eyePos;

	//�����_
	DirectX::SimpleMath::Vector3 m_refPos;

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
	Camera(int w = 800, int h = 600);
	virtual ~Camera();

	//�X�V����
	virtual void Update();

	//���擾
	const DirectX::SimpleMath::Matrix& GetView()const { return m_view; }
	const DirectX::SimpleMath::Matrix& GetProj()const { return m_proj; }

	//���Z�b�g
	void SetEyePos(const DirectX::SimpleMath::Vector3& eye) { m_eyePos = eye; }
	void SetRefPos(const DirectX::SimpleMath::Vector3& ref) { m_refPos = ref; }
	void SetAspect(float aspect) { m_aspect = aspect; }
	void SetNearClip(float nearClip) { m_nearClip = nearClip; }
	void SetFarClip(float  farClip) { m_farClip = farClip; }
};