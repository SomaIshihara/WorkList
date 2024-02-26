//======================================================
//
//メッシュフィールド処理[meshField.cpp]
//Author:石原颯馬
//
//======================================================
#include "meshField.h"
#include "../../_Core/manager/manager.h"
#include "../../_Core/renderer/renderer.h"
#include "../../_Core/texture/texture.h"
#include "../../_Core/utility/Utility.h"
#include "../../_Core/debugproc/debugproc.h"
#include <vector>

using namespace std;

//静的メンバ変数
CMeshField* CMeshField::m_pTop = nullptr;
CMeshField* CMeshField::m_pCur = nullptr;
int CMeshField::m_nNumAll = 0;

//=================================
//コンストラクタ
//=================================
CMeshField::CMeshField(int nPriority) : CObject(nPriority)
{
	//値クリア
	m_pos = IS_Utility::VEC3_ZERO;
	m_rot = IS_Utility::VEC3_ZERO;
	m_fWidth = 0.0f;
	m_fDepth = 0.0f;
	m_nBlockWidth = 0;
	m_nBlockDepth = 0;
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pVtxbuff = nullptr;
	m_pIdxBuff = nullptr;
	m_nIdxTexture = -1;

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
	m_nNumAll++;
	CObject::SetDrawType(CObject::DRAWTYPE::DRAW_MESH);
}

//=================================
//デストラクタ
//=================================
CMeshField::~CMeshField()
{
}

//=================================
//初期化
//=================================
HRESULT CMeshField::Init(void)
{
	//バッファ生成
	CreateBuff();

	//頂点設定
	SetVtxBuff();

	//インデックスバッファ設定
	SetIdxBuff();

	return S_OK;
}

//=================================
//終了
//=================================
void CMeshField::Uninit(void)
{
	//バッファ破棄
	ReleaseBuff();

	//自分自身破棄
	Release();
}

//=================================
//更新
//=================================
void CMeshField::Update(void)
{
}

//=================================
//描画
//=================================
void CMeshField::Draw(void)
{
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxbuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャ設定
	CTexture* pTexture = nullptr;
	pTexture = pManager->GetTexture();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//ポリゴン描画（インデックスされたやつ）
	int nPolyNum = ((((m_nBlockWidth + 1) * m_nBlockDepth * 2) + (2 * (m_nBlockDepth - 1))) - 2);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (m_nBlockWidth + 1) * (m_nBlockDepth + 1), 0, nPolyNum);
}

//=================================
//生成
//=================================
CMeshField* CMeshField::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fDepth,
	const int nBlockWidth, const int nBlockDepth)
{
	CMeshField* pMeshField = nullptr;

	if (pMeshField == nullptr)
	{
		//オブジェクトの生成
		pMeshField = new CMeshField;

		//初期化
		pMeshField->m_pos = pos;
		pMeshField->m_rot = rot;
		pMeshField->m_fWidth = fWidth;
		pMeshField->m_fDepth = fDepth;
		pMeshField->m_nBlockWidth = nBlockWidth;
		pMeshField->m_nBlockDepth = nBlockDepth;
		pMeshField->Init();

		return pMeshField;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//バッファ生成
//=================================
void CMeshField::CreateBuff(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * (m_nBlockWidth + 1) * (m_nBlockDepth + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxbuff,
		nullptr);

	//インデックスバッファの生成
	int nIdxNum = (((m_nBlockWidth + 1) * m_nBlockDepth * 2) + (2 * (m_nBlockDepth - 1)));
	pDevice->CreateIndexBuffer(sizeof(WORD) * nIdxNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		nullptr);
}

//=================================
//バッファ破棄
//=================================
void CMeshField::ReleaseBuff(void)
{
	//頂点バッファの破棄
	if (m_pVtxbuff != nullptr)
	{
		m_pVtxbuff->Release();
		m_pVtxbuff = nullptr;
	}

	//インデックスバッファ破棄
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
}

//=================================
//頂点設定
//=================================
void CMeshField::SetVtxBuff(void)
{
	//頂点の各情報設定
	SetVtxPos();
	SetVtxCol();
	SetVtxTex();
	SetVtxNor();
}

//=================================
//頂点座標の設定
//=================================
void CMeshField::SetVtxPos(void)
{
	VERTEX_3D* pVtx;

	//バッファロック
	//頂点バッファのロックと頂点情報へのポインタを取得
	m_pVtxbuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標+テクスチャ座標
	for (int nCount = 0; nCount < (m_nBlockWidth + 1) * (m_nBlockDepth + 1); nCount++)
	{
		//頂点座標（相対座標）
		pVtx[nCount].pos = D3DXVECTOR3(m_fWidth * (((float)(nCount % (m_nBlockWidth + 1)) - 0.5f * (m_nBlockWidth))),
			0.0f, -m_fDepth * (((float)(nCount / (m_nBlockWidth + 1))) - 0.5f * (m_nBlockDepth)));
	}

	//頂点バッファをアンロック
	m_pVtxbuff->Unlock();
}

//=================================
//頂点カラーの設定
//=================================
void CMeshField::SetVtxCol(void)
{
	VERTEX_3D* pVtx;

	//バッファロック
	//頂点バッファのロックと頂点情報へのポインタを取得
	m_pVtxbuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標+テクスチャ座標
	for (int nCount = 0; nCount < (m_nBlockWidth + 1) * (m_nBlockDepth + 1); nCount++)
	{
		//カラー
		pVtx[nCount].col = m_color;
	}

	//頂点バッファをアンロック
	m_pVtxbuff->Unlock();
}

//=================================
//頂点のテクスチャ座標設定
//=================================
void CMeshField::SetVtxTex(void)
{
	VERTEX_3D* pVtx;

	//バッファロック
	//頂点バッファのロックと頂点情報へのポインタを取得
	m_pVtxbuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標+テクスチャ座標
	for (int nCount = 0; nCount < (m_nBlockWidth + 1) * (m_nBlockDepth + 1); nCount++)
	{
		//テクスチャ座標
		pVtx[nCount].tex = D3DXVECTOR2(((float)(nCount % (m_nBlockWidth + 1))), ((float)(nCount / (m_nBlockWidth + 1))));
	}

	//頂点バッファをアンロック
	m_pVtxbuff->Unlock();
}

//=================================
//頂点の法線設定
//=================================
void CMeshField::SetVtxNor(void)
{
	VERTEX_3D* pVtx;

	//バッファロック
	//頂点バッファのロックと頂点情報へのポインタを取得
	m_pVtxbuff->Lock(0, 0, (void**)&pVtx, 0);

	vector<D3DXVECTOR3>* pNor = new vector<D3DXVECTOR3>[(m_nBlockWidth + 1) * (m_nBlockDepth + 1)];

	for (int cntZ = 0; cntZ < m_nBlockDepth; cntZ++)
	{
		for (int cntX = 0; cntX < m_nBlockWidth; cntX++)
		{
			D3DXVECTOR3 nor0, nor1, nor2, nor3;
			D3DXVECTOR3 vec0, vec1;
			int nVtx0 = cntZ * (m_nBlockWidth + 1) + cntX;
			int nVtx1 = cntZ * (m_nBlockWidth + 1) + cntX + 1;
			int nVtx2 = (cntZ + 1) * (m_nBlockWidth + 1) + cntX;
			int nVtx3 = (cntZ + 1) * (m_nBlockWidth + 1) + cntX + 1;

			//1
			vec0 = pVtx[nVtx3].pos - pVtx[nVtx1].pos;
			vec1 = pVtx[nVtx0].pos - pVtx[nVtx1].pos;
			D3DXVec3Cross(&nor1, &vec0, &vec1);
			D3DXVec3Normalize(&nor1, &nor1);

			//2
			vec0 = pVtx[nVtx0].pos - pVtx[nVtx2].pos;
			vec1 = pVtx[nVtx3].pos - pVtx[nVtx2].pos;
			D3DXVec3Cross(&nor2, &vec0, &vec1);
			D3DXVec3Normalize(&nor2, &nor2);

			//0
			nor0 = (nor1 + nor2);
			D3DXVec3Normalize(&nor0, &nor0);
			//3
			nor3 = (nor1 + nor2);
			D3DXVec3Normalize(&nor3, &nor3);

			pNor[nVtx0].push_back(nor0);
			pNor[nVtx1].push_back(nor1);
			pNor[nVtx2].push_back(nor2);
			pNor[nVtx3].push_back(nor3);
		}
	}

	for (int nCount = 0; nCount < (m_nBlockWidth + 1) * (m_nBlockDepth + 1); nCount++, pVtx++)
	{
		D3DXVECTOR3 nor = IS_Utility::VEC3_ZERO;

		//全法線を足す
		for (unsigned int cntNor = 0; cntNor < pNor[nCount].size(); cntNor++)
		{
			nor += pNor[nCount].at(cntNor);
		}
		D3DXVec3Normalize(&nor, &nor);

		//法線ベクトル
		pVtx->nor = nor;
	}

	delete[] pNor;

	//頂点バッファをアンロック
	m_pVtxbuff->Unlock();
}

//=================================
//インデックス設定
//=================================
void CMeshField::SetIdxBuff(void)
{
	WORD *pIdx;	//インデックス情報へのポインタ
	int nCntWidth;	//インデックスカウンタ

	//インデックスバッファ設定
	//バッファロック
	m_pIdxBuff->Lock(0, 0, (void **)&pIdx, 0);

	for (nCntWidth = 0; nCntWidth < m_nBlockDepth - 1; nCntWidth++)
	{
		//グネグネパート
		pIdx = SetIdxSwaingField(nCntWidth, pIdx);

		//チョン打ちするパート
		//最後のインデックス情報を次のにも入れる
		*pIdx = m_nBlockWidth + (m_nBlockWidth + 1) * nCntWidth;
		pIdx++;

		//その次のに次のループで最初に入る数字を入れる
		*pIdx = (m_nBlockWidth + 1) + (m_nBlockWidth + 1) * (nCntWidth + 1);
		pIdx++;
	}

	//最後のグネグネパート
	SetIdxSwaingField(nCntWidth, pIdx);

	//バッファアンロック
	m_pIdxBuff->Unlock();
}

//========================
//グネグネインデックス設定処理
//========================
WORD* CMeshField::SetIdxSwaingField(int nCntWidth, WORD *pIdx)
{
	//グネグネパート
	for (int nCountHeight = 0; nCountHeight < (m_nBlockWidth + 1) * 2; nCountHeight++, pIdx++)
	{
		*pIdx = (m_nBlockWidth + 1) * ((nCountHeight % 2) ^ 0x1) + nCountHeight / 2 + (m_nBlockWidth + 1) * nCntWidth;
	}
	return pIdx;
}

//========================
//乗っている面と法線取得処理
//========================
bool CMeshField::GetLanding(D3DXVECTOR3 posOld, D3DXVECTOR3 poslanding, D3DXVECTOR3* pOutposVtx, D3DXVECTOR3* pOutNor, D3DXVECTOR3* pOutUpVec)
{
	//頂点バッファのロックと頂点情報へのポインタを取得
	VERTEX_3D* pVtx;	//設定用ポインタ
	m_pVtxbuff->Lock(0, 0, (void**)&pVtx, 0);
	bool bLand = false;
	float fLengthNear = FLT_MAX;
	D3DXVECTOR3 posNearVtx = IS_Utility::VEC3_ZERO;
	D3DXVECTOR3 norNearVtx = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 dust;

	for (int cntZ = 0; cntZ < m_nBlockDepth; cntZ++)
	{
		for (int cntX = 0; cntX < m_nBlockWidth; cntX++)
		{
			int nVtx0 = cntZ * (m_nBlockWidth + 1) + cntX;
			int nVtx1 = cntZ * (m_nBlockWidth + 1) + cntX + 1;
			int nVtx2 = (cntZ + 1) * (m_nBlockWidth + 1) + cntX;
			int nVtx3 = (cntZ + 1) * (m_nBlockWidth + 1) + cntX + 1;
			D3DXVECTOR3 posVtx[4];
			posVtx[0] = IS_Utility::RotateVtx(pVtx[nVtx0].pos, m_rot, m_pos);
			posVtx[1] = IS_Utility::RotateVtx(pVtx[nVtx1].pos, m_rot, m_pos);
			posVtx[2] = IS_Utility::RotateVtx(pVtx[nVtx2].pos, m_rot, m_pos);
			posVtx[3] = IS_Utility::RotateVtx(pVtx[nVtx3].pos, m_rot, m_pos);

			if (D3DXVec3Cross(&dust, &(posVtx[3] - posVtx[2]), &(poslanding - (posVtx[2])))->y <= 0.0f &&
				D3DXVec3Cross(&dust, &(posVtx[0] - posVtx[3]), &(poslanding - (posVtx[3])))->y <= 0.0f &&
				D3DXVec3Cross(&dust, &(posVtx[2] - posVtx[0]), &(poslanding - (posVtx[0])))->y <= 0.0f)
			{
				D3DXVECTOR3 vec1, vec2, nor;
				vec1 = posVtx[0] - posVtx[2];
				vec2 = posVtx[3] - posVtx[2];
				D3DXVec3Cross(&nor, &vec1, &vec2);
				D3DXVec3Normalize(&nor, &nor);
				if (nor.y != 0.0f)
				{
					float fLength = fabsf(posOld.y - posVtx[2].y);
					if (fLengthNear > fLength)
					{
						posNearVtx = posVtx[2];
						norNearVtx = nor;
						fLengthNear = fLength;
						bLand = true;

						if (pOutUpVec != nullptr)
						{
							D3DXVec3Normalize(pOutUpVec, &(posVtx[0] - posVtx[2]));
						}
					}
				}
			}

			if (D3DXVec3Cross(&dust, &(posVtx[0] - posVtx[1]), &(poslanding - (posVtx[1])))->y <= 0.0f &&
				D3DXVec3Cross(&dust, &(posVtx[3] - posVtx[0]), &(poslanding - (posVtx[0])))->y <= 0.0f &&
				D3DXVec3Cross(&dust, &(posVtx[1] - posVtx[3]), &(poslanding - (posVtx[3])))->y <= 0.0f)
			{
				D3DXVECTOR3 vec1, vec2, nor;
				vec1 = posVtx[3] - posVtx[1];
				vec2 = posVtx[0] - posVtx[1];
				D3DXVec3Cross(&nor, &vec1, &vec2);
				D3DXVec3Normalize(&nor, &nor);
				if (nor.y != 0.0f)
				{
					float fLength = fabsf(posOld.y - posVtx[1].y);
					if (fLengthNear > fLength)
					{
						posNearVtx = posVtx[1];
						norNearVtx = nor;
						fLengthNear = fLength;
						bLand = true;

						if (pOutUpVec != nullptr)
						{
							D3DXVec3Normalize(pOutUpVec, &(posVtx[1] - posVtx[3]));
						}
					}
				}
			}
		}
	}

	//頂点バッファをアンロック
	m_pVtxbuff->Unlock();

	//代入
	if (pOutposVtx != nullptr)
	{
		*pOutposVtx = posNearVtx;
	}
	if (pOutNor != nullptr)
	{
		*pOutNor = norNearVtx;
	}

	return bLand;
}

//========================
//除外処理
//========================
void CMeshField::Exclusion(void)
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
	m_nNumAll--;	//総数減らす
}

//========================
//高さ取得
//========================
float CMeshField::GetHeight(D3DXVECTOR3 posOld, D3DXVECTOR3 posNew)
{
	D3DXVECTOR3 posVtx, nor;
	if (GetLanding(posOld, posNew, &posVtx, &nor) == true)
	{
		return (-((posNew.x - (posVtx.x)) * nor.x + (posNew.z - (posVtx.z)) * nor.z) / nor.y) + posVtx.y;
	}
	else
	{
		return -FLT_MAX;
	}
}

//========================
//立っているところの角度取得
//========================
D3DXVECTOR3 CMeshField::GetLandingRot(D3DXVECTOR3 posOld, D3DXVECTOR3 posLanding, float rotY)
{
	D3DXVECTOR3 posVtx, nor;
	if (GetLanding(posOld, posLanding, &posVtx, &nor) == true)
	{
		D3DXVECTOR3 rot;
		rot = IS_Utility::RotateVtx(nor, D3DXVECTOR3(0.5f * D3DX_PI, rotY, 0.0f), IS_Utility::VEC3_ZERO);
		return rot;
	}
	else
	{
		return IS_Utility::VEC3_ZERO;
	}
}

//========================
//高さ取得(ALL)
//========================
float CMeshField::GetHeightAll(D3DXVECTOR3 posOld, D3DXVECTOR3 posNew)
{
	CMeshField* pMeshField = m_pTop;
	CMeshField* pMeshFieldNear = nullptr;
	float fLengthNear = FLT_MAX;
	D3DXVECTOR3 posVtxNear, norNear;

	while (pMeshField != nullptr)
	{
		D3DXVECTOR3 posVtx, nor;
		if (pMeshField->GetLanding(posOld, posNew, &posVtx, &nor) == true)
		{
			float fLength = fabsf(posOld.y - posVtx.y);
			if (fLengthNear > fLength)
			{
				fLengthNear = fLength;
				pMeshFieldNear = pMeshField;
			}
		}

		pMeshField = pMeshField->GetNext();
	}

	if (pMeshFieldNear != nullptr)
	{
		return pMeshFieldNear->GetHeight(posOld, posNew);
	}
	return -FLT_MAX;
}

//========================
//立っているところの角度取得(ALL)
//========================
D3DXVECTOR3 CMeshField::GetLandingRotAll(D3DXVECTOR3 posOld, D3DXVECTOR3 posLanding, float rotY)
{
	CMeshField* pMeshField = m_pTop;
	CMeshField* pMeshFieldNear = nullptr;
	float fLengthNear = FLT_MAX;
	D3DXVECTOR3 posVtxNear, norNear;

	while (pMeshField != nullptr)
	{
		D3DXVECTOR3 posVtx, nor;
		if (pMeshField->GetLanding(posOld, posLanding, &posVtx, &nor) == true)
		{
			float fLength = fabsf(posOld.y - posVtx.y);
			if (fLengthNear > fLength)
			{
				fLengthNear = fLength;
				pMeshFieldNear = pMeshField;
			}
		}

		pMeshField = pMeshField->GetNext();
	}

	if (pMeshFieldNear != nullptr)
	{
		return pMeshFieldNear->GetLandingRot(posOld, posLanding, rotY);
	}
	return IS_Utility::VEC3_ZERO;
}