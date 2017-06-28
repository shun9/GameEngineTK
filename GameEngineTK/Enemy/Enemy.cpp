//--------------------------------------------------------------------------------------
// �t�@�C����: Enemy.cpp
// �쐬��:
// �쐬��:
// ����:
//--------------------------------------------------------------------------------------

#include "Enemy.h"
#include "../KeyBoardManager.h"
#include "../ShunLib/RandomNumber/RandomNumber.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Enemy::Enemy()
{
	m_pKeyboard = KeyBoardManager::GetInstance()->GetKeyBoard();

	m_sinAngle = 0.0f;

	Initialize();
}

Enemy::~Enemy()
{
}

//-----------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------
void Enemy::Initialize()
{
	// ���@�p�[�c�̃��[�h
	m_Obj.resize(PARTS_NUM);
	m_Obj[PARTS_TOWER].LoadModel(L"Resources/tower.cmo");
	m_Obj[PARTS_BASE].LoadModel(L"Resources/base.cmo");
	m_Obj[PARTS_ENGINE_R].LoadModel(L"Resources/engine.cmo");
	m_Obj[PARTS_ENGINE_L].LoadModel(L"Resources/engine.cmo");
	m_Obj[PARTS_FAN].LoadModel(L"Resources/fan.cmo");
	m_Obj[PARTS_SCORE].LoadModel(L"Resources/score.cmo");

	// �e�q�֌W�̍\�z�i�q���ɐe���Z�b�g�j
	m_Obj[PARTS_BASE].SetParent(
		&m_Obj[PARTS_TOWER]);

	m_Obj[PARTS_SCORE].SetParent(
		&m_Obj[PARTS_BASE]);

	m_Obj[PARTS_ENGINE_R].SetParent(
		&m_Obj[PARTS_TOWER]);
	m_Obj[PARTS_ENGINE_L].SetParent(
		&m_Obj[PARTS_TOWER]);

	m_Obj[PARTS_FAN].SetParent(
		&m_Obj[PARTS_TOWER]);

	// �e����̃I�t�Z�b�g�i���[�J���̍��W����j
	m_Obj[PARTS_TOWER].SetScale(
		Vector3(2, 2, 2));

	m_Obj[PARTS_BASE].SetTrans(
		Vector3(0, 0.7f, 0));

	m_Obj[PARTS_SCORE].SetTrans(
		Vector3(0, 1.0f, 0));
	m_Obj[PARTS_SCORE].SetScale(
		Vector3(2, 2, 2));

	m_Obj[PARTS_ENGINE_R].SetTrans(
		Vector3(0.22f, 0.3f, 0.22f));
	m_Obj[PARTS_ENGINE_R].SetAngle(
		Vector3(0, XMConvertToRadians(45), 0));

	m_Obj[PARTS_ENGINE_L].SetTrans(
		Vector3(-0.22f, 0.3f, 0.22f));
	m_Obj[PARTS_ENGINE_L].SetAngle(
		Vector3(0, XMConvertToRadians(-45), 0));

	m_Obj[PARTS_FAN].SetTrans(
		Vector3(0, 0.3f, 1.0f));


	{
		//���퓖���蔻�菉����
		m_collisionNodeBody.Initialize();

		//����ɓ����蔻���ݒ�
		m_collisionNodeBody.SetParent(&m_Obj[0]);

		// ����p�[�c����̃I�t�Z�b�g
		m_collisionNodeBody.SetTrans(Vector3(0, 0, 0));

		// �����蔻��̔��a
		m_collisionNodeBody.SetLocalRadius(1.0f);
	}


	// �������W�������_���Ɍ���
	Vector3 pos;

	ShunLib::RandomNumber rn;

	pos.x = rn(-10.0f,10.0f);
	pos.z = rn(-10.0f,10.0f);

	SetTrans(pos);

	m_Timer = 0;
	m_DistAngle = 0;

}

//-----------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------
void Enemy::Update()
{
	Keyboard::State keystate = m_pKeyboard->GetState();
	m_KeyboardTracker.Update(keystate);

	// ���@�p�[�c�̃M�~�b�N
	{
		// ���@�̊p�x��ϓ�
		Vector3 angle;

		angle = m_Obj[PARTS_SCORE].GetAngle();
		m_Obj[PARTS_SCORE].SetAngle(
			angle + Vector3(0.2f, 0.1f, 0));

		// �T�C���̈����̊p�x�����񂾂񑝂���
		m_sinAngle += 0.1f;
		// �t�@���̊p�x���������肫���肷��(-1�`+1)
		float fan_angle = sinf(m_sinAngle) * 3.0f;
		/*m_Obj[PLAYER_PARTS_FAN].SetRotation(
		Vector3(0, 0, fan_angle));*/
		//m_Obj[PARTS_FAN].SetTranslation(
		//	Vector3(sinf(m_sinAngle), 0, cosf(m_sinAngle)*3.0f));
	}

	m_Timer--;
	if (m_Timer < 0)
	{
		// �ڕW�p�x�̍Ē��I
		m_Timer = 60;
		// -0.5�`+0.5�̗���
		float rnd = (float)rand() / RAND_MAX - 0.5f;
		// -90�`+90�̗���
		rnd *= 180.0f;

		rnd = XMConvertToRadians(rnd);

		m_DistAngle += rnd;
	}

	{
		// ���@�̊p�x��ϓ�
		Vector3 rot = GetRot();

		float angle = m_DistAngle - rot.y;

		if (angle > XM_PI)
		{
			angle -= XM_2PI;
		}
		if (angle < -XM_PI)
		{
			angle += XM_2PI;
		}

		rot.y += angle *0.05f;

		SetRot(rot);
	}

	// �@�̂̌����Ă�������ɑO�i
	{
		// �ړ��x�N�g��
		Vector3 moveV(0, 0, -0.1f);
		// ���̊p�x�ɍ��킹�Ĉړ��x�N�g������]
		// ��]�s��
		float angle = m_Obj[0].GetAngle().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// ���@�̍��W���ړ�
		Vector3 pos = m_Obj[0].GetTrans();
		pos += moveV;
		m_Obj[0].SetTrans(pos);
	}

	// �s��X�V
	Calc();
	m_collisionNodeBody.Update();
}

//-----------------------------------------------------------------------------
// �s��X�V
//-----------------------------------------------------------------------------
void Enemy::Calc()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin();
		it != m_Obj.end();
		it++)
	{
		it->Update();
	}

}

//-----------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------
void Enemy::Draw()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin();
		it != m_Obj.end();
		it++)
	{
		it->Render();
	}
	//m_collisionNodeBody.Draw();
}

const DirectX::SimpleMath::Vector3& Enemy::GetTrans()
{
	// �^���N�p�[�c�̍��W��Ԃ�
	return m_Obj[0].GetTrans();
}

const DirectX::SimpleMath::Vector3& Enemy::GetRot()
{
	// �^���N�p�[�c�̍��W��Ԃ�
	return m_Obj[0].GetAngle();
}

void Enemy::SetTrans(const DirectX::SimpleMath::Vector3& trans)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_Obj[0].SetTrans(trans);
}

void Enemy::SetRot(const DirectX::SimpleMath::Vector3& rot)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_Obj[0].SetAngle(rot);
}

const DirectX::SimpleMath::Matrix& Enemy::GetLocalWorld()
{
	// �^���N�p�[�c�̃��[���h�s���Ԃ�
	return (m_Obj[0].GetWorld());
}
