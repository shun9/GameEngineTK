#include "ShortRangeAttackState.h"
#include <SimpleMath.h>
#include "../../MacroConstants.h"
#include "StandingState.h"

using namespace DirectX::SimpleMath;

ShortRangeAttackState* ShortRangeAttackState::m_instance = nullptr;

void ShortRangeAttackState::Enter(Player * player)
{
	m_time = 0;
}

PlayerState* ShortRangeAttackState::HandleInput(Player* player)
{
	if (m_time > 50)
	{
		return StandingState::GetInstance();
	}
	return nullptr;
}

void ShortRangeAttackState::Update(Player* player)
{
	m_time++;

	//‚UŒ‚
	(*player)[Player::SHIELD_PIVOT].SetTrans(player->GetPartsStartPos(Player::SHIELD_PIVOT) + Vector3(0.0f, MIN(m_time / 30.0f*0.8f, 0.8f), 0.0f));
	(*player)[Player::SHIELD_PIVOT].SetAngle(Vector3(0.0f, 0.0f, 0.0f));

	float shieldAngle = MIN(m_time / 30.0f*90.0f, 90.0f);
	(*player)[Player::PARTS_SHIELD_R].SetAngle(Vector3(shieldAngle, 0.0f, 0.0f));
	(*player)[Player::PARTS_SHIELD_L].SetAngle(Vector3(-shieldAngle, 180.0f, 0.0f));

	Vector3 move;
	Vector3 move2;
	float armAngle = m_time*10.0f;
	if (m_time < 20)
	{
		//Žè‚ðã‚°‚é
		(*player)[Player::ARM_R_PIVOT].SetAngle(Vector3(MIN(150.0f, armAngle), 0.0f, 0.0f));
		(*player)[Player::ARM_L_PIVOT].SetAngle(Vector3(MIN(150.0f, armAngle), 0.0f, 0.0f));

		move.x = 0.01f;
		move2.x = -0.01f;
	}
	else if (m_time < 35)
	{
		//Žè‚ð‘O•û‚ÉŒü‚¯‚é
		(*player)[Player::ARM_R_PIVOT].SetAngle(Vector3(MAX(90.0f, 350.0f - armAngle), 0.0f, 0.0f));
		(*player)[Player::ARM_L_PIVOT].SetAngle(Vector3(MAX(90.0f, 350.0f - armAngle), 0.0f, 0.0f));

		move.x = -0.02f;
		move2.x = 0.02f;
		move.z = -0.4f;
		move2.z = -0.4f;
	}
	else
	{
		//Žè‚ð–ß‚·
		move.x = 0.02f;
		move2.x = -0.02f;
		move.z = 0.4f;
		move2.z = 0.4f;
	}

	(*player)[Player::PARTS_SHIELD_R].SetTrans((*player)[Player::PARTS_SHIELD_R].GetTrans() + move);
	(*player)[Player::PARTS_SHIELD_L].SetTrans((*player)[Player::PARTS_SHIELD_L].GetTrans() + move2);
}

void ShortRangeAttackState::Exit(Player* player)
{
	//‰ŠúˆÊ’u‚É–ß‚·
	(*player)[Player::PARTS_SHIELD_R].SetScale(Vector3(1.0f, 1.0f, 1.0f));
	(*player)[Player::PARTS_SHIELD_L].SetScale(Vector3(1.0f, 1.0f, 1.0f));

	(*player)[Player::PARTS_SHIELD_R].SetTrans(player->GetPartsStartPos(Player::PARTS_SHIELD_R));
	(*player)[Player::PARTS_SHIELD_L].SetTrans(player->GetPartsStartPos(Player::PARTS_SHIELD_L));

	(*player)[Player::PARTS_SHIELD_R].SetAngle(Vector3(0.0f, 0.0f, 0.0f));
	(*player)[Player::PARTS_SHIELD_L].SetAngle(Vector3(0.0f, 180.0f, 0.0f));
	(*player)[Player::SHIELD_PIVOT].SetAngle(Vector3(0.0f, 0.0f, 0.0f));
	(*player)[Player::SHIELD_PIVOT].SetTrans(player->GetPartsStartPos(Player::SHIELD_PIVOT));

	(*player)[Player::ARM_R_PIVOT].SetAngle(Vector3(0.0f, 0.0f, 0.0f));
	(*player)[Player::ARM_L_PIVOT].SetAngle(Vector3(0.0f, 0.0f, 0.0f));

}
