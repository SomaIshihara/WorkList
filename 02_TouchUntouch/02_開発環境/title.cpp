//======================================================
//
//�^�C�g���V�[��[title.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "texture.h"
#include "title.h"
#include "fade.h"
#include "input.h"
#include "camera.h"
#include "sound.h"
#include "object2D.h"

//�ÓI�����o�ϐ�

//=================================
//�R���X�g���N�^
//=================================
CTitle::CTitle()
{
	m_pFade = nullptr;
	m_pStart = nullptr;
}

//=================================
//�f�X�g���N�^
//=================================
CTitle::~CTitle()
{
}

//=================================
//������
//=================================
HRESULT CTitle::Init(void)
{
	//�w�i
	CBG::Create()->BindTexture(CTexture::PRELOAD_26_BG_01);

	//�^�C�g�����S
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 300.0f, 0.0f), CManager::VEC3_ZERO, 1180.0f, 244.0f, CObject::PRIORITY_05)->BindTexture(CTexture::PRELOAD_00_TITLELOGO);

	//�X�^�[�g����
	m_pStart = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 600.0f, 0.0f), CManager::VEC3_ZERO, 560.0f, 48.0f, CObject::PRIORITY_05);
	m_pStart->BindTexture(CTexture::PRELOAD_01_STARTKB);

	//BGM�Đ�
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_OUT);

	return S_OK;
}

//=================================
//�I��
//=================================
void CTitle::Uninit(void)
{
	//����~
	CManager::GetInstance()->GetSound()->Stop();

	//�I�u�W�F�S�j��
	for (int cnt = 0; cnt < CObject::PRIORITY_FADE; cnt++)
	{
		CObject::ReleaseAll(cnt);
	}
}

//=================================
//�X�V
//=================================
void CTitle::Update(void)
{
	CManager* pIns = CManager::GetInstance();
	CInputKeyboard* pKeyboard = pIns->GetInputKeyboard();
	CInputGamePad* pGamepad = pIns->GetInputGamePad();
	bool bPush = false;

	if (pGamepad != nullptr && pGamepad->IsConnect() == true)
	{//�Q�[���p�b�h�ڑ�
		m_pStart->BindTexture(CTexture::PRELOAD_02_STARTGP);

		if (pGamepad->GetTrigger(XINPUT_GAMEPAD_A))
		{
			bPush = true;
		}
	}
	else
	{//���ڑ�
		m_pStart->BindTexture(CTexture::PRELOAD_01_STARTKB);

		if (pKeyboard->GetTrigger(DIK_RETURN))
		{
			bPush = true;
		}
	}

	if (m_pFade == nullptr && bPush == true)
	{//�X�y�[�X�����ꂽ
		m_pFade = CFade::Create(CScene::MODE_TUTORIAL);

		//SE�Đ�
		CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
	}
}

//=================================
//�`��
//=================================
void CTitle::Draw(void)
{
}
