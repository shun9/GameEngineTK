#pragma once
#include "../PlayerState.h"
#include "../../MacroConstants.h"

class StandingState :
	public PlayerState
{
private:
	static StandingState* m_instance;


public:
	// �V���O���g��
	static StandingState* GetInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new StandingState();
		}
		return m_instance;
	}

	//���̂̍폜
	static void DeleteInstance() { DELETE_POINTER(m_instance); }

private:
	//���Ԍv���p
	float m_time;

	//��]�p
	float m_rotation;

public:
	void Enter              (Player* player) override;
	PlayerState* HandleInput(Player* player) override;
	void Update             (Player* player) override;
	void Exit               (Player* player) override;


private:
	StandingState()
		:m_rotation(0.0f) {}

};