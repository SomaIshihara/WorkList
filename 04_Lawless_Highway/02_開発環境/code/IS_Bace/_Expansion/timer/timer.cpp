//======================================================
//
//タイマー処理[timer.cpp]
//Author:石原颯馬
//
//======================================================
#include "timer.h"
#include "..\..\..\main.h"
#include "..\..\_Core\manager\manager.h"
#include "..\..\_Core\renderer\renderer.h"
#include "..\..\_Core\texture\texture.h"
#include "..\..\_Core\input\input.h"
#include "..\..\_Core\_object\object_empty\object.h"
#include "..\..\_Expansion\number\number.h"
#include"..\..\_Core\utility\Utility.h"

//******************************************************************
// 基本タイマークラス
//******************************************************************
//=================================
//コンストラクタ
//=================================
CTimer::CTimer(int nPriority) : CObject(nPriority)
{
	//値クリア
	m_pos = IS_Utility::VEC3_ZERO;
	m_rot = IS_Utility::VEC3_ZERO;
	m_nCounter = 0;
	m_count = COUNT::COUNT_DOWN;
	m_shouldCount = false;
	m_nTime = 0;
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
	//タイマーカウンタリセット
	m_nCounter = 0;
	m_count = COUNT::COUNT_DOWN;
	m_shouldCount = false;

	//タイム設定
	Set(0, COUNT::COUNT_UP);

	//できた
	return S_OK;
}

//=================================
//終了
//=================================
void CTimer::Uninit(void)
{
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
		switch (m_count)
		{
		case COUNT::COUNT_UP:
			//タイマー更新
			m_nCounter++;

			if (m_nCounter >= MAX_FPS)
			{
				//カウンタリセット
				m_nCounter = 0;

				m_nTime++;	//加算
				if (m_nTime >= (int)pow(10, TIME_DIGIT))
				{//桁数の限界を超えた
					m_nTime = (int)pow(10, TIME_DIGIT) - 1;
					m_shouldCount = false;
				}
			}
			break;

		case COUNT::COUNT_DOWN:
			//タイマー更新
			m_nCounter--;

			if (m_nCounter <= 0)
			{
				//カウンタリセット
				m_nCounter = MAX_FPS;

				m_nTime--;	//減算
				if (m_nTime < 0)
				{//0を下回った
					m_nTime = 0;
					m_shouldCount = false;
				}
			}
			break;
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
//タイム設定処理
//=================================
void CTimer::Set(const int nScore,COUNT type)
{
	//数字設定
	m_nTime = nScore;
	m_count = type;
	m_nCounter = 0;

	//数字分割
	CutNumber();
}

//******************************************************************
// 秒タイマークラス
//******************************************************************
//=================================
//コンストラクタ
//=================================
CTimerSecond::CTimerSecond()
{
	m_fWidth = 0.0f;
}

//=================================
//デストラクタ
//=================================
CTimerSecond::~CTimerSecond()
{
}

//=================================
//初期化
//=================================
HRESULT CTimerSecond::Init(void)
{
	for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
	{//数字オブジェクト初期化
		m_pNumber[cnt] = nullptr;
	}

	return CTimer::Init();
}

//=================================
//終了
//=================================
void CTimerSecond::Uninit(void)
{
	for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
	{//数字オブジェクト終了
		if (m_pNumber[cnt] != nullptr)
		{//大丈夫。中身はある
			m_pNumber[cnt]->Uninit();
		}
	}

	CTimer::Uninit();
}

//=================================
//更新
//=================================
void CTimerSecond::Update(void)
{
	CTimer::Update();

	for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
	{//数字オブジェクト更新
		if (m_pNumber[cnt] != nullptr)
		{//大丈夫。中身はある
		 //オブジェクト2Dの更新処理
			m_pNumber[cnt]->Update();
		}
	}
}

//=================================
//描画
//=================================
void CTimerSecond::Draw(void)
{
	CTimer::Draw();
}

//=================================
//生成処理
//=================================
CTimerSecond* CTimerSecond::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight)
{
	CTimerSecond* pTimer = nullptr;

	if (pTimer == nullptr)
	{
		//タイマー管理オブジェクト生成
		pTimer = new CTimerSecond;

		//タイマー管理オブジェクト初期化
		pTimer->Init();

		//数字生成
		for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
		{//1枚分生成～テクスチャ設定（右から）
			//生成
			pTimer->m_pNumber[cnt] = CNumber::Create(pos + D3DXVECTOR3(-fOneWidth * (cnt + 1), 0.0f, 0.0f), rot, fOneWidth, fOneHeight);

			//初期化
			pTimer->m_pNumber[cnt]->Init();
		}

		//データ設定
		pTimer->SetPos(pos);
		pTimer->SetRot(rot);
		pTimer->m_fWidth = fOneWidth;

		return pTimer;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//再配置
//=================================
void CTimerSecond::Replace(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = CTimer::GetRot();
	float fOneWidth = m_pNumber[0]->GetWidth();
	float fOneHeight = m_pNumber[0]->GetHeight();

	for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
	{//1枚分生成～テクスチャ設定（右から）
		//生成
		m_pNumber[cnt]->SetPos(pos + D3DXVECTOR3(-fOneWidth * (cnt + 1), 0.0f, 0.0f));
	}
}

//=================================
//テクスチャ設定
//=================================
void CTimerSecond::BindTexture(const int nIdx)
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
void CTimerSecond::CutNumber(void)
{
	int nTime = CTimer::GetTime();
	for (int cnt = 0; cnt < TIME_DIGIT; cnt++)
	{//数字オブジェクトに渡す
		if (m_pNumber[cnt] != nullptr)
		{//大丈夫。中身はある
			m_pNumber[cnt]->SetNumber(nTime, cnt);
		}
	}
}

//******************************************************************
// 分秒ミリ秒タイマークラス
//******************************************************************
//=================================
//コンストラクタ
//=================================
CTimerMSmS::CTimerMSmS()
{
	m_fWidth = 0.0f;

}

//=================================
//デストラクタ
//=================================
CTimerMSmS::~CTimerMSmS()
{
}

//=================================
//初期化
//=================================
HRESULT CTimerMSmS::Init(void)
{
	//オブジェクト初期化（ぬるぽ入れる）
	for (int cnt = 0; cnt < 2; cnt++)
	{
		m_pMinute[cnt] = nullptr;
		m_pSecond[cnt] = nullptr;
		m_pMilliSecond[cnt] = nullptr;
		m_pSymbol[cnt] = nullptr;
	}

	return CTimer::Init();
}

//=================================
//終了
//=================================
void CTimerMSmS::Uninit(void)
{
	//オブジェクト終了
	for (int cnt = 0; cnt < 2; cnt++)
	{
		if (m_pMinute[cnt] != nullptr)
		{
			m_pMinute[cnt]->Uninit();
			m_pMinute[cnt] = nullptr;
		}
		if (m_pSecond[cnt] != nullptr)
		{
			m_pSecond[cnt]->Uninit();
			m_pSecond[cnt] = nullptr;
		}
		if (m_pMilliSecond[cnt] != nullptr)
		{
			m_pMilliSecond[cnt]->Uninit();
			m_pMilliSecond[cnt] = nullptr;
		}
		if (m_pSymbol[cnt] != nullptr)
		{
			m_pSymbol[cnt]->Uninit();
			m_pSymbol[cnt] = nullptr;
		}
	}

	CTimer::Uninit();
}

//=================================
//更新
//=================================
void CTimerMSmS::Update(void)
{
	CTimer::Update();

	//オブジェクト更新
	for (int cnt = 0; cnt < 2; cnt++)
	{
		if (m_pMinute[cnt] != nullptr)
		{
			m_pMinute[cnt]->Update();
		}
		if (m_pSecond[cnt] != nullptr)
		{
			m_pSecond[cnt]->Update();
		}
		if (m_pMilliSecond[cnt] != nullptr)
		{
			m_pMilliSecond[cnt]->Update();
		}
		if (m_pSymbol[cnt] != nullptr)
		{
			m_pSymbol[cnt]->Update();
		}
	}
}

//=================================
//描画
//=================================
void CTimerMSmS::Draw(void)
{
	CTimer::Draw();
}

//=================================
//生成処理
//=================================
CTimerMSmS* CTimerMSmS::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight)
{
	CTimerMSmS* pTimer = nullptr;

	if (pTimer == nullptr)
	{
		//タイマー管理オブジェクト生成
		pTimer = new CTimerMSmS;

		//タイマー管理オブジェクト初期化
		pTimer->Init();

		//オブジェクト生成
		float fAllWidth = fOneWidth * 7;	//内訳:数字(1)×6,記号(0.5)×2
		float fPlacePos = -(fAllWidth * 0.5f);	//初期位置
		//分
		for (int cnt = 0; cnt < 2; cnt++)
		{
			pTimer->m_pMinute[cnt] = CNumber::Create(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.5f) + (fOneWidth * cnt), 0.0f, 0.0f),
				rot, fOneWidth, fOneHeight);
			pTimer->m_pMinute[cnt]->Init();
		}
		//記号0
		fPlacePos += fOneWidth * 2;
		pTimer->m_pSymbol[0] = CNumber::Create(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.25f), 0.0f, 0.0f),
			rot, fOneWidth * 0.5f, fOneHeight);
		pTimer->m_pSymbol[0]->Init();

		//秒
		fPlacePos += fOneWidth * 0.5f;
		for (int cnt = 0; cnt < 2; cnt++)
		{
			pTimer->m_pSecond[cnt] = CNumber::Create(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.5f) + (fOneWidth * cnt), 0.0f, 0.0f),
				rot, fOneWidth, fOneHeight);
			pTimer->m_pSecond[cnt]->Init();
		}
		//記号1
		fPlacePos += fOneWidth * 2;
		pTimer->m_pSymbol[1] = CNumber::Create(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.25f), 0.0f, 0.0f),
			rot, fOneWidth * 0.5f, fOneHeight);
		pTimer->m_pSymbol[1]->Init();
		

		//ミリ秒
		fPlacePos += fOneWidth * 0.5f;
		for (int cnt = 0; cnt < 2; cnt++)
		{
			pTimer->m_pMilliSecond[cnt] = CNumber::Create(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.5f) + (fOneWidth * cnt), 0.0f, 0.0f),
				rot, fOneWidth, fOneHeight);
			pTimer->m_pMilliSecond[cnt]->Init();
		}

		//データ設定
		pTimer->SetPos(pos);
		pTimer->SetRot(rot);
		pTimer->m_fWidth = fOneWidth;

		return pTimer;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//ミリ秒含めた時間設定
//=================================
void CTimerMSmS::Set(const int nTime, const int nCounter, COUNT type)
{
	//数字設定
	CTimer::Set(nTime, type);
	CTimer::SetCounter(nCounter);
	CutNumber();
}

//=================================
//テクスチャ設定（数字）
//=================================
void CTimerMSmS::BindTexture(const int nIdx)
{
	for (int cnt = 0; cnt < 2; cnt++)
	{
		if (m_pMinute[cnt] != nullptr)
		{
			m_pMinute[cnt]->BindTexture(CTexture::PRELOAD::PRELOAD_04_TIMER_NUMBER);
			m_pMinute[cnt]->SetNumber(0, 0);
		}
		if (m_pSecond[cnt] != nullptr)
		{
			m_pSecond[cnt]->BindTexture(CTexture::PRELOAD::PRELOAD_04_TIMER_NUMBER);
			m_pSecond[cnt]->SetNumber(0, 0);
		}
		if (m_pMilliSecond[cnt] != nullptr)
		{
			m_pMilliSecond[cnt]->BindTexture(CTexture::PRELOAD::PRELOAD_04_TIMER_NUMBER);
			m_pMilliSecond[cnt]->SetNumber(0, 0);
		}
	}
}

//=================================
//テクスチャ設定（記号）
//=================================
void CTimerMSmS::BindSymbolTexture(const int nIdx)
{
	for (int cnt = 0; cnt < 2; cnt++)
	{
		if (m_pSymbol[cnt] != nullptr)
		{
			m_pSymbol[cnt]->BindTexture(CTexture::PRELOAD::PRELOAD_05_TIMER_SYMBOL);
			m_pSymbol[cnt]->SetTex(D3DXVECTOR2(0.5f * cnt, 0.0f), D3DXVECTOR2(0.5f * (cnt + 1), 1.0f));
		}
	}
}

//=================================
//数字分割処理
//=================================
void CTimerMSmS::CutNumber(void)
{
	int nSecond = CTimer::GetTime();		//すべて秒に直したものをあらかじめ入れる
	int nCounter = CTimer::GetCounter();	//ミリ秒に直す前のものを入れる
	int nMinute = nSecond / 60;				//秒を分に変換
	nSecond %= 60;							//分に変換した分を減らす
	int nMilliSecond = (nCounter * 100 / MAX_FPS);

	for (int cnt = 0; cnt < 2; cnt++)
	{
		if (m_pMinute[cnt] != nullptr)
		{
			m_pMinute[cnt]->SetNumber(nMinute, 1 - cnt);
		}
		if (m_pSecond[cnt] != nullptr)
		{
			m_pSecond[cnt]->SetNumber(nSecond, 1 - cnt);
		}
		if (m_pMilliSecond[cnt] != nullptr)
		{
			m_pMilliSecond[cnt]->SetNumber(nMilliSecond, 1 - cnt);
		}
	}
}

//=================================
//再配置
//=================================
void CTimerMSmS::Replace(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = CTimer::GetRot();
	float fOneWidth = m_pMinute[0]->GetWidth();
	float fOneHeight = m_pMinute[0]->GetHeight();
	float fAllWidth = fOneWidth * 7;	//内訳:数字(1)×6,記号(0.5)×2
	float fPlacePos = -(fAllWidth * 0.5f);	//初期位置
	//分
	for (int cnt = 0; cnt < 2; cnt++)
	{
		m_pMinute[cnt]->SetPos(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.5f) + (fOneWidth * cnt), 0.0f, 0.0f));
	}
	//記号0
	fPlacePos += fOneWidth * 2;
	m_pSymbol[0]->SetPos(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.25f), 0.0f, 0.0f));

	//秒
	fPlacePos += fOneWidth * 0.5f;
	for (int cnt = 0; cnt < 2; cnt++)
	{
		m_pSecond[cnt]->SetPos(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.5f) + (fOneWidth * cnt), 0.0f, 0.0f));
	}
	//記号1
	fPlacePos += fOneWidth * 2;
	m_pSymbol[1]->SetPos(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.25f), 0.0f, 0.0f));

	//ミリ秒
	fPlacePos += fOneWidth * 0.5f;
	for (int cnt = 0; cnt < 2; cnt++)
	{
		m_pMilliSecond[cnt]->SetPos(pos + D3DXVECTOR3(fPlacePos + (fOneWidth * 0.5f) + (fOneWidth * cnt), 0.0f, 0.0f));
	}
}