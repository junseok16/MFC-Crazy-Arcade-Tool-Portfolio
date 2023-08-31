#pragma once
#include "Texture.h"

class CSingleTexture : public CTexture
{
public:
	CSingleTexture() = default;
	virtual ~CSingleTexture() = default;

public:


private:
	TEXTURE_INFO* m_pTextureInfo = nullptr;
};

