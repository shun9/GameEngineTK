//************************************************/
//* @file  :Obj3d.cpp
//* @brief :三次元オブジェクトのクラス
//* @date  :2017/05/22
//* @author:S.Katou
//************************************************/
#include "Obj3d.h"

Camera* Obj3d::m_camera;

std::unique_ptr<DirectX::CommonStates>Obj3d::m_state;
std::unique_ptr<DirectX::EffectFactory>Obj3d::m_effectFactory;

Microsoft::WRL::ComPtr<ID3D11Device>            Obj3d::m_d3dDevice;
Microsoft::WRL::ComPtr<ID3D11DeviceContext>     Obj3d::m_d3dContext;

using namespace DirectX;

void Obj3d::InitStatic(Camera * camera, Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext)
{
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;

	//エフェクトファクトリー生成
	m_effectFactory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	m_effectFactory->SetDirectory(L"Resources");
	m_state = std::make_unique<CommonStates>(m_d3dDevice.Get());

	m_camera = camera;
}

Obj3d::Obj3d():
	m_parent(nullptr),
	m_scale(SimpleMath::Vector3(1.0f,1.0f,1.0f))
{
}

//Obj3d::~Obj3d()
//{
//}

void Obj3d::Update()
{
	using namespace SimpleMath;

	//回転行列
	Matrix scale = Matrix::CreateScale(m_scale);

	//回転行列
	Matrix rotateZ = Matrix::CreateRotationZ(m_angle.z);
	Matrix rotateX= Matrix::CreateRotationX(m_angle.x);
	Matrix rotateY = Matrix::CreateRotationY(m_angle.y);
	Matrix rotate = rotateZ* rotateX* rotateY;

	//平行移動行列
	Matrix trance = Matrix::CreateTranslation(m_trance);

	m_world = scale	* rotate * trance;

	//親がいる場合
	if (m_parent != nullptr)
	{
		m_world *= m_parent->GetWorld();
	}
}

void Obj3d::Render()
{
	if (m_model != nullptr)
	{
		m_model->Draw(m_d3dContext.Get(), *m_state, m_world, m_camera->GetView(), m_camera->GetProj());
	}
}


void Obj3d::LoadModel(const wchar_t* path)
{
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), path, *m_effectFactory);
}
