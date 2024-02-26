//======================================================
//
//メッシュ軌道処理[meshorbit.cpp]
//Author:石原颯馬
//
//======================================================
#include "meshorbit.h"
#include "../../IS_Bace/_Core/utility/Utility.h"
#include "../../IS_Bace/_Core/utility/Utility_Vector.h"
#include <vector>

using namespace std;

//無名名前空間
namespace
{
	const int BLOCK_X = 1;
}

//=================================
//コンストラクタ
//=================================
CMeshOrbit::CMeshOrbit(int nPriority) : CMeshField(nPriority)
{
}

//=================================
//デストラクタ
//=================================
CMeshOrbit::~CMeshOrbit()
{
}

//=================================
//初期化
//=================================
HRESULT CMeshOrbit::Init(void)
{
	CMeshField::Init();

	return S_OK;
}

//=================================
//終了
//=================================
void CMeshOrbit::Uninit(void)
{
	if (m_pVector != nullptr)
	{
		delete[] m_pVector;
		m_pVector = nullptr;
	}

	CMeshField::Uninit();
}

//=================================
//更新
//=================================
void CMeshOrbit::Update(void)
{
	CMeshField::Update();
}

//=================================
//描画
//=================================
void CMeshOrbit::Draw(void)
{
	CMeshField::Draw();
}

//=================================
//生成
//=================================
CMeshOrbit* CMeshOrbit::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fLength, const int nBlock)
{
	CMeshOrbit* pMeshOrbit = nullptr;

	if (pMeshOrbit == nullptr)
	{
		//オブジェクトの生成
		pMeshOrbit = new CMeshOrbit;

		//初期化
		pMeshOrbit->SetPos(pos);
		pMeshOrbit->SetRot(rot);
		pMeshOrbit->SetSize(fLength, fLength);
		pMeshOrbit->SetBlock(BLOCK_X, nBlock);
		pMeshOrbit->m_pVector = new IS_Utility::Utility_Vector3[nBlock];
		pMeshOrbit->Init();
		pMeshOrbit->SetVtxBuff();

		return pMeshOrbit;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//頂点設定
//=================================
void CMeshOrbit::SetVtxBuff(void)
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
	pVtx[0].pos = D3DXVECTOR3(fLength, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(-fLength, 0.0f, 0.0f);
	//頂点ずらす
	pVtx += (BLOCK_X + 1);

	//頂点座標
	for (int nCount = 0; nCount < nBlock; nCount++, pVtx += (BLOCK_X + 1))
	{
		//使用ベクトル
		D3DXVECTOR3 vec = m_pVector[nCount];

		//(中心)
		posCenter += (vec * fLength);

		//回転行列生成
		D3DXMATRIX mtx;
		D3DXMatrixIdentity(&mtx);
		D3DXMatrixRotationY(&mtx, -0.5f * D3DX_PI);
		D3DXVec3TransformCoord(&vec, &vec, &mtx);
		D3DXVec3Normalize(&vec, &vec);

		//両端座標配置
		pVtx[1].pos = posCenter + (vec * fLength);

		vec *= -1.0f;
		pVtx[0].pos = posCenter + (vec * fLength);
	}

	//頂点バッファをアンロック
	pVtxBuff->Unlock();
}

//=================================
//ベクトル押し出し
//=================================
void CMeshOrbit::Push(const IS_Utility::Utility_Vector3 vec)
{
	int nBlock = GetBlockDepth();
	if (m_pVector == nullptr)
	{//なぜかぬるぽなら生成
		m_pVector = new IS_Utility::Utility_Vector3[nBlock];
	}

	//なかったら生成してるしあるよね？？？
	if (m_pVector != nullptr)
	{
		//入れ替え
		for (int cnt = nBlock - 1; cnt > 0; cnt--)
		{
			m_pVector[cnt] = m_pVector[cnt - 1];
		}

		//先頭に入れたいのを入れる
		m_pVector[0] = vec;

		//頂点再設定
		SetVtxBuff();
	}
}