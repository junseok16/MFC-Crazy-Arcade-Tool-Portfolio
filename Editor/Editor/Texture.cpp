#include "pch.h"
#include "Texture.h"

#include "DeviceManager.h"
using namespace std;

CTexture::~CTexture()
{
	Release();
}

HRESULT CTexture::InsertTextureInfo(const std::wstring& _wstrFullPath, const std::wstring& _wstrStateKey, const int32& _iCount)
{
	for (int32 iIndex = 0; iIndex < _iCount; ++iIndex)
	{
		TEXTURE_INFO* pTextureInfo = new TEXTURE_INFO();
		ZeroMemory(pTextureInfo, sizeof(pTextureInfo));

		const wstring& wstrFinalPath = std::format(L"{0}{1}.png", _wstrFullPath, iIndex);

		if (FAILED(D3DXGetImageInfoFromFile(wstrFinalPath.c_str(), &(pTextureInfo->tImageInfo))))
		{
			// COM 객체는 Release 함수로 해제합니다.
			SAFE_RELEASE(pTextureInfo->pTexture);
			SAFE_DELETE(pTextureInfo);
			AfxMessageBox(L"D3DXCreateTextureFromFileEx 함수가 실패했습니다.");
			return E_FAIL;
		}

		if (FAILED(D3DXCreateTextureFromFileEx(CDeviceManager::GetInstance()->GetDevice(),
			wstrFinalPath.c_str(),
			pTextureInfo->tImageInfo.Width,
			pTextureInfo->tImageInfo.Height,
			pTextureInfo->tImageInfo.MipLevels,
			0,
			pTextureInfo->tImageInfo.Format,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0,
			nullptr,
			nullptr,
			&(pTextureInfo->pTexture))))
		{
			SAFE_RELEASE(pTextureInfo->pTexture);
			SAFE_DELETE(pTextureInfo);
			AfxMessageBox(L"D3DXCreateTextureFromFileEx 함수가 실패했습니다.");
			return E_FAIL;
		}

		m_umapTextureInfos[_wstrStateKey].push_back(pTextureInfo);
	}
	return S_OK;
}

const TEXTURE_INFO* CTexture::GetTextureInfo(const std::wstring& _wstrStateKey, const int32& _iCount)
{
	return m_umapTextureInfos[_wstrStateKey][_iCount];
}

void CTexture::Release()
{
	for (auto& pPairTextureInfo : m_umapTextureInfos)
	{
		for (auto& pTextureInfo : pPairTextureInfo.second)
		{
			SAFE_DELETE(pTextureInfo);
		}
	}
	m_umapTextureInfos.clear();
}
