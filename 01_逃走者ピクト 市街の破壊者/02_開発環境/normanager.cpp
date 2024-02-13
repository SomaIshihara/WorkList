//======================================================
//
//��ʐl�}�l�[�W������[normanager.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "normanager.h"
#include "manager.h"
#include "point.h"
#include "picto.h"

//�ÓI�����o�ϐ�
const int CNorManager::RESEARCH_NUM = 5;
const float CNorManager::NOBUILDING_TIME_PERCE = 0.5f;

//=================================
//�R���X�g���N�^
//=================================
CNorManager::CNorManager(int nPriority) : CObject(nPriority)
{
	m_maxPicto = CManager::INT_ZERO;
	m_spawnTime = CManager::INT_ZERO;
	m_counter = CManager::INT_ZERO;
}

//=================================
//�f�X�g���N�^
//=================================
CNorManager::~CNorManager()
{
}

//=================================
//������
//=================================
HRESULT CNorManager::Init(void)
{
	return S_OK;
}

//=================================
//�I��
//=================================
void CNorManager::Uninit(void)
{
	//�Ǘ��I�u�W�F�N�g�j��
	Release();
}

//=================================
//�X�V
//=================================
void CNorManager::Update(void)
{
	if (CPictoNormal::GetNumAll() < m_maxPicto)
	{//��ʐl�̐l��������ȉ�
		m_counter++;	//�J�E���g���₷
		if (m_counter >= m_spawnTime)
		{//�����̎���
			int spawnPoint = rand() % CPoint::GetNumAll();	//�K���Ɍ��߂�
			CPoint* pPoint = CPoint::GetTop();				//�擪�擾

			//�K���Ɍ��߂������̉񐔕���
			for (int cnt = 0; cnt < spawnPoint; cnt++)
			{
				pPoint = pPoint->GetNext();	//�������
			}

			//���߂��|�C���g���畦����
			CPictoNormal::Create(pPoint->GetPos());

			//���Z�b�g
			m_counter = 0;
		}
	}
}

//=================================
//�`��
//=================================
void CNorManager::Draw(void)
{
	
}

//=================================
//��������
//=================================
CNorManager* CNorManager::Create(void)
{
	CNorManager* pObjNorManager = nullptr;

	if (pObjNorManager == nullptr)
	{
		//�w�i�̐���
		pObjNorManager = new CNorManager;

		//������
		pObjNorManager->Init();

		return pObjNorManager;
	}
	else
	{
		return nullptr;
	}
}