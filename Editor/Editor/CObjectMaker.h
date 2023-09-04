#pragma once
#include "afxdialogex.h"


// CObjectMaker 대화 상자

class CObjectMaker : public CDialog
{
	DECLARE_DYNAMIC(CObjectMaker)

public:
	CObjectMaker(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CObjectMaker();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CObjectMaker };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	

public:
	afx_msg void OnDestroy();
};
