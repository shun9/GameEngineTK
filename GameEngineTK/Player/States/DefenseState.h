#pragma once
#include "../PlayerState.h"
#include "../../MacroConstants.h"

class DefenseState :
	public PlayerState
{
private:
	static DefenseState* m_instance;


	float m_time;

public:
	// ƒVƒ“ƒOƒ‹ƒgƒ“
	static DefenseState* GetInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new DefenseState();
		}
		return m_instance;
	}

	//À‘Ì‚Ìíœ
	static void DeleteInstance() { DELETE_POINTER(m_instance); }

public:
	void Enter              (Player* player) override;
	PlayerState* HandleInput(Player* player) override;
	void Update             (Player* player) override;
	void Exit               (Player* player) override;

private:
	DefenseState() {}
};