//======================================================
//
//アイテム処理[item.cpp]
//Author:石原颯馬
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "item.h"
#include "xmodel.h"
#include "sound.h"

//静的メンバ変数
int CItem::m_nNumAll = 0;
IScoreSetter* CItem::m_pScoreInterface = nullptr;
CItem* CItem::m_pTop = nullptr;	//リストの最初
CItem* CItem::m_pCur = nullptr;	//リストの終端
const int CItem::GET_SCORE = 1000;

//************************************************
//アイテム弾クラス
//************************************************
//=================================
//コンストラクタ（デフォルト）
//=================================
CItem::CItem()
{
	//値クリア
	m_nScore = CManager::INT_ZERO;

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
}

//=================================
//デストラクタ
//=================================
CItem::~CItem()
{
}

//=================================
//初期化
//=================================
HRESULT CItem::Init(void)
{
	SetType(TYPE_ITEM);
	return CObjectX::Init();
}

//=================================
//終了
//=================================
void CItem::Uninit(void)
{
	CObjectX::Uninit();
}

//=================================
//更新
//=================================
void CItem::Update(void)
{
	CObjectX::Update();
}

//=================================
//描画
//=================================
void CItem::Draw(void)
{
	CObjectX::Draw();
}

//=================================
//生成処理
//=================================
CItem* CItem::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CItem* pItem = NULL;

	if (pItem == NULL)
	{
		//オブジェクト生成
		pItem = new CItem;

		//初期化
		pItem->Init();

		//データ設定
		pItem->m_nScore = GET_SCORE;
		pItem->SetPos(pos);
		pItem->SetRot(rot);

		//モデル設定
		pItem->SetModel(CXModel::Load("data\\MODEL\\item.x"));

		//当たり判定設定
		pItem->SetCollider();
		pItem->GetCollider()->SetType(CBoxCollider::TYPE_TRIGGER);

		return pItem;
	}
	else
	{
		return NULL;
	}
}

//=================================
//アイテム取得
//=================================
void CItem::Get(void)
{
	if (m_pScoreInterface != nullptr)
	{
		m_pScoreInterface->Add(m_nScore);

		//SE再生
		CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_ITEM);
	}
	CItem::Uninit();
}

//=================================
//除外
//=================================
void CItem::Exclusion(void)
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

	CObjectX::Exclusion();	//親オブジェの除外も行う
}