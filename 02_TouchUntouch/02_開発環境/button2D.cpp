//======================================================
//
//�{�^������(2D)[button2D.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "button2D.h"
#include "input.h"
#include "Culc.h"
#include "manager.h"
#include "renderer.h"

//========================
//�R���X�g���N�^
//========================
CButton2D::CButton2D()
{
	//�l�N���A
	m_bHold = false;
	m_bPress = false;
	m_bTrigger = false;
	m_bRelease = false;
	m_bRepeate = false;
}

//========================
//�f�X�g���N�^
//========================
CButton2D::~CButton2D()
{
}

//========================
//������
//========================
HRESULT CButton2D::Init(void)
{
	//�e����
	CObject2D::Init();

	return S_OK;
}

//========================
//�I��
//========================
void CButton2D::Uninit(void)
{
	//�e����
	CObject2D::Uninit();
}

//========================
//�X�V
//========================
void CButton2D::Update(void)
{
	//�{�^������
	CInputMouse* mouse = CManager::GetInstance()->GetInputMouse();	//�}�E�X�擾

	//�}�E�X�擾
	if (mouse != nullptr)
	{
		D3DXVECTOR3 buttonPos = GetPos();			//�{�^���ʒu�擾
		float fWidth = GetWidth();					//�{�^�����擾
		float fHeight = GetHeight();				//�{�^�������擾
		D3DXVECTOR3 cursorPos = mouse->GetPos();	//�J�[�\���ʒu�擾

		if (cursorPos.x >= buttonPos.x - fWidth * 0.5f &&
			cursorPos.x <= buttonPos.x + fWidth * 0.5f &&
			cursorPos.y >= buttonPos.y - fHeight * 0.5f &&
			cursorPos.y <= buttonPos.y + fHeight * 0.5f)
		{//�͈͓�
			m_bHold = true;										//������
			m_bPress = mouse->GetPress(CInputMouse::CLICK_LEFT);		//�v���X
			m_bTrigger = mouse->GetTrigger(CInputMouse::CLICK_LEFT);	//�g���K�[
			m_bRelease = mouse->GetRelease(CInputMouse::CLICK_LEFT);	//�����[�X
			m_bRepeate = mouse->GetRepeate(CInputMouse::CLICK_LEFT);	//���s�[�g
		}
		else
		{//�͈͊O
			m_bHold = false;	//������
			m_bPress = false;	//�v���X
			m_bTrigger = false;	//�g���K�[
			m_bRelease = false;	//�����[�X
			m_bRepeate = false;	//���s�[�g
		}
	}
	else
	{//�}�E�X���擾�ł��Ȃ�
		m_bHold = false;	//������
		m_bPress = false;	//�v���X
		m_bTrigger = false;	//�g���K�[
		m_bRelease = false;	//�����[�X
		m_bRepeate = false;	//���s�[�g
	}

	//�e����
	CObject2D::Update();
}

//========================
//�`��
//========================
void CButton2D::Draw(void)
{
	//�e����
	CObject2D::Draw();
}

//========================
//����
//========================
CButton2D* CButton2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, int nPriority)
{
	CButton2D* pButton2D = nullptr;

	if (pButton2D == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pButton2D = new CButton2D;

		//������
		pButton2D->Init();

		//�f�[�^�ݒ�
		pButton2D->SetPos(pos);
		pButton2D->SetRot(rot);
		pButton2D->SetSize(fWidth, fHeight);

		return pButton2D;
	}
	else
	{
		return nullptr;
	}
}