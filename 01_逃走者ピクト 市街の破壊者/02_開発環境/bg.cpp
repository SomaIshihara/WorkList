//======================================================
//
//�w�i�i2D�j����[bg.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//=================================
//�R���X�g���N�^
//=================================
CBG::CBG(int nPriority) : CObject2D(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, CManager::FLOAT_ZERO), CManager::VEC3_ZERO, SCREEN_WIDTH, SCREEN_HEIGHT, nPriority)
{
	m_nIdxTexture = -1;
}

//=================================
//�f�X�g���N�^
//=================================
CBG::~CBG()
{
}

//=================================
//������
//=================================
HRESULT CBG::Init(void)
{
	//�e�N���X����
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//=================================
//�I��
//=================================
void CBG::Uninit(void)
{
	//�e�N���X����
	CObject2D::Uninit();
}

//=================================
//�X�V
//=================================
void CBG::Update(void)
{
	//�e�N���X����
	CObject2D::Update();
}

//=================================
//�`��
//=================================
void CBG::Draw(void)
{
	//Z�o�b�t�@���g�p���Ȃ�
	CManager::GetRenderer()->SetZEnable(false);

	//�e�N���X����
	CObject2D::Draw();
	
	//Z�o�b�t�@���g�p����
	CManager::GetRenderer()->SetZEnable(true);
}

//=================================
//��������
//=================================
CBG* CBG::Create(const int nPriority)
{
	CBG* pObjBG = nullptr;

	if (pObjBG == nullptr)
	{
		//�w�i�̐���
		pObjBG = new CBG(nPriority);

		//������
		pObjBG->Init();

		return pObjBG;
	}
	else
	{
		return nullptr;
	}
}