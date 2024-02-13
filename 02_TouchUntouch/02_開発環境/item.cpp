//======================================================
//
//�A�C�e������[item.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "item.h"
#include "xmodel.h"
#include "sound.h"

//�ÓI�����o�ϐ�
int CItem::m_nNumAll = 0;
IScoreSetter* CItem::m_pScoreInterface = nullptr;
CItem* CItem::m_pTop = nullptr;	//���X�g�̍ŏ�
CItem* CItem::m_pCur = nullptr;	//���X�g�̏I�[
const int CItem::GET_SCORE = 1000;

//************************************************
//�A�C�e���e�N���X
//************************************************
//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CItem::CItem()
{
	//�l�N���A
	m_nScore = CManager::INT_ZERO;

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
}

//=================================
//�f�X�g���N�^
//=================================
CItem::~CItem()
{
}

//=================================
//������
//=================================
HRESULT CItem::Init(void)
{
	SetType(TYPE_ITEM);
	return CObjectX::Init();
}

//=================================
//�I��
//=================================
void CItem::Uninit(void)
{
	CObjectX::Uninit();
}

//=================================
//�X�V
//=================================
void CItem::Update(void)
{
	CObjectX::Update();
}

//=================================
//�`��
//=================================
void CItem::Draw(void)
{
	CObjectX::Draw();
}

//=================================
//��������
//=================================
CItem* CItem::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CItem* pItem = NULL;

	if (pItem == NULL)
	{
		//�I�u�W�F�N�g����
		pItem = new CItem;

		//������
		pItem->Init();

		//�f�[�^�ݒ�
		pItem->m_nScore = GET_SCORE;
		pItem->SetPos(pos);
		pItem->SetRot(rot);

		//���f���ݒ�
		pItem->SetModel(CXModel::Load("data\\MODEL\\item.x"));

		//�����蔻��ݒ�
		pItem->SetCollider();
		pItem->GetCollider()->SetType(CBoxCollider::TYPE_TRIGGER);

		return pItem;
	}
	else
	{
		return NULL;
	}
}

//=================================
//�A�C�e���擾
//=================================
void CItem::Get(void)
{
	if (m_pScoreInterface != nullptr)
	{
		m_pScoreInterface->Add(m_nScore);

		//SE�Đ�
		CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_ITEM);
	}
	CItem::Uninit();
}

//=================================
//���O
//=================================
void CItem::Exclusion(void)
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

	CObjectX::Exclusion();	//�e�I�u�W�F�̏��O���s��
}