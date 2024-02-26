//======================================================
//
//リザルトシーンのヘッダ[result.h]
//Author:石原颯馬
//
//======================================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "..\..\manager\manager.h"

//前方宣言
class CPause;
class CFade;
class CObject2D;
class CTimerMSmS;

//仮
class CGoal;

//タイトルクラス
class CResult : public CScene
{
public:
	//結果列挙
	enum class RESULT
	{
		SUCCESS,
		LATETIME,
		MAX
	};

	//コンストラクタ・デストラクタ
	CResult();
	~CResult();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//設定
	static void Set(const RESULT result, const int ntime, const int nCounter);

private:
	CPause* m_pPause;	//ポーズ
	CFade* m_pFade;		//フェード
	CObject2D* m_pResult;	//遅刻か否か
	CTimerMSmS* m_pTimer;	//かかった時間
	CObject2D* m_pStart;	//スタート文字

	//結果
	static RESULT m_result;
	static int m_nTime;
	static int m_nCounter;
};

#endif // !_GAME_H_
