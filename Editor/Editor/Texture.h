#pragma once
class CTexture
{
public:
	CTexture() = default;
	virtual ~CTexture() = default;

public:
	virtual const TEXTURE_INFO GetTextureInfo(const std::wstring& _wstrKey, const int iCount = 0) = 0;
	virtual HRESULT InsertTexture(const std::wstring& _wstrPath, const std::wstring& _wstrKey, const int iCount = 0) = 0;
	virtual void Release() = 0;
};

