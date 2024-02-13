//======================================================
//
//�X�R�A����[score.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object.h"
#include "score.h"
#include "number.h"

//�}�N��
#define SCORE_INVISIBLE	(4)	//�����������\���ɂ���

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CScore::CScore(int nPriority) : CObject(nPriority)
{
	//�l�N���A
	m_pos = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
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
		m_pNumber[cnt] = nullptr;
	}

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
		if (m_pNumber[cnt] != nullptr)
		{//���v�B���g�͂���
			m_pNumber[cnt]->Uninit();
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
		if (m_pNumber[cnt] != nullptr)
		{//���v�B���g�͂���
			//�I�u�W�F�N�g2D�̍X�V����
			m_pNumber[cnt]->Update();
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

		//�f�[�^�ݒ�
		pScore->m_pos = pos;
		pScore->m_rot = rot;

		//����6��
		for (int cnt = 0; cnt < SCORE_DIGIT; cnt++)
		{
			//����
			pScore->m_pNumber[cnt] = CNumber::Create(pos + D3DXVECTOR3(-fOneWidth * (cnt + 1), 0.0f, 0.0f), rot, fOneWidth, fOneHeight);

			//������
			pScore->m_pNumber[cnt]->Init();
		}

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
void CScore::Set(const int nScore)
{
	//�����ݒ�
	m_nScore = nScore;
}

//=================================
//�X�R�A���Z����
//=================================
void CScore::Add(const int nAdd)
{
	//�������Z
	m_nScore += nAdd;
}

//=================================
//�e�N�X�`���ݒ�
//=================================
void CScore::BindTexture(const int nIdx)
{
	for (int cnt = 0; cnt < SCORE_DIGIT; cnt++)
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
void CScore::CutNumber(void)
{
	for (int cnt = 0; cnt < SCORE_DIGIT; cnt++)
	{//�����I�u�W�F�N�g�ɓn��
		if (m_pNumber[cnt] != nullptr)
		{//���v�B���g�͂���
			m_pNumber[cnt]->SetNumber(m_nScore, cnt);
		}
	}
}