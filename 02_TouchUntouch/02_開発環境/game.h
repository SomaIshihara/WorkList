//======================================================
//
//ゲームシーンのヘッダ[game.h]
//Author:石原颯馬
//
//======================================================
#ifndef _GAME_H_
#define _GAME_H_
#include "manager.h"

//前方宣言
class CPlayer;
class CScore;
class CTimer;
class CResult;
class CSwitchManager;
class CBlockManager;
class CPause;

//仮
class CGoal;

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
	CPlayer* m_pPlayer;	//プレイヤーポインタ
	CScore* m_pScore;	//スコアポインタ
	CTimer* m_pTimer;	//タイマーポインタ
	CResult* m_pResult;	//リザルトポインタ
	CSwitchManager* m_pSwitchManager;	//スイッチマネ
	CBlockManager* m_pBlockManager;		//ブロックマネ
	CPause* m_pPause;	//ポーズ
	bool m_bStart;		//ゲームを始めたか
};

#endif // !_GAME_H_
