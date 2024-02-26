//======================================================
//
//ゴール処理[goal.cpp]
//Author:石原颯馬
//
//======================================================
#include "goal.h"
#include "../../IS_Bace/_Core/_object/object_3d/object3D.h"
#include "../../IS_Bace/_Core/collision/collision.h"
#include "../../IS_Bace/_Core/utility/Utility.h"
#include "../../IS_Bace/_Core/texture/texture.h"

//=================================
//コンストラクタ
//=================================
CGoal::CGoal(int nPriority) : CObject(nPriority)
{
	//クリア
	m_pos = IS_Utility::VEC3_ZERO;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_pCollider = nullptr;
	m_bIsGoal = false;
}

//=================================
//デストラクタ
//=================================
CGoal::~CGoal()
{
}

//========================
//初期化処理
//========================
HRESULT CGoal::Init(void)
{
	//当たり判定付与
	m_pCollider = CBoxCollider::Create(this);
	m_pCollider->SetType(CBoxCollider::TYPE::TYPE_TRIGGER);

	//ゴール線オブジェクト生成
	CObject3D* pObj = CObject3D::Create(m_pos + D3DXVECTOR3(0.0f, 1.0f, 0.0f), IS_Utility::VEC3_ZERO, m_fWidth, m_fDepth);
	pObj->BindTexture(CTexture::PRELOAD_22_GOAL);

	return S_OK;
}

//========================
//終了処理
//========================
void CGoal::Uninit(void)
{
	if (m_pCollider != nullptr)
	{
		m_pCollider->Release();
		m_pCollider = nullptr;
	}

	//自分自身破棄
	Release();
}

//========================
//更新処理
//========================
void CGoal::Update(void)
{
	if (m_pCollider != nullptr)
	{
		m_pCollider->CollisionCheck();
		if (m_pCollider->GetResult().collList.size() >= 1)
		{
			m_bIsGoal = true;
		}
	}
}

//========================
//描画処理
//========================
void CGoal::Draw(void)
{

}

//========================
//生成処理
//========================
CGoal* CGoal::Create(const D3DXVECTOR3 pos, const float fWidth, const float fHeight, const float fDepth)
{
	CGoal* pGoal = nullptr;

	if (pGoal == nullptr)
	{
		//オブジェクト2Dの生成
		pGoal = new CGoal;

		//値設定
		pGoal->SetPos(pos);
		pGoal->m_fWidth = fWidth;
		pGoal->m_fHeight = fHeight;
		pGoal->m_fDepth = fDepth;

		//初期化
		pGoal->Init();

		return pGoal;
	}
	else
	{
		return nullptr;
	}
}
