// HelpDlg.cpp : �C���v�������e�[�V���� �t�@�C��
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
// CHelpDlg �_�C�A���O


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
// CHelpDlg ���b�Z�[�W �n���h��

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
	SetWindowText("�ڔ��`���[���Y  s8Tunes : Version 12.0");
	m_orig="By �������@2019�N03��23��";
	htxt[n++]="-------------------------------------------------------------------------------";
	htxt[n++]="                        �� s8Tunes �� �̊T�v�A�g����";
	htxt[n++]="-------------------------------------------------------------------------------";
	htxt[n++]=" ";
	htxt[n++]="�܂��ŏ��ɁA���y�t�@�C����o�^���Ă��������B";
	htxt[n++]="�t�@�C�����j���[�́u�t�H���_��o�^�v�ŁA�t�H���_�̒��̉��y�t�@�C�������ׂēo�^�ł��܂��B";
	htxt[n++]="�u�t�H���_��o�^�v�ŁA���[�J���f�B�X�N�h���C�u�S�̂��w�肷�邱�Ƃ��\�ł��B";
	htxt[n++]="�e�X�̉��y�t�@�C����s8Tunes�̃E�B���h�E�Ƀh���b�O���h���b�v���Ă��o�^�\�ł��B";
	htxt[n++]=" ";
	htxt[n++]="�Ȃ̑I���i�n�C���C�g�\���j�A���t�Ɋւ��Ă͈ȉ��̑��삪�\�ł��B";
	htxt[n++]="   �N���b�N�F���̋Ȃ̑I���i�n�C���C�g�\���j�B";
	htxt[n++]="   �_�u���N���b�N�F���̋Ȃ̉��t�J�n�B";
	htxt[n++]="   �㉺���APgUp�APgDn�AHome�AEnd�F����Ȃ�̋Ȃ�I���B";
	htxt[n++]="   A-Z�F�Ȗ��̓��̕������������A���������炻���I���B";
	htxt[n++]="   Enter�F�I���i�n�C���C�g�\���j�Ȃ̉��t�J�n�B";
	htxt[n++]="   Shift�L�[�������Ȃ��牉�t���J�n������ƁA�L�[�����������Ԃɉ����ċȊJ�n��x�点�܂��B";
	htxt[n++]="   Delete�L�[�F���t���̋Ȃ�I���A�\���B";
	htxt[n++]="   �ŏ�i�E�[������̊ۂ����̃N���b�N�F���t���̋Ȃ�I���A�\���B";
	htxt[n++]=" ";
	htxt[n++]="�I���i�n�C���C�g�\���j�Ȃ�SPEED�AKEY.CENT�̕ύX�͉��i�̃X���C�h�o�[�ōs���܂��B";
	htxt[n++]="   KF11,F12�Ŕ������A�X���C�h�o�[�̍��E�[�{�^����5CENT���A";
	htxt[n++]="   �X���C�h�o�[���̃N���b�N��50CENT�������ł��܂��B";
	htxt[n++]=" ";
	htxt[n++]="�ȍ���(������)���h���b�O���h���b�v���āA�ȍ��ڂ̈ړ��A���ёւ����ł��܂��B";
	htxt[n++]=" ";
	htxt[n++]="�Đ��ʒu�������㕔�̃X�N���[���o�[�̕H�`�}�[�N�͍��N���b�N�œ������܂��B";
	htxt[n++]="�܂����E���L�[�ő�����A�����߂����\�ł��B";
	htxt[n++]=" ";
	htxt[n++]="�Đ����[�h�őI���ȘA���A�I���ȃ��s�[�g��ݒ肷��ƁACtrl�L�[�AShift�L�[�ŕ����I�������Ȃ�";
	htxt[n++]="�Đ����܂��B�����Ȃ��I������ĂȂ���΁A�S�Ȃ��Đ����܂��B ";
	htxt[n++]=" ";
	htxt[n++]="���X�g�̔C�ӂ̋Ȃ��E�N���b�N����Ɖ��L�̃T�u���j���[���o�܂��B";
	htxt[n++]="�@�P�j�I������(������)�̍폜�F���X�g��������邾���ł��B";
	htxt[n++]="�@�@�@�������As8Songs�t�H���_�ɂ���Ȃ̓t�@�C�����폜���܂��B";
	htxt[n++]="�@�Q�j���ڂ̕����F���y�t�@�C���͂��̂܂܂ŁA���X�g��ŕ������邾���ł��B";
	htxt[n++]="�@�R�j�Ȗ��A�A�[�e�B�X�g���̕ύX�F���y�t�@�C���̃^�O�������������܂��B";
	htxt[n++]=" ";
	htxt[n++]="���X�g�̃^�C�g�������́u�Ȗ��v�u�A�[�e�B�X�g�v�u���ԁv�u�e���|�v�Ȃǂ��N���b�N����ƁA";
	htxt[n++]="���̍��ڂŃ\�[�g���܂��B";
	htxt[n++]=" ";
	htxt[n++]="�͈͍Đ�����ѕۑ��̎n�_�A�I�_�͂��ꂼ��A�Ȃ̓��A�Ȃ̍Ō�ɏ����ݒ肳��Ă��܂��B";
	htxt[n++]="�C�ӂ̉��t���_��[�n�_]�A[�I�_] �{�^���������Ƃ��̈ʒu���n�_�A�I�_�ɐݒ肳��܂��B";
	htxt[n++]="�n�_�ƏI�_�̎O�p�}�[�N���h���b�O���Ďn�_�A�I�_�̈ʒu��ݒ肷�鎖���o���܂��B";
	htxt[n++]="�Đ��o�[���E�N���b�N����Ǝn�_�ƏI�_���Ȃ̓��ƍŌ�ɍĐݒ肵�܂��B";
	htxt[n++]=" ";
	htxt[n++]="�ۑ��{�^���������Ǝn�_����I�_�܂ł�ۑ����܂��B";
	htxt[n++]="wav�t�@�C���ւ̕ۑ��͂��̂܂܉\�ł����Amp3�t�@�C���֕ۑ�����ɂ�lame.exe���K�v�ł��B";
	htxt[n++]="lame.exe��s8Tunes.exe�Ɠ����t�H���_�ɓ���ĉ������B";
	htxt[n++]="�͈͍Đ����̃t�@�C���́A���t�@�C�����ɘA�Ԃ�t�L�������O�ŁAs8Songs�t�H���_�ɕۑ�����A";
	htxt[n++]="���X�g�̍ŏ㕔�ɓo�^����܂��B";
	htxt[n++]=" ";
	htxt[n++]="�����ł͓��͕������u�Ȗ��v�u�A�[�e�B�X�g�v��ꏊ�v�Ɋ܂܂��Ȃ����X�g�̍ŏ㕔�Ɉړ����A";
	htxt[n++]="���v�����Ȑ����\������܂��B�����������󔒂ŋ�؂�ƁAAND�������o���܂��B";
	htxt[n++]=" ";
	htxt[n++]="Ctrl+A �ōĐ��o�[�A�H�`�Đ��}�[�N�Ȃǂ̐F�̍ق�5��ނ���I��ύX�ł��܂��B";
	htxt[n++]=" ";
	htxt[n++]="-------------------------------------------------------------------------------";
	htxt[n++]="�o�[�W�����A�b�v�͉��L�T�C�g�ōs���Ă��܂��B";
	htxt[n++]="www.shaku6.com";
	htxt[n++]="-------------------------------------------------------------------------------";
	htxt[n++]="";
#endif		
	for(i=0;strlen(htxt[i])!=0;i++){
		m_help.InsertString(-1,htxt[i]);//sort���Ȃ�
	}
	UpdateData(false);	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}
