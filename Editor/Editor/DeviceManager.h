#pragma once

class CDeviceManager final
{
	DECLARE_SINGLETON(CDeviceManager)

private:
	CDeviceManager();
	~CDeviceManager();

public:
	HRESULT Initialize();
	void RenderBegin();
	void RenderEnd(HWND _hWnd = nullptr);
	void Release();

public:
	LPDIRECT3DDEVICE9 GetDevice() const { return m_pDevice; }
	LPD3DXSPRITE GetSprite() const { return m_pSprite; }

private:
	void SetParameters(D3DPRESENT_PARAMETERS& _tD3dpp);

private:
	LPDIRECT3D9 m_pSDK = nullptr;
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;

	// 스프라이트 COM 객체
	LPD3DXSPRITE m_pSprite = nullptr;
};

