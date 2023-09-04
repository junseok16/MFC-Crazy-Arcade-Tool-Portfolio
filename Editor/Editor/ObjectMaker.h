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

	virtual BOOL OnInitDialog();

private:
	/**************
		값 타입
	**************/
	CString m_strName;
	CString m_strHP;
	CString m_strAttack;
	CString m_strDefense;

	/**************
		컨트롤 타입
	**************/
	CButton m_jobRadioBtn[3];
	CListBox m_objectListBox;

	/**************
		기타
	**************/
	std::map<CString, CREATURE_INFO*> m_mapCreatureInfos;

public:
	afx_msg void OnInsertObjectBnClicked();
	afx_msg void OnEraseObjectBnClicked();
	afx_msg void OnObjectListLbnSelchange();
	afx_msg void OnFindObjectBnClicked();
};
