#pragma once
#include "../PlayerState.h"
#include "../../MacroConstants.h"

class ShortRangeAttackState :
	public PlayerState
{
private:
	static ShortRangeAttackState* m_instance;

public:
	// ƒVƒ“ƒOƒ‹ƒgƒ“
	static ShortRangeAttackState* GetInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new ShortRangeAttackState();
		}
		return m_instance;
	}
	//À‘Ì‚Ìíœ
	static void DeleteInstance() { DELETE_POINTER(m_instance); }

private:
	float m_time;

public:
	void Enter(Player* player) override;
	PlayerState* HandleInput(Player* player) override;
	void Update(Player* player) override;
	void Exit(Player* player) override;

private:
	ShortRangeAttackState() {}
};