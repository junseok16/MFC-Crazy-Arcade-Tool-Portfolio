// CLogView.cpp: 구현 파일
//

#include "pch.h"
#include "Editor.h"
#include "LogView.h"


// CLogView

IMPLEMENT_DYNCREATE(CLogView, CView)

CLogView::CLogView()
{

}

CLogView::~CLogView()
{
}

BEGIN_MESSAGE_MAP(CLogView, CView)
END_MESSAGE_MAP()


// CLogView 그리기

void CLogView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CLogView 진단

#ifdef _DEBUG
void CLogView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CLogView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLogView 메시지 처리기
