#if !defined(AFX_ADDTHREAD_H__92324A99_2619_4ABD_946F_3F059F3D0D21__INCLUDED_)
#define AFX_ADDTHREAD_H__92324A99_2619_4ABD_946F_3F059F3D0D21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddThread.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CAddThread �_�C�A���O

class CAddThread : public CDialog
{
// �R���X�g���N�V����
public:
	CAddThread(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAddThread)
	enum { IDD = IDD_ADDTHREAD };
	CString	m_songpath;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAddThread)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAddThread)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ADDTHREAD_H__92324A99_2619_4ABD_946F_3F059F3D0D21__INCLUDED_)
