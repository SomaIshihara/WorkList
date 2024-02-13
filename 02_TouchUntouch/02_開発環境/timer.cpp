//======================================================
//
//タイマー処理[timer.cpp]
//Author:石原颯馬
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"
#include "object.h"
#include "timer.h"
#include "number.h"

//=================================
//コンストラクタ（デフォルト）
//=================================
CTimer::CTimer(int nPriority) : CObject(nPriority)
{
	//値クリア
	m_pos = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_nCounter = 0;
	m_count = COUNT_DOWN;
	m_shouldCount = false;
}

//=================================
//デストラクタ
//=================================
CTimer::~CTimer()
{
}

//=================================
//初期化
//=================================
HRESULT CTimer::Init(void)
{
	for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
	{//数字オブジェクト初期化
		m_pNumber[cnt] = nullptr;
	}

	//タイマーカウンタリセット
	m_nCounter = 0;
	m_count = COUNT_DOWN;
	m_shouldCount = false;

	//タイム設定
	Set(0, COUNT_UP);

	//できた
	return S_OK;
}

//=================================
//終了
//=================================
void CTimer::Uninit(void)
{
	for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
	{//数字オブジェクト終了
		if (m_pNumber[cnt] != nullptr)
		{//大丈夫。中身はある
			m_pNumber[cnt]->Uninit();
		}
	}

	//タイムオブジェクト破棄
	Release();
}

//=================================
//更新
//=================================
void CTimer::Update(void)
{
	//動かすなら回す
	if (m_shouldCount == true)
	{
		//タイマー更新
		m_nCounter++;

		if (m_nCounter >= MAX_FPS)
		{
			//カウンタリセット
			m_nCounter = 0;

			switch (m_count)
			{
			case COUNT_UP:
				m_nTime++;	//加算
				if (m_nTime >= (int)pow(10, TIME_DIGIT))
				{//桁数の限界を超えた
					m_nTime = (int)pow(10, TIME_DIGIT) - 1;
				}
				break;

			case COUNT_DOWN:
				m_nTime--;	//減算
				if (m_nTime < CManager::INT_ZERO)
				{//0を下回った
					m_nTime = CManager::INT_ZERO;
				}
				break;
			}
		}

		for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
		{//数字オブジェクト更新
			if (m_pNumber[cnt] != nullptr)
			{//大丈夫。中身はある
			 //オブジェクト2Dの更新処理
				m_pNumber[cnt]->Update();
			}
		}
	}

	//数字分割
	CutNumber();
}

//=================================
//描画
//=================================
void CTimer::Draw(void)
{
	//勝手にやってくれます
}

//=================================
//生成処理
//=================================
CTimer* CTimer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight)
{
	CTimer* pTimer = nullptr;

	if (pTimer == nullptr)
	{
		//タイマー管理オブジェクト生成
		pTimer = new CTimer;

		//タイマー管理オブジェクト初期化
		pTimer->Init();

		//データ設定
		pTimer->m_pos = pos;
		pTimer->m_rot = rot;

		for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
		{//1枚分生成～テクスチャ設定（右から）
			//生成
			pTimer->m_pNumber[cnt] = CNumber::Create(pos + D3DXVECTOR3(-fOneWidth * (cnt + 1),0.0f,0.0f), rot, fOneWidth, fOneHeight);

			//初期化
			pTimer->m_pNumber[cnt]->Init();
		}

		return pTimer;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//タイム設定処理
//=================================
void CTimer::Set(const int nScore,COUNT type)
{
	//数字設定
	m_nTime = nScore;

	//数字分割
	CutNumber();
}


//=================================
//テクスチャ設定
//=================================
void CTimer::BindTexture(const int nIdx)
{
	for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
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
void CTimer::CutNumber(void)
{
	for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
	{//数字オブジェクトに渡す
		if (m_pNumber[cnt] != nullptr)
		{//大丈夫。中身はある
			m_pNumber[cnt]->SetNumber(m_nTime, cnt);
		}
	}
}