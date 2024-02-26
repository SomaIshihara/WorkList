//======================================================
//
//�G�t�F�N�g(�r���{�[�h)����[effectBillboard.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "effectBillboard.h"
#include "..\..\_Core\manager\manager.h"
#include "..\..\_Core\renderer\renderer.h"
#include "..\..\_Core\texture\texture.h"
#include "..\..\_Core\utility\Utility.h"

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CEffectBillboard::CEffectBillboard(const int nLife, int nPriority) : CObjectBillboard(nPriority), m_nDefLife(nLife)
{
	//�l�N���A
	m_effect.move = IS_Utility::VEC3_ZERO;
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
	//�����Ǘ�
	m_effect.nLife--;	//���炷

	//���񂾁H
	if (m_effect.nLife <= 0)
	{//���񂾁B
		Uninit();	//�I��
		return;
	}

	//�e�N���X����
	CObjectBillboard::Update();

	//�ړ�
	D3DXVECTOR3 pos = GetPos();
	pos += m_effect.move;
	SetPos(pos);

	//�A�j���[�V����
	int nIdxTexture = CObjectBillboard::GetIdxTexture();
	int nPatWidth = CManager::GetInstance()->GetTexture()->GetPatWidth(nIdxTexture);
	int nPatHeight = CManager::GetInstance()->GetTexture()->GetPatHeight(nIdxTexture);
	float fLifePercent = static_cast<float>(m_nDefLife - m_effect.nLife);
	int nPatNum = static_cast<int>(fLifePercent / (static_cast<float>(m_nDefLife) / (nPatWidth * nPatHeight)));
	int u = nPatNum % nPatWidth;
	int v = nPatNum / nPatWidth;
	CObjectBillboard::SetTex(u, v);

	//�s�����x�ݒ�
	m_effect.col.a = (float)m_effect.nLife / m_nDefLife;
	SetCol(m_effect.col);
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
	CManager::GetInstance()->GetRenderer()->SetBlendType(CRenderer::BLENDTYPE::BLENDTYPE_ADD);

	//�e�N���X����
	CObjectBillboard::Draw();

	//�u�����f�B���O��ނ�ʏ��Ԃɖ߂�
	CManager::GetInstance()->GetRenderer()->SetBlendType(CRenderer::BLENDTYPE::BLENDTYPE_NORMAL);

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
		pObjEffect->SetRot(IS_Utility::VEC3_ZERO);
		pObjEffect->SetSize(fWidth, fHeight);

		return pObjEffect;
	}
	else
	{
		return nullptr;
	}
}