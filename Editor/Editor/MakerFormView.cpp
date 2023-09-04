// MakerFormView.cpp: 구현 파일
//

#include "pch.h"
#include "Editor.h"
#include "MakerFormView.h"

#include "TileMaker.h"
#include "ObjectMaker.h"

// MakerFormView

IMPLEMENT_DYNCREATE(CMakerFormView, CFormView)

CMakerFormView::CMakerFormView()
	: CFormView(IDD_MakerFormView)
{

}

CMakerFormView::~CMakerFormView()
{
}

void CMakerFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMakerFormView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMakerFormView::OnObjectMakerBnClicked)
	ON_BN_CLICKED(IDC_BUTTON2, &CMakerFormView::OnTileMakerBnClicked)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// MakerFormView 진단

#ifdef _DEBUG
void CMakerFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMakerFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// MakerFormView 메시지 처리기


void CMakerFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// 폼 뷰에 배치된 버튼의 폰트를 변경합니다.
	m_font.CreatePointFont(128, L"굴림");
	GetDlgItem(IDC_BUTTON1)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON2)->SetFont(&m_font);

	m_tileMaker = new CTileMaker();
	m_objectMaker = new CObjectMaker();
}


void CMakerFormView::OnObjectMakerBnClicked()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMakerFormView::OnTileMakerBnClicked()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMakerFormView::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SAFE_DELETE(m_objectMaker);
	SAFE_DELETE(m_tileMaker);
}
