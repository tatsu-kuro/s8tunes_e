// s8tuneDoc.cpp : CS8tuneDoc �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "s8tune.h"

#include "s8tuneDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CS8tuneDoc

IMPLEMENT_DYNCREATE(CS8tuneDoc, CDocument)

BEGIN_MESSAGE_MAP(CS8tuneDoc, CDocument)
	//{{AFX_MSG_MAP(CS8tuneDoc)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CS8tuneDoc �N���X�̍\�z/����

CS8tuneDoc::CS8tuneDoc()
{
	// TODO: ���̈ʒu�ɂP�x�����Ă΂��\�z�p�̃R�[�h��ǉ����Ă��������B

}

CS8tuneDoc::~CS8tuneDoc()
{
}

BOOL CS8tuneDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���̈ʒu�ɍď�����������ǉ����Ă��������B
	// (SDI �h�L�������g�͂��̃h�L�������g���ė��p���܂��B)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CS8tuneDoc �V���A���C�[�[�V����

void CS8tuneDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���̈ʒu�ɕۑ��p�̃R�[�h��ǉ����Ă��������B
	}
	else
	{
		// TODO: ���̈ʒu�ɓǂݍ��ݗp�̃R�[�h��ǉ����Ă��������B
	}
}

/////////////////////////////////////////////////////////////////////////////
// CS8tuneDoc �N���X�̐f�f

#ifdef _DEBUG
void CS8tuneDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CS8tuneDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CS8tuneDoc �R�}���h
