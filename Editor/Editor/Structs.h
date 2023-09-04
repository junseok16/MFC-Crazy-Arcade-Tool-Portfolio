#pragma once

/***************
	����� ���� Ÿ��
***************/
struct tagTransform
{
	D3DXVECTOR3 vPosition{};
	D3DXVECTOR3 vSize{};
	D3DXVECTOR3 vDirection{};
	D3DXVECTOR3 vLook{};
	D3DXMATRIX matWorld{};
};

struct tagFrameRate
{
	float fFrameRate = 0.0f;// �������� ���� ���� ����
	float fMaxFrameRate = 0.0f;// �ִ� �̹����� ������ ��
};

struct tagTexture
{
	LPDIRECT3DTEXTURE9 pTexture{};// COM ��ü
	D3DXIMAGE_INFO tImageInfo{};// ����ü
};

struct tagTile
{
	D3DXVECTOR3	vPosition{};// Ÿ���� �߽� ��ǥ
	D3DXVECTOR3 vSize{};// Ÿ���� ����, ���� ����
	BYTE byOption = 0;
	BYTE byTileID = 0;
	int32 iIndex = 0;
	int32 iParentIndex = 0;
};

struct tagCreature
{
	CString strName = L"";
	int32 iHP = 0;
	int32 iAttack = 0;
	int32 iDefense = 0;
	BYTE byJob = 0;
	BYTE byItem = 0;
};

struct tagTexturePath
{
	std::wstring wstrObjKey = L"";
	std::wstring wstrStateKey = L"";
	std::wstring wstrPath = L"";
	int32 iCount = 0;
};

using TRANSFORM_INFO = tagTransform;
using TEXTURE_INFO = tagTexture;
using FRAMERATE_INFO = tagFrameRate;
using TILE_INFO = tagTile;
using CREATURE_INFO = tagCreature;
using TEXTURE_PATH_INFO = tagTexturePath;
