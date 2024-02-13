//======================================================
//
//�e�̏���[shadow.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "shadow.h"
#include "renderer.h"
#include "texture.h"

//=================================
//�R���X�g���N�^
//=================================
CShadow::CShadow() : CObject3D(CManager::VEC3_ZERO, CManager::VEC3_ZERO, 20.0f, 20.0f)
{
}

//=================================
//�f�X�g���N�^
//=================================
CShadow::~CShadow()
{
}

//========================
//����������
//========================
HRESULT CShadow::Init(void)
{
	//�e����
	CObject3D::Init();

	//���F�e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\effect000.jpg");

	//�ł���
	return S_OK;
}

//========================
//�I������
//========================
void CShadow::Uninit(void)
{
	//�e����
	CObject3D::Uninit();
}

//========================
//�X�V����
//========================
void CShadow::Update(void)
{
	//�e����
	CObject3D::Update();
}

//========================
//�`�揈��
//========================
void CShadow::Draw(void)
{
	//�u�����f�B���O��ނ����Z�����ɕύX
	CManager::GetRenderer()->SetBlendType(CRenderer::BLENDTYPE_SUB);

	//�e����
	CObject3D::Draw();

	//�u�����f�B���O��ނ�ʏ��Ԃɖ߂�
	CManager::GetRenderer()->SetBlendType(CRenderer::BLENDTYPE_NORMAL);
}

//========================
//��������
//========================
CShadow* CShadow::Create(void)
{
	CShadow* pShadow = nullptr;

	if (pShadow == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pShadow = new CShadow();

		//������
		pShadow->Init();

		//�e�N�X�`���ݒ�
		pShadow->BindTexture(pShadow->m_nIdxTexture);

		return pShadow;
	}
	else
	{
		return nullptr;
	}
}

//========================
//�j������
//========================
void CShadow::Release(void)
{
	CObject3D::Release();
}

//========================
//�ʒu�����ݒ菈��
//========================
void CShadow::Set(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	//�ʒu�����ݒ�
	SetPos(pos);
	SetRot(rot);
}
