//======================================================
//
//タイトルシーン[title.cpp]
//Author:石原颯馬
//
//======================================================
#include "title.h"
#include "../../../../main.h"
#include "../../texture/texture.h"
#include "../../../_Expansion/fade/fade.h"	//ここなんとかして
#include "../../input/input.h"
#include "../../camera/camera.h"
#include "../../sound/sound.h"
#include "../../utility/Utility.h"
#include "../../_object/object_2d/object2D.h"
#include "../../../_Expansion/meshfield/meshField.h"
#include "../../../_Expansion/meshsky/meshsky.h"
#include "../../../../Addition/meshroad/meshroad.h"
#include "../../file(legacy)/file.h"
#include "../../../../Addition/starttext/starttext.h"

//静的メンバ変数

//=================================
//コンストラクタ
//=================================
CTitle::CTitle()
{
	m_pFade = nullptr;
}

//=================================
//デストラクタ
//=================================
CTitle::~CTitle()
{
}

//=================================
//初期化
//=================================
HRESULT CTitle::Init(void)
{
	//マップ配置
	//道路
	LoadRoadScriptFile("data//road_data_main.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_sub.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_TGConnect.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_dummy.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_tutorial.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);

	//地面
	CMeshField::Create(D3DXVECTOR3(0.0f, -381.5f, 6000.0f), IS_Utility::VEC3_ZERO, 2048.0f, 2048.0f, 24, 24)
		->BindTexture(CTexture::PRELOAD_34_FIELD_LEAF);

	//カメラ
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	pCamera->ResetPos();
	pCamera->SetPosR(D3DXVECTOR3(3000.0f, 100.0f, 8000.0f));
	pCamera->SetRot(D3DXVECTOR3(-0.1f * D3DX_PI, -0.2f * D3DX_PI, 0.0f));
	pCamera->SetLength(4000.0f);

	//タイトル
	CObject2D* pTitle = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.3f, 0.0f), IS_Utility::VEC3_ZERO, 384.0f, 216.0f, CObject::PRIORITY_05);
	pTitle->BindTexture(CTexture::PRELOAD::PRELOAD_00_TITLELOGO);

	//スタート文字
	CStartText* pStart = CStartText::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.6f, 0.0f), IS_Utility::VEC3_ZERO, 756.0f, 99.0f);
	pStart->BindTexture(CTexture::PRELOAD::PRELOAD_01_PUSHANYBUTTON);
	pStart->SetLitParam(5, 5, 2);

	//空
	CMeshSky::Create(D3DXVECTOR3(0.0f, 0.0f, 4000.0f), IS_Utility::VEC3_ZERO, 14000.0f, 12, 12);

	//BGM鳴らす
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//=================================
//終了
//=================================
void CTitle::Uninit(void)
{
	//音停止
	CManager::GetInstance()->GetSound()->Stop();

	//オブジェ全破棄
	for (int cnt = 0; cnt < CObject::PRIORITY_FADE; cnt++)
	{
		CObject::ReleaseAll(cnt);
	}
}

//=================================
//更新
//=================================
void CTitle::Update(void)
{
	CManager* pIns = CManager::GetInstance();
	CInputKeyboard* pKeyboard = pIns->GetInputKeyboard();
	CInputGamePad* pGamepad = pIns->GetInputGamePad();
	bool bPush = false;

	if (pGamepad != nullptr && pGamepad->GetTrigger(0xffff) == true)
	{
		bPush = true;
	}
	else
	{
		for (int cnt = 0; cnt < KEY_NUM; cnt++)
		{
			if (pKeyboard->GetTrigger(cnt))
			{
				bPush = true;
				break;
			}
		}
	}

	if (m_pFade == nullptr && bPush == true)
	{//スペース押された
		m_pFade = CFade::Create(CScene::MODE::MODE_GAME);
	}
}

//=================================
//描画
//=================================
void CTitle::Draw(void)
{
}
