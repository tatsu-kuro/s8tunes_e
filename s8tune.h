// s8tune.h : S8TUNE �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
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
#define ERASEMESS "Erase all songs�H","sure?"
#define ERASE1MESS "Erase selected songs�H","sure?"
#define SAVEBUTMESS "Save"
#define STOPBUTMESS "Stop"
#define TITLEMESS " s8Tunes (ShakuHachi Tunes) Version 12.1"
#else
#define TEMPOSTA "���� : "
#define KEYSTA "�� : "
#define CHANERR "\n\n�́A�������A�������͍Đ��ł��܂���B"
#define KYOKUNUM "���Ȑ�"
#define LAMEERRMESS "Lame.exe �� s8Tunes.exe �̂���t�H���_�ɃR�s�[����ƁAmp3�^���\�ɂȂ�܂��B"
#define TOUROKUMESS  "�Ȃ̉��y�t�@�C���̓o�^���܂��B"
#define ERASEMESS "���ׂĂ̓o�^�𖕏����܂����H","�m�F"
#define ERASE1MESS "�I������Ă���Ȃ𖕏����܂����H","�m�F"
#define SAVEBUTMESS "�ۑ�"
#define STOPBUTMESS "��~"
#define TITLEMESS " �ڔ��`���[���Y(s8Tunes) Version 12.1"
#endif

#if !defined(AFX_S8TUNE_H__F4FA6E2B_CAC5_41CF_B0E0_14EAED6C5E92__INCLUDED_)
#define AFX_S8TUNE_H__F4FA6E2B_CAC5_41CF_B0E0_14EAED6C5E92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CS8tuneApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� s8tune.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CS8tuneApp : public CWinApp
{
public:
	CS8tuneApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CS8tuneApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
	//{{AFX_MSG(CS8tuneApp)
//	afx_msg void OnAppAbout();
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_S8TUNE_H__F4FA6E2B_CAC5_41CF_B0E0_14EAED6C5E92__INCLUDED_)
