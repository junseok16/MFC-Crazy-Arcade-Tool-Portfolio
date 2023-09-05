#pragma once
#include "afxdialogex.h"


// CTileMaker 대화 상자

class CTileMaker : public CDialog
{
	DECLARE_DYNAMIC(CTileMaker)

public:
	CTileMaker(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTileMaker();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CTileMaker };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnTileListLbnSelchange();

private:
	std::map<CString, CImage*> m_mapImages;
	CListBox m_tileListBox;
	CStatic m_tileImage;
};
