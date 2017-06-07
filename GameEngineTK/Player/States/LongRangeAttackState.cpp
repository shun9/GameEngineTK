#include "LongRangeAttackState.h"
#include <SimpleMath.h>
#include "StandingState.h"

using namespace DirectX::SimpleMath;
LongRangeAttackState* LongRangeAttackState::m_instance = nullptr;

void LongRangeAttackState::Enter(Player * player)
{
	m_time = 0;
	m_headPos = -5.0f;
}

PlayerState * LongRangeAttackState::HandleInput(Player* player)
{
	if (m_headPos > 5.1f)
	{
		return StandingState::GetInstance();
	}
	return nullptr;
}

void LongRangeAttackState::Update(Player* player)
{
	Vector3 pos = (*player)[Player::PARTS_HEAD].GetTrans();
	pos.y += -m_headPos / 20.0f;
	pos.z += -0.3f;
	(*player)[Player::PARTS_HEAD].SetTrans(pos);
	m_headPos += 0.1f;
	StandingState::GetInstance()->Update(player);

}

void LongRangeAttackState::Exit(Player* player)
{
	//‰ŠúˆÊ’u‚É–ß‚·
	(*player)[Player::PARTS_HEAD].SetTrans(player->GetPartsStartPos(Player::PARTS_HEAD));
}
