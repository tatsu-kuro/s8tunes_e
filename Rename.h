#if !defined(AFX_RENAME_H__02E8E5AA_75B0_4B9A_A601_3ABF980B350E__INCLUDED_)
#define AFX_RENAME_H__02E8E5AA_75B0_4B9A_A601_3ABF980B350E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Rename.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CRename ダイアログ

class CRename : public CDialog
{
// コンストラクション
public:
	CRename(CWnd* pParent = NULL);   // 標準のコンストラクタ
	char rnstr[100];
// ダイアログ データ
	//{{AFX_DATA(CRename)
	enum { IDD = IDD_RENAME };
	CString	m_rename;
	CString	m_rename2;
	BOOL	m_changetag;
	CString	m_changetagtxt;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CRename)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CRename)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_RENAME_H__02E8E5AA_75B0_4B9A_A601_3ABF980B350E__INCLUDED_)
