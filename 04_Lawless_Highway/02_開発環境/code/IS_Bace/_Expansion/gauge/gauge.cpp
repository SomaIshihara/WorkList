//======================================================
//
//ゲージ処理[gauge.cpp]
//Author:石原颯馬
//
//======================================================
#include "gauge.h"
#include "..\..\..\main.h"
#include "..\..\_Core\manager\manager.h"
#include "..\..\_Core\renderer\renderer.h"
#include "..\..\_Core\texture\texture.h"
#include "..\..\_Core\input\input.h"
#include "..\..\_Core\_object\object_empty\object.h"
#include "..\..\_Expansion\number\number.h"
#include"..\..\_Core\utility\Utility.h"

//******************************************************************
// 基本タイマークラス
//******************************************************************
//=================================
//コンストラクタ
//=================================
CGauge::CGauge(int nPriority) : CObject(nPriority)
{
	//値クリア
	m_pos = IS_Utility::VEC3_ZERO;
	m_defaultPos = IS_Utility::VEC3_ZERO;
	m_rot = IS_Utility::VEC3_ZERO;
	m_fDefaultWidth = 0.0f;
	m_fGaugeRate = 0.0f;

	for (int cnt = 0; cnt < 2; cnt++)
	{
		m_apObj[cnt] = nullptr;
	}
}

//=================================
//デストラクタ
//=================================
CGauge::~CGauge()
{
}

//=================================
//初期化
//=================================
HRESULT CGauge::Init(void)
{
	return S_OK;
}

//=================================
//終了
//=================================
void CGauge::Uninit(void)
{
	//タイムオブジェクト破棄
	Release();
}

//=================================
//更新
//=================================
void CGauge::Update(void)
{
	
}

//=================================
//描画
//=================================
void CGauge::Draw(void)
{
	//勝手にやってくれます
}

//=================================
//生成処理
//=================================
CGauge* CGauge::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight)
{
	CGauge* pGauge = nullptr;

	if (pGauge == nullptr)
	{
		//タイマー管理オブジェクト生成
		pGauge = new CGauge;

		//タイマー管理オブジェクト初期化
		pGauge->Init();

		//データ設定
		pGauge->m_pos = pos;
		pGauge->m_rot = rot;
		pGauge->m_fDefaultWidth = fWidth;
		pGauge->m_defaultPos = pos;

		//オブジェクト生成
		if (pGauge->m_apObj[0] == nullptr)
		{
			pGauge->m_apObj[0] = CObject2D::Create(pos, rot, fWidth, fHeight);
			pGauge->m_apObj[0]->BindTexture(-1);
			pGauge->m_apObj[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (pGauge->m_apObj[1] == nullptr)
		{
			pGauge->m_apObj[1] = CObject2D::Create(pos, rot, fWidth * 0.95f, fHeight * 0.95f);
			pGauge->m_apObj[1]->BindTexture(-1);
			pGauge->m_apObj[1]->SetCol(D3DXCOLOR(1.0f, 0.5f, 0.2f, 1.0f));
		}
		
		return pGauge;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//位置設定
//=================================
void CGauge::SetPos(const D3DXVECTOR3 pos)
{
	//大元設定
	m_pos = pos;

	//各オブジェクト設定
	m_apObj[0]->SetPos(pos);
	m_apObj[1]->SetPos(pos);
}

//=================================
//角度設定
//=================================
void CGauge::SetRot(const D3DXVECTOR3 rot)
{
	//大元設定
	m_rot = rot;

	//各オブジェクト設定
	m_apObj[0]->SetRot(rot);
	m_apObj[1]->SetRot(rot);
}

//=================================
//割合設定
//=================================
void CGauge::SetRate(const float rate)
{
	m_fGaugeRate = IS_Utility::Clamp(rate, 1.0f, 0.0f);

	float fHeight = m_apObj[1]->GetHeight();
	D3DXVECTOR3 pos = m_defaultPos;
	pos.x -= m_fDefaultWidth * 0.5f;
	m_apObj[1]->SetPos(pos + D3DXVECTOR3((m_fDefaultWidth * 0.5f) * m_fGaugeRate, 0.0f, 0.0f));
	m_apObj[1]->SetSize(m_fDefaultWidth * m_fGaugeRate, fHeight);
}
