// s8tuneView.cpp : CS8tuneView クラスの動作の定義を行います。
// Version 4.3 kensaku() dispvolume() case を書き換える。こと
//10.3 タグ情報書き込み機能
#include "stdafx.h"
#include "s8tune.h"
#include "s8tuneDoc.h"
#include "s8tuneView.h"
#include "bass.h"
#include "bass_fx.h"
#include "basswma.h"
#include "bass_aac.h"
#include "bassenc.h"
#include <mbctype.h>
//#include "tags.h"
#include "Rename.h"
#include "AddThread.h"
#include <math.h>
#include <sys/stat.h> 
#include "direct.h"
#include "mmsystem.h"
#include "mp3infp_ExportFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
double CENT1=1.0005778;
HSTREAM chan;			// tempo channel handle
int songnum;
bool IsPlaying=false;
bool oyasumiF=true;//OnItemchangedSonglistでのスクロールバーの変更を停止するフラグ。起動時、フォルダ登録時はお休みする。
int ABmode=0;//0:全 1:範囲　2:録音
DWORD RGBsysbtn,RGBbtn,RGBhisi,RGBa2b,RGBwaku,RGBsumi;
bool BARtype;
int WSx,WSy;//window size
int ltimex,ltimey,rtimex,rtimey;
int SliderF=0;
int SliderMark=1;//1:left 2:hisigata 3:right
int posbutton;
int sankakuzure;
int VolumeF=0;
int FocusListKen;
int RepeatMode;
int findnum=-1;
int kensakutype=0;//0:song 1:artist 2:path
bool ChangeCursor=false;
int dragstart,dragend;
double playpos;
double ChanL,ChanA,ChanB;
int songlen,posa,posb;//それぞれ上記の10倍のint
char curdir[301],recordfn[301],inipath[301],listpath[301],temppath[301],s8sfolder[301],kasifolder[301],jpgfn[300];
//static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
HSTREAM Bass_StreamCreate(char *fn);
int checkpos(CPoint pos);
UINT CopyDirSongThread( LPVOID dammy );
int FindFocused(CListCtrl *m_songlist);
char *getEN(char *s);
//void GetNameArtist(HSTREAM tchan,char *fn,char *name,char *artist);
//void GetNameArtist_sub(char *fn,char *name);
bool isfile1(char *fn);
bool IsLameEncoder();
int IsSong(char *s);
char *seta2bstr(char *a2b,int a,int b);
void sleeptimelag();
#define KOIMARU 1
#define USUMARU 2
#define F11_F12 4
#define WAVoMP3 8
#define FOUNDNUM 16
#define REPEATD 32
//#define DISPTOTAL 32
//1:● 2:○ 4:F1-F12 8:wav/mp3 16:FOUNDNUM
void DispIroiro(CDC *pDC,CBitmap *m_bitmap_volume,int pos,int f);//f==1 丸を濃く f==2 表示だけ
#define DISPSPEED 1
#define DISPCENT 2
#define DISPKEY 4
#define DISPTOTAL 8
void DispTotal(CDC *pDC,CBitmap *m_bitmap_volume);

CListCtrl	m_songlist;
DWORD Timelag=0;
#define s8name 0
#define s8arti 1
#define s8time 2
#define s8a2b 3
#define s8tempo 4
//#define s8cent 5
#define s8key 5
#define s8path 6
//HMODULE hMp3infpDll;// = LoadLibrary("mp3infp.dll");
//#pragma comment(lib, "mp3infp.dll")

char s8strs[9][301];
char *ptext[]={
	"Volume:",
	"PlayingSongNumber:",
	"SaveMode(wav,mp3):",
	"RepeatMode(one_1,one_r,all_1,all_r):",
	"WindowRect(x,y,x2,y2,maxF):",
	"BarColorType:",
	"SongCol:",
	"ArtCol:",
	"TimeCol:",
	"Start-EndCol:",
	"TempoCol:",
//	"CentCol:",
	"KeyCol:",
	"FullpathCol:",
	"Song Title Y position:"
};

char *ptextdef[]={"50","0","wav","one_1","20,20,680,560,1","0","200","150","80","150","60","60","500","8"};
char ptxt[15][200];

int s8dx=0,s8dy=0;//上部部品および下部部品の移動幅
//#volume
#define VX0 (s8dx+133)//to where
#define VY0 61
//再生バー
#define X0 (s8dx+19)
#define Y0 28//30
#define WI 594
#define HE 12//10
//f1 f2 f3 wav の文字並びのy
#define F12Y Y0+23
//slider
//	setctrl(m_bartempo,s8dx+8,WSy-24,290,17);	
//	setctrl(m_barkey,s8dx+319,WSy-24,290,17);

#define SPEEDX1 (s8dx+15)
#define SPEEDX2 (s8dx+290)
#define SPEEDY1 (WSy-24)
#define SPEEDY2 (WSy-7)
//#define CENTX1 (s8dx+230)
//#define CENTX2 (s8dx+398)
#define KEYX1 (s8dx+326)
#define KEYX2 (s8dx+600)
/////////////////////////////////////////////////////////////////////////////
// CS8tuneView

IMPLEMENT_DYNCREATE(CS8tuneView, CFormView)

BEGIN_MESSAGE_MAP(CS8tuneView, CFormView)
	//{{AFX_MSG_MAP(CS8tuneView)
	ON_WM_HSCROLL()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_NOTIFY(NM_DBLCLK, IDC_SONGLIST, OnDblclkSonglist)
	ON_NOTIFY(NM_RCLICK, IDC_SONGLIST, OnRclickSonglist)
	ON_COMMAND(ID_DELETEONE, OnDeleteone)
	ON_COMMAND(ID_DUPLICATE, OnDuplicate)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_SONGLIST, OnColumnclickSonglist)
	ON_BN_CLICKED(IDC_REWIND, OnRewind)
	ON_BN_CLICKED(IDC_SETA, OnSeta)
	ON_BN_CLICKED(IDC_SETB, OnSetb)
	ON_BN_CLICKED(IDC_START2, OnStart2)
	ON_BN_CLICKED(IDC_REWIND2, OnRewind2)
	ON_COMMAND(ID_RENAME, OnRename)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_ADDFOLDER, OnAddfolder)
	ON_COMMAND(ID_DELETEALL, OnDeleteall)
	ON_BN_CLICKED(IDC_KENSAKU, OnKensaku)
	ON_COMMAND(ID_RETURN, OnReturn)
	ON_BN_CLICKED(IDC_HOZON, OnHozon)
	ON_COMMAND(IDC_WAVERECORD, OnWaverecord)
	ON_UPDATE_COMMAND_UI(IDC_WAVERECORD, OnUpdateWaverecord)
	ON_EN_SETFOCUS(IDC_KENSAKUSTR, OnSetfocusKensakustr)
	ON_NOTIFY(NM_SETFOCUS, IDC_SONGLIST, OnSetfocusSonglist)
	ON_COMMAND(IDC_MP3RECORD, OnMp3record)
	ON_UPDATE_COMMAND_UI(IDC_MP3RECORD, OnUpdateMp3record)
	ON_WM_DROPFILES()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDC_TOCUSONG, OnTocusong)
	ON_COMMAND(ID_ADDFILES, OnAddfiles)
	ON_COMMAND(IDC_REPEATON, OnRepeaton)
	ON_UPDATE_COMMAND_UI(IDC_REPEATON, OnUpdateRepeaton)
	ON_COMMAND(IDC_REPEATOFF, OnRepeatoff)
	ON_UPDATE_COMMAND_UI(IDC_REPEATOFF, OnUpdateRepeatoff)
	ON_WM_SETCURSOR()
	ON_NOTIFY(LVN_BEGINDRAG, IDC_SONGLIST, OnBegindragSonglist)
	ON_COMMAND(IDC_RENZOKU, OnRenzoku)
	ON_COMMAND(IDC_RENZOKUREPEAT, OnRenzokurepeat)
	ON_UPDATE_COMMAND_UI(IDC_RENZOKUREPEAT, OnUpdateRenzokurepeat)
	ON_UPDATE_COMMAND_UI(IDC_RENZOKU, OnUpdateRenzoku)
	ON_BN_CLICKED(IDC_TONEXT, OnTonext)
	ON_BN_CLICKED(IDC_TONEXT2, OnTonext2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_SONGLIST, OnItemchangedSonglist)
	ON_BN_CLICKED(IDC_TONOW, OnTonow)
	ON_COMMAND(ID_CTRL_A, OnCtrlA)
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_KENSAKUSTR, OnChangeKensakustr)
	ON_BN_DOUBLECLICKED(IDC_START, OnDoubleclickedStart)
	ON_BN_CLICKED(IDC_KENSAKUTYPE, OnKensakutype)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_PAUSE1, OnPause1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CS8tuneView クラスの構築/消滅

CS8tuneView::CS8tuneView()
	: CFormView(CS8tuneView::IDD)
{
//	if(__argc>=2)exit(0);//AfxGetMainWnd()->PostMessage(WM_CLOSE);
	//{{AFX_DATA_INIT(CS8tuneView)
	m_songname = _T("");
	m_kensakustr = _T("");
	//}}AFX_DATA_INIT
	// TODO: この場所に構築用のコードを追加してください。
	if(__argc>=2)exit(0);//AfxGetMainWnd()->PostMessage(WM_CLOSE);
}

CS8tuneView::~CS8tuneView()
{
}
void CS8tuneView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CS8tuneView)
	DDX_Control(pDX, IDC_KENSAKUTYPE, m_kentypectrl);
	DDX_Control(pDX, IDC_PAUSE1, m_pause2);
	DDX_Control(pDX, IDC_PAUSE, m_pause);
	DDX_Control(pDX, IDC_TONOW, m_tonow);
	DDX_Control(pDX, IDC_SONGNAME, m_s_songname);
	DDX_Control(pDX, IDC_KENSAKU, m_kensaku);
	DDX_Control(pDX, IDC_TONEXT2, m_tonext2);
	DDX_Control(pDX, IDC_TONEXT, m_tonext);
	DDX_Control(pDX, IDC_HOZON, m_hozon);
	DDX_Control(pDX, IDC_START2, m_start2);
	DDX_Control(pDX, IDC_START, m_start);
	DDX_Control(pDX, IDC_REWIND2, m_rewind2);
	DDX_Control(pDX, IDC_REWIND, m_rewind);
	DDX_Control(pDX, IDC_SETB, m_setb);
	DDX_Control(pDX, IDC_SETA, m_seta);
	DDX_Control(pDX, IDC_KENSAKUSTR, m_kensakuctl);
	DDX_Control(pDX, IDC_SCROLLBARTEMPO, m_bartempo);
	DDX_Control(pDX, IDC_SCROLLBARKEY, m_barkey);
	DDX_Text(pDX, IDC_SONGNAME, m_songname);
	DDX_Text(pDX, IDC_KENSAKUSTR, m_kensakustr);
	DDX_Control(pDX, IDC_SONGLIST, m_songlist);
	//}}AFX_DATA_MAP
}

/*

		[MP3]                   ID3v1       ID3v2       RiffSIF     APE
		フォーマット(※1)       "AFMT"      "AFMT"      "AFMT"      "AFMT"
		演奏時間(※1)           "TIME"      "TIME"      "TIME"      "TIME"
		タイトル                "INAM_v1"   "INAM_v2"   "INAM_rmp"  "INAM_APE"
		アーティスト            "IART_v1"   "IART_v2"   "IART_rmp"  "IART_APE"
		アルバム                "IPRD_v1"   "IPRD_v2"   "IPRD_rmp"  "IPRD_APE"
		コメント                "ICMT_v1"   "ICMT_v2"   "ICMT_rmp"  "ICMT_APE"
		作成日                  "ICRD_v1"   "ICRD_v2"   "ICRD_rmp"  "ICRD_APE"
		ジャンル                "IGNR_v1"   "IGNR_v2"   "IGNR_rmp"  "IGNR_APE"
		(ID3v2/RiffSIF)
		著作権                              "ICOP_v2"   "ICOP_rmp"
		ソフトウェア/エンコーダ             "ISFT_v2"   "ISFT_rmp"
		(ID3v2)
		作曲                                "COMP_v2"
		Orig.アーティスト                   "OART_v2"
		URL                                 "URL_v2"
		エンコードした人                    "ENC2_v2"
		(RiffSIF)
		ソース                                          "ISRC_rmp"
		エンジニア                                      "IENG_rmp"
		(ID3v1/2)
		トラック番号            "TRACK_v1"  "TRACK_v2"              "TRACK_APE"

		[WAV]
		フォーマット(※1)       "AFMT"
		演奏時間(※1)           "TIME"
		タイトル(※2)           "INAM"
		タイトル(※2)           "ISBJ"
		アーティスト            "IART"
		アルバム                "IPRD"
		コメント                "ICMT"
		作成日                  "ICRD"
		ジャンル                "IGNR"
		著作権                  "ICOP"
		ソフトウェア            "ISFT"
		ソース                  "ISRC"
		エンジニア              "IENG"

		[AVI]
		音声フォーマット(※1)   "AFMT"
		映像フォーマット(※1)   "VFMT"
		時間(※1)               "TIME"
		タイトル(※2)           "INAM"
		タイトル(※2)           "ISBJ"
		アーティスト            "IART"
		コメント                "ICMT"
		作成日                  "ICRD"
		ジャンル                "IGNR"
		著作権                  "ICOP"
		ソフトウェア            "ISFT"
		ソース                  "ISRC"
		エンジニア              "IENG"
		AVIバージョン           "AVIV"    (v2.37～)

		[VQF]
		フォーマット(※1)       "AFMT"
		演奏時間(※1)           "TIME"
		タイトル                "INAM"
		アーティスト            "IART"
		コメント                "ICMT"
		著作権                  "ICOP"
		保存名                  "FILE"

		[WMA]
		音声フォーマット(※1)   "AFMT"
		映像フォーマット(※1)   "VFMT"
		時間(※1)               "TIME"
		タイトル                "INAM"
		トラック                "TRACK"
		アーティスト            "IART"
		アルバム                "IPRD"
		コメント                "ICMT"
		作成日                  "ICRD"
		ジャンル                "IGNR"
		著作権                  "ICOP"
		URL(Album)              "URL1"
		URL(関連)               "URL2"


*/

HMODULE m_hMp3infpDll;
LPMP3INFP_GETVER m_mp3infp_GetVer;
LPMP3INFP_LOAD m_mp3infp_Load;
LPMP3INFP_VIEWPROP m_mp3infp_ViewProp;
LPMP3INFP_GETTYPE m_mp3infp_GetType;
LPMP3INFP_GETVALUE m_mp3infp_GetValue;
LPMP3INFP_MP3_GETTAGTYPE m_mp3infp_mp3_GetTagType;
LPMP3INFP_SETCONF m_mp3infp_SetConf;
LPMP3INFP_SETVALUE m_mp3infp_SetValue;
LPMP3INFP_SAVE m_mp3infp_Save;
LPMP3INFP_MP3_MAKEID3V1 m_mp3infp_mp3_MakeId3v1;
LPMP3INFP_MP3_DELID3V1 m_mp3infp_mp3_DelId3v1;
LPMP3INFP_MP3_MAKEID3V2 m_mp3infp_mp3_MakeId3v2;
LPMP3INFP_MP3_DELID3V2 m_mp3infp_mp3_DelId3v2;
LPMP3INFP_MP3_MAKERMP m_mp3infp_mp3_MakeRMP;
LPMP3INFP_MP3_DELRMP m_mp3infp_mp3_DelRMP;
LPMP3INFP_MP3_MAKEAPETAG m_mp3infp_mp3_MakeApeTag;
LPMP3INFP_MP3_DELAPETAG m_mp3infp_mp3_DelApeTag;

bool setmp3infp(char *fn,char *strTitle,char *strArtist) 
{
	m_hMp3infpDll = LoadLibrary("mp3infp.dll");
	if(m_hMp3infpDll == NULL)
	{
		AfxMessageBox("mp3infpをロードできませんでした");
		return false;
	}

	m_mp3infp_GetVer = (LPMP3INFP_GETVER )GetProcAddress(m_hMp3infpDll,"mp3infp_GetVer");
	// バージョンチェック
	if(m_mp3infp_GetVer && (m_mp3infp_GetVer() < 0x0243))
	{
		AfxMessageBox("mp3infp v2.43以上が必要です");
		FreeLibrary(m_hMp3infpDll);
		return false;
	}

	m_mp3infp_Load = (LPMP3INFP_LOAD )GetProcAddress(m_hMp3infpDll,"mp3infp_Load");
	m_mp3infp_ViewProp = (LPMP3INFP_VIEWPROP )GetProcAddress(m_hMp3infpDll,"mp3infp_ViewProp");
	m_mp3infp_GetType = (LPMP3INFP_GETTYPE )GetProcAddress(m_hMp3infpDll,"mp3infp_GetType");
	m_mp3infp_GetValue = (LPMP3INFP_GETVALUE )GetProcAddress(m_hMp3infpDll,"mp3infp_GetValue");
	m_mp3infp_mp3_GetTagType = (LPMP3INFP_MP3_GETTAGTYPE )GetProcAddress(m_hMp3infpDll,"mp3infp_mp3_GetTagType");
	m_mp3infp_SetConf = (LPMP3INFP_SETCONF )GetProcAddress(m_hMp3infpDll,"mp3infp_SetConf");
	m_mp3infp_SetValue = (LPMP3INFP_SETVALUE )GetProcAddress(m_hMp3infpDll,"mp3infp_SetValue");
	m_mp3infp_Save = (LPMP3INFP_SAVE )GetProcAddress(m_hMp3infpDll,"mp3infp_Save");
	m_mp3infp_mp3_MakeId3v1 = (LPMP3INFP_MP3_MAKEID3V1 )GetProcAddress(m_hMp3infpDll,"mp3infp_mp3_MakeId3v1");
	m_mp3infp_mp3_DelId3v1 = (LPMP3INFP_MP3_DELID3V1 )GetProcAddress(m_hMp3infpDll,"mp3infp_mp3_DelId3v1");
	m_mp3infp_mp3_MakeId3v2 = (LPMP3INFP_MP3_MAKEID3V2 )GetProcAddress(m_hMp3infpDll,"mp3infp_mp3_MakeId3v2");
	m_mp3infp_mp3_DelId3v2 = (LPMP3INFP_MP3_DELID3V2 )GetProcAddress(m_hMp3infpDll,"mp3infp_mp3_DelId3v2");
	m_mp3infp_mp3_MakeRMP = (LPMP3INFP_MP3_MAKERMP )GetProcAddress(m_hMp3infpDll,"mp3infp_mp3_MakeRMP");
	m_mp3infp_mp3_DelRMP = (LPMP3INFP_MP3_DELRMP )GetProcAddress(m_hMp3infpDll,"mp3infp_mp3_DelRMP");
	m_mp3infp_mp3_MakeApeTag = (LPMP3INFP_MP3_MAKEAPETAG )GetProcAddress(m_hMp3infpDll,"mp3infp_mp3_MakeApeTag");
	m_mp3infp_mp3_DelApeTag = (LPMP3INFP_MP3_DELAPETAG )GetProcAddress(m_hMp3infpDll,"mp3infp_mp3_DelApeTag");
	//DLLのロード
	if(m_mp3infp_Load(NULL,fn) != ERROR_SUCCESS)
	{
		AfxMessageBox("ロード失敗");
		FreeLibrary(m_hMp3infpDll);
		return false;
	}

	DWORD dwTagType;
	DWORD dwType = m_mp3infp_GetType();
	switch(dwType){
	case MP3INFP_FILE_MP3:
		dwTagType = m_mp3infp_mp3_GetTagType();
		if(dwTagType & MP3INFP_HAS_MP3_ID3V2)
		{
			m_mp3infp_SetValue("INAM_v2",(LPCTSTR )strTitle);
			m_mp3infp_SetValue("IART_v2",(LPCTSTR )strArtist);
		}
		else if(dwTagType & MP3INFP_HAS_MP3_RIFFSIF)
		{
			m_mp3infp_SetValue("INAM_rmp",(LPCTSTR )strTitle);
			m_mp3infp_SetValue("IART_rmp",(LPCTSTR )strArtist);
		}
		else if(dwTagType & MP3INFP_HAS_MP3_ID3V1)
		{
			m_mp3infp_SetValue("INAM_v1",(LPCTSTR )strTitle);
			m_mp3infp_SetValue("IART_v1",(LPCTSTR )strArtist);
		}
		else if((dwTagType & MP3INFP_HAS_MP3_APEV1) || (dwTagType & MP3INFP_HAS_MP3_APEV2))
		{
			m_mp3infp_SetValue("INAM_APE",(LPCTSTR )strTitle);
			m_mp3infp_SetValue("IART_APE",(LPCTSTR )strArtist);
		}else{//タグ情報が無いときはID3V2を作って書き込む VaioNoteでは上手く行ったり行かなかったり
			DWORD dwRet = m_mp3infp_mp3_MakeId3v2((LPCTSTR )fn);
			if(dwRet != ERROR_SUCCESS)
			{
				CString strMes;
				strMes.Format("Fail code=%08x",dwRet);
				AfxMessageBox(strMes);
				FreeLibrary(m_hMp3infpDll);
				return false;
			}
			m_mp3infp_SetValue("INAM_v2",(LPCTSTR )strTitle);
			m_mp3infp_SetValue("IART_v2",(LPCTSTR )strArtist);
/*			m_mp3infp_SetValue("INAM_APE",(LPCTSTR )strTitle);
			m_mp3infp_SetValue("IART_APE",(LPCTSTR )strArtist);
*/		}
		break;
	case MP3INFP_FILE_WAV:
	case MP3INFP_FILE_AVI:
		m_mp3infp_SetValue("ISBJ","");
		m_mp3infp_SetValue("INAM",(LPCTSTR )strTitle);
		m_mp3infp_SetValue("IART",(LPCTSTR )strArtist);
		break;
	case MP3INFP_FILE_VQF:
	case MP3INFP_FILE_WMA:
	case MP3INFP_FILE_OGG:
	case MP3INFP_FILE_APE:
	case MP3INFP_FILE_MP4:
		m_mp3infp_SetValue("INAM",(LPCTSTR )strTitle);
		m_mp3infp_SetValue("IART",(LPCTSTR )strArtist);
		break;
	case MP3INFP_FILE_UNKNOWN:
	default:
		break;
	}
	// Save
	DWORD dwRet = m_mp3infp_Save((LPCTSTR )fn);
	if(dwRet != ERROR_SUCCESS)
	{
		CString strMes;
		strMes.Format("Fail code=%08x",dwRet);
		AfxMessageBox(strMes);
		FreeLibrary(m_hMp3infpDll);
		return false;
	}
	FreeLibrary(m_hMp3infpDll);
	return true;
}
//void CMp3infp_sample2Dlg::OnButtonLoad() 
void GetNameArtist(char *fn,char *strTitle,char *strArtist)
{
	strcpy(strTitle,"");
	strcpy(strArtist,"");
	m_hMp3infpDll = LoadLibrary("mp3infp.dll");
	if(m_hMp3infpDll == NULL)
	{
		AfxMessageBox("mp3infpをロードできませんでした");
		return;// false;
	}

	m_mp3infp_GetVer = (LPMP3INFP_GETVER )GetProcAddress(m_hMp3infpDll,"mp3infp_GetVer");
	// バージョンチェック
	if(m_mp3infp_GetVer && (m_mp3infp_GetVer() < 0x0243))
	{
		AfxMessageBox("mp3infp v2.43以上が必要です");
		FreeLibrary(m_hMp3infpDll);
		return;// false;
	}

	m_mp3infp_Load = (LPMP3INFP_LOAD )GetProcAddress(m_hMp3infpDll,"mp3infp_Load");
	m_mp3infp_ViewProp = (LPMP3INFP_VIEWPROP )GetProcAddress(m_hMp3infpDll,"mp3infp_ViewProp");
	m_mp3infp_GetType = (LPMP3INFP_GETTYPE )GetProcAddress(m_hMp3infpDll,"mp3infp_GetType");
	m_mp3infp_GetValue = (LPMP3INFP_GETVALUE )GetProcAddress(m_hMp3infpDll,"mp3infp_GetValue");
	m_mp3infp_mp3_GetTagType = (LPMP3INFP_MP3_GETTAGTYPE )GetProcAddress(m_hMp3infpDll,"mp3infp_mp3_GetTagType");
	m_mp3infp_SetConf = (LPMP3INFP_SETCONF )GetProcAddress(m_hMp3infpDll,"mp3infp_SetConf");
	m_mp3infp_SetValue = (LPMP3INFP_SETVALUE )GetProcAddress(m_hMp3infpDll,"mp3infp_SetValue");
	m_mp3infp_Save = (LPMP3INFP_SAVE )GetProcAddress(m_hMp3infpDll,"mp3infp_Save");
	m_mp3infp_mp3_MakeId3v1 = (LPMP3INFP_MP3_MAKEID3V1 )GetProcAddress(m_hMp3infpDll,"mp3infp_mp3_MakeId3v1");
	m_mp3infp_mp3_DelId3v1 = (LPMP3INFP_MP3_DELID3V1 )GetProcAddress(m_hMp3infpDll,"mp3infp_mp3_DelId3v1");
	m_mp3infp_mp3_MakeId3v2 = (LPMP3INFP_MP3_MAKEID3V2 )GetProcAddress(m_hMp3infpDll,"mp3infp_mp3_MakeId3v2");
	m_mp3infp_mp3_DelId3v2 = (LPMP3INFP_MP3_DELID3V2 )GetProcAddress(m_hMp3infpDll,"mp3infp_mp3_DelId3v2");
	m_mp3infp_mp3_MakeRMP = (LPMP3INFP_MP3_MAKERMP )GetProcAddress(m_hMp3infpDll,"mp3infp_mp3_MakeRMP");
	m_mp3infp_mp3_DelRMP = (LPMP3INFP_MP3_DELRMP )GetProcAddress(m_hMp3infpDll,"mp3infp_mp3_DelRMP");
	m_mp3infp_mp3_MakeApeTag = (LPMP3INFP_MP3_MAKEAPETAG )GetProcAddress(m_hMp3infpDll,"mp3infp_mp3_MakeApeTag");
	m_mp3infp_mp3_DelApeTag = (LPMP3INFP_MP3_DELAPETAG )GetProcAddress(m_hMp3infpDll,"mp3infp_mp3_DelApeTag");
	//DLLのロード
	if(m_mp3infp_Load(NULL,fn) != ERROR_SUCCESS)
	{
		AfxMessageBox("ロード失敗");
		FreeLibrary(m_hMp3infpDll);
		return;// false;
	}

	// Load
	DWORD dwRet = m_mp3infp_Load(NULL,(LPCTSTR )fn);
	if(dwRet != ERROR_SUCCESS)
	{
		CString strMes;
		strMes.Format("Fail code=%08x",dwRet);
		AfxMessageBox(strMes);
		return;
	}
	char *value;
	DWORD dwTagType;
	DWORD dwType = m_mp3infp_GetType();
	switch(dwType){
	case MP3INFP_FILE_MP3:
		dwTagType = m_mp3infp_mp3_GetTagType();
		if((dwTagType & MP3INFP_HAS_MP3_APEV1) || (dwTagType & MP3INFP_HAS_MP3_APEV2))
		{
			m_mp3infp_GetValue("INAM_APE",&value);
			strcpy(strTitle,value);
			m_mp3infp_GetValue("IART_APE",&value);
			strcpy(strArtist,value);
		}
		else if(dwTagType & MP3INFP_HAS_MP3_ID3V2)
		{
			m_mp3infp_GetValue("INAM_v2",&value);
			strcpy(strTitle,value);
			m_mp3infp_GetValue("IART_v2",&value);
			strcpy(strArtist,value);
		}
		else if(dwTagType & MP3INFP_HAS_MP3_RIFFSIF)
		{
			m_mp3infp_GetValue("INAM_rmp",&value);
			strcpy(strTitle,value);
			m_mp3infp_GetValue("IART_rmp",&value);
			strcpy(strArtist,value);
		}
		else if(dwTagType & MP3INFP_HAS_MP3_ID3V1)
		{
			m_mp3infp_GetValue("INAM_v1",&value);
			strcpy(strTitle,value);
			m_mp3infp_GetValue("IART_v1",&value);
			strcpy(strArtist,value);
		}
		break;
	case MP3INFP_FILE_WAV:
		m_mp3infp_GetValue("INAM",&value);
		strcpy(strTitle,value);
		m_mp3infp_GetValue("IART",&value);
		strcpy(strArtist,value);
		break;
	case MP3INFP_FILE_AVI:
		m_mp3infp_GetValue("INAM",&value);
		strcpy(strTitle,value);
		m_mp3infp_GetValue("IART",&value);
		strcpy(strArtist,value);
		break;
	case MP3INFP_FILE_VQF:
		m_mp3infp_GetValue("INAM",&value);
		strcpy(strTitle,value);
		m_mp3infp_GetValue("IART",&value);
		strcpy(strArtist,value);
		break;
	case MP3INFP_FILE_WMA:
		m_mp3infp_GetValue("INAM",&value);
		strcpy(strTitle,value);
		m_mp3infp_GetValue("IART",&value);
		strcpy(strArtist,value);
		break;
	case MP3INFP_FILE_OGG:
		m_mp3infp_GetValue("INAM",&value);
		strcpy(strTitle,value);
		m_mp3infp_GetValue("IART",&value);
		strcpy(strArtist,value);
		break;
	case MP3INFP_FILE_APE:
		m_mp3infp_GetValue("INAM",&value);
		strcpy(strTitle,value);
		m_mp3infp_GetValue("IART",&value);
		strcpy(strArtist,value);
		break;
	case MP3INFP_FILE_MP4:
		m_mp3infp_GetValue("INAM",&value);
		strcpy(strTitle,value);
		m_mp3infp_GetValue("IART",&value);
		strcpy(strArtist,value);
		break;
	case MP3INFP_FILE_UNKNOWN:
	default:
		break;
	}
	FreeLibrary(m_hMp3infpDll);
}
int CS8tuneView::SetSongCnt()
{	//曲数を表示して、その数を返す。//	setctrl(m_s_songnum,,,140,17);	
	CDC *pDC=GetDC();
//	CDC MemDC;
//	CBitmap *pOldBmp;
//	int sc=m_songlist.GetItemCount();
//	DispIroiro(pDC,&m_bitmap_volume,0,sc,DISPTOTAL);
	DispTotal(pDC,&m_bitmap_volume);

//	MemDC.CreateCompatibleDC(pDC);
//	pOldBmp=MemDC.SelectObject(&m_bitmap_volume);
//	int x=s8dx+548,y=WSy-22,x1=0,y1=32,xd=8,yd=11,d=8;
//	pDC->FillSolidRect(x,y,60,11,RGBsysbtn);
//	pDC->FillSolidRect(x,y,60,11,RGB(0,0,0));
//	pDC->BitBlt(x+0*d,y,xd,yd,&MemDC,x1+d*((sc/10000)%10),y1,SRCAND);
//	pDC->BitBlt(x+1*d,y,xd,yd,&MemDC,x1+d*((sc/1000)%10),y1,SRCAND);
//	pDC->BitBlt(x+2*d,y,xd,yd,&MemDC,x1+d*((sc/100)%10),y1,SRCAND);
//	pDC->BitBlt(x+3*d,y,xd,yd,&MemDC,x1+d*((sc/10)%10),y1,SRCAND);
//	pDC->BitBlt(x+4*d,y,xd,yd,&MemDC,x1+d*(sc%10),y1,SRCAND);
//	MemDC.SelectObject(pOldBmp);
//	DeleteDC(MemDC);
	ReleaseDC(pDC);
//	char buf[20];
//	sprintf(buf,"%s %05d",KYOKUNUM,sc);
//	*cs=buf;
	return m_songlist.GetItemCount();
}
void ChangeBtnColor(CDC *pDC,CBitmap *bit,DWORD rgb1,DWORD rgb2)//システムのボタンの背景色をセットする。
{
	int x,y;
	CDC MemDC;
	CBitmap *pOldBmp;
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(bit);
	for(x=0;x<150;x++){
		for(y=0;y<50;y++){
			if(rgb1==MemDC.GetPixel(x,y))MemDC.SetPixel(x,y,rgb2);
		}
	}
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}
void CS8tuneView::ChangeBtnsColor(DWORD rgb1,DWORD rgb2)
{
	CDC *pDC=GetDC();
	ChangeBtnColor(pDC,&m_bitmap_pause,rgb1,rgb2);
	ChangeBtnColor(pDC,&m_bitmap_play,rgb1,rgb2);
	ChangeBtnColor(pDC,&m_bitmap_totop,rgb1,rgb2);
	ChangeBtnColor(pDC,&m_bitmap_tonext,rgb1,rgb2);
	ChangeBtnColor(pDC,&md_bitmap_pause,rgb1,rgb2);
	ChangeBtnColor(pDC,&md_bitmap_play,rgb1,rgb2);
	ChangeBtnColor(pDC,&md_bitmap_totop,rgb1,rgb2);
	ChangeBtnColor(pDC,&md_bitmap_tonext,rgb1,rgb2);
	ChangeBtnColor(pDC,&m_bitmap_tonow,rgb1,rgb2);
	ChangeBtnColor(pDC,&m_bitmap_seta,rgb1,rgb2);
	ChangeBtnColor(pDC,&m_bitmap_setb,rgb1,rgb2);
	ChangeBtnColor(pDC,&m_bitmap_saveab,rgb1,rgb2);
	ChangeBtnColor(pDC,&m_bitmap_stop,rgb1,rgb2);
	ChangeBtnColor(pDC,&m_bitmap_retr,rgb1,rgb2);
	ChangeBtnColor(pDC,&m_bitmap_kensong,rgb1,rgb2);
	ChangeBtnColor(pDC,&m_bitmap_kenartist,rgb1,rgb2);
	ChangeBtnColor(pDC,&m_bitmap_kenpath,rgb1,rgb2);
	ReleaseDC(pDC);
}

void CS8tuneView::SetButtons(){
	if(ABmode==2){

		ChangeBtnsColor(RGBsysbtn,RGB(255,255,255));//背景色をもとの状態に戻さないとfalseが不自然となる。（バックを白にしないと）
		m_seta.EnableWindow(false);
		m_setb.EnableWindow(false);
		m_start.EnableWindow(false);
		m_start2.EnableWindow(false);
		m_rewind.EnableWindow(false);
		m_rewind2.EnableWindow(false);
		m_pause.EnableWindow(false);
		m_pause2.EnableWindow(false);
		m_tonext.EnableWindow(false);
		m_tonext2.EnableWindow(false);
		//灰色に設定
		CDC *pDC=GetDC();
		ChangeBtnColor(pDC,&m_bitmap_stop,RGB(255,255,255),RGBsysbtn);
		ReleaseDC(pDC);
		m_hozon.SetBitmap(m_bitmap_stop);
		m_kensaku.EnableWindow(false);
	}else{
		ChangeBtnsColor(RGB(255,255,255),RGBsysbtn);//背景色を灰色に設定する
		m_rewind.EnableWindow(true);
		m_pause.EnableWindow(true);
		m_start.EnableWindow(true);
		m_tonext.EnableWindow(true);
		m_rewind2.EnableWindow(true);
		m_pause2.EnableWindow(true);
		m_start2.EnableWindow(true);
		m_tonext2.EnableWindow(true);
		m_seta.EnableWindow(true);
		m_setb.EnableWindow(true);
		m_hozon.SetBitmap(m_bitmap_saveab);
		m_kensaku.EnableWindow(true);
	}
}
static void InitFNames()
{
	CStdioFile ff;
	char buf[301];
	//exeファイルのフルパスを取得
	::GetModuleFileName(NULL,curdir,sizeof curdir);
	curdir[strlen(curdir)-strlen("s8tunes.exe")-1]='\0';
	sprintf(inipath,"%s\\s8Tunes.ini",curdir);
	sprintf(listpath,"%s\\s8Tunes_list.s8",curdir);
	sprintf(temppath,"%s\\s8Tunes_temp.txt",curdir);
	sprintf(s8sfolder,"%s\\s8Songs",curdir);
	mkdir(s8sfolder);
	sprintf(kasifolder,"%s\\kasigazou",curdir);
	mkdir(kasifolder);
	sprintf(buf,"%s\\%s",kasifolder,"enkakasi.txt");
	if(!ff.Open(buf,CFile::modeRead|CFile::typeText))
	{
#ifdef English
		ff.Open(buf,CFile::modeCreate|CFile::modeWrite|CFile::modeRead|CFile::typeText);
		ff.WriteString("rem　rem-lines are nothing.\n");
		ff.WriteString("rem　\n");
		ff.WriteString("rem　kawano.mp3,kawano.jpg\n");
		ff.WriteString("rem　\n");
		ff.WriteString("rem　above line means that \n");
		ff.WriteString("rem　if you play kawano.mp3 , the kawano.jpg would be displayed.\n");
		ff.WriteString("rem　\n");
		ff.WriteString("rem　put the kawano.jpg file in the kasigazou folder.\n");
		ff.Abort();
#else
		ff.Open(buf,CFile::modeCreate|CFile::modeWrite|CFile::modeRead|CFile::typeText);
		ff.WriteString("rem　行頭に rem のある行は無視します。\n");
		ff.WriteString("rem　\n");
		ff.WriteString("rem　たとへば\n");
		ff.WriteString("rem　kawano.mp3,kawano.jpg\n");
		ff.WriteString("rem　の１行があれば kawano.mp3 が始まるとき kawano.jpg を開きます。\n");
		ff.WriteString("rem　kawano.jpg をダブルクリックしたのと同じ動作をします。\n");
		ff.WriteString("rem　kawano.jpg はこのkasigazouフォルダに置いて下さい。\n");
		ff.Abort();
#endif
	}
}
int GetInt(char *buf)
{
	int num;
	sscanf(buf,"%d",&num);
	return num;
}


void CS8tuneView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	int sc;
	oyasumiF=true;
	SetFontSize();
	InitFNames();//	GetCurrentDirectory(300,curdir);

	BASS_Init(1,44100,0,0,NULL);
	m_barkey.SetScrollRange(-240,240,true);
	m_bartempo.SetScrollRange(25,300,true);
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(320);
	//左右の何にもないとこでもtipがでるが・・・
	m_playbarrect.left=X0;
	m_playbarrect.top=Y0;
	m_playbarrect.right=X0+WI+500;
	m_playbarrect.bottom=Y0+HE;
	readini();
 #ifdef English
	m_ToolTip.AddTool(&m_tonow, "Show the playing song.\nSame as Delete-key.");
  	m_ToolTip.AddTool(&m_kentypectrl, "Change what's retrieved.");
	m_ToolTip.AddTool(&m_rewind, "Move to the top of the song. (F1,Backspace-key)");
 	m_ToolTip.AddTool(&m_rewind2, "Move to the A-position of the song. (F6,Backspace-key)");
 	m_ToolTip.AddTool(&m_tonext, "Move to the next song's top. (F3)");
 	m_ToolTip.AddTool(&m_tonext2, "Move to the A-position of the next song. (F8)");
 	m_ToolTip.AddTool((CButton *)GetDlgItem(IDC_KENSAKU), "Move the results from 'title' and 'artist' at the top of the list.\nPut the space for AND-search. (Enter-key)");
 	m_ToolTip.AddTool(&m_hozon, "Save the song(from A to B) to a file.");
 	m_ToolTip.AddTool(&m_seta, "Set the position to A. ");
 	m_ToolTip.AddTool(&m_setb, "Set the position to B. ");
	m_ToolTip.AddTool(&m_bartempo,"Right click to reset the tempo.\nShift+F11,Shift+F12 to change it.");
	m_ToolTip.AddTool(&m_barkey,"Right click to reset the key.\nF11,F12:half tone, side-buttons:5cent,\nclick on bar area:50cent.");
	m_ToolTip.AddTool(this,IDS_PLAYBARRECT,&m_playbarrect,IDS_PLAYBARRECT);
	m_ToolTip.AddTool(&m_songlist,"Right click to MENU. Drag and drop the items to move them.\nClick the item headder( song_title, artist_name etc) to sort.");
#else
	m_ToolTip.AddTool(&m_tonow, "演奏中の曲を表示します。\nDelete キーと同。");
	m_ToolTip.AddTool(&m_kentypectrl, "検索の対象を変更します。");
	m_ToolTip.AddTool(&m_rewind, "曲の頭に再生ポイントを移動します。（F1,Backspace-Key）");
 	m_ToolTip.AddTool(&m_rewind2, "範囲再生の始点に移動します。（F6,Backspace-Key）");
 	m_ToolTip.AddTool(&m_tonext, "次の曲の頭に移動します。（F3）");
 	m_ToolTip.AddTool(&m_tonext2, "次の曲の範囲再生の始点に移動します。（F8）");
 	m_ToolTip.AddTool((CButton *)GetDlgItem(IDC_KENSAKU), "曲名、アーティストもしくは場所から検索し、結果をリストの最上部に移動します。空白で区切るとand検索します。(Enter-key)");
 	m_ToolTip.AddTool(&m_hozon, "始点から終点までの再生音をファイルに保存します。");
 	m_ToolTip.AddTool(&m_seta, "現在の再生位置を始点にセットします。");
 	m_ToolTip.AddTool(&m_setb, "現在の再生位置を終点にセットします。");
	m_ToolTip.AddTool(&m_bartempo,"右クリックすると速さをリセットします。\nShift+F11,Shift+F12で増減します。");
	m_ToolTip.AddTool(&m_barkey,"右クリックすると調をリセットします。\nF11,F12で半音、両端ボタンで5セント、バー内のクリックで50セント増減します。");
	m_ToolTip.AddTool(this,IDS_PLAYBARRECT,&m_playbarrect,IDS_PLAYBARRECT);
	m_ToolTip.AddTool(&m_songlist,"右クリックでメニューがでます。\n曲をドラッグ＆ドロップすると移動します。\n曲名などの項目ヘッダーをクリックすると、その項目でソートします。");
#endif

	m_pImageList = new CImageList; 
	ASSERT( m_pImageList != NULL ); 
	int nGrow=1;	// nGrowはイメージを確保する数 
	m_pImageList->Create( IDB_SPEAKER, 16,nGrow, RGB(0xff,0xff,0xff) ); 
	m_songlist.SetImageList( m_pImageList, LVSIL_SMALL );

#ifdef English

	m_songlist.InsertColumn(s8name,"    song title", LVCFMT_LEFT,GetInt(ptxt[SONLEN]));//SONGCLMLEN);//LVCFMT_LEFT、LVCFMT_RIGHT、または LVCFMT_CENTER。
	m_songlist.InsertColumn(s8arti,"artist name" , LVCFMT_LEFT,GetInt(ptxt[ARTLEN]));//ARTCLLEN);
	m_songlist.InsertColumn(s8time,"time" , LVCFMT_CENTER, GetInt(ptxt[TIMLEN]));
	m_songlist.InsertColumn(s8a2b,"A - B" , LVCFMT_CENTER,GetInt(ptxt[WIDLEN]));
	m_songlist.InsertColumn(s8tempo,"tempo" , LVCFMT_CENTER,GetInt(ptxt[TEMLEN]));
	m_songlist.InsertColumn(s8key,"key.cent" , LVCFMT_RIGHT, GetInt(ptxt[KEYLEN]));
	m_songlist.InsertColumn(s8path,"full path" , LVCFMT_LEFT,GetInt(ptxt[PATLEN]));
#else
	m_songlist.InsertColumn(s8name,"    曲名", LVCFMT_LEFT,GetInt(ptxt[SONLEN]));//185 178
	m_songlist.InsertColumn(s8arti,"アーティスト" , LVCFMT_LEFT,GetInt(ptxt[ARTLEN]));//100 90
	m_songlist.InsertColumn(s8time,"時間" , LVCFMT_CENTER,GetInt(ptxt[TIMLEN]));
	m_songlist.InsertColumn(s8a2b,"始点－終点" , LVCFMT_CENTER,GetInt(ptxt[WIDLEN]));
	m_songlist.InsertColumn(s8tempo,"速さ" , LVCFMT_CENTER, GetInt(ptxt[TEMLEN]));
	m_songlist.InsertColumn(s8key,"調.cent" , LVCFMT_RIGHT, GetInt(ptxt[KEYLEN]));
	m_songlist.InsertColumn(s8path,"場所" ,LVCFMT_LEFT,GetInt(ptxt[PATLEN]));//65 75
#endif

	/////////////////////////////////////////////////////////////////
	CRect rect;
	int maxF;
//	readini();
	SetBarColor(0);
	sscanf(ptxt[WINXY],"%d,%d,%d,%d,%d",&rect.left,&rect.top,&rect.right,&rect.bottom,&maxF);
	CWnd* pW=GetParent( ); // 親ウィンドウ(主ウィンドウ)のポインタを得ます。
	pW->MoveWindow( &rect ); // 指定した座標のウィンドウを描きます。
	if(maxF==1)AfxGetMainWnd()->PostMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
	read_s8t();
	if(strstr(ptxt[REPEA],"one_1"))RepeatMode=0;
	else if(strstr(ptxt[REPEA],"one_r"))RepeatMode=1;
	else if(strstr(ptxt[REPEA],"all_1"))RepeatMode=2;
	else RepeatMode=3;
	m_songlist.SetExtendedStyle(m_songlist.GetExtendedStyle()|LVS_EX_SUBITEMIMAGES|LVS_EX_FULLROWSELECT);
	m_bitmap_volume.LoadBitmap(IDB_VOLUME);
	m_bitmap_totop.LoadBitmap(IDB_TOTOP);
	md_bitmap_totop.LoadBitmap(IDB_TOTOP1);
	m_bitmap_play.LoadBitmap(IDB_PLAY);
	md_bitmap_play.LoadBitmap(IDB_PLAY1);
	m_bitmap_pause.LoadBitmap(IDB_PAUSE);
	md_bitmap_pause.LoadBitmap(IDB_PAUSE1);//disableにするビットマップは背景色をセットしない。
	m_bitmap_tonext.LoadBitmap(IDB_TONEXT);
	md_bitmap_tonext.LoadBitmap(IDB_TONEXT1);
	m_bitmap_tonow.LoadBitmap(IDB_TONOW);
	m_bitmap_seta.LoadBitmap(IDB_SETA);
	m_bitmap_setb.LoadBitmap(IDB_SETB);
	m_bitmap_saveab.LoadBitmap(IDB_SAVEAB);
	m_bitmap_stop.LoadBitmap(IDB_STOP);
	m_bitmap_retr.LoadBitmap(IDB_RETR);
	m_bitmap_kensong.LoadBitmap(IDB_KENSONG);
	m_bitmap_kenartist.LoadBitmap(IDB_KENARTIST);
	m_bitmap_kenpath.LoadBitmap(IDB_KENPATH);
	RGBsysbtn=GetSysColor(COLOR_BTNFACE);
	ChangeBtnsColor(RGB(255,255,255),RGBsysbtn);//背景色を
//	ChangeBtnsColor(RGB(255,0,0),RGBbtn);//レッドを
	m_tonow.SetBitmap(m_bitmap_tonow);
//	SetButtons();
	m_rewind.SetBitmap(m_bitmap_totop);
	m_pause.SetBitmap(m_bitmap_pause);
	m_start.SetBitmap(m_bitmap_play);
	m_tonext.SetBitmap(m_bitmap_tonext);
	m_rewind2.SetBitmap(md_bitmap_totop);
	m_pause2.SetBitmap(md_bitmap_pause);
	m_start2.SetBitmap(md_bitmap_play);
	m_tonext2.SetBitmap(md_bitmap_tonext);
	m_seta.SetBitmap(m_bitmap_seta);
	m_setb.SetBitmap(m_bitmap_setb);
	m_hozon.SetBitmap(m_bitmap_saveab);
	m_kensaku.SetBitmap(m_bitmap_retr);
	m_kentypectrl.SetBitmap(m_bitmap_kensong);

	// ボタンにビットマップをセットします。
	m_songname="shaku8Tunes";
	sc=SetSongCnt();
	SetTimer(1,100,NULL);
	UpdateData(false);
	DragAcceptFiles();
//カーソル
	m_hCursor = (HCURSOR)LoadImage( 
				AfxGetInstanceHandle(), 
				MAKEINTRESOURCE(IDC_CURDROP),
				IMAGE_CURSOR,
				32, 32,
				LR_DEFAULTSIZE | LR_SHARED );

	sscanf(ptxt[SONGN],"%d",&songnum);
	oyasumiF=false;
	if(sc>0){
		m_songlist.SetFocus();
		if(songnum>=sc)songnum=0;
		IsPlaying=false;
		StartSong(songnum,false);
		OnTocusong();
	}
}
/////////////////////////////////////////////////////////////////////////////
// CS8tuneView クラスの診断

#ifdef _DEBUG
void CS8tuneView::AssertValid() const
{
	CFormView::AssertValid();
}

void CS8tuneView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CS8tuneDoc* CS8tuneView::GetDocument() // 非デバッグ バージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CS8tuneDoc)));
	return (CS8tuneDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CS8tuneView クラスのメッセージ ハンドラ

int match(char *fj,char *ed)
{
	while(*ed!='\0'){
		if(*fj!=*ed)return(0);
		fj++;ed++;
	}
	return(1);
}
#ifdef English
char *strkan(char *fj,char *ed)
{
	return strstr(fj,ed);
}

#else
char *strkan(char *fj,char *ed)
{
	while(strstr(fj,ed)){
			while(1){
				if(match(fj,ed))return fj;
				if(_ismbblead(*fj)){
					fj++;fj++;
					if(match((fj-1),ed))break;
				}
				else fj++;
			}
			if(*fj=='\0')return NULL;
	}
	return NULL;
}
#endif

char *gets8t(char* str)
{
	int i,len;
	char *s="<s8t>";
	len=strlen(str);
	for(i=len-3;i>=0;i--){
		if(strstr(&str[i],s)){
			str[i]=0;
			return &str[i+strlen(s)];
		}
	}
	return str;
}

char * cntstrone(char *s,char *b1)
{
	char *p;
	if(p=strkan(s,b1)){
		return p+strlen(b1);
	}
	return 0;
}
//version10.9 不正なデータリストをチェックするようイチャモンを付けられたので、以下のように長さを制限してみた。
int CS8tuneView::InsertItemBuf(char *buf,int n)
{//データ(buf)をitem-nに書き込むみ、書き込んだ位置(n?)を返す。
	int i,c;
	for(i=7;i>=0;i--)strcpy(s8strs[i],gets8t(buf));
	c=m_songlist.InsertItem(n,NULL,1);
	if(strlen(s8strs[s8time])<300)m_songlist.SetItemText(c,s8name,s8strs[s8name]);
	if(strlen(s8strs[s8time])<300)m_songlist.SetItemText(c,s8arti,s8strs[s8arti]);
	if(strlen(s8strs[s8time])<10)m_songlist.SetItemText(c,s8time,s8strs[s8time]);
	if(strlen(s8strs[s8tempo])<10)m_songlist.SetItemText(c,s8tempo,s8strs[s8tempo]);
//	if(strlen(s8strs[s8cent])<10)m_songlist.SetItemText(c,s8cent,s8strs[s8cent]);
	if(strlen(s8strs[s8key])<10)m_songlist.SetItemText(c,s8key,s8strs[s8key]);
	if(strlen(s8strs[s8path])<MAX_PATH)m_songlist.SetItemText(c,s8path,s8strs[s8path]);
	if(strlen(s8strs[s8a2b])<20)m_songlist.SetItemText(c,s8a2b,s8strs[s8a2b]);
	return c;
}
void CS8tuneView::sets8strs(char *buf,int i)
{
	m_songlist.GetItemText(i,s8name,s8strs[s8name],300);
	m_songlist.GetItemText(i,s8arti,s8strs[s8arti],300);
	m_songlist.GetItemText(i,s8time,s8strs[s8time],300);
	m_songlist.GetItemText(i,s8tempo,s8strs[s8tempo],300);
//	m_songlist.GetItemText(i,s8cent,s8strs[s8cent],300);
	m_songlist.GetItemText(i,s8key,s8strs[s8key],300);
	m_songlist.GetItemText(i,s8path,s8strs[s8path],300);
	m_songlist.GetItemText(i,s8a2b,s8strs[s8a2b],300);
	sprintf(buf,"%s<s8t>%s<s8t>%s<s8t>%s<s8t>%s<s8t>%s<s8t>%s<s8t>%s",s8strs[0],s8strs[1],s8strs[2],s8strs[3],s8strs[4],s8strs[5],s8strs[6]);//,s8strs[8]);//,s8strs[9]);
}

void CS8tuneView::AddSongFile(char *fn,char *name,char *artist,int mlen)
{
	char *p,*pp,buf[31];
	if(strlen(name)==0){
		pp=fn;
		while(p=strkan(pp,"\\")){
			pp=p+1;
		}
		strcpy(name,pp);
	}
	m_songlist.InsertItem(0,NULL,1);//m_songlist.1(LVIF_TEXT|LVIF_IMAGE, 0,NULL, 0,0,-1, 0);
	m_songlist.SetItemText(0,s8name,name);
	sprintf(buf,"%02d:%02d",mlen/600,(mlen/10)%60);
	m_songlist.SetItemText(0,s8time, buf);
	m_songlist.SetItemText(0,s8tempo,"100%");
//	m_songlist.SetItemText(0,s8cent,"+0");
	m_songlist.SetItemText(0,s8key,"+0.00");
	m_songlist.SetItemText(0,s8path,fn);
	seta2bstr(buf,0,mlen);
	m_songlist.SetItemText(0,s8a2b,buf);
	m_songlist.SetItemText(0,s8arti,artist);
}
/*
void GetNameArtist_sub(char *fn,char *name)
{
	char *p,*pp;
	pp=fn;
	while(p=strkan(pp,"\\")){
		pp=p+1;
	}
	strcpy(name,pp);
}


void GetNameArtist(HSTREAM tchan,char *fn,char *name,char *artist)
{
	strcpy(artist,TAGS_Read(tchan, "%ARTI"));
	strcpy(name,TAGS_Read(tchan, "%TITL"));
	if(strlen(artist)==0){
		strcpy(artist,"unknown");
	}
	if(strlen(name)==0){
		GetNameArtist_sub(fn,name);
	}
}*/

HSTREAM Bass_StreamCreate(char *fn)
{
	HSTREAM tchan    = BASS_StreamCreateFile(FALSE, fn, 0, 0, BASS_STREAM_DECODE);
	if(!tchan) tchan = BASS_WMA_StreamCreateFile(FALSE,fn,0,0, BASS_STREAM_DECODE);
	if(!tchan) tchan = BASS_AAC_StreamCreateFile(FALSE,fn,0, 0, BASS_STREAM_DECODE);
	if(!tchan) tchan = BASS_MP4_StreamCreateFile(FALSE,fn,0, 0, BASS_STREAM_DECODE);
	if(!tchan) tchan = BASS_MusicLoad(FALSE, fn, 0, 0, BASS_MUSIC_RAMP|BASS_MUSIC_PRESCAN|BASS_STREAM_DECODE,0);
	return tchan;
}

void CS8tuneView::SetStr(int tck,int p,int sn)//tck:tempo2 key4 f=0ならバーのpositionをセットしない
{
	char buf[20];
	if(tck==s8tempo){
		if(p<100)sprintf(buf," %d%%",p);
		else sprintf(buf,"%d%%",p);//-75%  200%
	}else{
		if(p>=0)sprintf(buf,"+%d.%02d",(p*5)/100,(p*5)%100);//-75%  200%
		else{
			p=-p;
			sprintf(buf,"-%d.%02d",(p*5)/100,(p*5)%100);
		}
	}
	if(sn>=0){
		m_songlist.SetItemText(sn,tck,buf);
		SetKeyCent(sn,0);
	}
}
void CS8tuneView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) /* スクロールバー */
{
//	double dd;//,CENT1=1.0005778;
//	float freq;
	int p,maxp,minp,F,si;
	if(pScrollBar==GetDlgItem(IDC_SCROLLBARKEY) ) F=0;
//	else if(pScrollBar==GetDlgItem(IDC_SCROLLBARCENT) ) F=1; 
	else if(pScrollBar==GetDlgItem(IDC_SCROLLBARTEMPO) ) F=1;
	else // 主ウィンドウ用のスクロールバーがクリックされたときは、
	{
		CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
		return; 
	}
	p = pScrollBar->GetScrollPos();// スクロールボックス(ツマミ)の現在位置を得ます。
	pScrollBar->GetScrollRange(&minp, &maxp);
	// ユーザがどんな操作をしたか
	switch (nSBCode)
	{
	case SB_THUMBPOSITION:
		p = nPos;
		break;
	case SB_LINELEFT:
		if (p > minp)
			p--;
		break;
	case SB_LINERIGHT:
		if (p < maxp)
			p++;
		break;
	case SB_PAGELEFT:
		p -= 10;
		if (p < minp)
			p = minp;
		break;
	case SB_PAGERIGHT:
		p += 10;
		if (p > maxp)
			p = maxp;
		break;
	case SB_LEFT:
		p = minp;
		break;
	case SB_RIGHT:
		p = maxp;
		break;
	case SB_THUMBTRACK:
		p = nPos;
		break;
	}
	pScrollBar->SetScrollPos(p,TRUE);

	if((si=FindFocused(&m_songlist))!=-1){
		if(F==0){//key
			if(songnum==si)
				BASS_ChannelSetAttribute(chan, BASS_ATTRIB_TEMPO_PITCH, (float)p/float(20));//MESS(IDC_TEMPO, TBM_GETPOS, 0, 0));
			SetStr(s8key,p,si);
		}else if(F==1){//tempo
			if(songnum==si)
				BASS_ChannelSetAttribute(chan, BASS_ATTRIB_TEMPO, (float)(p-100));
			SetStr(s8tempo,p,si);		
		}
		if(songnum==si)SetSongsSelected(songnum,1);
	}
	UpdateData(false);
	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CS8tuneView::OnDestroy() 
{
	CFormView::OnDestroy();
	sprintf(ptxt[SONGN],"%d",songnum);
	sprintf(ptxt[SONLEN],"%d",m_songlist.GetColumnWidth(0));
	sprintf(ptxt[ARTLEN],"%d",m_songlist.GetColumnWidth(1));
	sprintf(ptxt[TIMLEN],"%d",m_songlist.GetColumnWidth(2));
	sprintf(ptxt[WIDLEN],"%d",m_songlist.GetColumnWidth(3));
	sprintf(ptxt[TEMLEN],"%d",m_songlist.GetColumnWidth(4));
//	sprintf(ptxt[CENLEN],"%d",m_songlist.GetColumnWidth(5));
	sprintf(ptxt[KEYLEN],"%d",m_songlist.GetColumnWidth(5));
	sprintf(ptxt[PATLEN],"%d",m_songlist.GetColumnWidth(6));
	writeini();
	KillTimer(1);
	BASS_StreamFree(chan);chan=NULL;
	BASS_Free();
}
void CS8tuneView::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==1){
		CDC* pDC=GetDC();
		DispSongA2B(pDC);
		ReleaseDC(pDC);
	}
	CFormView::OnTimer(nIDEvent);
}

void CS8tuneView::DragDrop(int si) 
{
	char buf[3001];
	int i,imagen;
	ChangeCursor=false;
	if(si>=dragstart&&si<=dragend+1)return;
	if(si<dragstart){//移動する複数項目の中には移動しない
		for(i=dragstart;i<=dragend;i++,si++){
			sets8strs(buf,i);
			imagen=GetItemImagen(i);
			m_songlist.DeleteItem(i);
			SetItemImage(InsertItemBuf(buf,si),imagen);
		}
	}else if(si>dragend+1){
		for(i=0;i<=dragend-dragstart;i++,si++){
			sets8strs(buf,dragstart);
			imagen=GetItemImagen(dragstart);
			m_songlist.DeleteItem(dragstart);
			SetItemImage(InsertItemBuf(buf,--si),imagen);
		}
	}
	SetSongsSelected(si-dragend+dragstart-1,dragend-dragstart+1);
	if((songnum=GetSongnum(m_songlist.GetItemCount()))==-1)MessageBox("DragDrop Error");
	UpdateData(false);
}

int subgets2bint(char *buf)
{
	int a,b,c;
	sscanf(buf,"%d:%d.%d",&a,&b,&c);
	return a*600+b*10+c;
}
void gets2bint(char *a2b,int *a,int *b)
{
	char buf1[30],buf2[30];
	strcpy(buf2,strstr(a2b,"-")+1);
	strcpy(buf1,a2b);
	*strstr(buf1,"-")=0;
	*a=subgets2bint(buf1);
	*b=subgets2bint(buf2);
}
char *seta2bstr(char *a2b,int a,int b)
{
	char buf1[20],buf2[20];
	sprintf(buf1,"%02d:%02d.%d",a/600,(a%600)/10,a%10);
	sprintf(buf2,"%02d:%02d.%d",b/600,(b%600)/10,b%10);
	sprintf(a2b,"%s-%s",buf1,buf2);
	return a2b;
}
void kasihyouji()
{
	if(strlen(jpgfn)>3&&isfile1(jpgfn))ShellExecute (NULL, NULL, jpgfn, NULL, NULL, SW_SHOWDEFAULT);
}
void kasijpgset(char *fn)
{
	int i;
	char buf[500],sfn[100];
	CStdioFile ff;
	for(i=strlen(fn);i>0;i--){
		if(fn[i]=='\\')break;
	}
	if(fn[i]=='\\')strcpy(sfn,&fn[i+1]);
	else return;
	sprintf(buf,"%s\\%s",kasifolder,"enkakasi.txt");
	if(ff.Open(buf,CFile::modeRead|CFile::typeText))
	{
		strcpy(jpgfn,"");
		while(ff.ReadString(buf,395)){
			if(buf[0]=='r'&&buf[1]=='e'&&buf[2]=='m')continue;
			if(strstr(buf,",")&&strstr(buf,sfn)){
				sprintf(jpgfn,"%s\\%s",kasifolder,strstr(buf,",")+1);//,の次の文字から
				if(strstr(jpgfn,"\n"))strcpy(strstr(jpgfn,"\n"),"");//改行は除去
//				if(strlen(jpgfn)>3&&isfile1(jpgfn))ShellExecute (NULL, NULL, jpgfn, NULL, NULL, SW_SHOWDEFAULT);
			}
		}
		ff.Abort();
	}
//	else{
//		ff.Open(buf,CFile::modeCreate|CFile::modeWrite|CFile::modeRead|CFile::typeText);
//		ff.WriteString("rem　行頭に rem のある行は無視します。\n");
//		ff.WriteString("rem　\n");
//		ff.WriteString("rem　たとへば\n");
//		ff.WriteString("rem　kawano.mp3,kawano.jpg\n");
//		ff.WriteString("rem　の１行があれば kawano.mp3 が始まるとき kawano.jpg を開きます。\n");
//		ff.WriteString("rem　kawano.jpg をダブルクリックしたのと同じ動作をします。\n");
//		ff.WriteString("rem　kawano.jpg はこのフォルダに置いて下さい。\n");
//		ff.Abort();
//	}
}
void sleeptimelag()
{
	if(Timelag!=0){//Timelagが設定されていれば
		DWORD timelag;
		timelag=timeGetTime();
		timelag=timeGetTime()-Timelag;
		Timelag=0;
		if(timelag<2000)timelag=2000;
		else if(timelag>10000)timelag=10000;
		Sleep(timelag);
	}
}

void CS8tuneView::StartSong(int sn,bool flag) 
{
	int i,sc,p,volume;
//	double dd;
//	float freq;
	char path[401],buf[1000],para[31],a2b[31];
	playpos=0;
	if(m_songlist.GetItemCount()==0)return;
	if(chan){
		BASS_StreamFree(chan);chan=NULL;
	}
	m_songlist.GetItemText(sn,s8path,path,300);
	chan=Bass_StreamCreate(path);
	kasijpgset(path);//jpgfnをセットするだけ
	if(chan)ChanL=BASS_ChannelBytes2Seconds(chan,BASS_ChannelGetLength(chan, BASS_POS_BYTE));
	else ChanL=0;
	m_songlist.GetItemText(sn,s8a2b,a2b,30);
	gets2bint(a2b,&posa,&posb);
	ChanA=(double)posa/10.0;
	ChanB=(double)posb/10.0;
	songlen=int(ChanL*10);
//	if(chan)BASS_ChannelGetAttribute(chan, BASS_ATTRIB_FREQ, &freq);
	// create a new stream - decoded & resampled :)	
	if(chan){
		if (!(chan=BASS_FX_TempoCreate(chan, BASS_SAMPLE_LOOP|BASS_FX_FREESOURCE))){
			BASS_StreamFree(chan);
			BASS_MusicFree(chan);
			chan=NULL;
		}
	}
	//volume set
	sscanf(ptxt[VOLUM],"%d",&volume);
	if(chan)BASS_ChannelSetAttribute(chan, BASS_ATTRIB_VOL,float(volume)/100.0f);// (float)p/100.0f);
	//key
	m_songlist.GetItemText(sn,s8key,para,19);
	sscanf(para,"%d",&p);
	if(chan)BASS_ChannelSetAttribute(chan, BASS_ATTRIB_TEMPO_PITCH, (float)p);
	//cent
//	m_songlist.GetItemText(sn,s8cent,para,19);
//	sscanf(para,"%d",&p);
//	if(p>=0)dd=pow(CENT1,p);
//	else dd=1.0f/pow(CENT1,-p);
//	if(chan){
//		BASS_ChannelGetAttribute(chan, BASS_ATTRIB_FREQ, &freq);
//		BASS_ChannelSetAttribute(chan, BASS_ATTRIB_TEMPO_FREQ, (float)freq*(float)dd);
//	}
	//tempo
	m_songlist.GetItemText(sn,s8tempo,para,19);
	sscanf(para,"%d%%",&p);
	if(chan)BASS_ChannelSetAttribute(chan, BASS_ATTRIB_TEMPO, (float)(p-100));
	if(ABmode==1&&chan)BASS_ChannelSetPosition(chan, (QWORD)BASS_ChannelSeconds2Bytes(chan,ChanA),NULL);
	if(IsPlaying==true&&chan){
		kasihyouji();
		sleeptimelag();
		BASS_ChannelPlay(chan,FALSE);
	}
	m_songlist.GetItemText(sn,s8name,buf,300);
	m_songname=buf;
	sc=m_songlist.GetItemCount();
	if(!chan)IsPlaying=false;
	SetItemImage(sn,(IsPlaying ? 0:2));//スピーカー表示
	for(i=0;i<sc;i++){
		if(i!=sn)SetItemImage(i,1);//スピーカー表示を消す
	}
	UpdateData(false);
	if(!chan&&flag){
		strcat(path,CHANERR);
		MessageBox(path);
	}
}

void CS8tuneView::OnDblclkSonglist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int sn=FindFocused(&m_songlist);
	if(ABmode==2)return;
	if(sn==songnum&&chan){
		if(IsPlaying==true){
			IsPlaying=false;
			BASS_ChannelPause(chan);
		}else{
			IsPlaying=true;
			sleeptimelag();
			BASS_ChannelPlay(chan,FALSE);
			kasihyouji();
		}
	}else{
		IsPlaying=true;
		StartSong(songnum=sn);
	}
	SetItemImage(songnum,(IsPlaying ? 0:2));//
//	SetButtons();
}
void CS8tuneView::OnRclickSonglist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(ABmode==2)return;
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_MENU1));
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CPoint point;
	GetCursorPos(&point);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x, point.y,AfxGetMainWnd());
	*pResult = 0;
}
void CS8tuneView::OnDeleteone() 
{
	char fn[501],fn1[501];
	int lasts,i,sc=m_songlist.GetItemCount();
	if(sc==0)return;
	oyasumiF=true;
	for(i=sc-1;i>=0;i--){
		if(m_songlist.GetItemState(i,LVIS_SELECTED)!=0){
			m_songlist.GetItemText(i,s8path,fn,299);
			lasts=i;
			if(GetItemImagen(i)!=1){//スピーカー付きの場合 0:演奏停止中 1:演奏中の曲ではない 2:演奏中
				BASS_StreamFree(chan);chan=NULL;
			}
			m_songlist.DeleteItem(i);
			sprintf(fn1,"%s\\s8Songs",curdir);
			if(strstr(fn,fn1)){
				if(isfile1(fn))CFile::Remove(fn);
			}
		}
	}
	sc=SetSongCnt();//m_songlist.GetItemCount();
	if((songnum=GetSongnum(sc))==-1){//スピーカー付きアイテムがなくなっている。
		IsPlaying=false;
		songnum=lasts;
		if(sc>0)StartSong(songnum,false);
	}
//	SetButtons();
	oyasumiF=false;
	UpdateData(false);
}
void CS8tuneView::OnDuplicate() 
{
	char buf[3001];
	int si=FindFocused(&m_songlist);
	if(si<0)return;
	if(songnum>=si)songnum++;
	sets8strs(buf,si);
	InsertItemBuf(buf,si);
	SetSongCnt();
	UpdateData(false);
}
int CALLBACK CS8tuneView::MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
//	CS8tuneView* pDlg = (CS8tuneView*)AfxGetMainWnd();
//	CString    cstr1 = pDlg->m_songlist.GetItemText(lParam1,lParamSort%100);// nSubItem);
//	CString    cstr2 = pDlg->m_songlist.GetItemText(lParam2,lParamSort%100);// nSubItem);
	CString    cstr1 = m_songlist.GetItemText(lParam1,lParamSort%100);// nSubItem);
	CString    cstr2 = m_songlist.GetItemText(lParam2,lParamSort%100);// nSubItem);
	if(lParamSort%100==8){//8 は回数
		CString str1="00000"+cstr1;
		CString str2="00000"+cstr2;
		if(lParamSort>99)return strcmp(str1.Right(5), str2.Right(5));
		else return strcmp(str2.Right(5), str1.Right(5));
	}
	if(lParamSort>99)return strcmp(cstr1, cstr2);
	else return strcmp(cstr2, cstr1);

}
void CS8tuneView::RenumberItem(int sub)
{
	LV_ITEM lvItem;
	int sc=m_songlist.GetItemCount();
	// m_list1はCListCtrl型のDDX変数で、ソートを行うリストビューコントロールのオブジェクトであるものとする
	for( int i = 0; i <sc ; i++ ) {
		lvItem.iItem = i;
		lvItem.iSubItem = 0;
		lvItem.mask = LVIF_PARAM;
		lvItem.lParam = i;		// ここで番号をアイテムに指定する
		m_songlist.SetItem(&lvItem);
	}
}
void CS8tuneView::OnColumnclickSonglist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int i,sm,sc,n1,n2;
	if(ChangeCursor==true)return;
	oyasumiF=true;
	NM_LISTVIEW* pNMLV = (NM_LISTVIEW*)pNMHDR;
	static int sortf[15]={0,0,0,0,0,0,0,0,0,0,0};
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	sm = pNMLV->iSubItem;
	sc = m_songlist.GetItemCount();
	if(sc>0){
		if(sortf[sm]==1)sortf[sm]=0;
		else sortf[sm]=1;
		RenumberItem(sm);
		m_songlist.SortItems( MyCompareProc,sm+sortf[sm]*100);
		if((songnum=GetSongnum(sc))==-1)MessageBox("Sort Error");
	}
	*pResult = 0;
	//tohilight
	for(i=0;i<sc;i++){
		if(m_songlist.GetItemState(i,LVIS_SELECTED)!=0){
//			m_songlist.SetFocus();
			SetSongsSelected(i,1);
			if(i+5<sc)n1=i+5;
			else n1=sc-1;
			m_songlist.EnsureVisible(n1, FALSE);
			if(i-5>0)n2=i-5;
			else n2=0;
			m_songlist.EnsureVisible(n2, FALSE);
			m_songlist.EnsureVisible(i, FALSE);
			break;
		}
	}
	oyasumiF=false;
}

//#define DISPTOTAL 32
//1:● 2:○ 4:F1-F12 8:wav/mp3 16:FOUNDNUM
void DispIroiro(CDC *pDC,CBitmap *m_bitmap_volume,int pos,int f)//f==1 丸を濃く f==2 表示だけ
{
	int volume;
	CDC MemDC;
	CBitmap *pOldBmp;
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(m_bitmap_volume);
	if(f&REPEATD){
		int x=X0-25,y=Y0+32;
		pDC->FillSolidRect(x,y,20,20,RGBsysbtn);
		if(strstr(ptxt[REPEA],"one_r"))pDC->BitBlt(x,y,20,20,&MemDC,139,0,SRCAND);
		if(strstr(ptxt[REPEA],"all_r"))pDC->BitBlt(x,y,20,20,&MemDC,139,20,SRCAND);
		if(strstr(ptxt[REPEA],"one_1"))pDC->BitBlt(x,y,20,20,&MemDC,139,20*2,SRCAND);
		if(strstr(ptxt[REPEA],"all_1"))pDC->BitBlt(x,y,20,20,&MemDC,139,20*3,SRCAND);
	}
	if(f&FOUNDNUM){
		int x=X0+479,y=F12Y-5,x1=0,y1=0,xd=8,yd=9,d=8,dd=8;
		pDC->FillSolidRect(x,y,32,9,RGBsysbtn);
		if(findnum>-1){
//			int x1=36,y1=23,xd=5,yd=7,d=5,dd=5;
			pDC->BitBlt(x+0*dd,y,xd,yd,&MemDC,x1+d*((findnum/1000)%10),y1,SRCAND);
			pDC->BitBlt(x+1*dd,y,xd,yd,&MemDC,x1+d*((findnum/100)%10),y1,SRCAND);
			pDC->BitBlt(x+2*dd,y,xd,yd,&MemDC,x1+d*((findnum/10)%10),y1,SRCAND);
			pDC->BitBlt(x+3*dd,y,xd,yd,&MemDC,x1+d*(findnum%10),y1,SRCAND);//129
			pDC->BitBlt(x+4*dd+1,y,xd,yd,&MemDC,129,y1,SRCAND);//  /
		}
	}
	if(f&F11_F12){//f1-f12 wav,mp3の描画
		//f1-f12を表示
		int x[14]={8,52,97,127,193,222,267,311,442};
		int i;
		for(i=0;i<9;i++){
			if(i==4||i==3)pDC->BitBlt(X0+x[i],F12Y-2,14,10,&MemDC,14*i,77,SRCAND);
			else pDC->BitBlt(X0+x[i],F12Y-4,14,10,&MemDC,14*i,77,SRCAND);
		}//WSy=rect.bottom;
		int t[7]={16,286,401-149,527};
		pDC->FillSolidRect(s8dx+ 15,WSy-28,289,3,RGB(110,110,110));
		pDC->FillSolidRect(s8dx+321,WSy-28,293,3,RGB(110,110,110));
//		pDC->FillSolidRect(s8dx+15,WSy-44,289,1,RGB(210,210,210));
//		pDC->FillSolidRect(s8dx+321,WSy-44,293,1,RGB(210,210,210));
		pDC->BitBlt(s8dx+t[0],WSy-40,25,9,&MemDC,41,89,SRCAND);//Shi+
			pDC->BitBlt(s8dx+t[0]+25,WSy-40,18,9,&MemDC,0,89,SRCAND);//F11
		pDC->BitBlt(s8dx+t[1]-25,WSy-40,25,9,&MemDC,41,89,SRCAND);//Shi+
			pDC->BitBlt(s8dx+t[1],WSy-40,18,9,&MemDC,21,89,SRCAND);//F12
		pDC->BitBlt(s8dx+t[2]+70,WSy-40,18,9,&MemDC,0,89,SRCAND);//F11
		pDC->BitBlt(s8dx+t[3]+70,WSy-40,18,9,&MemDC,21,89,SRCAND);//F12
	}
	if(f&WAVoMP3){//wav or mp3の描画
		pDC->FillSolidRect(X0+394,F12Y-4,28,9,RGBsysbtn);
		if(strstr(ptxt[ISMP3],"wav"))pDC->BitBlt(X0+394,F12Y-6,29,12,&MemDC,99,88,SRCAND);
		else pDC->BitBlt(X0+394,F12Y-6,29,12,&MemDC,69,88,SRCAND);		
	}
	if(f&KOIMARU||f&USUMARU){		
//#define VX1 136//on maru
//#define VX2 152//off maru
#define VX3 12//bar
		if(pos<0)pos=0;
		else if(pos>66)pos=66;
		pDC->FillSolidRect(VX0+11,VY0-2,82,19,RGBsysbtn);//(234,232,216));
		pDC->BitBlt(VX0+10,VY0+3-4,84,17,&MemDC,0,11,SRCAND);
		pDC->FillSolidRect(VX0+VX3+pos,VY0,13,17,RGBsysbtn);//(234,232,216));
		if(f&KOIMARU)pDC->BitBlt(VX0+VX3+pos-1,VY0-1,13+2,17,&MemDC,94-1,30,SRCCOPY);//濃く
		else pDC->BitBlt(VX0+VX3+pos-1,VY0-1,13+2,17,&MemDC,110-1,30,SRCCOPY);//薄く
		if(!(f&WAVoMP3)){//OnDrawでは表示だけ。
			sscanf(ptxt[VOLUM],"%d",&volume);
			if((pos*100/66!=volume)&&chan){
				BASS_ChannelSetAttribute(chan, BASS_ATTRIB_VOL,float(pos*100/66)/100.0f);
			}
			sprintf(ptxt[VOLUM],"%d",pos*100/66);
		}
	}
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}
void Hisigata(CDC *pDC,int x,int y)
{
	CBrush BR, *oldB; // oldB は、使う必要はありません。(選択前の、古いブラシのポインタを保存します。)
	BR.CreateSolidBrush(RGBhisi);// RGB(0,255,255) ); // BR を水色のブラシとする
	oldB = pDC->SelectObject(&BR); // ブラシ BR を選択します。(以後の塗りつぶしには BR が使用されます。)
	POINT po[5];
	po[0].x=x-5;po[0].y=y+6;
	po[1].x=x;po[1].y=y+1;
	po[2].x=x+5;po[2].y=y+6;
	po[3].x=x;po[3].y=y+11;
	pDC->SetPolyFillMode(WINDING );
	pDC->Polygon(po,4);
	pDC->SelectObject(oldB); // ブラシを元に戻します。
}

void Waku(CDC *pDC,int x,int y,int dx,int dy)
{
	pDC->FillSolidRect(x,y,dx,1,RGB(0,0,0));
	pDC->FillSolidRect(x,y,1,dy,RGB(0,0,0));
	pDC->FillSolidRect(x+dx,y,1,dy,RGB(0,0,0));
	pDC->FillSolidRect(x,y+dy,dx+1,1,RGB(0,0,0));
}

void getNewfn(char *path,char *type)
{//path:元のパス fn:Wmaを保存するフォルダ
	int i;
	char temp1[250],temp2[250],temp3[250];
	strcpy(temp1,getEN(path));
	strcpy(strstr(temp1,"."),"");

	for(i=1;i<100;i++){
		sprintf(temp2,"%s\\%s_%02d.wav",s8sfolder,temp1,i);
		sprintf(temp3,"%s\\%s_%02d.mp3",s8sfolder,temp1,i);
		if(isfile1(temp2)||isfile1(temp3))continue;
		break;
	}//_99もあるなら上書き
	if(strstr(type,"wav"))strcpy(recordfn,temp2);
	else strcpy(recordfn,temp3);
}

char *getlast_(char *s)
{
	char *p,*pp;
	if(strlen(s)==0)return s;
	p=s;
	while(pp=strkan(p,"_")){
		pp++;
		p=pp;
	}
	return --p;
}

void  CS8tuneView::Wave2mp3(char *wav)
{
	char oldname[301],oldart[301];
	HSTREAM tchan;
	int tlen=0;
	m_songlist.GetItemText(songnum,s8name,oldname,300);
	strcat(oldname,getlast_(wav));
	m_songlist.GetItemText(songnum,s8arti,oldart,300);
	if(tchan=Bass_StreamCreate(wav)){
		tlen = (int)(BASS_ChannelBytes2Seconds(tchan, BASS_ChannelGetLength(tchan, BASS_POS_BYTE))*10.0f);
		BASS_StreamFree(tchan);tchan=NULL;
	}
	SetCurrentDirectory(curdir);
	AddSongFile(wav,oldname,oldart,tlen);
	ABmode=1;
	if(songnum>=0)songnum++;
	SetSongCnt();
	SetSongsSelected(0,1);
	m_songlist.EnsureVisible(0, FALSE);
}
void MoveChanPos(int dpos)
{//再生位置を動かす
//	int len=(int)(10.0*ChanL);//BASS_ChannelBytes2Seconds(chan, BASS_ChannelGetLength(chan, BASS_POS_BYTE)));
	int pos=(int)(10.0*BASS_ChannelBytes2Seconds(chan, BASS_ChannelGetPosition(chan,NULL)));
	int posa=int(10.0*ChanA);
	int posb=int(10.0*ChanB);//0=pos*10 1:a 2:b
	pos=pos+dpos;
	if(pos<0)pos=0;
	if(pos<posa||pos>posb)pos=pos-dpos;
	playpos=0;
	BASS_ChannelSetPosition(chan, (QWORD)BASS_ChannelSeconds2Bytes(chan,float(pos)/10.0f),NULL);
}
int SelectedSongsFNE(CListCtrl *slist,int *ssf,int *ssn,int *sse)
{
	int  i,sgn=0,songnum_sgn=-1,sc = slist->GetItemCount();
	if(sc==0)return 0;
	for(i=0;i<sc;i++){
		if(slist->GetItemState(i,LVIS_SELECTED)!=0){
			sgn++;
			if(sgn==1)*ssf=i;
			if(songnum==i)songnum_sgn=sgn;
			if(sgn==songnum_sgn+1)*ssn=i;
			*sse=i;
		}
	}
	if(sgn==1)return 1;
	if(songnum_sgn==-1)*ssn=*ssf;
	return 2;
}
void CS8tuneView::DispSongA2B(CDC* pDC)
{//再生バーなどを表示し、再生位置が終点かチェックして、モードごとに振り分ける。
//	char buf[50];
	int i,pos;
	if(chan){
		double posd=BASS_ChannelBytes2Seconds(chan, BASS_ChannelGetPosition(chan,NULL));
		pos=int(10.0*posd);
//終点に来たら始点に戻す
		if(ABmode==0){
			if(posd<playpos||posd+0.1>ChanL){
				BASS_ChannelSetPosition(chan, (QWORD)BASS_ChannelSeconds2Bytes(chan,0),NULL);
				playpos=0;
				if(RepeatMode==0){
					BASS_ChannelPause(chan);
					IsPlaying=0;
				}else if(RepeatMode==2||RepeatMode==3){
					int ssf,ssn,sse;
					playpos=0;
					if(SelectedSongsFNE(&m_songlist,&ssf,&ssn,&sse)>1){
						if(songnum>=sse){//m_songlist.GetItemCount()-1){
							if(RepeatMode==2){
								BASS_ChannelPause(chan);
								IsPlaying=0;
							}else{
								StartSong(songnum=ssf);
							}
						}else{
							StartSong(songnum=ssn);
						}
					}else{
						if(songnum==m_songlist.GetItemCount()-1){
							if(RepeatMode==2){
								BASS_ChannelPause(chan);
								IsPlaying=0;
							}else{
								StartSong(songnum=0);
							}
						}else{
							StartSong(++songnum);
						}
					}
				}
				SetItemImage(songnum,(IsPlaying ? 0:2));//SetItemImage(songnum,0);
				return;
			}else playpos=posd;
		}else if(ABmode==1){
			bool cf=false;
			if(posd+0.1>ChanB&&posd<ChanB+0.5)cf=true;
			else if(posd<playpos&&posd<0.2)cf=true;
			if(cf){
				BASS_ChannelSetPosition(chan, (QWORD)BASS_ChannelSeconds2Bytes(chan,ChanA),NULL);
				if(RepeatMode==0){
					BASS_ChannelPause(chan);
					IsPlaying=0;
				}else if(RepeatMode==2||RepeatMode==3){
					int ssf,ssn,sse;
					playpos=0;
					if(SelectedSongsFNE(&m_songlist,&ssf,&ssn,&sse)>1){
						if(songnum>=sse){//
							if(RepeatMode==2){
								BASS_ChannelPause(chan);
								IsPlaying=0;
							}else{
								StartSong(songnum=ssf);
							}
						}else{
							StartSong(songnum=ssn);
						}
					}else{
						if(songnum==m_songlist.GetItemCount()-1){//最後の曲
							if(RepeatMode==2){
								BASS_ChannelPause(chan);
								IsPlaying=0;
							}else{
								StartSong(songnum=0);
							}
						}else{
							StartSong(++songnum);
						}
					}
				}
				SetItemImage(songnum,(IsPlaying ? 0:2));//SetItemImage(songnum,0);
				playpos=0;
				return;
			}else playpos=posd;
		}else if(ABmode==2){//最後なら停止
			if(posd+0.5>ChanB||posd+0.5>ChanL||(posd<ChanA&&posd>1.0)){
				StopRecord();//0.4-0.5secほど調整すると具合良いようだ
				return;
			}else playpos=posd;
		}
	}
//ダミーのCDCを作る
	CDC dcDummy;
	dcDummy.CreateCompatibleDC(pDC);
	CBitmap bmpDummy;
	bmpDummy.CreateCompatibleBitmap(pDC, 3000,2000);//rc.Width(), rc.Height());
	dcDummy.SelectObject(&bmpDummy);
	dcDummy.FillSolidRect(X0-10,Y0-20,WI+20,HE+40,RGBsysbtn);
// --------------------------------
// ここでdcDummyに描画
// --------------------------------
	dcDummy.FillSolidRect(X0,Y0,WI,HE,RGBwaku);//枠内塗りつぶし
	if(!chan){//歌が一回も再生されていなければ再生スライダーを表示して戻る
		Waku(&dcDummy,X0,Y0,WI,HE);//枠を縁取り
		Hisigata(&dcDummy,X0,Y0);
		// すべて終わったところでダミーからBitBlt
		pDC->BitBlt(X0-10,Y0-2,WI+20,HE+4,&dcDummy,X0-10,Y0-2,SRCCOPY);
			
		// メモリの解放、ダブっているが
		dcDummy.DeleteDC();
		bmpDummy.DeleteObject();
		return;
	}
/////////////////////////////////

//範囲(a-b)
	dcDummy.FillSolidRect(WI*posa/songlen+X0+1,Y0+1,WI*(posb-posa)/songlen,HE-1,RGBa2b);//RGB(190,190,190));
//再生済み範囲(a-
	if(ABmode==0){
		if(BARtype)dcDummy.FillSolidRect(X0+1,Y0+1,WI*pos/songlen,HE-1,RGBsumi);
		else for(i=X0+2;i<WI*pos/songlen+X0-1;i+=2)
			dcDummy.FillSolidRect(i,Y0+2,1,HE-3,RGBsumi);

	}else{
		if(BARtype&&pos>posa)dcDummy.FillSolidRect(WI*posa/songlen+X0,Y0+1,WI*(pos-posa)/songlen,HE-1,RGBsumi);
		else for(i=WI*posa/songlen+X0;i<WI*pos/songlen+X0-1&&i<WI*posb/songlen+X0;i+=2)
			dcDummy.FillSolidRect(i,Y0+2,1,HE-3,RGBsumi);//(100,100,100));
	}
//枠
	Waku(&dcDummy,X0,Y0,WI,HE);
	if(BARtype||(ABmode==1||ABmode==2||pos<posa)){//範囲再生のときは範囲枠の左右縦線を書く
//		dcDummy.FillSolidRect(WI*posa/songlen+X0,Y0+1,1,HE-1,RGB(0,0,0));//
		dcDummy.FillSolidRect(WI*posa/songlen+X0+0,Y0+2,1,HE-3,RGB(0,0,0));//
		dcDummy.FillSolidRect(WI*posa/songlen+X0+1,Y0+3,1,HE-5,RGB(0,0,0));//
		dcDummy.FillSolidRect(WI*posa/songlen+X0+2,Y0+4,1,HE-7,RGB(0,0,0));//
		dcDummy.FillSolidRect(WI*posa/songlen+X0+3,Y0+5,1,HE-9,RGB(0,0,0));//
		dcDummy.FillSolidRect(WI*posa/songlen+X0+4,Y0+6,1,HE-11,RGB(0,0,0));//
	}
	if(BARtype||(ABmode==1||ABmode==2||pos<posb)){//
//		dcDummy.FillSolidRect(WI*posb/songlen+X0,Y0+1,1,HE,RGB(0,0,0));
		dcDummy.FillSolidRect(WI*posb/songlen+X0-0,Y0+2,1,HE-3,RGB(0,0,0));
		dcDummy.FillSolidRect(WI*posb/songlen+X0-1,Y0+3,1,HE-5,RGB(0,0,0));
		dcDummy.FillSolidRect(WI*posb/songlen+X0-2,Y0+4,1,HE-7,RGB(0,0,0));
		dcDummy.FillSolidRect(WI*posb/songlen+X0-3,Y0+5,1,HE-9,RGB(0,0,0));
		dcDummy.FillSolidRect(WI*posb/songlen+X0-4,Y0+6,1,HE-11,RGB(0,0,0));
	}
//枠の左外、右外をgrayで塗る。(菱形が残らないように)
	dcDummy.FillSolidRect(X0+WI+1,Y0,10,HE,RGBsysbtn);//右外
	dcDummy.FillSolidRect(X0-10,Y0,10,HE,RGBsysbtn);//左外
//菱形
	Hisigata(&dcDummy,WI*pos/songlen+X0,Y0);
//録音ボタンの上部の録音レベル
	int recx=X0+393,recy=F12Y-6,recdx=30,recdy=11,vol;
	static bool recbarerasef=true;
	if(ABmode==2){
		recbarerasef=true;
		vol=abs(LOWORD(BASS_ChannelGetLevel(chan)));
		vol=int(log(vol)*recdx/log(32768));
		if(vol>14)vol=(vol-14)*recdx/(recdx-14);
		else vol=0;
		dcDummy.FillSolidRect(recx,recy,recdx,recdy,RGB(255,255,255));
		if(vol>35)dcDummy.FillSolidRect(recx,recy,vol,recdy,RGB(255,0,0));
		else dcDummy.FillSolidRect(recx,recy,vol,recdy,RGB(0,255,0));
		Waku(&dcDummy,recx,recy,recdx-1,recdy-1);
		pDC->BitBlt(recx,recy,recdx,recdy,&dcDummy,recx,recy,SRCCOPY);//録音ボタンの上部の録音レベル

	}else if(recbarerasef==true){
		recbarerasef=false;
		dcDummy.FillSolidRect(recx,recy,recdx,recdy,RGBsysbtn);//塗りつぶし
		DispIroiro(&dcDummy,&m_bitmap_volume,0,WAVoMP3);
		pDC->BitBlt(recx,recy,recdx,recdy,&dcDummy,recx,recy,SRCCOPY);//録音ボタンの上部の録音レベル
	}
//	{
//現在の再生位置
//	sprintf(buf,"%02d:%02d",pos/600,(pos/10)%60);
//	m_songstr=buf;
		CDC MemDC;
		CBitmap *pOldBmp;
		MemDC.CreateCompatibleDC(pDC);
		pOldBmp=MemDC.SelectObject(&m_bitmap_volume);
		int y=12,x1=0,y1=32,xd=8,yd=11,d=8;
		dcDummy.FillSolidRect(ltimex,ltimey,100,11,RGBsysbtn);
		dcDummy.BitBlt(ltimex+0*d,ltimey,xd,yd,&MemDC,x1+d*((pos/600)/10),y1,SRCAND);
		dcDummy.BitBlt(ltimex+1*d,ltimey,xd,yd,&MemDC,x1+d*((pos/600)%10),y1,SRCAND);
		dcDummy.BitBlt(ltimex+2*d,ltimey,xd-4,yd,&MemDC,x1+d*10,y1,SRCAND);
		dcDummy.BitBlt(ltimex+2*d+5,ltimey,xd,yd,&MemDC,x1+d*(((pos/10)%60)/10),y1,SRCAND);
		dcDummy.BitBlt(ltimex+3*d+5,ltimey,xd,yd,&MemDC,x1+d*(((pos/10)%60)%10),y1,SRCAND);
//残りの再生時間
//	sprintf(buf,"-%02d:%02d",(songlen-pos)/600,(songlen-pos)/10%60);
//	m_songstr2=buf;
		dcDummy.FillSolidRect(rtimex,rtimey,100,11,RGBsysbtn);
		dcDummy.BitBlt(rtimex+0*d-6,rtimey,xd-4,yd,&MemDC,x1+d*11,y1,SRCAND);
		dcDummy.BitBlt(rtimex+0*d,rtimey,xd,yd,&MemDC,x1+d*(((songlen-pos)/600)/10),y1,SRCAND);
		dcDummy.BitBlt(rtimex+1*d,rtimey,xd,yd,&MemDC,x1+d*(((songlen-pos)/600)%10),y1,SRCAND);
		dcDummy.BitBlt(rtimex+2*d,rtimey,xd-4,yd,&MemDC,x1+d*10,y1,SRCAND);
		dcDummy.BitBlt(rtimex+2*d+5,rtimey,xd,yd,&MemDC,x1+d*((((songlen-pos)/10)%60)/10),y1,SRCAND);
		dcDummy.BitBlt(rtimex+3*d+5,rtimey,xd,yd,&MemDC,x1+d*((((songlen-pos)/10)%60)%10),y1,SRCAND);
		MemDC.SelectObject(pOldBmp);
		DeleteDC(MemDC);
//	}
	// すべて終わったところでダミーからBitBlt
	pDC->BitBlt(X0-10,Y0-2,WI+20,HE+4,&dcDummy,X0-10,Y0-2,SRCCOPY);//bar
	pDC->BitBlt(ltimex,ltimey,100,11,&dcDummy,ltimex,ltimey,SRCCOPY);//現在の再生位置
	pDC->BitBlt(rtimex,rtimey,100,11,&dcDummy,rtimex,rtimey,SRCCOPY);//残りの再生時間

	// メモリの解放
	dcDummy.DeleteDC();
	bmpDummy.DeleteObject();
	
//	sprintf(buf,"posa=%d, posb=%d, button=%d    ",posa,posb,posbutton);
//	pDC->TextOut(10,20,buf);
	UpdateData(false);
}
void CS8tuneView::OnSeta() 
{//1-591
	char a2b[31];
	if(!chan)return;
	int pos=(int)(10.0*BASS_ChannelBytes2Seconds(chan, BASS_ChannelGetPosition(chan,NULL)));
	OnTocusong();
	if(pos>posb)posb=songlen;
	posa=pos;
	ChanA=(double)posa/10.0;
	ChanB=(double)posb/10.0;
	seta2bstr(a2b,posa,posb);
	m_songlist.SetItemText(songnum,s8a2b,a2b);
}

void CS8tuneView::Setab() 
{//1-591
	char a2b[31];
	if(!chan)return;
	OnTocusong();
	ChanA=(double)posa/10.0;
	ChanB=(double)posb/10.0;
	seta2bstr(a2b,posa,posb);
	m_songlist.SetItemText(songnum,s8a2b,a2b);
}

void CS8tuneView::OnSetb() 
{
	char a2b[31];
	if(!chan)return;
	int pos=int(10.0*BASS_ChannelBytes2Seconds(chan, BASS_ChannelGetPosition(chan,NULL)));
	OnTocusong();
	if(pos<posa)posa=0;
	posb=pos;
	ChanA=(double)posa/10.0;
	ChanB=(double)posb/10.0;
	seta2bstr(a2b,posa,posb);
	m_songlist.SetItemText(songnum,s8a2b,a2b);
	if(ABmode==1){
		playpos=0;
		BASS_ChannelSetPosition(chan, (QWORD)BASS_ChannelSeconds2Bytes(chan,ChanA),NULL);
	}
}

int FindFocused(CListCtrl *m_songlist)//これはリスト中に一個しかない。この関数はこれでよし、解決。
{//LVIS_FOCUSED
	int i,c=m_songlist->GetItemCount();
	for(i=0;i<c;i++){
		if(m_songlist->GetItemState(i, LVIS_FOCUSED) != 0)break;
	}
	if(i<c)return i;
	else return -1;
}

void CS8tuneView::OnStart()//play button
{
	m_songlist.SetFocus();
	if(ABmode==2)return;//0:全 1:範囲　2:録音
	if(!chan){
		StartSong(songnum);
		return;
	}
	playpos=0;
	if(ABmode==0){
		if(IsPlaying==false)IsPlaying=true;
		else IsPlaying=false;
	}else{
		ABmode=0;
		IsPlaying=true;
	}
	if(IsPlaying==false)BASS_ChannelPause(chan);
	else {
		kasihyouji();
		sleeptimelag();
		BASS_ChannelPlay(chan,FALSE);
	}
	SetItemImage(songnum,(IsPlaying ? 0:2));//
}
void CS8tuneView::OnStart2() 
{
	m_songlist.SetFocus();
	if(ABmode==2)return;
	if(!chan){
		StartSong(songnum);
		return;
	}
	playpos=0;
	double pos=BASS_ChannelBytes2Seconds(chan, BASS_ChannelGetPosition(chan,NULL));
	if(pos<ChanA||pos>ChanB){
		BASS_ChannelSetPosition(chan, (QWORD)BASS_ChannelSeconds2Bytes(chan,ChanA),NULL);
	}
	if(ABmode==1){
		if(IsPlaying==false)IsPlaying=true;
		else IsPlaying=false;
	}else{
		ABmode=1;
		IsPlaying=true;
	}
	if(IsPlaying==false)BASS_ChannelPause(chan);
	else {
		kasihyouji();
		sleeptimelag();
		BASS_ChannelPlay(chan,FALSE);
	}
	SetItemImage(songnum,(IsPlaying ? 0:2));//
}
void CS8tuneView::OnRename() 
{
	static bool tagf=false;
	CRename dlg;
	char buf[301],buf2[301],fn[301];
	int si=FindFocused(&m_songlist);
	if(si<0)return;
	m_songlist.GetItemText(si,s8name,buf,300);
	m_songlist.GetItemText(si,s8arti,buf2,300);
	m_songlist.GetItemText(si,s8path,fn,300);
	dlg.m_changetag=tagf;

#ifdef English
	strcpy(dlg.rnstr,"change song name and artist name");
	dlg.m_changetagtxt="change the tag data of the song.\nplaying song can't be.";
#else
	strcpy(dlg.rnstr,"曲名、アーティスト名の変更");
	dlg.m_changetagtxt="曲のタグ情報も書き換えます。\n演奏中の曲のタグデータは変更できません。";
#endif
	while(1){
		dlg.m_rename=buf;
		dlg.m_rename2=buf2;

		if(dlg.DoModal()==IDOK){
			strcpy(buf,dlg.m_rename);
			strcpy(buf2,dlg.m_rename2);
			if(strlen(buf)==0)continue;
			m_songlist.SetItemText(si,s8name,buf);
			m_songlist.SetItemText(si,s8arti,buf2);
			if(dlg.m_changetag)setmp3infp(fn,buf,buf2);
			break;
		}else break;
	}
	if(dlg.m_changetag)tagf=true;
	else tagf=false;
}

BOOL CS8tuneView::PreTranslateMessage(MSG* pMsg) 
{
	CPoint po;
	int pos,temp,volume;
	switch(pMsg->message){
		case WM_RBUTTONDOWN:
			GetCursorPos(&po);
			ScreenToClient(&po);
			temp=FindFocused(&m_songlist);
			if((pos=checkpos(po))==3&&chan){//speed slider
				if(songnum==temp)BASS_ChannelSetAttribute(chan,BASS_ATTRIB_TEMPO,0.0);
				SetStr(s8tempo,100,temp);
				m_bartempo.SetScrollPos(100);
			}else if(pos==5&&chan){//key slider
				if(songnum==temp)BASS_ChannelSetAttribute(chan, BASS_ATTRIB_TEMPO_PITCH,0.0);
				SetStr(s8key,0,temp);
				m_barkey.SetScrollPos(0);
			}else break;
			UpdateData(false);
			break;
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
			if(ChangeCursor){
				CRect rect;
				POINT ptCursor;
				ChangeCursor=false;
				AfxGetMainWnd()->PostMessage(WM_SETCURSOR);
				GetCursorPos(&ptCursor);
				m_songlist.ScreenToClient(&ptCursor);
				m_songlist.GetItemRect(0,&rect,LVIR_BOUNDS);
				int n=ptCursor.y/(rect.bottom-rect.top);
				if(n>0)DragDrop(n+m_songlist.GetTopIndex()-1);
				break;
			}
		case WM_MOUSEMOVE: 
			m_ToolTip.RelayEvent(pMsg);
			break;
		case WM_KEYUP:
			if(pMsg->wParam==VK_SHIFT){
				Timelag=0;
			}
			break;
		case WM_KEYDOWN:
			if(ABmode==2&&!(pMsg->wParam==VK_F4||pMsg->wParam==VK_F5))break;
			//F4,F5は録音中でも働く
			else if(FocusListKen==0 && pMsg->wParam==VK_RIGHT){
				MoveChanPos(10);
			}else if(FocusListKen==0 && pMsg->wParam==VK_LEFT){
				MoveChanPos(-10);
			}else if(FocusListKen==0 && pMsg->wParam==VK_DELETE){
				OnTocusong();
			}else if(FocusListKen==0 && pMsg->wParam==VK_BACK){
				if(chan){
					m_songlist.SetFocus();
					int	pos=(int)(10.0*BASS_ChannelBytes2Seconds(chan, BASS_ChannelGetPosition(chan,NULL)));
					playpos=0;
					if(ABmode==0)BASS_ChannelSetPosition(chan, (QWORD)BASS_ChannelSeconds2Bytes(chan,0),NULL);
					else BASS_ChannelSetPosition(chan, (QWORD)BASS_ChannelSeconds2Bytes(chan,ChanA),NULL);
				}
			}else if(FocusListKen==1 && 
				(pMsg->wParam==VK_UP||
				pMsg->wParam==VK_DOWN||
				pMsg->wParam==VK_HOME||
				pMsg->wParam==VK_END||
				pMsg->wParam==VK_PRIOR||
				pMsg->wParam==VK_NEXT)){
				m_songlist.SetFocus();
			}else if(FocusListKen==0 && pMsg->wParam==VK_RETURN){
				if(ABmode==2)break;
				int sn=FindFocused(&m_songlist);
				if(sn==songnum&&chan){
					if(IsPlaying==true){
						IsPlaying=false;
						BASS_ChannelPause(chan);
					}else{
						IsPlaying=true;
						sleeptimelag();
						BASS_ChannelPlay(chan,FALSE);
						kasihyouji();
					}
				}else{
					IsPlaying=true;
					StartSong(songnum=sn);
				}
				SetItemImage(songnum,(IsPlaying ? 0:2));//
//				SetButtons();
			}else if(pMsg->wParam==VK_F1){
				OnRewind();
			}else if(pMsg->wParam==VK_F2){
				OnStart();
			}else if(pMsg->wParam==VK_F3){
				OnTonext();
			}else if(pMsg->wParam==VK_F4&&chan){
				sscanf(ptxt[VOLUM],"%d",&volume);
				pos=volume*66/100-1;
//				pos=(volume-1)*66/100;
				CDC *pDC=GetDC();
				DispIroiro(pDC,&m_bitmap_volume,pos,USUMARU);
				ReleaseDC(pDC);
			}else if(pMsg->wParam==VK_F5&&chan){
				sscanf(ptxt[VOLUM],"%d",&volume);
				pos=volume*66/100+2;
//				pos=(volume+2)*66/100;
				CDC *pDC=GetDC();
				DispIroiro(pDC,&m_bitmap_volume,pos,USUMARU);
				ReleaseDC(pDC);
			}else if(pMsg->wParam==VK_F6){
				OnRewind2();
			}else if(pMsg->wParam==VK_F7){
				OnStart2();
//				f7sub();
			}else if(pMsg->wParam==VK_F8){
				OnTonext2();
			}else if(pMsg->wParam==VK_F9){
				if(FocusListKen==0){
					m_kensakuctl.SetFocus();
				}else OnKensakutype();
			}else if(pMsg->wParam==VK_F11){
//				if(::GetKeyState(VK_CONTROL) & 0xF000){
//					OnHScroll(SB_LINELEFT,m_barcent.GetScrollPos(),&m_barcent);
//				}else if(::GetKeyState(VK_CONTROL) & 0xF000){
				if(::GetKeyState(VK_SHIFT) & 0xF000){
					OnHScroll(SB_LINELEFT,m_bartempo.GetScrollPos(),&m_bartempo);
				}else{
					for(int k=0;k<20;k++)OnHScroll(SB_LINELEFT,m_barkey.GetScrollPos(),&m_barkey);
				}
			}else if(pMsg->wParam==VK_F12){
				if(::GetKeyState(VK_SHIFT) & 0xF000){
					OnHScroll(SB_LINERIGHT,m_bartempo.GetScrollPos(),&m_bartempo);
				}else{
					for(int k=0;k<20;k++)OnHScroll(SB_LINERIGHT,m_barkey.GetScrollPos(),&m_barkey);
				}
			}else if(pMsg->wParam==VK_SHIFT){
				if(Timelag==0)Timelag=timeGetTime();
			}else break;
			return true;
	}
	return CFormView::PreTranslateMessage(pMsg);
}
int CS8tuneView::GetItemImagen(int itemn)
{
	LV_ITEM item;
	item.mask = LVIF_IMAGE;
	item.iSubItem =0;
	item.iItem = itemn;
	m_songlist.GetItem(&item);
	return item.iImage;
}
int CS8tuneView::GetSongnum(int sc)
{//スピーカー付きアイテムの位置を返す。無ければ-1
	int i;
	for(i=0;i<sc;i++){
		if(GetItemImagen(i)!=1)return i;
	}
	return -1;
}
void CS8tuneView::SetItemImage(int itemn,int imgn)
{
	LV_ITEM item;
	item.iItem = itemn;
	item.iImage= imgn;
	item.mask = LVIF_IMAGE;
	item.iSubItem =0;
	m_songlist.SetItem(&item);
}
int checkpos(CPoint pos)
{//		else pDC->BitBlt(X0+393,F12Y-6,29,12,&MemDC,69,88,SRCAND);		

	int x=pos.x,y=pos.y;
	if(y<F12Y+6&&y>F12Y-6){
		if(x>X0+393&&x<X0+393+29)return 6;
	}
	if(x>=X0-5&&x<=(X0+WI+5)){
		if(y>=Y0&&y<=(Y0+HE+10))return 1;
	}
	if(x>=(VX0+5)&&x<=(VX0+100)){
		if(y>(VY0-3)&&y<=(VY0+20))return 2;
	}
	if(y>SPEEDY1&&y<SPEEDY2){
		if(x>SPEEDX1&&x<SPEEDX2)return 3;
		if(x>KEYX1&&x<KEYX2)return 5;
	}
	/*
		if(f&REPEATD){
		pDC->FillSolidRect(X0-30,Y0+31,30,20,RGBsysbtn);
		if(strstr(ptxt[REPEA],"one_r"))pDC->BitBlt(X0-30,Y0+31,50,19,&MemDC,139,20,SRCAND);
		if(strstr(ptxt[REPEA],"all_r"))pDC->BitBlt(X0-30,Y0+31,50,19,&MemDC,139,0,SRCAND);
		if(strstr(ptxt[REPEA],"one_1"))pDC->BitBlt(X0-30,Y0+31,50,19,&MemDC,139,40,SRCAND);
	}
*/
	if(y>Y0+30&&y<Y0+50&&x>X0-30&&x<X0)return 7;
	return 0;
}
int IsSong(char *s)
{
	char *p;
	if((p=strstr(s,".mp3"))||(p=strstr(s,".MP3"))){if(*(p+4)==0)return 1;}
	if((p=strstr(s,".wma"))||(p=strstr(s,".WMA"))){if(*(p+4)==0)return 2;}
	if((p=strstr(s,".wav"))||(p=strstr(s,".WAV"))){if(*(p+4)==0)return 3;}
	if((p=strstr(s,".AAC"))||(p=strstr(s,".aac"))){if(*(p+4)==0)return 4;}
	if((p=strstr(s,".m4a"))||(p=strstr(s,".M4A"))){if(*(p+4)==0)return 5;}
	return 0;
}
int x2pos(int x){
	return x*songlen/WI;
}
void CS8tuneView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int ckpos;
	if((ckpos=checkpos(point))==1&&chan!=0){//saisei bar
		SliderF=1;
		int x = point.x -X0;
		if(x<0)x=0;
		if(x>WI+5)x=WI;
		//WI*posa/songlen=x
		//int pos=x*songlen/WI;
		int zure=songlen/100;
		posbutton=x2pos(x);
		if (x2pos(x)>posa - zure && x2pos(x)<posa + zure) {
			sankakuzure = posa - x2pos(x);
			SliderMark = 1;
		}
		else if (x2pos(x)>posb - zure && x2pos(x)<posb + zure) {
			sankakuzure = posb - x2pos(x);
			SliderMark = 3;
		}
		else {
			SliderMark = 2;
			int len=(int)(10.0*BASS_ChannelBytes2Seconds(chan, BASS_ChannelGetLength(chan,BASS_POS_BYTE)));
			BASS_ChannelSetPosition(chan, (QWORD)BASS_ChannelSeconds2Bytes(chan,float(len*(point.x-X0)/WI)/10.0f),NULL);
			playpos=0;
		}
	}else if(ckpos==2){
		CDC *pDC=GetDC();
		DispIroiro(pDC,&m_bitmap_volume,point.x-VX0-17,KOIMARU);
		ReleaseDC(pDC);	
		VolumeF=1;
	}else if(ckpos==6&&ABmode!=2){//mp3 wave
		if(strstr(ptxt[ISMP3],"wav")){
			if(IsLameEncoder()){
				strcpy(ptxt[ISMP3],"mp3");
			}else {
				MessageBox(LAMEERRMESS);
			}
		}else {
			strcpy(ptxt[ISMP3],"wav");
		}
		CDC *pDC=GetDC();
		DispIroiro(pDC,&m_bitmap_volume,0,WAVoMP3);
		ReleaseDC(pDC);
	}else if(ckpos==7){
		CDC *pDC=GetDC();
		if(RepeatMode==1){RepeatMode=2;strcpy(ptxt[REPEA],"all_1");}
		else if(RepeatMode==2){RepeatMode=3;strcpy(ptxt[REPEA],"all_r");}
		else if(RepeatMode==3){RepeatMode=0;strcpy(ptxt[REPEA],"one_1");}
		else if(RepeatMode==0){RepeatMode=1;strcpy(ptxt[REPEA],"one_r");}
		DispIroiro(pDC,&m_bitmap_volume,0,REPEATD);
		ReleaseDC(pDC);	
	}
	CFormView::OnLButtonDown(nFlags, point);
}
/*
}else if ((CapNYSmode == PlayMode || CapNYSmode == ListMode) && pMsg->message == WM_LBUTTONDOWN) {
		CPoint pt;
		pt = pMsg->pt;
		ScreenToClient(&pt);
		ldownf = 1;
	
		PicPosflag = CheckPicPos(CapNYSmode, pt.x, pt.y);
		return false;

	}
	else if (pMsg->message == WM_LBUTTONUP) {
		HCURSOR hCursor = LoadCursor(NULL, IDC_ARROW);     // 砂時計カーソル
		SetCursor(hCursor);//DC_ARROW
		CPoint pt=pMsg->pt;
		ScreenToClient(&pt);
	
		ldownf = 0;
//		touchf = false;
		int x = CheckPicPos(CapNYSmode, pt.x, pt.y);

		if (x == 7 && CapNYSmode == PlayMode && PicPosflag == 6) {//videoをドラッグしListref上でUpしたとき
			OnStnClickedArrowore();
		}

		sliderf = false;
		return false;
	}
	else if (pMsg->message == WM_MOUSEMOVE) {
		if (!touchf) {
			m_tooltip.RelayEvent(pMsg);
		}
		CPoint pt = pMsg->pt;
		ScreenToClient(&pt);

		if (PicPosflag == 6 && CapNYSmode == PlayMode) {
			if (ldownf == 1) {
				HCURSOR hCursor = LoadCursor(NULL, IDC_HAND);     // 砂時計カーソル
				SetCursor(hCursor);//DC_ARROW
			}
			else {
				PicPosflag = -1;
			}
		}
	}
	*/
/*

void CCapNYS2Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
//	m_tooltip.RelayEvent(pMsg);
	if (CapNYSmode == PlayMode &&(changingDownf || changingIDf))return;

	if (CapNYSmode == CaptMode && m_down_x) {
		if (point.x - m_move_x > 15) {
			m_x_off -= 5;
			if (m_x_off < 1)m_x_off = 1;
			m_move_x = point.x;
			MCM4304_x(m_dev, m_x_off, m_y_off);
		}
		else if (point.x - m_move_x < -15) {
			m_x_off += 5;
			if (m_x_off > 115)m_x_off = 115;
			m_move_x = point.x;
			MCM4304_x(m_dev, m_x_off, m_y_off);
		}
	}
	if (CapNYSmode == PlayMode) {
		int x = checkslider(point.x, point.y);
		if (sliderf) {
			if (x >= 0) {
				if (x*maxframenum / slidew >= maxframenum)SetFrame = maxframenum - 1;//かたまりそう？
				else SetFrame = x*maxframenum / slidew;
			}
			else {
				sliderf = 0;
			}
		}
		if (sliderf == 1) {
			if (x + sankakuzure<trimposb - 20)trimposa = x + sankakuzure;
			else trimposa = trimposb - 20;
			if (trimposa<0)trimposa = 0;
		}
		else if (sliderf == 3) {
			if (x + sankakuzure>trimposa + 20)trimposb = x + sankakuzure;
			else trimposb = trimposa + 20;
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
int CheckPicPos(int mode, int x, int y)
{
	int i, r = -1;
	if (mode == 0 || mode == 1)return -1;
	for (i = 0; i<9; i++) {
		if (x >= PicPos[i][0] && y >= PicPos[i][1] && x<PicPos[i][0] + PicPos[i][2] && y<PicPos[i][1] + PicPos[i][3]) {
			r = i;
		}
	}
	if (mode == 2) {//slider上なら（GWINの下1/5も含めて)
		if (checkslider(x, y) >=  0)r = -1;
	}else if (mode == 3) {//listavi
		i = 9;
		if (x >= PicPos[i][0] && y >= PicPos[i][1] && x<PicPos[i][0] + PicPos[i][2] && y<PicPos[i][1] + PicPos[i][3]) {
			r = i;
		}
	}
	return r;
}
//0:capture 1:preview 2:play 3:disp
//0:del 1:setid 2:toref矢印 3:memo 4:changeid 5:curplay 6:video 7:listref 8:listcurrent 9:listavi 
//15:sensor 16:camnum 17:sen_onof 18:nextcom

int checkslider(int x, int y)
{
	if (y >= slidey - Gwinh/10 && y<slidey + slideh + 30) {
		if (x >= slidex - 15 && x <= slidex + 15 + slidew) {
			if (x<slidex)return 0;
			else if (x>slidex + slidew)return slidew;
			else return x - slidex;
		}
	}
	else if (x>Gwinx && x<Gwinx + Gwinw && y>Gwiny && y<Gwiny + Gwinh) {
		return -2;
	}
	return -1;
}
*/
/*
void CCapNYS2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (CapNYSmode == PlayMode) {//pretranslateでslider以外の処理は済んでいる
		if (changingIDf) {
			changingDownf = true;
			return;
		}
		else {
			changingDownf = false;
		}
		int x = checkslider(point.x, point.y);
		if (x >= 0) {
			if (!m_pPlayThread) {
				m_pPlayThread = AfxBeginThread(PlayThread, this);
				sliderf = 0;
			}
			if (x>trimposa - 14 && x<trimposa + 14) {
				sankakuzure = trimposa - x;
				sliderf = 1;
			}
			else if (x>trimposb - 14 && x<trimposb + 14) {
				sankakuzure = trimposb - x;
				sliderf = 3;
			}
			else {
				sliderf = 2;
			}
			SetFrame = x*maxframenum / slidew;
			moviepausef = true;
		}
	}
	else if (CapNYSmode == CaptMode) {
		m_down_x =m_move_x= point.x;
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


WI*posa/songlen//

*/
void CS8tuneView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(SliderF==1){
		SliderF=0;
	}else if(VolumeF==1){
		CDC *pDC=GetDC();
		DispIroiro(pDC,&m_bitmap_volume,point.x-VX0-17,USUMARU);
		ReleaseDC(pDC);
		VolumeF=0;
	}
	CFormView::OnLButtonUp(nFlags, point);
}
//x>=X0
void CS8tuneView::OnMouseMove(UINT nFlags, CPoint point) 
{
	ChangeCursor=false;
	if(SliderF==1){
		if(checkpos(point)==1&&chan){
			
			int x = point.x -X0;
			if(x<0)x=0;
			if(x>WI+5)x=WI;

			int zure=songlen/100;
			if(SliderMark==2){
				BASS_ChannelSetPosition(chan, (QWORD)BASS_ChannelSeconds2Bytes(chan,float(songlen*(point.x-X0)/WI)/10.0f),NULL);
				playpos=0;
			}else if(SliderMark==1){//left
				if(x2pos(x) + sankakuzure<posb - zure)posa=x2pos(x)+sankakuzure;
				else posa=posb - zure;
				Setab();
			}else{//right
				if(x2pos(x)+sankakuzure>posa+zure)posb=x2pos(x)+sankakuzure;
				else posb=posa+zure;
				Setab();
			}
		}else{
			SliderF=0;
		}
	}else if(VolumeF==1){
		CDC *pDC=GetDC();
		if(checkpos(point)==2){
			DispIroiro(pDC,&m_bitmap_volume,point.x-VX0-17,KOIMARU);
		}else{
			DispIroiro(pDC,&m_bitmap_volume,point.x-VX0-17,USUMARU);
			VolumeF=0;
		}
		ReleaseDC(pDC);
	}
	CFormView::OnMouseMove(nFlags, point);
}

#define setctrl(ct,x,y,dx,dy);{rect.left=x;rect.right=x+dx,rect.top=y;rect.bottom=y+dy;ct.MoveWindow(&rect,TRUE);}
void CS8tuneView::setctrls()
{
	int dx=5,ctrtopy=57,yp;
	RECT rect;
	rect.left=8;
	rect.right=WSx-8;
	rect.top=87;//+2
	rect.bottom=WSy-48;//-1

	m_songlist.MoveWindow(&rect,TRUE);

	setctrl(m_rewind,s8dx+12+dx,ctrtopy,29,23);
	setctrl(m_pause,s8dx+42+dx,ctrtopy,29,23);
	setctrl(m_start,s8dx+72+dx,ctrtopy,29,23);
	setctrl(m_tonext,s8dx+102+dx,ctrtopy,29,23);

	setctrl(m_rewind2,s8dx+227+dx,ctrtopy,29,23);
	setctrl(m_pause2,s8dx+257+dx,ctrtopy,29,23);
	setctrl(m_start2,s8dx+287+dx,ctrtopy,29,23);
	setctrl(m_tonext2,s8dx+317+dx,ctrtopy,29,23);	

	setctrl(m_seta,s8dx+347+dx,ctrtopy,29,23);
	setctrl(m_setb,s8dx+377+dx,ctrtopy,29,23);
	setctrl(m_hozon,s8dx+407+dx,ctrtopy,30,23);

	setctrl(m_kentypectrl,s8dx+440+dx,ctrtopy,43,23)
	setctrl(m_kensakuctl,s8dx+482+dx,ctrtopy,103,23);
	setctrl(m_kensaku,s8dx+586+dx,ctrtopy,23,23);

	ltimex=s8dx+19;
	ltimey=12;

	sscanf(ptxt[TITLEP],"%d",&yp);
	setctrl(m_s_songname,s8dx+62,yp,487,25);
	setctrl(m_tonow,s8dx+555,12,11,11);
	rtimex=s8dx+562+14;
	rtimey=12;
	setctrl(m_bartempo,s8dx+14,WSy-24,217+73,17);	
	setctrl(m_barkey,s8dx+321,WSy-24,293,17);
}

//static CFont pFont;
CFont pFont;
void CS8tuneView::SetFontSize()
{
	//コントロールのフォントサイズを90にする。
	//windows8 vaio　は85にしないとはみ出る？englishでは78
	LOGFONT logfont;  // LOGFONT 構造体
	// アイコンのフォントを取得
	SystemParametersInfo( SPI_GETICONTITLELOGFONT,
		sizeof(LOGFONT), &logfont, 0);
#ifdef VaioTouch8
#ifdef English
	pFont.CreatePointFont(78,logfont.lfFaceName);
#else
	pFont.CreatePointFont(85,logfont.lfFaceName);
#endif
#else
	pFont.CreatePointFont(90,logfont.lfFaceName);
#endif
//	m_s_statichanni.SetFont(&pFont);
	m_seta.SetFont(&pFont);
	m_setb.SetFont(&pFont);
	m_hozon.SetFont(&pFont);
//	m_kentypectrl.SetFont(&pFont);
	m_kensakuctl.SetFont(&pFont);
	m_kensaku.SetFont(&pFont);
//	m_s_songstr.SetFont(&pFont);
	m_s_songname.SetFont(&pFont);
//	m_s_songstr2.SetFont(&pFont);
//	m_bartempo.SetFont(&pFont);
//	m_barcent.SetFont(&pFont);
//	m_barkey.SetFont(&pFont);
//	m_s_tempostr.SetFont(&pFont);
//	m_s_pitchstr.SetFont(&pFont);
//	m_s_ratestr.SetFont(&pFont);
//	m_s_songnum.SetFont(&pFont);
	m_s_songname.SetFont(&pFont);
	m_songlist.SetFont(&pFont);
//	pFont.DeleteObject();
} 
void CS8tuneView::OnDraw(CDC* pDC) 
{
	static bool initf=true;
	int volume;
	if(initf==true){
		initf=false;
		AfxGetMainWnd()->SetWindowText(TITLEMESS);
	}
	sscanf(ptxt[VOLUM],"%d",&volume);
	DispTotal(pDC,&m_bitmap_volume);
	DispIroiro(pDC,&m_bitmap_volume,volume*66/100,USUMARU|F11_F12|WAVoMP3|REPEATD);
	int fsn=FindFocused(&m_songlist);
	if(fsn!=-1)SetKeyCent(fsn,1);
}
bool cmpstring(char *s1,char *s2)
{
	char b1[301],b2[301];
	if(strlen(s2)==0)return true;
	strcpy(b1,_strlwr( _strdup( s1 ) ));
	strcpy(b2,_strlwr( _strdup( s2 ) ));
	if(strstr(b1,b2))return true;
	return false;
}
void CS8tuneView::OnDeleteall() 
{
	if(MessageBox(ERASEMESS,MB_YESNO)==IDYES){
		oyasumiF=true;
		songnum=0;
		m_songname="shaku8Tunes";
		m_songlist.DeleteAllItems();
		SetSongCnt();
		UpdateData(false);
		BASS_ChannelSetPosition(chan, (QWORD)BASS_ChannelSeconds2Bytes(chan,0.0),NULL);
		BASS_StreamFree(chan);chan=NULL;
		IsPlaying=false;
//		SetButtons();
		oyasumiF=false;
	}
}
void CS8tuneView::SetSongsSelected(int sn,int n)
{//snからn個だけをハイライト表示
	int sc=m_songlist.GetItemCount(),i;
	for(i=0;i<sc;i++){
		if(i>=sn&&i<sn+n)m_songlist.SetItemState(i,LVIS_SELECTED | LVIS_FOCUSED,LVIS_SELECTED | LVIS_FOCUSED);
		else m_songlist.SetItemState(i,NULL,LVIS_SELECTED | LVIS_FOCUSED);
	}
}

void CS8tuneView::OnKensaku() 
{
	char hiken[301],*p,ken[100],ken1[100],ken2[100],buf[3000];
	int sc=m_songlist.GetItemCount(),cnt=0,imagen;
	LV_ITEM item;
	item.mask = LVIF_IMAGE;
	item.iSubItem =0;
	UpdateData(true);
	strcpy(ken,m_kensakustr);
	if(strlen(ken)<1)return;
	ken1[0]=0;
	ken2[0]=0;
	if(p=strkan(ken," ")){
		*p=0;
		strcpy(ken1,p+1);
	}else if(p=strkan(ken,"　")){
		*p=0;
		strcpy(ken1,p+2);
	}
	if(p=strkan(ken1," ")){
		*p=0;
		strcpy(ken2,p+1);
	}else if(p=strkan(ken1,"　")){
		*p=0;
		strcpy(ken2,p+2);
	}
	oyasumiF=true;
	for(int i=0;i<sc;i++){
		if(kensakutype==0)m_songlist.GetItemText(i,s8name,hiken,300);
		else if(kensakutype==1)m_songlist.GetItemText(i,s8arti,hiken,300);
		else m_songlist.GetItemText(i,s8path,hiken,300);

		if(cmpstring(hiken,ken2)&&cmpstring(hiken,ken1)&&cmpstring(hiken,ken)){
			cnt++;
			sets8strs(buf,i);
			if(i!=0){
				imagen=GetItemImagen(i);
				m_songlist.DeleteItem(i);
				SetItemImage(InsertItemBuf(buf,0),imagen);
			}
			m_songlist.SetItemState(0,LVIS_SELECTED | LVIS_FOCUSED,LVIS_SELECTED | LVIS_FOCUSED);
		}
	}
	findnum=cnt;
	if(cnt>0){
		for(i=cnt;i<sc;i++)m_songlist.SetItemState(i,NULL,LVIS_SELECTED | LVIS_FOCUSED);
		m_songlist.SetFocus();
		m_songlist.EnsureVisible(0, FALSE);
	}
	if((songnum=GetSongnum(sc))==-1)MessageBox("Kensaku Error");
	CDC *pDC=GetDC();
	DispIroiro(pDC,&m_bitmap_volume,0,FOUNDNUM);
	ReleaseDC(pDC);
	oyasumiF=false;
}
void CS8tuneView::OnChangeKensakustr() 
{
	UpdateData(true);
//	CDC *pDC=GetDC();
//	DispIroiro(pDC,&m_bitmap_volume,findnum=-1,FOUNDNUM);
//	ReleaseDC(pDC);
	UpdateData(false);
}

void CS8tuneView::OnReturn() 
{
	if(ABmode==2)return;
	OnKensaku();
}

bool isfile1(char *fn)
{
	struct stat st;
	if (stat(fn, &st) != 0)return false;
	return true;
}
char *getEN(char *s)
{
	char *p,*pp;
	if(strlen(s)==0)return s;
	p=s;
	while(pp=strkan(p,"\\")){
		pp++;
		p=pp;
	}
	return +p;
}

bool IsLameEncoder()
{
	char path[305];
	sprintf(path,"%s\\lame.exe",curdir);
	if(isfile1(path))return true;
	else return false;
}

void CS8tuneView::OnHozon() 
{
	char path[MAX_PATH],lamemp3[MAX_PATH];
	int sc=m_songlist.GetItemCount();
	if(!chan)return;
	if(sc<1)return;
	if(songnum<0)return;
	if(ABmode==2){
		StopRecord();
		m_songlist.SetFocus();
		return;
	}
	IsPlaying=true;
	OnTocusong();
	BASS_ChannelPause(chan);

	playpos=0;
	BASS_ChannelSetPosition(chan, (QWORD)BASS_ChannelSeconds2Bytes(chan,ChanA),NULL);
	ABmode=2;//範囲録音
	SetItemImage(songnum,(IsPlaying ? 0:2));
	SetButtons();
	m_songlist.GetItemText(songnum,s8path,path,300);
	if(strstr(ptxt[ISMP3],"wav")){
		getNewfn(path,"wav");//recordfnを得る。curdir\s8Songs\fn_01.wav　のような
		BASS_Encode_Start(chan,recordfn, BASS_ENCODE_PCM, NULL, 0);
	}else{
		getNewfn(path,"mp3");
		sprintf(lamemp3,"lame --alt-preset standard - \"s8Songs\\%s\"",getEN(recordfn));
		SetCurrentDirectory(curdir);
		BASS_Encode_Start(chan,lamemp3, 0, NULL, 0);
	}
	BASS_ChannelPlay(chan, FALSE); // start the channel playing & encoding  
}
void AddSong2File(CStdioFile *fw,char *fn,char *name,char *artist,int mlen)
{
	char buf[2*MAX_PATH+150];
	sprintf(buf,"%s<s8t>%s<s8t>%s<s8t>%d\n",fn,name,artist,mlen);
	fw->WriteString(buf);
}
char ThreadFolder[MAX_PATH];
char ThreadSong[MAX_PATH];
bool ThreadFlag;
int songcnt;
bool DirSong_1(CStdioFile *fw,char *lpszSDir)
{
	char name[301],artist[301];
	HSTREAM tchan;
	if(tchan=Bass_StreamCreate(lpszSDir)){
		int mlen = (int)(BASS_ChannelBytes2Seconds(tchan, BASS_ChannelGetLength(tchan, BASS_POS_BYTE))*10.0f);
		if(mlen<10)return false;//1秒以下は無視
//		GetNameArtist(tchan,lpszSDir,name,artist);
		GetNameArtist(lpszSDir,name,artist);
		BASS_StreamFree(tchan);tchan=NULL;
		AddSong2File(fw,lpszSDir,name,artist,mlen);
		sprintf(ThreadSong,"%04d %s",songcnt,lpszSDir);
		return true;
	}
	return false;
}
void SearchDirSongs(CStdioFile *fw,char *DirName)
{
	WIN32_FIND_DATA fd;  // 列挙情報取得用
	char Pattern[MAX_PATH];
	if (DirName[strlen(DirName)-1]!='\\') // 最後が"\" か？ 
		lstrcat(DirName,"\\"); // 検索するファイル名作成 
	lstrcpy(Pattern,DirName); // 探索パスを作成 
	lstrcat(Pattern,"*.*");
	
	HANDLE hFind;   // 検索用のハンドル 
	if(ThreadFlag==false)return;
	try{//////////////////////////////////////////////////////////////////////////////
	hFind = FindFirstFile(Pattern,&fd); // 最初のファイルを検索 
	if(hFind==INVALID_HANDLE_VALUE) 
		return;  // ファイルは１個も存在しない(実際は . ..があるので実行されないはず) 
	do{ 
		if(ThreadFlag==false)break;
		if(strcmp(fd.cFileName,".")!=0 && strcmp(fd.cFileName,"..")!=0){ // . ..は無視 
			if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){ // フォルダ属性か調べる 
				//現在のフォルダに見つかったフォルダを追加
				char SubFolder[MAX_PATH]; 
				lstrcpy(SubFolder,DirName); // 探索パスを作成 
				lstrcat(Pattern,"\\");
				sprintf(SubFolder,"%s\\%s",DirName,fd.cFileName);
				SearchDirSongs(fw,SubFolder);  // サブフォルダを検索する 
			}else{
				char fpath[MAX_PATH];
				sprintf(fpath,"%s\\%s",DirName,fd.cFileName);
				if(IsSong(fpath)){
					if(DirSong_1(fw,fpath))songcnt++;
				}
			}
		} 
	}while(FindNextFile(hFind,&fd)==TRUE);  // ファイルが無くなるまで続ける 
	}catch(...){}
	FindClose(hFind);  //ハンドルを閉じる 
} 

void CS8tuneView::OnAddfolder()
{
	char cdr[500],buf[1000];
	char folder[300];
	LPMALLOC pma;
	BROWSEINFO bif;
	LPITEMIDLIST iil;
	int sc;
	oyasumiF=true;
	strcpy(folder,"none");
	strcpy(buf,"wav wma mp3 mp4 aac");
	if (::SHGetMalloc(&pma)==NOERROR)//Shell の標準のアロケータを取得
	{
		GetCurrentDirectory(sizeof(cdr),cdr);
		memset(&bif,0x00,sizeof(bif));
		bif.hwndOwner=m_hWnd;//GetSafeHwnd();
		bif.pidlRoot=NULL;
		bif.pszDisplayName=cdr;
		bif.lpszTitle=buf;//"転送先フォルダ"
		bif.ulFlags=BIF_RETURNFSANCESTORS|BIF_RETURNONLYFSDIRS;
		bif.lpfn=NULL;
		bif.lParam=0;
		if((iil=SHBrowseForFolder(&bif)))
		{
			if(::SHGetPathFromIDList(iil,folder))
			{//bufに選択されたパスが入っています。
				TRACE("buf=%s\n",folder);
			}
			//iilを解放します。
			pma->Free(iil);
		}
		pma->Release();
	}
	int tm;
	strcpy(ThreadFolder,folder);
	if(strstr(folder,"none")&&strlen(folder)==4)return;
	AfxBeginThread(CopyDirSongThread,&tm);
	CAddThread dlg;
	if(dlg.DoModal()==IDOK){
		char *p1,*p2,*p3;//,fn[MAX_PATH];
		int mlen;
		CStdioFile fr;
		//sprintf(fn,"%s\\s8Tunes_temp.txt",curdir);
		fr.Open(temppath,CFile::modeRead|CFile::typeText);

		while(fr.ReadString(buf,995)){
			p1=strstr(buf,"<s8t>");
			*p1=0;
			p1=p1+5;
			p2=strstr(p1,"<s8t>");
			*p2=0;
			p2=p2+5;
			p3=strstr(p2,"<s8t>");
			*p3=0;
			p3=p3+5;
			sscanf(p3,"%d",&mlen);
			AddSongFile(buf,p1,p2,mlen);
		}
		fr.Abort();
	}
	sc=SetSongCnt();
	oyasumiF=false;
	if((songnum=GetSongnum(sc))==-1&&sc>0){//スピーカー付きアイテムがない。
		m_songlist.SetFocus();
		songnum=0;
		IsPlaying=false;
		StartSong(songnum,false);
		SetSongsSelected(songnum,1);
	}
	UpdateData(false);
}
UINT CopyDirSongThread( LPVOID dammy )
{
	CStdioFile fw;
//	char fn[MAX_PATH];
//	sprintf(fn,"%s\\s8Tunes_temp.txt",curdir);
	fw.Open(temppath,CFile::modeCreate|CFile::modeWrite|CFile::modeRead|CFile::typeText);
	songcnt=0;
	strcpy(ThreadSong,"");
	ThreadFlag=true;
	SearchDirSongs(&fw,ThreadFolder);	
	fw.Abort();
	sprintf(ThreadSong,"%04d%s",songcnt,TOUROKUMESS);
	ThreadFlag=false;	
	return 0;
};

void CS8tuneView::read_s8t()
{
	char buf[3001];
	CStdioFile ff;
	int songi=0;
	if(ff.Open(listpath,CFile::modeRead|CFile::typeText)){
		while(ff.ReadString(buf,3000)){
			if(!strstr(buf,"<s8t>"))continue;
			if(buf[strlen(buf)-1]=='\n')buf[strlen(buf)-1]=0;
			if(strlen(buf)>10)InsertItemBuf(buf,0);
		}
		ff.Abort();
	}
}
void CS8tuneView::write_s8t()
{
	CStdioFile ff;
	char buf[3001];
	int i,sc=m_songlist.GetItemCount();
	ff.Open(listpath,CFile::modeCreate|
				CFile::modeWrite|CFile::modeRead|CFile::typeText);
	for(i=sc-1;i>=0;i--){
		sets8strs(buf,i);
		strcat(buf,"\n");
		ff.WriteString(buf);
	}
	ff.Abort();
}

void CS8tuneView::readini()
{
	int i;
	char buf[500];
	CStdioFile ff;
	if(!ff.Open(inipath,CFile::modeRead|CFile::typeText))
	{
		ff.Open(inipath,CFile::modeCreate|
				CFile::modeWrite|CFile::modeRead|CFile::typeText);
		for(i=0;i<PARA;i++){
			sprintf(buf,"%s%s\n",ptext[i],ptextdef[i]);
			ff.WriteString(buf);
		}
		ff.Abort();
		for(i=0;i<PARA;i++){
			strcpy(ptxt[i],ptextdef[i]);
		}
	}
	else{
		bool txtf[PARA+1];
		for(i=0;i<PARA;i++)txtf[i]=false;
		while(ff.ReadString(buf,395)){
			for(i=0;i<PARA;i++){
				if(strstr(buf,ptext[i])){
					strcpy(ptxt[i],&buf[strlen(ptext[i])]);
					ptxt[i][strlen(ptxt[i])-1]=0;
					txtf[i]=true;
				}
			}
		}
		ff.Abort();

		for(i=0;i<PARA;i++){
			if(!txtf[i]){
				strcpy(ptxt[i],ptextdef[i]);
			}
		}
	}
}
void CS8tuneView::writeini()
{
	CStdioFile ff;
	char buf[301];
	int i;	
	ff.Open(inipath,CFile::modeCreate|
				CFile::modeWrite|CFile::modeRead|CFile::typeText);
	for(i=0;i<PARA;i++){//writeini
		sprintf(buf,"%s%s\n",ptext[i],ptxt[i]);
		ff.WriteString(buf);
	}
	ff.Abort();
	write_s8t();
}
void CS8tuneView::StopRecord()
{
	IsPlaying=false;
	playpos=0;
	BASS_Encode_Stop(chan);
	BASS_ChannelPause(chan);
	BASS_ChannelSetPosition(chan, (QWORD)BASS_ChannelSeconds2Bytes(chan,ChanA),NULL);
	Wave2mp3(recordfn);
	ABmode=1;
	SetItemImage(songnum,(IsPlaying ? 0:2));
	SetButtons();
//	BASS_StreamFree(chan);
//	chan=NULL;
}

void CS8tuneView::OnWaverecord() 
{
	strcpy(ptxt[ISMP3],"wav");
	CDC *pDC=GetDC();
	DispIroiro(pDC,&m_bitmap_volume,0,WAVoMP3);
	ReleaseDC(pDC);
}

void CS8tuneView::OnUpdateWaverecord(CCmdUI* pCmdUI) 
{
	if(ABmode==2){
		pCmdUI->Enable(false);
	}else{
		pCmdUI->Enable(true);
	}
		if(strstr(ptxt[ISMP3],"wav"))pCmdUI->SetCheck(TRUE);
		else pCmdUI->SetCheck(FALSE);
}

void CS8tuneView::OnSetfocusKensakustr() 
{
	FocusListKen=1;	
}

void CS8tuneView::OnSetfocusSonglist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	FocusListKen=0;
	*pResult = 0;
}
void CS8tuneView::OnMp3record() 
{
	if(IsLameEncoder()){
		strcpy(ptxt[ISMP3],"mp3");
		CDC *pDC=GetDC();
		DispIroiro(pDC,&m_bitmap_volume,0,WAVoMP3);
		ReleaseDC(pDC);
	}else{
		MessageBox(LAMEERRMESS);
	}	
}

void CS8tuneView::OnUpdateMp3record(CCmdUI* pCmdUI) 
{
	if(ABmode==2){
		pCmdUI->Enable(false);
	}else{
		pCmdUI->Enable(true);
	}
	if(strstr(ptxt[ISMP3],"mp3"))pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}
void CS8tuneView::OnDropFiles(HDROP hDropInfo) 
{
	HSTREAM tchan;
	char fn[300],name[300],artist[300];
	int NameSize = sizeof(fn);
	int FileNumber;
	CString str;
	int sc,i,mlen;
	FileNumber = DragQueryFile(hDropInfo, 0xffffffff, fn, NameSize);
	for(i=0; i<FileNumber; i++){
		DragQueryFile(hDropInfo, i, fn, NameSize);
		if(!IsSong(fn))continue;
		if(!(tchan=Bass_StreamCreate(fn))){
			continue;
		}
		mlen = (int)(BASS_ChannelBytes2Seconds(tchan, BASS_ChannelGetLength(tchan, BASS_POS_BYTE))*10.0f);
		if(mlen<10)continue;//1秒以下は無視
//		GetNameArtist(tchan,fn,name,artist);
		GetNameArtist(fn,name,artist);
		BASS_StreamFree(tchan);tchan=NULL;
		AddSongFile(fn,name,artist,mlen);
	}
	sc=SetSongCnt();
	if((songnum=GetSongnum(sc))==-1){//スピーカー付きアイテムがない。
		BASS_StreamFree(chan);chan=NULL;
		IsPlaying=false;
		songnum=0;
		if(sc>0)StartSong(songnum,false);
		SetSongsSelected(songnum,1);
	}
	UpdateData(false);
	CFormView::OnDropFiles(hDropInfo);
}

void CS8tuneView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if(checkpos(point)==1&&chan!=0){
		char a2b[31];
		OnTocusong();
		ChanA=0;
		ChanB=BASS_ChannelBytes2Seconds(chan, BASS_ChannelGetLength(chan, BASS_POS_BYTE));
		seta2bstr(a2b,posa=0,posb=int(10.0*ChanB));
		m_songlist.SetItemText(songnum,s8a2b,a2b);
	}
	CFormView::OnRButtonDown(nFlags, point);
}

void CS8tuneView::OnTocusong() 
{
	m_songlist.SetFocus();
	if(m_songlist.GetItemState(songnum,LVIS_SELECTED)==0)
		SetSongsSelected(songnum,1);
	m_songlist.EnsureVisible(songnum, FALSE);
}

void CS8tuneView::OnAddfiles() 
{
	int mlen,sc;
	HSTREAM tchan;
	CFileDialog fdlg(TRUE,NULL,NULL,OFN_ALLOWMULTISELECT|OFN_LONGNAMES,"Songs (*.mp3;*.m4a;*.aac;*.wma;*.wav )|*.mp3; *.m4a; *.aac; *.wma; *.wav|All Files (*.*)|*.*||",NULL);
	CString str;
	char fn[301],buf[8192],name[301],artist[301];
	buf[0]=0;
	fdlg.m_ofn.lpstrFile=buf;
	fdlg.m_ofn.nMaxFile=8192;
	if(fdlg.DoModal()==IDOK)
	{
		POSITION pos;
		pos=fdlg.GetStartPosition();
		while(pos!=NULL)
		{
			str=fdlg.GetNextPathName(pos);
			strcpy(fn,LPCTSTR(str));
			if(!(tchan=Bass_StreamCreate(fn))){
				MessageBox("Selected file couldn't be loaded!");
				continue;
			}
			mlen = (int)(BASS_ChannelBytes2Seconds(tchan, BASS_ChannelGetLength(tchan, BASS_POS_BYTE))*10.0f);
			GetNameArtist(fn,name,artist);
			if(mlen<10)continue;//1秒以下は無視
			BASS_StreamFree(tchan);tchan=NULL;
			AddSongFile(fn,name,artist,mlen);
		}
		sc=SetSongCnt();
		if((songnum=GetSongnum(sc))==-1&&sc>0){//スピーカー付きアイテムがない。
			IsPlaying=false;
			songnum=0;
			StartSong(songnum,false);
			SetSongsSelected(songnum,1);
		}
		UpdateData(false);
	}
}
BOOL CS8tuneView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(ChangeCursor){
		SetCursor( m_hCursor );
		return true;
	} 
	return CFormView::OnSetCursor(pWnd, nHitTest, message);
}
void CS8tuneView::OnBegindragSonglist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int i;
	ChangeCursor=true;
	for(i=0;;i++)if(m_songlist.GetItemState(i,LVIS_SELECTED)!=0)break;
	dragstart=i;
	for(i=dragstart;;i++){
		if(m_songlist.GetItemState(i,LVIS_SELECTED)==0)break;
	}
	dragend=i-1;
	*pResult = 0;
}

void CS8tuneView::OnRepeaton() 
{
	RepeatMode=1;strcpy(ptxt[REPEA],"one_r");
	CDC *pDC=GetDC();
	DispIroiro(pDC,&m_bitmap_volume,0,REPEATD);
	ReleaseDC(pDC);
}

void CS8tuneView::OnUpdateRepeaton(CCmdUI* pCmdUI) 
{
	if(strstr(ptxt[REPEA],"one_r"))pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CS8tuneView::OnRepeatoff() 
{
	RepeatMode=0;strcpy(ptxt[REPEA],"one_1");
	CDC *pDC=GetDC();
	DispIroiro(pDC,&m_bitmap_volume,0,REPEATD);
	ReleaseDC(pDC);
}

void CS8tuneView::OnUpdateRepeatoff(CCmdUI* pCmdUI) 
{
	if(strstr(ptxt[REPEA],"one_1"))pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CS8tuneView::OnRenzoku() 
{
	RepeatMode=2;strcpy(ptxt[REPEA],"all_1");
	CDC *pDC=GetDC();
	DispIroiro(pDC,&m_bitmap_volume,0,REPEATD);
	ReleaseDC(pDC);
}
void CS8tuneView::OnUpdateRenzoku(CCmdUI* pCmdUI) 
{
	if(strstr(ptxt[REPEA],"all_1"))pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);	
}

void CS8tuneView::OnRenzokurepeat() 
{
	RepeatMode=3;strcpy(ptxt[REPEA],"all_r");
	CDC *pDC=GetDC();
	DispIroiro(pDC,&m_bitmap_volume,0,REPEATD);
	ReleaseDC(pDC);
}

void CS8tuneView::OnUpdateRenzokurepeat(CCmdUI* pCmdUI) 
{
	if(strstr(ptxt[REPEA],"all_r"))pCmdUI->SetCheck(TRUE);
	else pCmdUI->SetCheck(FALSE);
}

void CS8tuneView::OnTonext() 
{
	m_songlist.SetFocus();
	if(!chan)return;
	ABmode=0;
	if(songnum==m_songlist.GetItemCount()-1){
		StartSong(songnum=0);
	}else{
		StartSong(++songnum);
	}
}

void CS8tuneView::OnTonext2() 
{
	m_songlist.SetFocus();
	if(!chan)return;
	ABmode=1;
	if(songnum==m_songlist.GetItemCount()-1){
		StartSong(songnum=0);
	}else{
		StartSong(++songnum);
	}
	BASS_ChannelSetPosition(chan, (QWORD)BASS_ChannelSeconds2Bytes(chan, ChanA),NULL);
//	SetButtons();
}

void CS8tuneView::OnRewind() 
{
	m_songlist.SetFocus();
	if(!chan)return;
	int	pos=(int)(10.0*BASS_ChannelBytes2Seconds(chan, BASS_ChannelGetPosition(chan,NULL)));
	playpos=0;
	ABmode=0;
	if(pos<5){
		if(songnum==0)songnum=m_songlist.GetItemCount()-1;
		else songnum--;
		StartSong(songnum);
	}else{
		BASS_ChannelSetPosition(chan, (QWORD)BASS_ChannelSeconds2Bytes(chan, 0),NULL);
	}
//	SetButtons();
}

void CS8tuneView::OnRewind2() 
{
	m_songlist.SetFocus();
	if(!chan)return;
	int	pos=(int)(10.0*BASS_ChannelBytes2Seconds(chan, BASS_ChannelGetPosition(chan,NULL)));
	int posa=int(ChanA*10.0);
	ABmode=1;
	playpos=0;
	if(pos>=posa&&pos<posa+5){
		if(songnum==0)songnum=m_songlist.GetItemCount()-1;
		else songnum--;
		StartSong(songnum);
	}else{
		BASS_ChannelSetPosition(chan, (QWORD)BASS_ChannelSeconds2Bytes(chan,ChanA),NULL);
	}
//	SetButtons();
}

void CS8tuneView::OnItemchangedSonglist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int tempfsn=0;
	static int fsn=-100;
	if(!oyasumiF){
		tempfsn=FindFocused(&m_songlist);
		if(tempfsn!=-1&&fsn!=tempfsn){
			fsn=tempfsn;
			SetKeyCent(fsn,1);
		}
	}
	*pResult = 0;
}

void CS8tuneView::OnTonow() 
{
	OnTocusong();
}
bool bartype[6]={1,1,0,0,0};
DWORD rgbs[6][5]={	RGB(254,254,254),RGB(200,200,200),RGB(255,255,255),RGB(225,225,225),RGB(250,250,250),
					RGB(254,254,254),RGB(235,235,235),RGB(200,200,200),RGB(245,245,245),RGB(250,250,250),
					RGB(150,150,150),RGB(200,200,200),RGB(0,0,0),RGB(225,225,225),RGB(100,100,100),
					RGB(255,10,15),RGB(80,80,255),RGB(0,0,0),RGB(80,255,80),RGB(255,10,15),
					RGB(155,70,155),RGB(180,255,200),RGB(55,55,55),RGB(180,180,255),RGB(185,90,185)};

void CS8tuneView::SetBarColor(int n)//0 or 1
{

//	CDC *pDC=GetDC();
	int type;
	DWORD oldbtn;
	oldbtn=RGBbtn;
	sscanf(ptxt[COLORTYPE],"%d",&type);
	type=(type+n)%5;
	sprintf(ptxt[COLORTYPE],"%d",type);
	BARtype=bartype[type];
	RGBbtn=rgbs[type][0];
	RGBwaku=rgbs[type][1];
	RGBsumi=rgbs[type][2];
	RGBa2b=rgbs[type][3];
	RGBhisi=rgbs[type][4];
//	ChangeBtnsColor(oldbtn,RGBbtn);
//	ReleaseDC(pDC);
//	SetButtons();
}	

void CS8tuneView::OnCtrlA() 
{
	SetBarColor(1);
}

void CS8tuneView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	if(::IsWindow(m_songlist.m_hWnd)){
		CRect rect;
		if(cx>DEFINITDX){WSx=cx;s8dx=(cx-DEFINITDX)/2;}
		else{WSx=DEFINITDX;s8dx=0;}
		if(cy>DEFINITDY){WSy=cy;s8dy=cy-DEFINITDY;}
		else{WSy=DEFINITDY;s8dy=0;}
		setctrls();
	}
}

void CS8tuneView::OnDoubleclickedStart() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	
}

void CS8tuneView::OnKensakutype() 
{
	kensakutype+=1;
	kensakutype=kensakutype%3;
	if(kensakutype==0)m_kentypectrl.SetBitmap(m_bitmap_kensong);
	else if(kensakutype==1)m_kentypectrl.SetBitmap(m_bitmap_kenartist);
	else m_kentypectrl.SetBitmap(m_bitmap_kenpath);
	UpdateData(false);
//	m_kentypectrl.SetFocus();
	m_kensakuctl.SetFocus();
}

void CS8tuneView::OnPause() 
{
	m_songlist.SetFocus();
	if(ABmode==2)return;//0:全 1:範囲　2:録音
	if(!chan){
//		StartSong(songnum);
		return;
	}
	playpos=0;
	ABmode=0;
	IsPlaying=false;
	BASS_ChannelPause(chan);
	SetItemImage(songnum,(IsPlaying ? 0:2));//
//	SetButtons();	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	
}

void CS8tuneView::OnPause1() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	m_songlist.SetFocus();
	if(ABmode==2)return;
	if(!chan){
//		StartSong(songnum);
		return;
	}
	playpos=0;
	double pos=BASS_ChannelBytes2Seconds(chan, BASS_ChannelGetPosition(chan,NULL));
	if(pos<ChanA||pos>ChanB){
		BASS_ChannelSetPosition(chan, (QWORD)BASS_ChannelSeconds2Bytes(chan,ChanA),NULL);
	}
	ABmode=1;
	IsPlaying=false;
	BASS_ChannelPause(chan);
	SetItemImage(songnum,(IsPlaying ? 0:2));//	
}
int prt1(CDC *pDC,CDC *MemDC,int x,int y,char c)
{
	int retx=8,x1=0,y1=0;
	if(c=='+')x1+=8*10;
	else if(c=='-')x1+=8*12;
	else if(c=='.'){
		retx=4;
		x1+=123;
	}
	else if(c=='0')x1+=8*0;
	else if(c=='1')x1+=8*1;
	else if(c=='2')x1+=8*2;
	else if(c=='3')x1+=8*3;
	else if(c=='4')x1+=8*4;
	else if(c=='5')x1+=8*5;
	else if(c=='6')x1+=8*6;
	else if(c=='7')x1+=8*7;
	else if(c=='8')x1+=8*8;
	else if(c=='9')x1+=8*9;
	else if(c==37)x1+=8*13;//'%%'
	pDC->BitBlt(x,y,8,9,MemDC,x1,y1,SRCAND);//plusminus
	return retx;
}
void CS8tuneView::SetKeyCent(int fsn,int f) 
{
	int p,i,nx;
//	double dd;
	float ff;
//	char buf[50],para[31];
	char para[31];
	CDC MemDC;
	CBitmap *pOldBmp;
	CDC *pDC=GetDC();
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(&m_bitmap_volume);
	//keys
	{
		int x=s8dx+445+70-149/2,y=WSy-40,x1=0,y1=0,xd=8,yd=11,d=8;
		m_songlist.GetItemText(fsn,s8key,para,19);
		sscanf(para,"%ff",&ff);
		p=int(ff*20.0);
//		if(p>=0)sprintf(buf,"+%d.%02d",(p*5)/100,(p*5)%100);//-75%  200%
//		else sprintf(buf,"-%d.%02d",(-p*5)/100,(-p*5)&100);
		if(f)m_barkey.SetScrollPos(p);
		pDC->FillSolidRect(x,y,100,11,RGBsysbtn);
		pDC->BitBlt(x-38,y,65,9,&MemDC,43,51,SRCAND);
		x=x+30;
		nx=0;//
		for(i=0;para[i]!=0;i++){
			nx=prt1(pDC,&MemDC,x+=nx,y,para[i]);
		}
	}
	//tempo
	{
		int x=s8dx+63-3+73/2+10,y=WSy-40,x1=0,y1=0,xd=8,yd=11,d=8;
		m_songlist.GetItemText(fsn,s8tempo,para,19);
		sscanf(para,"%d%%",&p);
		if(f)m_bartempo.SetScrollPos(p);
		pDC->FillSolidRect(x,y,127,11,RGBsysbtn);
		pDC->BitBlt(x,y,42,9,&MemDC,0,63,SRCAND);
		x=x+42;
		nx=0;
		for(i=0;para[i]!=0;i++){
			nx=prt1(pDC,&MemDC,x+=nx,y,para[i]);
		}
	}
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
	ReleaseDC(pDC);
}

void DispTotal(CDC *pDC,CBitmap *m_bitmap_volume)
{//x=X0+503,y=F12Y-4
	CDC MemDC;
	CBitmap *pOldBmp;
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp=MemDC.SelectObject(m_bitmap_volume);
//	int x=s8dx+550,y=WSy-21,x1=0,y1=0,xd=8,yd=11,d=8;
	int x=X0+522,y=F12Y-5,x1=0,y1=0,xd=8,yd=9,d=8;
	int sc=m_songlist.GetItemCount();
	pDC->FillSolidRect(x,y,60,11,RGBsysbtn);
	pDC->BitBlt(x+0*d,y,xd,yd,&MemDC,x1+d*((sc/10000)%10),y1,SRCAND);
	pDC->BitBlt(x+1*d,y,xd,yd,&MemDC,x1+d*((sc/1000)%10),y1,SRCAND);
	pDC->BitBlt(x+2*d,y,xd,yd,&MemDC,x1+d*((sc/100)%10),y1,SRCAND);
	pDC->BitBlt(x+3*d,y,xd,yd,&MemDC,x1+d*((sc/10)%10),y1,SRCAND);
	pDC->BitBlt(x+4*d,y,xd,yd,&MemDC,x1+d*(sc%10),y1,SRCAND);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}
