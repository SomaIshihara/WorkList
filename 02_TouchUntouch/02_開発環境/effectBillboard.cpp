//======================================================
//
//エフェクト(ビルボード)処理[effectBillboard.cpp]
//Author:石原颯馬
//
//======================================================
#include "effectBillboard.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//=================================
//コンストラクタ（デフォルト）
//=================================
CEffectBillboard::CEffectBillboard(const int nLife, int nPriority) : CObjectBillboard(nPriority), m_nDefLife(nLife)
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
CEffectBillboard::~CEffectBillboard()
{
}

//=================================
//初期化
//=================================
HRESULT CEffectBillboard::Init(void)
{
	//親クラス処理
	if (FAILED(CObjectBillboard::Init()))
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
void CEffectBillboard::Uninit(void)
{
	//親クラス処理
	CObjectBillboard::Uninit();
}

//=================================
//更新
//=================================
void CEffectBillboard::Update(void)
{
	//親クラス処理
	CObjectBillboard::Update();

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
void CEffectBillboard::Draw(void)
{
	//Zテスト無効化
	CManager::GetInstance()->GetRenderer()->SetEnableZTest(false);

	//アルファテスト有効化
	CManager::GetInstance()->GetRenderer()->SetEnableAlplaTest(true);

	//ブレンディング種類を加算合成に変更
	CManager::GetInstance()->GetRenderer()->SetBlendType(CRenderer::BLENDTYPE_ADD);

	//親クラス処理
	CObjectBillboard::Draw();

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
CEffectBillboard* CEffectBillboard::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fWidth, const float fHeight,
	const D3DXCOLOR col, const int nLife)
{
	CEffectBillboard* pObjEffect = nullptr;

	if (pObjEffect == nullptr)
	{
		//背景の生成
		pObjEffect = new CEffectBillboard(nLife);

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