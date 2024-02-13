//======================================================
//
//チュートリアル用オブジェ処理[tutorialobj.cpp]
//Author:石原颯馬
//
//======================================================
#include "tutorialobj.h"
#include "manager.h"
#include "object3D.h"
#include "objectX.h"
#include "xmodel.h"
#include "debugproc.h"
#include "texture.h"

//静的メンバ変数
CTutorialObj* CTutorialObj::m_pTop = nullptr;
CTutorialObj* CTutorialObj::m_pCur = nullptr;
int CTutorialObj::m_nNumAll = 0;

//=================================
//コンストラクタ
//=================================
CTutorialObj::CTutorialObj(int nPriority) : CObject(nPriority)
{
	m_pos = CManager::VEC3_ZERO;
	m_fWidth = CManager::FLT_ZERO;
	m_fHeight = CManager::FLT_ZERO;
	m_fDepth = CManager::FLT_ZERO;

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
	m_pCollider = nullptr;
	m_nNumber = 0;
	m_bPopup = false;
	m_nNumAll++;
}

//=================================
//デストラクタ
//=================================
CTutorialObj::~CTutorialObj()
{
}

//=================================
//初期化
//=================================
HRESULT CTutorialObj::Init(void)
{
	SetType(TYPE_TUTORIALOBJ);
	return S_OK;
}

//=================================
//終了
//=================================
void CTutorialObj::Uninit(void)
{
	if (m_pCollider != nullptr)
	{
		m_pCollider->Release();
		m_pCollider = nullptr;
	}

	Release();
}

//=================================
//更新
//=================================
void CTutorialObj::Update(void)
{
	m_bPopup = false;	//表示をしない（なおキャラが表示させる可能性がある
}

//=================================
//描画
//=================================
void CTutorialObj::Draw(void)
{
	//チュートリアル表示設定
	if (m_bPopup == true)
	{
		m_pTutorial->SetCol(D3DCOLOR(0xffffffff));
	}
	else
	{
		m_pTutorial->SetCol(D3DCOLOR(0x00ffffff));
	}
}

//=================================
//生成
//=================================
CTutorialObj* CTutorialObj::Create(const D3DXVECTOR3 pos, const int nNumber)
{
	CTutorialObj* pTutorialObj = nullptr;

	if (pTutorialObj == nullptr)
	{
		//オブジェクトの生成
		pTutorialObj = new CTutorialObj;

		//初期化
		pTutorialObj->Init();

		//データ設定
		pTutorialObj->m_pos = pos;
		pTutorialObj->m_nNumber = nNumber;
		pTutorialObj->m_fWidth = 100.0f;
		pTutorialObj->m_fHeight = 100.0f;
		pTutorialObj->m_fDepth = 200.0f;

		//当たり判定設定
		pTutorialObj->m_pCollider = CBoxCollider::Create(pTutorialObj);
		pTutorialObj->m_pCollider->SetTag(CBoxCollider::TAG_UNIV);
		pTutorialObj->m_pCollider->SetType(CBoxCollider::TYPE_TRIGGER);

		//表示用オブジェ生成
		pTutorialObj->m_pTutorial = CObject3D::Create(pos + D3DXVECTOR3(0.0f, 200.0f, 50.0f), D3DXVECTOR3(-0.5f * D3DX_PI,0.0f,0.0f), 231.0f, 131.0f, PRIORITY_05);
		pTutorialObj->m_pTutorial->BindTexture(CTexture::PRELOAD_17_TUTORIAL_01 + nNumber);
		pTutorialObj->m_pObj = CObjectX::Create(pos + D3DXVECTOR3(0.0f, 0.0f, 50.0f), CManager::VEC3_ZERO, CXModel::Load("data\\MODEL\\tutorialobj.x"));

		return pTutorialObj;
	}

	return nullptr;
}

//=================================
//除外
//=================================
void CTutorialObj::Exclusion(void)
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