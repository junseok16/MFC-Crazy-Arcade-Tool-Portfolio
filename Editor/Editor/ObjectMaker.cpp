// CObjectMaker.cpp: 구현 파일
//

#include "pch.h"
#include "Editor.h"
#include "afxdialogex.h"
#include "ObjectMaker.h"


// CObjectMaker 대화 상자

IMPLEMENT_DYNAMIC(CObjectMaker, CDialog)

CObjectMaker::CObjectMaker(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CObjectMaker, pParent)
{

}

CObjectMaker::~CObjectMaker()
{
}

void CObjectMaker::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CObjectMaker, CDialog)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CObjectMaker 메시지 처리기


void CObjectMaker::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
