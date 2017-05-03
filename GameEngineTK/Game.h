//
// Game.h
//

#pragma once
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>
#include "StepTimer.h"
#include "DebugCamera.h"
#include <WICTextureLoader.h>

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;

private:

	//�e��s��
	DirectX::SimpleMath::Matrix m_world;	
	DirectX::SimpleMath::Matrix m_view;				
	DirectX::SimpleMath::Matrix m_proj;

	std::unique_ptr<DebugCamera> m_camera;

	//���f��
	std::unique_ptr<DirectX::Model>m_ground;
	std::unique_ptr<DirectX::Model>m_sky;
	std::unique_ptr<DirectX::Model>m_teapot;
	std::unique_ptr<DirectX::EffectFactory>m_effectFactory;

	DirectX::SimpleMath::Matrix m_teapotWorld[20];
	DirectX::SimpleMath::Vector3 m_teapotFirstPos[20];

	//�X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;

private:
	DirectX::SimpleMath::Vector3 Lerp(DirectX::SimpleMath::Vector3 startPosition, DirectX::SimpleMath::Vector3 targetPosition, float t);
	float Linearity(float time);

};