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
#include "symbol.h"

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CTimer::CTimer(int nPriority) : CObject(nPriority)
{
	//�l�N���A
	m_nIdxTexture = -1;
	m_pos = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fOneWidth = CManager::FLOAT_ZERO;
	m_fOneHeight = CManager::FLOAT_ZERO;
	m_nCounter = 0;
	m_count = COUNT_DOWN;
	m_shouldCount = false;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h�j
//=================================
CTimer::CTimer(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight, int nPriority) : CObject(nPriority)
{
	//�l�ݒ�
	m_nIdxTexture = -1;
	m_pos = pos;
	m_rot = rot;
	m_fOneWidth = fOneWidth;
	m_fOneHeight = fOneHeight;
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

	//�e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();
	m_nIdxTexture = CTexture::PRELOAD_NUMBER;

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
#ifdef _DEBUG
	//[debug]�����ݒ�
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F3) == true)
	{
		Set(2,COUNT_DOWN);	//�f�o�b�O�p�����炱��ł������
	}
#endif // DEBUG
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
	CTimer* pScore = nullptr;

	if (pScore == nullptr)
	{
		//�^�C�}�[�Ǘ��I�u�W�F�N�g����
		pScore = new CTimer;

		//�^�C�}�[�Ǘ��I�u�W�F�N�g������
		pScore->Init();

		//�L���I�u�W�F����
		CTexture* pTexture = CManager::GetTexture();
		int ntexNum = CTexture::PRELOAD_SYMBOL;

		//�L�����u��
		CSymbol* pSymbol;

		//�����I�u�W�F����
		int cnt;

		//�u�b�v
		pSymbol = CSymbol::Create(pos, rot, fOneWidth, fOneHeight);
		pSymbol->Init();
		pSymbol->BindTexture(ntexNum);
		pSymbol->SetSymbol(TYPE_SEC);

		for (cnt = 0; cnt < TIME_DIGIT; cnt++)
		{//1���������`�e�N�X�`���ݒ�i�E����j
			//����
			pScore->m_pNumber[cnt] = CNumber::Create(pos + D3DXVECTOR3(-fOneWidth * (cnt + 1),0.0f,0.0f), rot, fOneWidth, fOneHeight);

			//������
			pScore->m_pNumber[cnt]->Init();

			//�e�N�X�`���ݒ�
			pScore->m_pNumber[cnt]->BindTexture(pScore->m_nIdxTexture);
		}

		//�u�Ɓv
		pSymbol = CSymbol::Create(pos + D3DXVECTOR3(-fOneWidth * 3 - 24.0f, -9.0f, 0.0f), CManager::VEC3_ZERO, 24.0f, 36.0f);
		pSymbol->Init();
		pSymbol->BindTexture(ntexNum);
		pSymbol->SetSymbol(TYPE_TO);

		//�u���v
		pSymbol = CSymbol::Create(pos + D3DXVECTOR3(-fOneWidth * 3 - 48.0f, -9.0f, 0.0f), CManager::VEC3_ZERO, 24.0f, 36.0f);
		pSymbol->Init();
		pSymbol->BindTexture(ntexNum);
		pSymbol->SetSymbol(TYPE_A);

		return pScore;
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