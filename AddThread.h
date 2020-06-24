#if !defined(AFX_ADDTHREAD_H__92324A99_2619_4ABD_946F_3F059F3D0D21__INCLUDED_)
#define AFX_ADDTHREAD_H__92324A99_2619_4ABD_946F_3F059F3D0D21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddThread.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CAddThread ダイアログ

class CAddThread : public CDialog
{
// コンストラクション
public:
	CAddThread(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CAddThread)
	enum { IDD = IDD_ADDTHREAD };
	CString	m_songpath;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CAddThread)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAddThread)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ADDTHREAD_H__92324A99_2619_4ABD_946F_3F059F3D0D21__INCLUDED_)
