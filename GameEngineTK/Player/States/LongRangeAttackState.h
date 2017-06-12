#pragma once
#include "../PlayerState.h"
#include "../../MacroConstants.h"

class LongRangeAttackState :
	public PlayerState
{
private:
	static LongRangeAttackState* m_instance;

public:
	// �V���O���g��
	static LongRangeAttackState* GetInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new LongRangeAttackState();
		}
		return m_instance;
	}

	//���̂̍폜
	static void DeleteInstance() { DELETE_POINTER(m_instance); }

private:
	float m_time;
	float m_headPos;

	DirectX::SimpleMath::Vector3 m_bulletTrans;

	DirectX::SimpleMath::Vector3 m_firstTrans;
	DirectX::SimpleMath::Vector3 m_firstScale;
	DirectX::SimpleMath::Vector3 m_firstAngle;
	Obj3d* m_firstParent;

public:
	void Enter(Player* player) override;
	PlayerState* HandleInput(Player* player) override;
	void Update(Player* player) override;
	void Exit(Player* player) override;

private:
	LongRangeAttackState() {}
};