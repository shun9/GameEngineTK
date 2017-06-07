#pragma once
#include "../PlayerState.h"
#include "../../MacroConstants.h"

class LongRangeAttackState :
	public PlayerState
{
private:
	static LongRangeAttackState* m_instance;

public:
	// シングルトン
	static LongRangeAttackState* GetInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new LongRangeAttackState();
		}
		return m_instance;
	}

	//実体の削除
	static void DeleteInstance() { DELETE_POINTER(m_instance); }

private:
	float m_time;
	float m_headPos;

public:
	void Enter(Player* player) override;
	PlayerState* HandleInput(Player* player) override;
	void Update(Player* player) override;
	void Exit(Player* player) override;

private:
	LongRangeAttackState() {}
};