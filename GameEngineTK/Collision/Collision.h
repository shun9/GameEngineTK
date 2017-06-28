//************************************************/
//* @file  :Collision.h
//* @brief :衝突判定ライブラリ
//* @date  :2017/06/15
//* @author:S.Katou
//************************************************/
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>
namespace ShunLib
{
	/// <summary>
	/// 球体クラス
	/// </summary>
	class Sphere
	{
	public:
		//中心座標
		DirectX::SimpleMath::Vector3 m_center;

		//半径
		float m_radius;

	public:
		Sphere() :m_radius(1.0f) {}
	};

	/// <summary>
	/// 線分クラス
	/// </summary>
	class Segment
	{
	public:
		//線分開始点
		DirectX::SimpleMath::Vector3 m_start;

		//線分終了点
		DirectX::SimpleMath::Vector3 m_end;
	};

	/// <summary>
	/// 球と球の当たり判定
	/// </summary>
	/// <param name="A">球１</param>
	/// <param name="B">球２</param>
	/// <returns>true : 当たっている</returns>
	/// <returns>false: 当たっていない</returns>
	bool CheckSphere2Sphere(const Sphere& A, const Sphere& B);
}
