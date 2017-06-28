//************************************************/
//* @file  :Collision.h
//* @brief :衝突判定ライブラリ
//* @date  :2017/06/15
//* @author:S.Katou
//************************************************/
#include "Collision.h"
using namespace ShunLib;

/// <summary>
/// 球と球の当たり判定
/// </summary>
/// <param name="A">球１</param>
/// <param name="B">球２</param>
/// <returns>true : 当たっている</returns>
/// <returns>false: 当たっていない</returns>
bool ShunLib::CheckSphere2Sphere(const Sphere& A, const Sphere& B)
{
	//中心座標間の差
	auto sub = B.m_center - A.m_center;

	//中心座標間の距離
	float distance = sub.x*sub.x + sub.y*sub.y + sub.z*sub.z;

	//距離が半径の和より大きければ、当たっていない
	float radius = A.m_radius + B.m_radius;
	radius = radius*radius;

	if (distance > radius)
	{
		return false;
	}
	return true;
}

