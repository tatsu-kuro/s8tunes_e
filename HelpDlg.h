#if !defined(AFX_HELPDLG_H__B6538604_0337_41E0_BAC2_92FA059AC878__INCLUDED_)
#define AFX_HELPDLG_H__B6538604_0337_41E0_BAC2_92FA059AC878__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HelpDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CHelpDlg �_�C�A���O

class CHelpDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CHelpDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CHelpDlg)
	enum { IDD = IDD_HELPDLG };
	CListBox	m_help;
	CString	m_orig;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CHelpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CHelpDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_HELPDLG_H__B6538604_0337_41E0_BAC2_92FA059AC878__INCLUDED_)
