//======================================================
//
//�X�s�[�h���[�^�[����[speedmeter.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "speedmeter.h"
#include "../../IS_Bace/_Core/texture/texture.h"
#include "../../IS_Bace/_Core/_object/object_2d/object2D.h"
#include "../../IS_Bace/_Core/utility/Utility.h"

//=================================
//�R���X�g���N�^
//=================================
CSpeedMeter::CSpeedMeter()
{
	m_pos = IS_Utility::VEC3_ZERO;
	m_fRadius = 0.0f;
	m_pObjFrame = nullptr;
	m_pObjMeter = nullptr;
}

//=================================
//�f�X�g���N�^
//=================================
CSpeedMeter::~CSpeedMeter()
{
}

//=================================
//������
//=================================
HRESULT CSpeedMeter::Init(void)
{
	//�I�u�W�F�N�g����
	m_pObjFrame = CObject2D::Create(m_pos, IS_Utility::VEC3_ZERO, m_fRadius, m_fRadius, CObject::PRIORITY_05);
	m_pObjFrame->BindTexture(CTexture::PRELOAD_35_SPEEDMETER_01);
	m_pObjMeter = CObject2D::Create(m_pos, IS_Utility::VEC3_ZERO, m_fRadius, m_fRadius, CObject::PRIORITY_05);
	m_pObjMeter->BindTexture(CTexture::PRELOAD_36_SPEEDMETER_02);

	return S_OK;
}

//=================================
//�I��
//=================================
void CSpeedMeter::Uninit(void)
{
	Release();
}

//=================================
//�X�V
//=================================
void CSpeedMeter::Update(void)
{
	
}

//=================================
//�`��
//=================================
void CSpeedMeter::Draw(void)
{
	
}

//=================================
//�ʒu�ݒ�
//=================================
void CSpeedMeter::SetPos(const D3DXVECTOR3 pos)
{
	//�匳�ݒ�
	m_pos = pos;

	//�I�u�W�F�N�g�ݒ�
	m_pObjFrame->SetPos(pos);
	m_pObjMeter->SetPos(pos);
}

//=================================
//�Q�[�W�ݒ�
//=================================
void CSpeedMeter::SetGauge(const float gauge)
{
	float clampGauge = IS_Utility::Clamp(gauge, 1.0f, 0.0f);
	m_pObjMeter->SetRot(D3DXVECTOR3(0.0f, 0.0f, -0.5f * D3DX_PI * clampGauge));
}

//=================================
//����
//=================================
CSpeedMeter* CSpeedMeter::Create(const D3DXVECTOR3 pos, const float fRadius)
{
	CSpeedMeter* pSpeedMeter = nullptr;

	if (pSpeedMeter == nullptr)
	{
		//�I�u�W�F�N�g�̐���
		pSpeedMeter = new CSpeedMeter;

		//������
		pSpeedMeter->m_pos = pos;
		pSpeedMeter->m_fRadius = fRadius;
		pSpeedMeter->Init();

		return pSpeedMeter;
	}
	else
	{
		return nullptr;
	}
}
