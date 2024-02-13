//======================================================
//
//���x������[level.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"
#include "object.h"
#include "level.h"
#include "number.h"
#include "symbol.h"

//�ÓI�����o�ϐ�
const int CLevel::m_nSymbolX = 5;

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CLevel::CLevel(int nPriority) : CObject(nPriority), m_nLevelDigit(1)
{
	//�l�N���A
	m_nIdxTexture = -1;
	m_pos = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fOneWidth = CManager::FLOAT_ZERO;
	m_fOneHeight = CManager::FLOAT_ZERO;
	m_nLevel = CManager::INT_ZERO;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h�j
//=================================
CLevel::CLevel(const int nLevelDigit, int nPriority) : CObject(nPriority), m_nLevelDigit(nLevelDigit)
{
	//�l�ݒ�
	m_nIdxTexture = -1;
	m_pos = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fOneWidth = CManager::FLOAT_ZERO;
	m_fOneHeight = CManager::FLOAT_ZERO;
	m_nLevel = CManager::INT_ZERO;
}

//=================================
//�f�X�g���N�^
//=================================
CLevel::~CLevel()
{
}

//=================================
//������
//=================================
HRESULT CLevel::Init(void)
{
	//�����I�u�W�F�N�g���I�m��
	m_ppNumber = new CNumber*[m_nLevelDigit];

	for (int cnt = 0; cnt < m_nLevelDigit; cnt++)
	{//�����I�u�W�F�N�g������
		m_ppNumber[cnt] = nullptr;
	}

	//�e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();
	m_nIdxTexture = CTexture::PRELOAD_NUMBER;
	m_nLevel = 1;

	//�ł���
	return S_OK;
}

//=================================
//�I��
//=================================
void CLevel::Uninit(void)
{
	for (int cnt = 0; cnt < m_nLevelDigit; cnt++)
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
void CLevel::Update(void)
{
	for (int cnt = 0; cnt < m_nLevelDigit; cnt++)
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
void CLevel::Draw(void)
{
	//����ɂ���Ă���܂�
}

//=================================
//��������
//=================================
CLevel* CLevel::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight, const int nLevelDigit,
	const int nIconTexNum)
{
	CLevel* pLevel = nullptr;

	if (pLevel == nullptr)
	{
		//���x���Ǘ��I�u�W�F�N�g����
		pLevel = new CLevel(nLevelDigit,5);

		//�^�C�}�[�Ǘ��I�u�W�F�N�g������
		pLevel->Init();

		//�L���I�u�W�F����
		CTexture* pTexture = CManager::GetTexture();
		int ntexNum = CTexture::PRELOAD_SYMBOL;

		//�L�����u��
		CSymbol* pSymbol;

		//�����I�u�W�F����
		int cnt;
		for (cnt = 0; cnt < nLevelDigit; cnt++)
		{//1���������`�e�N�X�`���ݒ�i�E����j
			//����
			pLevel->m_ppNumber[cnt] = CNumber::Create(pos + D3DXVECTOR3(-fOneWidth * cnt,0.0f,0.0f), rot, fOneWidth, fOneHeight);

			//������
			pLevel->m_ppNumber[cnt]->Init();

			//�e�N�X�`���ݒ�
			pLevel->m_ppNumber[cnt]->BindTexture(pLevel->m_nIdxTexture);
		}

		//�A�C�R��
		CObject2D* pIcon = CObject2D::Create(pos + D3DXVECTOR3(-fOneWidth * cnt, 0.0f, 0.0f), CManager::VEC3_ZERO, fOneHeight, fOneHeight,PRIORITY_UI);
		pIcon->Init();
		pIcon->BindTexture(nIconTexNum);

		return pLevel;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//������������
//=================================
void CLevel::CutNumber(void)
{
	for (int cnt = 0; cnt < m_nLevelDigit; cnt++)
	{//�����I�u�W�F�N�g�ɓn��
		if (m_ppNumber[cnt] != nullptr)
		{//���v�B���g�͂���
			m_ppNumber[cnt]->SetNumber(m_nLevel, cnt);
		}
	}
}