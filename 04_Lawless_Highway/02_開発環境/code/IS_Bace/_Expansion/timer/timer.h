//======================================================
//
//タイマー処理のヘッダ[timer.h]
//Author:石原颯馬
//
//======================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "..\..\_Core\_object\object_2d\object2D.h"

#define TIME_DIGIT	(3)	//タイマーの桁数

class CObject2D;
class CNumber;

//******************************************************************
// 基本タイマークラス
//******************************************************************
class CTimer : public CObject
{
public:
	//タイマーカウント種類
	enum class COUNT
	{
		COUNT_UP = 0,
		COUNT_DOWN,
		COUNT_MAX
	};

	//コンストラクタ・デストラクタ
	CTimer(int nPriority = PRIORITY_05);	//デフォルト
	virtual ~CTimer();

	//基本処理
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	int GetTime(void) { return m_nTime; }
	COUNT GetCountType(void) { return m_count; }
	virtual float GetWidth(void) = 0;
	int GetCounter(void) { return m_nCounter; }

	//設定
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; Replace(); }
	void Set(const int nTime, COUNT type);	//タイマー設定
	bool GetShouldCount(void) { return m_shouldCount; }
	void Start(void) { m_shouldCount = true; }
	void Stop(void) { m_shouldCount = false; }
	void Add(const int nTime) { m_nTime += nTime; }
	virtual void BindTexture(const int nIdx) = 0;	//テクスチャ設定（数字オブジェクトすべてに適用）

	//除外（必要なし）
	void Exclusion(void){}

protected:
	//設定
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetCounter(const int nCounter) { m_nCounter = nCounter; }
	virtual void Replace(void) = 0;

private:
	virtual void CutNumber(void) = 0;	//数字分割
	D3DXVECTOR3 m_pos;					//位置（1桁目の数字の中心を想定）
	D3DXVECTOR3 m_rot;					//向き（1桁目の数字の中心を想定）
	int m_nCounter;						//タイマーカウンタ
	int m_nTime;						//タイム
	COUNT m_count;						//カウント種類
	bool m_shouldCount;					//カウントするかどうか
};

//******************************************************************
// 秒タイマークラス
//******************************************************************
class CTimerSecond : public CTimer
{
public:
	//コンストラクタ・デストラクタ
	CTimerSecond();
	~CTimerSecond();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//取得
	float GetWidth(void) { return m_fWidth * TIME_DIGIT; }

	//設定
	void BindTexture(const int nIdx);

	//オブジェクトを生成(fOneWidth,fOneHeight:1桁当たりのサイズ)
	static CTimerSecond* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight);
protected:
	void Replace(void);

private:
	void CutNumber(void);

	float m_fWidth;
	CNumber* m_pNumber[TIME_DIGIT];		//数字
};

//******************************************************************
// 分秒ミリ秒タイマークラス
//******************************************************************
class CTimerMSmS : public CTimer
{
public:
	//コンストラクタ・デストラクタ
	CTimerMSmS();
	~CTimerMSmS();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//取得
	float GetWidth(void) { return m_fWidth * 7; }

	//設定
	void Set(const int nTime, const int nCounter, COUNT type);
	void BindTexture(const int nIdx);
	void BindSymbolTexture(const int nIdx);

	//オブジェクトを生成(fOneWidth,fOneHeight:1桁当たりのサイズ)
	static CTimerMSmS* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight);
protected:
	void Replace(void);

private:
	void CutNumber(void);

	float m_fWidth;
	CNumber* m_pMinute[2];
	CNumber* m_pSecond[2];
	CNumber* m_pMilliSecond[2];
	CObject2D* m_pSymbol[2];	//[0]:分と秒,[1]:秒とミリ秒
};

#endif	//多重