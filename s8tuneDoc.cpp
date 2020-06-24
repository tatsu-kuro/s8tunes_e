// s8tuneDoc.cpp : CS8tuneDoc クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "s8tune.h"

#include "s8tuneDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CS8tuneDoc

IMPLEMENT_DYNCREATE(CS8tuneDoc, CDocument)

BEGIN_MESSAGE_MAP(CS8tuneDoc, CDocument)
	//{{AFX_MSG_MAP(CS8tuneDoc)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CS8tuneDoc クラスの構築/消滅

CS8tuneDoc::CS8tuneDoc()
{
	// TODO: この位置に１度だけ呼ばれる構築用のコードを追加してください。

}

CS8tuneDoc::~CS8tuneDoc()
{
}

BOOL CS8tuneDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CS8tuneDoc シリアライゼーション

void CS8tuneDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: この位置に保存用のコードを追加してください。
	}
	else
	{
		// TODO: この位置に読み込み用のコードを追加してください。
	}
}

/////////////////////////////////////////////////////////////////////////////
// CS8tuneDoc クラスの診断

#ifdef _DEBUG
void CS8tuneDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CS8tuneDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CS8tuneDoc コマンド
