//======================================================
//
//インターフェース一覧[interface.h]
//Author:石原颯馬
//
//======================================================
#ifndef _INTERFACE_H_
#define _INTERFACE_H_

//前方宣言
class CObject;

//操作関係インターフェース
__interface IControllStat
{
	int GetType(void) = 0;		//操作中のキャラタイプ
	int GetPress(void) = 0;		//操作状況
	bool IsJump(void) = 0;		//ジャンプするか
};

//当たり判定関係インターフェース
__interface ICollisionReader
{
	D3DXVECTOR3 GetMove(void) = 0;
	D3DXVECTOR3 GetPosOld(void) = 0;
	void SetPos(const D3DXVECTOR3 pos) = 0;
	float GetWidth(void) = 0;
	float GetHeight(void) = 0;
	float GetDepth(void) = 0;
	CObject* GetObj(void) = 0;
};

//スコア設定用インターフェース
__interface IScoreSetter
{
	void Set(const int nScore) = 0;	//スコア設定
	void Add(const int nAdd) = 0;	//スコア加算
};

#endif // !_INTERFACE_H_
