//======================================================
//
//��������[number.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object2D.h"
#include "number.h"
#include "input.h"
#include <assert.h>

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CNumber::CNumber(int nPriority) :CObject2D(nPriority)
{
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h �ʒu����and�������j
//=================================
CNumber::CNumber(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, int nPriority) 
	: CObject2D(pos,rot, fWidth, fHeight, nPriority)
{
}

//=================================
//�f�X�g���N�^
//=================================
CNumber::~CNumber()
{
}

//=================================
//������
//=================================
HRESULT CNumber::Init(void)
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
void CNumber::Uninit(void)
{
	//�e�N���X����
	CObject2D::Uninit();
}

//=================================
//�X�V
//=================================
void CNumber::Update(void)
{
	//�e�N���X����
	CObject2D::Update();
}

//=================================
//�`��
//=================================
void CNumber::Draw(void)
{
	//�e�N���X����
	CObject2D::Draw();
}

//=================================
//��������
//=================================
CNumber* CNumber::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight)
{
	CNumber* pNumber = nullptr;

	if (pNumber == nullptr)
	{
		//�I�u�W�F�N�g�A�j���[�V����2D�̐���
		pNumber = new CNumber(pos, rot, fWidth, fHeight);

		//������
		pNumber->Init();

		return pNumber;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//�������������inDigit��0�ȏ�œ��͂��邱�Ɓj
//=================================
void CNumber::SetNumber(const long long nSource, const int nDigit)
{
	int nNumber = 0;	//1�����̐���

	if (nDigit < 0)
	{//�s��
		assert(false);
	}

	//�����Ƃ̐���������
	nNumber = nSource % (long long)pow(10, nDigit + 1) / (long long)pow(10, nDigit);

	//�p�^�[���������擾
	CTexture* pTexture = CManager::GetTexture();
	int nPatWidth = pTexture->GetPatWidth(m_nIdxTexture);
	int nPatHeight = pTexture->GetPatHeight(m_nIdxTexture);

	//�e�N�X�`���ݒ�
	D3DXVECTOR2 tex0, tex3;
	tex0 = D3DXVECTOR2((float)(nNumber % nPatWidth) / nPatWidth,
		(float)(nNumber / nPatWidth) / nPatHeight);
	tex3 = D3DXVECTOR2((float)(nNumber % nPatWidth + 1) / nPatWidth,
		(float)(nNumber / nPatWidth + 1) / nPatHeight);

	if (FAILED(SetTex(tex0, tex3)))
	{
		assert(false);
	}
}

//=================================
//������p�e�N�X�`���ݒ菈��
//=================================
void CNumber::BindTexture(int nIdx)
{
	//�e�N�X�`���ݒ�
	m_nIdxTexture = nIdx;

	//�e�ɂ��`����
	CObject2D::BindTexture(nIdx);
}