// CMapView.cpp: 구현 파일
//

#include "pch.h"
#include "Editor.h"
#include "MapView.h"

#include "DeviceManager.h"
#include "MainFrm.h"
#include "Terrain.h"
#include "EditorView.h"

// CMapView

IMPLEMENT_DYNCREATE(CMapView, CView)

CMapView::CMapView()
{

}

CMapView::~CMapView()
{
}

BEGIN_MESSAGE_MAP(CMapView, CView)
END_MESSAGE_MAP()


// CMapView 그리기

void CMapView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CEditorView* pEditorView = dynamic_cast<CEditorView*>(pMainFrm->GetSceneWndSplitter()->GetPane(0, 0));
	CTerrain* pTerrain = pEditorView->GetTerrain();

	VERIFY_NULLPTR(pTerrain);

	CDeviceManager::GetInstance()->RenderBegin();
	pTerrain->RenderToMapView();
	CDeviceManager::GetInstance()->RenderEnd(m_hWnd);
}


// CMapView 진단

#ifdef _DEBUG
void CMapView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMapView 메시지 처리기
