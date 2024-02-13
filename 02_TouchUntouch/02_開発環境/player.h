//======================================================
//
//プレイヤー処理のヘッダ[player.h]
//Author:石原颯馬
//
//======================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "character.h"
#include "interface.h"

//前方宣言
class CInputGamePad;

//プレイヤークラス
class CPlayer : public IControllStat
{
public:
	//コンストラクタ・デストラクタ
	CPlayer();
	~CPlayer();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	//インターフェース
	int GetType(void) { return m_controllType; }	//操作中のキャラタイプ
	int GetPress(void) { return m_nPressMove; };	//操作状況
	bool IsJump(void) { return m_bPressJump; }		//ジャンプするか

	//設定
	void SetControll(const bool bEnable) { m_bControlled = bEnable; }

private:
	//変数
	CCharacter::TYPE m_controllType;				//操作中のキャラのタイプ
	int m_nPressMove;								//押されている移動使用ボタン
	bool m_bPressJump;								//ジャンプボタンが押されているか
	bool m_bControlled;								//操作できるか
};

#endif