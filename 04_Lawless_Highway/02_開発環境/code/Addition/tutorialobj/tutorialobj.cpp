//======================================================
//
//チュートリアルテキスト処理[tutorialobj.cpp]
//Author:石原颯馬
//
//======================================================
#include "tutorialobj.h"
#include "../../IS_Bace/_Core/manager/manager.h"
#include "../../IS_Bace/_Core/texture/texture.h"
#include "../../IS_Bace/_Core/input/input.h"
#include "../player/player.h"

//無名名前空間
namespace
{
	float RADIUS = 300.0f;
}

//静的メンバ
const D3DXVECTOR3 CTutorialObj::PILOT_CHECKPOINT = D3DXVECTOR3(-900.0f, -380.0f, 845.0f);
const D3DXVECTOR3 CTutorialObj::START_CHECKPOINT = D3DXVECTOR3(0.0f, 99.0f, 0.0f);
const D3DXVECTOR3 CTutorial_01::CHECKPOINT = D3DXVECTOR3(12600.0f, -378.0f, -1845.0f);
const D3DXVECTOR3 CTutorial_02::CHECKPOINT = D3DXVECTOR3(8610.0f, -378.0f, -1845.0f);
const D3DXVECTOR3 CTutorial_03::CHECKPOINT = D3DXVECTOR3(4090.0f, -380.0f, 845.0f);
const D3DXVECTOR3 CTutorial_05::CHECKPOINT = D3DXVECTOR3(0.0f, 100.0f, -2300.0f);

//=================================
//コンストラクタ
//=================================
CTutorialObj::CTutorialObj(int nPriority) : CObject2D(nPriority)
{
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
	CObject2D::Init();

	return S_OK;
}

//=================================
//終了
//=================================
void CTutorialObj::Uninit(void)
{
	CObject2D::Uninit();
}

//=================================
//更新
//=================================
void CTutorialObj::Update(void)
{
	//プレイヤー位置取得
	D3DXVECTOR3 pos = m_pPlayer->GetPos();

	//チュートリアル状態に応じた処理
	m_pState->Update(this, pos);

	//自動操縦
	float length = D3DXVec3Length(&(pos - PILOT_CHECKPOINT));
	if (length <= RADIUS)
	{
		SetWaitingPirot();
		SetState(new CTutorial_05);
	}

	//ゲーム移行処理
	length = D3DXVec3Length(&(pos - START_CHECKPOINT));
	if (length <= RADIUS)
	{
		m_pPlayer->SetState(CPlayer::STATE::STATE_GAME);
	}

	CObject2D::Update();
}

//=================================
//描画
//=================================
void CTutorialObj::Draw(void)
{
	CObject2D::Draw();
}

//=================================
//生成
//=================================
CTutorialObj* CTutorialObj::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, CTimer* pTimer, CPlayer* pPlayer)
{
	CTutorialObj* pTutorialObj = nullptr;

	if (pTutorialObj == nullptr)
	{
		//オブジェクトの生成
		pTutorialObj = new CTutorialObj;

		//初期化
		pTutorialObj->Init();
		pTutorialObj->SetPos(pos);
		pTutorialObj->SetRot(rot);
		pTutorialObj->SetSize(fWidth, fHeight);
		pTutorialObj->SetState(new CTutorial_01);
		pTutorialObj->m_pPlayer = pPlayer;
		pTutorialObj->m_pTimer = pTimer;

		return pTutorialObj;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//ハンドル操作:更新処理
//=================================
void CTutorial_01::Update(CTutorialObj* obj, D3DXVECTOR3 playerPos)
{
	CInputGamePad* pGamePad = CManager::GetInstance()->GetInputGamePad();

	//コントローラーに合わせてテクスチャ変更
	if (pGamePad != nullptr && pGamePad->IsConnect() == true)
	{//ゲームパッド用
		obj->BindTexture(CTexture::PRELOAD::PRELOAD_28_TUTORIAL_01_GP);
	}
	else
	{//キーボード用
		obj->BindTexture(CTexture::PRELOAD::PRELOAD_27_TUTORIAL_01_KB);
	}
	
	float length = D3DXVec3Length(&(playerPos - CHECKPOINT));
	if (length <= RADIUS)
	{
		obj->SetState(new CTutorial_02);
	}
}

//=================================
//ブースト:更新処理
//=================================
void CTutorial_02::Update(CTutorialObj* obj, D3DXVECTOR3 playerPos)
{
	CInputGamePad* pGamePad = CManager::GetInstance()->GetInputGamePad();

	//コントローラーに合わせてテクスチャ変更
	if (pGamePad != nullptr && pGamePad->IsConnect() == true)
	{//ゲームパッド用
		obj->BindTexture(CTexture::PRELOAD::PRELOAD_30_TUTORIAL_02_GP);
	}
	else
	{//キーボード用
		obj->BindTexture(CTexture::PRELOAD::PRELOAD_29_TUTORIAL_02_KB);
	}

	float length = D3DXVec3Length(&(playerPos - CHECKPOINT));
	if (length <= RADIUS)
	{
		obj->SetState(new CTutorial_03);
	}
}

//=================================
//ブレーキドリフト操作:更新処理
//=================================
void CTutorial_03::Update(CTutorialObj* obj, D3DXVECTOR3 playerPos)
{
	CInputGamePad* pGamePad = CManager::GetInstance()->GetInputGamePad();

	//コントローラーに合わせてテクスチャ変更
	if (pGamePad != nullptr && pGamePad->IsConnect() == true)
	{//ゲームパッド用
		obj->BindTexture(CTexture::PRELOAD::PRELOAD_32_TUTORIAL_03_GP);
	}
	else
	{//キーボード用
		obj->BindTexture(CTexture::PRELOAD::PRELOAD_31_TUTORIAL_03_KB);
	}

	float length = D3DXVec3Length(&(playerPos - CHECKPOINT));
	if (length <= RADIUS)
	{
		obj->SetState(new CTutorial_04);
	}
}

//=================================
//目的表示:更新処理
//=================================
void CTutorial_04::Update(CTutorialObj* obj, D3DXVECTOR3 playerPos)
{
	if (m_bIsSet == false)
	{
		m_bIsSet = true;
		obj->BindTexture(CTexture::PRELOAD::PRELOAD_33_TUTORIAL_04);
	}
}

//=================================
//自動操縦後ゲーム切り替え:更新処理
//=================================
void CTutorial_05::Update(CTutorialObj* obj, D3DXVECTOR3 playerPos)
{
	if (m_bIsSet == false)
	{
		m_bIsSet = true;
		obj->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}

	float length = D3DXVec3Length(&(playerPos - CHECKPOINT));
	if (m_bIsPirot == false && length <= RADIUS)
	{
		m_bIsPirot = true;
		obj->GameStart();
	}
}