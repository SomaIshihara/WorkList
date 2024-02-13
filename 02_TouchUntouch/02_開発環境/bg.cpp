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
CBG::CBG(int nPriority) : CObject2D(nPriority)
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

	SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, CManager::FLT_ZERO));
	SetRot(CManager::VEC3_ZERO);
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

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
	//�e�N���X����
	CObject2D::Draw();
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