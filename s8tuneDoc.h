// s8tuneDoc.h : CS8tuneDoc �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_S8TUNEDOC_H__D45E635D_81E7_4303_9FCC_CCCE8AB547CE__INCLUDED_)
#define AFX_S8TUNEDOC_H__D45E635D_81E7_4303_9FCC_CCCE8AB547CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CS8tuneDoc : public CDocument
{
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CS8tuneDoc();
	DECLARE_DYNCREATE(CS8tuneDoc)

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

//�I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CS8tuneDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CS8tuneDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CS8tuneDoc)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_S8TUNEDOC_H__D45E635D_81E7_4303_9FCC_CCCE8AB547CE__INCLUDED_)
