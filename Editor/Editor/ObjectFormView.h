#pragma once



// CObjectFormView 폼 보기

class CObjectFormView : public CFormView
{
	DECLARE_DYNCREATE(CObjectFormView)

protected:
	CObjectFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CObjectFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CObjectFormView };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButtonObject();
};


