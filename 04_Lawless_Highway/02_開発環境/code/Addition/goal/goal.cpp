//======================================================
//
//�S�[������[goal.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "goal.h"
#include "../../IS_Bace/_Core/_object/object_3d/object3D.h"
#include "../../IS_Bace/_Core/collision/collision.h"
#include "../../IS_Bace/_Core/utility/Utility.h"
#include "../../IS_Bace/_Core/texture/texture.h"

//=================================
//�R���X�g���N�^
//=================================
CGoal::CGoal(int nPriority) : CObject(nPriority)
{
	//�N���A
	m_pos = IS_Utility::VEC3_ZERO;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_pCollider = nullptr;
	m_bIsGoal = false;
}

//=================================
//�f�X�g���N�^
//=================================
CGoal::~CGoal()
{
}

//========================
//����������
//========================
HRESULT CGoal::Init(void)
{
	//�����蔻��t�^
	m_pCollider = CBoxCollider::Create(this);
	m_pCollider->SetType(CBoxCollider::TYPE::TYPE_TRIGGER);

	//�S�[�����I�u�W�F�N�g����
	CObject3D* pObj = CObject3D::Create(m_pos + D3DXVECTOR3(0.0f, 1.0f, 0.0f), IS_Utility::VEC3_ZERO, m_fWidth, m_fDepth);
	pObj->BindTexture(CTexture::PRELOAD_22_GOAL);

	return S_OK;
}

//========================
//�I������
//========================
void CGoal::Uninit(void)
{
	if (m_pCollider != nullptr)
	{
		m_pCollider->Release();
		m_pCollider = nullptr;
	}

	//�������g�j��
	Release();
}

//========================
//�X�V����
//========================
void CGoal::Update(void)
{
	if (m_pCollider != nullptr)
	{
		m_pCollider->CollisionCheck();
		if (m_pCollider->GetResult().collList.size() >= 1)
		{
			m_bIsGoal = true;
		}
	}
}

//========================
//�`�揈��
//========================
void CGoal::Draw(void)
{

}

//========================
//��������
//========================
CGoal* CGoal::Create(const D3DXVECTOR3 pos, const float fWidth, const float fHeight, const float fDepth)
{
	CGoal* pGoal = nullptr;

	if (pGoal == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pGoal = new CGoal;

		//�l�ݒ�
		pGoal->SetPos(pos);
		pGoal->m_fWidth = fWidth;
		pGoal->m_fHeight = fHeight;
		pGoal->m_fDepth = fDepth;

		//������
		pGoal->Init();

		return pGoal;
	}
	else
	{
		return nullptr;
	}
}
