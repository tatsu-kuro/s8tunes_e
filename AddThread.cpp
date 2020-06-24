// AddThread.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "s8tune.h"
#include "AddThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern char ThreadSong[MAX_PATH];
extern bool ThreadFlag;//�����false�ɂ����thread���甲����

/////////////////////////////////////////////////////////////////////////////
// CAddThread �_�C�A���O


CAddThread::CAddThread(CWnd* pParent /*=NULL*/)
	: CDialog(CAddThread::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddThread)
	m_songpath = _T("");
	//}}AFX_DATA_INIT
}


void CAddThread::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddThread)
	DDX_Text(pDX, IDC_SONGPATH, m_songpath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddThread, CDialog)
	//{{AFX_MSG_MAP(CAddThread)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddThread ���b�Z�[�W �n���h��

void CAddThread::OnTimer(UINT nIDEvent) 
{
	m_songpath=ThreadSong;
	UpdateData(false);
	CDialog::OnTimer(nIDEvent);
}

BOOL CAddThread::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ThreadFlag=true;;
	
	SetTimer(1,100,NULL);
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CAddThread::OnCancel() 
{
	// TODO: ���̈ʒu�ɓ��ʂȌ㏈����ǉ����Ă��������B
	ThreadFlag=false;
	KillTimer(1);
	CDialog::OnCancel();
}

void CAddThread::OnOK() 
{
	if(ThreadFlag==true){
		ThreadFlag=false;
		Sleep(500);
		return;
	}
	KillTimer(1);
	CDialog::OnOK();
}
