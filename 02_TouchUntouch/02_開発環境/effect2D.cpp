//======================================================
//
//エフェクト処理(2D)[effect2D.cpp]
//Author:石原颯馬
//
//======================================================
#include "effect2D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//=================================
//コンストラクタ
//=================================
CEffect2D::CEffect2D(const int nLife, int nPriority) : CObject2D(nPriority), m_nDefLife(nLife)
{
	//値クリア
	m_nIdxTexture = -1;
	m_effect.move = CManager::VEC3_ZERO;
	m_effect.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_effect.nLife = 0;
}

//=================================
//デストラクタ
//=================================
CEffect2D::~CEffect2D()
{
}

//=================================
//初期化
//=================================
HRESULT CEffect2D::Init(void)
{
	//親クラス処理
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	//テクスチャ読み込み
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\effect000.jpg");

	return S_OK;
}

//=================================
//終了
//=================================
void CEffect2D::Uninit(void)
{
	//親クラス処理
	CObject2D::Uninit();
}

//=================================
//更新
//=================================
void CEffect2D::Update(void)
{
	//親クラス処理
	CObject2D::Update();

	//移動
	D3DXVECTOR3 pos = GetPos();
	pos += m_effect.move;
	SetPos(pos);

	//寿命管理
	m_effect.nLife--;	//減らす

	//不透明度設定
	m_effect.col.a = (float)m_effect.nLife / m_nDefLife;
	SetCol(m_effect.col);

	if (m_effect.nLife <= 0)
	{//死んだ
		Uninit();	//終了
	}
}

//=================================
//描画
//=================================
void CEffect2D::Draw(void)
{
	//Zテスト無効化
	CManager::GetInstance()->GetRenderer()->SetEnableZTest(false);

	//アルファテスト有効化
	CManager::GetInstance()->GetRenderer()->SetEnableAlplaTest(true);

	//ブレンディング種類を加算合成に変更
	CManager::GetInstance()->GetRenderer()->SetBlendType(CRenderer::BLENDTYPE_ADD);

	//親クラス処理
	CObject2D::Draw();

	//ブレンディング種類を通常状態に戻す
	CManager::GetInstance()->GetRenderer()->SetBlendType(CRenderer::BLENDTYPE_NORMAL);

	//アルファテスト無効化
	CManager::GetInstance()->GetRenderer()->SetEnableAlplaTest(false);

	//Zテスト無効化
	CManager::GetInstance()->GetRenderer()->SetEnableZTest(true);
}

//=================================
//生成処理
//=================================
CEffect2D* CEffect2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fWidth, const float fHeight,
	const D3DXCOLOR col, const int nLife)
{
	CEffect2D* pObjEffect = nullptr;

	if (pObjEffect == nullptr)
	{
		//背景の生成
		pObjEffect = new CEffect2D(nLife);

		//初期化
		pObjEffect->Init();

		//データ設定
		pObjEffect->m_effect.move = move;
		pObjEffect->m_effect.col = col;
		pObjEffect->m_effect.nLife = nLife;
		pObjEffect->SetPos(pos);
		pObjEffect->SetRot(CManager::VEC3_ZERO);
		pObjEffect->SetSize(fWidth, fHeight);

		//テクスチャ設定
		pObjEffect->BindTexture(pObjEffect->m_nIdxTexture);

		return pObjEffect;
	}
	else
	{
		return nullptr;
	}
}