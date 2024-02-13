//======================================================
//
//�i���o�[����[bg.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "progressbar.h"
#include "manager.h"
#include "object2D.h"

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CProgressBar::CProgressBar(int nPriority)
{
	
}

//=================================
//�f�X�g���N�^
//=================================
CProgressBar::~CProgressBar()
{
}

//=================================
//������
//=================================
HRESULT CProgressBar::Init(void)
{
	//�ł���
	return S_OK;
}

//=================================
//�I��
//=================================
void CProgressBar::Uninit(void)
{
	m_pFrame->Uninit();
	m_pBar->Uninit();

	//�Ǘ��I�u�W�F�N�g�j��
	Release();
}

//=================================
//�X�V
//=================================
void CProgressBar::Update(void)
{
	
}

//=================================
//�`��
//=================================
void CProgressBar::Draw(void)
{
	
}

//=================================
//��������
//=================================
CProgressBar* CProgressBar::Create(const D3DXVECTOR3 pos, const float fWidth, const float fHeight)
{
	CProgressBar* pObjProgressBar = NULL;

	if (pObjProgressBar == NULL)
	{
		//�Ǘ��I�u�W�F�N�g�����E������
		pObjProgressBar = new CProgressBar;
		pObjProgressBar->Init();
		pObjProgressBar->m_fDefWidth = fWidth * 0.95f;

		//�g�����E������
		pObjProgressBar->m_pFrame = CObject2D::Create(pos, CManager::VEC3_ZERO, fWidth, fHeight, PRIORITY_UI);
		pObjProgressBar->m_pFrame->Init();
		pObjProgressBar->m_pFrame->BindTexture(-1);

		//�o�[�����E������
		pObjProgressBar->m_pBar = CObject2D::Create(pos, CManager::VEC3_ZERO, fWidth * 0.95f, fHeight * 0.95f, PRIORITY_UI);
		pObjProgressBar->m_pBar->Init();
		pObjProgressBar->m_pBar->BindTexture(-1);
		pObjProgressBar->m_pBar->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		return pObjProgressBar;
	}
	else
	{
		return NULL;
	}
}

//=================================
//�����ݒ�
//=================================
void CProgressBar::SetPercent(const float fParcent)
{
	m_fParcent = fParcent;	//�l�ύX
	m_pBar->SetSize(m_fDefWidth * fParcent, m_pBar->GetHeight());
}
