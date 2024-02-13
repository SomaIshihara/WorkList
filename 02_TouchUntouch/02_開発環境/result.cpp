//======================================================
//
//リザルトシーン[result.cpp]
//Author:石原颯馬
//
//======================================================
#include "manager.h"
#include "result.h"
#include "ranking.h"
#include "timer.h"
#include "score.h"
#include "fade.h"
#include "input.h"
#include "texture.h"
#include "sound.h"

//静的メンバ変数
const int CResult::PLAYSOUND_COUNTER = 4;

//=================================
//コンストラクタ
//=================================
CResult::CResult()
{
	m_pTimer = nullptr;
	m_pBonus = nullptr;
	m_pScore = nullptr;
	m_pPress = nullptr;
	m_pFade = nullptr;
	m_nConter = 0;
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
	//文字背景（投げっぱなし）
	CObject2D* pObj = CObject2D::Create(CManager::SCREEN_CENTER, CManager::VEC3_ZERO, 570.0f, 336.0f, CObject::PRIORITY_05);
	pObj->SetCol(D3DXCOLOR(0.66f, 0.5f, 0.75f, 1.0f));
	pObj->BindTexture(-1);

	//時間（数字）
	m_pTimer = CTimer::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 130.0f, 240.0f, 0.0f), CManager::VEC3_ZERO, 32.0f, 48.0f);
	m_pTimer->Set(0, CTimer::COUNT_DOWN);	//初期値だが、Createで変更がされる
	m_pTimer->Stop();
	m_pTimer->BindTexture(CTexture::PRELOAD_03_NUMBER);
	//時間（文字）
	pObj = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 74.0f, 240.0f, 0.0f), CManager::VEC3_ZERO, 168.0f, 48.0f, CObject::PRIORITY_05);
	pObj->BindTexture(CTexture::PRELOAD_04_TIMERSTR);

	//ボーナス（数字）
	m_pBonus = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 192.0f, 288.0f, 0.0f), CManager::VEC3_ZERO, 32.0f, 48.0f);
	m_pBonus->Set(0);
	m_pBonus->BindTexture(CTexture::PRELOAD_03_NUMBER);
	//ボーナス（文字）
	pObj = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 108.0f, 288.0f, 0.0f), CManager::VEC3_ZERO, 168.0f, 48.0f, CObject::PRIORITY_05);
	pObj->BindTexture(CTexture::PRELOAD_06_BONUSSTR);

	//最終スコア（数字）
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 192.0f, 384.0f, 0.0f), CManager::VEC3_ZERO, 32.0f, 48.0f);
	m_pScore->Set(0);	//初期値だが、Createで変更がされる
	m_pScore->BindTexture(CTexture::PRELOAD_03_NUMBER);
	//最終スコア（文字）
	pObj = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 108.0f, 384.0f, 0.0f), CManager::VEC3_ZERO, 168.0f, 48.0f, CObject::PRIORITY_05);
	pObj->BindTexture(CTexture::PRELOAD_05_SCORESTR);

	//遷移文字
	m_pPress = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 480.0f, 0.0f), CManager::VEC3_ZERO, 560.0f, 48.0f, CObject::PRIORITY_05);
	m_pPress->BindTexture(CTexture::PRELOAD_07_SCENERANKKB);

	return S_OK;
}

//=================================
//終了
//=================================
void CResult::Uninit(void)
{
	
}

//=================================
//更新
//=================================
void CResult::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamePad* pGamepad = CManager::GetInstance()->GetInputGamePad();

	m_nConter++;
	
	if (m_pTimer->GetTime() > 0)
	{//時間を減らしてボーナス加算
		m_pTimer->Add(-1);
		m_pBonus->Add(100);

		if (m_nConter >= PLAYSOUND_COUNTER)
		{
			m_nConter = 0;
			//SE再生
			CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_ITEM);
		}
	}//↓は時間が0になったら実行
	else if (m_pBonus->GetScore() > 0)
	{//ボーナスから最終スコアに移動
		m_pBonus->Add(-100);
		m_pScore->Add(100);

		if (m_nConter >= PLAYSOUND_COUNTER)
		{
			m_nConter = 0;
			//SE再生
			CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_ITEM);
		}
	}//下はボーナス移動完了後実行
	else
	{//移動しきった
		bool bPush = false;
		if (pGamepad != nullptr && pGamepad->IsConnect() == true)
		{//ゲームパッド操作
			if (pGamepad->GetTrigger(XINPUT_GAMEPAD_A) == true)
			{
				bPush = true;
			}
		}
		else if (pKeyboard->GetTrigger(DIK_RETURN) == true)
		{//キーボード操作
			bPush = true;
		}

		if (bPush == true && m_pFade == nullptr)
		{
			CRanking::Set(m_pScore->GetScore());
			m_pFade = CFade::Create(CScene::MODE_RANKING);

			//SE再生
			CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
		}
	}

	if (pGamepad != nullptr && pGamepad->IsConnect() == true)
	{//ゲームパッド文字切替
		m_pPress->BindTexture(CTexture::PRELOAD_08_SCENERANKGP);
	}
	else
	{//キーボード文字切替
		m_pPress->BindTexture(CTexture::PRELOAD_07_SCENERANKKB);
	}
}

//=================================
//描画
//=================================
void CResult::Draw(void)
{
	//勝手にやってくれる
}

//=================================
//生成
//=================================
CResult* CResult::Create(const int nTimer, const int nScore)
{
	CResult* pResult = nullptr;

	if (pResult == nullptr)
	{
		//オブジェクト2Dの生成
		pResult = new CResult;

		//初期化
		pResult->Init();

		//データ設定
		pResult->m_pTimer->Set(nTimer, CTimer::COUNT_DOWN);
		pResult->m_pTimer->Stop();
		pResult->m_pScore->Set(nScore);
		
		return pResult;
	}
	else
	{
		return nullptr;
	}
}
