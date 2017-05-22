//************************************************/
//* @file  :Obj3d.h
//* @brief :三次元オブジェクトのクラス
//* @date  :2017/05/22
//* @author:S.Katou
//************************************************/
#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include <Model.h>
#include "Camera.h"
#include <CommonStates.h>
#include <Effects.h>

class Obj3d
{
private:
	static Camera* m_camera;

	static std::unique_ptr<DirectX::CommonStates>m_state;
	static std::unique_ptr<DirectX::EffectFactory>m_effectFactory;

	static Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;

public:
	//静的メンバーの初期化
	static void InitStatic(Camera* camera,
		Microsoft::WRL::ComPtr<ID3D11Device>d3dDevice, 
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>d3dContext);

private:
	std::unique_ptr<DirectX::Model>m_model;
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Vector3 m_trance;
	DirectX::SimpleMath::Vector3 m_angle;
	float m_scale;

	//親となる3dオブジェクトのポインタ
	Obj3d* m_parent;

public:
	Obj3d();
	~Obj3d();

	void Update();
	void Render();

	void LoadModel(const wchar_t* path);
	DirectX::SimpleMath::Matrix GetWorld() { return m_world; }
	void SetScale(float scale) { m_scale = scale; }
	void SetTrance(float scale) { m_scale = scale; }
	void SetAngle(float scale) { m_scale = scale; }
};