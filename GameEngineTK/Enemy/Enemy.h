/**
*	@file	Enemy.h
*
*	@brief	�G
*
*	@author	���V�@�L��
*/
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <vector>
#include "../Obj3d.h"

#include "../Collision/SphereNode.h"

// ���@
class Enemy
{
public:
	// �p�[�c
	enum PARTS
	{
		PARTS_TOWER,	// ��
		PARTS_BASE,	// ��n
		PARTS_ENGINE_R,	// �E�G���W��
		PARTS_ENGINE_L,	// ���G���W��
		PARTS_FAN,	// ���C��
		PARTS_SCORE,	// ����

		PARTS_NUM
	};

	// �R���X�g���N�^
	Enemy();
	// �f�X�g���N�^
	~Enemy();
	// ������
	void Initialize();
	// ���t���[���X�V
	void Update();
	// �s��̌v�Z
	void Calc();
	// �`��
	void Draw();
	// ���W���擾
	const DirectX::SimpleMath::Vector3& GetTrans();
	const DirectX::SimpleMath::Vector3 & GetRot();
	// ���W��ݒ�
	void SetTrans(const DirectX::SimpleMath::Vector3& trans);
	// ��]��ݒ�
	void SetRot(const DirectX::SimpleMath::Vector3& rot);
	// ���[���h�s����擾
	const DirectX::SimpleMath::Matrix& GetLocalWorld();

	const ShunLib::SphereNode& GetBodyCollisionNode() { return m_collisionNodeBody; }

protected:
	// �����o�ϐ�
	// ���{�b�g�̍\���p�[�c
	std::vector<Obj3d>	m_Obj;
	// �L�[�{�[�h
	DirectX::Keyboard* m_pKeyboard;
	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;

	// ���@�̃M�~�b�N�Ɏg���p�x
	float m_sinAngle;
	// �^�C�}�[
	int m_Timer;
	// �ڕW�p�x
	float m_DistAngle;

	//���̓����蔻��
	ShunLib::SphereNode m_collisionNodeBody;
};

