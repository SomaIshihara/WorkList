//======================================================
//
//����������[havenum.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"
#include "object.h"
#include "havenum.h"
#include "number.h"
#include "symbol.h"

//�ÓI�����o�ϐ�
const int CHaveNum::m_nSymbolX = 5;

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CHaveNum::CHaveNum(int nPriority) : CObject(nPriority), m_nHaveNumDigit(1)
{
	//�l�N���A
	m_nIdxTexture = -1;
	m_pos = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fOneWidth = CManager::FLOAT_ZERO;
	m_fOneHeight = CManager::FLOAT_ZERO;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h�j
//=================================
CHaveNum::CHaveNum(const int nHaveNumDigit, int nPriority) : CObject(nPriority), m_nHaveNumDigit(nHaveNumDigit)
{
	//�l�ݒ�
	m_nIdxTexture = -1;
	m_pos = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fOneWidth = CManager::FLOAT_ZERO;
	m_fOneHeight = CManager::FLOAT_ZERO;
}

//=================================
//�f�X�g���N�^
//=================================
CHaveNum::~CHaveNum()
{
}

//=================================
//������
//=================================
HRESULT CHaveNum::Init(void)
{
	//�����I�u�W�F�N�g���I�m��
	m_ppNumber = new CNumber*[m_nHaveNumDigit];

	for (int cnt = 0; cnt < m_nHaveNumDigit; cnt++)
	{//�����I�u�W�F�N�g������
		m_ppNumber[cnt] = nullptr;
	}

	//�e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();
	m_nIdxTexture = CTexture::PRELOAD_NUMBER;

	//�ł���
	return S_OK;
}

//=================================
//�I��
//=================================
void CHaveNum::Uninit(void)
{
	for (int cnt = 0; cnt < m_nHaveNumDigit; cnt++)
	{//�����I�u�W�F�N�g�I��
		if (m_ppNumber[cnt] != nullptr)
		{//���v�B���g�͂���
			m_ppNumber[cnt]->Uninit();
		}
	}

	//�����I�u�W�F�N�g�z��j��
	delete[] m_ppNumber;

	//�^�C���I�u�W�F�N�g�j��
	Release();
}

//=================================
//�X�V
//=================================
void CHaveNum::Update(void)
{
	for (int cnt = 0; cnt < m_nHaveNumDigit; cnt++)
	{//�����I�u�W�F�N�g�X�V
		if (m_ppNumber[cnt] != nullptr)
		{//���v�B���g�͂���
			//�����̍X�V����
			m_ppNumber[cnt]->Update();
		}
	}

	//��������
	CutNumber();
}

//=================================
//�`��
//=================================
void CHaveNum::Draw(void)
{
	//����ɂ���Ă���܂�
}

//=================================
//��������
//=================================
CHaveNum* CHaveNum::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight, const int nHaveNumDigit,
	const int nIconTexNum)
{
	CHaveNum* pHaveNum = nullptr;

	if (pHaveNum == nullptr)
	{
		//�������Ǘ��I�u�W�F�N�g����
		pHaveNum = new CHaveNum(nHaveNumDigit,5);

		//�^�C�}�[�Ǘ��I�u�W�F�N�g������
		pHaveNum->Init();

		//�L���I�u�W�F����
		CTexture* pTexture = CManager::GetTexture();
		int ntexNum = CTexture::PRELOAD_SYMBOL;

		//�L�����u��
		CSymbol* pSymbol;

		//�����I�u�W�F����
		int cnt;
		for (cnt = 0; cnt < nHaveNumDigit; cnt++)
		{//1���������`�e�N�X�`���ݒ�i�E����j
			//����
			pHaveNum->m_ppNumber[cnt] = CNumber::Create(pos + D3DXVECTOR3(-fOneWidth * cnt,0.0f,0.0f), rot, fOneWidth, fOneHeight);

			//������
			pHaveNum->m_ppNumber[cnt]->Init();

			//�e�N�X�`���ݒ�
			pHaveNum->m_ppNumber[cnt]->BindTexture(pHaveNum->m_nIdxTexture);
		}

		//�u�~�v
		pSymbol = CSymbol::Create(pos + D3DXVECTOR3(-fOneWidth * cnt, 0.0f, 0.0f), rot, fOneWidth, fOneHeight);
		pSymbol->Init();
		pSymbol->BindTexture(ntexNum);
		pSymbol->SetSymbol(m_nSymbolX);
		cnt++;	//�A�C�R���̔z�u�ڈ�

		//�A�C�R��
		CObject2D* pIcon = CObject2D::Create(pos + D3DXVECTOR3(-fOneWidth * cnt, 0.0f, 0.0f), CManager::VEC3_ZERO, fOneHeight, fOneHeight,PRIORITY_UI);
		pIcon->Init();
		pIcon->BindTexture(nIconTexNum);

		return pHaveNum;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//������������
//=================================
void CHaveNum::CutNumber(void)
{
	for (int cnt = 0; cnt < m_nHaveNumDigit; cnt++)
	{//�����I�u�W�F�N�g�ɓn��
		if (m_ppNumber[cnt] != nullptr)
		{//���v�B���g�͂���
			m_ppNumber[cnt]->SetNumber(m_nHaveNum, cnt);
		}
	}
}