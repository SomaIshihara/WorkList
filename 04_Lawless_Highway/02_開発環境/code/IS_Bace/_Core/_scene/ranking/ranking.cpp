//======================================================
//
//ランキングシーン[ranking.cpp]
//Author:石原颯馬
//
//======================================================
#include "ranking.h"
#include "../../../../main.h"
#include "../../manager/manager.h"
#include "../../sound/sound.h"
#include "../../../_Expansion/timer/timer.h"
#include "../../input/input.h"
#include "../../../_Expansion/fade/fade.h"
#include "../../texture/texture.h"
#include "../../utility/Utility.h"
#include "../../../../Addition/meshroad/meshroad.h"
#include "../../../_Expansion/meshsky/meshsky.h"
#include "../../file(legacy)/file.h"
#include "../../camera/camera.h"

//静的メンバ変数
const int CRanking::MAX_RANK = 5;

//無名名前空間
namespace
{
	D3DXVECTOR3 pos1stRank = D3DXVECTOR3(328.0f, 180.0f, 0.0f);
	D3DXVECTOR3 pos1stTime = pos1stRank + D3DXVECTOR3(164.0f, 0.0f, 0.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(100.0f, 84.0f, 0.0f);
}

//=================================
//コンストラクタ
//=================================
CRanking::CRanking()
{
	m_pFade = nullptr;
}

//=================================
//デストラクタ
//=================================
CRanking::~CRanking()
{
}

//=================================
//初期化
//=================================
HRESULT CRanking::Init(void)
{
	//スコア値
	RankTimeMSmS* pRankScore = new RankTimeMSmS[MAX_RANK];	//動的確保
	Load(pRankScore);

	//ランキング文字
	CObject2D* pRanking = CObject2D::Create(D3DXVECTOR3(328.0f, 70.0f, 0.0f), IS_Utility::VEC3_ZERO, 360.0f, 96.0f, CObject::PRIORITY_05);
	pRanking->BindTexture(CTexture::PRELOAD::PRELOAD_15_RANKING_TEXT);

	//順位と時間配置
	for (int cnt = 0; cnt < MAX_RANK; cnt++)
	{
		//順位
		CObject2D* pRank = CObject2D::Create(pos1stRank + (move * (float)cnt), IS_Utility::VEC3_ZERO, 64.0f, 64.0f,CObject::PRIORITY_05);
		pRank->BindTexture(CTexture::PRELOAD::PRELOAD_16_1ST + cnt);

		//時間
		CTimerMSmS* pTimer = CTimerMSmS::Create(pos1stTime + (move * (float)cnt), IS_Utility::VEC3_ZERO, 32.0f, 64.0f);
		pTimer->BindTexture(CTexture::PRELOAD::PRELOAD_04_TIMER_NUMBER);
		pTimer->BindSymbolTexture(CTexture::PRELOAD::PRELOAD_05_TIMER_SYMBOL);
		pTimer->Set(pRankScore[cnt].nTime, pRankScore[cnt].nCounter, CTimer::COUNT::COUNT_DOWN);
	}

	//マップ配置
	//道路
	LoadRoadScriptFile("data//road_data_main.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_sub.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_TGConnect.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_dummy.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_tutorial.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);

	//地面
	CMeshField::Create(D3DXVECTOR3(0.0f, -381.5f, 6000.0f), IS_Utility::VEC3_ZERO, 2048.0f, 2048.0f, 24, 24)
		->BindTexture(CTexture::PRELOAD_34_FIELD_LEAF);

	//カメラ
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	pCamera->ResetPos();
	pCamera->SetPosR(D3DXVECTOR3(6000.0f, 100.0f, 5000.0f));
	pCamera->SetRot(D3DXVECTOR3(-0.05f * D3DX_PI, 0.3f * D3DX_PI, 0.0f));
	pCamera->SetLength(2000.0f);

	//スタート文字
	CObject2D* pStart = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.9f, 0.0f), IS_Utility::VEC3_ZERO, 756.0f, 99.0f, CObject::PRIORITY_05);
	pStart->BindTexture(CTexture::PRELOAD::PRELOAD_01_PUSHANYBUTTON);

	CMeshSky::Create(D3DXVECTOR3(0.0f, 0.0f, 4000.0f), IS_Utility::VEC3_ZERO, 14000.0f, 12, 12);

	//消す
	delete[] pRankScore;	//スコア破棄

	//BGM鳴らす
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_RANKING);

	return S_OK;
}

//=================================
//終了
//=================================
void CRanking::Uninit(void)
{
	//音停止
	CManager::GetInstance()->GetSound()->Stop();

	//オブジェ全破棄
	for (int cnt = 0; cnt < CObject::PRIORITY_FADE; cnt++)
	{
		CObject::ReleaseAll(cnt);
	}
}

//=================================
//更新
//=================================
void CRanking::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamePad* pGamepad = CManager::GetInstance()->GetInputGamePad();
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

	if(bPush == true && m_pFade == nullptr)
	{
		m_pFade = CFade::Create(CScene::MODE::MODE_TITLE);
	}
}

//=================================
//描画
//=================================
void CRanking::Draw(void)
{
}

//=================================
//ランキング設定
//=================================
void CRanking::Set(const RankTimeMSmS nTimer)
{
	//ランキング読み込み
	RankTimeMSmS* pRanking = new RankTimeMSmS[MAX_RANK];
	Load(pRanking);

	//ソート
	if (pRanking[MAX_RANK - 1].nTime > nTimer.nTime || 
		(pRanking[MAX_RANK - 1].nTime == nTimer.nTime && pRanking[MAX_RANK - 1].nCounter > nTimer.nCounter))
	{
		pRanking[MAX_RANK - 1] = nTimer;	//とりあえず入れる

		//ソート
		for (int cnt = MAX_RANK - 1; cnt > 0; cnt--)
		{
			if (pRanking[cnt].nTime < pRanking[cnt - 1].nTime ||
				(pRanking[cnt].nTime == pRanking[cnt - 1].nTime && pRanking[cnt].nCounter < pRanking[cnt - 1].nCounter))
			{//入れ替え
				RankTimeMSmS temp = pRanking[cnt - 1];
				pRanking[cnt - 1] = pRanking[cnt];
				pRanking[cnt] = temp;
			}
		}
	}

	//ランキング書き込み
	Save(pRanking);

	delete[] pRanking;	//破棄
}

//=================================
//ランキング読み込み
//=================================
void CRanking::Load(RankTimeMSmS* pRanking)
{
	FILE* pFile = nullptr;
	pFile = fopen("data//ranking.bin", "rb");

	if (pFile != nullptr)
	{//ランキングファイルがある（読み込み）
		fread(&pRanking[0], sizeof(RankTimeMSmS), MAX_RANK, pFile);
		fclose(pFile);	//閉じる
	}
	else
	{//ランキングファイルがない（新規作成）
		for (int cnt = 0; cnt < MAX_RANK; cnt++)
		{
			pRanking[cnt].nTime = 5940;	//とりあえず0で埋める
			pRanking[cnt].nCounter = 59;	//とりあえず0で埋める
		}
		Save(pRanking);
	}
}

//=================================
//ランキング書き込み
//=================================
void CRanking::Save(RankTimeMSmS* pRanking)
{
	FILE* pFile = nullptr;
	pFile = fopen("data//ranking.bin", "wb");

	assert(("書き込みモードで開けなかったよ！奇跡だね！", pFile != nullptr));

	//開けた体で進める
	fwrite(pRanking, sizeof(RankTimeMSmS), MAX_RANK, pFile);	//書き込み

	fclose(pFile);	//閉じる
}
