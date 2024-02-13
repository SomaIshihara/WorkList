//======================================================
//
//�A�j���[�V��������I�u�W�F�N�g�i2D�j����[objectAnim2D.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "objectAnim2D.h"
#include "input.h"
#include <assert.h>

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CObjectAnim2D::CObjectAnim2D(int nPriority) : CObject2D(nPriority)
{
	//�l�N���A
	m_nCounterAnim = CManager::INT_ZERO;
	m_nPatternAnim = CManager::INT_ZERO;
	m_nAnimSpeed = CManager::INT_ZERO;
	m_bLoop = true;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h �ʒu����and�p�^�[���������j
//=================================
CObjectAnim2D::CObjectAnim2D(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,
	const float fWidth, const float fHeight, const int nAnimSpeed, const bool bLoop, int nPriority)
	: CObject2D(pos,rot, fWidth, fHeight, nPriority)
{
	//�l�N���A
	m_nCounterAnim = CManager::INT_ZERO;
	m_nPatternAnim = CManager::INT_ZERO;

	//�l�ݒ�
	m_nAnimSpeed = nAnimSpeed;
	m_bLoop = bLoop;
}

//=================================
//�f�X�g���N�^
//=================================
CObjectAnim2D::~CObjectAnim2D()
{
}

//=================================
//������
//=================================
HRESULT CObjectAnim2D::Init(void)
{
	//�e�N���X����
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}
	//�l������
	m_nCounterAnim = CManager::INT_ZERO;
	m_nPatternAnim = CManager::INT_ZERO;

	//�p�^�[���������擾
	CTexture* pTexture = CManager::GetTexture();
	int nPatWidth = pTexture->GetPatWidth(m_nIdxTexture);
	int nPatHeight = pTexture->GetPatHeight(m_nIdxTexture);

	//�e�N�X�`���ݒ�
	D3DXVECTOR2 tex0, tex3;
	tex0 = D3DXVECTOR2((float)(m_nPatternAnim % nPatWidth) / nPatWidth,
		(float)(m_nPatternAnim / nPatWidth) / nPatHeight);
	tex3 = D3DXVECTOR2((float)(m_nPatternAnim % nPatWidth + 1) / nPatWidth,
		(float)(m_nPatternAnim / nPatWidth + 1) / nPatHeight);

	if (FAILED(SetTex(tex0, tex3)))
	{
		return E_FAIL;
	}

	return S_OK;
}
//=================================
//�I��
//=================================
void CObjectAnim2D::Uninit(void)
{
	//�e�N���X����
	CObject2D::Uninit();
}

//=================================
//�X�V
//=================================
void CObjectAnim2D::Update(void)
{
	//�e�N���X����
	CObject2D::Update();
	
	m_nCounterAnim++;

	if ((m_nCounterAnim % m_nAnimSpeed) == 0)
	{
		m_nCounterAnim = 0;	//�J�E���^�����l�ɖ߂�

		//�p�^�[���������擾
		CTexture* pTexture = CManager::GetTexture();
		int nPatWidth = pTexture->GetPatWidth(m_nIdxTexture);
		int nPatHeight = pTexture->GetPatHeight(m_nIdxTexture);

		//�p�^�[��No�X�V
		if (m_bLoop == true)
		{//���[�v����ݒ�̏ꍇ
			m_nPatternAnim = (m_nPatternAnim + 1) % (nPatHeight * nPatWidth);
		}
		else
		{//���[�v���Ȃ��ݒ�̏ꍇ
			m_nPatternAnim++;
			if (m_nPatternAnim >= (nPatHeight * nPatWidth))
			{//�A�j���[�V�����I��
				Uninit();
				return;
			}
		}

		//�e�N�X�`���ݒ�
		D3DXVECTOR2 tex0, tex3;
		tex0 = D3DXVECTOR2((float)(m_nPatternAnim % nPatWidth) / nPatWidth,
			(float)(m_nPatternAnim / nPatWidth) / nPatHeight);
		tex3 = D3DXVECTOR2((float)(m_nPatternAnim % nPatWidth + 1) / nPatWidth,
			(float)(m_nPatternAnim / nPatWidth + 1) / nPatHeight);

		if (FAILED(SetTex(tex0, tex3)))
		{
			assert(false);
		}
	}
}

//=================================
//�`��
//=================================
void CObjectAnim2D::Draw(void)
{
	//�e�N���X����
	CObject2D::Draw();
}

//=================================
//��������
//=================================
CObjectAnim2D* CObjectAnim2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const int nAnimSpeed, const bool bLoop)
{
	CObjectAnim2D* pObjAnim2D = nullptr;

	if (pObjAnim2D == nullptr)
	{
		//�I�u�W�F�N�g�A�j���[�V����2D�̐���
		pObjAnim2D = new CObjectAnim2D(pos, rot, fWidth, fHeight, nAnimSpeed, bLoop);

		//������
		pObjAnim2D->Init();

		//�e�N�X�`�����蓖��
		pObjAnim2D->BindTexture(pObjAnim2D->m_nIdxTexture);

		return pObjAnim2D;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//�e�N�X�`���ݒ菈��
//=================================
void CObjectAnim2D::BindTexture(int nIdx)
{
	//�A�j���[�V�������̔ԍ��ݒ�
	m_nIdxTexture = nIdx;

	//�e�N�X�`�����W�Đݒ�
	CTexture* pTexture = CManager::GetTexture();
	int nPatWidth = pTexture->GetPatWidth(m_nIdxTexture);
	int nPatHeight = pTexture->GetPatHeight(m_nIdxTexture);

	//�e�N�X�`���ݒ�
	D3DXVECTOR2 tex0, tex3;
	tex0 = D3DXVECTOR2((float)(m_nPatternAnim % nPatWidth) / nPatWidth,
		(float)(m_nPatternAnim / nPatWidth) / nPatHeight);
	tex3 = D3DXVECTOR2((float)(m_nPatternAnim % nPatWidth + 1) / nPatWidth,
		(float)(m_nPatternAnim / nPatWidth + 1) / nPatHeight);

	if (FAILED(SetTex(tex0, tex3)))
	{
		assert(false);
	}

	//�e�ɂ��`����
	CObject2D::BindTexture(nIdx);
}