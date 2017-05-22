//************************************************/
//* @file  :Obj3d.cpp
//* @brief :三次元オブジェクトのクラス
//* @date  :2017/05/22
//* @author:S.Katou
//************************************************/
#include "Obj3d.h"

Camera* m_camera;

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

}

Obj3d::Obj3d()
{
}

Obj3d::~Obj3d()
{
}

void Obj3d::LoadModel(const wchar_t* path)
{
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), path, *m_effectFactory);
}
