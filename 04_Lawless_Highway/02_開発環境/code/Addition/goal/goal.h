//======================================================
//
//ゴール処理[goal.h]
//Author:石原颯馬
//
//======================================================
#ifndef _GOAL_H_	//多重インクルード対策
#define _GOAL_H_
#include "../../IS_Bace/_Core/_object/object_empty/object.h"
#include "../../IS_Bace/_Core/utility/Utility.h"
#include "../../IS_Bace/_Core/interface.h"

//前方宣言
class CBoxCollider;

//オブジェクトクラス
class CGoal : public CObject , public ICollisionReader
{
public:
	//コンストラクタ・デストラクタ
	CGoal(int nPriority = PRIORITY_02);	//デフォルト
	virtual ~CGoal();

	//基本処理
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//生成
	static CGoal* Create(const D3DXVECTOR3 pos, const float fWidth, const float fHeight, const float fDepth);

	//取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	bool IsGoal(void) { return m_bIsGoal; }

	//設定
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }	//位置
	
	//除外
	virtual void Exclusion(void){}

	//インタフェース実装
	D3DXVECTOR3 GetMove(void) { return IS_Utility::VEC3_ZERO; }
	D3DXVECTOR3 GetPosOld(void) { return m_pos; }
	float GetDepth(void) { return m_fDepth; }
	CObject* GetObj(void) { return this; }

private:
	D3DXVECTOR3 m_pos;	//位置
	float m_fWidth;		//幅
	float m_fHeight;	//高さ
	float m_fDepth;		//奥行
	bool m_bIsGoal;		//ゴールしたか
	CBoxCollider* m_pCollider;
};

#endif	//多重