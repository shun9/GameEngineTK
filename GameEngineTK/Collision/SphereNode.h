//************************************************/
//* @file  :SphereNode.h
//* @brief :���̓����蔻��p�N���X
//* @date  :2017/06/19
//* @author:S.Katou
//************************************************/
#pragma once
#include "Collision.h"
#include "CollisionNode.h"

namespace ShunLib{
	class SphereNode : public Sphere, public CollisionNode{

	protected:
		//���[�J�����a
		float m_localRadius;

	public:
		SphereNode();
		~SphereNode();

		//������
		void Initialize();

		//�X�V���`��
		void Update();
		void Draw();

		/*--[���ݒ�]--*/
		void SetLocalRadius(float radius) { m_localRadius = radius; }
	};
}
