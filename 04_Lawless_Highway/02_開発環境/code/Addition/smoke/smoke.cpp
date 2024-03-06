//======================================================
//
//煙処理[smoke.cpp]
//Author:石原颯馬
//
//======================================================
#include "smoke.h"
#include "../../IS_Bace/_Core/manager/manager.h"
#include "../../IS_Bace/_Core/renderer/renderer.h"
#include "../../IS_Bace/_Core/texture/texture.h"

//=================================
//コンストラクタ
//=================================
CSmoke::CSmoke(int nAnimSpeed) : CObjectBillboard(4) , m_nAnimSpeed(nAnimSpeed)
{
	m_nCounter = 0;
	m_nPattern = 0;
}

//=================================
//デストラクタ
//=================================
CSmoke::~CSmoke()
{
}

//=================================
//初期化
//=================================
HRESULT CSmoke::Init(void)
{
	return CObjectBillboard::Init();
}

//=================================
//終了
//=================================
void CSmoke::Uninit(void)
{
	CObjectBillboard::Uninit();
}

//=================================
//更新
//=================================
void CSmoke::Update(void)
{
	//アニメーション
	m_nCounter++;
	if (m_nCounter >= m_nAnimSpeed)
	{
		m_nCounter = 0;

		int nIdxTexture = CObjectBillboard::GetIdxTexture();
		int nPatWidth = CManager::GetInstance()->GetTexture()->GetPatWidth(nIdxTexture);
		int nPatHeight = CManager::GetInstance()->GetTexture()->GetPatHeight(nIdxTexture);
		m_nPattern = (m_nPattern + 1) % (nPatWidth * nPatHeight);

		int u = m_nPattern % nPatWidth;
		int v = m_nPattern / nPatWidth;

		CObjectBillboard::SetTex(u, v);
	}

	CObjectBillboard::Update();
}

//=================================
//描画
//=================================
void CSmoke::Draw(void)
{
	//アルファテスト有効化
	CManager::GetInstance()->GetRenderer()->SetEnableAlplaTest(true);

	//親クラス処理
	CObjectBillboard::Draw();

	//アルファテスト無効化
	CManager::GetInstance()->GetRenderer()->SetEnableAlplaTest(false);
}

//=================================
//生成
//=================================
CSmoke* CSmoke::Create(const D3DXVECTOR3 pos, const float fRadius, const int nAnimSpeed)
{
	CSmoke* pSmoke = nullptr;

	if (pSmoke == nullptr)
	{
		//オブジェクトの生成
		pSmoke = new CSmoke(nAnimSpeed);

		//初期化
		pSmoke->Init();
		pSmoke->SetPos(pos);
		pSmoke->SetRot(D3DXVECTOR3(-0.3f, 0.0f, 0.0f));
		pSmoke->SetSize(fRadius, fRadius);
		pSmoke->SetTex(0, 0);
		pSmoke->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		return pSmoke;
	}
	else
	{
		return nullptr;
	}
}
