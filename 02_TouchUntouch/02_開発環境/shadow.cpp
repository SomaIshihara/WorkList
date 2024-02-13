//======================================================
//
//�e�̏���[shadow.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "shadow.h"
#include "renderer.h"
#include "texture.h"
#include "block3D.h"
#include "switch.h"
#include "switchmanager.h"
#include "character.h"

//=================================
//�R���X�g���N�^
//=================================
CShadow::CShadow(int nPriority) : CObject3D(nPriority)
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

	//�e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\effect000.jpg");

	CObject3D::SetPos(CManager::VEC3_ZERO);	//�ʒu�ݒ�
	CObject3D::SetRot(CManager::VEC3_ZERO);	//�����ݒ�
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
	pRenderer->SetBlendType(CRenderer::BLENDTYPE_SUB);

	//Z�e�X�g������
	pRenderer->SetEnableZTest(false);

	//�e����
	CObject3D::Draw();

	//Z�e�X�g�L����
	pRenderer->SetEnableZTest(true);

	//�u�����f�B���O��ނ�ʏ��Ԃɖ߂�
	pRenderer->SetBlendType(CRenderer::BLENDTYPE_NORMAL);
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
void CShadow::Set(D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const CCharacter::TYPE type)
{
	//���������i�u���b�N�ƃX�C�b�`�̂ݑ���j
	float fLengthNear = FLT_MAX;

	//�u���b�N
	CBlock3D* pBlock = CBlock3D::GetTop();

	while (pBlock != nullptr)
	{
		D3DXVECTOR3 posBlock = pBlock->GetPos();
		float fWidthBlockHalf = pBlock->GetWidth() * 0.5f;
		float fDepthBlockHalf = pBlock->GetDepth() * 0.5f;

		if (pos.x <= posBlock.x + fWidthBlockHalf && pos.x >= posBlock.x - fWidthBlockHalf &&
			pos.z <= posBlock.z + fDepthBlockHalf && pos.z >= posBlock.z - fDepthBlockHalf)
		{//�u���b�N�̐^��ɂ���
			//�u���b�N�̎�ނ��ʏ킩on�̃M�~�b�N��
			CBlock3D::TYPE blocktype = pBlock->GetType();
			if (blocktype == CBlock3D::TYPE_NORMAL)
			{//�ʏ�
				float fHeightBlockHalf = pBlock->GetHeight() * 0.5f;
				float fLength = pos.y - posBlock.y - fHeightBlockHalf;

				fLengthNear = ConpareLength(fLengthNear, fLength);
			}
			else if (blocktype == CBlock3D::TYPE_GIMMICK_01 || blocktype == CBlock3D::TYPE_GIMMICK_02)
			{//�M�~�b�N
				if (CBlock3D::GetSwitchManager()->IsPush()[blocktype - CBlock3D::TYPE_GIMMICK_01] == true)
				{
					float fHeightBlockHalf = pBlock->GetHeight() * 0.5f;
					float fLength = pos.y - posBlock.y - fHeightBlockHalf;

					fLengthNear = ConpareLength(fLengthNear, fLength);
				}
			}
			else if (blocktype == CBlock3D::TYPE_A || blocktype == CBlock3D::TYPE_B)
			{//�F
				if (type == blocktype)
				{
					float fHeightBlockHalf = pBlock->GetHeight() * 0.5f;
					float fLength = pos.y - posBlock.y - fHeightBlockHalf;

					fLengthNear = ConpareLength(fLengthNear, fLength);
				}
			}
		}

		pBlock = pBlock->GetNext();
	}

	//�X�C�b�`
	CSwitch* pSwitch = CSwitch::GetTop();

	while (pSwitch != nullptr)
	{
		D3DXVECTOR3 posSwitch = pSwitch->GetPos();
		float fWidthSwitchHalf = pSwitch->GetMove()->GetWidth() * 0.5f;
		float fDepthSwitchHalf = pSwitch->GetMove()->GetDepth() * 0.5f;

		if (pos.x < posSwitch.x + fWidthSwitchHalf && pos.x > posSwitch.x - fWidthSwitchHalf &&
			pos.z < posSwitch.z + fDepthSwitchHalf && pos.z > posSwitch.z - fDepthSwitchHalf)
		{//�u���b�N�̐^��ɂ���
			float fHeightSwitchHalf = pSwitch->GetMove()->GetHeight() * 0.5f;
			float fLength = pos.y - posSwitch.y + fHeightSwitchHalf;

			if (fLength >= 0.0f && fLengthNear > fLength)
			{
				fLengthNear = fLength;	//�ŒZ���������
			}
		}

		pSwitch = pSwitch->GetNext();
	}

	//����
	pos.y -= fLengthNear;

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
