// CObjectFormView.cpp: 구현 파일
//

#include "pch.h"
#include "Editor.h"
#include "ObjectFormView.h"


// CObjectFormView

IMPLEMENT_DYNCREATE(CObjectFormView, CFormView)

CObjectFormView::CObjectFormView()
	: CFormView(IDD_CObjectFormView)
{

}

CObjectFormView::~CObjectFormView()
{
}

void CObjectFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CObjectFormView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CObjectFormView::OnBnClickedButtonObject)
END_MESSAGE_MAP()


// CObjectFormView 진단

#ifdef _DEBUG
void CObjectFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CObjectFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CObjectFormView 메시지 처리기


void CObjectFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	
	CFont m_font;
	m_font.CreatePointFont(128, L"굴림");
}


void CObjectFormView::OnBnClickedButtonObject()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	ERR_MSG(L"테스트");
	UpdateData(FALSE);
}
