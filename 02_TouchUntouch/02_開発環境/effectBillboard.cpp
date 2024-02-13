//======================================================
//
//�G�t�F�N�g(�r���{�[�h)����[effectBillboard.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "effectBillboard.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CEffectBillboard::CEffectBillboard(const int nLife, int nPriority) : CObjectBillboard(nPriority), m_nDefLife(nLife)
{
	//�l�N���A
	m_nIdxTexture = -1;
	m_effect.move = CManager::VEC3_ZERO;
	m_effect.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_effect.nLife = 0;
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
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();
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
	CManager::GetInstance()->GetRenderer()->SetEnableZTest(false);

	//�A���t�@�e�X�g�L����
	CManager::GetInstance()->GetRenderer()->SetEnableAlplaTest(true);

	//�u�����f�B���O��ނ����Z�����ɕύX
	CManager::GetInstance()->GetRenderer()->SetBlendType(CRenderer::BLENDTYPE_ADD);

	//�e�N���X����
	CObjectBillboard::Draw();

	//�u�����f�B���O��ނ�ʏ��Ԃɖ߂�
	CManager::GetInstance()->GetRenderer()->SetBlendType(CRenderer::BLENDTYPE_NORMAL);

	//�A���t�@�e�X�g������
	CManager::GetInstance()->GetRenderer()->SetEnableAlplaTest(false);

	//Z�e�X�g������
	CManager::GetInstance()->GetRenderer()->SetEnableZTest(true);
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
		pObjEffect = new CEffectBillboard(nLife);

		//������
		pObjEffect->Init();

		//�f�[�^�ݒ�
		pObjEffect->m_effect.move = move;
		pObjEffect->m_effect.col = col;
		pObjEffect->m_effect.nLife = nLife;
		pObjEffect->SetPos(pos);
		pObjEffect->SetRot(CManager::VEC3_ZERO);
		pObjEffect->SetSize(fWidth, fHeight);

		//�e�N�X�`���ݒ�
		pObjEffect->BindTexture(pObjEffect->m_nIdxTexture);

		return pObjEffect;
	}
	else
	{
		return nullptr;
	}
}