//======================================================
//
//�`���[�g���A���p�I�u�W�F����[tutorialobj.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "tutorialobj.h"
#include "manager.h"
#include "object3D.h"
#include "objectX.h"
#include "xmodel.h"
#include "debugproc.h"
#include "texture.h"

//�ÓI�����o�ϐ�
CTutorialObj* CTutorialObj::m_pTop = nullptr;
CTutorialObj* CTutorialObj::m_pCur = nullptr;
int CTutorialObj::m_nNumAll = 0;

//=================================
//�R���X�g���N�^
//=================================
CTutorialObj::CTutorialObj(int nPriority) : CObject(nPriority)
{
	m_pos = CManager::VEC3_ZERO;
	m_fWidth = CManager::FLT_ZERO;
	m_fHeight = CManager::FLT_ZERO;
	m_fDepth = CManager::FLT_ZERO;

	if (m_pCur == nullptr)
	{//�Ō�������Ȃ��i���Ȃ킿�擪�����Ȃ��j
		m_pTop = this;			//�����擪
		m_pPrev = nullptr;		//�O��N�����Ȃ�
		m_pNext = nullptr;
	}
	else
	{//�Ō��������
		m_pPrev = m_pCur;		//�Ō���������̑O�̃I�u�W�F
		m_pCur->m_pNext = this;	//�Ō���̎��̃I�u�W�F������
		m_pNext = nullptr;		//�����̎��̃I�u�W�F�͂��Ȃ�
	}
	m_pCur = this;				//�����Ō��
	m_pCollider = nullptr;
	m_nNumber = 0;
	m_bPopup = false;
	m_nNumAll++;
}

//=================================
//�f�X�g���N�^
//=================================
CTutorialObj::~CTutorialObj()
{
}

//=================================
//������
//=================================
HRESULT CTutorialObj::Init(void)
{
	SetType(TYPE_TUTORIALOBJ);
	return S_OK;
}

//=================================
//�I��
//=================================
void CTutorialObj::Uninit(void)
{
	if (m_pCollider != nullptr)
	{
		m_pCollider->Release();
		m_pCollider = nullptr;
	}

	Release();
}

//=================================
//�X�V
//=================================
void CTutorialObj::Update(void)
{
	m_bPopup = false;	//�\�������Ȃ��i�Ȃ��L�������\��������\��������
}

//=================================
//�`��
//=================================
void CTutorialObj::Draw(void)
{
	//�`���[�g���A���\���ݒ�
	if (m_bPopup == true)
	{
		m_pTutorial->SetCol(D3DCOLOR(0xffffffff));
	}
	else
	{
		m_pTutorial->SetCol(D3DCOLOR(0x00ffffff));
	}
}

//=================================
//����
//=================================
CTutorialObj* CTutorialObj::Create(const D3DXVECTOR3 pos, const int nNumber)
{
	CTutorialObj* pTutorialObj = nullptr;

	if (pTutorialObj == nullptr)
	{
		//�I�u�W�F�N�g�̐���
		pTutorialObj = new CTutorialObj;

		//������
		pTutorialObj->Init();

		//�f�[�^�ݒ�
		pTutorialObj->m_pos = pos;
		pTutorialObj->m_nNumber = nNumber;
		pTutorialObj->m_fWidth = 100.0f;
		pTutorialObj->m_fHeight = 100.0f;
		pTutorialObj->m_fDepth = 200.0f;

		//�����蔻��ݒ�
		pTutorialObj->m_pCollider = CBoxCollider::Create(pTutorialObj);
		pTutorialObj->m_pCollider->SetTag(CBoxCollider::TAG_UNIV);
		pTutorialObj->m_pCollider->SetType(CBoxCollider::TYPE_TRIGGER);

		//�\���p�I�u�W�F����
		pTutorialObj->m_pTutorial = CObject3D::Create(pos + D3DXVECTOR3(0.0f, 200.0f, 50.0f), D3DXVECTOR3(-0.5f * D3DX_PI,0.0f,0.0f), 231.0f, 131.0f, PRIORITY_05);
		pTutorialObj->m_pTutorial->BindTexture(CTexture::PRELOAD_17_TUTORIAL_01 + nNumber);
		pTutorialObj->m_pObj = CObjectX::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 50.0f), CManager::VEC3_ZERO, CXModel::Load("data\\MODEL\\tutorialobj.x"));

		return pTutorialObj;
	}

	return nullptr;
}

//=================================
//���O
//=================================
void CTutorialObj::Exclusion(void)
{
	if (m_pPrev != nullptr)
	{//�O�ɃI�u�W�F������
		m_pPrev->m_pNext = m_pNext;	//�O�̃I�u�W�F�̎��̃I�u�W�F�͎����̎��̃I�u�W�F
	}
	if (m_pNext != nullptr)
	{
		m_pNext->m_pPrev = m_pPrev;	//���̃I�u�W�F�̑O�̃I�u�W�F�͎����̑O�̃I�u�W�F
	}

	if (m_pCur == this)
	{//�Ō���ł���
		m_pCur = m_pPrev;	//�Ō���������̑O�̃I�u�W�F�ɂ���
	}
	if (m_pTop == this)
	{
		m_pTop = m_pNext;	//�擪�������̎��̃I�u�W�F�ɂ���
	}

	//����
	m_nNumAll--;	//�������炷
}