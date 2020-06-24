// s8tuneView.h : CS8tuneView クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_S8TUNEVIEW_H__671C0D32_B1B3_41C8_ABA6_12A06C2348D3__INCLUDED_)
#define AFX_S8TUNEVIEW_H__671C0D32_B1B3_41C8_ABA6_12A06C2348D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CS8tuneView : public CFormView
{
protected: // シリアライズ機能のみから作成します。
	CS8tuneView();
	DECLARE_DYNCREATE(CS8tuneView)

public:
	//{{AFX_DATA(CS8tuneView)
	enum { IDD = IDD_S8TUNE_FORM };
	CStatic	m_kentypectrl;
	CButton	m_pause2;
	CButton	m_pause;
	CStatic	m_tonow;
	CStatic	m_bittonow;
	CStatic	m_s_statictempo;
	CStatic	m_s_statickey;
	CStatic	m_s_staticcent;
	CStatic	m_s_songname;
	CButton	m_kensaku;
	CButton	m_tonext2;
	CButton	m_tonext;
	CButton	m_hozon;
	CButton	m_start2;
	CButton	m_start;
	CButton	m_rewind2;
	CButton	m_rewind;
	CButton	m_setb;
	CButton	m_seta;
	CEdit	m_kensakuctl;
	CScrollBar	m_bartempo;
	CScrollBar	m_barkey;
	CString	m_songname;
	CString	m_kensakustr;
	//}}AFX_DATA

// アトリビュート
public:
	CS8tuneDoc* GetDocument();
	CImageList* m_pImageList;
// オペレーション
public:
	static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	void AddSongFile(char *fn,char *name,char *artist,int mlen);
	void ChangeBtnsColor(DWORD rgb1,DWORD rgb2);
	void DispSongA2B(CDC* pDC);//	void AddSongs(int type);
	void DragDrop(int n);
	int GetItemImagen(int itemn);
	int GetSongnum(int sc);
	int InsertItemBuf(char *buf,int n);
	void RenumberItem(int sub);
	void read_s8t();
	void readini();
	void SetBarColor(int n);
	void SetButtons();
	void setctrls();
	void SetFontSize();
	void SetItemImage(int itemn,int imgn);
	void SetKeyCent(int fsn,int f);
	void sets8strs(char *buf,int i);
	int SetSongCnt();
	void SetSongsSelected(int sn,int n);
	void SetStr(int tck,int p,int sn);
	void StartSearchDir( void *p_p );
	void StartSong(int sn,bool flag=true);
	void StopRecord();
	void Wave2mp3(char *wav);
	void writeini();
	void write_s8t();
	void Setab(); 
// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CS8tuneView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	virtual void OnInitialUpdate(); // 構築後の最初の１度だけ呼び出されます。
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	HCURSOR  m_hCursor;
	RECT m_playbarrect;
	CBitmap m_bitmap_volume;
	CBitmap m_bitmap_totop;
	CBitmap md_bitmap_totop;
	CBitmap m_bitmap_tonext;
	CBitmap md_bitmap_tonext;
	CBitmap m_bitmap_play;
	CBitmap md_bitmap_play;
	CBitmap m_bitmap_pause;
	CBitmap md_bitmap_pause;
	CBitmap m_bitmap_tonow;
	CBitmap m_bitmap_seta;
	CBitmap m_bitmap_setb;
	CBitmap m_bitmap_saveab;
	CBitmap m_bitmap_stop;
	CBitmap m_bitmap_retr;
	CBitmap m_bitmap_kensong;
	CBitmap m_bitmap_kenartist;
	CBitmap m_bitmap_kenpath;

	virtual ~CS8tuneView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CToolTipCtrl m_ToolTip;

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CS8tuneView)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStart();
	afx_msg void OnDblclkSonglist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickSonglist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteone();
	afx_msg void OnDuplicate();
	afx_msg void OnColumnclickSonglist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRewind();
	afx_msg void OnSeta();
	afx_msg void OnSetb();
	afx_msg void OnStart2();
	afx_msg void OnRewind2();
	afx_msg void OnRename();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnAddfolder();
	afx_msg void OnDeleteall();
	afx_msg void OnKensaku();
	afx_msg void OnReturn();
	afx_msg void OnHozon();
	afx_msg void OnWaverecord();
	afx_msg void OnUpdateWaverecord(CCmdUI* pCmdUI);
	afx_msg void OnSetfocusKensakustr();
	afx_msg void OnSetfocusSonglist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMp3record();
	afx_msg void OnUpdateMp3record(CCmdUI* pCmdUI);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTocusong();
	afx_msg void OnAddfiles();
	afx_msg void OnRepeaton();
	afx_msg void OnUpdateRepeaton(CCmdUI* pCmdUI);
	afx_msg void OnRepeatoff();
	afx_msg void OnUpdateRepeatoff(CCmdUI* pCmdUI);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnBegindragSonglist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRenzoku();
	afx_msg void OnRenzokurepeat();
	afx_msg void OnUpdateRenzokurepeat(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRenzoku(CCmdUI* pCmdUI);
	afx_msg void OnTonext();
	afx_msg void OnTonext2();
	afx_msg void OnItemchangedSonglist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTonow();
	afx_msg void OnCtrlA();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnChangeKensakustr();
	afx_msg void OnDoubleclickedStart();
	afx_msg void OnKensakutype();
	afx_msg void OnPause();
	afx_msg void OnPause1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // s8tuneView.cpp ファイルがデバッグ環境の時使用されます。
inline CS8tuneDoc* CS8tuneView::GetDocument()
   { return (CS8tuneDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_S8TUNEVIEW_H__671C0D32_B1B3_41C8_ABA6_12A06C2348D3__INCLUDED_)
