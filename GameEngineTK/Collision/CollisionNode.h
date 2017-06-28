//************************************************/
//* @file  :CollisionNode.h
//* @brief :�����蔻��m�[�h
//* @date  :2017/06/19
//* @author:S.Katou
//************************************************/
#pragma once
#include "../Obj3d.h"
namespace ShunLib {
	class CollisionNode{

	protected:
		using Vector3 = DirectX::SimpleMath::Vector3;
		using Matrix = DirectX::SimpleMath::Matrix;

	protected:
		//�f�o�b�O�\���p
		Obj3d m_obj;

		//�e����̃I�t�Z�b�g
		Vector3 m_trans;

	public:
		CollisionNode();
		virtual ~CollisionNode();

		//������
		virtual void Initialize() = 0;

		//�X�V���`��
		virtual void Update() = 0;
		virtual void Draw() = 0;

		/*--[���ݒ�]--*/
		void SetParent(Obj3d* parent) { m_obj.SetParent(parent); }
		void SetTrans(const Vector3& trans) { m_trans = trans; }

	};
}

