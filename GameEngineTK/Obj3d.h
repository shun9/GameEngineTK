//************************************************/
//* @file  :Obj3d.h
//* @brief :�O�����I�u�W�F�N�g�̃N���X
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
	//�ÓI�����o�[�̏�����
	static void InitStatic(Camera* camera,
		Microsoft::WRL::ComPtr<ID3D11Device>d3dDevice,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>d3dContext);

private:
	//���f���|�C���^
	std::unique_ptr<DirectX::Model>m_model;

	//���[���h���W
	DirectX::SimpleMath::Matrix m_world;

	//�ړ��p�x�N�g��
	DirectX::SimpleMath::Vector3 m_trance;

	//��]�p�x�N�g��
	DirectX::SimpleMath::Vector3 m_angle;

	//�g�嗦
	DirectX::SimpleMath::Vector3 m_scale;

	//�e�ƂȂ�3d�I�u�W�F�N�g�̃|�C���^
	Obj3d* m_parent;

public:
	Obj3d();
	//~Obj3d();

	void Update();
	void Render();

	void LoadModel(const wchar_t* path);
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	void SetTrans(const DirectX::SimpleMath::Vector3& trance) { m_trance = trance; }
	void SetAngle(const DirectX::SimpleMath::Vector3& angle) { m_angle = angle; }
	void SetParent(Obj3d* parent) { m_parent = parent; }

	DirectX::SimpleMath::Matrix GetWorld() { return m_world; }
	const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; }
	const DirectX::SimpleMath::Vector3& GetTrans() { return m_trance; }
	const DirectX::SimpleMath::Vector3& GetAngle() { return m_angle; }
	const Obj3d* GetParent() { return m_parent; }

};