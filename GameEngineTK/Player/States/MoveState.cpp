#include "MoveState.h"
#include <SimpleMath.h>
#include "../../KeyBoardManager.h"
#include "StandingState.h"
#include "DefenseState.h"
#include "LongRangeAttackState.h"
#include "ShortRangeAttackState.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
MovingState* MovingState::m_instance = nullptr;

void MovingState::Enter(Player* player)
{
	m_time = 0.0f;
}

PlayerState * MovingState::HandleInput(Player* player)
{
	auto kb = KeyBoardManager::GetInstance()->GetState();

	//Z�L�[�œ���΂�
	if (kb.Z)
	{
		return LongRangeAttackState::GetInstance();
	}

	//X�L�[�Ŗh��Ԑ�
	if (kb.X)
	{
		return DefenseState::GetInstance();
	}

	//C�L�[�ŏ��U��
	if (kb.C)
	{
		return ShortRangeAttackState::GetInstance();
	}

	//�ړ����Ă�����ύX���Ȃ�
	if (kb.W || kb.S || kb.A || kb.D) { return nullptr; }

	//����w���Ă��Ȃ������痧����Ԃɖ߂�
	return StandingState::GetInstance();
}

void MovingState::Update(Player* player)
{
	auto kb = KeyBoardManager::GetInstance()->GetState();

	//�ړ�����
	float length = 0.1f;
	Vector3 spd(sin(XMConvertToRadians(player->GetAngle().y))*length, 0.0f, cos(XMConvertToRadians(player->GetAngle().y))*length);
	Vector3 pos = player->GetTrans();
	Vector3 angle = player->GetAngle();
	if (kb.W) { player->SetTrans(pos - spd); }
	if (kb.S) { player->SetTrans(pos + spd); }
	if (kb.A) { player->SetAngle(angle + Vector3::UnitY); }
	if (kb.D) { player->SetAngle(angle - Vector3::UnitY); }

	StandingState::GetInstance()->Update(player);
}

void MovingState::Exit(Player* player)
{
}
