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

	// 行列を更新
	m_obj.Update();

	{
		// 判定球の要素を計算
		const Matrix& worldm = m_obj.GetWorld();

		// モデル座標系での中心点
		Vector3 center(0, 0, 0);
		Vector3 right(1, 0, 0);

		// ワールド座標に変換
		center = Vector3::Transform(center, worldm);
		right = Vector3::Transform(right, worldm);

		// 判定球の要素を代入
		Sphere::m_center = center;
		Sphere::m_radius = Vector3::Distance(center, right);
	}
}

void SphereNode::Draw()
{
	m_obj.Render();
}
