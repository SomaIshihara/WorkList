//======================================================
//
//ランキングシーン[ranking.cpp]
//Author:石原颯馬
//
//======================================================
#include "ranking.h"
#include "texture.h"
#include "input.h"
#include "fade.h"
#include "object2D.h"
#include "score.h"
#include "sound.h"

//静的メンバ変数
const int CRanking::MAX_RANK = 5;

//=================================
//コンストラクタ
//=================================
CRanking::CRanking()
{
	m_pFade = nullptr;
	m_pPress = nullptr;
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
	int* pRankScore = new int[MAX_RANK];	//動的確保
	Load(pRankScore);

	//投げっぱオブジェ
	CObject2D* pObj2D = nullptr;
	CScore* pScore = nullptr;

	//背景
	CBG::Create()->BindTexture(CTexture::PRELOAD_27_BG_02);

	//ランキング文字
	pObj2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 108.0f, 0.0f), CManager::VEC3_ZERO, 400.0f, 96.0f, CObject::PRIORITY_05);
	pObj2D->BindTexture(CTexture::PRELOAD_09_RANKSTR);

	//順位
	for (int cnt = 0; cnt < MAX_RANK; cnt++)
	{
		//文字
		pObj2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 104.0f, 240.0f + (72.0f * cnt), 0.0f), CManager::VEC3_ZERO, 104.0f, 48.0f, CObject::PRIORITY_05);
		pObj2D->BindTexture(CTexture::PRELOAD_10_RANK_01 + cnt);

		//数字
		pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 156.0f, 240.0f + (72.0f * cnt), 0.0f), CManager::VEC3_ZERO, 32.0f, 48.0f);
		pScore->BindTexture(CTexture::PRELOAD_03_NUMBER);
		pScore->Set(pRankScore[cnt]);
	}

	//戻る文字
	m_pPress = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 636.0f, 0.0f), CManager::VEC3_ZERO, 560.0f, 48.0f, CObject::PRIORITY_05);
	m_pPress->BindTexture(CTexture::PRELOAD_15_SCENETITLEKB);

	delete[] pRankScore;	//スコア破棄

	return S_OK;
}

//=================================
//終了
//=================================
void CRanking::Uninit(void)
{
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

	if (pGamepad != nullptr && pGamepad->IsConnect() == true)
	{//ゲームパッド接続
		m_pPress->BindTexture(CTexture::PRELOAD_16_SCENETITLEGP);

		if (pGamepad->GetTrigger(XINPUT_GAMEPAD_A) == true)
		{
			bPush = true;
		}
	}
	else
	{//未接続
		m_pPress->BindTexture(CTexture::PRELOAD_15_SCENETITLEKB);

		if (pKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			bPush = true;
		}
	}

	if(bPush == true && m_pFade == nullptr)
	{
		m_pFade = CFade::Create(CScene::MODE_TITLE);

		//SE再生
		CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
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
void CRanking::Set(const int nScore)
{
	int* pRanking = new int[MAX_RANK];	//一応静的constも変数なので
													//ランキング読み込み
	Load(pRanking);

	//ソート
	if (pRanking[MAX_RANK - 1] < nScore)
	{//表示できる中で一番低い順位に入るか
		pRanking[MAX_RANK - 1] = nScore;	//とりあえず入れる

		for (int cnt = MAX_RANK - 1; cnt > 0; cnt--)
		{
			if (pRanking[cnt] > pRanking[cnt - 1])
			{//入れ替え
				int nTemp = pRanking[cnt - 1];
				pRanking[cnt - 1] = pRanking[cnt];
				pRanking[cnt] = nTemp;
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
void CRanking::Load(int* pRanking)
{
	FILE* pFile = nullptr;
	pFile = fopen("data\\ranking.bin", "rb");

	if (pFile != nullptr)
	{//ランキングファイルがある（読み込み）
		fread(&pRanking[0], sizeof(int), MAX_RANK, pFile);
		fclose(pFile);	//閉じる
	}
	else
	{//ランキングファイルがない（新規作成）
		for (int cnt = 0; cnt < MAX_RANK; cnt++)
		{
			pRanking[cnt] = 0;	//とりあえず0で埋める
		}
		Save(pRanking);
	}
}

//=================================
//ランキング書き込み
//=================================
void CRanking::Save(int* pRanking)
{
	FILE* pFile = nullptr;
	pFile = fopen("data\\ranking.bin", "wb");

	assert(("書き込みモードで開けなかったよ！奇跡だね！", pFile != nullptr));

	//開けた体で進める
	fwrite(pRanking, sizeof(int), MAX_RANK, pFile);	//書き込み

	fclose(pFile);	//閉じる
}
