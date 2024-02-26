//======================================================
//
//�|�[�Y���[game.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "pause.h"
#include "..\..\texture\texture.h"
#include "..\..\input\input.h"
#include "..\..\..\_Expansion\bg\bg.h"
#include "..\..\_object\object_2d\object2D.h"
#include "..\..\..\_Expansion\fade\fade.h"
#include "..\..\sound\sound.h"
#include "..\..\utility\Utility.h"

//=================================
//�R���X�g���N�^
//=================================
CPause::CPause()
{
	m_mode = MODE::MODE_RESUME;
	m_bScreenShot = false;
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
	return S_OK;
}

//=================================
//�I��
//=================================
void CPause::Uninit(void)
{
	
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
	}
	else
	{//�X�N�V�����[�h
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
		CFade::Create(CScene::MODE::MODE_GAME);
		break;
	case CPause::MODE_EXIT:
		CManager::GetInstance()->SetEnableUpdate(true);
		CFade::Create(CScene::MODE::MODE_TITLE);
		break;
	case CPause::MODE_SCREENSHOT:
		m_bScreenShot = true;
		break;
	default:
		break;
	}
}
