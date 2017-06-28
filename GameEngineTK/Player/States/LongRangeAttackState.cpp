#include "LongRangeAttackState.h"
#include <SimpleMath.h>
#include "StandingState.h"
#include "MoveState.h"
#include "../../KeyBoardManager.h"

using namespace DirectX::SimpleMath;
LongRangeAttackState* LongRangeAttackState::m_instance = nullptr;

void LongRangeAttackState::Enter(Player * player)
{
	m_time = 0;
	m_headPos = -5.0f;

	m_firstTrans = (*player)[Player::PARTS_HEAD].GetTrans();
	m_firstScale = (*player)[Player::PARTS_HEAD].GetScale();
	m_firstAngle = (*player)[Player::PARTS_HEAD].GetAngle();
	m_firstParent = (*player)[Player::PARTS_HEAD].GetParent();

	Matrix world = (*player)[Player::PARTS_HEAD].GetWorld();
	Vector3 scale;
	Quaternion rota;
	Vector3 pos;
	world.Decompose(scale, rota, pos);
	(*player)[Player::PARTS_HEAD].SetParent(nullptr);
	(*player)[Player::PARTS_HEAD].SetScale(scale);
	(*player)[Player::PARTS_HEAD].SetAngleQ(rota);
	(*player)[Player::PARTS_HEAD].SetTrans(pos);

	m_bulletTrans = Vector3(0.0f, -0.4f, -1.0f);
	m_bulletTrans = Vector3::Transform(m_bulletTrans, rota);
}

PlayerState * LongRangeAttackState::HandleInput(Player* player)
{
	if (m_time > 60)
	{
		return StandingState::GetInstance();
	}
	return nullptr;
}

void LongRangeAttackState::Update(Player* player)
{

	m_time++;

	Vector3 pos = (*player)[Player::PARTS_HEAD].GetTrans();
	pos += m_bulletTrans;
	(*player)[Player::PARTS_HEAD].SetTrans(pos);


	//Vector3 pos = (*player)[Player::PARTS_HEAD].GetTrans();
	//pos.y += -m_headPos / 20.0f;
	//pos.z += -0.3f;
	//(*player)[Player::PARTS_HEAD].SetTrans(pos);
	//m_headPos += 0.1f;

	MovingState::GetInstance()->Update(player);

}

void LongRangeAttackState::Exit(Player* player)
{
	//‰ŠúˆÊ’u‚É–ß‚·
	(*player)[Player::PARTS_HEAD].SetParent(m_firstParent);
	(*player)[Player::PARTS_HEAD].SetTrans(m_firstTrans);
	(*player)[Player::PARTS_HEAD].SetScale(m_firstScale);
	(*player)[Player::PARTS_HEAD].SetAngle(m_firstAngle);

}
