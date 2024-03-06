//======================================================
//
//スタート文字処理[starttext.cpp]
//Author:石原颯馬
//
//======================================================
#include "starttext.h"
#include "../../IS_Bace/_Core/texture/texture.h"
#include "../../IS_Bace/_Core/_object/object_2d/object2D.h"
#include "../../IS_Bace/_Core/utility/Utility.h"

//=================================
//コンストラクタ
//=================================
CStartText::CStartText() : CObject2D(CObject::PRIORITY_05)
{
	m_nCounterUnLit = 0;
	m_nDefUnLitTime = 0;
	m_nDegUnLitTime = 0;
	m_nUnLitPercent = 100;
}

//=================================
//デストラクタ
//=================================
CStartText::~CStartText()
{
}

//=================================
//初期化
//=================================
HRESULT CStartText::Init(void)
{
	return CObject2D::Init();
}

//=================================
//終了
//=================================
void CStartText::Uninit(void)
{
	CObject2D::Uninit();
}

//=================================
//更新
//=================================
void CStartText::Update(void)
{
	if (m_nCounterUnLit > 0)
	{//消灯中
		m_nCounterUnLit--;

		CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	else
	{//消灯してない
		int nRand = rand() % 100;
		if (nRand < m_nUnLitPercent)
		{//消灯する
			m_nCounterUnLit = m_nDefUnLitTime + (rand() % (m_nDegUnLitTime * 2) - m_nDegUnLitTime);
		}
		CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	CObject2D::Update();
}

//=================================
//描画
//=================================
void CStartText::Draw(void)
{
	CObject2D::Draw();
}

//=================================
//生成
//=================================
CStartText* CStartText::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight)
{
	CStartText* pStartText = nullptr;

	if (pStartText == nullptr)
	{
		//オブジェクトの生成
		pStartText = new CStartText;

		//初期化
		pStartText->Init();
		pStartText->SetPos(pos);
		pStartText->SetRot(rot);
		pStartText->SetSize(fWidth, fHeight);

		return pStartText;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//点灯パラメータ設定
//=================================
void CStartText::SetLitParam(const int nDef, const int nDegree, const int nPercent)
{
	m_nDefUnLitTime = nDef;
	m_nDegUnLitTime = nDegree;
	m_nUnLitPercent = nPercent;
}
