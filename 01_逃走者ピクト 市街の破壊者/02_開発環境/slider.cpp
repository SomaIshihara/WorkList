//======================================================
//
//�X���C�_�[����[slider.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "slider.h"
#include "picto.h"
#include "manager.h"
#include "object2D.h"
#include "texture.h"
#include "input.h"

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CSlider::CSlider()
{
	m_pObjFrame = nullptr;
	m_pObjMove = nullptr;
	m_ppObjIcon = nullptr;
	m_pos = CManager::VEC3_ZERO;
	m_fOneWidth = CManager::FLOAT_ZERO;
	m_fOneHeight = CManager::FLOAT_ZERO;
	m_nIdxNum = CManager::INT_ZERO;
	m_nSelect = CManager::INT_ZERO;
	m_bClick = false;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h�j
//=================================
CSlider::CSlider(const D3DXVECTOR3 pos, const float fOneWidth, const float fOneHeight, const int nIdxNum)
{
	m_pObjFrame = nullptr;
	m_pObjMove = nullptr;
	m_ppObjIcon = nullptr;
	m_pos = pos;
	m_fOneWidth = fOneWidth;
	m_fOneHeight = fOneHeight;
	m_nIdxNum = nIdxNum;
	m_nSelect = CManager::INT_ZERO;
	m_bClick = false;
}

//=================================
//�f�X�g���N�^
//=================================
CSlider::~CSlider()
{
}

//========================
//����������
//========================
HRESULT CSlider::Init(void)
{
	//�g
	m_pObjFrame = CObject2D::Create(m_pos, CManager::VEC3_ZERO, m_fOneWidth * m_nIdxNum, m_fOneHeight, PRIORITY_UI);
	m_pObjFrame->BindTexture(-1);
	m_pObjFrame->SetCol(D3DXCOLOR(0.0f, 0.7f, 0.0f, 1.0f));

	//�ړ���
	m_pObjMove = CObject2D::Create(m_pos, CManager::VEC3_ZERO, m_fOneWidth, m_fOneHeight, PRIORITY_UI);
	m_pObjMove->BindTexture(-1);

	//�A�C�R��
	m_ppObjIcon = new CObject2D*[m_nIdxNum];
	for (int cnt = 0; cnt < m_nIdxNum; cnt++)
	{
		float fPosX = (-((float)m_nIdxNum * 0.5f) + (0.5f + (float)cnt)) * m_fOneWidth;
		m_ppObjIcon[cnt] = CObject2D::Create(m_pos + D3DXVECTOR3(fPosX, 0.0f, 0.0f), CManager::VEC3_ZERO, m_fOneWidth, m_fOneHeight, PRIORITY_UI);
	}
	m_ppObjIcon[0]->BindTexture(CTexture::PRELOAD_SLIDER_01);
	m_ppObjIcon[1]->BindTexture(CTexture::PRELOAD_SLIDER_02);
	m_ppObjIcon[2]->BindTexture(CTexture::PRELOAD_SLIDER_03);

	m_nSelect = CPictoTaxi::MODE_SABO;

	return S_OK;
}

//========================
//�I������
//========================
void CSlider::Uninit(void)
{
	if (m_ppObjIcon != nullptr)
	{
		delete[] m_ppObjIcon;
		m_ppObjIcon = nullptr;
	}

	//�������g�j��
	Release();
}

//========================
//�X�V����
//========================
void CSlider::Update(void)
{
	CInputMouse* mouse =  CManager::GetInputMouse();	//�}�E�X�擾
	D3DXVECTOR3 mousePos = mouse->GetPos();				//�}�E�X�ʒu�擾
	D3DXVECTOR3 movePos = m_pObjMove->GetPos();

	//�N���b�N
	if (mouse->GetTrigger(MOUSE_CLICK_LEFT) == true &&
		mousePos.x >= movePos.x - m_fOneWidth * 0.5f && mousePos.x <= movePos.x + m_fOneWidth * 0.5f &&
		mousePos.y >= movePos.y - m_fOneHeight * 0.5f && mousePos.y <= movePos.y + m_fOneHeight * 0.5f)
	{//�N���b�N����
		m_bClick = true;
	}
	if(mouse->GetRelease(MOUSE_CLICK_LEFT) == true)
	{//������
		m_bClick = false;
	}

	//�I��
	if (m_bClick == true)
	{
		for (int cnt = 0; cnt < m_nIdxNum; cnt++)
		{
			D3DXVECTOR3 iconPos = m_ppObjIcon[cnt]->GetPos();
			if (mousePos.x >= iconPos.x - m_fOneWidth * 0.5f && mousePos.x <= iconPos.x + m_fOneWidth * 0.5f &&
				mousePos.y >= iconPos.y - m_fOneHeight * 0.5f && mousePos.y <= iconPos.y + m_fOneHeight * 0.5f)
			{//�ړ�����
				m_nSelect = cnt;
			}
		}
	}
	else
	{
		for (int cnt = 0; cnt < m_nIdxNum; cnt++)
		{
			D3DXVECTOR3 iconPos = m_ppObjIcon[cnt]->GetPos();
			if (mouse->GetTrigger(MOUSE_CLICK_LEFT) == true &&
				mousePos.x >= iconPos.x - m_fOneWidth * 0.5f && mousePos.x <= iconPos.x + m_fOneWidth * 0.5f &&
				mousePos.y >= iconPos.y - m_fOneHeight * 0.5f && mousePos.y <= iconPos.y + m_fOneHeight * 0.5f)
			{//�ړ�����
				m_bClick = true;
				m_nSelect = cnt;
			}
		}
	}

	//�ړ����ړ�
	float fPosX = (-((float)m_nIdxNum * 0.5f) + (0.5f + (float)m_nSelect)) * m_fOneWidth;
	movePos = m_pos + D3DXVECTOR3(fPosX, 0.0f, 0.0f);
	m_pObjMove->SetPos(movePos);
}

//========================
//�`�揈��
//========================
void CSlider::Draw(void)
{
}

//========================
//��������
//========================
CSlider* CSlider::Create(const D3DXVECTOR3 pos, const float fOneWidth, const float fOneHeight, const int nIdxNum)
{
	CSlider* pSlider = nullptr;

	if (pSlider == nullptr)
	{
		//�s�N�g�̐���
		pSlider = new CSlider(pos, fOneWidth, fOneHeight, nIdxNum);

		//������
		pSlider->Init();

		return pSlider;
	}
	else
	{
		return nullptr;
	}
}
