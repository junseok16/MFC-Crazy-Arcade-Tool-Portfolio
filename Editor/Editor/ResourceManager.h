#pragma once

class CTexture;

class CResourceManager final
{
	DECLARE_SINGLETON(CResourceManager)

private:
	CResourceManager() = default;
	~CResourceManager();

public:
	void Release();

public:
	// ≈ÿΩ∫√≥
	CTexture* GetTexture(const std::wstring& _strKey) { return m_umapTextures[_strKey]; }
	CTexture* LoadTexture(const std::wstring& _strKey, const std::wstring& _strPath, uint32 _uiTransparency = RGB(255, 0, 255));

private:
	std::unordered_map<std::wstring, CTexture*> m_umapTextures;
};

