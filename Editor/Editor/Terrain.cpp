#include "pch.h"
#include "Terrain.h"

#include "DeviceManager.h"
#include "ResourceManager.h"
#include "EditorView.h"
using namespace std;

CTerrain::~CTerrain() { Release(); }

HRESULT CTerrain::Initialize()
{
	m_vecTileInfos.reserve(ITILEX * ITILEY);

	for (int32 iRow = 0; iRow < ITILEY; ++iRow) {
		for (int32 iColumn = 0; iColumn < ITILEX; ++iColumn) {

			TILE_INFO* pTileInfo = new TILE_INFO();
			float fX = (FTILECX * iColumn) + (iRow % 2) * (FTILECX / 2.0f);
			float fY = (FTILECY / 2.0f) * iRow;

			pTileInfo->vPosition = { fX, fY, 0.0f };
			pTileInfo->vSize = { FTILECX, FTILECY, 0.0f };
			pTileInfo->byOption = 0;
			pTileInfo->byTileID = 3;
			m_vecTileInfos.push_back(pTileInfo);
		}
	}
	return S_OK;
}

void CTerrain::Update() {}

void CTerrain::RenderToEditorView()
{
	// 로컬 좌표계에서 월드 좌표계로 변환할 행렬입니다.
	D3DXMATRIX matWorld, matScale, matTrans;
	RECT rcClnt{};
	
	wstring wstrTileIndex = L"";
	int32 iTileIndex = 0;

	for (auto& pTileInfo : m_vecTileInfos)
	{
		// 타일을 출력합니다.
		D3DXMatrixIdentity(&matWorld);

		D3DXMatrixScaling(&matScale, 1.0f, 1.0f, 1.0f);
		// D3DXMatrixRotationZ();
		D3DXMatrixTranslation(&matTrans,
			pTileInfo->vPosition.x - m_pOwnerView->GetScrollPos(0),
			pTileInfo->vPosition.y - m_pOwnerView->GetScrollPos(1),
			pTileInfo->vPosition.z);

		matWorld = matScale * matTrans;

		GetClientRect(m_pOwnerView->m_hWnd, &rcClnt);
		float fX = FWINCX / (float)(rcClnt.right - rcClnt.left);
		float fY = FWINCY / (float)(rcClnt.bottom - rcClnt.top);
		SetRatio(&matWorld, fX, fY);

		LPD3DXSPRITE pSpriteCOM = CDeviceManager::GetInstance()->GetSpriteCOM();
		pSpriteCOM->SetTransform(&matWorld);

		const TEXTURE_INFO* pTexureInfo = CResourceManager::GetInstance()->GetTextureInfo(L"Terrain", L"Tile", pTileInfo->byTileID);

		float fPositionX = pTexureInfo->tImageInfo.Width / 2.0f;
		float fPositionY = pTexureInfo->tImageInfo.Height / 2.0f;
		D3DXVECTOR3 vecPosition(fPositionX, fPositionY, 0.0f);

		pSpriteCOM->Draw(pTexureInfo->pTexture,
			nullptr,
			&vecPosition,
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		// 타일 번호를 출력합니다.
		wstrTileIndex = format(L"{0}", iTileIndex);

		CDeviceManager::GetInstance()->GetFontCOM()->DrawTextW(pSpriteCOM,	// 스프라이트 COM 객체
			wstrTileIndex.c_str(),											// 출력할 문자열
			wstrTileIndex.size(),											// 문자열의 길이
			nullptr,														// 출력할 렉트의 주소
			0,																// 정렬 옵션
			D3DCOLOR_ARGB(255, 0, 0, 0));									// 출력할 폰트 색상

		++iTileIndex;
	}
}

void CTerrain::RenderToMapView()
{
	// 로컬 좌표계에서 월드 좌표계로 변환할 행렬입니다.
	D3DXMATRIX matWorld, matScale, matTrans;

	for (auto& pTileInfos : m_vecTileInfos)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.0f, 1.0f, 1.0f);
		D3DXMatrixTranslation(&matTrans,
			pTileInfos->vPosition.x,
			pTileInfos->vPosition.y,
			pTileInfos->vPosition.z);

		matWorld = matScale * matTrans;

		SetRatio(&matWorld, 0.3f, 0.3f);

		LPD3DXSPRITE pSpriteCOM = CDeviceManager::GetInstance()->GetSpriteCOM();
		pSpriteCOM->SetTransform(&matWorld);

		const TEXTURE_INFO* pTexureInfo = CResourceManager::GetInstance()->GetTextureInfo(L"Terrain", L"Tile", pTileInfos->byTileID);
		float fPositionX = pTexureInfo->tImageInfo.Width / 2.0f;
		float fPositionY = pTexureInfo->tImageInfo.Height / 2.0f;

		D3DXVECTOR3 vecPosition(fPositionX, fPositionY, 0.0f);

		pSpriteCOM->Draw(pTexureInfo->pTexture,
			nullptr,
			&vecPosition,
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CTerrain::Release()
{
	for (auto& pTileInfo : m_vecTileInfos)
	{
		SAFE_DELETE(pTileInfo);
	}
	m_vecTileInfos.clear();
	m_vecTileInfos.shrink_to_fit();
}

void CTerrain::SetRatio(D3DXMATRIX* _pMat, float _fRatioX, float _fRatioY)
{
	_pMat->_11 *= _fRatioX;
	_pMat->_21 *= _fRatioX;
	_pMat->_31 *= _fRatioX;
	_pMat->_41 *= _fRatioX;

	_pMat->_12 *= _fRatioY;
	_pMat->_22 *= _fRatioY;
	_pMat->_32 *= _fRatioY;
	_pMat->_42 *= _fRatioY;
}

void CTerrain::ChangeTileTo(const D3DXVECTOR3& _vPosition, const int32& _iTileID)
{
	int32 iIndex = GetTileIndex(_vPosition);
	if (iIndex == -1)
	{
		return;
	}

	m_vecTileInfos[iIndex]->byTileID = _iTileID;
}

int32 CTerrain::GetTileIndex(const D3DXVECTOR3& _vPosition)
{
	for (uint32 iIndex = 0; iIndex < m_vecTileInfos.size(); ++iIndex)
	{
		if (PickTile(_vPosition, iIndex))
		{
			return iIndex;
		}
	}
	return -1;
}

bool CTerrain::PickTile(const D3DXVECTOR3& _vPosition, const int32& _iIndex)
{
	D3DXVECTOR3 vPoint[4]
	{
		// 상우하좌 포인트입니다.
		{ m_vecTileInfos[_iIndex]->vPosition.x, m_vecTileInfos[_iIndex]->vPosition.y + (FTILECY / 2.0f), 0.0f },
		{ m_vecTileInfos[_iIndex]->vPosition.x + (FTILECX / 2.0f), m_vecTileInfos[_iIndex]->vPosition.y, 0.0f },
		{ m_vecTileInfos[_iIndex]->vPosition.x, m_vecTileInfos[_iIndex]->vPosition.y - (FTILECY / 2.0f), 0.0f },
		{ m_vecTileInfos[_iIndex]->vPosition.x - (FTILECX / 2.0f), m_vecTileInfos[_iIndex]->vPosition.y, 0.0f }
	};

	D3DXVECTOR3 vDirection[4]
	{
		vPoint[1] - vPoint[0],// ↘
		vPoint[2] - vPoint[1],// ↙
		vPoint[3] - vPoint[2],// ↖
		vPoint[0] - vPoint[3] // ↗
	};

	D3DXVECTOR3 vNormal[4]
	{
		{ -vDirection[0].y, vDirection[0].x, 0.0f },
		{ -vDirection[1].y, vDirection[1].x, 0.0f },
		{ -vDirection[2].y, vDirection[2].x, 0.0f },
		{ -vDirection[3].y, vDirection[3].x, 0.0f }
	};

	D3DXVECTOR3	vMouseDirection[4]
	{
		_vPosition - vPoint[0],
		_vPosition - vPoint[1],
		_vPosition - vPoint[2],
		_vPosition - vPoint[3]
	};

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);
		D3DXVec3Normalize(&vMouseDirection[i], &vMouseDirection[i]);

		if (0.0f < D3DXVec3Dot(&vNormal[i], &vMouseDirection[i]))
		{
			return false;
		}
	}

	return true;
}

