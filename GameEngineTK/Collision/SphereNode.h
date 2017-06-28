//************************************************/
//* @file  :SphereNode.h
//* @brief :球の当たり判定用クラス
//* @date  :2017/06/19
//* @author:S.Katou
//************************************************/
#pragma once
#include "Collision.h"
#include "CollisionNode.h"

namespace ShunLib{
	class SphereNode : public Sphere, public CollisionNode{

	protected:
		//ローカル半径
		float m_localRadius;

	public:
		SphereNode();
		~SphereNode();

		//初期化
		void Initialize();

		//更新＆描画
		void Update();
		void Draw();

		/*--[情報設定]--*/
		void SetLocalRadius(float radius) { m_localRadius = radius; }
	};
}
