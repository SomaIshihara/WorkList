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
#include "fade.h"
#include "sound.h"

//=================================
//�R���X�g���N�^
//=================================
CPause::CPause()
{
	m_pBG = nullptr;
	m_pPauseStr = nullptr;

	for (int cnt = 0; cnt < MODE_MAX; cnt++)
	{
		m_apSelect[cnt] = nullptr;
	}

	m_bScreenShot = false;
	m_aStickFrag[0] = 0;
	m_aStickFrag[1] = 0;
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
	//�w�i
	m_pBG = CBG::Create(CObject::PRIORITY_05);
	m_pBG->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
	m_pBG->BindTexture(-1);

	//����
	m_pPauseStr = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 90.0f, 0.0f), CManager::VEC3_ZERO, 608.0f, 162.0f, CObject::PRIORITY_05);
	m_pPauseStr->BindTexture(CTexture::PRELOAD_21_PAUSE_STR);

	//�I��
	for (int cnt = 0; cnt < MODE_MAX - 1; cnt++)
	{
		m_apSelect[cnt] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 270.0f + (180.0f * cnt), 0.0f), CManager::VEC3_ZERO, 584.0f, 126.0f, CObject::PRIORITY_05);
		m_apSelect[cnt]->BindTexture(CTexture::PRELOAD_22_PAUSE_RESUME + cnt);
	}

	//�X�N�V�����̂ݕʂ̂Ƃ���ɒu��
	m_apSelect[MODE_SCREENSHOT] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - 131.0f, 114.0f, 0.0f), CManager::VEC3_ZERO, 132.5f, 100.0f, CObject::PRIORITY_05);
	m_apSelect[MODE_SCREENSHOT]->BindTexture(CTexture::PRELOAD_25_PAUSE_SCREENSHOT);

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
	if (m_pPauseStr != nullptr)
	{
		m_pPauseStr->Uninit();
		m_pPauseStr = nullptr;
	}

	//�I��
	for (int cnt = 0; cnt < MODE_MAX; cnt++)
	{
		if (m_apSelect[cnt] != nullptr)
		{
			m_apSelect[cnt]->Uninit();
			m_apSelect[cnt] = nullptr;
		}
	}
}

//=================================
//�X�V
//=================================
void CPause::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamePad* pGamepad = CManager::GetInstance()->GetInputGamePad();

	if (pGamepad != nullptr && pGamepad->IsConnect() == true)
	{//�Q�[���p�b�h
		//�i�\���j
		if (pGamepad->GetTrigger(XINPUT_GAMEPAD_DPAD_UP) == true)
		{//��i-�j
			m_mode = (MODE)(((m_mode + MODE_MAX) - 1) % MODE_MAX);
		}
		else if (pGamepad->GetTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true)
		{//���i+�j
			m_mode = (MODE)(((m_mode + MODE_MAX) + 1) % MODE_MAX);
		}
		else if (m_mode != MODE_SCREENSHOT && pGamepad->GetTrigger(XINPUT_GAMEPAD_DPAD_RIGHT) == true)
		{//���i�X�N�V�����[�h�ȊO�̎��X�N�V�����[�h�j
			m_mode = MODE_SCREENSHOT;
		}
		else if (m_mode == MODE_SCREENSHOT && pGamepad->GetTrigger(XINPUT_GAMEPAD_DPAD_LEFT) == true)
		{//���i�X�N�V�����[�h���Q�[���ɖ߂�j
			m_mode = MODE_RESUME;
		}

		//�X�e�B�b�N
		SHORT nStickX = pGamepad->GetLStickX();
		SHORT nStickY = pGamepad->GetLStickY();

		//�X�e�B�b�N���|����ĂȂ��Ƃ��͕����𒆉��ɂ���
		if (nStickX == 0)
		{
			m_aStickFrag[0] = 0;	//����
		}
		if (nStickY == 0)
		{
			m_aStickFrag[1] = 0;	//����
		}

		if (fabsf(nStickX) > fabsf(nStickY))
		{//X�����D��
			if (m_aStickFrag[0] <= 0 && nStickX > 0)
			{//�E�i�X�N�V�����[�h�ȊO�̎��X�N�V�����[�h�j
				m_mode = MODE_SCREENSHOT;
				m_aStickFrag[0] = 1;	//+����
			}
			else if (m_aStickFrag[0] >= 0 && nStickX < 0)
			{//���i�X�N�V�����[�h���Q�[���ɖ߂�j
				m_mode = MODE_RESUME;
				m_aStickFrag[0] = -1;	//-����
			}
		}
		else if (fabsf(nStickX) < fabsf(nStickY))
		{//Y�����D��
			if (m_aStickFrag[1] <= 0 && nStickY > 0)
			{//��i-�j
				m_mode = (MODE)(((m_mode + MODE_MAX) - 1) % MODE_MAX);
				m_aStickFrag[1] = 1;	//+����
			}
			else if (m_aStickFrag[1] >= 0 && nStickY < 0)
			{//���i+�j
				m_mode = (MODE)(((m_mode + MODE_MAX) + 1) % MODE_MAX);
				m_aStickFrag[1] = -1;	//-����
			}
		}
	}
	else
	{//�L�[�{�[�h
		//�ړ�
		if (pKeyboard->GetTrigger(DIK_W) == true)
		{//��i-�j
			m_mode = (MODE)(((m_mode + MODE_MAX) - 1) % MODE_MAX);
		}
		else if (pKeyboard->GetTrigger(DIK_S) == true)
		{//���i+�j
			m_mode = (MODE)(((m_mode + MODE_MAX) + 1) % MODE_MAX);
		}
		else if (m_mode != MODE_SCREENSHOT && pKeyboard->GetTrigger(DIK_D) == true)
		{//�E�i�X�N�V�����[�h�ȊO�̎��X�N�V�����[�h�j
			m_mode = MODE_SCREENSHOT;
		}
		else if (m_mode == MODE_SCREENSHOT && pKeyboard->GetTrigger(DIK_A) == true)
		{//���i�X�N�V�����[�h���Q�[���ɖ߂�j
			m_mode = MODE_RESUME;
		}
	}

	if (m_bScreenShot == false)
	{//�ʏ�
		if (pGamepad != nullptr && pGamepad->GetTrigger(XINPUT_GAMEPAD_A) == true)
		{
			Select();
		}
		else if (pKeyboard != nullptr && pKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			Select();
		}

		//�펞�\�����͕s����
		m_pBG->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
		m_pPauseStr->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		//�������񂷂ׂĔ�����
		for (int cnt = 0; cnt < MODE_MAX; cnt++)
		{
			m_apSelect[cnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}

		//�I������Ă���Ƃ��낾�����邭
		m_apSelect[m_mode]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{//�X�N�V�����[�h
		//�|�[�Y�Ŏg������ׂē���
		m_pBG->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		m_pPauseStr->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		for (int cnt = 0; cnt < MODE_MAX; cnt++)
		{
			m_apSelect[cnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}

		//�X�N�V�����[�h����
		if (pGamepad != nullptr && pGamepad->GetTrigger(XINPUT_GAMEPAD_A) == true)
		{
			m_bScreenShot = false;
		}
		else if (pKeyboard != nullptr && pKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			m_bScreenShot = false;
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
//�I�����Ď��s
//=================================
void CPause::Select(void)
{
	switch (m_mode)
	{
	case CPause::MODE_RESUME:
		CManager::GetInstance()->SetEnableUpdate(true);
		break;
	case CPause::MODE_RESTART:
		CManager::GetInstance()->SetEnableUpdate(true);
		CFade::Create(CScene::MODE_GAME);
		break;
	case CPause::MODE_EXIT:
		CManager::GetInstance()->SetEnableUpdate(true);
		CFade::Create(CScene::MODE_TITLE);
		break;
	case CPause::MODE_SCREENSHOT:
		m_bScreenShot = true;
		break;
	default:
		break;
	}
}
