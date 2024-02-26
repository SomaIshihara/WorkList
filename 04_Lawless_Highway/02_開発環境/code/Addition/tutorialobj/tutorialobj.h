//======================================================
//
//チュートリアルテキスト処理[tutorialobj.h]
//Author:石原颯馬
//
//======================================================
#ifndef _TUTORIAL_OBJ_H_
#define _TUTORIAL_OBJ_H_

#include "../../IS_Bace/_Core/_object/object_2d/object2D.h"
#include "../player/player.h"
#include "../../IS_Bace/_Expansion/timer/timer.h"

//前方宣言
class CTutorialState;

//チュートリアルテキストクラス
class CTutorialObj : public CObject2D
{
public:
	//コンストラクタ・デストラクタ
	CTutorialObj(int nPriority = CObject::PRIORITY_05);
	~CTutorialObj();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CTutorialObj* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, CTimer* pTimer, CPlayer* pPlayer);

	//設定
	void SetState(CTutorialState* pState) { m_pState = pState; }
	void SetWaitingPirot(void) { m_pPlayer->SetState(CPlayer::STATE::STATE_SYSTEM_START); }
	void GameStart(void) { m_pPlayer->SetState(CPlayer::STATE::STATE_GAME); m_pTimer->Start(); }
private:
	static const D3DXVECTOR3 PILOT_CHECKPOINT;
	static const D3DXVECTOR3 START_CHECKPOINT;
	CTutorialState* m_pState;
	CPlayer* m_pPlayer;
	CTimer* m_pTimer;
};

//チュートリアル内容状態
class CTutorialState
{
public:
	//コンストラクタ・デストラクタ
	CTutorialState() {}
	virtual ~CTutorialState(){}

	//更新処理
	virtual void Update(CTutorialObj* obj, D3DXVECTOR3 playerPos) = 0;
};

//ハンドル操作
class CTutorial_01 : public CTutorialState
{
public:
	//コンストラクタ・デストラクタ
	CTutorial_01(){}
	~CTutorial_01(){}

	//更新
	void Update(CTutorialObj* obj, D3DXVECTOR3 playerPos);
private:
	static const D3DXVECTOR3 CHECKPOINT;
};

//ブースト操作
class CTutorial_02 : public CTutorialState
{
public:
	//コンストラクタ・デストラクタ
	CTutorial_02() {}
	~CTutorial_02() {}

	//更新
	void Update(CTutorialObj* obj, D3DXVECTOR3 playerPos);
private:
	static const D3DXVECTOR3 CHECKPOINT;
};

//ブレーキドリフト操作
class CTutorial_03 : public CTutorialState
{
public:
	//コンストラクタ・デストラクタ
	CTutorial_03() {}
	~CTutorial_03() {}

	//更新
	void Update(CTutorialObj* obj, D3DXVECTOR3 playerPos);
private:
	static const D3DXVECTOR3 CHECKPOINT;
};

//目的表示
class CTutorial_04 : public CTutorialState
{
public:
	//コンストラクタ・デストラクタ
	CTutorial_04() { m_bIsSet = false; m_bIsPirot = false; }
	~CTutorial_04() {}

	//更新
	void Update(CTutorialObj* obj, D3DXVECTOR3 playerPos);
private:
	bool m_bIsSet;		//テクスチャ設定済みか
	bool m_bIsPirot;	//自動操縦状態にしたか
};

//自動操縦後ゲーム切り替え
class CTutorial_05 : public CTutorialState
{
public:
	//コンストラクタ・デストラクタ
	CTutorial_05() { m_bIsSet = false; m_bIsPirot = false; }
	~CTutorial_05() {}

	//更新
	void Update(CTutorialObj* obj, D3DXVECTOR3 playerPos);
private:
	bool m_bIsSet;		//テクスチャ設定済みか
	bool m_bIsPirot;	//自動操縦状態にしたか
	static const D3DXVECTOR3 CHECKPOINT;
};

#endif // !_TUTORIAL_OBJ_H_
