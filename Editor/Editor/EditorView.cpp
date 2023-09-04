#include "pch.h"
#include "framework.h"

#ifndef SHARED_HANDLERS
#include "Editor.h"
#endif

#include "MainFrm.h"
#include "EditorDoc.h"
#include "EditorView.h"
#include "MapView.h"

#include "DeviceManager.h"
#include "ResourceManager.h"
#include "Terrain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 핸들 윈도우입니다.
HWND g_hWnd;

IMPLEMENT_DYNCREATE(CEditorView, CScrollView)

BEGIN_MESSAGE_MAP(CEditorView, CScrollView)
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


CEditorView::CEditorView() noexcept { }

CEditorView::~CEditorView() { }

BOOL CEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}


void CEditorView::OnDraw(CDC* /*pDC*/)
{
	CEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) { return; }
	
	CDeviceManager::GetInstance()->RenderBegin();
	m_pTerrain->RenderToEditorView();
	CDeviceManager::GetInstance()->RenderEnd();
}


BOOL CEditorView::OnPreparePrinting(CPrintInfo* pInfo) { return DoPreparePrinting(pInfo); }

void CEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) { }

void CEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) { }


#ifdef _DEBUG
void CEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEditorDoc* CEditorView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEditorDoc)));
	return (CEditorDoc*)m_pDocument;
}
#endif


void CEditorView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// 핸들 윈도우를 초기화합니다.
	g_hWnd = m_hWnd;

	InitWindowPos();
	InitDevice();
	InitResource();
	InitObject();
}


void CEditorView::OnDestroy()
{
	CScrollView::OnDestroy();

	// 지형을 해제합니다.
	SAFE_DELETE(m_pTerrain);

	CDeviceManager::GetInstance()->DestroyInstance();
	CResourceManager::GetInstance()->DestroyInstance();
}


void CEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CScrollView::OnLButtonDown(nFlags, point);

	m_pTerrain->ChangeTileTo(D3DXVECTOR3((float)(point.x + GetScrollPos(0)), (float)(point.y + GetScrollPos(1)), 0.0f), 0);

	// 에디터 뷰를 갱신합니다.
	Invalidate(FALSE);

	// 맵 뷰를 생긴합니다.
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMapView* pMapView = dynamic_cast<CMapView*>(pMainFrm->GetInspectorWndSplitter()->GetPane(0, 0));
	pMapView->Invalidate(FALSE);
}

void CEditorView::InitWindowPos()
{
	/*
	* 가로 마름모 타일 개수 * 가로 마름모 타일 길이, 세로 마름모 타일 개수 * 세로 마름모 타일 길이 / 2
	*/
	SetScrollSizes(MM_TEXT, CSize(ITILEX * ITILECX, ITILEY * ITILECY / 2));
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();

	RECT rcWnd{};
	pMainFrm->GetWindowRect(&rcWnd);
	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);

	RECT rcEditorView{};
	GetClientRect(&rcEditorView);

	float fWidthFrm = (float)(rcWnd.right - rcEditorView.right);
	float fHeightFrm = (float)(rcWnd.bottom - rcEditorView.bottom);

	pMainFrm->SetWindowPos(nullptr, 0, 0, int32(IWINCX + fWidthFrm), int32(IWINCY + fHeightFrm), SWP_NOZORDER);
}

void CEditorView::InitDevice()
{
	// 디바이스를 초기화합니다.
	if (FAILED(CDeviceManager::GetInstance()->Initialize()))
	{
		AfxMessageBox(L"장치를 초기화할 수 없습니다.");
		return;
	}
}

void CEditorView::InitResource()
{
	// 리소스를 불러옵니다.
	if (FAILED(CResourceManager::GetInstance()->LoadTexture(L"Multi\\Terrain\\Tile\\Tile", L"Terrain", L"Tile", 36)))
	{
		AfxMessageBox(L"리소스를 불러올 수 없습니다.");
		return;
	}
}

void CEditorView::InitObject()
{
	// 지형을 초기화합니다.
	m_pTerrain = new CTerrain();

	if (FAILED(m_pTerrain->Initialize()))
	{
		AfxMessageBox(L"지형을 초기화할 수 없습니다.");
		return;
	}

	m_pTerrain->SetOwnerView(this);
}
