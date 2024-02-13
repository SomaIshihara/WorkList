//======================================================
//
//チュートリアルシーン[game.cpp]
//Author:石原颯馬
//
//======================================================
#include "tutorial.h"
#include "input.h"
#include "texture.h"
#include "objectX.h"
#include "manager.h"
#include "camera.h"
#include "sound.h"
#include "character.h"
#include "player.h"
#include "objloader.h"
#include "switchmanager.h"
#include "blockmanager.h"
#include "block3D.h"
#include "object3D.h"
#include "tutorialobj.h"
#include "goal.h"
#include "item.h"

//シーン系
#include "result.h"

//UI系
#include "fade.h"

//静的メンバ変数
const int CTutorial::TUTORIAL_MOVE = 4;		//移動説明の番号
const int CTutorial::TUTORIAL_CHANGE = 5;	//切替説明の番号

//=================================
//コンストラクタ
//=================================
CTutorial::CTutorial()
{
	m_pPlayer = nullptr;
	m_pSwitchManager = nullptr;
	m_pFade = nullptr;
	m_pMoveTutorial = nullptr;
	m_pChangeTutorial = nullptr;
}

//=================================
//デストラクタ
//=================================
CTutorial::~CTutorial()
{
}

//=================================
//初期化
//=================================
HRESULT CTutorial::Init(void)
{
	//カメラリセット
	CManager::GetInstance()->CManager::GetInstance()->GetCamera()->ResetPos();

	//操作プレイヤーのクラス生成
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Init();
	}

	//スイッチ管理オブジェ生成と設定
	m_pSwitchManager = CSwitchManager::Create();
	CBlock3D::SetSwitchManager(m_pSwitchManager);
	CObjLoader::LoadData("data\\tut_mapdata_tutorial.ismd");

	//ブロックマネ生成
	m_pBlockManager = CBlockManager::Create(m_pSwitchManager, m_pPlayer);

	//テクスチャ変えたいチュートリアルオブジェクトを取得
	CTutorialObj* pTutorialObj = CTutorialObj::GetTop();

	while (pTutorialObj != nullptr)
	{
		if (pTutorialObj->GetNumber() == TUTORIAL_MOVE)
		{
			m_pMoveTutorial = pTutorialObj;
		}
		else if (pTutorialObj->GetNumber() == TUTORIAL_CHANGE)
		{
			m_pChangeTutorial = pTutorialObj;
		}
		pTutorialObj = pTutorialObj->GetNext();
	}

	//背景
	CObject3D* pObj3D = CObject3D::Create(D3DXVECTOR3(0.0f, 300.0f, 700.0f), D3DXVECTOR3(-0.5f * D3DX_PI, 0.0f, 0.0f), 7200.0f, 4404.0f, CObject::PRIORITY_BG);
	pObj3D->BindTexture(CTexture::PRELOAD_26_BG_01);
	
	//キャラ生成
	CCharacter::Create(D3DXVECTOR3(100.0f,150.0f,0.0f),CCharacter::TYPE_A, m_pPlayer);
	CCharacter::Create(D3DXVECTOR3(0.0f, 150.0f, 0.0f),CCharacter::TYPE_B, m_pPlayer);
	return S_OK;
}

//=================================
//終了
//=================================
void CTutorial::Uninit(void)
{
	//オブジェ全破棄
	for (int cnt = 0; cnt < CObject::PRIORITY_FADE; cnt++)
	{
		CObject::ReleaseAll(cnt);
	}

	//音止める
	CManager::GetInstance()->GetSound()->Stop();

	//スコア用インターフェースポインタ消す
	CItem::UnsetScoreInterface();

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}
}

//=================================
//更新
//=================================
void CTutorial::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();	//キーボード取得
	CInputGamePad* pGamepad = CManager::GetInstance()->GetInputGamePad();
	CGoal* pGoal = CGoal::GetTop();
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	bool bGoal = false;

	//ゲームパッド使用取得
	if (pGamepad != nullptr && pGamepad->IsConnect() == true)
	{//使用中
		if (m_pMoveTutorial != nullptr)
		{
			m_pMoveTutorial->GetTutorialStr()->BindTexture(CTexture::PRELOAD_30_TUTORIAL_05_GP);
		}
		if (m_pChangeTutorial != nullptr)
		{
			m_pChangeTutorial->GetTutorialStr()->BindTexture(CTexture::PRELOAD_31_TUTORIAL_06_GP);
		}
	}
	else
	{//未使用
		if (m_pMoveTutorial != nullptr)
		{
			m_pMoveTutorial->GetTutorialStr()->BindTexture(CTexture::PRELOAD_28_TUTORIAL_05_KB);
		}
		if (m_pChangeTutorial != nullptr)
		{
			m_pChangeTutorial->GetTutorialStr()->BindTexture(CTexture::PRELOAD_29_TUTORIAL_06_KB);
		}
	}

	//終了判定
	if (pGoal != nullptr)
	{
		while (pGoal != nullptr)
		{
			if (pGoal->IsGoal() == true)
			{//糸冬
				bGoal = true;
				break;
			}
			pGoal = pGoal->GetNext();
		}
	}

	//チュートリアルスキップ
	if (pKeyboard != nullptr && pKeyboard->GetTrigger(DIK_P) == true)
	{
		bGoal = true;
	}
	else if(pGamepad != nullptr && pGamepad->IsConnect() == true && pGamepad->GetTrigger(XINPUT_GAMEPAD_START))
	{
		bGoal = true;
	}

	if (bGoal == true)
	{//ゴールした
		m_pPlayer->SetControll(false);
		if (m_pFade == nullptr)
		{
			//フェード出す
			m_pFade = CFade::Create(CScene::MODE_GAME);

			//BGM再生
			CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_OUT);
		}
	}
	else
	{//ゴールしてない
		m_pPlayer->SetControll(true);
	}

	//とりあえず回す（有効・無効は上でやる）
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Update();
	}

	if (pCamera != nullptr)
	{//カメラ移動
		D3DXVECTOR3 posV = pCamera->GetPosV();
		D3DXVECTOR3 posR = pCamera->GetPosR();
		CCharacter** chara = CCharacter::GetChara();

		float posXCenter = (chara[0]->GetPos().x + chara[1]->GetPos().x) * 0.5f;
		float lenXHalf = fabsf(chara[0]->GetPos().x - chara[1]->GetPos().x) * 0.5f;
		float posYCenter = (chara[0]->GetPos().y + chara[1]->GetPos().y) * 0.5f;
		float lenYHalf = fabsf(chara[0]->GetPos().y - chara[1]->GetPos().y) * 0.5f;
		posV.x = posXCenter;
		posR.x = posXCenter;
		posV.y = posYCenter;
		posR.y = posYCenter;

		pCamera->SetPosV(posV);
		pCamera->SetPosR(posR);

		if (lenXHalf * 2.0f >= 900.0f)
		{//仮
			pCamera->SetLength(lenXHalf * 2.0f);
		}
		else
		{
			pCamera->SetLength(900.0f);
		}
	}
}

//=================================
//描画
//=================================
void CTutorial::Draw(void)
{
	//普段はすべてCObjectクラス継承してるものが動いているので自動描画
	//ポーズの中身もすべてCObjectクラス継承してるので自動描画
	//よってここですることはない
}