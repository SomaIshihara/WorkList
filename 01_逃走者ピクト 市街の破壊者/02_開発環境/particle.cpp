//======================================================
//
//�p�[�e�B�N������[particle.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "particle.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "effect.h"
#include "Culc.h"

//�}�N��
#define ROT_ACCU	(100)	//�p�x�̐��x
#define SPEED_ACCU	(100)	//���x�̐��x
#define PART_EFFECT_LIFE	(20)	//�G�t�F�N�g�p�p�[�e�B�N���̎���

//****************************************
//2D�p�[�e�B�N��
//****************************************
//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CParticle2D::CParticle2D()
{
	//�p�[�e�B�N���̃N���A
	m_particle.pos = CManager::VEC3_ZERO;
	m_particle.nLife = CManager::INT_ZERO;
	m_particle.nEffeceNum = CManager::INT_ZERO;
	m_particle.fSpeedBace = CManager::FLOAT_ZERO;
	m_particle.fSpeedDegree = CManager::FLOAT_ZERO;
	m_particle.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_particle.fWidth = CManager::FLOAT_ZERO;
	m_particle.fHeight = CManager::FLOAT_ZERO;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h�j
//=================================
CParticle2D::CParticle2D(const D3DXVECTOR3 pos, const int nLife, const int nEffeceNum, const float fSpeedBace, const float fSpeedDegree,
	const D3DXCOLOR col, const float fWidth, const float fHeight)
{
	//�p�[�e�B�N���̏�����
	m_particle.pos = pos;
	m_particle.nLife = nLife;
	m_particle.nEffeceNum = nEffeceNum;
	m_particle.fSpeedBace = fSpeedBace;
	m_particle.fSpeedDegree = fSpeedDegree;
	m_particle.col = col;
	m_particle.fWidth = fWidth;
	m_particle.fHeight = fHeight;
}

//=================================
//�f�X�g���N�^
//=================================
CParticle2D::~CParticle2D()
{
}

//=================================
//������
//=================================
HRESULT CParticle2D::Init(void)
{
	//�ł���
	return S_OK;
}

//=================================
//�I��
//=================================
void CParticle2D::Uninit(void)
{
	//�p�[�e�B�N���Ǘ��I�u�W�F�N�g�j��
	Release();
}

//=================================
//�X�V
//=================================
void CParticle2D::Update(void)
{
	//�G�t�F�N�g�ǉ�����
	for (int cntEffectNum = 0; cntEffectNum < m_particle.nEffeceNum; cntEffectNum++)
	{
		//�ʒu�i�p�[�e�B�N���̈ʒu�Ɠ����j
		//�ړ���
		float fRot = (float)(rand() % (int)(ROT_ACCU * TWO_PI + 1) - (int)(D3DX_PI * ROT_ACCU)) / (float)ROT_ACCU;
		float fSpeed = (rand() % (int)(m_particle.fSpeedDegree * SPEED_ACCU)) / SPEED_ACCU + m_particle.fSpeedBace;
		D3DXVECTOR3 move;
		move.x = sinf(fRot) * fSpeed;	//X
		move.y = cosf(fRot) * fSpeed;	//Y
		move.z = 0.0f;

		//�������i�p�[�e�B�N���ɂ���j
		//�F�i�p�[�e�B�N���ɂ���j
		//�����i�}�N���j

		//�G�t�F�N�g���o��
		CEffect2D* pEffect;
		pEffect = pEffect->Create(m_particle.pos, move, m_particle.fWidth, m_particle.fHeight, m_particle.col, PART_EFFECT_LIFE);
		pEffect->Init();

		//AllEffect�̂ق���for���𔲂���
		break;
	}

	//�G�t�F�N�g�����Ǘ�
	m_particle.nLife--;

	if (m_particle.nLife <= CManager::INT_ZERO)
	{
		Uninit();
	}
}

//=================================
//��������
//=================================
CParticle2D* CParticle2D::Create(const D3DXVECTOR3 pos, const int nLife, const int nEffeceNum, const float fSpeedBace, const float fSpeedDegree,
	const D3DXCOLOR col, const float fWidth, const float fHeight)
{
	CParticle2D* pParticle = nullptr;

	if (pParticle == nullptr)
	{
		//�p�[�e�B�N���Ǘ��I�u�W�F�N�g����
		pParticle = new CParticle2D(pos, nLife, nEffeceNum, fSpeedBace, fSpeedDegree, col, fWidth, fHeight);

		//�p�[�e�B�N���Ǘ��I�u�W�F�N�g������
		pParticle->Init();

		return pParticle;
	}
	else
	{
		return nullptr;
	}
}

//****************************************
//�r���{�[�h�p�[�e�B�N��
//****************************************
//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CParticleBillboard::CParticleBillboard()
{
	//�p�[�e�B�N���̃N���A
	m_particle.pos = CManager::VEC3_ZERO;
	m_particle.nLife = CManager::INT_ZERO;
	m_particle.nEffeceNum = CManager::INT_ZERO;
	m_particle.fSpeedBace = CManager::FLOAT_ZERO;
	m_particle.fSpeedDegree = CManager::FLOAT_ZERO;
	m_particle.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_particle.fWidth = CManager::FLOAT_ZERO;
	m_particle.fHeight = CManager::FLOAT_ZERO;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h�j
//=================================
CParticleBillboard::CParticleBillboard(const D3DXVECTOR3 pos, const int nLife, const int nEffeceNum, const float fSpeedBace, const float fSpeedDegree,
	const D3DXCOLOR col, const float fWidth, const float fHeight)
{
	//�p�[�e�B�N���̏�����
	m_particle.pos = pos;
	m_particle.nLife = nLife;
	m_particle.nEffeceNum = nEffeceNum;
	m_particle.fSpeedBace = fSpeedBace;
	m_particle.fSpeedDegree = fSpeedDegree;
	m_particle.col = col;
	m_particle.fWidth = fWidth;
	m_particle.fHeight = fHeight;
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
		float fRotZ = (float)(rand() % (int)(ROT_ACCU * TWO_PI + 1) - (int)(D3DX_PI * ROT_ACCU)) / (float)ROT_ACCU;
		float fRotY = (float)(rand() % (int)(ROT_ACCU * TWO_PI + 1) - (int)(D3DX_PI * ROT_ACCU)) / (float)ROT_ACCU;
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

		//AllEffect�̂ق���for���𔲂���
		break;
	}

	//�G�t�F�N�g�����Ǘ�
	m_particle.nLife--;

	if (m_particle.nLife <= CManager::INT_ZERO)
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
		pParticle = new CParticleBillboard(pos, nLife, nEffeceNum, fSpeedBace, fSpeedDegree, col, fWidth, fHeight);

		//�p�[�e�B�N���Ǘ��I�u�W�F�N�g������
		pParticle->Init();

		return pParticle;
	}
	else
	{
		return nullptr;
	}
}