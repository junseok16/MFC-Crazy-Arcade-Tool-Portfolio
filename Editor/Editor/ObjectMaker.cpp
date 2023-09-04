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
	, m_strName(_T("")), m_strHP(_T("")), m_strAttack(_T("")), m_strDefense(_T("")) {

}

CObjectMaker::~CObjectMaker()
{
}

void CObjectMaker::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Text(pDX, IDC_EDIT2, m_strHP);
	DDX_Text(pDX, IDC_EDIT3, m_strAttack);
	DDX_Text(pDX, IDC_EDIT4, m_strDefense);
	DDX_Control(pDX, IDC_LIST1, m_objectListBox);
	DDX_Control(pDX, IDC_RADIO1, m_jobRadioBtn[0]);
	DDX_Control(pDX, IDC_RADIO2, m_jobRadioBtn[1]);
	DDX_Control(pDX, IDC_RADIO3, m_jobRadioBtn[2]);
}


BEGIN_MESSAGE_MAP(CObjectMaker, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CObjectMaker::OnInsertObjectBnClicked)
	ON_BN_CLICKED(IDC_BUTTON3, &CObjectMaker::OnEraseObjectBnClicked)
	ON_LBN_SELCHANGE(IDC_LIST1, &CObjectMaker::OnObjectListLbnSelchange)
	ON_BN_CLICKED(IDC_BUTTON5, &CObjectMaker::OnFindObjectBnClicked)
END_MESSAGE_MAP()


// CObjectMaker 메시지 처리기


void CObjectMaker::OnDestroy()
{
	CDialog::OnDestroy();

	for_each(m_mapCreatureInfos.begin(), m_mapCreatureInfos.end(), SAFE_DELETE_MAP());
	m_mapCreatureInfos.clear();
}


BOOL CObjectMaker::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CObjectMaker::OnInsertObjectBnClicked()
{
	UpdateData(TRUE);
	
	CREATURE_INFO* pCretureInfo = new CREATURE_INFO();

	// 스태틱 텍스트 변수를 불러옵니다.
	pCretureInfo->strName = m_strName;
	pCretureInfo->iAttack = _ttoi(m_strAttack);
	pCretureInfo->iAttack = _ttoi(m_strDefense);
	pCretureInfo->iHP = _ttoi(m_strHP);
	
	// 라디오 버튼 변수를 불러옵니다.
	for (uint32 iIndex = 0; iIndex < 3; iIndex++)
	{
		if (m_jobRadioBtn[iIndex].GetCheck())
		{
			pCretureInfo->byJob = iIndex;
			break;
		}
	}

	/*
	// 체크 버튼 변수를 불러옵니다.
	pCretureInfo->byItem = 0x00;

	if (m_itemBtn[0].GetCheck()) { pCretureInfo->byItem |= RUBY; }
	if (m_itemBtn[1].GetCheck()) { pCretureInfo->byItem |= DIAMOND; }
	if (m_itemBtn[2].GetCheck()) { pCretureInfo->byItem |= SAPPHIRE; }
	*/

	m_objectListBox.AddString(pCretureInfo->strName);
	m_mapCreatureInfos.insert({ pCretureInfo->strName, pCretureInfo });
	UpdateData(FALSE);
}


void CObjectMaker::OnEraseObjectBnClicked()
{
	UpdateData(TRUE);

	int32 iIndex = m_objectListBox.GetCurSel();
	if (LB_ERR == iIndex) { return; }

	CString strFindName;
	m_objectListBox.GetText(iIndex, strFindName);
	m_objectListBox.DeleteString(iIndex);

	auto iter = m_mapCreatureInfos.find(strFindName);
	if (iter == m_mapCreatureInfos.end()) { return; }

	delete iter->second;
	iter->second = nullptr;
	m_mapCreatureInfos.erase(iter);

	UpdateData(FALSE);
}

void CObjectMaker::OnFindObjectBnClicked()
{
	
}

void CObjectMaker::OnObjectListLbnSelchange()
{
	UpdateData(TRUE);

	int32 iIndex = m_objectListBox.GetCurSel();
	if (LB_ERR == iIndex) { return; }

	CString strFindName;
	m_objectListBox.GetText(iIndex, strFindName);

	auto iter = m_mapCreatureInfos.find(strFindName);
	if (iter == m_mapCreatureInfos.end()) { return; }

	CString strHP;
	strHP.Format(_T("%d"), iter->second->iHP);

	CString strAttack;
	strAttack.Format(_T("%d"), iter->second->iAttack);

	m_strName = iter->second->strName;
	m_strHP = strHP;
	m_strAttack = strAttack;

	for (int32 iIndex = 0; iIndex < 3; ++iIndex)
	{
		m_jobRadioBtn[iIndex].SetCheck(FALSE);
		// m_Check[iIndex].SetCheck(FALSE);
	}

	m_jobRadioBtn[iter->second->byJob].SetCheck(TRUE);

	/*
	if (iter->second->byItem & RUBY) { m_Check[0].SetCheck(TRUE); }
	if (iter->second->byItem & DIAMOND) { m_Check[1].SetCheck(TRUE); }
	if (iter->second->byItem & SAPPHIRE) { m_Check[2].SetCheck(TRUE); }
	*/
	UpdateData(FALSE);
}
