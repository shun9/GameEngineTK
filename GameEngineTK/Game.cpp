//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

//コンストラクタ
Game::Game() :
    m_window(0),
    m_outputWidth(800),
    m_outputHeight(600),
    m_featureLevel(D3D_FEATURE_LEVEL_9_1)
{
}

// Initialize the Direct3D resources required to run.
//初期化
void Game::Initialize(HWND window, int width, int height)
{
    m_window = window;
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateDevice();

    CreateResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */
	/*--以下に記述--*/
	//カメラ生成
	m_key = std::make_unique<Keyboard>();
	m_camera = std::make_unique<FollowCamera>();
	m_camera->SetKeyboard(m_key.get());

	Obj3d::InitStatic(m_camera.get(), m_d3dDevice, m_d3dContext);


	//行列初期化
	m_view = Matrix::CreateLookAt(Vector3(3.f, 3.f, 3.5f),
		Vector3::Zero, Vector3::UnitY);
	m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
		float(m_outputWidth) / float(m_outputHeight), 0.1f, 1000.0f);
	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());

	//カメラ生成
	m_debugCamera = std::make_unique<DebugCamera>(m_outputWidth, m_outputHeight);

	//エフェクトファクトリー生成
	m_effectFactory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	m_effectFactory->SetDirectory(L"Resources");

	m_ground = Model::CreateFromCMO(m_d3dDevice.Get(), L"Resources\\Ground200.cmo", *m_effectFactory);
	m_sky = std::make_unique<Obj3d>();
	m_sky->LoadModel(L"Resources\\Sky1.cmo");

	//ギミック用あれこれ
	m_rotation = 1.0f;
	m_headPos = 0.0f;
	m_bigShieldCnt = 0;
	m_shieldAttackCnt = 0;
	m_isHeadShoot = false;
	m_isBigShield = false;
	m_isShieldAttack = false;
	m_isShieldGimmic = false;

	//ロボットの生成
	m_robot.resize(PLAYER_PARTS_NUM);
	m_robot[PLAYER_PARTS_HEAD]    .LoadModel(L"Resources\\Head.cmo"        );
	m_robot[PLAYER_PARTS_BODYTOP] .LoadModel(L"Resources\\BodyTop.cmo"     );
	m_robot[PLAYER_PARTS_BODY]    .LoadModel(L"Resources\\Body.cmo");
	m_robot[PLAYER_PARTS_ARM_R]   .LoadModel(L"Resources\\Arm.cmo");
	m_robot[PLAYER_PARTS_ARM_L]   .LoadModel(L"Resources\\Arm.cmo");
	m_robot[PLAYER_PARTS_HAND_R]  .LoadModel(L"Resources\\Hand.cmo");
	m_robot[PLAYER_PARTS_HAND_L]  .LoadModel(L"Resources\\Hand.cmo");
	m_robot[PLAYER_PARTS_SHIELD_R].LoadModel(L"Resources\\Shield.cmo"      );
	m_robot[PLAYER_PARTS_SHIELD_L].LoadModel(L"Resources\\Shield.cmo"      );
	m_robot[PLAYER_PARTS_LEG]     .LoadModel(L"Resources\\Leg.cmo"         );
	m_robot[PLAYER_PARTS_FOOT]    .LoadModel(L"Resources\\Foot.cmo"        );


	//親の設定
	m_robot[PLAYER_SHIELD_PIVOT]  .SetParent(&m_robot[PLAYER_PIVOT]);
	m_robot[PLAYER_ARM_R_PIVOT]   .SetParent(&m_robot[PLAYER_PARTS_BODYTOP]);
	m_robot[PLAYER_ARM_L_PIVOT]   .SetParent(&m_robot[PLAYER_PARTS_BODYTOP]);
	m_robot[PLAYER_PARTS_HEAD]    .SetParent(&m_robot[PLAYER_PARTS_BODY]);
	m_robot[PLAYER_PARTS_BODYTOP] .SetParent(&m_robot[PLAYER_PARTS_BODY]   );
	m_robot[PLAYER_PARTS_BODY]    .SetParent(&m_robot[PLAYER_PIVOT]);
	m_robot[PLAYER_PARTS_ARM_R]   .SetParent(&m_robot[PLAYER_ARM_R_PIVOT]);
	m_robot[PLAYER_PARTS_ARM_L]   .SetParent(&m_robot[PLAYER_ARM_L_PIVOT]);
	m_robot[PLAYER_PARTS_HAND_R]  .SetParent(&m_robot[PLAYER_PARTS_ARM_R]);
	m_robot[PLAYER_PARTS_HAND_L]  .SetParent(&m_robot[PLAYER_PARTS_ARM_L]);
	m_robot[PLAYER_PARTS_SHIELD_R].SetParent(&m_robot[PLAYER_SHIELD_PIVOT] );
	m_robot[PLAYER_PARTS_SHIELD_L].SetParent(&m_robot[PLAYER_SHIELD_PIVOT] );
	m_robot[PLAYER_PARTS_LEG]     .SetParent(&m_robot[PLAYER_PARTS_BODY]   );
	m_robot[PLAYER_PARTS_FOOT]    .SetParent(&m_robot[PLAYER_PARTS_LEG]    );


	//位置の設定
	m_robot[PLAYER_SHIELD_PIVOT]  .SetTrans(Vector3(0.0f, 0.0f, 0.0f       ));
	m_robot[PLAYER_ARM_R_PIVOT]   .SetTrans(Vector3(0.2f, 0.2f, 0.05f));
	m_robot[PLAYER_ARM_L_PIVOT]   .SetTrans(Vector3(-0.2f, 0.2f, 0.05f));
	m_robot[PLAYER_PARTS_HEAD]    .SetTrans(Vector3(0.0f, 0.72f,0.1f       ));
	m_robot[PLAYER_PARTS_BODYTOP] .SetTrans(Vector3(0.0f, 0.37f,0.0f       ));
	m_robot[PLAYER_PARTS_BODY]    .SetTrans(Vector3(0.0f, 0.5f, 0.0f));
	m_robot[PLAYER_PARTS_ARM_R]   .SetTrans(Vector3(0.0f, 0.0f, 0.0f));
	m_robot[PLAYER_PARTS_ARM_L]   .SetTrans(Vector3(0.0f, 0.0f, 0.0f));
	m_robot[PLAYER_PARTS_HAND_R]  .SetTrans(Vector3(0.0f, 0.55f, 0.51f));
	m_robot[PLAYER_PARTS_HAND_L]  .SetTrans(Vector3(0.0f, 0.55f, 0.51f));
	m_robot[PLAYER_PARTS_SHIELD_R].SetTrans(Vector3(0.8f, 0.6f, 0.0f       ));
	m_robot[PLAYER_PARTS_SHIELD_L].SetTrans(Vector3(-0.8f,0.6f, 0.0f       ));
	m_robot[PLAYER_PARTS_LEG]     .SetTrans(Vector3(0.0f, -0.2f,0.02f      ));
	m_robot[PLAYER_PARTS_FOOT]    .SetTrans(Vector3(0.0f, -0.25f, 0.0f     ));


	//拡大率設定
	m_robot[PLAYER_SHIELD_PIVOT]  .SetScale(Vector3(1.2f, 1.2f, 1.2f       ));
	m_robot[PLAYER_PARTS_HEAD]    .SetScale(Vector3(1.6f, 2.0f, 1.6f       ));
	m_robot[PLAYER_PARTS_BODYTOP] .SetScale(Vector3(1.0f, 0.9f, 1.0f       ));
	m_robot[PLAYER_PARTS_BODY]    .SetScale(Vector3(1.5f, 1.5f, 1.5f       ));
	m_robot[PLAYER_PARTS_SHIELD_R].SetScale(Vector3(1.0f, 1.0f, 1.0f       ));
	m_robot[PLAYER_PARTS_SHIELD_L].SetScale(Vector3(1.0f, 1.0f, 1.0f       ));
	m_robot[PLAYER_PARTS_LEG]     .SetScale(Vector3(1.0f, 1.0f, 1.0f       ));
	m_robot[PLAYER_PARTS_FOOT]    .SetScale(Vector3(0.7f, 0.7f, 0.7f       ));


	//角度設定
	m_robot[PLAYER_PARTS_HEAD]    .SetAngle(Vector3(20.0f, 0.0f, 0.0f      ));
	m_robot[PLAYER_PARTS_BODYTOP] .SetAngle(Vector3(-5.0f, 0.0f, 0.0f      ));
	m_robot[PLAYER_PARTS_SHIELD_L].SetAngle(Vector3(0.0f, 180.0f, 0.0f     ));
	m_robot[PLAYER_PARTS_ARM_R].SetAngle(Vector3(150.0f, 0.0f, -10.0f));
	m_robot[PLAYER_PARTS_ARM_L].SetAngle(Vector3(150.0f, 0.0f, 10.0f));
	m_robot[PLAYER_PARTS_HAND_R].SetAngle(Vector3(135.0f, 0.0f, 0.0f));
	m_robot[PLAYER_PARTS_HAND_L].SetAngle(Vector3(135.0f, 0.0f, 0.0f));

	//初期位置を保存しておく
	std::vector<Obj3d>::iterator robotItr;
	for (robotItr = m_robot.begin(); robotItr != m_robot.end(); robotItr++)
	{
		m_robotStartPos.push_back(Vector3((*robotItr).GetTrans()));
	}
}

// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });
	Render();
}


// Updates the world.
//更新
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
	/*--以下に記述--*/
	elapsedTime;

	m_robot[0].GetAngle();
	//カメラ更新
	m_camera->SetTargetPos(m_robot[0].GetTrans());
	//m_camera->SetAngle(XMConvertToRadians(m_robot[0].GetAngle().y));
	m_camera->SetAngle(0.0f);
	m_camera->Update();

	m_sky->Update();

	//行列設定
	m_view = m_camera->GetView();
	m_proj = m_camera->GetProj();


	auto kb = m_key->GetState();

	//ロボットのギミック
	GimmicRobot();

	//移動距離
	float length = 0.1f;
	Vector3 spd(sin(XMConvertToRadians(m_robot[0].GetAngle().y))*length, 0.0f, cos(XMConvertToRadians(m_robot[0].GetAngle().y))*length);
	Vector3 pos = m_robot[0].GetTrans();
	Vector3 angle = m_robot[0].GetAngle();
	if (kb.W) { m_robot[0].SetTrans(pos - spd); }
	if (kb.S) { m_robot[0].SetTrans(pos + spd); }
	if (kb.A) { m_robot[0].SetAngle(angle + Vector3::UnitY); }
	if (kb.D) { m_robot[0].SetAngle(angle - Vector3::UnitY); }

	std::vector<Obj3d>::iterator robotItr;
	for (robotItr = m_robot.begin(); robotItr != m_robot.end(); robotItr++)
	{
		(*robotItr).Update();
	}
}


// Draws the scene.
//描画
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    // TODO: Add your rendering code here.
	/*--以下に記述--*/
	Matrix world = Matrix::CreateTranslation(Vector3(0.0f, -1.0f, 0.0f));
	m_ground->Draw(m_d3dContext.Get(), *m_states, world, m_view, m_proj);

	m_sky->Render();

	for (int i = 0; i < PLAYER_PARTS_NUM; i++)
	{
		m_robot[i].Render();
	}


    Present();
}

// Helper method to clear the back buffers.
//画面を塗りつぶす
void Game::Clear()
{
    // Clear the views.
    m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);
    m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

    // Set the viewport.
    CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
    m_d3dContext->RSSetViewports(1, &viewport);
}

// Presents the back buffer contents to the screen.
//描画命令を実行
void Game::Present()
{
    // The first argument instructs DXGI to block until VSync, putting the application
    // to sleep until the next VSync. This ensures we don't waste any cycles rendering
    // frames that will never be displayed to the screen.
    HRESULT hr = m_swapChain->Present(1, 0);

    // If the device was reset we must completely reinitialize the renderer.
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
    {
        OnDeviceLost();
    }
    else
    {
        DX::ThrowIfFailed(hr);
    }
}

// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    m_outputWidth = std::max(width, 1);
    m_outputHeight = std::max(height, 1);

    CreateResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}

// These are the resources that depend on the device.
void Game::CreateDevice()
{
    UINT creationFlags = 0;

#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    static const D3D_FEATURE_LEVEL featureLevels [] =
    {
        // TODO: Modify for supported Direct3D feature levels (see code below related to 11.1 fallback handling).
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    // Create the DX11 API device object, and get a corresponding context.
    HRESULT hr = D3D11CreateDevice(
        nullptr,                                // specify nullptr to use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        featureLevels,
        _countof(featureLevels),
        D3D11_SDK_VERSION,
        m_d3dDevice.ReleaseAndGetAddressOf(),   // returns the Direct3D device created
        &m_featureLevel,                        // returns feature level of device created
        m_d3dContext.ReleaseAndGetAddressOf()   // returns the device immediate context
        );

    if (hr == E_INVALIDARG)
    {
        // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it.
        hr = D3D11CreateDevice(nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            creationFlags,
            &featureLevels[1],
            _countof(featureLevels) - 1,
            D3D11_SDK_VERSION,
            m_d3dDevice.ReleaseAndGetAddressOf(),
            &m_featureLevel,
            m_d3dContext.ReleaseAndGetAddressOf()
            );
    }

    DX::ThrowIfFailed(hr);

#ifndef NDEBUG
    ComPtr<ID3D11Debug> d3dDebug;
    if (SUCCEEDED(m_d3dDevice.As(&d3dDebug)))
    {
        ComPtr<ID3D11InfoQueue> d3dInfoQueue;
        if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
        {
#ifdef _DEBUG
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
            D3D11_MESSAGE_ID hide [] =
            {
                D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
                // TODO: Add more message IDs here as needed.
            };
            D3D11_INFO_QUEUE_FILTER filter = {};
            filter.DenyList.NumIDs = _countof(hide);
            filter.DenyList.pIDList = hide;
            d3dInfoQueue->AddStorageFilterEntries(&filter);
        }
    }
#endif

    // DirectX 11.1 if present
    if (SUCCEEDED(m_d3dDevice.As(&m_d3dDevice1)))
        (void)m_d3dContext.As(&m_d3dContext1);

    // TODO: Initialize device dependent objects here (independent of window size).
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateResources()
{
    // Clear the previous window size specific context.
    ID3D11RenderTargetView* nullViews [] = { nullptr };
    m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
    m_renderTargetView.Reset();
    m_depthStencilView.Reset();
    m_d3dContext->Flush();

    UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
    UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
    DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    UINT backBufferCount = 2;

    // If the swap chain already exists, resize it, otherwise create one.
    if (m_swapChain)
    {
        HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

        if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
        {
            // If the device was removed for any reason, a new device and swap chain will need to be created.
            OnDeviceLost();

            // Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method
            // and correctly set up the new device.
            return;
        }
        else
        {
            DX::ThrowIfFailed(hr);
        }
    }
    else
    {
        // First, retrieve the underlying DXGI Device from the D3D Device.
        ComPtr<IDXGIDevice1> dxgiDevice;
        DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

        // Identify the physical adapter (GPU or card) this device is running on.
        ComPtr<IDXGIAdapter> dxgiAdapter;
        DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

        // And obtain the factory object that created it.
        ComPtr<IDXGIFactory1> dxgiFactory;
        DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

        ComPtr<IDXGIFactory2> dxgiFactory2;
        if (SUCCEEDED(dxgiFactory.As(&dxgiFactory2)))
        {
            // DirectX 11.1 or later

            // Create a descriptor for the swap chain.
            DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
            swapChainDesc.Width = backBufferWidth;
            swapChainDesc.Height = backBufferHeight;
            swapChainDesc.Format = backBufferFormat;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferCount = backBufferCount;

            DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = { 0 };
            fsSwapChainDesc.Windowed = TRUE;

            // Create a SwapChain from a Win32 window.
            DX::ThrowIfFailed(dxgiFactory2->CreateSwapChainForHwnd(
                m_d3dDevice.Get(),
                m_window,
                &swapChainDesc,
                &fsSwapChainDesc,
                nullptr,
                m_swapChain1.ReleaseAndGetAddressOf()
                ));

            DX::ThrowIfFailed(m_swapChain1.As(&m_swapChain));
        }
        else
        {
            DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
            swapChainDesc.BufferCount = backBufferCount;
            swapChainDesc.BufferDesc.Width = backBufferWidth;
            swapChainDesc.BufferDesc.Height = backBufferHeight;
            swapChainDesc.BufferDesc.Format = backBufferFormat;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.OutputWindow = m_window;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;
            swapChainDesc.Windowed = TRUE;

            DX::ThrowIfFailed(dxgiFactory->CreateSwapChain(m_d3dDevice.Get(), &swapChainDesc, m_swapChain.ReleaseAndGetAddressOf()));
        }

        // This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
        DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
    }

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

    m_depthStencilView.Reset();
    m_renderTargetView.Reset();
    m_swapChain1.Reset();
    m_swapChain.Reset();
    m_d3dContext1.Reset();
    m_d3dContext.Reset();
    m_d3dDevice1.Reset();
    m_d3dDevice.Reset();

    CreateDevice();

    CreateResources();
}

//ロボットギミック
void Game::GimmicRobot()
{
	//通常時のギミック
	NormalState();

	//Zキーで頭飛ばし
	HeadShoot();

	//Xキーで防御態勢
	BigShield();

	//Cキーで盾攻撃
	ShieldAttack();
}

//通常時のギミック
void Game::NormalState()
{
	auto kb = m_key->GetState();

	//本体が回転しているときの調整用倍率
	float magnification = 1.0f;
	if (kb.A) { magnification = 0.5f; }
	if (kb.D) { magnification = 2.0f; }
	m_rotation = magnification;

	//盾の回転
	Vector3 angle = m_robot[PLAYER_SHIELD_PIVOT].GetAngle();
	angle.y += m_rotation;
	m_robot[PLAYER_SHIELD_PIVOT].SetAngle(angle);

	//脚の回転
	angle = m_robot[PLAYER_PARTS_LEG].GetAngle();
	angle.y += m_rotation * 2;
	m_robot[PLAYER_PARTS_LEG].SetAngle(angle);

	//足の回転
	angle = m_robot[PLAYER_PARTS_FOOT].GetAngle();
	angle.y += -(m_rotation * 3);
	m_robot[PLAYER_PARTS_FOOT].SetAngle(angle);

}

//防御態勢
void Game::BigShield()
{
	auto kb = m_key->GetState();

	if (kb.X) {
		if (!m_isBigShield && !m_isShieldGimmic)
		{
			m_isBigShield = true;
			m_bigShieldCnt = 0;
			m_isShieldGimmic = true;
		}
	}

	if (m_isBigShield)
	{
		m_bigShieldCnt++;

		//手を上げる
		m_robot[PLAYER_ARM_R_PIVOT].SetAngle(Vector3(std::min(150.0f, m_bigShieldCnt*10.0f), 0.0f, 0.0f));
		m_robot[PLAYER_ARM_L_PIVOT].SetAngle(Vector3(std::min(150.0f, m_bigShieldCnt*10.0f), 0.0f, 0.0f));

		//盾を拡大
		m_robot[PLAYER_PARTS_SHIELD_R].SetScale(Vector3(1.5f, 1.5f, 1.5f));
		m_robot[PLAYER_PARTS_SHIELD_L].SetScale(Vector3(1.5f, 1.5f, 1.5f));

		m_robot[PLAYER_PARTS_SHIELD_R].SetTrans(Vector3(1.5f, 0.6f, 0.0f));
		m_robot[PLAYER_PARTS_SHIELD_L].SetTrans(Vector3(-1.5f, 0.6f, 0.0f));

		//盾の高速回転
		Vector3 angle = m_robot[PLAYER_SHIELD_PIVOT].GetAngle();
		angle.y += 15.0f;
		m_robot[PLAYER_SHIELD_PIVOT].SetAngle(angle);

		if (m_bigShieldCnt > 120)
		{
			//初期位置に戻す
			m_robot[PLAYER_PARTS_SHIELD_R].SetScale(Vector3(1.0f, 1.0f, 1.0f));
			m_robot[PLAYER_PARTS_SHIELD_L].SetScale(Vector3(1.0f, 1.0f, 1.0f));

			m_robot[PLAYER_PARTS_SHIELD_R].SetTrans(m_robotStartPos[PLAYER_PARTS_SHIELD_R]);
			m_robot[PLAYER_PARTS_SHIELD_L].SetTrans(m_robotStartPos[PLAYER_PARTS_SHIELD_L]);


			m_robot[PLAYER_ARM_R_PIVOT].SetAngle(Vector3(0.0f, 0.0f, 0.0f));
			m_robot[PLAYER_ARM_L_PIVOT].SetAngle(Vector3(0.0f, 0.0f, 0.0f));

			m_isBigShield = false;
			m_isShieldGimmic = false;
		}
	}
}

//頭打ち
void Game::HeadShoot()
{
	auto kb = m_key->GetState();

	if (kb.Z) {
		if (!m_isHeadShoot)
		{
			m_isHeadShoot = true;
			m_headPos = -5.0f;
		}
	}

	if (m_isHeadShoot)
	{
		Vector3 pos = m_robot[PLAYER_PARTS_HEAD].GetTrans();
		pos.y += -m_headPos / 20.0f;
		pos.z += -0.3f;
		m_robot[PLAYER_PARTS_HEAD].SetTrans(pos);
		m_headPos += 0.1f;
		if (m_headPos > 5.1f)
		{
			//初期位置に戻す
			m_robot[PLAYER_PARTS_HEAD].SetTrans(m_robotStartPos[PLAYER_PARTS_HEAD]);

			m_isHeadShoot = false;
		}
	}
}

//盾攻撃
void Game::ShieldAttack()
{
	auto kb = m_key->GetState();

	if (kb.C) {
		if (!m_isShieldAttack && !m_isShieldGimmic)
		{
			m_isShieldAttack = true;
			m_shieldAttackCnt = 0;
			m_isShieldGimmic = true;
		}
	}

	if (m_isShieldAttack)
	{
		m_shieldAttackCnt++;

		//盾攻撃
		m_robot[PLAYER_SHIELD_PIVOT].SetTrans(m_robotStartPos[PLAYER_SHIELD_PIVOT] + Vector3(0.0f, std::min(m_shieldAttackCnt / 30.0f*0.8f, 0.8f), 0.0f));
		m_robot[PLAYER_SHIELD_PIVOT].SetAngle(Vector3(0.0f,0.0f,0.0f));

		float shieldAngle = std::min(m_shieldAttackCnt / 30.0f*90.0f, 90.0f);
		m_robot[PLAYER_PARTS_SHIELD_R].SetAngle(Vector3(shieldAngle, 0.0f, 0.0f));
		m_robot[PLAYER_PARTS_SHIELD_L].SetAngle(Vector3(-shieldAngle, 180.0f, 0.0f));

		Vector3 move;
		Vector3 move2;
		float armAngle = m_shieldAttackCnt*10.0f;
		if (m_shieldAttackCnt < 20)
		{
			//手を上げる
			m_robot[PLAYER_ARM_R_PIVOT].SetAngle(Vector3(std::min(150.0f, armAngle), 0.0f, 0.0f));
			m_robot[PLAYER_ARM_L_PIVOT].SetAngle(Vector3(std::min(150.0f, armAngle), 0.0f, 0.0f));

			move.x  =  0.01f;
			move2.x = -0.01f;
		}
		else if(m_shieldAttackCnt < 35)
		{
			//手を前方に向ける
			m_robot[PLAYER_ARM_R_PIVOT].SetAngle(Vector3(std::max(90.0f, 350.0f-armAngle), 0.0f, 0.0f));
			m_robot[PLAYER_ARM_L_PIVOT].SetAngle(Vector3(std::max(90.0f, 350.0f - armAngle), 0.0f, 0.0f));

			move.x  = -0.02f;
			move2.x =  0.02f;
			move.z  = -0.4f;
			move2.z = -0.4f;
		}
		else
		{
			move.x  =  0.02f;
			move2.x = -0.02f;
			move.z  =  0.4f;
			move2.z =  0.4f;
		}

		m_robot[PLAYER_PARTS_SHIELD_R].SetTrans(m_robot[PLAYER_PARTS_SHIELD_R].GetTrans() + move);
		m_robot[PLAYER_PARTS_SHIELD_L].SetTrans(m_robot[PLAYER_PARTS_SHIELD_L].GetTrans() + move2);

		if (m_shieldAttackCnt > 50)
		{
			//初期位置に戻す
			m_robot[PLAYER_PARTS_SHIELD_R].SetScale(Vector3(1.0f, 1.0f, 1.0f));
			m_robot[PLAYER_PARTS_SHIELD_L].SetScale(Vector3(1.0f, 1.0f, 1.0f));

			m_robot[PLAYER_PARTS_SHIELD_R].SetTrans(m_robotStartPos[PLAYER_PARTS_SHIELD_R]);
			m_robot[PLAYER_PARTS_SHIELD_L].SetTrans(m_robotStartPos[PLAYER_PARTS_SHIELD_L]);

			m_robot[PLAYER_PARTS_SHIELD_R].SetAngle(Vector3(0.0f, 0.0f, 0.0f));
			m_robot[PLAYER_PARTS_SHIELD_L].SetAngle(Vector3(0.0f, 180.0f, 0.0f));
			m_robot[PLAYER_SHIELD_PIVOT].SetAngle(Vector3(0.0f, 0.0f, 0.0f));
			m_robot[PLAYER_SHIELD_PIVOT].SetTrans(m_robotStartPos[PLAYER_SHIELD_PIVOT]);

			m_robot[PLAYER_ARM_R_PIVOT].SetAngle(Vector3(0.0f, 0.0f, 0.0f));
			m_robot[PLAYER_ARM_L_PIVOT].SetAngle(Vector3(0.0f, 0.0f, 0.0f));
			m_isShieldAttack = false;
			m_isShieldGimmic = false;
		}
	}
}
