// CTileMaker.cpp: 구현 파일
//

#include "pch.h"
#include "Editor.h"
#include "afxdialogex.h"
#include "TileMaker.h"
#include "FileExplorer.h"

#include "MainFrm.h"
#include "Terrain.h"
#include "EditorView.h"
using namespace std;

// CTileMaker 대화 상자

IMPLEMENT_DYNAMIC(CTileMaker, CDialog)

CTileMaker::CTileMaker(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CTileMaker, pParent)
{

}

CTileMaker::~CTileMaker()
{
}

void CTileMaker::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_tileListBox);
	DDX_Control(pDX, IDC_PICTURE, m_tileImage);
}


BEGIN_MESSAGE_MAP(CTileMaker, CDialog)
	ON_WM_DESTROY()
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CTileMaker::OnTileListLbnSelchange)
END_MESSAGE_MAP()


// CTileMaker 메시지 처리기


void CTileMaker::OnDestroy()
{
	CDialog::OnDestroy();

	for_each(m_mapImages.begin(), m_mapImages.end(), [](auto& _pair)
		{
			_pair.second->Destroy();
			SAFE_DELETE(_pair.second);
		}
	);
	m_mapImages.clear();
}


void CTileMaker::OnDropFiles(HDROP hDropInfo)
{
	UpdateData(TRUE);

	CDialog::OnDropFiles(hDropInfo);

	TCHAR szFilePath[MAX_PATH] = L"";
	TCHAR szFileName[MIN_STR] = L"";

	// DragQueryFile : 드롭된 파일의 정보를 얻어오는 함수
	// 두 번째 매개 변수 : 0xffffffff(-1)을 지정하면 드롭된 파일의 개수를 반환 
	int32 iNumFiles = DragQueryFile(hDropInfo, 0xffff'ffff, nullptr, 0);

	for (int32 iIndex = 0; iIndex < iNumFiles; ++iIndex)
	{
		DragQueryFile(hDropInfo, iIndex, szFilePath, MAX_PATH);

		CString	strRelative = CFileExplorer::ConvertToRelativePath(szFilePath);
		CString	strFileName = PathFindFileName(strRelative);

		lstrcpy(szFileName, strFileName.GetString());

		// 파일의 확장자 명을 제거하는 함수
		PathRemoveExtension(szFileName);
		strFileName = szFileName;

		auto iter = m_mapImages.find(strFileName);
		if (iter == m_mapImages.end())
		{
			CImage* pImage = new CImage();
			pImage->Load(strRelative);

			m_mapImages.insert({ strFileName, pImage });
			m_tileListBox.AddString(szFileName);
		}
	}

	// Horizontal_Scroll();
	UpdateData(FALSE);
}


void CTileMaker::OnTileListLbnSelchange()
{
	UpdateData(TRUE);

	// 타일 이미지를 출력합니다.
	int32 iIndex = m_tileListBox.GetCurSel();
	if (LB_ERR == iIndex) { return; }

	CString strFindName;
	m_tileListBox.GetText(iIndex, strFindName);

	auto iter = m_mapImages.find(strFindName);
	if (iter == m_mapImages.end()) { return; }

	m_tileImage.SetBitmap(*(iter->second));

	// 타일 인덱스를 변경합니다.
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CEditorView* pEditorView = dynamic_cast<CEditorView*>(pMainFrm->GetSceneWndSplitter()->GetPane(0, 0));
	pEditorView->SetTerrainIndex(iIndex);

	UpdateData(FALSE);
}
