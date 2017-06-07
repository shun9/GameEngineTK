#include "DefenseState.h"
#include <SimpleMath.h>
#include "../../MacroConstants.h"
#include "StandingState.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

DefenseState* DefenseState::m_instance = nullptr;

void DefenseState::Enter(Player * player)
{
	m_time = 0;
}

PlayerState * DefenseState::HandleInput(Player * player)
{
	//ˆê’èŽžŠÔŒã‚É—§‚¿ó‘Ô‚É–ß‚é
	if (m_time > 120)
	{
		return StandingState::GetInstance();
	}

	return nullptr;
}

void DefenseState::Update(Player * player)
{
	//ŽžŠÔ‚ÌƒJƒEƒ“ƒg
	m_time++;

	//Žè‚ðã‚°‚é
	(*player)[Player::PARTS::ARM_R_PIVOT].SetAngle(Vector3(MIN(150.0f, m_time*10.0f), 0.0f, 0.0f));
	(*player)[Player::PARTS::ARM_L_PIVOT].SetAngle(Vector3(MIN(150.0f, m_time*10.0f), 0.0f, 0.0f));

	//‚‚ðŠg‘å
	(*player)[Player::PARTS::PARTS_SHIELD_R].SetScale(Vector3(1.5f, 1.5f, 1.5f));
	(*player)[Player::PARTS::PARTS_SHIELD_L].SetScale(Vector3(1.5f, 1.5f, 1.5f));
	(*player)[Player::PARTS::PARTS_SHIELD_R].SetTrans(Vector3(1.5f, 0.6f, 0.0f));
	(*player)[Player::PARTS::PARTS_SHIELD_L].SetTrans(Vector3(-1.5f, 0.6f, 0.0f));

	//‚‚Ì‚‘¬‰ñ“]
	Vector3 angle = (*player)[Player::PARTS::SHIELD_PIVOT].GetAngle();
	angle.y += 15.0f;
	(*player)[Player::PARTS::SHIELD_PIVOT].SetAngle(angle);
}

void DefenseState::Exit(Player* player)
{
	//‰ŠúˆÊ’u‚É–ß‚·
	(*player)[Player::PARTS_SHIELD_R].SetScale(Vector3(1.0f, 1.0f, 1.0f));
	(*player)[Player::PARTS_SHIELD_L].SetScale(Vector3(1.0f, 1.0f, 1.0f));
	(*player)[Player::PARTS_SHIELD_R].SetTrans(player->GetPartsStartPos(Player::PARTS_SHIELD_R));
	(*player)[Player::PARTS_SHIELD_L].SetTrans(player->GetPartsStartPos(Player::PARTS_SHIELD_L));
	(*player)[Player::ARM_R_PIVOT]   .SetAngle(Vector3(0.0f, 0.0f, 0.0f));
	(*player)[Player::ARM_L_PIVOT]   .SetAngle(Vector3(0.0f, 0.0f, 0.0f));
}
