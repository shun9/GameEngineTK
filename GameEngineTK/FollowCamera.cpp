//************************************************/
//* @file  :FollowCamera.cpp
//* @brief :自機に追従するカメラを制御するクラス
//* @date  :2017/05/15
//* @author:S.Katou
//************************************************/
#include "FollowCamera.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;

//カメラと自機の距離
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

//＋ーーーーーーーーーーーーーー＋
//｜機能  :更新処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void FollowCamera::Update()
{
	//自機の上方
	m_refPos = m_targetPos + Vector3(0.0f, 2.0f, 0.0f);

	//参照点から視点への差分
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANSE);

	//自機の後ろに回り込むための回転
	Matrix rot = Matrix::CreateRotationY(m_targetAngle);
	cameraV = Vector3::TransformNormal(cameraV, rot);
	m_eyePos = m_refPos + cameraV;


	Camera::Update();
}
