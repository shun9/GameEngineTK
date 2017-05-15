//************************************************/
//* @file  :FollowCamera.h
//* @brief :自機に追従するカメラを制御するクラス
//* @date  :2017/05/15
//* @author:S.Katou
//************************************************/
#pragma once
#include "Camera.h"

class FollowCamera :public Camera
{
protected:
	//カメラと自機の距離
	static const float CAMERA_DISTANSE;
	float m_targetAngle;
	DirectX::SimpleMath::Vector3 m_targetPos;

public:
	FollowCamera(int w = 800, int h = 600);
	~FollowCamera();

	void Update()override;

	//情報取得
	const DirectX::SimpleMath::Vector3& GetTarget()const { return m_targetPos; }
	float GetAngle()const { return m_targetAngle; }

	//情報セット
	void SetTargetPos(const DirectX::SimpleMath::Vector3& target) { m_targetPos = target; }
	void SetAngle(float angle) { m_targetAngle = angle; }

};
