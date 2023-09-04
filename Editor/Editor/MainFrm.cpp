#include "pch.h"
#include "framework.h"
#include "Editor.h"

#include "MainFrm.h"

#include "EditorView.h"
#include "MapView.h"
#include "MakerFormView.h"
#include "LogView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame() noexcept
{

}

CMainFrame::~CMainFrame()
{

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

#pragma region 도구 모음
	/*
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	*/
#pragma endregion

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs)) { return FALSE; }
	
	return TRUE;
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	if (!m_editorWndSplitter.CreateStatic(this, 1, 2)) { return FALSE; }

	if (!m_inspectorWndSplitter.CreateStatic(&m_editorWndSplitter, 2, 1, WS_CHILD | WS_VISIBLE, m_editorWndSplitter.IdFromRowCol(0, 0))) { return FALSE; }
	m_inspectorWndSplitter.CreateView(0, 0, RUNTIME_CLASS(CMapView), CSize(300, 400), pContext);
	m_inspectorWndSplitter.CreateView(1, 0, RUNTIME_CLASS(CMakerFormView), CSize(300, 400), pContext);

	if (!m_sceneWndSplitter.CreateStatic(&m_editorWndSplitter, 2, 1, WS_CHILD | WS_VISIBLE, m_editorWndSplitter.IdFromRowCol(0, 1))) { return FALSE; }
	m_sceneWndSplitter.CreateView(0, 0, RUNTIME_CLASS(CEditorView), CSize(IWINCX, IWINCY), pContext);
	m_sceneWndSplitter.CreateView(1, 0, RUNTIME_CLASS(CLogView), CSize(500, 200), pContext);

	m_editorWndSplitter.SetColumnInfo(0, 300, 100);	
	return TRUE;
}
