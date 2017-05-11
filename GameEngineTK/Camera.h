//************************************************/
//* @file  :Camera.h
//* @brief :カメラを制御するクラス
//* @date  :2017/05/11
//* @author:S.Katou
//************************************************/
#pragma once
#include <SimpleMath.h>

class Camera
{
protected:
	//ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	//カメラ位置
	DirectX::SimpleMath::Vector3 m_eyePos;

	//注視点
	DirectX::SimpleMath::Vector3 m_targetPos;

	//射影行列
	DirectX::SimpleMath::Matrix m_proj;
	//垂直方向視野角
	float m_fovY;

	//画面の横幅と縦幅の比率
	float m_aspect;

	//手前の表示限界距離
	float m_nearClip;

	//奥の表示限界距離
	float m_farClip;

public:
	Camera();
	virtual ~Camera();

	//更新処理
	void Update();

	//情報取得
	DirectX::SimpleMath::Matrix GetView() { return m_view; }
	DirectX::SimpleMath::Matrix GetProj() { return m_proj; }

	//情報セット
	void SetEyePos(const DirectX::SimpleMath::Vector3& eye) { m_eyePos = eye; }
	void SetTargetPos(const DirectX::SimpleMath::Vector3& target) { m_targetPos = target; }
	void SetAspect(float aspect) { m_aspect = aspect; }
	void SetNearClip(float nearClip) { m_nearClip = nearClip; }
	void SetFarClip(float  farClip) { m_farClip = farClip; }
};