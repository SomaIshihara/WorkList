//======================================================
//
//モデルキャラ処理[chara.cpp]
//Author:石原颯馬
//
//======================================================
#include "chara.h"
#include "../../_Core/manager/manager.h"
#include "../../_Core/renderer/renderer.h"
#include "../../_Core/texture/texture.h"
#include "../charmodel/model.h"
#include "../charmotion/motion.h"
#include "../file(legacy)/file.h"
#include "../utility/Utility.h"

//=================================
//コンストラクタ
//=================================
CChara::CChara(int nPriority) : CObject(nPriority)
{
	m_pos = IS_Utility::VEC3_ZERO;
	m_rot = IS_Utility::VEC3_ZERO;
	m_ppModel = nullptr;
	m_pMotion = nullptr;
	m_nNumModel = 0;
}

//=================================
//デストラクタ
//=================================
CChara::~CChara()
{
}

//========================
//初期化処理
//========================
HRESULT CChara::Init(void)
{
	return S_OK;
}

//========================
//終了処理
//========================
void CChara::Uninit(void)
{
	//モーション破棄
	if (m_pMotion != nullptr)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	if (m_ppModel != nullptr)
	{
		for (int cnt = 0; cnt < m_nNumModel; cnt++)
		{//一つずつ消す
			if (m_ppModel[cnt] != nullptr)
			{
				m_ppModel[cnt]->Uninit();
				delete m_ppModel[cnt];
				m_ppModel[cnt] = nullptr;
			}
		}
		delete[] m_ppModel;	//配列そのものを破棄
	}

	Release();
}

//========================
//更新処理
//========================
void CChara::Update(void)
{
	//モデル設定
	if (m_ppModel != nullptr)
	{
		for (int cnt = 0; cnt < m_nNumModel; cnt++)
		{
			if (m_ppModel[cnt] != nullptr)
			{
				m_ppModel[cnt]->Update();
			}
		}
	}

	//モーションがある
	if (m_pMotion != nullptr)
	{
		//モーション更新
		m_pMotion->Update();
	}

	//モーション終了した
	if (m_pMotion->IsFinish() == true && GetMotion() == MOTIONTYPE::MOTIONTYPE_LAND)
	{
		SetMotion(MOTIONTYPE::MOTIONTYPE_NEUTRAL);
	}
}

//========================
//描画処理
//========================
void CChara::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイス取得
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();			//テクスチャオブジェクト取得
	D3DXMATRIX mtxRot, mtxTrans, mtxTexture;							//計算用
	D3DMATERIAL9 matDef;												//現在のマテリアル保存用

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//モデル取得
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

	//アルファテスト有効化
	CRenderer* pRenderer = CManager::GetInstance()->GetRenderer();
	pRenderer->SetEnableAlplaTest(true);

	//モデル描画
	if (m_ppModel != nullptr)
	{
		for (int cnt = 0; cnt < m_nNumModel; cnt++)
		{
			if (m_ppModel[cnt] != nullptr)
			{
				m_ppModel[cnt]->Draw();
			}
		}
	}

	//アルファテスト無効化
	pRenderer->SetEnableAlplaTest(false);

	//マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//========================
//生成処理
//========================
CChara* CChara::Create(const char * pPath, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CChara* pChara = nullptr;

	if (pChara == nullptr)
	{
		//オブジェクト2Dの生成
		pChara = new CChara;

		//初期化
		if (SUCCEEDED(pChara->Init()))
		{
			pChara->m_pos = pos;
			pChara->m_rot = rot;

			//モデル読み込み
			if (FAILED(pChara->SetupModel(pPath)))
			{//うまくいかなかったので生成したもの消す
				pChara->Uninit();
				pChara = nullptr;
			}
		}
		else
		{//うまくいかなかったので生成したもの消す
			pChara->Uninit();
			pChara = nullptr;
		}

		return pChara;
	}
	else
	{
		return nullptr;
	}
}

//========================
//モーション取得処理
//========================
inline CChara::MOTIONTYPE CChara::GetMotion(void)
{
	return (MOTIONTYPE)m_pMotion->GetType();
}

//========================
//モーション設定処理
//========================
inline void CChara::SetMotion(MOTIONTYPE type)
{
	m_pMotion->Set(static_cast<int>(type));
}

//========================
//モデル組み立て処理
//========================
HRESULT CChara::SetupModel(const char* pPath)
{
	//モーション生成・初期化
	m_pMotion = new CMotion;
	if (SUCCEEDED(m_pMotion->Init()) &&
		LoadMotionViewerFile(pPath, &m_ppModel, m_pMotion, &m_nNumModel) == true)
	{
		//モーション補正
		m_ppModel[0]->SetPosOffset(m_ppModel[0]->GetPosOffset());

		//モーション設定
		m_pMotion->Set(0);

		//成功返す
		return S_OK;
	}
	else
	{//うまくいかなかったので生成したもの消す
		return E_FAIL;
	}
}