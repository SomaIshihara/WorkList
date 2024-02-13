//======================================================
//
//ポーズ画面[game.cpp]
//Author:石原颯馬
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
//コンストラクタ
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
//デストラクタ
//=================================
CPause::~CPause()
{
}

//=================================
//初期化
//=================================
HRESULT CPause::Init(void)
{
	//背景
	m_pBG = CBG::Create(CObject::PRIORITY_05);
	m_pBG->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
	m_pBG->BindTexture(-1);

	//文字
	m_pPauseStr = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 90.0f, 0.0f), CManager::VEC3_ZERO, 608.0f, 162.0f, CObject::PRIORITY_05);
	m_pPauseStr->BindTexture(CTexture::PRELOAD_21_PAUSE_STR);

	//選択部
	for (int cnt = 0; cnt < MODE_MAX - 1; cnt++)
	{
		m_apSelect[cnt] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 270.0f + (180.0f * cnt), 0.0f), CManager::VEC3_ZERO, 584.0f, 126.0f, CObject::PRIORITY_05);
		m_apSelect[cnt]->BindTexture(CTexture::PRELOAD_22_PAUSE_RESUME + cnt);
	}

	//スクショ部のみ別のところに置く
	m_apSelect[MODE_SCREENSHOT] = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH - 131.0f, 114.0f, 0.0f), CManager::VEC3_ZERO, 132.5f, 100.0f, CObject::PRIORITY_05);
	m_apSelect[MODE_SCREENSHOT]->BindTexture(CTexture::PRELOAD_25_PAUSE_SCREENSHOT);

	return S_OK;
}

//=================================
//終了
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

	//選択部
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
//更新
//=================================
void CPause::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamePad* pGamepad = CManager::GetInstance()->GetInputGamePad();

	if (pGamepad != nullptr && pGamepad->IsConnect() == true)
	{//ゲームパッド
		//（十字）
		if (pGamepad->GetTrigger(XINPUT_GAMEPAD_DPAD_UP) == true)
		{//上（-）
			m_mode = (MODE)(((m_mode + MODE_MAX) - 1) % MODE_MAX);
		}
		else if (pGamepad->GetTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true)
		{//下（+）
			m_mode = (MODE)(((m_mode + MODE_MAX) + 1) % MODE_MAX);
		}
		else if (m_mode != MODE_SCREENSHOT && pGamepad->GetTrigger(XINPUT_GAMEPAD_DPAD_RIGHT) == true)
		{//横（スクショモード以外の時スクショモード）
			m_mode = MODE_SCREENSHOT;
		}
		else if (m_mode == MODE_SCREENSHOT && pGamepad->GetTrigger(XINPUT_GAMEPAD_DPAD_LEFT) == true)
		{//左（スクショモード時ゲームに戻る）
			m_mode = MODE_RESUME;
		}

		//スティック
		SHORT nStickX = pGamepad->GetLStickX();
		SHORT nStickY = pGamepad->GetLStickY();

		//スティックが倒されてないときは方向を中央にする
		if (nStickX == 0)
		{
			m_aStickFrag[0] = 0;	//中央
		}
		if (nStickY == 0)
		{
			m_aStickFrag[1] = 0;	//中央
		}

		if (fabsf(nStickX) > fabsf(nStickY))
		{//X方向優先
			if (m_aStickFrag[0] <= 0 && nStickX > 0)
			{//右（スクショモード以外の時スクショモード）
				m_mode = MODE_SCREENSHOT;
				m_aStickFrag[0] = 1;	//+方向
			}
			else if (m_aStickFrag[0] >= 0 && nStickX < 0)
			{//左（スクショモード時ゲームに戻る）
				m_mode = MODE_RESUME;
				m_aStickFrag[0] = -1;	//-方向
			}
		}
		else if (fabsf(nStickX) < fabsf(nStickY))
		{//Y方向優先
			if (m_aStickFrag[1] <= 0 && nStickY > 0)
			{//上（-）
				m_mode = (MODE)(((m_mode + MODE_MAX) - 1) % MODE_MAX);
				m_aStickFrag[1] = 1;	//+方向
			}
			else if (m_aStickFrag[1] >= 0 && nStickY < 0)
			{//下（+）
				m_mode = (MODE)(((m_mode + MODE_MAX) + 1) % MODE_MAX);
				m_aStickFrag[1] = -1;	//-方向
			}
		}
	}
	else
	{//キーボード
		//移動
		if (pKeyboard->GetTrigger(DIK_W) == true)
		{//上（-）
			m_mode = (MODE)(((m_mode + MODE_MAX) - 1) % MODE_MAX);
		}
		else if (pKeyboard->GetTrigger(DIK_S) == true)
		{//下（+）
			m_mode = (MODE)(((m_mode + MODE_MAX) + 1) % MODE_MAX);
		}
		else if (m_mode != MODE_SCREENSHOT && pKeyboard->GetTrigger(DIK_D) == true)
		{//右（スクショモード以外の時スクショモード）
			m_mode = MODE_SCREENSHOT;
		}
		else if (m_mode == MODE_SCREENSHOT && pKeyboard->GetTrigger(DIK_A) == true)
		{//左（スクショモード時ゲームに戻る）
			m_mode = MODE_RESUME;
		}
	}

	if (m_bScreenShot == false)
	{//通常
		if (pGamepad != nullptr && pGamepad->GetTrigger(XINPUT_GAMEPAD_A) == true)
		{
			Select();
		}
		else if (pKeyboard != nullptr && pKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			Select();
		}

		//常時表示部は不透明
		m_pBG->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
		m_pPauseStr->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		//いったんすべて半透明
		for (int cnt = 0; cnt < MODE_MAX; cnt++)
		{
			m_apSelect[cnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}

		//選択されているところだけ明るく
		m_apSelect[m_mode]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{//スクショモード
		//ポーズで使うやつすべて透明
		m_pBG->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		m_pPauseStr->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		for (int cnt = 0; cnt < MODE_MAX; cnt++)
		{
			m_apSelect[cnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}

		//スクショモード解除
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
//描画
//=================================
void CPause::Draw(void)
{
	//CObjectを親にしているから勝手に描画される
}

//=================================
//選択して実行
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
