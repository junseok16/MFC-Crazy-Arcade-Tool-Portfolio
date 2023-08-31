#include "pch.h"
#include "ResourceManager.h"

IMPLEMENT_SINGLETON(CResourceManager)

CResourceManager::~CResourceManager()
{
	Release();
}

void CResourceManager::Release()
{
	for (auto& texture : m_umapTextures)
	{
		if (texture.second != nullptr)
		{
			SAFE_DELETE(texture.second);
		}
	}
	m_umapTextures.clear();
}

CTexture* CResourceManager::LoadTexture(const std::wstring& _strKey, const std::wstring& _strPath, uint32 _uiTransparency)
{
	return nullptr;
}
