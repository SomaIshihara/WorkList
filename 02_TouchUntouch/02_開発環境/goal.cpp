//======================================================
//
//ゴール処理[goal.cpp]
//Author:石原颯馬
//
//======================================================
#include "goal.h"
#include "manager.h"
#include "objectX.h"
#include "xmodel.h"
#include "debugproc.h"
#include "switch.h"

//静的メンバ変数
CGoal* CGoal::m_pTop = nullptr;
CGoal* CGoal::m_pCur = nullptr;
int CGoal::m_nNumAll = 0;

//=================================
//コンストラクタ
//=================================
CGoal::CGoal(int nPriority) : CObject(nPriority)
{
	m_aSwitch[0] = nullptr;
	m_aSwitch[1] = nullptr;
	m_pBase = nullptr;
	m_pos = CManager::VEC3_ZERO;
	m_move = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fWidth = CManager::FLT_ZERO;
	m_fHeight = CManager::FLT_ZERO;
	m_fDepth = CManager::FLT_ZERO;
	m_bGoal = false;

	if (m_pCur == nullptr)
	{//最後尾がいない（すなわち先頭もいない）
		m_pTop = this;			//俺が先頭
		m_pPrev = nullptr;		//前後誰もいない
		m_pNext = nullptr;
	}
	else
	{//最後尾がいる
		m_pPrev = m_pCur;		//最後尾が自分の前のオブジェ
		m_pCur->m_pNext = this;	//最後尾の次のオブジェが自分
		m_pNext = nullptr;		//自分の次のオブジェはいない
	}
	m_pCur = this;				//俺が最後尾
	m_nNumAll++;
}

//=================================
//デストラクタ
//=================================
CGoal::~CGoal()
{
}

//=================================
//初期化
//=================================
HRESULT CGoal::Init(void)
{
	SetType(TYPE_GOAL);
	return S_OK;
}

//=================================
//終了
//=================================
void CGoal::Uninit(void)
{
	Release();
}

//=================================
//更新
//=================================
void CGoal::Update(void)
{
	m_bGoal = true;	//ゴールしてるかもしれないのでいったんtrue
	for (int cnt = 0; cnt < CCharacter::TYPE_MAX; cnt++)
	{
		if (m_aSwitch[cnt] != nullptr && m_aSwitch[cnt]->IsPush() == false)
		{
			m_bGoal = false;	//ゴールしてないわ。falseにする
			break;
		}
	}
}

//=================================
//描画
//=================================
void CGoal::Draw(void)
{
	//必要なし
}

//=================================
//生成
//=================================
CGoal* CGoal::Create(const D3DXVECTOR3 pos)
{
	CGoal* pGoal = nullptr;

	if (pGoal == nullptr)
	{
		//オブジェクト2Dの生成
		pGoal = new CGoal;

		//初期化
		pGoal->Init();

		//データ設定
		pGoal->m_pos = pos;

		//土台生成
		pGoal->m_pBase = CObjectX::Create(pGoal->m_pos, CManager::VEC3_ZERO, CXModel::Load("data\\MODEL\\Goal_Base.x"));

		//スイッチ生成
		pGoal->m_aSwitch[CCharacter::TYPE_A] = CSwitch::Create(pGoal->m_pos + D3DXVECTOR3(-55.0f, 10.0f, 0.0f), CSwitch::TYPE_GOAL_A);
		pGoal->m_aSwitch[CCharacter::TYPE_B] = CSwitch::Create(pGoal->m_pos + D3DXVECTOR3(55.0f,10.0f,0.0f), CSwitch::TYPE_GOAL_B);

		return pGoal;
	}

	return nullptr;
}

//=================================
//除外
//=================================
void CGoal::Exclusion(void)
{
	if (m_pPrev != nullptr)
	{//前にオブジェがいる
		m_pPrev->m_pNext = m_pNext;	//前のオブジェの次のオブジェは自分の次のオブジェ
	}
	if (m_pNext != nullptr)
	{
		m_pNext->m_pPrev = m_pPrev;	//次のオブジェの前のオブジェは自分の前のオブジェ
	}

	if (m_pCur == this)
	{//最後尾でした
		m_pCur = m_pPrev;	//最後尾を自分の前のオブジェにする
	}
	if (m_pTop == this)
	{
		m_pTop = m_pNext;	//先頭を自分の次のオブジェにする
	}
}
