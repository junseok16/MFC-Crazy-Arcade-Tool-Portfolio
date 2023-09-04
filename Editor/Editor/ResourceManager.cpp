#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
using namespace std;

IMPLEMENT_SINGLETON(CResourceManager)

CResourceManager::~CResourceManager()
{
	Release();
}

void CResourceManager::Release()
{
	for (auto& pairTexture : m_umapTextures)
	{
		if (pairTexture.second != nullptr)
		{
			SAFE_DELETE(pairTexture.second);
		}
	}
	m_umapTextures.clear();
}

HRESULT CResourceManager::LoadTexture(const std::wstring& _wstrPath, const std::wstring& _wstrTextureKey, const std::wstring& _wstrStateKey, const int32& _iCount)
{
	const wstring strFullPath = m_strPath + _wstrPath;

	if (m_umapTextures.find(_wstrTextureKey) != m_umapTextures.end())
	{
		return E_FAIL;
	}

	// 새로운 텍스처를 생성합니다.
	CTexture* pTexture = new CTexture();
	if (FAILED(pTexture->InsertTextureInfo(strFullPath, _wstrStateKey, _iCount)))
	{
		SAFE_DELETE(pTexture);
		AfxMessageBox(strFullPath.c_str());
		return E_FAIL;
	}

	m_umapTextures.insert({ _wstrTextureKey, pTexture });
	return S_OK;
}

CTexture* CResourceManager::GetTexture(const std::wstring& _wstrTextureKey)
{
	return m_umapTextures[_wstrTextureKey];
}

const TEXTURE_INFO* CResourceManager::GetTextureInfo(const std::wstring& _wstrTextureKey, const std::wstring& _wstrStateKey, const int32& _iCount)
{
	if (m_umapTextures[_wstrTextureKey] == nullptr)
	{
		return nullptr;
	}
	return m_umapTextures[_wstrTextureKey]->GetTextureInfo(_wstrStateKey, _iCount);
}
