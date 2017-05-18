//************************************************/
//* @file  :FollowCamera.h
//* @brief :���@�ɒǏ]����J�����𐧌䂷��N���X
//* @date  :2017/05/15
//* @author:S.Katou
//************************************************/
#pragma once
#include "Camera.h"
#include <Keyboard.h>

class FollowCamera :public Camera
{
protected:
	//�J�������[�h
	static const bool FPS;
	static const bool TPS;

	//�J�����Ǝ��@�̋���
	static const float CAMERA_DISTANSE;
	float m_targetAngle;
	DirectX::SimpleMath::Vector3 m_targetPos;
	DirectX::Keyboard* m_keyboard;
	DirectX::Keyboard::KeyboardStateTracker m_keyTracker;

	bool m_cameraMode;

public:
	FollowCamera(int w = 800, int h = 600);
	~FollowCamera();

	void InitiallizeTPS();

	void Update()override;

	//���擾
	const DirectX::SimpleMath::Vector3& GetTarget()const { return m_targetPos; }
	float GetAngle()const { return m_targetAngle; }

	//���Z�b�g
	void SetTargetPos(const DirectX::SimpleMath::Vector3& target) { m_targetPos = target; }
	void SetAngle(float angle) { m_targetAngle = angle; }

	void SetKeyboard(DirectX::Keyboard* key) { m_keyboard = key; }
};
