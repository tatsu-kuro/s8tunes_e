// s8tuneDoc.h : CS8tuneDoc クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_S8TUNEDOC_H__D45E635D_81E7_4303_9FCC_CCCE8AB547CE__INCLUDED_)
#define AFX_S8TUNEDOC_H__D45E635D_81E7_4303_9FCC_CCCE8AB547CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CS8tuneDoc : public CDocument
{
protected: // シリアライズ機能のみから作成します。
	CS8tuneDoc();
	DECLARE_DYNCREATE(CS8tuneDoc)

// アトリビュート
public:

// オペレーション
public:

//オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CS8tuneDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CS8tuneDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CS8tuneDoc)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_S8TUNEDOC_H__D45E635D_81E7_4303_9FCC_CCCE8AB547CE__INCLUDED_)
