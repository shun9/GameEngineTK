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

#include <vector>

#include "../Obj3d.h"
#include "../Collision/SphereNode.h"

class PlayerState;

class Player : public Obj3d{

	protected:
		//ロボット
		std::vector<Obj3d>m_robot;
		std::vector<DirectX::SimpleMath::Vector3>m_robotStartPos;

		// ステート
		PlayerState* m_state;

		// 速度
		DirectX::SimpleMath::Vector3 m_speed;

		// 加速度
		DirectX::SimpleMath::Vector3 m_acceleSpeed;

		//球の当たり判定
		ShunLib::SphereNode m_collisionNodeBullet;

	public:
		enum PARTS
		{
			PIVOT,			    //本体の基点
			SHIELD_PIVOT,	    //盾の基点
			ARM_R_PIVOT,		//右腕の基点
			ARM_L_PIVOT,		//左腕の基点
			PARTS_HEAD,	        //頭
			PARTS_BODYTOP,	    //胴体　上
			PARTS_ARM_R,	    //腕　右
			PARTS_ARM_L,	    //腕　左
			PARTS_HAND_R,	    //手　右
			PARTS_HAND_L,	    //手　左
			PARTS_BODY,	        //胴体
			PARTS_SHIELD_R,	    //盾　右
			PARTS_SHIELD_L,	    //盾　左
			PARTS_LEG,	        //脚
			PARTS_FOOT,	        //足

			PARTS_NUM,	        //パーツの数
		};

public:
		Player();
		virtual ~Player(){}

		// 更新
		void Update();

		// 描画
		void Render();

		/*--[情報取得]--*/
		const DirectX::SimpleMath::Vector3 GetSpeed() { return m_speed; }
		const DirectX::SimpleMath::Vector3 GetAcceleSpeed() { return m_acceleSpeed; }
		const DirectX::SimpleMath::Vector3 GetPartsStartPos(int partsNum) { return m_robotStartPos[partsNum]; }
		Obj3d& GetParts(int num) { return m_robot[num]; }
		const ShunLib::SphereNode& GetBulletCollisionNode() { return m_collisionNodeBullet; }


		/*--[情報設定]--*/
		void SetSpeed(const DirectX::SimpleMath::Vector3& speed){ m_speed = speed; }
		void SetAcceleSpeed(const DirectX::SimpleMath::Vector3& speed) { m_acceleSpeed = speed; }

	private:
		//初期化
		void Init();

public:
	//パーツ情報を直接取得できるように
	Obj3d& operator[](int num) { return m_robot[num]; }
};
