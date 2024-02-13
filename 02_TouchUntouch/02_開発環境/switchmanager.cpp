//======================================================
//
//�X�C�b�`�}�l�[�W������[switchmanager.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "switchmanager.h"
#include "manager.h"

//=================================
//�R���X�g���N�^
//=================================
CSwitchManager::CSwitchManager(int nPriority) : CObject(nPriority)
{
	Reset();
}

//=================================
//�f�X�g���N�^
//=================================
CSwitchManager::~CSwitchManager()
{
}

//=================================
//������
//=================================
HRESULT CSwitchManager::Init(void)
{
	return S_OK;
}

//=================================
//�I��
//=================================
void CSwitchManager::Uninit(void)
{
	//�Ǘ��I�u�W�F�N�g�j��
	Release();
}

//=================================
//�X�V
//=================================
void CSwitchManager::Update(void)
{
	CSwitch* pSwitch = CSwitch::GetTop();
	Reset();	//��������������ĂȂ����Ƃɂ���

	while (pSwitch != nullptr)
	{
		if (pSwitch->IsPush() == true)
		{//������Ă��炻�̃O���[�v�̃X�C�b�`��on�ɂ���
			m_aPush[pSwitch->GetType()] = true;
		}

		//���������������
		pSwitch->Pull();

		pSwitch = pSwitch->GetNext();
	}
}

//=================================
//�`��
//=================================
void CSwitchManager::Draw(void)
{
	
}

//=================================
//���Z�b�g
//=================================
void CSwitchManager::Reset(void)
{
	for (int cnt = 0; cnt < CSwitch::TYPE_MAX; cnt++)
	{
		m_aPush[cnt] = false;
	}
}

//=================================
//��������
//=================================
CSwitchManager* CSwitchManager::Create(void)
{
	CSwitchManager* pObjSwitchManager = nullptr;

	if (pObjSwitchManager == nullptr)
	{
		//�}�l�̐���
		pObjSwitchManager = new CSwitchManager;

		//������
		pObjSwitchManager->Init();

		return pObjSwitchManager;
	}
	else
	{
		return nullptr;
	}
}