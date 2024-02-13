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
#include <assert.h>

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CNumber::CNumber(int nPriority) :CObject2D(nPriority)
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

	//�e�N�X�`���ݒ�
	D3DXVECTOR2 tex0, tex3;
	tex0 = D3DXVECTOR2(0.0f, 0.0f);
	tex3 = D3DXVECTOR2(1.0f, 1.0f);

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
		//����
		pNumber = new CNumber;

		//������
		pNumber->Init();

		//�f�[�^�ݒ�
		pNumber->SetPos(pos);
		pNumber->SetRot(rot);
		pNumber->SetSize(fWidth, fHeight);

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
void CNumber::SetNumber(const int nSource, const int nDigit)
{
	int nNumber = 0;	//1�����̐���

	if (nDigit < 0)
	{//�s��
		assert(false);
	}

	//�����Ƃ̐���������
	nNumber = nSource % (int)pow(10, nDigit + 1) / (int)pow(10, nDigit);

	//�p�^�[���������擾
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();
	int nIdx = GetIdxTexture();	//�e�N�X�`���ԍ��擾
	int nPatWidth = pTexture->GetPatWidth(nIdx);
	int nPatHeight = pTexture->GetPatHeight(nIdx);

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
//�e�N�X�`���ݒ�
//=================================
void CNumber::BindTexture(int nIdx)
{
	//�e�N�X�`���ݒ�
	CObject2D::BindTexture(nIdx);

	//�p�^�[���������擾
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();
	int nPatWidth = pTexture->GetPatWidth(nIdx);
	int nPatHeight = pTexture->GetPatHeight(nIdx);

	//�e�N�X�`���ݒ�
	D3DXVECTOR2 tex0, tex3;
	tex0 = D3DXVECTOR2((float)(0 % nPatWidth) / nPatWidth,
		(float)(0 / nPatWidth) / nPatHeight);
	tex3 = D3DXVECTOR2((float)(0 % nPatWidth + 1) / nPatWidth,
		(float)(0 / nPatWidth + 1) / nPatHeight);

	if (FAILED(SetTex(tex0, tex3)))
	{
		assert(false);
	}
}
