#include "StandingState.h"

#include <simplemath.h>
#include "MoveState.h"
#include "DefenseState.h"
#include "LongRangeAttackState.h"
#include "ShortRangeAttackState.h"
#include "../../KeyBoardManager.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

StandingState* StandingState::m_instance = nullptr;

/// <summary>
/// 入口処理
/// </summary>
/// <param name="player"></param>
void StandingState::Enter(Player* player)
{
	m_time = 0.0f;
}

/// <summary>
/// 入力処理
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="keyTracker">入力されたキー</param>
/// <returns>次の状態があるときは状態を返す</returns>
PlayerState* StandingState::HandleInput(Player* player)
{
	auto kb = KeyBoardManager::GetInstance()->GetState();

	//移動キーで移動
	if (kb.A || kb.W || kb.D || kb.S)
	{
		return MovingState::GetInstance();
	}

	//Zキーで頭飛ばし
	if (kb.Z)
	{
		return LongRangeAttackState::GetInstance();
	}

	//Xキーで防御態勢
	if (kb.X)
	{
		return DefenseState::GetInstance();
	}

	//Cキーで盾攻撃
	if (kb.C)
	{
		return ShortRangeAttackState::GetInstance();
	}

	return nullptr;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="player"></param>
void StandingState::Update(Player* player)
{
	auto kb = KeyBoardManager::GetInstance()->GetState();

	//本体が回転しているときの調整用倍率
	float magnification = 1.0f;
	if (kb.A) { magnification = 0.5f; }
	if (kb.D) { magnification = 2.0f; }
	m_rotation = magnification;

	//盾の回転
	Vector3 angle = (*player)[Player::PARTS::SHIELD_PIVOT].GetAngle();
	angle.y += m_rotation;
	(*player)[Player::PARTS::SHIELD_PIVOT].SetAngle(angle);

	//脚の回転
	angle = (*player)[Player::PARTS::PARTS_LEG].GetAngle();
	angle.y += m_rotation * 2;
	(*player)[Player::PARTS::PARTS_LEG].SetAngle(angle);

	//足の回転
	angle = (*player)[Player::PARTS::PARTS_FOOT].GetAngle();
	angle.y += -(m_rotation * 3);
	(*player)[Player::PARTS::PARTS_FOOT].SetAngle(angle);
}

/// <summary>
/// 出口処理
/// </summary>
/// <param name="player"></param>
void StandingState::Exit(Player* player)
{

}

