//======================================================
//
//スイッチ処理[switch.cpp]
//Author:石原颯馬
//
//======================================================
#include "switch.h"
#include "manager.h"
#include "objectX.h"
#include "xmodel.h"
#include "debugproc.h"

//静的メンバ変数
CXModel* CSwitch::m_pModelBase = nullptr;
CXModel* CSwitch::m_pModelMove = nullptr;
CSwitch* CSwitch::m_pTop = nullptr;
CSwitch* CSwitch::m_pCur = nullptr;
int CSwitch::m_nNumAll = 0;
const float CSwitch::MOVE_DEF_HEIGHT = 10.0f;

//=================================
//コンストラクタ
//=================================
CSwitch::CSwitch(int nPriority) : CObject(nPriority)
{
	m_pObjBase = nullptr;
	m_pObjMove = nullptr;
	m_pos = CManager::VEC3_ZERO;
	m_move = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fWidth = CManager::FLT_ZERO;
	m_fHeight = CManager::FLT_ZERO;
	m_fDepth = CManager::FLT_ZERO;
	m_type = TYPE_MAX;

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
CSwitch::~CSwitch()
{
}

//=================================
//初期化
//=================================
HRESULT CSwitch::Init(void)
{
	SetType(TYPE_SWITCH);
	return S_OK;
}

//=================================
//終了
//=================================
void CSwitch::Uninit(void)
{
	//モデル破棄
	if (m_pObjBase != nullptr)
	{
		m_pObjBase->Uninit();
		m_pObjBase = nullptr;
	}
	if (m_pObjMove != nullptr)
	{
		m_pObjMove->Uninit();
		m_pObjMove = nullptr;
	}

	Release();
}

//=================================
//更新
//=================================
void CSwitch::Update(void)
{
	if (m_bPush == true)
	{
		m_move.y = -0.1f;	//仮
	}
	else
	{
		m_move.y = 0.1f;	//仮
	}

	m_pObjMove->SetPos(m_pObjMove->GetPos() + m_move);

	//上がり下がりすぎたら位置戻す
	if (m_pObjMove->GetPos().y < m_pos.y + 1.0f)
	{
		m_pObjMove->SetPos(m_pos + D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	else if (m_pObjMove->GetPos().y > m_pos.y + MOVE_DEF_HEIGHT)
	{
		m_pObjMove->SetPos(m_pos + D3DXVECTOR3(0.0f, MOVE_DEF_HEIGHT, 0.0f));
	}
}

//=================================
//描画
//=================================
void CSwitch::Draw(void)
{
	//必要なし
}

//=================================
//生成
//=================================
CSwitch* CSwitch::Create(const D3DXVECTOR3 pos, const TYPE type)
{
	CSwitch* pSwitch = nullptr;

	if (pSwitch == nullptr)
	{
		//オブジェクト2Dの生成
		pSwitch = new CSwitch;

		//初期化
		pSwitch->Init();

		//データ設定
		pSwitch->m_pos = pos;
		pSwitch->m_type = type;

		//モデルが読み込まれてなければ読み込み
		if (m_pModelBase == nullptr)
		{//土台がぬるぽ
			m_pModelBase = CXModel::Load("data\\MODEL\\switch_01.x");
		}
		if (m_pModelMove == nullptr)
		{//土台がぬるぽ
			m_pModelMove = CXModel::Load("data\\MODEL\\switch_02.x");
		}

		//モデル生成
		pSwitch->m_pObjBase = CObjectX::Create(pSwitch->m_pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f), CManager::VEC3_ZERO, m_pModelBase);
		pSwitch->m_pObjBase->SetCollider();
		pSwitch->m_pObjBase->GetCollider()->SetType(CBoxCollider::TYPE_COLLISION);
		pSwitch->m_pObjBase->SetType(TYPE_SWITCH);

		pSwitch->m_pObjMove = CObjectX::Create(pSwitch->m_pos + D3DXVECTOR3(0.0f, MOVE_DEF_HEIGHT, 0.0f), CManager::VEC3_ZERO, m_pModelMove);
		pSwitch->m_pObjMove->SetCollider();
		pSwitch->m_pObjMove->GetCollider()->SetType(CBoxCollider::TYPE_COLLISION);
		pSwitch->m_pObjMove->SetType(TYPE_SWITCH);

		//色変え
		if (type == TYPE_A)
		{//紫
			pSwitch->m_pObjBase->SetColor(true, D3DCOLOR(0xffab7fc7));
			pSwitch->m_pObjMove->SetColor(true, D3DCOLOR(0xffab7fc7));
			pSwitch->m_pObjBase->GetCollider()->SetTag(CBoxCollider::TAG_UNIV);
			pSwitch->m_pObjMove->GetCollider()->SetTag(CBoxCollider::TAG_UNIV);
		}
		else if(type == TYPE_B)
		{//黄色
			pSwitch->m_pObjBase->SetColor(true, D3DCOLOR(0xfff7ea31));
			pSwitch->m_pObjMove->SetColor(true, D3DCOLOR(0xfff7ea31));
			pSwitch->m_pObjBase->GetCollider()->SetTag(CBoxCollider::TAG_UNIV);
			pSwitch->m_pObjMove->GetCollider()->SetTag(CBoxCollider::TAG_UNIV);
		}
		else if (type == TYPE_GOAL_A)
		{//ゴール用（タイプA）
			pSwitch->m_pObjBase->SetColor(true, D3DCOLOR(0xfff39aac));
			pSwitch->m_pObjMove->SetColor(true, D3DCOLOR(0xfff39aac));
			pSwitch->m_pObjBase->GetCollider()->SetTag(CBoxCollider::TAG_TYPE_A);
			pSwitch->m_pObjMove->GetCollider()->SetTag(CBoxCollider::TAG_TYPE_A);
		}
		else if (type == TYPE_GOAL_B)
		{//ゴール用（タイプB）
			pSwitch->m_pObjBase->SetColor(true, D3DCOLOR(0xff68c7ec));
			pSwitch->m_pObjMove->SetColor(true, D3DCOLOR(0xff68c7ec));
			pSwitch->m_pObjBase->GetCollider()->SetTag(CBoxCollider::TAG_TYPE_B);
			pSwitch->m_pObjMove->GetCollider()->SetTag(CBoxCollider::TAG_TYPE_B);
		}

		return pSwitch;
	}

	return nullptr;
}

//=================================
//除外
//=================================
void CSwitch::Exclusion(void)
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

	//成仏
	m_nNumAll--;	//総数減らす
}
