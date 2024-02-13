//======================================================
//
//当たり判定処理の[collision.cpp]
//Author:石原颯馬
//
//======================================================
#include "collision.h"
#include "Culc.h"
#include "manager.h"
#include "objectBillboard.h"

//静的メンバ変数
CBoxCollider* CBoxCollider::m_pTop;	//先頭オブジェクト
CBoxCollider* CBoxCollider::m_pCur;	//最後尾オブジェクト
bool CBoxCollider::m_aTagColl[CBoxCollider::TAG_MAX][CBoxCollider::TAG_MAX] =
{//  Univ   A    B
	{true,true,true},	//Univ
	{true,true,false},	//A
	{true,false,true}	//B
};

//=================================
//コンストラクタ
//=================================
CCollision::CCollision()
{
	m_vtxMin = CManager::VEC3_ZERO;
	m_vtxMax = CManager::VEC3_ZERO;
}

//=================================
//デストラクタ
//=================================
CCollision::~CCollision()
{
}

//=================================
//当たり判定チェック
//=================================
bool CCollision::CollisionCheck(const D3DXVECTOR3 posOld, const D3DXVECTOR3 posNew, const D3DXVECTOR3 posCenter, const D3DXVECTOR3 rot)
{
	//前側面
	if (CollisionPolygon(posOld, posNew, posCenter, rot, D3DXVECTOR3(0.0f, 0.0f, -1.0f),
		D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMin.z), D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMin.z),
		D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMin.z), D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMin.z)) == true)
	{
		return true;
	}

	//右側面
	if (CollisionPolygon(posOld, posNew, posCenter, rot, D3DXVECTOR3(1.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMin.z), D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMin.z),
		D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMin.z), D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMin.z)) == true)
	{
		return true;
	}

	//奥側面
	if (CollisionPolygon(posOld, posNew, posCenter, rot, D3DXVECTOR3(0.0f, 0.0f, 1.0f),
		D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMax.z), D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMax.z),
		D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMax.z), D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMax.z)) == true)
	{
		return true;
	}

	//左側面
	if (CollisionPolygon(posOld, posNew, posCenter, rot, D3DXVECTOR3(-1.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMax.z), D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMin.z),
		D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMin.z), D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMax.z)) == true)
	{
		return true;
	}

	//上側面
	if (CollisionPolygon(posOld, posNew, posCenter, rot, D3DXVECTOR3(0.0f, 1.0f, 0.0f),
		D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMin.z), D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMin.z),
		D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMax.z), D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMax.z)) == true)
	{
		return true;
	}

	//下側面
	if (CollisionPolygon(posOld, posNew, posCenter, rot, D3DXVECTOR3(0.0f, -1.0f, 0.0f),
		D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMin.z), D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMin.z),
		D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMax.z), D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMax.z)) == true)
	{
		return true;
	}

	return false;
}

//=================================
//ポリゴンごとの当たり判定チェック
//=================================
bool CCollision::CollisionPolygon(const D3DXVECTOR3 posOld, const D3DXVECTOR3 posNew, const D3DXVECTOR3 posCenter, const D3DXVECTOR3 rot,
	const D3DXVECTOR3 vecNor, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 pos3)
{
	//頂点の回転に必要な変数
	//各頂点を求めるのに必要な変数
	D3DXMATRIX mtxWorld;	//回転のベースとなるワールドマトリ
	D3DXMATRIX mtxRot;		//回転行列
	D3DXMATRIX mtxTrans;	//すべて変換後の行列
	D3DXVECTOR3 vtxTrans;	//変換後の点

	//頂点の回転
	pos0 = RotateVtx(pos0, rot, posCenter);	//pos0
	pos1 = RotateVtx(pos1, rot, posCenter);	//pos1
	pos2 = RotateVtx(pos2, rot, posCenter);	//pos2
	pos3 = RotateVtx(pos3, rot, posCenter);	//pos3

	//当たり判定
	if (D3DXVec3Dot(&posOld, &vecNor) * D3DXVec3Dot(&posNew, &vecNor) <= 0)
	{
		//ポリゴン貫通しているか
		D3DXVECTOR3 ray = posNew - posOld;			//レイ
		D3DXVec3Normalize(&ray, &ray);				//レイを正規化
		float fU, fV, fD;							//ごみ箱

		if (D3DXIntersectTri(&pos0, &pos1, &pos3, &posOld, &ray, &fU, &fV, &fD) == true || D3DXIntersectTri(&pos1, &pos2, &pos3, &posOld, &ray, &fU, &fV, &fD) == true)
		{//四角形を三角形に分割し、どちらかtrue帰ってきたら選択できた
			return true;
		}
	}
	
	return false;
}

//=================================
//コンストラクタ
//=================================
CBoxCollider::CBoxCollider()
{
	if (m_pCur == nullptr)
	{//最後尾がいない（すなわち先頭もいない）
		m_pTop = this;		//俺が先頭
		m_pPrev = nullptr;		//前後誰もいない
		m_pNext = nullptr;
	}
	else
	{//最後尾がいる
		m_pPrev = m_pCur;		//最後尾が自分の前のオブジェ
		m_pCur->m_pNext = this;	//最後尾の次のオブジェが自分
		m_pNext = nullptr;			//自分の次のオブジェはいない
	}
	m_pCur = this;				//俺が最後尾
}

//=================================
//デストラクタ
//=================================
CBoxCollider::~CBoxCollider()
{
}

//=================================
//当たり判定チェック
//=================================
void CBoxCollider::CollisionCheck(void)
{
	//当たり判定結果
	CollisionResult collResult;
	collResult.bHit[0] = false;
	collResult.bHit[1] = false;
	collResult.bHit[2] = false;
	
	//そもそも当たり判定有効か
	if (this->m_type != TYPE_NONE)
	{
		//自分の当たり判定
		D3DXVECTOR3 move = m_iCollisionReader->GetMove();
		D3DXVECTOR3 posOld = m_iCollisionReader->GetPosOld();
		D3DXVECTOR3 pos = posOld;
		float fPlayerWidth = m_iCollisionReader->GetWidth() * 0.5f;
		float fPlayerHeight = m_iCollisionReader->GetHeight() * 0.5f;
		float fPlayerDepth = m_iCollisionReader->GetDepth() * 0.5f;

		//X
		pos.x += move.x;
		ColFloat playerCol;
		playerCol.pPosMain = &pos.x;
		playerCol.pPosSubA = pos.y;
		playerCol.pPosSubB = pos.z;
		playerCol.fSizeMain = fPlayerWidth;
		playerCol.fSizeSubA = fPlayerHeight;
		playerCol.fSizeSubB = fPlayerDepth;

		CBoxCollider* pCollider = CBoxCollider::GetTop();

		while (pCollider != nullptr)
		{
			if (pCollider != this && pCollider->m_type != TYPE_NONE && m_aTagColl[this->m_tag][pCollider->m_tag] == true)
			{
				ColFloat otherCol;
				D3DXVECTOR3 posOther = pCollider->m_iCollisionReader->GetPosOld() + pCollider->m_iCollisionReader->GetMove();
				otherCol.pPosMain = &posOther.x;
				otherCol.pPosSubA = posOther.y;
				otherCol.pPosSubB = posOther.z;
				otherCol.fSizeMain = pCollider->m_iCollisionReader->GetWidth() * 0.5f;
				otherCol.fSizeSubA = pCollider->m_iCollisionReader->GetHeight() * 0.5f;
				otherCol.fSizeSubB = pCollider->m_iCollisionReader->GetDepth() * 0.5f;

				if (CollisionAxis(playerCol, posOld.x, otherCol, pCollider->m_type))	//当たり判定
				{
					//重複チェック
					bool bRegisted = false;
					for (int cnt = 0; cnt < collResult.collList.size(); cnt++)
					{
						if (collResult.collList[cnt] == pCollider->m_iCollisionReader->GetObj())
						{
							bRegisted = true;
							break;
						}

					}

					if (bRegisted == false)
					{//重複してない
						collResult.collList.emplace_back(pCollider->m_iCollisionReader->GetObj());
					}

					collResult.bHit[0] = true;
				}
			}
			pCollider = pCollider->GetNext();	//次のブロック
		}

		//Y
		pos.y += move.y;
		playerCol.pPosMain = &pos.y;
		playerCol.pPosSubA = pos.x;
		playerCol.pPosSubB = pos.z;
		playerCol.fSizeMain = fPlayerHeight;
		playerCol.fSizeSubA = fPlayerWidth;
		playerCol.fSizeSubB = fPlayerDepth;

		pCollider = CBoxCollider::GetTop();

		while (pCollider != nullptr)
		{
			if (pCollider != this && pCollider->m_type != TYPE_NONE && m_aTagColl[this->m_tag][pCollider->m_tag] == true)
			{
				ColFloat otherCol;
				D3DXVECTOR3 posOther = pCollider->m_iCollisionReader->GetPosOld() + pCollider->m_iCollisionReader->GetMove();
				otherCol.pPosMain = &posOther.y;
				otherCol.pPosSubA = posOther.x;
				otherCol.pPosSubB = posOther.z;
				otherCol.fSizeMain = pCollider->m_iCollisionReader->GetHeight() * 0.5f;
				otherCol.fSizeSubA = pCollider->m_iCollisionReader->GetWidth() * 0.5f;
				otherCol.fSizeSubB = pCollider->m_iCollisionReader->GetDepth() * 0.5f;

				if (CollisionAxis(playerCol, posOld.y, otherCol, pCollider->m_type) == true)	//当たり判定
				{//着地した
				 //重複チェック
					bool bRegisted = false;
					for (int cnt = 0; cnt < collResult.collList.size(); cnt++)
					{
						if (collResult.collList[cnt] == pCollider->m_iCollisionReader->GetObj())
						{
							bRegisted = true;
							break;
						}

					}

					if (bRegisted == false)
					{//重複してない
						collResult.collList.emplace_back(pCollider->m_iCollisionReader->GetObj());
					}

					if (pCollider->m_type == TYPE_COLLISION)
					{
						collResult.bHit[1] = true;
					}
				}
			}
			pCollider = pCollider->GetNext();	//次のブロック
		}

		//Z
		pos.z += move.z;
		playerCol.pPosMain = &pos.z;
		playerCol.pPosSubA = pos.x;
		playerCol.pPosSubB = pos.y;
		playerCol.fSizeMain = fPlayerDepth;
		playerCol.fSizeSubA = fPlayerWidth;
		playerCol.fSizeSubB = fPlayerHeight;

		pCollider = CBoxCollider::GetTop();

		while (pCollider != nullptr)
		{
			if (pCollider != this && pCollider->m_type != TYPE_NONE && m_aTagColl[this->m_tag][pCollider->m_tag] == true)
			{
				ColFloat otherCol;
				D3DXVECTOR3 posOther = pCollider->m_iCollisionReader->GetPosOld() + pCollider->m_iCollisionReader->GetMove();
				otherCol.pPosMain = &posOther.z;
				otherCol.pPosSubA = posOther.x;
				otherCol.pPosSubB = posOther.y;
				otherCol.fSizeMain = pCollider->m_iCollisionReader->GetDepth() * 0.5f;
				otherCol.fSizeSubA = pCollider->m_iCollisionReader->GetWidth() * 0.5f;
				otherCol.fSizeSubB = pCollider->m_iCollisionReader->GetHeight() * 0.5f;

				if (CollisionAxis(playerCol, posOld.z, otherCol, pCollider->m_type))	//当たり判定
				{
					//重複チェック
					bool bRegisted = false;
					for (int cnt = 0; cnt < collResult.collList.size(); cnt++)
					{
						if (collResult.collList[cnt] == pCollider->m_iCollisionReader->GetObj())
						{
							bRegisted = true;
							break;
						}

					}

					if (bRegisted == false)
					{//重複してない
						collResult.collList.emplace_back(pCollider->m_iCollisionReader->GetObj());
					}

					collResult.bHit[2] = true;
				}
			}
			pCollider = pCollider->GetNext();	//次のブロック
		}

		//当たり判定後の位置設定
		m_iCollisionReader->SetPos(pos);

	}

	m_collisionResult = collResult;
}

//=================================
//当たり判定生成
//=================================
CBoxCollider * CBoxCollider::Create(ICollisionReader* iCollisionReader)
{
	CBoxCollider* pCollider = nullptr;

	if (pCollider == nullptr && iCollisionReader != nullptr)
	{
		pCollider = new CBoxCollider;
		pCollider->m_iCollisionReader = iCollisionReader;

		return pCollider;
	}
	return nullptr;
}

//=================================
//当たり判定破棄
//=================================
void CBoxCollider::Release(void)
{
	if (m_pPrev != nullptr)
	{//前にオブジェがいる
		m_pPrev->m_pNext = m_pNext;	//前のオブジェの次のオブジェは自分の次のオブジェ
	}
	if (m_pNext != nullptr)
	{
		m_pNext->m_pPrev = m_pPrev;	//次のオブジェの前のオブジェは自分の前のオブジェ
	}

	if (m_pCur == this)
	{//最後尾でした
		m_pCur = m_pPrev;	//最後尾を自分の前のオブジェにする
	}
	if (m_pTop == this)
	{
		m_pTop = m_pNext;	//先頭を自分の次のオブジェにする
	}

	//成仏
	delete this;	//自分自身破棄
}

//=================================
//軸単位での当たり判定
//=================================
bool CBoxCollider::CollisionAxis(ColFloat source, const float fPosMainOld, ColFloat dest, const TYPE otherType)
{
	bool bCollision = false;

	if (source.pPosSubA - source.fSizeSubA < dest.pPosSubA + dest.fSizeSubA &&
		source.pPosSubA + source.fSizeSubA > dest.pPosSubA - dest.fSizeSubA &&
		source.pPosSubB - source.fSizeSubB < dest.pPosSubB + dest.fSizeSubB &&
		source.pPosSubB + source.fSizeSubB > dest.pPosSubB - dest.fSizeSubB)
	{
		if (this->m_type == TYPE_COLLISION && otherType == TYPE_COLLISION)
		{//両方ぶつかる
			if (fPosMainOld + source.fSizeMain <= *dest.pPosMain - dest.fSizeMain &&
				*source.pPosMain + source.fSizeMain > *dest.pPosMain - dest.fSizeMain)
			{
				*source.pPosMain = *dest.pPosMain - dest.fSizeMain - source.fSizeMain;
				bCollision = true;
			}
			else if (fPosMainOld - source.fSizeMain >= *dest.pPosMain + dest.fSizeMain &&
				*source.pPosMain - source.fSizeMain < *dest.pPosMain + dest.fSizeMain)
			{
				*source.pPosMain = *dest.pPosMain + dest.fSizeMain + source.fSizeMain;
				bCollision = true;
			}
		}
		else if(*source.pPosMain - source.fSizeMain < *dest.pPosMain + dest.fSizeMain &&
			*source.pPosMain + source.fSizeMain > *dest.pPosMain - dest.fSizeMain)
		{//どちらか重なる設定なのは確定なので重なっているか確認
			bCollision = true;
		}
		
	}

	return bCollision;
}
