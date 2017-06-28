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
	//自機の上方
	Vector3 refPos = m_targetPos + Vector3(0.0f, 1.5f, 0.0f);

	//参照点から視点への差分
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANSE);

	//自機の後ろに回り込むための回転
	Matrix rot = Matrix::CreateRotationY(XMConvertToRadians(m_targetAngle));
	cameraV = Vector3::TransformNormal(cameraV, rot);
	Vector3 eyePos = refPos + cameraV;

	m_eyePos = eyePos;
	m_refPos = refPos;
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :更新処理
//｜引数  :なし(void)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void FollowCamera::Update()
{
	//キーボードの状態を取得
	DirectX::Keyboard::State keyState= m_keyboard->GetState();
	m_keyTracker.Update(keyState);

	//Cキーを押したらカメラの状態を切り替える
	if (m_keyTracker.IsKeyPressed(Keyboard::Keyboard::Q))
	{
		//フラグ切替
		m_cameraMode = !m_cameraMode;

		if (m_cameraMode == TPS)
		{
			InitiallizeTPS();
		}
	}

	/*--ゴム紐カメラ--*/
	if (m_cameraMode == TPS)
	{
		//自機の上方
		Vector3 refPos = m_targetPos + Vector3(0.0f, 2.5f, 0.0f);

		//参照点から視点への差分
		Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANSE);

		//自機の後ろに回り込むための回転
		Matrix rot = Matrix::CreateRotationY(XMConvertToRadians(m_targetAngle));
		cameraV = Vector3::TransformNormal(cameraV, rot);
		Vector3 eyePos = refPos + cameraV;

		m_eyePos = m_eyePos + (eyePos - m_eyePos)*0.05f;
		m_refPos = m_refPos + (refPos - m_refPos)*0.2f;
	}

	/*--FPSカメラ--*/
	if (m_cameraMode == FPS)
	{
		//自機の上方
		Vector3 eyePos = m_targetPos + Vector3(0.0f, 0.2f, 0.0f);

		Vector3 cameraV(0.0f, 0.0f, -CAMERA_DISTANSE);

		//自機の後ろに回り込むための回転
		Matrix rot = Matrix::CreateRotationY(XMConvertToRadians(m_targetAngle));
		cameraV = Vector3::TransformNormal(cameraV, rot);

		Vector3 refPos = eyePos + cameraV;

		m_refPos = refPos;
		m_eyePos = eyePos + cameraV*0.1f;
	}

	Camera::Update();
}
