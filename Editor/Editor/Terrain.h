#pragma once

class CEditorView;

class CTerrain
{
public:
	CTerrain() = default;
	virtual ~CTerrain();

public:
	HRESULT Initialize();

	void Update();

	void RenderToEditorView();

	void RenderToMapView();

	void Release();

public:
	void SetOwnerView(CEditorView* _pOwnerView) { m_pOwnerView = _pOwnerView; }

public:
	void ChangeTileTo(const D3DXVECTOR3& _vPosition, const int32& _iTileID);

	int32 GetTileIndex(const D3DXVECTOR3& _vPosition);

	bool PickTile(const D3DXVECTOR3& _vPosition, const int32& _iIndex);

	void SetRatio(D3DXMATRIX* _pOut, float _fRatioX, float _fRatioY);

private:
	std::vector<TILE_INFO*> m_vecTileInfos;

	CEditorView* m_pOwnerView = nullptr;
};

