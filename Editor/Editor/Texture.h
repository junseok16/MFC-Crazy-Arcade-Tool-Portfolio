#pragma once

class CTexture
{
public:
	CTexture() = default;
	virtual ~CTexture();

public:
	HRESULT InsertTextureInfo(const std::wstring& _wstrFullPath, const std::wstring& _wstrStateKey, const int32& _iCount = 0);

	const TEXTURE_INFO* GetTextureInfo(const std::wstring& _wstrStateKey, const int32& _iCount = 0);
	
	void Release();

private:
	std::unordered_map<std::wstring, std::vector<TEXTURE_INFO*>> m_umapTextureInfos;
};

