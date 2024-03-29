//==========================================
//
//フェード表示プログラム[fade.cpp]
//Author:石原颯馬
//
//==========================================
#include "fade.h"
#include "..\bg\bg.h"
#include "..\..\_Core\manager\manager.h"
#include "..\..\_Core\_object\object_empty\object.h"
#include "..\..\_Core\_object\object_2d\object2D.h"
#include "..\..\_Core\renderer\renderer.h"
#include "..\..\_Core\texture\texture.h"

//静的メンバ変数
const float CFade::FADE_SPEED = 0.032f;

//========================
//コンストラクタ
//========================
CFade::CFade() : CBG(PRIORITY_FADE)
{
	m_fade = FADE::FADE_NONE;
	m_modeNext = CScene::MODE::MODE_MAX;
	m_fAlpha = 0.0f;
}

//========================
//デストラクタ
//========================
CFade::~CFade()
{
}

//========================
//フェード初期化処理
//========================
HRESULT CFade::Init(void)
{
	CBG::Init();
	m_fade = FADE::FADE_NONE;	//フェードなし
	return S_OK;
}

//========================
//フェード終了処理
//========================
void CFade::Uninit(void)
{
	CBG::Uninit();
}

//========================
//フェード更新処理
//========================
void CFade::Update(void)
{
	if (m_fade != FADE::FADE_NONE)
	{
		if (m_fade == FADE::FADE_IN)
		{
			m_fAlpha -= FADE_SPEED;
			if (m_fAlpha <= 0.0f)
			{
				m_fAlpha = 0.0f;
				m_fade = FADE::FADE_NONE;
			}
		}
		else if (m_fade == FADE::FADE_OUT)
		{
			m_fAlpha += FADE_SPEED;
			if (m_fAlpha >= 1.0f)
			{
				m_fAlpha = 1.0f;
				m_fade = FADE::FADE_IN;
				CManager::GetInstance()->SetMode(m_modeNext);
			}
		}
	}
	else
	{//フェード終了
		Uninit();
		return;
	}

	//色変える
	CObject2D::SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_fAlpha));

	CBG::Update();
}

//========================
//フェード描画処理
//========================
void CFade::Draw(void)
{
	CBG::Draw();
}

//========================
//フェード生成処理
//========================
CFade* CFade::Create(CScene::MODE sceneNext)
{
	CFade* pFade = nullptr;

	if (pFade == nullptr)
	{
		//フェードの生成
		pFade = new CFade;

		//初期化
		pFade->Init();
		pFade->BindTexture(-1);

		//ちかちか防止
		pFade->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

		//次のシーン設定
		pFade->SetNext(sceneNext);

		return pFade;
	}
	else
	{
		return nullptr;
	}
}

//========================
//次のシーン設定処理
//========================
void CFade::SetNext(CScene::MODE sceneNext)
{
	m_modeNext = sceneNext;
	m_fade = FADE::FADE_OUT;
	m_fAlpha = 0.0f;
}