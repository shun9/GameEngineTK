#include "Player.h"
#include "PlayerState.h"
#include "States\StandingState.h"
#include "../KeyBoardManager.h"

using namespace std;
using namespace DirectX::SimpleMath;

Player::Player():
	m_speed(Vector3(0.0f, 0.0f, 0.0f))	,
	m_acceleSpeed(Vector3(0.0f, 0.05f, 0.0f))
{
	Init();

	// デフォルトのステート設定
	m_state = StandingState::GetInstance();
}

void Player::Update()
{
	// ステートの更新
	m_state->Update(this);

	// ステートに入力を渡す
	PlayerState* state = m_state->HandleInput(this);

	// ステートが変化していたら
	if (state != nullptr)
	{
		// ステートの出口処理
		m_state->Exit(this);
		// ステートを最新に更新
		m_state = state;
		// ステートの入り口処理
		m_state->Enter(this);
	}


	// 基底の更新
	this->Obj3d::Update();

	// 全パーツの更新
	for (auto itr = m_robot.begin(); itr != m_robot.end(); itr++)
	{
		(*itr).Update();
	}
}

void Player::Render()
{
	// 全パーツの描画
	for (auto itr = m_robot.begin(); itr != m_robot.end(); itr++)
	{
		(*itr).Render();
	}
}

void Player::Init()
{
	//ロボットの生成
	m_robot.resize(PARTS_NUM);
	m_robot[PARTS_HEAD]    .LoadModel(L"Resources\\Head.cmo");
	m_robot[PARTS_BODYTOP] .LoadModel(L"Resources\\BodyTop.cmo");
	m_robot[PARTS_BODY]    .LoadModel(L"Resources\\Body.cmo");
	m_robot[PARTS_ARM_R]   .LoadModel(L"Resources\\Arm.cmo");
	m_robot[PARTS_ARM_L]   .LoadModel(L"Resources\\Arm.cmo");
	m_robot[PARTS_HAND_R]  .LoadModel(L"Resources\\Hand.cmo");
	m_robot[PARTS_HAND_L]  .LoadModel(L"Resources\\Hand.cmo");
	m_robot[PARTS_SHIELD_R].LoadModel(L"Resources\\Shield.cmo");
	m_robot[PARTS_SHIELD_L].LoadModel(L"Resources\\Shield.cmo");
	m_robot[PARTS_LEG]     .LoadModel(L"Resources\\Leg.cmo");
	m_robot[PARTS_FOOT]    .LoadModel(L"Resources\\Foot.cmo");


	//親の設定
	m_robot[PIVOT]         .SetParent(this);
	m_robot[SHIELD_PIVOT]  .SetParent(&m_robot[PIVOT]);
	m_robot[ARM_R_PIVOT]   .SetParent(&m_robot[PARTS_BODYTOP]);
	m_robot[ARM_L_PIVOT]   .SetParent(&m_robot[PARTS_BODYTOP]);
	m_robot[PARTS_HEAD]    .SetParent(&m_robot[PARTS_BODY]);
	m_robot[PARTS_BODYTOP] .SetParent(&m_robot[PARTS_BODY]);
	m_robot[PARTS_BODY]    .SetParent(&m_robot[PIVOT]);
	m_robot[PARTS_ARM_R]   .SetParent(&m_robot[ARM_R_PIVOT]);
	m_robot[PARTS_ARM_L]   .SetParent(&m_robot[ARM_L_PIVOT]);
	m_robot[PARTS_HAND_R]  .SetParent(&m_robot[PARTS_ARM_R]);
	m_robot[PARTS_HAND_L]  .SetParent(&m_robot[PARTS_ARM_L]);
	m_robot[PARTS_SHIELD_R].SetParent(&m_robot[SHIELD_PIVOT]);
	m_robot[PARTS_SHIELD_L].SetParent(&m_robot[SHIELD_PIVOT]);
	m_robot[PARTS_LEG]     .SetParent(&m_robot[PARTS_BODY]);
	m_robot[PARTS_FOOT]    .SetParent(&m_robot[PARTS_LEG]);


	//位置の設定
	m_robot[SHIELD_PIVOT]  .SetTrans(Vector3(0.0f, 0.0f, 0.0f));
	m_robot[ARM_R_PIVOT]   .SetTrans(Vector3(0.2f, 0.2f, 0.05f));
	m_robot[ARM_L_PIVOT]   .SetTrans(Vector3(-0.2f, 0.2f, 0.05f));
	m_robot[PARTS_HEAD]    .SetTrans(Vector3(0.0f, 0.72f, 0.1f));
	m_robot[PARTS_BODYTOP] .SetTrans(Vector3(0.0f, 0.37f, 0.0f));
	m_robot[PARTS_BODY]    .SetTrans(Vector3(0.0f, 0.5f, 0.0f));
	m_robot[PARTS_ARM_R]   .SetTrans(Vector3(0.0f, 0.0f, 0.0f));
	m_robot[PARTS_ARM_L]   .SetTrans(Vector3(0.0f, 0.0f, 0.0f));
	m_robot[PARTS_HAND_R]  .SetTrans(Vector3(0.0f, 0.55f, 0.51f));
	m_robot[PARTS_HAND_L]  .SetTrans(Vector3(0.0f, 0.55f, 0.51f));
	m_robot[PARTS_SHIELD_R].SetTrans(Vector3(0.8f, 0.6f, 0.0f));
	m_robot[PARTS_SHIELD_L].SetTrans(Vector3(-0.8f, 0.6f, 0.0f));
	m_robot[PARTS_LEG]     .SetTrans(Vector3(0.0f, -0.2f, 0.02f));
	m_robot[PARTS_FOOT]    .SetTrans(Vector3(0.0f, -0.25f, 0.0f));


	//拡大率設定
	m_robot[SHIELD_PIVOT]  .SetScale(Vector3(1.2f, 1.2f, 1.2f));
	m_robot[PARTS_HEAD]    .SetScale(Vector3(1.6f, 2.0f, 1.6f));
	m_robot[PARTS_BODYTOP] .SetScale(Vector3(1.0f, 0.9f, 1.0f));
	m_robot[PARTS_BODY]    .SetScale(Vector3(1.5f, 1.5f, 1.5f));
	m_robot[PARTS_SHIELD_R].SetScale(Vector3(1.0f, 1.0f, 1.0f));
	m_robot[PARTS_SHIELD_L].SetScale(Vector3(1.0f, 1.0f, 1.0f));
	m_robot[PARTS_LEG]     .SetScale(Vector3(1.0f, 1.0f, 1.0f));
	m_robot[PARTS_FOOT]    .SetScale(Vector3(0.7f, 0.7f, 0.7f));


	//角度設定
	m_robot[PARTS_HEAD]    .SetAngle(Vector3(20.0f, 0.0f, 0.0f));
	m_robot[PARTS_BODYTOP] .SetAngle(Vector3(-5.0f, 0.0f, 0.0f));
	m_robot[PARTS_SHIELD_L].SetAngle(Vector3(0.0f, 180.0f, 0.0f));
	m_robot[PARTS_ARM_R]   .SetAngle(Vector3(150.0f, 0.0f, -10.0f));
	m_robot[PARTS_ARM_L]   .SetAngle(Vector3(150.0f, 0.0f, 10.0f));
	m_robot[PARTS_HAND_R]  .SetAngle(Vector3(135.0f, 0.0f, 0.0f));
	m_robot[PARTS_HAND_L]  .SetAngle(Vector3(135.0f, 0.0f, 0.0f));

	//初期位置を保存しておく
	std::vector<Obj3d>::iterator robotItr;
	for (robotItr = m_robot.begin(); robotItr != m_robot.end(); robotItr++)
	{
		m_robotStartPos.push_back(Vector3((*robotItr).GetTrans()));
	}
}
