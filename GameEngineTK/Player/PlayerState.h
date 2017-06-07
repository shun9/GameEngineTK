// ---------------------------------------
// Brief : �X�e�[�g�p�^�[���̃w�b�_
//
// Create: 2017/06/01
//
// Author: Y.Watanabe
// ---------------------------------------
#pragma once

#include "Player.h"

static const float PI = 3.141592;

class PlayerState
{
	public:
		PlayerState(){};

		// ���z�f�X�g���N�^
		virtual ~PlayerState() {}

		// ��������
		virtual void Enter(Player* player) = 0;

		// �؂�ւ�����
		virtual PlayerState* HandleInput(Player* player) = 0;

		// �X�V����
		virtual void Update(Player* player) = 0;

		// �o������
		virtual void Exit(Player* player) = 0;

};