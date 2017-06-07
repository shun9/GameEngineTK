// ---------------------------------------
// Brief : ステートパターンのヘッダ
//
// Create: 2017/06/01
//
// Author: Y.Watanabe
// ---------------------------------------
#pragma once

#include "Player.h"

static const float PI = 3.141592;

class PlayerState
{
	public:
		PlayerState(){};

		// 仮想デストラクタ
		virtual ~PlayerState() {}

		// 入口処理
		virtual void Enter(Player* player) = 0;

		// 切り替え処理
		virtual PlayerState* HandleInput(Player* player) = 0;

		// 更新処理
		virtual void Update(Player* player) = 0;

		// 出口処理
		virtual void Exit(Player* player) = 0;

};