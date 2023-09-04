// CTileMaker.cpp: 구현 파일
//

#include "pch.h"
#include "Editor.h"
#include "afxdialogex.h"
#include "TileMaker.h"


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
}


BEGIN_MESSAGE_MAP(CTileMaker, CDialog)
END_MESSAGE_MAP()


// CTileMaker 메시지 처리기
