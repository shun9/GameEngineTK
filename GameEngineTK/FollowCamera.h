//************************************************/
//* @file  :FollowCamera.h
//* @brief :���@�ɒǏ]����J�����𐧌䂷��N���X
//* @date  :2017/05/15
//* @author:S.Katou
//************************************************/
#pragma once
#include "Camera.h"

class FollowCamera :public Camera
{
protected:
	//�J�����Ǝ��@�̋���
	static const float CAMERA_DISTANSE;
	float m_targetAngle;
	DirectX::SimpleMath::Vector3 m_targetPos;

public:
	FollowCamera(int w = 800, int h = 600);
	~FollowCamera();

	void Update()override;

	//���擾
	const DirectX::SimpleMath::Vector3& GetTarget()const { return m_targetPos; }
	float GetAngle()const { return m_targetAngle; }

	//���Z�b�g
	void SetTargetPos(const DirectX::SimpleMath::Vector3& target) { m_targetPos = target; }
	void SetAngle(float angle) { m_targetAngle = angle; }

};
