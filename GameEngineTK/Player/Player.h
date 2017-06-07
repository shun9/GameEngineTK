#pragma once

#include <windows.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <DirectXColors.h>
#include <WICTextureLoader.h>
#include <algorithm>
#include <Memory>

#include <Keyboard.h>

#include "../Obj3d.h"
#include <vector>

class PlayerState;

class Player : public Obj3d
{
	protected:
		//���{�b�g
		std::vector<Obj3d>m_robot;
		std::vector<DirectX::SimpleMath::Vector3>m_robotStartPos;

		// �X�e�[�g
		PlayerState* m_state;

		// ���x
		DirectX::SimpleMath::Vector3 m_speed;

		// �����x
		DirectX::SimpleMath::Vector3 m_acceleSpeed;

	public:
		enum PARTS
		{
			PIVOT,			    //�{�̂̊�_
			SHIELD_PIVOT,	    //���̊�_
			ARM_R_PIVOT,		//�E�r�̊�_
			ARM_L_PIVOT,		//���r�̊�_
			PARTS_HEAD,	        //��
			PARTS_BODYTOP,	    //���́@��
			PARTS_ARM_R,	    //�r�@�E
			PARTS_ARM_L,	    //�r�@��
			PARTS_HAND_R,	    //��@�E
			PARTS_HAND_L,	    //��@��
			PARTS_BODY,	        //����
			PARTS_SHIELD_R,	    //���@�E
			PARTS_SHIELD_L,	    //���@��
			PARTS_LEG,	        //�r
			PARTS_FOOT,	        //��

			PARTS_NUM,	        //�p�[�c�̐�
		};
public:
		Player();
		virtual ~Player(){}

		// �X�V
		void Update();

		// �`��
		void Render();

		// getter =====
		// ���x�̎擾
		const DirectX::SimpleMath::Vector3 GetSpeed() { return m_speed; }

		// �����x�̎擾
		const DirectX::SimpleMath::Vector3 GetAcceleSpeed() { return m_acceleSpeed; }

		const DirectX::SimpleMath::Vector3 GetPartsStartPos(int partsNum) { return m_robotStartPos[partsNum]; }

		Obj3d& GetParts(int num) { return m_robot[num]; }

		// setter =====

		// ���x�̐ݒ�
		void SetSpeed(const DirectX::SimpleMath::Vector3& speed){ m_speed = speed; }

		// �����x�̐ݒ�
		void SetAcceleSpeed(const DirectX::SimpleMath::Vector3& speed) { m_acceleSpeed = speed; }

	private:
		void Init();

public:
	Obj3d& operator[](int num) { return m_robot[num]; }
};
