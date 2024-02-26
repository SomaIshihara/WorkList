//======================================================
//
//背景（2D）処理[bg.cpp]
//Author:石原颯馬
//
//======================================================
#include "bg.h"
#include "..\..\..\main.h"
#include "..\..\_Core\manager\manager.h"
#include "..\..\_Core\renderer\renderer.h"
#include "..\..\_Core\texture\texture.h"
#include "..\..\_Core\utility\Utility.h"

//=================================
//コンストラクタ
//=================================
CBG::CBG(int nPriority) : CObject2D(nPriority)
{
	m_nIdxTexture = -1;
}

//=================================
//デストラクタ
//=================================
CBG::~CBG()
{
}

//=================================
//初期化
//=================================
HRESULT CBG::Init(void)
{
	//親クラス処理
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	SetRot(IS_Utility::VEC3_ZERO);
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	return S_OK;
}

//=================================
//終了
//=================================
void CBG::Uninit(void)
{
	//親クラス処理
	CObject2D::Uninit();
}

//=================================
//更新
//=================================
void CBG::Update(void)
{
	//親クラス処理
	CObject2D::Update();
}

//=================================
//描画
//=================================
void CBG::Draw(void)
{
	//親クラス処理
	CObject2D::Draw();
}

//=================================
//生成処理
//=================================
CBG* CBG::Create(const int nPriority)
{
	CBG* pObjBG = nullptr;

	if (pObjBG == nullptr)
	{
		//背景の生成
		pObjBG = new CBG(nPriority);

		//初期化
		pObjBG->Init();

		return pObjBG;
	}
	else
	{
		return nullptr;
	}
}