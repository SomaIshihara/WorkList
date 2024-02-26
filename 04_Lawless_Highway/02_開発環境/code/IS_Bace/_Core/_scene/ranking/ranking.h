//======================================================
//
//ランキングシーンのヘッダ[ranking.h]
//Author:石原颯馬
//
//======================================================
#ifndef _RANKING_H_
#define _RANKING_H_
#include "..\..\manager\manager.h"

//前方宣言
class CFade;

//タイトルクラス
class CRanking : public CScene
{
public:
	//ミリ秒付きの時間構造体
	struct RankTimeMSmS
	{
		//デフォルトコンストラクタ
		RankTimeMSmS()
		{
			nTime = 0;
			nCounter = 0;
		}
		
		//簡単代入用コンストラクタ
		RankTimeMSmS(const int time,const int counter)
		{
			nTime = time;
			nCounter = counter;
		}

		int nTime;
		int nCounter;
	};

	//静的const
	static const int MAX_RANK;

	//コンストラクタ・デストラクタ
	CRanking();
	~CRanking();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//設定
	static void Set(const RankTimeMSmS nTimer);

private:
	static void Load(RankTimeMSmS* pRanking);
	static void Save(RankTimeMSmS* pRanking);

	//オブジェ（いったんスコア類すべて投げっぱで）
	CFade* m_pFade;
};

#endif // !_RANKING_H_
