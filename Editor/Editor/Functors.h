#pragma once

template<typename T>
void SAFE_DELETE(T& _pTemp)
{
	if (_pTemp)
	{
		delete _pTemp;
		_pTemp = nullptr;
	}
}

template<typename T>
unsigned long SAFE_RELEASE(T& _pTemp)
{
	unsigned long lReferenceCount = 0;
	if (_pTemp)
	{
		lReferenceCount = _pTemp->Release();
		_pTemp = nullptr;
	}

	return lReferenceCount;
}

template<typename T>
void SAFE_DELETES(T& _pTemp)
{
	if (_pTemp)
	{
		delete[] _pTemp;
		_pTemp = nullptr;
	}
}

struct SAFE_DELETE_FUNCTOR
{
public:
	template<typename T>
	void operator()(T& _pTemp)
	{
		if (_pTemp)
		{
			delete _pTemp;
			_pTemp = nullptr;
		}
	}
};

struct SAFE_DELETE_MAP
{
public:
	template<typename T>
	void operator()(T& _pair)
	{
		if (_pair.second)
		{
			delete _pair.second;
			_pair.second = nullptr;
		}
	}
};

class CTag_Finder
{
private:
	const TCHAR*	m_pStr;

public:
	CTag_Finder(const TCHAR* pStr)
		: m_pStr(pStr)
	{

	}

public:
	template<typename T>
	bool	operator()(T& Pair)
	{
		if (!lstrcmp(m_pStr, Pair.first))
			return true;

		return false;
	}
};

static D3DXVECTOR3 GetMousePosition()
{
	POINT tPoint{};
	GetCursorPos(&tPoint);
	ScreenToClient(g_hWnd, &tPoint);
	return D3DXVECTOR3((float)tPoint.x, (float)tPoint.y, 0.f);
}
