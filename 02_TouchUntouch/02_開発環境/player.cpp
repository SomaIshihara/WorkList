//======================================================
//
//プレイヤー処理[player.cpp]
//Author:石原颯馬
//
//======================================================
#include "player.h"
#include "manager.h"
#include "input.h"
#include "camera.h"
#include "sound.h"

//=================================
//コンストラクタ
//=================================
CPlayer::CPlayer()
{

}

//=================================
//デストラクタ
//=================================
CPlayer::~CPlayer()
{}

//=================================
//初期化
//=================================
HRESULT CPlayer::Init(void)
{
	m_controllType = CCharacter::TYPE_A;
	return S_OK;
}

//=================================
//終了
//=================================
void CPlayer::Uninit(void)
{
	
}

//=================================
//更新
//=================================
void CPlayer::Update(void)
{
	if (m_bControlled == true)
	{//操作可能
		CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();	//キーボード取得
		CInputGamePad* pGamepad = CManager::GetInstance()->GetInputGamePad();		//ゲームパッド取得

		if (pGamepad != nullptr && pGamepad->IsConnect() == true)
		{//ゲームパッド接続
			//移動
			if (pGamepad->GetPress(XINPUT_GAMEPAD_DPAD_LEFT) == true || pGamepad->GetLStickX() < 0)
			{//Aキーが押されている
				m_nPressMove = DIK_A;
			}
			else if (pGamepad->GetPress(XINPUT_GAMEPAD_DPAD_RIGHT) == true || pGamepad->GetLStickX() > 0)
			{//Dキーが押されている
				m_nPressMove = DIK_D;
			}
			else
			{//何も押されていない
				m_nPressMove = 0;
			}

			//ジャンプ
			m_bPressJump = (pGamepad->GetTrigger(XINPUT_GAMEPAD_A) == true) ? true : false;

			//キャラ切替
			if (pGamepad->GetTrigger(XINPUT_GAMEPAD_X) == true)
			{
				m_controllType = (m_controllType == CCharacter::TYPE_A) ? CCharacter::TYPE_B : CCharacter::TYPE_A;

				//SE再生
				CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_CHANGE);
			}
		}
		else
		{//未接続
			//移動
			if (pKeyboard->GetPress(DIK_A) == true)
			{//Aキーが押されている
				m_nPressMove = DIK_A;
			}
			else if (pKeyboard->GetPress(DIK_D) == true)
			{//Dキーが押されている
				m_nPressMove = DIK_D;
			}
			else
			{//何も押されていない
				m_nPressMove = 0;
			}

			//ジャンプ
			m_bPressJump = (pKeyboard->GetTrigger(DIK_SPACE) == true) ? true : false;

			//キャラ切替
			if (pKeyboard->GetTrigger(DIK_S) == true)
			{
				m_controllType = (m_controllType == CCharacter::TYPE_A) ? CCharacter::TYPE_B : CCharacter::TYPE_A;

				//SE再生
				CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_CHANGE);
			}
		}
	}
	else
	{//不可能
		m_nPressMove = 0;
		m_bPressJump = false;
	}
}