//======================================================
//
//�L������[symbol.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object2D.h"
#include "symbol.h"
#include "input.h"
#include <assert.h>

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CSymbol::CSymbol(int nPriority) :CObject2D(nPriority)
{
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h �ʒu����and�������j
//=================================
CSymbol::CSymbol(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, int nPriority)
	: CObject2D(pos,rot, fWidth, fHeight, nPriority)
{
}

//=================================
//�f�X�g���N�^
//=================================
CSymbol::~CSymbol()
{
}

//=================================
//������
//=================================
HRESULT CSymbol::Init(void)
{
	//�e�N���X����
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}
	//�p�^�[���������擾
	CTexture* pTexture = CManager::GetTexture();
	int nPatWidth = pTexture->GetPatWidth(m_nIdxTexture);
	int nPatHeight = pTexture->GetPatHeight(m_nIdxTexture);

	//�e�N�X�`���ݒ�
	D3DXVECTOR2 tex0, tex3;
	tex0 = D3DXVECTOR2((float)(CManager::INT_ZERO % nPatWidth) / nPatWidth,
		(float)(CManager::INT_ZERO / nPatWidth) / nPatHeight);
	tex3 = D3DXVECTOR2((float)(CManager::INT_ZERO % nPatWidth + 1) / nPatWidth,
		(float)(CManager::INT_ZERO / nPatWidth + 1) / nPatHeight);

	if (FAILED(SetTex(tex0, tex3)))
	{
		return E_FAIL;
	}

	return S_OK;
}
//=================================
//�I��
//=================================
void CSymbol::Uninit(void)
{
	//�e�N���X����
	CObject2D::Uninit();
}

//=================================
//�X�V
//=================================
void CSymbol::Update(void)
{
	//�e�N���X����
	CObject2D::Update();
}

//=================================
//�`��
//=================================
void CSymbol::Draw(void)
{
	//�e�N���X����
	CObject2D::Draw();
}

//=================================
//��������
//=================================
CSymbol* CSymbol::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight)
{
	CSymbol* pSymbol = nullptr;

	if (pSymbol == nullptr)
	{
		//�L���I�u�W�F�̐���
		pSymbol = new CSymbol(pos, rot, fWidth, fHeight);

		//������
		pSymbol->Init();

		return pSymbol;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//�������������inNum��0�ȏ�œ��͂��邱�Ɓj
//=================================
void CSymbol::SetSymbol(const int nNum)
{
	if (nNum < 0)
	{//�s��
		assert(false);
	}

	//�p�^�[���������擾
	CTexture* pTexture = CManager::GetTexture();
	int nPatWidth = pTexture->GetPatWidth(m_nIdxTexture);
	int nPatHeight = pTexture->GetPatHeight(m_nIdxTexture);

	//�e�N�X�`���ݒ�
	D3DXVECTOR2 tex0, tex3;
	tex0 = D3DXVECTOR2((float)(nNum % nPatWidth) / nPatWidth,
		(float)(nNum / nPatWidth) / nPatHeight);
	tex3 = D3DXVECTOR2((float)(nNum % nPatWidth + 1) / nPatWidth,
		(float)(nNum / nPatWidth + 1) / nPatHeight);

	if (FAILED(SetTex(tex0, tex3)))
	{
		assert(false);
	}
}

//=================================
//������p�e�N�X�`���ݒ菈��
//=================================
void CSymbol::BindTexture(int nIdx)
{
	//�e�N�X�`���ݒ�
	m_nIdxTexture = nIdx;

	//�e�ɂ��`����
	CObject2D::BindTexture(nIdx);
}