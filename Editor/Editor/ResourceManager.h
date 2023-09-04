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
	HRESULT LoadTexture(const std::wstring& _wstrPath, const std::wstring& _wstrTextureKey, const std::wstring& _wstrStateKey, const int32& _iCount);
	
	CTexture* GetTexture(const std::wstring& _wstrTextureKey);
	
	const TEXTURE_INFO* GetTextureInfo(const std::wstring& _wstrTextureKey, const std::wstring& _wstrStateKey, const int32& _iCount);
	

private:
	std::wstring m_strPath = L"..\\Resources\\";

	std::unordered_map<std::wstring, CTexture*> m_umapTextures;
};

