//======================================================
//
//�I�u�W�F�N�g����[object.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "object.h"

//�ÓI�ϐ�������
CObject* CObject::m_apTop[PRIORITY_MAX] = {};
CObject* CObject::m_apCur[PRIORITY_MAX] = {};
int CObject::m_nNumAll = 0;

//=================================
//�R���X�g���N�^
//=================================
CObject::CObject(int nPriority)
{
	if (m_apCur[nPriority] == nullptr)
	{//�Ō�������Ȃ��i���Ȃ킿�擪�����Ȃ��j
		m_apTop[nPriority] = this;	//�����擪
		m_pPrev = nullptr;				//�O��N�����Ȃ�
		m_pNext = nullptr;
	}
	else
	{//�Ō��������
		m_pPrev = m_apCur[nPriority];		//�Ō���������̑O�̃I�u�W�F
		m_apCur[nPriority]->m_pNext = this;	//�Ō���̎��̃I�u�W�F������
		m_pNext = nullptr;						//�����̎��̃I�u�W�F�͂��Ȃ�
	}
	m_nPriority = nPriority;	//�D�揇�ʓ����
	m_apCur[nPriority] = this;	//�����Ō��
	m_bDeath = false;			//�����Ă�
}

//=================================
//�f�X�g���N�^
//=================================
CObject::~CObject()
{}

//=================================
//�I�u�W�F�N�g���ׂĔj��
//=================================
void CObject::ReleaseAll(void)
{
	for (int cnt = 0; cnt < PRIORITY_MAX; cnt++)
	{
		CObject* pObject = m_apTop[cnt];	//�擪������

		while (pObject != nullptr)
		{//�Ō���܂ŉ񂵑�����
			CObject* pObjectNext = pObject->m_pNext;	//���̃I�u�W�F�ۑ�
			pObject->Uninit();		//�j��
			pObject = pObjectNext;	//��������
		}
	}

	//�E��
	Death();
}

//=================================
//�I�u�W�F�N�g�D��x�ʂ��ׂĔj��
//=================================
void CObject::ReleaseAll(const int nPriority)
{
	CObject* pObject = m_apTop[nPriority];	//�擪������

	while (pObject != nullptr)
	{//�Ō���܂ŉ񂵑�����
		CObject* pObjectNext = pObject->m_pNext;	//���̃I�u�W�F�ۑ�
		pObject->Uninit();		//�j��
		pObject = pObjectNext;	//��������
	}

	//�E��
	Death();
}

//=================================
//�I�u�W�F�N�g���ׂčX�V
//=================================
void CObject::UpdateAll(void)
{
	for (int cnt = 0; cnt < PRIORITY_MAX; cnt++)
	{
		CObject* pObject = m_apTop[cnt];	//�擪������

		while (pObject != nullptr)
		{//�Ō���܂ŉ񂵑�����
			CObject* pObjectNext = pObject->m_pNext;	//���̃I�u�W�F�ۑ�
			
			if (pObject->m_bDeath == false)
			{
				pObject->Update();		//�X�V
			}

			pObject = pObjectNext;	//��������
		}
	}

	//�E��
	Death();
}

//=================================
//�I�u�W�F�N�g���ׂĕ`��
//=================================
void CObject::DrawAll(void)
{
	CCamera* pCamera = CManager::GetInstance()->CManager::GetInstance()->GetCamera();	//�J����
	pCamera->SetCamera();

	for (int cnt = 0; cnt < PRIORITY_MAX; cnt++)
	{
		CObject* pObject = m_apTop[cnt];	//�擪������

		while (pObject != nullptr)
		{//�Ō���܂ŉ񂵑�����
			CObject* pObjectNext = pObject->m_pNext;	//���̃I�u�W�F�ۑ�
			pObject->Draw();		//�`��
			pObject = pObjectNext;	//��������
		}
	}
}

//=================================
//�I�u�W�F�N�g�j��
//=================================
void CObject::Release(void)
{
	m_bDeath = true;	//���S�t���O�������܂����B
}

//=================================
//�Ԃ��E��
//=================================
void CObject::Death(void)
{
	for (int cnt = 0; cnt < PRIORITY_MAX; cnt++)
	{
		CObject* pObject = m_apTop[cnt];	//�擪������

		while (pObject != nullptr)
		{//�Ō���܂ŉ񂵑�����
			CObject* pObjectNext = pObject->m_pNext;	//���̃I�u�W�F�ۑ�

			if (pObject->m_bDeath == true)
			{//���S�t���O�������Ă�
				if (pObject->m_pPrev != nullptr)
				{//�O�ɃI�u�W�F������
					pObject->m_pPrev->m_pNext = pObject->m_pNext;	//�O�̃I�u�W�F�̎��̃I�u�W�F�͎����̎��̃I�u�W�F
				}
				if (pObject->m_pNext != nullptr)
				{
					pObject->m_pNext->m_pPrev = pObject->m_pPrev;	//���̃I�u�W�F�̑O�̃I�u�W�F�͎����̑O�̃I�u�W�F
				}

				if (m_apCur[cnt] == pObject)
				{//�Ō���ł���
					m_apCur[cnt] = pObject->m_pPrev;	//�Ō���������̑O�̃I�u�W�F�ɂ���
				}
				if (m_apTop[cnt] == pObject)
				{
					m_apTop[cnt] = pObject->m_pNext;	//�擪�������̎��̃I�u�W�F�ɂ���
				}

				//���X�g�g�p���Ă���N���X�̏��O
				pObject->Exclusion();

				//����
				delete pObject;	//�������g�j��
				m_nNumAll--;	//�������炷
			}

			pObject = pObjectNext;	//��������
		}
	}
}