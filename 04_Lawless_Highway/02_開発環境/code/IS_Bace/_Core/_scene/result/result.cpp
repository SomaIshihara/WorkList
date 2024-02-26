//======================================================
//
//リザルトシーン[result.cpp]
//Author:石原颯馬
//
//======================================================
#include "result.h"
#include "../../../../main.h"
#include "../pause/pause.h"
#include "../result/result.h"
#include "../ranking/ranking.h"
#include "../../manager/manager.h"
#include "../../texture/texture.h"
#include "../../camera/camera.h"
#include "../../sound/sound.h"
#include "../../_object/object_empty/object.h"
#include "../../input/input.h"
#include "../../utility/Utility.h"
#include "../../../_Expansion/fade/fade.h"
#include "../../../_Expansion/timer/timer.h"

//静的メンバ
CResult::RESULT CResult::m_result = CResult::RESULT::SUCCESS;
int CResult::m_nTime = 0;
int CResult::m_nCounter = 0;

//=================================
//コンストラクタ
//=================================
CResult::CResult()
{
	m_pPause = nullptr;
	m_pFade = nullptr;
	m_pResult = nullptr;
	m_pTimer = nullptr;
	m_pStart = nullptr;
}

//=================================
//デストラクタ
//=================================
CResult::~CResult()
{
}

//=================================
//初期化
//=================================
HRESULT CResult::Init(void)
{
	//テキスト
	m_pResult = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.325f, 0.0f), IS_Utility::VEC3_ZERO, 480.0f, 96.0f);
	m_pResult->BindTexture(CTexture::PRELOAD::PRELOAD_13_RESULT_SUCCESS);

	//時間
	m_pTimer = CTimerMSmS::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.55f, 0.0f), IS_Utility::VEC3_ZERO, 72.0f, 96.0f);
	m_pTimer->Set(m_nTime, m_nCounter, CTimer::COUNT::COUNT_DOWN);
	m_pTimer->BindTexture(CTexture::PRELOAD::PRELOAD_04_TIMER_NUMBER);
	m_pTimer->BindSymbolTexture(CTexture::PRELOAD::PRELOAD_05_TIMER_SYMBOL);

	//スタート文字
	m_pStart = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.9f, 0.0f), IS_Utility::VEC3_ZERO, 756.0f, 99.0f);
	m_pStart->BindTexture(CTexture::PRELOAD::PRELOAD_01_PUSHANYBUTTON);

	return S_OK;
}

//=================================
//終了
//=================================
void CResult::Uninit(void)
{
	//オブジェ全破棄
	for (int cnt = 0; cnt < CObject::PRIORITY_FADE; cnt++)
	{
		CObject::ReleaseAll(cnt);
	}

	//音止める
	CManager::GetInstance()->GetSound()->Stop();
}

//=================================
//更新
//=================================
void CResult::Update(void)
{
	CManager* pIns = CManager::GetInstance();
	CInputKeyboard* pKeyboard = pIns->GetInputKeyboard();
	CInputGamePad* pGamepad = pIns->GetInputGamePad();
	bool bPush = false;

	if (pGamepad != nullptr && pGamepad->GetTrigger(0xffff) == true)
	{
		bPush = true;
	}
	else
	{
		for (int cnt = 0; cnt < KEY_NUM; cnt++)
		{
			if (pKeyboard->GetTrigger(cnt))
			{
				bPush = true;
				break;
			}
		}
	}

	if (m_pFade == nullptr && bPush == true)
	{//スペース押された
		m_pFade = CFade::Create(CScene::MODE::MODE_RANKING);
	}
}

//=================================
//描画
//=================================
void CResult::Draw(void)
{
	//普段はすべてCObjectクラス継承してるものが動いているので自動描画
	//ポーズの中身もすべてCObjectクラス継承してるので自動描画
	//よってここですることはない
}

//=================================
//リザルト設定
//=================================
void CResult::Set(const RESULT result, const int ntime, const int nCounter)
{
	m_result = result;
	m_nTime = ntime;
	m_nCounter = nCounter;
}
