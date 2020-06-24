#if !defined(AFX_HELPDLG_H__B6538604_0337_41E0_BAC2_92FA059AC878__INCLUDED_)
#define AFX_HELPDLG_H__B6538604_0337_41E0_BAC2_92FA059AC878__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HelpDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CHelpDlg ダイアログ

class CHelpDlg : public CDialog
{
// コンストラクション
public:
	CHelpDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CHelpDlg)
	enum { IDD = IDD_HELPDLG };
	CListBox	m_help;
	CString	m_orig;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CHelpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CHelpDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_HELPDLG_H__B6538604_0337_41E0_BAC2_92FA059AC878__INCLUDED_)
