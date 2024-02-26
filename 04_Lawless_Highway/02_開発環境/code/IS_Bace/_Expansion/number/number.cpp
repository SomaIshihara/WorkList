//======================================================
//
//数字処理[number.cpp]
//Author:石原颯馬
//
//======================================================
#include "number.h"
#include "..\..\_Core\manager\manager.h"
#include "..\..\_Core\renderer\renderer.h"
#include "..\..\_Core\texture\texture.h"
#include "..\..\_Core\_object\object_2d\object2D.h"
#include <assert.h>

//=================================
//コンストラクタ（デフォルト）
//=================================
CNumber::CNumber(int nPriority) :CObject2D(nPriority)
{
}

//=================================
//デストラクタ
//=================================
CNumber::~CNumber()
{
}

//=================================
//初期化
//=================================
HRESULT CNumber::Init(void)
{
	//親クラス処理
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	//テクスチャ設定
	D3DXVECTOR2 tex0, tex3;
	tex0 = D3DXVECTOR2(0.0f, 0.0f);
	tex3 = D3DXVECTOR2(1.0f, 1.0f);

	if (FAILED(SetTex(tex0, tex3)))
	{
		return E_FAIL;
	}

	return S_OK;
}
//=================================
//終了
//=================================
void CNumber::Uninit(void)
{
	//親クラス処理
	CObject2D::Uninit();
}

//=================================
//更新
//=================================
void CNumber::Update(void)
{
	//親クラス処理
	CObject2D::Update();
}

//=================================
//描画
//=================================
void CNumber::Draw(void)
{
	//親クラス処理
	CObject2D::Draw();
}

//=================================
//生成処理
//=================================
CNumber* CNumber::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight)
{
	CNumber* pNumber = nullptr;

	if (pNumber == nullptr)
	{
		//生成
		pNumber = new CNumber;

		//初期化
		pNumber->Init();

		//データ設定
		pNumber->SetPos(pos);
		pNumber->SetRot(rot);
		pNumber->SetSize(fWidth, fHeight);

		return pNumber;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//数字分割処理（nDigitは0以上で入力すること）
//=================================
void CNumber::SetNumber(const int nSource, const int nDigit)
{
	int nNumber = 0;	//1桁分の数字

	if (nDigit < 0)
	{//不正
		assert(false);
	}

	//桁ごとの数字を入れる
	nNumber = nSource % (int)pow(10, nDigit + 1) / (int)pow(10, nDigit);

	//パターン幅高さ取得
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();
	int nIdx = GetIdxTexture();	//テクスチャ番号取得
	int nPatWidth = pTexture->GetPatWidth(nIdx);
	int nPatHeight = pTexture->GetPatHeight(nIdx);

	//テクスチャ設定
	D3DXVECTOR2 tex0, tex3;
	tex0 = D3DXVECTOR2((float)(nNumber % nPatWidth) / nPatWidth,
		(float)(nNumber / nPatWidth) / nPatHeight);
	tex3 = D3DXVECTOR2((float)(nNumber % nPatWidth + 1) / nPatWidth,
		(float)(nNumber / nPatWidth + 1) / nPatHeight);

	if (FAILED(SetTex(tex0, tex3)))
	{
		assert(false);
	}
}

//=================================
//テクスチャ設定
//=================================
void CNumber::BindTexture(int nIdx)
{
	//テクスチャ設定
	CObject2D::BindTexture(nIdx);

	//パターン幅高さ取得
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();
	int nPatWidth = pTexture->GetPatWidth(nIdx);
	int nPatHeight = pTexture->GetPatHeight(nIdx);

	//テクスチャ設定
	D3DXVECTOR2 tex0, tex3;
	tex0 = D3DXVECTOR2((float)(0 % nPatWidth) / nPatWidth,
		(float)(0 / nPatWidth) / nPatHeight);
	tex3 = D3DXVECTOR2((float)(0 % nPatWidth + 1) / nPatWidth,
		(float)(0 / nPatWidth + 1) / nPatHeight);

	if (FAILED(SetTex(tex0, tex3)))
	{
		assert(false);
	}
}
