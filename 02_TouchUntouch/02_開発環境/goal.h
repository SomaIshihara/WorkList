//======================================================
//
//ゴール処理のヘッダ[goal.h]
//Author:石原颯馬
//
//======================================================
#ifndef _GOAL_H_
#define _GOAL_H_

//必要なのインクルード
#include "object.h"
#include "character.h"

//前方宣言
class CObjectX;
class CSwitch;

//キャラクタークラス
class CGoal : public CObject
{
public:
	//当たり判定用float3つ
	struct ColFloat
	{
		float* pPosMain, pPosSubA, pPosSubB;
		float fSizeMain, fSizeSubA, fSizeSubB;
	};

	//コンストラクタ・デストラクタ
	CGoal(int nPriority = PRIORITY_04);
	~CGoal();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CGoal* Create(const D3DXVECTOR3 pos);

	//取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	bool IsGoal(void) { return m_bGoal; }
	static CGoal* GetTop(void) { return m_pTop; }
	CGoal* GetNext(void) { return m_pNext; }

	//設定
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }

	//除外
	void Exclusion(void);

private:
	D3DXMATRIX m_mtxWorld;			//ワールドマトリ
	CObjectX* m_pBase;				//土台
	CSwitch* m_aSwitch[CCharacter::TYPE_MAX];	//人数分のスイッチオブジェ

	//リスト
	static CGoal* m_pTop;	//先頭オブジェクト
	static CGoal* m_pCur;	//最後尾オブジェクト
	CGoal* m_pNext;			//次のオブジェクト
	CGoal* m_pPrev;			//前のオブジェクト
	static int m_nNumAll;		//総数

	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_move;				//移動量
	D3DXVECTOR3 m_rot;				//向き
	float m_fWidth, m_fHeight, m_fDepth;	//サイズ
	bool m_bGoal;
};

#endif // !_CHARACTER_H_
