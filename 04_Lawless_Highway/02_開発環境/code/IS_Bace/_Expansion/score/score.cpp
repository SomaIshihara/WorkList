//======================================================
//
//スコア処理[score.cpp]
//Author:石原颯馬
//
//======================================================
#include "score.h"
#include "..\..\_Core\manager\manager.h"
#include "..\..\_Core\renderer\renderer.h"
#include "..\..\_Core\texture\texture.h"
#include "..\..\_Core\_object\object_empty\object.h"
#include "..\number\number.h"
#include "..\..\_Core\utility\Utility.h"

//マクロ
#define SCORE_INVISIBLE	(4)	//何桁分かを非表示にする

//=================================
//コンストラクタ（デフォルト）
//=================================
CScore::CScore(int nPriority) : CObject(nPriority)
{
	//値クリア
	m_pos = IS_Utility::VEC3_ZERO;
	m_rot = IS_Utility::VEC3_ZERO;
	m_nScore = 0;
}

//=================================
//デストラクタ
//=================================
CScore::~CScore()
{
}

//=================================
//初期化
//=================================
HRESULT CScore::Init(void)
{
	for (int cnt = 0; cnt < SCORE_DIGIT; cnt++)
	{//数字オブジェクト初期化
		m_pNumber[cnt] = nullptr;
	}

	//スコア設定
	Set(0);

	//できた
	return S_OK;
}

//=================================
//終了
//=================================
void CScore::Uninit(void)
{
	for (int cnt = 0; cnt < SCORE_DIGIT; cnt++)
	{//数字オブジェクト終了
		if (m_pNumber[cnt] != nullptr)
		{//大丈夫。中身はある
			m_pNumber[cnt]->Uninit();
		}
	}

	//スコアオブジェクト破棄
	Release();
}

//=================================
//更新
//=================================
void CScore::Update(void)
{
	for (int cnt = 0; cnt < SCORE_DIGIT; cnt++)
	{//数字オブジェクト更新
		if (m_pNumber[cnt] != nullptr)
		{//大丈夫。中身はある
			//オブジェクト2Dの更新処理
			m_pNumber[cnt]->Update();
		}
	}

	//数字分割
	CutNumber();
}

//=================================
//描画
//=================================
void CScore::Draw(void)
{
	//描画は勝手にやってくれます
}

//=================================
//生成処理
//=================================
CScore* CScore::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight)
{
	CScore* pScore = nullptr;

	if (pScore == nullptr)
	{
		//スコア管理オブジェクト生成
		pScore = new CScore;

		//スコア管理オブジェクト初期化
		pScore->Init();

		//データ設定
		pScore->m_pos = pos;
		pScore->m_rot = rot;

		//数字6桁
		for (int cnt = 0; cnt < SCORE_DIGIT; cnt++)
		{
			//生成
			pScore->m_pNumber[cnt] = CNumber::Create(pos + D3DXVECTOR3(-fOneWidth * (cnt + 1), 0.0f, 0.0f), rot, fOneWidth, fOneHeight);

			//初期化
			pScore->m_pNumber[cnt]->Init();
		}

		return pScore;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//スコア設定処理
//=================================
void CScore::Set(const int nScore)
{
	//数字設定
	m_nScore = nScore;
}

//=================================
//スコア加算処理
//=================================
void CScore::Add(const int nAdd)
{
	//数字加算
	m_nScore += nAdd;
}

//=================================
//テクスチャ設定
//=================================
void CScore::BindTexture(const int nIdx)
{
	for (int cnt = 0; cnt < SCORE_DIGIT; cnt++)
	{//数字オブジェクトに渡す
		if (m_pNumber[cnt] != nullptr)
		{//大丈夫。中身はある
			m_pNumber[cnt]->BindTexture(nIdx);
		}
	}
}

//=================================
//数字分割処理
//=================================
void CScore::CutNumber(void)
{
	for (int cnt = 0; cnt < SCORE_DIGIT; cnt++)
	{//数字オブジェクトに渡す
		if (m_pNumber[cnt] != nullptr)
		{//大丈夫。中身はある
			m_pNumber[cnt]->SetNumber(m_nScore, cnt);
		}
	}
}