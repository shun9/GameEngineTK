#include "SphereNode.h"

using namespace ShunLib;

SphereNode::SphereNode():
	m_localRadius(1.0f)
{

}

SphereNode::~SphereNode()
{

}

void SphereNode::Initialize()
{
	m_obj.LoadModel(L"Resources\\SphereNode.cmo");
}

void SphereNode::Update()
{
	m_obj.SetTrans(m_trans);
	m_obj.SetScale(Vector3(m_localRadius));

	// �s����X�V
	m_obj.Update();

	{
		// ���苅�̗v�f���v�Z
		const Matrix& worldm = m_obj.GetWorld();

		// ���f�����W�n�ł̒��S�_
		Vector3 center(0, 0, 0);
		Vector3 right(1, 0, 0);

		// ���[���h���W�ɕϊ�
		center = Vector3::Transform(center, worldm);
		right = Vector3::Transform(right, worldm);

		// ���苅�̗v�f����
		Sphere::m_center = center;
		Sphere::m_radius = Vector3::Distance(center, right);
	}
}

void SphereNode::Draw()
{
	m_obj.Render();
}
