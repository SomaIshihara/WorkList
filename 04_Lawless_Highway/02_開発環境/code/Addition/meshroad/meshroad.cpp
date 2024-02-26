//======================================================
//
//メッシュ道路処理[meshroad.cpp]
//Author:石原颯馬
//
//======================================================
#include "meshroad.h"
#include "../../IS_Bace/_Expansion/meshfield/meshField.h"
#include "../../IS_Bace/_Core/utility/Utility.h"
#include "../../IS_Bace/_Core/utility/Utility_Vector.h"
#include <vector>

using namespace std;

//静的メンバ変数
CMeshRoad* CMeshRoad::m_pTop = nullptr;
CMeshRoad* CMeshRoad::m_pCur = nullptr;
int CMeshRoad::m_nNumAll = 0;

//無名名前空間
namespace
{
	const int BLOCK_X = 2;
}

//=================================
//コンストラクタ
//=================================
CMeshRoad::CMeshRoad()
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
	m_nNumAll++;
}

//=================================
//デストラクタ
//=================================
CMeshRoad::~CMeshRoad()
{
}

//=================================
//初期化
//=================================
HRESULT CMeshRoad::Init(void)
{
	CMeshField::Init();

	return S_OK;
}

//=================================
//終了
//=================================
void CMeshRoad::Uninit(void)
{
	CMeshField::Uninit();
}

//=================================
//更新
//=================================
void CMeshRoad::Update(void)
{
	CMeshField::Update();
}

//=================================
//描画
//=================================
void CMeshRoad::Draw(void)
{
	CMeshField::Draw();
}

//=================================
//生成
//=================================
CMeshRoad* CMeshRoad::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fLength,
	const std::vector<D3DXVECTOR3>& vVector)
{
	CMeshRoad* pMeshField = nullptr;

	if (pMeshField == nullptr)
	{
		//オブジェクトの生成
		pMeshField = new CMeshRoad;

		//初期化
		pMeshField->SetPos(pos);
		pMeshField->SetRot(rot);
		pMeshField->SetSize(fLength, fLength);
		pMeshField->SetBlock(BLOCK_X, vVector.size());
		pMeshField->m_vVector = vVector;
		pMeshField->Init();
		pMeshField->SetVtxBuff();

		return pMeshField;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//生成（便利ベクトル版）
//=================================
CMeshRoad* CMeshRoad::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fLength,
	const std::vector<IS_Utility::Utility_Vector3>& vVector)
{
	int nVectorNum = vVector.size();
	std::vector<D3DXVECTOR3> vDXVector;

	//消す
	vDXVector.clear();

	for (int cnt = 0; cnt < nVectorNum; cnt++)
	{
		vDXVector.push_back(vVector[cnt]);
	}

	return CMeshRoad::Create(pos, rot, fLength, vDXVector);
}

//=================================
//除外処理
//=================================
void CMeshRoad::Exclusion(void)
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

	CMeshField::Exclusion();
}

//=================================
//頂点設定
//=================================
void CMeshRoad::SetVtxBuff(void)
{
	VERTEX_3D* pVtx;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	float fLength = GetWidth();
	int nBlock = GetBlockDepth();
	D3DXVECTOR3 posCenter = IS_Utility::VEC3_ZERO;

	//バッファロック
	//頂点バッファのロックと頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//最初の頂点設定
	//中心
	pVtx[1].pos = posCenter;

	//両端
	pVtx[0].pos = D3DXVECTOR3(fLength, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-fLength, 0.0f, 0.0f);
	//頂点ずらす
	pVtx += 3;

	//頂点座標
	for (int nCount = 0; nCount < nBlock; nCount++, pVtx += 3)
	{
		//使用ベクトル
		D3DXVECTOR3 vec = m_vVector[nCount];

		//中心
		pVtx[1].pos = posCenter + (vec * fLength);
		posCenter += (vec * fLength);

		D3DXMATRIX mtx;

		D3DXMatrixIdentity(&mtx);
		D3DXMatrixRotationY(&mtx, -0.5f * D3DX_PI);
		D3DXVec3TransformCoord(&vec, &vec, &mtx);
		vec.y = 0.0f;
		D3DXVec3Normalize(&vec, &vec);

		//両端
		pVtx[2].pos = pVtx[1].pos + (vec * fLength);

		vec *= -1.0f;
		pVtx[0].pos = pVtx[1].pos + (vec * fLength);

	}

	//頂点バッファをアンロック
	pVtxBuff->Unlock();
}

//========================
//高さ取得
//========================
float CMeshRoad::GetHeight(D3DXVECTOR3 posOld, D3DXVECTOR3 posNew)
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
//自動操縦用移動方向取得
//========================
D3DXVECTOR3 CMeshRoad::GetPirotRot(D3DXVECTOR3 posOld, D3DXVECTOR3 posLanding)
{
	D3DXVECTOR3 posVtx, nor, vec;
	if (GetLanding(posOld, posLanding, &posVtx, &nor, &vec) == true)
	{
		return vec;
	}
	else
	{
		return IS_Utility::VEC3_ZERO;
	}
}

//========================
//高さ取得(ALL)
//========================
float CMeshRoad::GetHeightAll(D3DXVECTOR3 posOld, D3DXVECTOR3 posNew)
{
	CMeshRoad* pMeshRoad = m_pTop;
	CMeshRoad* pMeshRoadNear = nullptr;
	float fLengthNear = FLT_MAX;
	D3DXVECTOR3 posVtxNear, norNear;

	while (pMeshRoad != nullptr)
	{
		D3DXVECTOR3 posVtx, nor;
		if (pMeshRoad->GetLanding(posOld, posNew, &posVtx, &nor) == true)
		{
			float fLength = fabsf(posOld.y - posVtx.y);
			if (fLengthNear > fLength)
			{
				fLengthNear = fLength;
				pMeshRoadNear = pMeshRoad;
			}
		}

		pMeshRoad = pMeshRoad->GetNext();
	}

	if (pMeshRoadNear != nullptr)
	{
		return pMeshRoadNear->GetHeight(posOld, posNew);
	}
	return -FLT_MAX;
}

//========================
//自動操縦用移動方向取得(ALL)
//========================
D3DXVECTOR3 CMeshRoad::GetPirotRotAll(D3DXVECTOR3 posOld, D3DXVECTOR3 posLanding)
{
	CMeshRoad* pMeshField = m_pTop;
	CMeshRoad* pMeshFieldNear = nullptr;
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
		return pMeshFieldNear->GetPirotRot(posOld, posLanding);
	}
	return IS_Utility::VEC3_ZERO;
}
