// HelpDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "s8tune.h"
#include "HelpDlg.h"
#include "s8tune.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpDlg ダイアログ


CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHelpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHelpDlg)
	m_orig = _T("");
	//}}AFX_DATA_INIT
	Create(CHelpDlg::IDD,pParent);
}


void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHelpDlg)
	DDX_Control(pDX, IDC_HELPLISTBOX, m_help);
	DDX_Text(pDX, IDC_TATSUAKI, m_orig);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialog)
	//{{AFX_MSG_MAP(CHelpDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpDlg メッセージ ハンドラ

void CHelpDlg::OnOK() 
{
	DestroyWindow();		
//	CDialog::OnOK();
}

BOOL CHelpDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	char *htxt[100];
	int i,n=0;
#ifdef English
	SetWindowText("s8Tunes (Shakuhachi Tunes) Version 12.0");
	m_orig="By Tatsuaki Kuroda 2019/03/24";
	htxt[n++]="---------------------------------------------------------------";
 	htxt[n++]="              How to use the Shakuhachi Tunes";
	htxt[n++]="---------------------------------------------------------------";
	htxt[n++]="Double click the song : play the song.";
	htxt[n++]="Enter key : play the highlighted song.";
	htxt[n++]="Up & down arrow key : change the highlighted song.";
	htxt[n++]="Home, End, PgUp and PgDown : change the highlighted song.";
	htxt[n++]="A-Z keys : search the songs and highlight it.";
	htxt[n++]="Delete key : highlight and move to the current playing song.";
	htxt[n++]="Click on the upper slide-bar : move the playing position there.";
	htxt[n++]="Right & left arrow key : forward & rewind the playing position.";
	htxt[n++]="Backspace key : move to the top of the song.";
	htxt[n++]=" ";
	htxt[n++]="Mouse right click the song : go to the submenu.";
	htxt[n++]="    erase data of the selected songs : don't erase the song file.";
	htxt[n++]="    duplicate data of the song.";
	htxt[n++]="    change the song and artist name.";
	htxt[n++]=" ";
	htxt[n++]="Mouse right click the upper slide-bar : reset the A and B position.";
	htxt[n++]="Mouse right click the lower slide-bars : reset them at zero.";
	htxt[n++]="Drag and drop the songs : move the songs.";
	htxt[n++]=" ";
	htxt[n++]="CTRL+A : Change colors of the buttons etc. ";
	htxt[n++]="---------------------------------------------------------------";
	htxt[n++]="www.shaku6.com";
	htxt[n++]="---------------------------------------------------------------";
	htxt[n++]="";
#else 
	SetWindowText("尺八チューンズ  s8Tunes : Version 12.0");
	m_orig="By たつあき　2019年03月23日";
	htxt[n++]="-------------------------------------------------------------------------------";
	htxt[n++]="                        ＜ s8Tunes ＞ の概要、使い方";
	htxt[n++]="-------------------------------------------------------------------------------";
	htxt[n++]=" ";
	htxt[n++]="まず最初に、音楽ファイルを登録してください。";
	htxt[n++]="ファイルメニューの「フォルダを登録」で、フォルダの中の音楽ファイルをすべて登録できます。";
	htxt[n++]="「フォルダを登録」で、ローカルディスクドライブ全体を指定することも可能です。";
	htxt[n++]="各々の音楽ファイルをs8Tunesのウィンドウにドラッグ＆ドロップしても登録可能です。";
	htxt[n++]=" ";
	htxt[n++]="曲の選択（ハイライト表示）、演奏に関しては以下の操作が可能です。";
	htxt[n++]="   クリック：その曲の選択（ハイライト表示）。";
	htxt[n++]="   ダブルクリック：その曲の演奏開始。";
	htxt[n++]="   上下矢印、PgUp、PgDn、Home、End：それなりの曲を選択。";
	htxt[n++]="   A-Z：曲名の頭の文字を検索し、見つかったらそれを選択。";
	htxt[n++]="   Enter：選択（ハイライト表示）曲の演奏開始。";
	htxt[n++]="   Shiftキーを押しながら演奏を開始させると、キーを押した時間に応じて曲開始を遅らせます。";
	htxt[n++]="   Deleteキー：演奏中の曲を選択、表示。";
	htxt[n++]="   最上段右端当たりの丸い矢印のクリック：演奏中の曲を選択、表示。";
	htxt[n++]=" ";
	htxt[n++]="選択（ハイライト表示）曲のSPEED、KEY.CENTの変更は下段のスライドバーで行えます。";
	htxt[n++]="   KF11,F12で半音ずつ、スライドバーの左右端ボタンで5CENTずつ、";
	htxt[n++]="   スライドバー内のクリックで50CENTずつ増減できます。";
	htxt[n++]=" ";
	htxt[n++]="曲項目(複数可)をドラッグ＆ドロップして、曲項目の移動、並び替えができます。";
	htxt[n++]=" ";
	htxt[n++]="再生位置を示す上部のスクロールバーの菱形マークは左クリックで動かせます。";
	htxt[n++]="また左右矢印キーで早送り、巻き戻しが可能です。";
	htxt[n++]=" ";
	htxt[n++]="再生モードで選択曲連続、選択曲リピートを設定すると、Ctrlキー、Shiftキーで複数選択した曲を";
	htxt[n++]="再生します。複数曲が選択されてなければ、全曲を再生します。 ";
	htxt[n++]=" ";
	htxt[n++]="リストの任意の曲を右クリックすると下記のサブメニューが出ます。";
	htxt[n++]="　１）選択項目(複数可)の削除：リストから消えるだけです。";
	htxt[n++]="　　　ただし、s8Songsフォルダにある曲はファイルも削除します。";
	htxt[n++]="　２）項目の複製：音楽ファイルはそのままで、リスト上で複製するだけです。";
	htxt[n++]="　３）曲名、アーティスト名の変更：音楽ファイルのタグ情報を書き換えます。";
	htxt[n++]=" ";
	htxt[n++]="リストのタイトル部分の「曲名」「アーティスト」「時間」「テンポ」などをクリックすると、";
	htxt[n++]="その項目でソートします。";
	htxt[n++]=" ";
	htxt[n++]="範囲再生および保存の始点、終点はそれぞれ、曲の頭、曲の最後に初期設定されています。";
	htxt[n++]="任意の演奏時点で[始点]、[終点] ボタンを押すとその位置が始点、終点に設定されます。";
	htxt[n++]="始点と終点の三角マークをドラッグして始点、終点の位置を設定する事も出来ます。";
	htxt[n++]="再生バーを右クリックすると始点と終点を曲の頭と最後に再設定します。";
	htxt[n++]=" ";
	htxt[n++]="保存ボタンを押すと始点から終点までを保存します。";
	htxt[n++]="wavファイルへの保存はそのまま可能ですが、mp3ファイルへ保存するにはlame.exeが必要です。";
	htxt[n++]="lame.exeをs8Tunes.exeと同じフォルダに入れて下さい。";
	htxt[n++]="範囲再生音のファイルは、元ファイル名に連番を付記した名前で、s8Songsフォルダに保存され、";
	htxt[n++]="リストの最上部に登録されます。";
	htxt[n++]=" ";
	htxt[n++]="検索では入力文字が「曲名」「アーティスト」｢場所」に含まれる曲がリストの最上部に移動し、";
	htxt[n++]="合致した曲数が表示されます。検索文字を空白で区切ると、AND検索が出来ます。";
	htxt[n++]=" ";
	htxt[n++]="Ctrl+A で再生バー、菱形再生マークなどの色体裁を5種類から選択変更できます。";
	htxt[n++]=" ";
	htxt[n++]="-------------------------------------------------------------------------------";
	htxt[n++]="バージョンアップは下記サイトで行っています。";
	htxt[n++]="www.shaku6.com";
	htxt[n++]="-------------------------------------------------------------------------------";
	htxt[n++]="";
#endif		
	for(i=0;strlen(htxt[i])!=0;i++){
		m_help.InsertString(-1,htxt[i]);//sortしない
	}
	UpdateData(false);	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
