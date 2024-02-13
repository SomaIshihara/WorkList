//======================================================
//
//�X�R�A����[score.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"
#include "object.h"
#include "score.h"
#include "number.h"
#include "symbol.h"
#include "building.h"
#include "xmodel.h"

//�}�N��
#define SCORE_INVISIBLE	(4)	//�����������\���ɂ���

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CScore::CScore(int nPriority) : CObject(nPriority)
{
	//�l�N���A
	m_nIdxTextureNumber = -1;
	m_pos = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fOneWidth = CManager::FLOAT_ZERO;
	m_fOneHeight = CManager::FLOAT_ZERO;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h�j
//=================================
CScore::CScore(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight, int nPriority) : CObject(nPriority)
{
	//�l�ݒ�
	m_nIdxTextureNumber = -1;
	m_pos = pos;
	m_rot = rot;
	m_fOneWidth = fOneWidth;
	m_fOneHeight = fOneHeight;
}

//=================================
//�f�X�g���N�^
//=================================
CScore::~CScore()
{
}

//=================================
//������
//=================================
HRESULT CScore::Init(void)
{
	for (int cnt = 0; cnt < SCORE_DIGIT; cnt++)
	{//�����I�u�W�F�N�g������
		m_pNumberTenHundred[cnt] = nullptr;
	}

	//�e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();
	m_nIdxTextureNumber = CTexture::PRELOAD_NUMBER;
	m_nIdxtextureSymbol = CTexture::PRELOAD_SYMBOL;

	//�X�R�A�ݒ�
	Set(0);

	//�ł���
	return S_OK;
}

//=================================
//�I��
//=================================
void CScore::Uninit(void)
{
	for (int cnt = 0; cnt < SCORE_DIGIT; cnt++)
	{//�����I�u�W�F�N�g�I��
		if (m_pNumberTenHundred[cnt] != nullptr)
		{//���v�B���g�͂���
			m_pNumberTenHundred[cnt]->Uninit();
		}
	}

	//�X�R�A�I�u�W�F�N�g�j��
	Release();
}

//=================================
//�X�V
//=================================
void CScore::Update(void)
{
	for (int cnt = 0; cnt < SCORE_DIGIT; cnt++)
	{//�����I�u�W�F�N�g�X�V
		if (m_pNumberHMillion[cnt] != nullptr)
		{//���v�B���g�͂���
			//�I�u�W�F�N�g2D�̍X�V����
			m_pNumberHMillion[cnt]->Update();
		}
	}
	for (int cnt = 0; cnt < SCORE_DIGIT; cnt++)
	{//�����I�u�W�F�N�g�X�V
		if (m_pNumberTenHundred[cnt] != nullptr)
		{//���v�B���g�͂���
			//�I�u�W�F�N�g2D�̍X�V����
			m_pNumberTenHundred[cnt]->Update();
		}
	}

	//��������
	CutNumber();
}

//=================================
//�`��
//=================================
void CScore::Draw(void)
{
	//�`��͏���ɂ���Ă���܂�
}

//=================================
//��������
//=================================
CScore* CScore::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight)
{
	CScore* pScore = nullptr;

	if (pScore == nullptr)
	{
		//�X�R�A�Ǘ��I�u�W�F�N�g����
		pScore = new CScore;

		//�X�R�A�Ǘ��I�u�W�F�N�g������
		pScore->Init();

		//����
		CSymbol* pSymbol;

		//��
		pSymbol = CSymbol::Create(pos, rot, fOneWidth, fOneHeight);
		pSymbol->Init();
		pSymbol->BindTexture(pScore->m_nIdxtextureSymbol);
		pSymbol->SetSymbol(CScore::TYPE_TEN_HUNDRED);

		//����8��+�L��2
		for (int cnt = 0; cnt < SCORE_DIGIT; cnt++)
		{
			//����
			pScore->m_pNumberTenHundred[cnt] = pScore->m_pNumberTenHundred[cnt]->Create(pos + D3DXVECTOR3(-fOneWidth * (cnt + 1), 0.0f, 0.0f), rot, fOneWidth, fOneHeight);	//����4��+�L��2

			//������
			pScore->m_pNumberTenHundred[cnt]->Init();

			//�e�N�X�`���ݒ�
			pScore->m_pNumberTenHundred[cnt]->BindTexture(pScore->m_nIdxTextureNumber);
		}
		
		//��
		pSymbol = CSymbol::Create(pos + D3DXVECTOR3(-fOneWidth * 5, 0.0f, 0.0f), rot, fOneWidth, fOneHeight);	//����4��+�L��
		pSymbol->Init();
		pSymbol->BindTexture(pScore->m_nIdxtextureSymbol);
		pSymbol->SetSymbol(CScore::TYPE_HMILLION);

		for (int cnt = 0; cnt < SCORE_DIGIT; cnt++)
		{
			//����
			pScore->m_pNumberHMillion[cnt] = CNumber::Create(pos + D3DXVECTOR3(-fOneWidth * (cnt + 6), 0.0f, 0.0f), rot, fOneWidth, fOneHeight);

			//������
			pScore->m_pNumberHMillion[cnt]->Init();

			//�e�N�X�`���ݒ�
			pScore->m_pNumberHMillion[cnt]->BindTexture(pScore->m_nIdxTextureNumber);
		}

		//�ʉ݋L��
		pSymbol = CSymbol::Create(pos + D3DXVECTOR3(-fOneWidth * 10, 0.0f, 0.0f), rot, fOneWidth, fOneHeight);
		pSymbol->Init();
		pSymbol->BindTexture(pScore->m_nIdxtextureSymbol);
		pSymbol->SetSymbol(CScore::TYPE_PIC);

		return pScore;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//�X�R�A�ݒ菈��
//=================================
void CScore::Set(const long long nScore)
{
	//�����ݒ�
	m_nScore = nScore;
}

//=================================
//�X�R�A���Z����
//=================================
void CScore::Add(const long long nAdd)
{
	//�������Z
	m_nScore += nAdd;
}

//=================================
//������������
//=================================
void CScore::CutNumber(void)
{
	for (int cnt = 0; cnt < SCORE_DIGIT; cnt++)
	{//�����I�u�W�F�N�g�ɓn��
		if (m_pNumberTenHundred[cnt] != nullptr)
		{//���v�B���g�͂���
			m_pNumberHMillion[cnt]->SetNumber(m_nScore, cnt + SCORE_INVISIBLE + 4);
		}
	}
	for (int cnt = 0; cnt < SCORE_DIGIT; cnt++)
	{//�����I�u�W�F�N�g�ɓn��
		if (m_pNumberTenHundred[cnt] != nullptr)
		{//���v�B���g�͂���
			m_pNumberTenHundred[cnt]->SetNumber(m_nScore, cnt + SCORE_INVISIBLE);
		}
	}
}