#pragma once
#include "../PlayerState.h"
#include "../../MacroConstants.h"

class MovingState :
	public PlayerState
{
private:
	static MovingState* m_instance;

public:
	// �V���O���g��
	static MovingState* GetInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new MovingState();
		}
		return m_instance;
	}
	//���̂̍폜
	static void DeleteInstance() { DELETE_POINTER(m_instance); }

private:
	float m_time;

public:
	void Enter              (Player* player)override;
	PlayerState* HandleInput(Player* player) override;
	void Update             (Player* player) override;
	void Exit               (Player* player) override;



private:
	MovingState(){}
};