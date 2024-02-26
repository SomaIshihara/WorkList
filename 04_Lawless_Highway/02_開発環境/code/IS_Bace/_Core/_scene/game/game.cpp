//======================================================
//
//ゲームシーン[game.cpp]
//Author:石原颯馬
//
//======================================================
#include "game.h"
#include "../../../../main.h"
#include "../pause/pause.h"
#include "../result/result.h"
#include "../ranking/ranking.h"
#include "../../manager/manager.h"
#include "../../texture/texture.h"
#include "../../utility/Utility.h"
#include "../../utility/Utility_Vector.h"
#include "../../camera/camera.h"
#include "../../sound/sound.h"
#include "../../_object/object_empty/object.h"
#include "../../input/input.h"
#include "../../../../Addition/imgcontroller/imgcontroller.h"
#include "../../../_Expansion/fade/fade.h"
#include "../../file(legacy)/file.h"

#include "../../../../Addition/player/player.h"
#include "../../../_Expansion/meshfield/meshField.h"
#include "../../../../Addition/meshroad/meshroad.h"
#include "../../../_Expansion/meshsky/meshsky.h"
#include "../../../_Expansion/timer/timer.h"
#include "../../../_Expansion/gauge/gauge.h"
#include "../../../../Addition/goal/goal.h"
#include "../../../../Addition/tutorialobj/tutorialobj.h"
#include "../../../../Addition/object2dmap/object2DMap.h"
#include "../../../../Addition/speedmeter/speedmeter.h"

#include "../../../../ISMD_IO/objloader/objloader.h"

namespace
{
	int TIME_LIMIT = 90;
	float BGM_FADEOUT_SPEED = 0.01f;
}

//=================================
//コンストラクタ
//=================================
CGame::CGame()
{
	m_pPause = nullptr;
	m_pFade = nullptr;
	m_pTimer = nullptr;
	m_pGauge = nullptr;
	m_pPlayer = nullptr;
	m_bUseGP = false;
	m_pConfig = nullptr;
	m_fBGMVolume = 0.0f;
}

//=================================
//デストラクタ
//=================================
CGame::~CGame()
{
}

//=================================
//初期化
//=================================
HRESULT CGame::Init(void)
{
	//カメラリセット
	CManager::GetInstance()->CManager::GetInstance()->GetCamera()->ResetPos();
	CManager::GetInstance()->CManager::GetInstance()->GetCamera()->SetLength(100.0f);

	//先に配置
	m_pGauge = CGauge::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 110.0f, 0.0f), IS_Utility::VEC3_ZERO, 256.0f, 24.0f);
	m_pGauge->SetRate(1.0f);
	CObject2DMap* pMap = CObject2DMap::Create(D3DXVECTOR3(116.0f, SCREEN_HEIGHT - 116.0f, 0.0f), IS_Utility::VEC3_ZERO, 200.0f, 200.0f);
	CSpeedMeter* pSpeedMeter = CSpeedMeter::Create(D3DXVECTOR3(SCREEN_WIDTH - 116.0f, SCREEN_HEIGHT - 116.0f, 0.0f), 200.0f);

	//プレイヤー配置
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(22485.0f, -378.0f, -1845.0f), m_pGauge, pMap, pSpeedMeter);
	m_pPlayer->SetRot(D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f));
	m_pPlayer->SetState(CPlayer::STATE::STATE_TUTORIAL);

	//オブジェクト配置
	//道路
	LoadRoadScriptFile("data//road_data_main.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_sub.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_TGConnect.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_dummy.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_tutorial.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);

	//地面
	CMeshField::Create(D3DXVECTOR3(0.0f, -381.5f, 6000.0f), IS_Utility::VEC3_ZERO, 2048.0f, 2048.0f, 24, 24)
		->BindTexture(CTexture::PRELOAD_34_FIELD_LEAF);

	//UI
	m_pTimer = CTimerMSmS::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 32.0f, 0.0f), IS_Utility::VEC3_ZERO, 48.0f, 64.0f);
	m_pTimer->CTimer::Set(0, CTimer::COUNT::COUNT_UP);
	m_pTimer->BindTexture(CTexture::PRELOAD::PRELOAD_04_TIMER_NUMBER);
	m_pTimer->BindSymbolTexture(CTexture::PRELOAD::PRELOAD_05_TIMER_SYMBOL);

	//操作
	m_pConfig = CObject2D::Create(D3DXVECTOR3(1173.0f, 76.5f, 0.0f), IS_Utility::VEC3_ZERO, 214.0f, 153.0f, CObject::PRIORITY_05);
	m_pConfig->BindTexture(CTexture::PRELOAD_23_CONFIG_KB);

	//チュートリアルオブジェクト
	CTutorialObj::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 44.5f, 0.0f), IS_Utility::VEC3_ZERO, 313.0f, 89.0f, m_pTimer, m_pPlayer);

	//メッシュ空
	CMeshSky::Create(D3DXVECTOR3(6000.0f,0.0f,4000.0f), IS_Utility::VEC3_ZERO, 18000.0f, 12, 12);
	m_pGoal = CGoal::Create(D3DXVECTOR3(-1500.0f, 13.0f, 16500.0f), 600.0f, 600.0f, 100.0f);

	//BGM鳴らす
	m_fBGMVolume = 1.0f;
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_GAME);

	return S_OK;
}

//=================================
//終了
//=================================
void CGame::Uninit(void)
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
void CGame::Update(void)
{
	CManager* pIns = CManager::GetInstance();
	CSound* pSound = pIns->GetSound();
	CInputKeyboard* pKeyboard = pIns->GetInputKeyboard();
	CInputGamePad* pGamepad = pIns->GetInputGamePad();

	//コントローラ設定
	if (m_bUseGP == false && pGamepad->IsConnect() == true)
	{//キーボードモード中にゲームパッド接続
		m_pPlayer->SetController(new CImgController(new CControllerGP));
		m_pConfig->BindTexture(CTexture::PRELOAD_24_CONFIG_GP);
	}
	else if (pGamepad->IsConnect() == false)
	{//ゲームパッドモード中にゲームパッド切断
		m_pPlayer->SetController(new CImgController(new CControllerKB));
		m_pConfig->BindTexture(CTexture::PRELOAD_23_CONFIG_KB);
	}

	//ゴール処理
	if (m_pGoal->IsGoal() == true)
	{//ゴール範囲に入った
		if (m_bIsGoal == false)
		{//1回だけする処理
			m_bIsGoal = true;
			m_pPlayer->SetState(CPlayer::STATE::STATE_SYSTEM_GOAL);
			//値設定
			int nTime, nCounter;

			//時間取得
			m_pTimer->Stop();
			nTime = m_pTimer->GetTime();
			nCounter = m_pTimer->GetCounter();

			//既存タイマーの位置ずらし
			m_pTimer->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.55f, 0.0f));

			//ゲージを見えなくする
			m_pGauge->SetPos(D3DXVECTOR3(0.0f, -300.0f, 0.0f));

			//ランキングに設定
			CRanking::Set(CRanking::RankTimeMSmS(nTime, nCounter));

			//テキスト
			CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.325f, 0.0f),
				IS_Utility::VEC3_ZERO, 480.0f, 96.0f)->BindTexture(CTexture::PRELOAD::PRELOAD_13_RESULT_SUCCESS);

			//スタート文字
			CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.9f, 0.0f), IS_Utility::VEC3_ZERO, 756.0f, 99.0f)
				->BindTexture(CTexture::PRELOAD::PRELOAD_01_PUSHANYBUTTON);

			//ブレーキ音だけ鳴らしほかの車効果音は消す
			pSound->Stop(CSound::SOUND_LABEL_SE_RUN);
			pSound->Stop(CSound::SOUND_LABEL_SE_DRIFT);
			pSound->Play(CSound::SOUND_LABEL_SE_CLEARBRAKE);
		}

		//音小さくする
		m_fBGMVolume = IS_Utility::Clamp(m_fBGMVolume - BGM_FADEOUT_SPEED, 1.0f, 0.0f);
		pSound->SetVolume(CSound::SOUND_LABEL_BGM_GAME, m_fBGMVolume);

		//ボタン処理
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
		{//リザルト遷移
			m_pFade = CFade::Create(CScene::MODE::MODE_RANKING);
		}
	}
}

//=================================
//描画
//=================================
void CGame::Draw(void)
{
	//普段はすべてCObjectクラス継承してるものが動いているので自動描画
	//ポーズの中身もすべてCObjectクラス継承してるので自動描画
	//よってここですることはない
}