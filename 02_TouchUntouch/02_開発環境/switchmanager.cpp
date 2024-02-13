//======================================================
//
//スイッチマネージャ処理[switchmanager.cpp]
//Author:石原颯馬
//
//======================================================
#include "switchmanager.h"
#include "manager.h"

//=================================
//コンストラクタ
//=================================
CSwitchManager::CSwitchManager(int nPriority) : CObject(nPriority)
{
	Reset();
}

//=================================
//デストラクタ
//=================================
CSwitchManager::~CSwitchManager()
{
}

//=================================
//初期化
//=================================
HRESULT CSwitchManager::Init(void)
{
	return S_OK;
}

//=================================
//終了
//=================================
void CSwitchManager::Uninit(void)
{
	//管理オブジェクト破棄
	Release();
}

//=================================
//更新
//=================================
void CSwitchManager::Update(void)
{
	CSwitch* pSwitch = CSwitch::GetTop();
	Reset();	//いっかい押されてないことにする

	while (pSwitch != nullptr)
	{
		if (pSwitch->IsPush() == true)
		{//押されてたらそのグループのスイッチをonにする
			m_aPush[pSwitch->GetType()] = true;
		}

		//いったん引っ張る
		pSwitch->Pull();

		pSwitch = pSwitch->GetNext();
	}
}

//=================================
//描画
//=================================
void CSwitchManager::Draw(void)
{
	
}

//=================================
//リセット
//=================================
void CSwitchManager::Reset(void)
{
	for (int cnt = 0; cnt < CSwitch::TYPE_MAX; cnt++)
	{
		m_aPush[cnt] = false;
	}
}

//=================================
//生成処理
//=================================
CSwitchManager* CSwitchManager::Create(void)
{
	CSwitchManager* pObjSwitchManager = nullptr;

	if (pObjSwitchManager == nullptr)
	{
		//マネの生成
		pObjSwitchManager = new CSwitchManager;

		//初期化
		pObjSwitchManager->Init();

		return pObjSwitchManager;
	}
	else
	{
		return nullptr;
	}
}