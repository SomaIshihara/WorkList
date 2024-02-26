//======================================================
//
//�^�C�}�[����[timer.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "timer.h"
#include "..\..\..\main.h"
#include "..\..\_Core\manager\manager.h"
#include "..\..\_Core\renderer\renderer.h"
#include "..\..\_Core\texture\texture.h"
#include "..\..\_Core\input\input.h"
#include "..\..\_Core\_object\object_empty\object.h"
#include "..\..\_Expansion\number\number.h"
#include"..\..\_Core\utility\Utility.h"

//******************************************************************
// ��{�^�C�}�[�N���X
//******************************************************************
//=================================
//�R���X�g���N�^
//=================================
CTimer::CTimer(int nPriority) : CObject(nPriority)
{
	//�l�N���A
	m_pos = IS_Utility::VEC3_ZERO;
	m_rot = IS_Utility::VEC3_ZERO;
	m_nCounter = 0;
	m_count = COUNT::COUNT_DOWN;
	m_shouldCount = false;
	m_nTime = 0;
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
	//�^�C�}�[�J�E���^���Z�b�g
	m_nCounter = 0;
	m_count = COUNT::COUNT_DOWN;
	m_shouldCount = false;

	//�^�C���ݒ�
	Set(0, COUNT::COUNT_UP);

	//�ł���
	return S_OK;
}

//=================================
//�I��
//=================================
void CTimer::Uninit(void)
{
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
		switch (m_count)
		{
		case COUNT::COUNT_UP:
			//�^�C�}�[�X�V
			m_nCounter++;

			if (m_nCounter >= MAX_FPS)
			{
				//�J�E���^���Z�b�g
				m_nCounter = 0;

				m_nTime++;	//���Z
				if (m_nTime >= (int)pow(10, TIME_DIGIT))
				{//�����̌��E�𒴂���
					m_nTime = (int)pow(10, TIME_DIGIT) - 1;
					m_shouldCount = false;
				}
			}
			break;

		case COUNT::COUNT_DOWN:
			//�^�C�}�[�X�V
			m_nCounter--;

			if (m_nCounter <= 0)
			{
				//�J�E���^���Z�b�g
				m_nCounter = MAX_FPS;

				m_nTime--;	//���Z
				if (m_nTime < 0)
				{//0���������
					m_nTime = 0;
					m_shouldCount = false;
				}
			}
			break;
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
//�^�C���ݒ菈��
//=================================
void CTimer::Set(const int nScore,COUNT type)
{
	//�����ݒ�
	m_nTime = nScore;
	m_count = type;
	m_nCounter = 0;

	//��������
	CutNumber();
}

//******************************************************************
// �b�^�C�}�[�N���X
//******************************************************************
//=================================
//�R���X�g���N�^
//=================================
CTimerSecond::CTimerSecond()
{
	m_fWidth = 0.0f;
}

//=================================
//�f�X�g���N�^
//=================================
CTimerSecond::~CTimerSecond()
{
}

//=================================
//������
//=================================
HRESULT CTimerSecond::Init(void)
{
	for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
	{//�����I�u�W�F�N�g������
		m_pNumber[cnt] = nullptr;
	}

	return CTimer::Init();
}

//=================================
//�I��
//=================================
void CTimerSecond::Uninit(void)
{
	for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
	{//�����I�u�W�F�N�g�I��
		if (m_pNumber[cnt] != nullptr)
		{//���v�B���g�͂���
			m_pNumber[cnt]->Uninit();
		}
	}

	CTimer::Uninit();
}

//=================================
//�X�V
//=================================
void CTimerSecond::Update(void)
{
	CTimer::Update();

	for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
	{//�����I�u�W�F�N�g�X�V
		if (m_pNumber[cnt] != nullptr)
		{//���v�B���g�͂���
		 //�I�u�W�F�N�g2D�̍X�V����
			m_pNumber[cnt]->Update();
		}
	}
}

//=================================
//�`��
//=================================
void CTimerSecond::Draw(void)
{
	CTimer::Draw();
}

//=================================
//��������
//=================================
CTimerSecond* CTimerSecond::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight)
{
	CTimerSecond* pTimer = nullptr;

	if (pTimer == nullptr)
	{
		//�^�C�}�[�Ǘ��I�u�W�F�N�g����
		pTimer = new CTimerSecond;

		//�^�C�}�[�Ǘ��I�u�W�F�N�g������
		pTimer->Init();

		//��������
		for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
		{//1���������`�e�N�X�`���ݒ�i�E����j
			//����
			pTimer->m_pNumber[cnt] = CNumber::Create(pos + D3DXVECTOR3(-fOneWidth * (cnt + 1), 0.0f, 0.0f), rot, fOneWidth, fOneHeight);

			//������
			pTimer->m_pNumber[cnt]->Init();
		}

		//�f�[�^�ݒ�
		pTimer->SetPos(pos);
		pTimer->SetRot(rot);
		pTimer->m_fWidth = fOneWidth;

		return pTimer;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//�Ĕz�u
//=================================
void CTimerSecond::Replace(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = CTimer::GetRot();
	float fOneWidth = m_pNumber[0]->GetWidth();
	float fOneHeight = m_pNumber[0]->GetHeight();

	for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
	{//1���������`�e�N�X�`���ݒ�i�E����j
		//����
		m_pNumber[cnt]->SetPos(pos + D3DXVECTOR3(-fOneWidth * (cnt + 1), 0.0f, 0.0f));
	}
}

//=================================
//�e�N�X�`���ݒ�
//=================================
void CTimerSecond::BindTexture(const int nIdx)
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
void CTimerSecond::CutNumber(void)
{
	int nTime = CTimer::GetTime();
	for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
	{//�����I�u�W�F�N�g�ɓn��
		if (m_pNumber[cnt] != nullptr)
		{//���v�B���g�͂���
			m_pNumber[cnt]->SetNumber(nTime, cnt);
		}
	}
}

//******************************************************************
// ���b�~���b�^�C�}�[�N���X
//******************************************************************
//=================================
//�R���X�g���N�^
//=================================
CTimerMSmS::CTimerMSmS()
{
	m_fWidth = 0.0f;

}

//=================================
//�f�X�g���N�^
//=================================
CTimerMSmS::~CTimerMSmS()
{
}

//=================================
//������
//=================================
HRESULT CTimerMSmS::Init(void)
{
	//�I�u�W�F�N�g�������i�ʂ�ۓ����j
	for (int cnt = 0; cnt < 2; cnt++)
	{
		m_pMinute[cnt] = nullptr;
		m_pSecond[cnt] = nullptr;
		m_pMilliSecond[cnt] = nullptr;
		m_pSymbol[cnt] = nullptr;
	}

	return CTimer::Init();
}

//=================================
//�I��
//=================================
void CTimerMSmS::Uninit(void)
{
	//�I�u�W�F�N�g�I��
	for (int cnt = 0; cnt < 2; cnt++)
	{
		if (m_pMinute[cnt] != nullptr)
		{
			m_pMinute[cnt]->Uninit();
			m_pMinute[cnt] = nullptr;
		}
		if (m_pSecond[cnt] != nullptr)
		{
			m_pSecond[cnt]->Uninit();
			m_pSecond[cnt] = nullptr;
		}
		if (m_pMilliSecond[cnt] != nullptr)
		{
			m_pMilliSecond[cnt]->Uninit();
			m_pMilliSecond[cnt] = nullptr;
		}
		if (m_pSymbol[cnt] != nullptr)
		{
			m_pSymbol[cnt]->Uninit();
			m_pSymbol[cnt] = nullptr;
		}
	}

	CTimer::Uninit();
}

//=================================
//�X�V
//=================================
void CTimerMSmS::Update(void)
{
	CTimer::Update();

	//�I�u�W�F�N�g�X�V
	for (int cnt = 0; cnt < 2; cnt++)
	{
		if (m_pMinute[cnt] != nullptr)
		{
			m_pMinute[cnt]->Update();
		}
		if (m_pSecond[cnt] != nullptr)
		{
			m_pSecond[cnt]->Update();
		}
		if (m_pMilliSecond[cnt] != nullptr)
		{
			m_pMilliSecond[cnt]->Update();
		}
		if (m_pSymbol[cnt] != nullptr)
		{
			m_pSymbol[cnt]->Update();
		}
	}
}

//=================================
//�`��
//=================================
void CTimerMSmS::Draw(void)
{
	CTimer::Draw();
}

//=================================
//��������
//=================================
CTimerMSmS* CTimerMSmS::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight)
{
	CTimerMSmS* pTimer = nullptr;

	if (pTimer == nullptr)
	{
		//�^�C�}�[�Ǘ��I�u�W�F�N�g����
		pTimer = new CTimerMSmS;

		//�^�C�}�[�Ǘ��I�u�W�F�N�g������
		pTimer->Init();

		//�I�u�W�F�N�g����
		float fAllWidth = fOneWidth * 7;	//����:����(1)�~6,�L��(0.5)�~2
		float fPlacePos = -(fAllWidth * 0.5f);	//�����ʒu
		//��
		for (int cnt = 0; cnt < 2; cnt++)
		{
			pTimer->m_pMinute[cnt] = CNumber::Create(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.5f) + (fOneWidth * cnt), 0.0f, 0.0f),
				rot, fOneWidth, fOneHeight);
			pTimer->m_pMinute[cnt]->Init();
		}
		//�L��0
		fPlacePos += fOneWidth * 2;
		pTimer->m_pSymbol[0] = CNumber::Create(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.25f), 0.0f, 0.0f),
			rot, fOneWidth * 0.5f, fOneHeight);
		pTimer->m_pSymbol[0]->Init();

		//�b
		fPlacePos += fOneWidth * 0.5f;
		for (int cnt = 0; cnt < 2; cnt++)
		{
			pTimer->m_pSecond[cnt] = CNumber::Create(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.5f) + (fOneWidth * cnt), 0.0f, 0.0f),
				rot, fOneWidth, fOneHeight);
			pTimer->m_pSecond[cnt]->Init();
		}
		//�L��1
		fPlacePos += fOneWidth * 2;
		pTimer->m_pSymbol[1] = CNumber::Create(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.25f), 0.0f, 0.0f),
			rot, fOneWidth * 0.5f, fOneHeight);
		pTimer->m_pSymbol[1]->Init();
		

		//�~���b
		fPlacePos += fOneWidth * 0.5f;
		for (int cnt = 0; cnt < 2; cnt++)
		{
			pTimer->m_pMilliSecond[cnt] = CNumber::Create(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.5f) + (fOneWidth * cnt), 0.0f, 0.0f),
				rot, fOneWidth, fOneHeight);
			pTimer->m_pMilliSecond[cnt]->Init();
		}

		//�f�[�^�ݒ�
		pTimer->SetPos(pos);
		pTimer->SetRot(rot);
		pTimer->m_fWidth = fOneWidth;

		return pTimer;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//�~���b�܂߂����Ԑݒ�
//=================================
void CTimerMSmS::Set(const int nTime, const int nCounter, COUNT type)
{
	//�����ݒ�
	CTimer::Set(nTime, type);
	CTimer::SetCounter(nCounter);
	CutNumber();
}

//=================================
//�e�N�X�`���ݒ�i�����j
//=================================
void CTimerMSmS::BindTexture(const int nIdx)
{
	for (int cnt = 0; cnt < 2; cnt++)
	{
		if (m_pMinute[cnt] != nullptr)
		{
			m_pMinute[cnt]->BindTexture(CTexture::PRELOAD::PRELOAD_04_TIMER_NUMBER);
			m_pMinute[cnt]->SetNumber(0, 0);
		}
		if (m_pSecond[cnt] != nullptr)
		{
			m_pSecond[cnt]->BindTexture(CTexture::PRELOAD::PRELOAD_04_TIMER_NUMBER);
			m_pSecond[cnt]->SetNumber(0, 0);
		}
		if (m_pMilliSecond[cnt] != nullptr)
		{
			m_pMilliSecond[cnt]->BindTexture(CTexture::PRELOAD::PRELOAD_04_TIMER_NUMBER);
			m_pMilliSecond[cnt]->SetNumber(0, 0);
		}
	}
}

//=================================
//�e�N�X�`���ݒ�i�L���j
//=================================
void CTimerMSmS::BindSymbolTexture(const int nIdx)
{
	for (int cnt = 0; cnt < 2; cnt++)
	{
		if (m_pSymbol[cnt] != nullptr)
		{
			m_pSymbol[cnt]->BindTexture(CTexture::PRELOAD::PRELOAD_05_TIMER_SYMBOL);
			m_pSymbol[cnt]->SetTex(D3DXVECTOR2(0.5f * cnt, 0.0f), D3DXVECTOR2(0.5f * (cnt + 1), 1.0f));
		}
	}
}

//=================================
//������������
//=================================
void CTimerMSmS::CutNumber(void)
{
	int nSecond = CTimer::GetTime();		//���ׂĕb�ɒ��������̂����炩���ߓ����
	int nCounter = CTimer::GetCounter();	//�~���b�ɒ����O�̂��̂�����
	int nMinute = nSecond / 60;				//�b�𕪂ɕϊ�
	nSecond %= 60;							//���ɕϊ������������炷
	int nMilliSecond = (nCounter * 100 / MAX_FPS);

	for (int cnt = 0; cnt < 2; cnt++)
	{
		if (m_pMinute[cnt] != nullptr)
		{
			m_pMinute[cnt]->SetNumber(nMinute, 1 - cnt);
		}
		if (m_pSecond[cnt] != nullptr)
		{
			m_pSecond[cnt]->SetNumber(nSecond, 1 - cnt);
		}
		if (m_pMilliSecond[cnt] != nullptr)
		{
			m_pMilliSecond[cnt]->SetNumber(nMilliSecond, 1 - cnt);
		}
	}
}

//=================================
//�Ĕz�u
//=================================
void CTimerMSmS::Replace(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = CTimer::GetRot();
	float fOneWidth = m_pMinute[0]->GetWidth();
	float fOneHeight = m_pMinute[0]->GetHeight();
	float fAllWidth = fOneWidth * 7;	//����:����(1)�~6,�L��(0.5)�~2
	float fPlacePos = -(fAllWidth * 0.5f);	//�����ʒu
	//��
	for (int cnt = 0; cnt < 2; cnt++)
	{
		m_pMinute[cnt]->SetPos(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.5f) + (fOneWidth * cnt), 0.0f, 0.0f));
	}
	//�L��0
	fPlacePos += fOneWidth * 2;
	m_pSymbol[0]->SetPos(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.25f), 0.0f, 0.0f));

	//�b
	fPlacePos += fOneWidth * 0.5f;
	for (int cnt = 0; cnt < 2; cnt++)
	{
		m_pSecond[cnt]->SetPos(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.5f) + (fOneWidth * cnt), 0.0f, 0.0f));
	}
	//�L��1
	fPlacePos += fOneWidth * 2;
	m_pSymbol[1]->SetPos(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.25f), 0.0f, 0.0f));

	//�~���b
	fPlacePos += fOneWidth * 0.5f;
	for (int cnt = 0; cnt < 2; cnt++)
	{
		m_pMilliSecond[cnt]->SetPos(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.5f) + (fOneWidth * cnt), 0.0f, 0.0f));
	}
}