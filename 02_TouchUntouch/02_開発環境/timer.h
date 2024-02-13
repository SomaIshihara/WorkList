//======================================================
//
//タイマー処理のヘッダ[timer.h]
//Author:石原颯馬
//
//======================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "object2D.h"

#define TIME_DIGIT	(3)	//タイマーの桁数

class CNumber;

class CTimer : public CObject
{
public:
	//タイマーカウント種類
	typedef enum
	{
		COUNT_UP = 0,
		COUNT_DOWN,
		COUNT_MAX
	} COUNT;

	//コンストラクタ・デストラクタ
	CTimer(int nPriority = PRIORITY_05);	//デフォルト
	~CTimer();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CTimer* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight);	//オブジェクトを生成(fOneWidth,fOneHeight:1桁当たりのサイズ)

	//取得（純粋仮想関数の関係上実装しているが、こいつにサイズやらはいらないのですべて0を返す）
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	//float GetWidth(void) { return CManager::FLT_ZERO; }
	//float GetHeight(void) { return CManager::FLT_ZERO; }
	//float GetDepth(void) { return CManager::FLT_ZERO; }
	int GetModelIdx(void) { return -1; }
	int GetTime(void) { return m_nTime; }

	//設定
	void Set(const int nTime, COUNT type);	//タイマー設定
	bool GetCount(void) { return m_shouldCount; }
	void Start(void) { m_shouldCount = true; }
	void Stop(void) { m_shouldCount = false; }
	void Add(const int nTime) { m_nTime += nTime; }
	void BindTexture(const int nIdx);	//テクスチャ設定（数字オブジェクトすべてに適用）

	//除外（必要なし）
	void Exclusion(void){}

private:
	void CutNumber(void);				//数字分割
	CNumber* m_pNumber[TIME_DIGIT];		//数字
	D3DXVECTOR3 m_pos;					//位置（1桁目の数字の中心を想定）
	D3DXVECTOR3 m_rot;					//向き（1桁目の数字の中心を想定）
	int m_nCounter;						//タイマーカウンタ
	int m_nTime;						//タイム
	COUNT m_count;						//カウント種類
	bool m_shouldCount;					//カウントするかどうか
};

#endif	//多重