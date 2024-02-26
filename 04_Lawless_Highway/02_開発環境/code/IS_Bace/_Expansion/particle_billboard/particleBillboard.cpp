//======================================================
//
//�p�[�e�B�N������[particle.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "particleBillboard.h"
#include "..\effect_billboard\effectBillboard.h"
#include "..\..\_Core\manager\manager.h"
#include "..\..\_Core\renderer\renderer.h"
#include "..\..\_Core\texture\texture.h"
#include "..\..\_Core\utility\Utility.h"

//�}�N��
#define ROT_ACCU	(100)	//�p�x�̐��x
#define SPEED_ACCU	(100)	//���x�̐��x
#define PART_EFFECT_LIFE	(8)	//�G�t�F�N�g�p�p�[�e�B�N���̎���

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CParticleBillboard::CParticleBillboard()
{
	//�p�[�e�B�N���̃N���A
	m_particle.pos = IS_Utility::VEC3_ZERO;
	m_particle.nLife = 0;
	m_particle.nEffeceNum = 0;
	m_particle.fSpeedBace = 0.0f;
	m_particle.fSpeedDegree = 0.0f;
	m_particle.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_particle.fWidth = 0.0f;
	m_particle.fHeight = 0.0f;
	m_nIdxTexture = -1;
}

//=================================
//�f�X�g���N�^
//=================================
CParticleBillboard::~CParticleBillboard()
{
}

//=================================
//������
//=================================
HRESULT CParticleBillboard::Init(void)
{
	//�ł���
	return S_OK;
}

//=================================
//�I��
//=================================
void CParticleBillboard::Uninit(void)
{
	//�p�[�e�B�N���Ǘ��I�u�W�F�N�g�j��
	Release();
}

//=================================
//�X�V
//=================================
void CParticleBillboard::Update(void)
{
	//�G�t�F�N�g�ǉ�����
	for (int cntEffectNum = 0; cntEffectNum < m_particle.nEffeceNum; cntEffectNum++)
	{
		//�ʒu�i�p�[�e�B�N���̈ʒu�Ɠ����j
		//�ړ���
		float fRotZ = (float)(rand() % (int)(ROT_ACCU * IS_Utility::TWO_PI + 1) - (int)(D3DX_PI * ROT_ACCU)) / (float)ROT_ACCU;
		float fRotY = (float)(rand() % (int)(ROT_ACCU * IS_Utility::TWO_PI + 1) - (int)(D3DX_PI * ROT_ACCU)) / (float)ROT_ACCU;
		float fSpeed = (rand() % (int)(m_particle.fSpeedDegree * SPEED_ACCU)) / SPEED_ACCU + m_particle.fSpeedBace;
		D3DXVECTOR3 move;
		move.x = sinf(fRotZ) * cosf(fRotY) * fSpeed;	//X
		move.y = cosf(fRotZ) * fSpeed;					//Y
		move.z = cosf(fRotZ) * cosf(fRotY) * fSpeed;	//Z

		//�������i�p�[�e�B�N���ɂ���j
		//�F�i�p�[�e�B�N���ɂ���j
		//�����i�}�N���j

		//�G�t�F�N�g���o��
		CEffectBillboard* pEffect;
		pEffect = pEffect->Create(m_particle.pos, move, m_particle.fWidth, m_particle.fHeight, m_particle.col, PART_EFFECT_LIFE);
		pEffect->Init();
		pEffect->BindTexture(m_nIdxTexture);
	}

	//�G�t�F�N�g�����Ǘ�
	m_particle.nLife--;

	if (m_particle.nLife <= 0)
	{
		Uninit();
	}
}

//=================================
//��������
//=================================
CParticleBillboard* CParticleBillboard::Create(const D3DXVECTOR3 pos, const int nLife, const int nEffeceNum, const float fSpeedBace, const float fSpeedDegree,
	const D3DXCOLOR col, const float fWidth, const float fHeight)
{
	CParticleBillboard* pParticle = nullptr;

	if (pParticle == nullptr)
	{
		//�p�[�e�B�N���Ǘ��I�u�W�F�N�g����
		pParticle = new CParticleBillboard;

		//�p�[�e�B�N���Ǘ��I�u�W�F�N�g������
		pParticle->Init();

		//�f�[�^�ݒ�
		pParticle->m_particle.pos = pos;
		pParticle->m_particle.nLife = nLife;
		pParticle->m_particle.nEffeceNum = nEffeceNum;
		pParticle->m_particle.fSpeedBace = fSpeedBace;
		pParticle->m_particle.fSpeedDegree = fSpeedDegree;
		pParticle->m_particle.col = col;
		pParticle->m_particle.fWidth = fWidth;
		pParticle->m_particle.fHeight = fHeight;

		return pParticle;
	}
	else
	{
		return nullptr;
	}
}