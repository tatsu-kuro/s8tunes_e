// MainFrm.h : CMainFrame �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__1292ABB2_E0B6_41DF_868F_B3AB0F9543B4__INCLUDED_)
#define AFX_MAINFRM_H__1292ABB2_E0B6_41DF_868F_B3AB0F9543B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "HelpDlg.h"
class CMainFrame : public CFrameWnd
{
	
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// �A�g���r���[�g
public:
	CHelpDlg* myDlg;
// �I�y���[�V����
public:
//void SaveWindowPlacement();
//void InitWindowPlacement(CREATESTRUCT& cs);

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnDestroy();
	afx_msg void OnHelpdlg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MAINFRM_H__1292ABB2_E0B6_41DF_868F_B3AB0F9543B4__INCLUDED_)
