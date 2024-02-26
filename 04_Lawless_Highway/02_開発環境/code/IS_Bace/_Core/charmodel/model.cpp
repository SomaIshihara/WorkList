//======================================================
//
//モデル処理[model.cpp]
//Author:石原颯馬
//
//======================================================
#include "model.h"
#include "..\..\_Core\manager\manager.h"
#include "..\..\_Core\renderer\renderer.h"
#include "..\..\_Core\texture\texture.h"
#include "..\utility\Utility.h"
#include <assert.h>

//=================================
//コンストラクタ
//=================================
CModel::CModel()
{
	m_pos = IS_Utility::VEC3_ZERO;
	m_rot = IS_Utility::VEC3_ZERO;
	m_posMotioned = IS_Utility::VEC3_ZERO;
	m_rotMotioned = IS_Utility::VEC3_ZERO;
	m_pParent = nullptr;
	m_dwNumMatModel = 0;
	m_pBuffMat = nullptr;
	m_pMesh = nullptr;
}

//=================================
//デストラクタ
//=================================
CModel::~CModel()
{
}

//========================
//初期化処理
//========================
HRESULT CModel::Init(void)
{
	return S_OK;
}

//========================
//終了処理
//========================
void CModel::Uninit(void)
{
	//メッシュの破棄
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	//マテリアルの破棄
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	//テクスチャ番号破棄
	if (m_pIdxtexture != nullptr)
	{
		delete[] m_pIdxtexture;
		m_pIdxtexture = nullptr;
	}
}

//========================
//更新処理
//========================
void CModel::Update(void)
{
	//いったん仮の値を入れる
	m_posMotioned = m_pos;
	m_rotMotioned = m_rot;
}

//========================
//描画処理
//========================
void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイス取得
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();						//テクスチャオブジェクト取得
	D3DXMATRIX mtxRot, mtxTrans, mtxTexture;							//計算用
	D3DXMATRIX mtxParent;												//親のマトリ
	D3DMATERIAL9 matDef;												//現在のマテリアル保存用
	D3DXMATERIAL *pMat;													//マテリアルデータへのポインタ

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//モデル取得
	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotMotioned.y, m_rotMotioned.x, m_rotMotioned.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, m_posMotioned.x, m_posMotioned.y, m_posMotioned.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//パーツの親マトリ設定
	if (m_pParent != nullptr)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//パーツのマトリと親マトリをかけ合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//マテリアルデータへのポインタ取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMatModel; nCntMat++)
	{
		//マテリアル設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャ設定
		pDevice->SetTexture(0, pTexture->GetAddress(m_pIdxtexture[nCntMat]));

		//モデル描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//========================
//生成処理
//========================
CModel* CModel::Create(const char * pPath, const D3DXVECTOR3 posOffset, const D3DXVECTOR3 rotOffset)
{
	CModel* pModel = nullptr;

	if (pModel == nullptr)
	{
		//オブジェクト2Dの生成
		pModel = new CModel();

		//初期化
		pModel->Init();
		pModel->Load(pPath);
		pModel->m_pos = posOffset;
		pModel->m_rot = rotOffset;

		return pModel;
	}
	else
	{
		return nullptr;
	}
}

//========================
//読み込み処理
//========================
HRESULT CModel::Load(const char* pPath)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイス取得
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();						//テクスチャオブジェクト取得
	m_pIdxtexture = nullptr;											//テクスチャ番号ポインタをnullptrにする

	if (SUCCEEDED(D3DXLoadMeshFromX(
		pPath,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		nullptr,
		&m_pBuffMat,
		nullptr,
		&m_dwNumMatModel,
		&m_pMesh)))
	{
		//テクスチャポインタ確保
		if (m_pIdxtexture == nullptr)
		{//nullptr
		 //テクスチャ番号配列確保
			m_pIdxtexture = new int[(int)m_dwNumMatModel];

			//テクスチャ読み込み
			D3DXMATERIAL* pMat;	//マテリアルポインタ

								//マテリアル情報に対するポインタ取得
			pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

			//テクスチャ読み込み
			for (int nCntTex = 0; nCntTex < (int)m_dwNumMatModel; nCntTex++)
			{
				m_pIdxtexture[nCntTex] = -1;
				if (pMat[nCntTex].pTextureFilename != nullptr)
				{//テクスチャあるよ
				 //テクスチャ読み込み
					m_pIdxtexture[nCntTex] = pTexture->Regist(pMat[nCntTex].pTextureFilename);
				}
				else
				{//ないよ
					m_pIdxtexture[nCntTex] = -1;	//テクスチャ取得時にnullptrになるようにする
				}
			}
		}
		else
		{//おかしい
			assert(false);
		}
	}

	return S_OK;
}
