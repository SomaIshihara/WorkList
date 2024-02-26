//==========================================
//
//仮想コントローラ[imgcontroller.cpp]
//Author:石原颯馬
//
//==========================================
#include "imgcontroller.h"
#include "../../IS_Bace/_Core/manager/manager.h"
#include "../../IS_Bace/_Core/input/input.h"

//************************************************
// キーボード入力
//************************************************
//========================
//ハンドル操作
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
//ブレーキ操作
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
//ニトロ操作
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
// ゲームパッド入力
//************************************************
//========================
//ハンドル操作
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
//ブレーキ操作
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
//ニトロ操作
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