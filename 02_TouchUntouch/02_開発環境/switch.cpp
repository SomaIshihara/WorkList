//======================================================
//
//�X�C�b�`����[switch.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "switch.h"
#include "manager.h"
#include "objectX.h"
#include "xmodel.h"
#include "debugproc.h"

//�ÓI�����o�ϐ�
CXModel* CSwitch::m_pModelBase = nullptr;
CXModel* CSwitch::m_pModelMove = nullptr;
CSwitch* CSwitch::m_pTop = nullptr;
CSwitch* CSwitch::m_pCur = nullptr;
int CSwitch::m_nNumAll = 0;
const float CSwitch::MOVE_DEF_HEIGHT = 10.0f;

//=================================
//�R���X�g���N�^
//=================================
CSwitch::CSwitch(int nPriority) : CObject(nPriority)
{
	m_pObjBase = nullptr;
	m_pObjMove = nullptr;
	m_pos = CManager::VEC3_ZERO;
	m_move = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fWidth = CManager::FLT_ZERO;
	m_fHeight = CManager::FLT_ZERO;
	m_fDepth = CManager::FLT_ZERO;
	m_type = TYPE_MAX;

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
	m_nNumAll++;
}

//=================================
//�f�X�g���N�^
//=================================
CSwitch::~CSwitch()
{
}

//=================================
//������
//=================================
HRESULT CSwitch::Init(void)
{
	SetType(TYPE_SWITCH);
	return S_OK;
}

//=================================
//�I��
//=================================
void CSwitch::Uninit(void)
{
	//���f���j��
	if (m_pObjBase != nullptr)
	{
		m_pObjBase->Uninit();
		m_pObjBase = nullptr;
	}
	if (m_pObjMove != nullptr)
	{
		m_pObjMove->Uninit();
		m_pObjMove = nullptr;
	}

	Release();
}

//=================================
//�X�V
//=================================
void CSwitch::Update(void)
{
	if (m_bPush == true)
	{
		m_move.y = -0.1f;	//��
	}
	else
	{
		m_move.y = 0.1f;	//��
	}

	m_pObjMove->SetPos(m_pObjMove->GetPos() + m_move);

	//�オ�艺���肷������ʒu�߂�
	if (m_pObjMove->GetPos().y < m_pos.y + 1.0f)
	{
		m_pObjMove->SetPos(m_pos + D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	else if (m_pObjMove->GetPos().y > m_pos.y + MOVE_DEF_HEIGHT)
	{
		m_pObjMove->SetPos(m_pos + D3DXVECTOR3(0.0f, MOVE_DEF_HEIGHT, 0.0f));
	}
}

//=================================
//�`��
//=================================
void CSwitch::Draw(void)
{
	//�K�v�Ȃ�
}

//=================================
//����
//=================================
CSwitch* CSwitch::Create(const D3DXVECTOR3 pos, const TYPE type)
{
	CSwitch* pSwitch = nullptr;

	if (pSwitch == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pSwitch = new CSwitch;

		//������
		pSwitch->Init();

		//�f�[�^�ݒ�
		pSwitch->m_pos = pos;
		pSwitch->m_type = type;

		//���f�����ǂݍ��܂�ĂȂ���Γǂݍ���
		if (m_pModelBase == nullptr)
		{//�y�䂪�ʂ��
			m_pModelBase = CXModel::Load("data\\MODEL\\switch_01.x");
		}
		if (m_pModelMove == nullptr)
		{//�y�䂪�ʂ��
			m_pModelMove = CXModel::Load("data\\MODEL\\switch_02.x");
		}

		//���f������
		pSwitch->m_pObjBase = CObjectX::Create(pSwitch->m_pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), CManager::VEC3_ZERO, m_pModelBase);
		pSwitch->m_pObjBase->SetCollider();
		pSwitch->m_pObjBase->GetCollider()->SetType(CBoxCollider::TYPE_COLLISION);
		pSwitch->m_pObjBase->SetType(TYPE_SWITCH);

		pSwitch->m_pObjMove = CObjectX::Create(pSwitch->m_pos + D3DXVECTOR3(0.0f, MOVE_DEF_HEIGHT, 0.0f), CManager::VEC3_ZERO, m_pModelMove);
		pSwitch->m_pObjMove->SetCollider();
		pSwitch->m_pObjMove->GetCollider()->SetType(CBoxCollider::TYPE_COLLISION);
		pSwitch->m_pObjMove->SetType(TYPE_SWITCH);

		//�F�ς�
		if (type == TYPE_A)
		{//��
			pSwitch->m_pObjBase->SetColor(true, D3DCOLOR(0xffab7fc7));
			pSwitch->m_pObjMove->SetColor(true, D3DCOLOR(0xffab7fc7));
			pSwitch->m_pObjBase->GetCollider()->SetTag(CBoxCollider::TAG_UNIV);
			pSwitch->m_pObjMove->GetCollider()->SetTag(CBoxCollider::TAG_UNIV);
		}
		else if(type == TYPE_B)
		{//���F
			pSwitch->m_pObjBase->SetColor(true, D3DCOLOR(0xfff7ea31));
			pSwitch->m_pObjMove->SetColor(true, D3DCOLOR(0xfff7ea31));
			pSwitch->m_pObjBase->GetCollider()->SetTag(CBoxCollider::TAG_UNIV);
			pSwitch->m_pObjMove->GetCollider()->SetTag(CBoxCollider::TAG_UNIV);
		}
		else if (type == TYPE_GOAL_A)
		{//�S�[���p�i�^�C�vA�j
			pSwitch->m_pObjBase->SetColor(true, D3DCOLOR(0xfff39aac));
			pSwitch->m_pObjMove->SetColor(true, D3DCOLOR(0xfff39aac));
			pSwitch->m_pObjBase->GetCollider()->SetTag(CBoxCollider::TAG_TYPE_A);
			pSwitch->m_pObjMove->GetCollider()->SetTag(CBoxCollider::TAG_TYPE_A);
		}
		else if (type == TYPE_GOAL_B)
		{//�S�[���p�i�^�C�vB�j
			pSwitch->m_pObjBase->SetColor(true, D3DCOLOR(0xff68c7ec));
			pSwitch->m_pObjMove->SetColor(true, D3DCOLOR(0xff68c7ec));
			pSwitch->m_pObjBase->GetCollider()->SetTag(CBoxCollider::TAG_TYPE_B);
			pSwitch->m_pObjMove->GetCollider()->SetTag(CBoxCollider::TAG_TYPE_B);
		}

		return pSwitch;
	}

	return nullptr;
}

//=================================
//���O
//=================================
void CSwitch::Exclusion(void)
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
