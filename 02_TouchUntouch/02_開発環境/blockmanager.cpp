//======================================================
//
//ブロックマネージャ処理[blockmanager.cpp]
//Author:石原颯馬
//
//======================================================
#include "blockmanager.h"
#include "manager.h"
#include "switchmanager.h"
#include "block3D.h"
#include "character.h"
#include "xmodel.h"

//静的メンバ変数
CXModel* CBlockManager::m_pModelNor = nullptr;
CXModel* CBlockManager::m_pModelGimOff = nullptr;

//=================================
//コンストラクタ
//=================================
CBlockManager::CBlockManager(int nPriority) : CObject(nPriority)
{

}

//=================================
//デストラクタ
//=================================
CBlockManager::~CBlockManager()
{
}

//=================================
//初期化
//=================================
HRESULT CBlockManager::Init(void)
{
	return S_OK;
}

//=================================
//終了
//=================================
void CBlockManager::Uninit(void)
{
	//管理オブジェクト破棄
	Release();
}

//=================================
//更新
//=================================
void CBlockManager::Update(void)
{
	CBlock3D* pBlock = CBlock3D::GetTop();

	while (pBlock != nullptr)
	{
		//スイッチに応じた当たり判定
		CBlock3D::TYPE type = pBlock->GetType();
		if (type == CBlock3D::TYPE_GIMMICK_01 || type == CBlock3D::TYPE_GIMMICK_02)
		{//ギミック系
			if (m_pSwitchManager->IsPush()[type - 1] == true)
			{
				pBlock->GetCollider()->SetType(CBoxCollider::TYPE_COLLISION);
				pBlock->SetModel(m_pModelNor);
			}
			else
			{
				pBlock->GetCollider()->SetType(CBoxCollider::TYPE_NONE);
				pBlock->SetModel(m_pModelGimOff);
			}
		}
		else if (type == CBlock3D::TYPE_A)
		{//タイプA（ピンク）
			if (m_iControllStat->GetType() == CCharacter::TYPE_A)
			{//操作中キャラが同じタイプ
				pBlock->SetModel(m_pModelNor);
			}
			else
			{//違う
				pBlock->SetModel(m_pModelGimOff);
			}
		}
		else if (type == CBlock3D::TYPE_B)
		{//タイプB（空色）
			if (m_iControllStat->GetType() == CCharacter::TYPE_B)
			{//操作中キャラが同じタイプ
				pBlock->SetModel(m_pModelNor);
			}
			else
			{//違う
				pBlock->SetModel(m_pModelGimOff);
			}
		}
		else
		{
			pBlock->SetModel(m_pModelNor);
		}

		pBlock = pBlock->GetNext();
	}
}

//=================================
//描画
//=================================
void CBlockManager::Draw(void)
{
	
}

//=================================
//生成処理
//=================================
CBlockManager* CBlockManager::Create(CSwitchManager* pSwitchManager, IControllStat* iControllStat)
{
	CBlockManager* pObjBlockManager = nullptr;

	if (pObjBlockManager == nullptr)
	{
		//マネの生成
		pObjBlockManager = new CBlockManager;

		//初期化
		pObjBlockManager->Init();

		//データ設定
		pObjBlockManager->m_pSwitchManager = pSwitchManager;
		pObjBlockManager->m_iControllStat = iControllStat;

		//モデル設定
		if (m_pModelNor == nullptr)
		{
			m_pModelNor = CXModel::Load("data\\MODEL\\block_univ.x");
		}
		if (m_pModelGimOff == nullptr)
		{
			m_pModelGimOff = CXModel::Load("data\\MODEL\\block_univ_gimoff.x");
		}

		return pObjBlockManager;
	}
	else
	{
		return nullptr;
	}
}