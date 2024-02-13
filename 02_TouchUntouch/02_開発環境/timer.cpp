//======================================================
//
//�^�C�}�[����[timer.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"
#include "object.h"
#include "timer.h"
#include "number.h"

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CTimer::CTimer(int nPriority) : CObject(nPriority)
{
	//�l�N���A
	m_pos = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_nCounter = 0;
	m_count = COUNT_DOWN;
	m_shouldCount = false;
}

//=================================
//�f�X�g���N�^
//=================================
CTimer::~CTimer()
{
}

//=================================
//������
//=================================
HRESULT CTimer::Init(void)
{
	for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
	{//�����I�u�W�F�N�g������
		m_pNumber[cnt] = nullptr;
	}

	//�^�C�}�[�J�E���^���Z�b�g
	m_nCounter = 0;
	m_count = COUNT_DOWN;
	m_shouldCount = false;

	//�^�C���ݒ�
	Set(0, COUNT_UP);

	//�ł���
	return S_OK;
}

//=================================
//�I��
//=================================
void CTimer::Uninit(void)
{
	for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
	{//�����I�u�W�F�N�g�I��
		if (m_pNumber[cnt] != nullptr)
		{//���v�B���g�͂���
			m_pNumber[cnt]->Uninit();
		}
	}

	//�^�C���I�u�W�F�N�g�j��
	Release();
}

//=================================
//�X�V
//=================================
void CTimer::Update(void)
{
	//�������Ȃ��
	if (m_shouldCount == true)
	{
		//�^�C�}�[�X�V
		m_nCounter++;

		if (m_nCounter >= MAX_FPS)
		{
			//�J�E���^���Z�b�g
			m_nCounter = 0;

			switch (m_count)
			{
			case COUNT_UP:
				m_nTime++;	//���Z
				if (m_nTime >= (int)pow(10, TIME_DIGIT))
				{//�����̌��E�𒴂���
					m_nTime = (int)pow(10, TIME_DIGIT) - 1;
				}
				break;

			case COUNT_DOWN:
				m_nTime--;	//���Z
				if (m_nTime < CManager::INT_ZERO)
				{//0���������
					m_nTime = CManager::INT_ZERO;
				}
				break;
			}
		}

		for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
		{//�����I�u�W�F�N�g�X�V
			if (m_pNumber[cnt] != nullptr)
			{//���v�B���g�͂���
			 //�I�u�W�F�N�g2D�̍X�V����
				m_pNumber[cnt]->Update();
			}
		}
	}

	//��������
	CutNumber();
}

//=================================
//�`��
//=================================
void CTimer::Draw(void)
{
	//����ɂ���Ă���܂�
}

//=================================
//��������
//=================================
CTimer* CTimer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight)
{
	CTimer* pTimer = nullptr;

	if (pTimer == nullptr)
	{
		//�^�C�}�[�Ǘ��I�u�W�F�N�g����
		pTimer = new CTimer;

		//�^�C�}�[�Ǘ��I�u�W�F�N�g������
		pTimer->Init();

		//�f�[�^�ݒ�
		pTimer->m_pos = pos;
		pTimer->m_rot = rot;

		for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
		{//1���������`�e�N�X�`���ݒ�i�E����j
			//����
			pTimer->m_pNumber[cnt] = CNumber::Create(pos + D3DXVECTOR3(-fOneWidth * (cnt + 1),0.0f,0.0f), rot, fOneWidth, fOneHeight);

			//������
			pTimer->m_pNumber[cnt]->Init();
		}

		return pTimer;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//�^�C���ݒ菈��
//=================================
void CTimer::Set(const int nScore,COUNT type)
{
	//�����ݒ�
	m_nTime = nScore;

	//��������
	CutNumber();
}


//=================================
//�e�N�X�`���ݒ�
//=================================
void CTimer::BindTexture(const int nIdx)
{
	for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
	{//�����I�u�W�F�N�g�ɓn��
		if (m_pNumber[cnt] != nullptr)
		{//���v�B���g�͂���
			m_pNumber[cnt]->BindTexture(nIdx);
		}
	}
}


//=================================
//������������
//=================================
void CTimer::CutNumber(void)
{
	for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
	{//�����I�u�W�F�N�g�ɓn��
		if (m_pNumber[cnt] != nullptr)
		{//���v�B���g�͂���
			m_pNumber[cnt]->SetNumber(m_nTime, cnt);
		}
	}
}