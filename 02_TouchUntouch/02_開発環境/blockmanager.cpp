//======================================================
//
//�u���b�N�}�l�[�W������[blockmanager.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "blockmanager.h"
#include "manager.h"
#include "switchmanager.h"
#include "block3D.h"
#include "character.h"
#include "xmodel.h"

//�ÓI�����o�ϐ�
CXModel* CBlockManager::m_pModelNor = nullptr;
CXModel* CBlockManager::m_pModelGimOff = nullptr;

//=================================
//�R���X�g���N�^
//=================================
CBlockManager::CBlockManager(int nPriority) : CObject(nPriority)
{

}

//=================================
//�f�X�g���N�^
//=================================
CBlockManager::~CBlockManager()
{
}

//=================================
//������
//=================================
HRESULT CBlockManager::Init(void)
{
	return S_OK;
}

//=================================
//�I��
//=================================
void CBlockManager::Uninit(void)
{
	//�Ǘ��I�u�W�F�N�g�j��
	Release();
}

//=================================
//�X�V
//=================================
void CBlockManager::Update(void)
{
	CBlock3D* pBlock = CBlock3D::GetTop();

	while (pBlock != nullptr)
	{
		//�X�C�b�`�ɉ����������蔻��
		CBlock3D::TYPE type = pBlock->GetType();
		if (type == CBlock3D::TYPE_GIMMICK_01 || type == CBlock3D::TYPE_GIMMICK_02)
		{//�M�~�b�N�n
			if (m_pSwitchManager->IsPush()[type - 1] == true)
			{
				pBlock->GetCollider()->SetType(CBoxCollider::TYPE_COLLISION);
				pBlock->SetModel(m_pModelNor);
			}
			else
			{
				pBlock->GetCollider()->SetType(CBoxCollider::TYPE_NONE);
				pBlock->SetModel(m_pModelGimOff);
			}
		}
		else if (type == CBlock3D::TYPE_A)
		{//�^�C�vA�i�s���N�j
			if (m_iControllStat->GetType() == CCharacter::TYPE_A)
			{//���쒆�L�����������^�C�v
				pBlock->SetModel(m_pModelNor);
			}
			else
			{//�Ⴄ
				pBlock->SetModel(m_pModelGimOff);
			}
		}
		else if (type == CBlock3D::TYPE_B)
		{//�^�C�vB�i��F�j
			if (m_iControllStat->GetType() == CCharacter::TYPE_B)
			{//���쒆�L�����������^�C�v
				pBlock->SetModel(m_pModelNor);
			}
			else
			{//�Ⴄ
				pBlock->SetModel(m_pModelGimOff);
			}
		}
		else
		{
			pBlock->SetModel(m_pModelNor);
		}

		pBlock = pBlock->GetNext();
	}
}

//=================================
//�`��
//=================================
void CBlockManager::Draw(void)
{
	
}

//=================================
//��������
//=================================
CBlockManager* CBlockManager::Create(CSwitchManager* pSwitchManager, IControllStat* iControllStat)
{
	CBlockManager* pObjBlockManager = nullptr;

	if (pObjBlockManager == nullptr)
	{
		//�}�l�̐���
		pObjBlockManager = new CBlockManager;

		//������
		pObjBlockManager->Init();

		//�f�[�^�ݒ�
		pObjBlockManager->m_pSwitchManager = pSwitchManager;
		pObjBlockManager->m_iControllStat = iControllStat;

		//���f���ݒ�
		if (m_pModelNor == nullptr)
		{
			m_pModelNor = CXModel::Load("data\\MODEL\\block_univ.x");
		}
		if (m_pModelGimOff == nullptr)
		{
			m_pModelGimOff = CXModel::Load("data\\MODEL\\block_univ_gimoff.x");
		}

		return pObjBlockManager;
	}
	else
	{
		return nullptr;
	}
}