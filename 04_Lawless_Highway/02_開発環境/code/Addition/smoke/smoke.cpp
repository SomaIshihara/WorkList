//======================================================
//
//������[smoke.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "smoke.h"
#include "../../IS_Bace/_Core/manager/manager.h"
#include "../../IS_Bace/_Core/renderer/renderer.h"
#include "../../IS_Bace/_Core/texture/texture.h"

//=================================
//�R���X�g���N�^
//=================================
CSmoke::CSmoke(int nAnimSpeed) : CObjectBillboard(4) , m_nAnimSpeed(nAnimSpeed)
{
	m_nCounter = 0;
	m_nPattern = 0;
}

//=================================
//�f�X�g���N�^
//=================================
CSmoke::~CSmoke()
{
}

//=================================
//������
//=================================
HRESULT CSmoke::Init(void)
{
	return CObjectBillboard::Init();
}

//=================================
//�I��
//=================================
void CSmoke::Uninit(void)
{
	CObjectBillboard::Uninit();
}

//=================================
//�X�V
//=================================
void CSmoke::Update(void)
{
	//�A�j���[�V����
	m_nCounter++;
	if (m_nCounter >= m_nAnimSpeed)
	{
		m_nCounter = 0;

		int nIdxTexture = CObjectBillboard::GetIdxTexture();
		int nPatWidth = CManager::GetInstance()->GetTexture()->GetPatWidth(nIdxTexture);
		int nPatHeight = CManager::GetInstance()->GetTexture()->GetPatHeight(nIdxTexture);
		m_nPattern = (m_nPattern + 1) % (nPatWidth * nPatHeight);

		int u = m_nPattern % nPatWidth;
		int v = m_nPattern / nPatWidth;

		CObjectBillboard::SetTex(u, v);
	}

	CObjectBillboard::Update();
}

//=================================
//�`��
//=================================
void CSmoke::Draw(void)
{
	//�A���t�@�e�X�g�L����
	CManager::GetInstance()->GetRenderer()->SetEnableAlplaTest(true);

	//�e�N���X����
	CObjectBillboard::Draw();

	//�A���t�@�e�X�g������
	CManager::GetInstance()->GetRenderer()->SetEnableAlplaTest(false);
}

//=================================
//����
//=================================
CSmoke* CSmoke::Create(const D3DXVECTOR3 pos, const float fRadius, const int nAnimSpeed)
{
	CSmoke* pSmoke = nullptr;

	if (pSmoke == nullptr)
	{
		//�I�u�W�F�N�g�̐���
		pSmoke = new CSmoke(nAnimSpeed);

		//������
		pSmoke->Init();
		pSmoke->SetPos(pos);
		pSmoke->SetRot(D3DXVECTOR3(-0.3f, 0.0f, 0.0f));
		pSmoke->SetSize(fRadius, fRadius);
		pSmoke->SetTex(0, 0);
		pSmoke->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		return pSmoke;
	}
	else
	{
		return nullptr;
	}
}
