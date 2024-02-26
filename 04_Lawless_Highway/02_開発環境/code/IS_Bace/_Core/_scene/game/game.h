//======================================================
//
//ゲームシーンのヘッダ[game.h]
//Author:石原颯馬
//
//======================================================
#ifndef _GAME_H_
#define _GAME_H_
#include "..\..\manager\manager.h"

//前方宣言
class CPause;
class CFade;
class CTimerMSmS;
class CPlayer;
class CGauge;
class CGoal;
class CObject2D;

//タイトルクラス
class CGame : public CScene
{
public:
	//コンストラクタ・デストラクタ
	CGame();
	~CGame();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CPause* m_pPause;		//ポーズ
	CFade* m_pFade;			//フェード
	CTimerMSmS* m_pTimer;	//タイマー
	CPlayer* m_pPlayer;
	CGauge* m_pGauge;
	CGoal* m_pGoal;
	CObject2D* m_pConfig;
	bool m_bIsGoal;
	bool m_bUseGP;
	float m_fBGMVolume;
};

#endif // !_GAME_H_
