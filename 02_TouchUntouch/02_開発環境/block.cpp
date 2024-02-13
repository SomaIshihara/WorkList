//======================================================
//
//�u���b�N����[block.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "block.h"

//****************************************
//2D�u���b�N
//****************************************
//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CBlock2D::CBlock2D(int nPriority) : CObject2D(nPriority)
{
	//�l�N���A
	m_nIdxTexture = -1;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h �ʒu�������j
//=================================
CBlock2D::CBlock2D(const D3DXVECTOR3 pos, const float fWidth, const float fHeight, int nPriority) :CObject2D(pos, VEC3_ZERO, fWidth, fHeight, nPriority)
{
	//�l�N���A
	m_nIdxTexture = -1;
}

//=================================
//�f�X�g���N�^
//=================================
CBlock2D::~CBlock2D()
{
}

//=================================
//������
//=================================
HRESULT CBlock2D::Init(void)
{
	//�e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Block_R_01.png");

	SetType(TYPE_BLOCK);	//�^�C�v�ݒ�

	return CObject2D::Init();
}

//=================================
//�I��
//=================================
void CBlock2D::Uninit(void)
{
	CObject2D::Uninit();
}

//=================================
//�X�V
//=================================
void CBlock2D::Update(void)
{
	CObject2D::Update();
}

//=================================
//�`��
//=================================
void CBlock2D::Draw(void)
{
	CObject2D::Draw();
}

//=================================
//��������
//=================================
CBlock2D* CBlock2D::Create(const D3DXVECTOR3 pos, const float fWidth, const float fHeight)
{
	CBlock2D* pBlock = NULL;

	if (pBlock == NULL)
	{
		//�I�u�W�F�N�g�A�j���[�V����2D�̐���
		pBlock = new CBlock2D(pos, fWidth, fHeight);

		//������
		pBlock->Init();

		//�e�N�X�`���ݒ�
		pBlock->BindTexture(pBlock->m_nIdxTexture);

		return pBlock;
	}
	else
	{
		return NULL;
	}
}

//****************************************
//3D�u���b�N
//****************************************
//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CBlock3D::CBlock3D(int nPriority) : CObjectX(nPriority)
{
	//�l�N���A
	m_nIdxTexture = -1;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h �ʒu�������j
//=================================
CBlock3D::CBlock3D(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nIdx, int nPriority) : CObjectX(pos, VEC3_ZERO, nIdx, nPriority)
{
	//�l�N���A
	m_nIdxTexture = -1;
}

//=================================
//�f�X�g���N�^
//=================================
CBlock3D::~CBlock3D()
{
}

//=================================
//������
//=================================
HRESULT CBlock3D::Init(void)
{
	SetType(TYPE_BLOCK);	//�^�C�v�ݒ�

	return CObjectX::Init();
}

//=================================
//�I��
//=================================
void CBlock3D::Uninit(void)
{
	CObjectX::Uninit();
}

//=================================
//�X�V
//=================================
void CBlock3D::Update(void)
{
	CObjectX::Update();
}

//=================================
//�`��
//=================================
void CBlock3D::Draw(void)
{
	CObjectX::Draw();
}

//=================================
//��������
//=================================
CBlock3D* CBlock3D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nIdx)
{
	CBlock3D* pBlock = NULL;

	if (pBlock == NULL)
	{
		//�I�u�W�F�N�g�A�j���[�V����2D�̐���
		pBlock = new CBlock3D(pos, rot, nIdx);

		//������
		pBlock->Init();

		return pBlock;
	}
	else
	{
		return NULL;
	}
}