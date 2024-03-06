//======================================================
//
//�X�^�[�g��������[starttext.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "starttext.h"
#include "../../IS_Bace/_Core/texture/texture.h"
#include "../../IS_Bace/_Core/_object/object_2d/object2D.h"
#include "../../IS_Bace/_Core/utility/Utility.h"

//=================================
//�R���X�g���N�^
//=================================
CStartText::CStartText() : CObject2D(CObject::PRIORITY_05)
{
	m_nCounterUnLit = 0;
	m_nDefUnLitTime = 0;
	m_nDegUnLitTime = 0;
	m_nUnLitPercent = 100;
}

//=================================
//�f�X�g���N�^
//=================================
CStartText::~CStartText()
{
}

//=================================
//������
//=================================
HRESULT CStartText::Init(void)
{
	return CObject2D::Init();
}

//=================================
//�I��
//=================================
void CStartText::Uninit(void)
{
	CObject2D::Uninit();
}

//=================================
//�X�V
//=================================
void CStartText::Update(void)
{
	if (m_nCounterUnLit > 0)
	{//������
		m_nCounterUnLit--;

		CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	else
	{//�������ĂȂ�
		int nRand = rand() % 100;
		if (nRand < m_nUnLitPercent)
		{//��������
			m_nCounterUnLit = m_nDefUnLitTime + (rand() % (m_nDegUnLitTime * 2) - m_nDegUnLitTime);
		}
		CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	CObject2D::Update();
}

//=================================
//�`��
//=================================
void CStartText::Draw(void)
{
	CObject2D::Draw();
}

//=================================
//����
//=================================
CStartText* CStartText::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight)
{
	CStartText* pStartText = nullptr;

	if (pStartText == nullptr)
	{
		//�I�u�W�F�N�g�̐���
		pStartText = new CStartText;

		//������
		pStartText->Init();
		pStartText->SetPos(pos);
		pStartText->SetRot(rot);
		pStartText->SetSize(fWidth, fHeight);

		return pStartText;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//�_���p�����[�^�ݒ�
//=================================
void CStartText::SetLitParam(const int nDef, const int nDegree, const int nPercent)
{
	m_nDefUnLitTime = nDef;
	m_nDegUnLitTime = nDegree;
	m_nUnLitPercent = nPercent;
}
