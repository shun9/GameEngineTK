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
/// ��������
/// </summary>
/// <param name="player"></param>
void StandingState::Enter(Player* player)
{
	m_time = 0.0f;
}

/// <summary>
/// ���͏���
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="keyTracker">���͂��ꂽ�L�[</param>
/// <returns>���̏�Ԃ�����Ƃ��͏�Ԃ�Ԃ�</returns>
PlayerState* StandingState::HandleInput(Player* player)
{
	auto kb = KeyBoardManager::GetInstance()->GetState();

	//�ړ��L�[�ňړ�
	if (kb.A || kb.W || kb.D || kb.S)
	{
		return MovingState::GetInstance();
	}

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

	return nullptr;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="player"></param>
void StandingState::Update(Player* player)
{
	auto kb = KeyBoardManager::GetInstance()->GetState();

	//�{�̂���]���Ă���Ƃ��̒����p�{��
	float magnification = 1.0f;
	if (kb.A) { magnification = 0.5f; }
	if (kb.D) { magnification = 2.0f; }
	m_rotation = magnification;

	//���̉�]
	Vector3 angle = (*player)[Player::PARTS::SHIELD_PIVOT].GetAngle();
	angle.y += m_rotation;
	(*player)[Player::PARTS::SHIELD_PIVOT].SetAngle(angle);

	//�r�̉�]
	angle = (*player)[Player::PARTS::PARTS_LEG].GetAngle();
	angle.y += m_rotation * 2;
	(*player)[Player::PARTS::PARTS_LEG].SetAngle(angle);

	//���̉�]
	angle = (*player)[Player::PARTS::PARTS_FOOT].GetAngle();
	angle.y += -(m_rotation * 3);
	(*player)[Player::PARTS::PARTS_FOOT].SetAngle(angle);
}

/// <summary>
/// �o������
/// </summary>
/// <param name="player"></param>
void StandingState::Exit(Player* player)
{

}

