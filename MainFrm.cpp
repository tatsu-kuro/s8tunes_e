// MainFrm.cpp : CMainFrame �N���X�̓���̒�`���s���܂��B

#include "stdafx.h"
#include "s8tune.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern char ptxt[][200];

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_DESTROY()
	ON_COMMAND(ID_HELPDLG, OnHelpdlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame �N���X�̍\�z/����

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}
/////////////////////////////////////////////////////////////////////////////
// CMainFrame �N���X�̐f�f

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame ���b�Z�[�W �n���h��

//�ő剻�̎��͎���ő剻���ċN������B�j
void CMainFrame::OnDestroy() 
{
	WINDOWPLACEMENT wndPlace;
	wndPlace.length = sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(&wndPlace);
	sprintf(ptxt[WINXY],"%d,%d,%d,%d,%d",
		wndPlace.rcNormalPosition.left,
		wndPlace.rcNormalPosition.top,
		wndPlace.rcNormalPosition.right,
		wndPlace.rcNormalPosition.bottom,
		wndPlace.showCmd==SW_SHOWMAXIMIZED ? 1:0);
	CFrameWnd::OnDestroy();
}

void CMainFrame::OnHelpdlg() 
{
	myDlg=new CHelpDlg(this);			
}
