//==========================================
//
//���z�R���g���[��[imgcontroller.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "imgcontroller.h"
#include "../../IS_Bace/_Core/manager/manager.h"
#include "../../IS_Bace/_Core/input/input.h"

//************************************************
// �L�[�{�[�h����
//************************************************
//========================
//�n���h������
//========================
float CControllerKB::Handle(void)
{
	float handle = 0.0f;
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();
	if (pKeyboard != nullptr)
	{
		if (pKeyboard->GetPress(DIK_A) == true || pKeyboard->GetPress(DIK_LEFTARROW) == true)
		{
			handle = -1.0f;
		}
		if (pKeyboard->GetPress(DIK_D) == true || pKeyboard->GetPress(DIK_RIGHTARROW) == true)
		{
			handle = 1.0f;
		}
	}
	return handle;
}

//========================
//�u���[�L����
//========================
bool CControllerKB::Brake(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();
	if (pKeyboard != nullptr)
	{
		if (pKeyboard->GetPress(DIK_S) == true || pKeyboard->GetPress(DIK_DOWNARROW) == true)
		{
			return true;
		}
	}

	return false;
}

//========================
//�j�g������
//========================
bool CControllerKB::Nitro(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();
	if (pKeyboard != nullptr)
	{
		if (pKeyboard->GetPress(DIK_W) == true || pKeyboard->GetPress(DIK_UPARROW) == true)
		{
			return true;
		}
	}

	return false;
}

//************************************************
// �Q�[���p�b�h����
//************************************************
//========================
//�n���h������
//========================
float CControllerGP::Handle(void)
{
	CInputGamePad* pGamepad = CManager::GetInstance()->GetInputGamePad();
	if (pGamepad != nullptr)
	{
		return (float)pGamepad->GetLStickX() / CInputGamePad::STICK_MAX;
	}
	return 0.0f;
}

//========================
//�u���[�L����
//========================
bool CControllerGP::Brake(void)
{
	CInputGamePad* pGamepad = CManager::GetInstance()->GetInputGamePad();
	if (pGamepad != nullptr)
	{
		if (pGamepad->GetPress(XINPUT_GAMEPAD_RIGHT_SHOULDER) == true)
		{
			return true;
		}
	}

	return false;
}

//========================
//�j�g������
//========================
bool CControllerGP::Nitro(void)
{
	CInputGamePad* pGamepad = CManager::GetInstance()->GetInputGamePad();
	if (pGamepad != nullptr)
	{
		if (pGamepad->GetPress(XINPUT_GAMEPAD_A) == true)
		{
			return true;
		}
	}

	return false;
}