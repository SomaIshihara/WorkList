//======================================================
//
//当たり判定処理のヘッダ[collision.h]
//Author:石原颯馬
//
//======================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "interface.h"
#include <vector>

//前方宣言
class CObject;

//当たり判定クラス（旧）
class CCollision
{
public:
	//コンストラクタ・デストラクタ
	CCollision();
	~CCollision();

	//当たり判定チェック
	bool CollisionCheck(const D3DXVECTOR3 posOld, const D3DXVECTOR3 posNew, const D3DXVECTOR3 posCenter, const D3DXVECTOR3 rot);

	//設定
	void SetVtx(const D3DXVECTOR3 vtxMin, const D3DXVECTOR3 vtxMax) { m_vtxMin = vtxMin, m_vtxMax = vtxMax; }

	//取得
	void GetVtx(D3DXVECTOR3* vtxMin, D3DXVECTOR3* vtxMax) { *vtxMin = m_vtxMin, *vtxMax = m_vtxMax; }

private:
	bool CollisionPolygon(const D3DXVECTOR3 posOld, const D3DXVECTOR3 posNew, const D3DXVECTOR3 posCenter, const D3DXVECTOR3 rot,
		const D3DXVECTOR3 vecNor, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 pos3);
	D3DXVECTOR3 m_vtxMin, m_vtxMax;	//当たり判定最低値・最高値
};

//箱の当たり判定クラス
class CBoxCollider
{
public:
	//当たり判定種類
	enum TYPE
	{
		TYPE_COLLISION = 0,	//ぶつかる
		TYPE_TRIGGER,		//重なる
		TYPE_NONE,			//当たり判定がない
		TYPE_MAX
	};

	//タグ
	enum TAG
	{
		TAG_UNIV = 0,
		TAG_TYPE_A,
		TAG_TYPE_B,
		TAG_MAX
	};

	//当たり判定用float3つ
	struct ColFloat
	{
		float* pPosMain, pPosSubA, pPosSubB;
		float fSizeMain, fSizeSubA, fSizeSubB;
	};

	//当たり判定結果
	struct CollisionResult
	{
		std::vector<CObject*> collList;	//当たったやつリスト
		bool bHit[3];					//衝突したかを3軸分
	};

	//コンストラクタ・デストラクタ
	CBoxCollider();
	~CBoxCollider();

	//当たり判定チェック（当たっていれば当たったオブジェクト、なければぬるぽ）
	void CollisionCheck(void);

	//当たり判定設定
	static CBoxCollider* Create(ICollisionReader* iCollisionReader);
	void SetType(TYPE type) { m_type = type; }
	void SetTag(TAG tag) { m_tag = tag; }

	//破棄
	void Release(void);

	//取得
	CollisionResult GetResult(void) { return m_collisionResult; }
	static bool GetTagColl(TAG myTag, TAG otherTag) { return m_aTagColl[myTag][otherTag]; }

	//リスト取得
	static CBoxCollider* GetTop(void) { return m_pTop; }
	CBoxCollider* GetNext(void) { return m_pNext; }

private:
	//リスト
	static CBoxCollider* m_pTop;	//先頭オブジェクト
	static CBoxCollider* m_pCur;	//最後尾オブジェクト
	CBoxCollider* m_pNext;			//次のオブジェクト
	CBoxCollider* m_pPrev;			//前のオブジェクト

	//当たり判定設定
	static bool m_aTagColl[TAG_MAX][TAG_MAX];

	bool CollisionAxis(ColFloat source, const float fPosMainOld, ColFloat dest, const TYPE otherType);

	ICollisionReader* m_iCollisionReader;	//当たり判定に使うものの取得に使うインターフェース
	TYPE m_type;							//当たり判定種類
	CollisionResult m_collisionResult;		//当たり判定結果
	TAG m_tag;								//タグ（当たり判定設定用）
};

#endif // !_COLLISION_H_
