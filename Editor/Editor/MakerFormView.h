#pragma once


// MakerFormView 폼 보기

class CTileMaker;
class CObjectMaker;

class CMakerFormView : public CFormView
{
	DECLARE_DYNCREATE(CMakerFormView)

protected:
	CMakerFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMakerFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MakerFormView };
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

private:
	CFont m_font;
	CObjectMaker* m_objectMaker = nullptr;
	CTileMaker* m_tileMaker = nullptr;

public:
	virtual void OnInitialUpdate();
	afx_msg void OnObjectMakerBnClicked();
	afx_msg void OnTileMakerBnClicked();
	afx_msg void OnDestroy();
};


