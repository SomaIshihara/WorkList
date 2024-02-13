//======================================================
//
//�S�[������[goal.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "goal.h"
#include "manager.h"
#include "objectX.h"
#include "xmodel.h"
#include "debugproc.h"
#include "switch.h"

//�ÓI�����o�ϐ�
CGoal* CGoal::m_pTop = nullptr;
CGoal* CGoal::m_pCur = nullptr;
int CGoal::m_nNumAll = 0;

//=================================
//�R���X�g���N�^
//=================================
CGoal::CGoal(int nPriority) : CObject(nPriority)
{
	m_aSwitch[0] = nullptr;
	m_aSwitch[1] = nullptr;
	m_pBase = nullptr;
	m_pos = CManager::VEC3_ZERO;
	m_move = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fWidth = CManager::FLT_ZERO;
	m_fHeight = CManager::FLT_ZERO;
	m_fDepth = CManager::FLT_ZERO;
	m_bGoal = false;

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
CGoal::~CGoal()
{
}

//=================================
//������
//=================================
HRESULT CGoal::Init(void)
{
	SetType(TYPE_GOAL);
	return S_OK;
}

//=================================
//�I��
//=================================
void CGoal::Uninit(void)
{
	Release();
}

//=================================
//�X�V
//=================================
void CGoal::Update(void)
{
	m_bGoal = true;	//�S�[�����Ă邩������Ȃ��̂ł�������true
	for (int cnt = 0; cnt < CCharacter::TYPE_MAX; cnt++)
	{
		if (m_aSwitch[cnt] != nullptr && m_aSwitch[cnt]->IsPush() == false)
		{
			m_bGoal = false;	//�S�[�����ĂȂ���Bfalse�ɂ���
			break;
		}
	}
}

//=================================
//�`��
//=================================
void CGoal::Draw(void)
{
	//�K�v�Ȃ�
}

//=================================
//����
//=================================
CGoal* CGoal::Create(const D3DXVECTOR3 pos)
{
	CGoal* pGoal = nullptr;

	if (pGoal == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pGoal = new CGoal;

		//������
		pGoal->Init();

		//�f�[�^�ݒ�
		pGoal->m_pos = pos;

		//�y�䐶��
		pGoal->m_pBase = CObjectX::Create(pGoal->m_pos, CManager::VEC3_ZERO, CXModel::Load("data\\MODEL\\Goal_Base.x"));

		//�X�C�b�`����
		pGoal->m_aSwitch[CCharacter::TYPE_A] = CSwitch::Create(pGoal->m_pos + D3DXVECTOR3(-55.0f, 10.0f, 0.0f), CSwitch::TYPE_GOAL_A);
		pGoal->m_aSwitch[CCharacter::TYPE_B] = CSwitch::Create(pGoal->m_pos + D3DXVECTOR3(55.0f,10.0f,0.0f), CSwitch::TYPE_GOAL_B);

		return pGoal;
	}

	return nullptr;
}

//=================================
//���O
//=================================
void CGoal::Exclusion(void)
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
}
