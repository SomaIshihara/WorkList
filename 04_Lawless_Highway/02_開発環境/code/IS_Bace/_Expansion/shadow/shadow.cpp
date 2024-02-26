//======================================================
//
//影の処理[shadow.cpp]
//Author:石原颯馬
//
//======================================================
#include "shadow.h"
#include "..\..\_Core\manager\manager.h"
#include "..\..\_Core\renderer\renderer.h"
#include "..\..\_Core\texture\texture.h"
#include "..\..\_Core\utility\Utility.h"

//=================================
//コンストラクタ
//=================================
CShadow::CShadow(int nPriority) : CObject3D(nPriority)
{
	m_nIdxTexture = -1;
}

//=================================
//デストラクタ
//=================================
CShadow::~CShadow()
{
}

//========================
//初期化処理
//========================
HRESULT CShadow::Init(void)
{
	//親処理
	CObject3D::Init();

	//テクスチャ読み込み
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\effect000.jpg");

	CObject3D::SetPos(IS_Utility::VEC3_ZERO);	//位置設定
	CObject3D::SetRot(IS_Utility::VEC3_ZERO);	//向き設定
	CObject3D::SetSize(50.0f, 50.0f);		//サイズ設定

	//できた
	return S_OK;
}

//========================
//終了処理
//========================
void CShadow::Uninit(void)
{
	//親処理
	CObject3D::Uninit();
}

//========================
//更新処理
//========================
void CShadow::Update(void)
{
	//親処理
	CObject3D::Update();
}

//========================
//描画処理
//========================
void CShadow::Draw(void)
{
	//レンダラ取得
	CRenderer* pRenderer = CManager::GetInstance()->GetRenderer();

	//ブレンディング種類を加算合成に変更
	pRenderer->SetBlendType(CRenderer::BLENDTYPE::BLENDTYPE_SUB);

	//Zテスト無効化
	pRenderer->SetEnableZTest(false);

	//親処理
	CObject3D::Draw();

	//Zテスト有効化
	pRenderer->SetEnableZTest(true);

	//ブレンディング種類を通常状態に戻す
	pRenderer->SetBlendType(CRenderer::BLENDTYPE::BLENDTYPE_NORMAL);
}

//========================
//生成処理
//========================
CShadow* CShadow::Create(void)
{
	CShadow* pShadow = nullptr;

	if (pShadow == nullptr)
	{
		//オブジェクト2Dの生成
		pShadow = new CShadow();

		//初期化
		pShadow->Init();

		//テクスチャ設定
		pShadow->BindTexture(pShadow->m_nIdxTexture);

		return pShadow;
	}
	else
	{
		return nullptr;
	}
}

//========================
//破棄処理
//========================
void CShadow::Release(void)
{
	CObject3D::Release();
}

//========================
//位置向き設定処理
//========================
void CShadow::Set(D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	//位置向き設定
	SetPos(pos);
	SetRot(rot);
}

//========================
//長さ比較
//========================
float CShadow::ConpareLength(const float fNear, const float fLength)
{
	if (fLength >= 0.0f && fNear > fLength)
	{
		return fLength;
	}
	else
	{
		return fNear;
	}
}
