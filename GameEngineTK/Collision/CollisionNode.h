//************************************************/
//* @file  :CollisionNode.h
//* @brief :当たり判定ノード
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
		//デバッグ表示用
		Obj3d m_obj;

		//親からのオフセット
		Vector3 m_trans;

	public:
		CollisionNode();
		virtual ~CollisionNode();

		//初期化
		virtual void Initialize() = 0;

		//更新＆描画
		virtual void Update() = 0;
		virtual void Draw() = 0;

		/*--[情報設定]--*/
		void SetParent(Obj3d* parent) { m_obj.SetParent(parent); }
		void SetTrans(const Vector3& trans) { m_trans = trans; }

	};
}

