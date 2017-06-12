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
#include "FollowCamera.h"
#include "Obj3d.h"
#include "Player\Player.h"
#include "Enemy\Enemy.h"

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

	//�M�~�b�N�p���ꂱ��
	float m_rotation;		//��]�p
	float m_headPos;		//���ʒu�@���ł��p
	int m_bigShieldCnt;		//���Ԃ̃J�E���g�@�h��Ԑ��p
	int m_shieldAttackCnt;	//���Ԃ̃J�E���g�@���U���p
	bool m_isHeadShoot;		//���ł��t���O
	bool m_isBigShield;		//�h��Ԑ��t���O
	bool m_isShieldAttack;	//���U���t���O
	bool m_isShieldGimmic;	//���S�ʃt���O

	std::unique_ptr<Player> m_player;

	//�X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;

	//�e��s��
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	std::unique_ptr<DebugCamera> m_debugCamera;

	std::unique_ptr<DirectX::Model>m_ground;
	std::unique_ptr<Obj3d>m_sky;
	std::unique_ptr<DirectX::EffectFactory>m_effectFactory;
	std::unique_ptr<FollowCamera> m_camera;

	// �G
	std::vector<std::unique_ptr<Enemy>> m_enemies;
};