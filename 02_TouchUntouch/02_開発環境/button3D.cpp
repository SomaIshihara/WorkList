//======================================================
//
//�{�^������(3D)[button3D.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "button3D.h"
#include "input.h"
#include "Culc.h"
#include "manager.h"
#include "renderer.h"

//========================
//�R���X�g���N�^
//========================
CButton3D::CButton3D(int nPriority) : CObject3D(nPriority)
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
CButton3D::~CButton3D()
{
}

//========================
//������
//========================
HRESULT CButton3D::Init(void)
{
	//�e����
	CObject3D::Init();

	return S_OK;
}

//========================
//�I��
//========================
void CButton3D::Uninit(void)
{
	//�e����
	CObject3D::Uninit();
}

//========================
//�X�V
//========================
void CButton3D::Update(void)
{
	//�{�^������
	CInputMouse* mouse = CManager::GetInstance()->GetInputMouse();	//�}�E�X�擾

	//�}�E�X�擾
	if (mouse != nullptr)
	{
		D3DXVECTOR3 buttonPos = GetPos();			//�{�^���ʒu�擾
		D3DXVECTOR3 buttonRot = GetRot();			//�{�^���p�x�擾
		float fWidth = GetWidth();					//�{�^�����擾
		float fDepth = GetDepth();					//�{�^�������擾
		D3DXVECTOR3 cursorPos = mouse->GetPos();	//�J�[�\���ʒu�擾

		//�I�u�W�F�N�g�I���i0.0�`1.0�j
		D3DXVECTOR3 posNear = mouse->ConvertClickPosToWorld(0.0f);
		D3DXVECTOR3 posFar = mouse->ConvertClickPosToWorld(1.0f);

		//���_�v�Z
		D3DXVECTOR3 pos0 = D3DXVECTOR3(-fWidth * 0.5f, 0.0f, fDepth * 0.5f);
		D3DXVECTOR3 pos1 = D3DXVECTOR3(fWidth * 0.5f, 0.0f, fDepth * 0.5f);
		D3DXVECTOR3 pos2 = D3DXVECTOR3(-fWidth * 0.5f, 0.0f, -fDepth * 0.5f);
		D3DXVECTOR3 pos3 = D3DXVECTOR3(fWidth * 0.5f, 0.0f, -fDepth * 0.5f);
		pos0 = RotateVtx(pos0, buttonRot, buttonPos);
		pos1 = RotateVtx(pos1, buttonRot, buttonPos);
		pos2 = RotateVtx(pos2, buttonRot, buttonPos);
		pos3 = RotateVtx(pos3, buttonRot, buttonPos);

		float fDust;
		D3DXVECTOR3 nor = (posFar - posNear);
		D3DXVec3Normalize(&nor, &nor);
		if (D3DXIntersectTri(&pos2, &pos1, &pos0, &posNear, &nor, &fDust, &fDust, &fDust) == true ||
			D3DXIntersectTri(&pos1, &pos2, &pos3, &posNear, &nor, &fDust, &fDust, &fDust) == true)
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
	CObject3D::Update();
}

//========================
//�`��
//========================
void CButton3D::Draw(void)
{
	//�e����
	CObject3D::Draw();
}

//========================
//����
//========================
CButton3D* CButton3D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight)
{
	CButton3D* pButton3D = nullptr;

	if (pButton3D == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pButton3D = new CButton3D;
		pButton3D->SetPos(pos);
		pButton3D->SetRot(rot);
		pButton3D->SetSize(fWidth, fHeight);

		//������
		pButton3D->Init();

		return pButton3D;
	}
	else
	{
		return nullptr;
	}
}