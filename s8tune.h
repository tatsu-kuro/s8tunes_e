// s8tune.h : S8TUNE アプリケーションのメイン ヘッダー ファイル
#define VOLUM 0
#define SONGN 1
#define ISMP3 2
#define REPEA 3
#define WINXY 4
#define COLORTYPE 5
#define SONLEN 6
#define ARTLEN 7
#define TIMLEN 8
#define WIDLEN 9
#define TEMLEN 10
#define KEYLEN 11
#define PATLEN 12
#define TITLEP 13//title position +-y
#define PARA 14
#define DEFINITDX 630
#define DEFINITDY 462

#define English
//#define VaioTouch8
#ifdef English
#define TEMPOSTA "tempo : "
#define KEYSTA "key : "
#define CHANERR "\n\nwould be incorrect."
#define KYOKUNUM "Total "
#define LAMEERRMESS "Copy [Lame.exe] into the folder of [s8Tunes.exe] and you can make the mp3-file."
#define TOUROKUMESS  "songs are ready for adding."
#define ERASEMESS "Erase all songs？","sure?"
#define ERASE1MESS "Erase selected songs？","sure?"
#define SAVEBUTMESS "Save"
#define STOPBUTMESS "Stop"
#define TITLEMESS " s8Tunes (ShakuHachi Tunes) Version 12.1"
#else
#define TEMPOSTA "速さ : "
#define KEYSTA "調 : "
#define CHANERR "\n\nは、無いか、もしくは再生できません。"
#define KYOKUNUM "総曲数"
#define LAMEERRMESS "Lame.exe を s8Tunes.exe のあるフォルダにコピーすると、mp3録音可能になります。"
#define TOUROKUMESS  "曲の音楽ファイルの登録します。"
#define ERASEMESS "すべての登録を抹消しますか？","確認"
#define ERASE1MESS "選択されている曲を抹消しますか？","確認"
#define SAVEBUTMESS "保存"
#define STOPBUTMESS "停止"
#define TITLEMESS " 尺八チューンズ(s8Tunes) Version 12.1"
#endif

#if !defined(AFX_S8TUNE_H__F4FA6E2B_CAC5_41CF_B0E0_14EAED6C5E92__INCLUDED_)
#define AFX_S8TUNE_H__F4FA6E2B_CAC5_41CF_B0E0_14EAED6C5E92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CS8tuneApp:
// このクラスの動作の定義に関しては s8tune.cpp ファイルを参照してください。
//

class CS8tuneApp : public CWinApp
{
public:
	CS8tuneApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CS8tuneApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション
	//{{AFX_MSG(CS8tuneApp)
//	afx_msg void OnAppAbout();
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_S8TUNE_H__F4FA6E2B_CAC5_41CF_B0E0_14EAED6C5E92__INCLUDED_)
