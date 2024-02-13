//======================================================
//
//�G����[enemy.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "enemy.h"
#include "input.h"
#include "bullet.h"
#include "Culc.h"

//�}�N��
#define PLAYER_SPEED	(5.0f)	//���̈ړ����x

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CEnemy::CEnemy(int nPriority) : CObjectAnim2D(nPriority)
{
	m_nIdxTexture = -1;
	m_move = CManager::VEC3_ZERO;
	m_nLife = 1;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h �ʒu����and�p�^�[���������j
//=================================
CEnemy::CEnemy(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const int nAnimSpeed, const int nLife, int nPriority)
	: CObjectAnim2D(pos, rot, fWidth, fHeight, nAnimSpeed, true, nPriority)
{
	m_nIdxTexture = -1;
	m_move = CManager::VEC3_ZERO;
	m_nLife = nLife;
}

//=================================
//�f�X�g���N�^
//=================================
CEnemy::~CEnemy()
{
}

//=================================
//������
//=================================
HRESULT CEnemy::Init(void)
{
	//�e�N���X����
	if (FAILED(CObjectAnim2D::Init()))
	{
		return E_FAIL;
	}

	//�e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Enemy_01.png", 2, 1);

	//��ސݒ�
	SetType(TYPE_ENEMY);

	return S_OK;
}

//=================================
//�I��
//=================================
void CEnemy::Uninit(void)
{
	CObjectAnim2D::Uninit();
}

//=================================
//�X�V
//=================================
void CEnemy::Update(void)
{
	//�A�j���[�V����
	CObjectAnim2D::Update();
}

//=================================
//�`��
//=================================
void CEnemy::Draw(void)
{
	CObjectAnim2D::Draw();
}

//=================================
//��������
//=================================
CEnemy* CEnemy::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const int nAnimSpeed, const int nLife)
{
	CEnemy* pEnemy = nullptr;

	if (pEnemy == nullptr)
	{
		//�G�̐���
		pEnemy = new CEnemy(pos, rot, fWidth, fHeight, nAnimSpeed, nLife);

		//������
		pEnemy->Init();

		//�e�N�X�`���ݒ�
		pEnemy->BindTexture(pEnemy->m_nIdxTexture);

		return pEnemy;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//�_���[�W�ݒ肨��ю��S���菈��
//=================================
void CEnemy::AddDamage(int nDamage)
{
	m_nLife -= nDamage;	//�_���[�W�t�^

	//���S����
	if (m_nLife <= DEATH_LIFE)
	{
		Uninit();	//�I������
	}
}