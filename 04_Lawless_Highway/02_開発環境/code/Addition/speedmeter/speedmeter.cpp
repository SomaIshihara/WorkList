//======================================================
//
//スピードメーター処理[speedmeter.cpp]
//Author:石原颯馬
//
//======================================================
#include "speedmeter.h"
#include "../../IS_Bace/_Core/texture/texture.h"
#include "../../IS_Bace/_Core/_object/object_2d/object2D.h"
#include "../../IS_Bace/_Core/utility/Utility.h"

//=================================
//コンストラクタ
//=================================
CSpeedMeter::CSpeedMeter()
{
	m_pos = IS_Utility::VEC3_ZERO;
	m_fRadius = 0.0f;
	m_pObjFrame = nullptr;
	m_pObjMeter = nullptr;
}

//=================================
//デストラクタ
//=================================
CSpeedMeter::~CSpeedMeter()
{
}

//=================================
//初期化
//=================================
HRESULT CSpeedMeter::Init(void)
{
	//オブジェクト生成
	m_pObjFrame = CObject2D::Create(m_pos, IS_Utility::VEC3_ZERO, m_fRadius, m_fRadius, CObject::PRIORITY_05);
	m_pObjFrame->BindTexture(CTexture::PRELOAD_35_SPEEDMETER_01);
	m_pObjMeter = CObject2D::Create(m_pos, IS_Utility::VEC3_ZERO, m_fRadius, m_fRadius, CObject::PRIORITY_05);
	m_pObjMeter->BindTexture(CTexture::PRELOAD_36_SPEEDMETER_02);

	return S_OK;
}

//=================================
//終了
//=================================
void CSpeedMeter::Uninit(void)
{
	Release();
}

//=================================
//更新
//=================================
void CSpeedMeter::Update(void)
{
	
}

//=================================
//描画
//=================================
void CSpeedMeter::Draw(void)
{
	
}

//=================================
//位置設定
//=================================
void CSpeedMeter::SetPos(const D3DXVECTOR3 pos)
{
	//大元設定
	m_pos = pos;

	//オブジェクト設定
	m_pObjFrame->SetPos(pos);
	m_pObjMeter->SetPos(pos);
}

//=================================
//ゲージ設定
//=================================
void CSpeedMeter::SetGauge(const float gauge)
{
	float clampGauge = IS_Utility::Clamp(gauge, 1.0f, 0.0f);
	m_pObjMeter->SetRot(D3DXVECTOR3(0.0f, 0.0f, -0.5f * D3DX_PI * clampGauge));
}

//=================================
//生成
//=================================
CSpeedMeter* CSpeedMeter::Create(const D3DXVECTOR3 pos, const float fRadius)
{
	CSpeedMeter* pSpeedMeter = nullptr;

	if (pSpeedMeter == nullptr)
	{
		//オブジェクトの生成
		pSpeedMeter = new CSpeedMeter;

		//初期化
		pSpeedMeter->m_pos = pos;
		pSpeedMeter->m_fRadius = fRadius;
		pSpeedMeter->Init();

		return pSpeedMeter;
	}
	else
	{
		return nullptr;
	}
}
