// Rename.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "s8tune.h"
#include "Rename.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CRename ダイアログ


CRename::CRename(CWnd* pParent /*=NULL*/)
	: CDialog(CRename::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRename)
	m_rename = _T("");
	m_rename2 = _T("");
	m_changetag = FALSE;
	m_changetagtxt = _T("");
	//}}AFX_DATA_INIT
}


void CRename::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRename)
	DDX_Text(pDX, IDC_RENAME, m_rename);
	DDV_MaxChars(pDX, m_rename, 100);
	DDX_Text(pDX, IDC_RENAME2, m_rename2);
	DDV_MaxChars(pDX, m_rename2, 100);
	DDX_Check(pDX, IDC_CHANGETAG, m_changetag);
	DDX_Text(pDX, IDC_CHANGETAGTXT, m_changetagtxt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRename, CDialog)
	//{{AFX_MSG_MAP(CRename)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRename メッセージ ハンドラ

BOOL CRename::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText(rnstr);
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
