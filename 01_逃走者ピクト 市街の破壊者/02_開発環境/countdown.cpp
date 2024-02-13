//======================================================
//
//�J�E���g�_�E������[countdown.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "countdown.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object2D.h"
#include "sound.h"

//=================================
//�R���X�g���N�^
//=================================
CCountDown::CCountDown(const int startCount) : m_startCount(startCount)
{
	m_pos = CManager::VEC3_ZERO;
	m_pFrame = nullptr;
	m_ppCount = nullptr;
	m_count = startCount + 1;
	m_counterSec = CManager::INT_ZERO;
	m_shouldCount = false;
}

//=================================
//�f�X�g���N�^
//=================================
CCountDown::~CCountDown()
{
}

//=================================
//������
//=================================
HRESULT CCountDown::Init(void)
{
	return S_OK;
}

//=================================
//�I��
//=================================
void CCountDown::Uninit(void)
{
	//�g�j��
	if (m_pFrame != nullptr)
	{
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	//�J�E���g
	for (int cnt = 0; cnt < m_startCount + 1; cnt++)
	{
		if (m_ppCount[cnt] != nullptr)
		{
			m_ppCount[cnt]->Uninit();
			m_ppCount[cnt] = nullptr;
		}
	}

	delete[] m_ppCount;
}

//=================================
//�X�V
//=================================
void CCountDown::Update(void)
{
	if (m_shouldCount == true)
	{//�X�^�[�g���Ă���
		m_counterSec++;
		if (m_counterSec >= MAX_FPS)
		{//1�b���̃t���[�����񂵂�
			m_counterSec = 0;
			m_count--;
		}
	}

	//�\���ݒ�
	//�������񌳂ɖ߂�
	for (int cnt = 0; cnt < m_startCount + 1; cnt++)
	{
		m_ppCount[cnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//�Â�����
	for (int cnt = 0; cnt < m_count; cnt++)
	{
		m_ppCount[cnt]->SetCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	}
}

//=================================
//�`��
//=================================
void CCountDown::Draw(void)
{
	//�蓮�`��
	m_pFrame->Draw();
	for (int cnt = 0; cnt < m_startCount + 1; cnt++)
	{
		m_ppCount[cnt]->Draw();
	}
}

//=================================
//��������
//=================================
CCountDown* CCountDown::Create(const D3DXVECTOR3 pos, const float fOneWidth, const float fHeight, const int nCount)
{
	CCountDown* pObjCountDown = nullptr;

	if (pObjCountDown == nullptr)
	{
		//�w�i�̐���
		pObjCountDown = new CCountDown(nCount);

		//������
		pObjCountDown->Init();
		pObjCountDown->SetPos(pos);

		//�g
		pObjCountDown->m_pFrame = CObject2D::Create(pos, CManager::VEC3_ZERO, fOneWidth * (nCount + 1), fHeight,PRIORITY_UI);
		pObjCountDown->m_pFrame->Init();
		pObjCountDown->m_pFrame->BindTexture(CTexture::PRELOAD_COUNTDOWN_01);

		//�J�E���g
		//�p�^�[���������擾
		CTexture* pTexture = CManager::GetTexture();
		int nPatWidth = pTexture->GetPatWidth(CTexture::PRELOAD_COUNTDOWN_02);
		int nPatHeight = pTexture->GetPatHeight(CTexture::PRELOAD_COUNTDOWN_02);

		//�z�񐶐�
		pObjCountDown->m_ppCount = new CObject2D*[nCount + 1];

		//�I�u�W�F�N�g����
		for (int cnt = 0; cnt < nCount + 1; cnt++)
		{
			pObjCountDown->m_ppCount[cnt] = CObject2D::Create(pos + D3DXVECTOR3(((float)cnt - (0.5f * nCount)) * fOneWidth, 0.0f, 0.0f),
				CManager::VEC3_ZERO, fOneWidth, fHeight, PRIORITY_UI);
			pObjCountDown->m_ppCount[cnt]->Init();
			pObjCountDown->m_ppCount[cnt]->BindTexture(CTexture::PRELOAD_COUNTDOWN_02);

			//�e�N�X�`���ݒ�
			D3DXVECTOR2 tex0, tex3;
			tex0 = D3DXVECTOR2((float)(cnt % nPatWidth) / nPatWidth,
				(float)(cnt / nPatWidth) / nPatHeight);
			tex3 = D3DXVECTOR2((float)(cnt % nPatWidth + 1) / nPatWidth,
				(float)(cnt / nPatWidth + 1) / nPatHeight);

			//�ݒ�
			pObjCountDown->m_ppCount[cnt]->SetTex(tex0, tex3);
		}

		return pObjCountDown;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//�J�E���g�_�E���J�n
//=================================
void CCountDown::Start(void)
{
	m_shouldCount = true;
	m_count--;
}
