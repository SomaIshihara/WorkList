//======================================================
//
//�G�t�F�N�g����[effect.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "effect.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//****************************************
//2D�G�t�F�N�g
//****************************************
//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CEffect2D::CEffect2D(int nPriority) : CObject2D(nPriority), m_nDefLife(0)
{
	//�l�N���A
	m_nIdxTexture = -1;
	m_effect.move = CManager::VEC3_ZERO;
	m_effect.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_effect.nLife = 0;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h�j
//=================================
CEffect2D::CEffect2D(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fWidth, const float fHeight,
	const D3DXCOLOR col, const int nLife, int nPriority) : CObject2D(pos, CManager::VEC3_ZERO, fWidth, fHeight, nPriority), m_nDefLife(nLife)
{
	//�l�ݒ�
	m_nIdxTexture = -1;
	m_effect.move = move;
	m_effect.col = col;
	m_effect.nLife = nLife;
}

//=================================
//�f�X�g���N�^
//=================================
CEffect2D::~CEffect2D()
{
}

//=================================
//������
//=================================
HRESULT CEffect2D::Init(void)
{
	//�e�N���X����
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	//�e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\effect000.jpg");

	return S_OK;
}

//=================================
//�I��
//=================================
void CEffect2D::Uninit(void)
{
	//�e�N���X����
	CObject2D::Uninit();
}

//=================================
//�X�V
//=================================
void CEffect2D::Update(void)
{
	//�e�N���X����
	CObject2D::Update();

	//�ړ�
	D3DXVECTOR3 pos = GetPos();
	pos += m_effect.move;
	SetPos(pos);

	//�����Ǘ�
	m_effect.nLife--;	//���炷

	//�s�����x�ݒ�
	m_effect.col.a = (float)m_effect.nLife / m_nDefLife;
	SetCol(m_effect.col);

	if (m_effect.nLife <= 0)
	{//����
		Uninit();	//�I��
	}
}

//=================================
//�`��
//=================================
void CEffect2D::Draw(void)
{
	//Z�e�X�g������
	CManager::GetRenderer()->SetEnableZTest(false);

	//�A���t�@�e�X�g�L����
	CManager::GetRenderer()->SetEnableAlplaTest(true);

	//�u�����f�B���O��ނ����Z�����ɕύX
	CManager::GetRenderer()->SetBlendType(CRenderer::BLENDTYPE_ADD);

	//�e�N���X����
	CObject2D::Draw();

	//�u�����f�B���O��ނ�ʏ��Ԃɖ߂�
	CManager::GetRenderer()->SetBlendType(CRenderer::BLENDTYPE_NORMAL);

	//�A���t�@�e�X�g������
	CManager::GetRenderer()->SetEnableAlplaTest(false);

	//Z�e�X�g������
	CManager::GetRenderer()->SetEnableZTest(true);
}

//=================================
//��������
//=================================
CEffect2D* CEffect2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fWidth, const float fHeight,
	const D3DXCOLOR col, const int nLife)
{
	CEffect2D* pObjEffect = nullptr;

	if (pObjEffect == nullptr)
	{
		//�w�i�̐���
		pObjEffect = new CEffect2D(pos, move, fWidth, fHeight, col, nLife);

		//������
		pObjEffect->Init();

		//�e�N�X�`���ݒ�
		pObjEffect->BindTexture(pObjEffect->m_nIdxTexture);

		return pObjEffect;
	}
	else
	{
		return nullptr;
	}
}

//****************************************
//�r���{�[�h�G�t�F�N�g
//****************************************
//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CEffectBillboard::CEffectBillboard(int nPriority) : CObjectBillboard(nPriority), m_nDefLife(0)
{
	//�l�N���A
	m_nIdxTexture = -1;
	m_effect.move = CManager::VEC3_ZERO;
	m_effect.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_effect.nLife = 0;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h�j
//=================================
CEffectBillboard::CEffectBillboard(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fWidth, const float fHeight,
	const D3DXCOLOR col, const int nLife, int nPriority) : CObjectBillboard(pos, CManager::VEC3_ZERO, fWidth, fHeight, nPriority), m_nDefLife(nLife)
{
	//�l�ݒ�
	m_nIdxTexture = -1;
	m_effect.move = move;
	m_effect.col = col;
	m_effect.nLife = nLife;
}

//=================================
//�f�X�g���N�^
//=================================
CEffectBillboard::~CEffectBillboard()
{
}

//=================================
//������
//=================================
HRESULT CEffectBillboard::Init(void)
{
	//�e�N���X����
	if (FAILED(CObjectBillboard::Init()))
	{
		return E_FAIL;
	}

	//�e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\effect000.jpg");

	return S_OK;
}

//=================================
//�I��
//=================================
void CEffectBillboard::Uninit(void)
{
	//�e�N���X����
	CObjectBillboard::Uninit();
}

//=================================
//�X�V
//=================================
void CEffectBillboard::Update(void)
{
	//�e�N���X����
	CObjectBillboard::Update();

	//�ړ�
	D3DXVECTOR3 pos = GetPos();
	pos += m_effect.move;
	SetPos(pos);

	//�����Ǘ�
	m_effect.nLife--;	//���炷

	//�s�����x�ݒ�
	m_effect.col.a = (float)m_effect.nLife / m_nDefLife;
	SetCol(m_effect.col);

	if (m_effect.nLife <= 0)
	{//����
		Uninit();	//�I��
	}
}

//=================================
//�`��
//=================================
void CEffectBillboard::Draw(void)
{
	//Z�e�X�g������
	CManager::GetRenderer()->SetEnableZTest(false);

	//�A���t�@�e�X�g�L����
	CManager::GetRenderer()->SetEnableAlplaTest(true);

	//�u�����f�B���O��ނ����Z�����ɕύX
	CManager::GetRenderer()->SetBlendType(CRenderer::BLENDTYPE_ADD);

	//�e�N���X����
	CObjectBillboard::Draw();

	//�u�����f�B���O��ނ�ʏ��Ԃɖ߂�
	CManager::GetRenderer()->SetBlendType(CRenderer::BLENDTYPE_NORMAL);

	//�A���t�@�e�X�g������
	CManager::GetRenderer()->SetEnableAlplaTest(false);

	//Z�e�X�g������
	CManager::GetRenderer()->SetEnableZTest(true);
}

//=================================
//��������
//=================================
CEffectBillboard* CEffectBillboard::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fWidth, const float fHeight,
	const D3DXCOLOR col, const int nLife)
{
	CEffectBillboard* pObjEffect = nullptr;

	if (pObjEffect == nullptr)
	{
		//�w�i�̐���
		pObjEffect = new CEffectBillboard(pos, move, fWidth, fHeight, col, nLife);

		//������
		pObjEffect->Init();

		//�e�N�X�`���ݒ�
		pObjEffect->BindTexture(pObjEffect->m_nIdxTexture);

		return pObjEffect;
	}
	else
	{
		return nullptr;
	}
}