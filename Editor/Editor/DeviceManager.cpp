#include "pch.h"
#include "DeviceManager.h"

IMPLEMENT_SINGLETON(CDeviceManager)

CDeviceManager::CDeviceManager() { }

CDeviceManager::~CDeviceManager()
{
	Release();
}

HRESULT CDeviceManager::Initialize()
{
	// 디바이스를 조사할 객체를 생성합니다.
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	// 디바이스를 조사합니다.
	D3DCAPS9 tDeviceCaps;
	ZeroMemory(&tDeviceCaps, sizeof(D3DCAPS9));

	HRESULT hDeviceCapsResult = m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &tDeviceCaps);
	if (FAILED(hDeviceCapsResult))
	{
		AfxMessageBox(L"GetDeviceCaps() failed!");
		return E_FAIL;
	}

	DWORD lVertexProcessing = 0;
	if (tDeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		lVertexProcessing |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		lVertexProcessing |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	
	D3DPRESENT_PARAMETERS tD3dpp;
	ZeroMemory(&tD3dpp, sizeof(D3DPRESENT_PARAMETERS));
	SetDeviceParameters(tD3dpp);

	// 그래픽카드를 제어할 객체를 생성합니다.
	{
		HRESULT hCreateDeviceResult = m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, lVertexProcessing, &tD3dpp, &m_pDevice);
		if (FAILED(hCreateDeviceResult))
		{
			AfxMessageBox(L"디바이스 객체를 생성할 수 없습니다.");
			return E_FAIL;
		}
	}

	// 스프라이트 COM 객체를 생성합니다.
	{
		HRESULT hCreateSpriteResult = D3DXCreateSprite(m_pDevice, &m_pSpriteCOM);
		if (FAILED(hCreateSpriteResult))
		{
			AfxMessageBox(L"스프라이트 COM 객체를 생성할 수 없습니다.");
			return E_FAIL;
		}
	}

	// 폰트 COM 객체를 생성합니다.
	{
		D3DXFONT_DESCW tFontInfo;
		ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));

		tFontInfo.Height = 20;
		tFontInfo.Width = 10;
		tFontInfo.Weight = FW_HEAVY;
		tFontInfo.CharSet = HANGEUL_CHARSET;
		lstrcpy(tFontInfo.FaceName, L"굴림");

		if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFontCOM)))
		{
			AfxMessageBox(L"폰트 COM 객체를 생성할 수 없습니다.");
			return E_FAIL;
		}
	}
	
	return S_OK;
}

void CDeviceManager::RenderBegin()
{
	m_pDevice->Clear(0,											// 렉트 개수	
		nullptr,												// 렉트 첫 번째 주소	
		D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET,	// 지울 버퍼 종류
		D3DCOLOR_ARGB(255, 0, 0, 255),							// 후면 버퍼 색상
		1.0f,													// 깊이 버퍼 초기화 값
		0);														// 스텐실 버퍼 초기화 값

	m_pDevice->BeginScene();
	m_pSpriteCOM->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDeviceManager::RenderEnd(HWND _hWnd)
{
	m_pSpriteCOM->End();
	m_pDevice->EndScene();
	m_pDevice->Present(nullptr, nullptr, _hWnd, nullptr);
}

void CDeviceManager::Release()
{
	SAFE_RELEASE(m_pSpriteCOM);
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pSDK);
}

void CDeviceManager::SetDeviceParameters(D3DPRESENT_PARAMETERS& _tD3dpp)
{
	_tD3dpp.BackBufferWidth = IWINCX;
	_tD3dpp.BackBufferHeight = IWINCY;
	_tD3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	_tD3dpp.BackBufferCount = 1;
	
	_tD3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;	// 멀티 샘플링
	_tD3dpp.MultiSampleQuality = 0;

	_tD3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		// 스왑 체인
	_tD3dpp.hDeviceWindow = g_hWnd;
	_tD3dpp.Windowed = TRUE;						// 창 모드

	_tD3dpp.EnableAutoDepthStencil = TRUE;
	_tD3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	_tD3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	_tD3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}
