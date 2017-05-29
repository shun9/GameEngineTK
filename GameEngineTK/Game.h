//
// Game.h
//

#pragma once
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>
#include <Keyboard.h>
#include <vector>
#include "StepTimer.h"
#include "DebugCamera.h"
//#include "Camera.h"
#include "FollowCamera.h"
#include "Obj3d.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:
	enum PLAYER_PARTS
	{
		PLAYER_PARTS_HEAD,	//頭
		PLAYER_PARTS_CANNON,//大砲　
		PLAYER_PARTS_BODY,	//胴体
		PLAYER_PARTS_LEG,	//脚
		PLAYER_PARTS_FOOT,	//足

		PLAYER_PARTS_NUM,	//パーツの数
	};

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

	//キーボード
	std::unique_ptr<DirectX::Keyboard>m_key;

	//ステート
	std::unique_ptr<DirectX::CommonStates> m_states;

	//ロボット関連
	DirectX::SimpleMath::Matrix m_robotWorld;
	DirectX::SimpleMath::Matrix m_robotWorld2;
	DirectX::SimpleMath::Vector3 m_robotPos;

	//向いている方向
	float m_angle;

	//各種行列
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	std::unique_ptr<DebugCamera> m_debugCamera;

	std::unique_ptr<DirectX::Model>m_ground;
	std::unique_ptr<Obj3d>m_sky;
	std::unique_ptr<DirectX::EffectFactory>m_effectFactory;
	std::unique_ptr<FollowCamera> m_camera;
	std::vector<Obj3d>m_robot;
};