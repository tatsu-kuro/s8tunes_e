#if !defined(AFX_RENAME_H__02E8E5AA_75B0_4B9A_A601_3ABF980B350E__INCLUDED_)
#define AFX_RENAME_H__02E8E5AA_75B0_4B9A_A601_3ABF980B350E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Rename.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CRename �_�C�A���O

class CRename : public CDialog
{
// �R���X�g���N�V����
public:
	CRename(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	char rnstr[100];
// �_�C�A���O �f�[�^
	//{{AFX_DATA(CRename)
	enum { IDD = IDD_RENAME };
	CString	m_rename;
	CString	m_rename2;
	BOOL	m_changetag;
	CString	m_changetagtxt;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CRename)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CRename)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_RENAME_H__02E8E5AA_75B0_4B9A_A601_3ABF980B350E__INCLUDED_)
