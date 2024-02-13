//======================================================
//
//�|�[�Y���[game.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "pause.h"
#include "texture.h"
#include "input.h"
#include "bg.h"
#include "object2D.h"
#include "button.h"
#include "fade.h"
#include "sound.h"

//=================================
//�R���X�g���N�^
//=================================
CPause::CPause()
{
	m_pBG = nullptr;
	m_pPolygon = nullptr;
	m_pContinue = nullptr;
	m_pRestart = nullptr;
	m_pExit = nullptr;
	m_pScreenShot = nullptr;
	m_bScreenShotMode = false;
}

//=================================
//�f�X�g���N�^
//=================================
CPause::~CPause()
{
}

//=================================
//������
//=================================
HRESULT CPause::Init(void)
{
	//�g�������
	m_pBG = CBG::Create(PRIORITY_UI);
	m_pPolygon = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 90.0f, 0.0f), CManager::VEC3_ZERO, 600.0f, 180.0f, PRIORITY_PAUSE);
	m_pContinue = CButton2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 270.0f, 0.0f), CManager::VEC3_ZERO, 600.0f, 180.0f, PRIORITY_PAUSE);
	m_pRestart = CButton2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 450.0f, 0.0f), CManager::VEC3_ZERO, 600.0f, 180.0f, PRIORITY_PAUSE);
	m_pExit = CButton2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 630.0f, 0.0f), CManager::VEC3_ZERO, 600.0f, 180.0f, PRIORITY_PAUSE);
	m_pScreenShot = CButton2D::Create(D3DXVECTOR3(SCREEN_WIDTH - 80.0f, 80.0f, 0.0f), CManager::VEC3_ZERO, 160.0f, 160.0f, PRIORITY_PAUSE);

	//�e�N�X�`���\��\��i�Ȃ��e�N�X�`���͂��炩����preload�œǂݍ��񂾂��̂Ƃ���j
	CTexture* pTexture = CManager::GetTexture();
	m_pBG->BindTexture(-1);
	m_pBG->SetCol(D3DXCOLOR(1.0f,1.0f,1.0f,0.5f));
	m_pPolygon->BindTexture(CTexture::PRELOAD_PAUSE);
	m_pContinue->BindTexture(CTexture::PRELOAD_PAUSEBUTTON_01);
	m_pRestart->BindTexture(CTexture::PRELOAD_PAUSEBUTTON_02);
	m_pExit->BindTexture(CTexture::PRELOAD_PAUSEBUTTON_03);
	m_pScreenShot->BindTexture(CTexture::PRELOAD_PAUSEBUTTON_04);

	return S_OK;
}

//=================================
//�I��
//=================================
void CPause::Uninit(void)
{
	if (m_pBG != nullptr)
	{
		m_pBG->Uninit();
		m_pBG = nullptr;
	}
	if (m_pPolygon != nullptr)
	{
		m_pPolygon->Uninit();
		m_pPolygon = nullptr;
	}
	if (m_pContinue != nullptr)
	{
		m_pContinue->Uninit();
		m_pContinue = nullptr;
	}
	if (m_pRestart != nullptr)
	{
		m_pRestart->Uninit();
		m_pRestart = nullptr;
	}
	if (m_pExit != nullptr)
	{
		m_pExit->Uninit();
		m_pExit = nullptr;
	}
	if (m_pScreenShot != nullptr)
	{
		m_pScreenShot->Uninit();
		m_pScreenShot = nullptr;
	}
}

//=================================
//�X�V
//=================================
void CPause::Update(void)
{
	CSound* pSound = CManager::GetSound();

	//�{�^���ނ̓����_���[�̍X�V��~�ɂ��蓮�ōX�V����
	m_pContinue->Update();
	m_pRestart->Update();
	m_pExit->Update();
	m_pScreenShot->Update();

	//�X�N�V�����[�h���m�F
	if (m_bScreenShotMode == false)
	{//���ʂɕ`��
		//�{�^���ɉ���������
		if (m_pContinue->IsClickTrigger() == true)
		{//�Q�[���ɖ߂�
			ReleaseSome();
			CManager::SetPause(false);
			pSound->Play(CSound::SOUND_LABEL_SE_BUTTON);
		}
		else if (m_pRestart->IsClickTrigger() == true)
		{//���X�^�[�g
			CFade::Create(CScene::MODE_GAME);
			CManager::SetPause(false);
			pSound->Play(CSound::SOUND_LABEL_SE_BUTTON);
		}
		else if (m_pExit->IsClickTrigger() == true)
		{//�I��
			CFade::Create(CScene::MODE_TITLE);
			CManager::SetPause(false);
			pSound->Play(CSound::SOUND_LABEL_SE_BUTTON);
		}
		else if (m_pScreenShot->IsClickTrigger() == true)
		{//�X�N�V�����[�h
			m_bScreenShotMode = true;

			//��������\������Ă�������
			m_pBG->SetEnable(false);
			m_pPolygon->SetEnable(false);
			m_pContinue->SetEnable(false);
			m_pRestart->SetEnable(false);
			m_pExit->SetEnable(false);
			m_pScreenShot->SetEnable(false);

			pSound->Play(CSound::SOUND_LABEL_SE_BUTTON);
		}
	}
	else
	{//�X�N�V�����[�h
		CInputMouse* pMouse = CManager::GetInputMouse();	//�}�E�X�擾

		if (pMouse->GetTrigger(MOUSE_CLICK_LEFT) == true)
		{//���N���b�N�����ꂽ
			m_bScreenShotMode = false;	//�X�N�V�����[�h�I��

			//�L����
			m_pBG->SetEnable(true);
			m_pPolygon->SetEnable(true);
			m_pContinue->SetEnable(true);
			m_pRestart->SetEnable(true);
			m_pExit->SetEnable(true);
			m_pScreenShot->SetEnable(true);

			pSound->Play(CSound::SOUND_LABEL_SE_BUTTON);
		}
	}
}

//=================================
//�`��
//=================================
void CPause::Draw(void)
{
	//CObject��e�ɂ��Ă��邩�珟��ɕ`�悳���
}

//=================================
//�ꕔ�j��
//=================================
void CPause::ReleaseSome(void)
{
	//�g����������j��
	if (m_pBG != nullptr)
	{
		m_pBG->Uninit();
		m_pBG = nullptr;
	}
	
	if (m_pPolygon != nullptr)
	{
		m_pPolygon->Uninit();
		m_pPolygon = nullptr;
	}
	
	if (m_pContinue != nullptr)
	{
		m_pContinue->Uninit();
		m_pContinue = nullptr;
	}
	
	if (m_pRestart != nullptr)
	{
		m_pRestart->Uninit();
		m_pRestart = nullptr;
	}
	
	if (m_pExit != nullptr)
	{
		m_pExit->Uninit();
		m_pExit = nullptr;
	}
	
	if (m_pScreenShot != nullptr)
	{
		m_pScreenShot->Uninit();
		m_pScreenShot = nullptr;
	}
}
