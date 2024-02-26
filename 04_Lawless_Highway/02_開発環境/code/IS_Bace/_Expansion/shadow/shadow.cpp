//======================================================
//
//�e�̏���[shadow.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "shadow.h"
#include "..\..\_Core\manager\manager.h"
#include "..\..\_Core\renderer\renderer.h"
#include "..\..\_Core\texture\texture.h"
#include "..\..\_Core\utility\Utility.h"

//=================================
//�R���X�g���N�^
//=================================
CShadow::CShadow(int nPriority) : CObject3D(nPriority)
{
	m_nIdxTexture = -1;
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

	//�e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\effect000.jpg");

	CObject3D::SetPos(IS_Utility::VEC3_ZERO);	//�ʒu�ݒ�
	CObject3D::SetRot(IS_Utility::VEC3_ZERO);	//�����ݒ�
	CObject3D::SetSize(50.0f, 50.0f);		//�T�C�Y�ݒ�

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
	//�����_���擾
	CRenderer* pRenderer = CManager::GetInstance()->GetRenderer();

	//�u�����f�B���O��ނ����Z�����ɕύX
	pRenderer->SetBlendType(CRenderer::BLENDTYPE::BLENDTYPE_SUB);

	//Z�e�X�g������
	pRenderer->SetEnableZTest(false);

	//�e����
	CObject3D::Draw();

	//Z�e�X�g�L����
	pRenderer->SetEnableZTest(true);

	//�u�����f�B���O��ނ�ʏ��Ԃɖ߂�
	pRenderer->SetBlendType(CRenderer::BLENDTYPE::BLENDTYPE_NORMAL);
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
void CShadow::Set(D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	//�ʒu�����ݒ�
	SetPos(pos);
	SetRot(rot);
}

//========================
//������r
//========================
float CShadow::ConpareLength(const float fNear, const float fLength)
{
	if (fLength >= 0.0f && fNear > fLength)
	{
		return fLength;
	}
	else
	{
		return fNear;
	}
}
