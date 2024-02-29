//======================================================
//
//プレイヤー処理[player.cpp]
//Author:石原颯馬
//
//======================================================

//インクルード
#include "player.h"

#include "../../IS_Bace/_Core/manager/manager.h"
#include "../../IS_Bace/_Core/renderer/renderer.h"
#include "../../IS_Bace/_Core/texture/texture.h"
#include "../../IS_Bace/_Core/sound/sound.h"
#include "../../IS_Bace/_Core/camera/camera.h"
#include "../../IS_Bace/_Core/utility/Utility.h"
#include "../../IS_Bace/_Core/file(legacy)/file.h"
#include "../../IS_Bace/_Core/input/input.h"
#include "../../IS_Bace/_Core/debugproc/debugproc.h"
#include "../smoke/smoke.h"
#include "../../IS_Bace/_Expansion/meshfield/meshField.h"
#include "../meshroad/meshroad.h"
#include "../../IS_Bace/_Core/collision/collision.h"
#include "../../main.h"
#include "../imgcontroller/imgcontroller.h"
#include "../../IS_Bace/_Expansion/particle_billboard/particleBillboard.h"
#include "../../IS_Bace/_Core/_object/object_3d/object3D.h"
#include "../../IS_Bace/_Expansion/gauge/gauge.h"
#include "../object2dmap/object2DMap.h"
#include "../speedmeter/speedmeter.h"

//無名名前空間
namespace
{
	const float CHARA_RESPAWN_HEIGHT = 0.0f;
	const float ROTATE_SPEED = 0.01f;
	const float ACCEL_COEF = 0.04f;
	const float BRAKE_POW = 3.0f;
	const float NITRO_POW = 10.0f;
	const float BASE_ADD_NITRO = 0.001f;
	const float DRIFT_ADD_NITRO = 0.0005f;
	const float USE_NITRO = -0.01f;
	const float REQ_MIN_NITRO = 0.05f;
	const float NO_NITRO_SPEED = 0.7f;
	const float WHEEL_RADIUS = 22.0f;
	const float MAX_RPM = 1800.0f;
	const float MAX_RPS = MAX_RPM / 60;
	const float TUTORIAL_REST = 0.7f;
	const float WEIGHT = 10.0f;
	const float DRIFT_HANDLING_POWER = 1.4f;
	const float MAX_CAMERA_LEN = 170.0f;
	const float MIN_CAMERA_LEN = 110.0f;
	const float BOOST_FIRE_ALPHA_PLUS = 0.2f;
	const float BOOST_FIRE_ALPHA_MINUS = 0.02f;
	const float BOOST_FIRE_R = 0.3f;
	const float BOOST_FIRE_G = 0.41f;
	const float BOOST_FIRE_B = 1.0f;
	const float HILL_JUDGE = 0.44f;		//坂道と判断するYのベクトル量（坂道の角度=26°としたときのYの距離を正規化）
	const float SMOKE_ALPHA_MAX = 0.3f;
	const float SMOKE_ALPHA_ADD = 0.006f;
	const float SMOKE_ALPHA_DEC = -0.0012f;
}

//=================================
//コンストラクタ
//=================================
CPlayer::CPlayer(int nPriority) : CChara(nPriority)
{
	m_pController = nullptr;
	m_pCollider = nullptr;
	m_posOld = IS_Utility::VEC3_ZERO;
	m_move = IS_Utility::VEC3_ZERO;
	m_vecMove = IS_Utility::VEC3_ZERO;
	m_fSpeed = 0.0f;
	m_fWidth = 10.0f;
	m_fHeight = 0.0f;
	m_fDepth = 10.0f;
	m_nCounterJumpTime = 0;
	m_bBoost = false;
	m_bDrift = false;
	m_fHandleRot = 0.0f;
	m_fDriftRot = 0.0f;
	m_pBoostFire = nullptr;
	m_pGauge = nullptr;
	m_pMap = nullptr;
	m_pSpeedMeter = nullptr;
	m_fBoostFireAlpha = 0.0f;
	m_fSpeedLimit = 0.0f;
	m_apDriftSmoke[0] = nullptr;
	m_apDriftSmoke[1] = nullptr;
	m_fSmokeAlpha = 0.0f;
}

//=================================
//デストラクタ
//=================================
CPlayer::~CPlayer()
{
}

//=================================
//初期化
//=================================
HRESULT CPlayer::Init(void)
{
	CManager* pManager = CManager::GetInstance();
	CSound* pSound = pManager->GetSound();

	//親初期化
	CChara::Init();

	//前の位置を設定
	m_posOld = GetPos();

	//向き設定
	D3DXVECTOR3 rot = GetRot();
	rot.y += IS_Utility::FixRot(rot.y + D3DX_PI);
	SetRot(rot);
	m_fHandleRot = rot.y;

	//カメラの距離設定
	pManager->GetCamera()->SetLength(MAX_CAMERA_LEN);

	//コントローラーいったんKBで設定
	m_pController = new CImgController(new CControllerKB);

	//ブースト時の炎のオブジェクト生成
	m_pBoostFire = CObject3D::Create(IS_Utility::VEC3_ZERO, IS_Utility::VEC3_ZERO, 2.0f, 20.0f,PRIORITY_04);
	m_pBoostFire->BindTexture(CTexture::PRELOAD_26_EFFECT_FIRE);
	SetBoostFire(GetPos());

	//ドリフト時の煙オブジェクト生成
	m_apDriftSmoke[0] = CSmoke::Create(IS_Utility::VEC3_ZERO, 10.0f, 4);
	m_apDriftSmoke[0]->BindTexture(CTexture::PRELOAD_25_EFFECT_SMOKE);
	m_apDriftSmoke[1] = CSmoke::Create(IS_Utility::VEC3_ZERO, 10.0f, 4);
	m_apDriftSmoke[1]->BindTexture(CTexture::PRELOAD_25_EFFECT_SMOKE);
	SetSmokePos(GetPos());
	SetSmokeAlpha(m_fSmokeAlpha);

	//あらかじめ音鳴らす
	pSound->Play(CSound::SOUND_LABEL_SE_RUN);
	pSound->SetVolume(CSound::SOUND_LABEL_SE_RUN, 0.0f);

	return S_OK;
}

//=================================
//終了
//=================================
void CPlayer::Uninit(void)
{
	if (m_pCollider != nullptr)
	{
		m_pCollider->Release();
		m_pCollider = nullptr;
	}
	if (m_pController != nullptr)
	{
		delete m_pController;
		m_pController = nullptr;
	}

	CChara::Uninit();

	Release();
}

//=================================
//更新
//=================================
void CPlayer::Update(void)
{
	CManager* pManager = CManager::GetInstance();
	CCamera* pCamera = pManager->GetCamera();
	
	D3DXVECTOR3 pos = GetPos();
	m_posOld = pos;	//前の位置設定

	if (m_state == STATE::STATE_GAME)
	{//ゲーム操作（速度制限なし）
		m_fSpeedLimit = MAX_RPS;
		Control(pos);

		//リスポーン判定
		if (pos.y <= CHARA_RESPAWN_HEIGHT)
		{
			pos = D3DXVECTOR3(0.0f, 120.0f, -2300.0f);
			m_fHandleRot = D3DX_PI;
			m_fDriftRot = 0.0f;
			m_fSpeed = MAX_RPS * NO_NITRO_SPEED * 0.6f;
			m_nCounterJumpTime = 0;
		}
	}
	else if (m_state == STATE::STATE_TUTORIAL)
	{//チュートリアル操作（速度制限あり）
		m_fSpeedLimit = MAX_RPS * TUTORIAL_REST;
		Control(pos);
	}
	else if (m_state == STATE::STATE_SYSTEM_START)
	{//スタート前操縦
		AutoControll(pos);
	}
	else if (m_state == STATE::STATE_SYSTEM_GOAL)
	{//ゴール演出
		//減速
		m_fSpeed = IS_Utility::Clamp(m_fSpeed * 0.9f, MAX_RPS, 0.0f);

		//方向指定
		m_vecMove = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		//重力加速度による移動量変更
		m_move = m_vecMove * WHEEL_RADIUS * D3DX_PI * m_fSpeed / MAX_FPS;
		
		//カメラ位置更新
		pCamera->SetRot(D3DXVECTOR3(-0.04f * D3DX_PI, 0.8f * D3DX_PI, 0.0f));
	}

	//位置向き更新
	pCamera->SetPosR(pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f));
	pCamera->SetLength(IS_Utility::Clamp(MAX_CAMERA_LEN * (m_fSpeed / MAX_RPS),
		MAX_CAMERA_LEN, MIN_CAMERA_LEN));
	CChara::SetPos(pos + m_move);
	CChara::SetRot(D3DXVECTOR3(0.0f, m_fHandleRot + m_fDriftRot,0.0f));
	m_pMap->SetCameraPosR(pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f));
	m_pMap->SetCameraPosV(pos + D3DXVECTOR3(1.0f, 1500.0f, 0.0f));

	//ブースト時の炎の見た目設定
	SetBoostFire(pos);

	//ドリフト時の煙の見た目設定
	SetSmokePos(pos);

	//スピードメーターの設定
	m_pSpeedMeter->SetGauge(m_fSpeed / MAX_RPS);

	//移動量減衰
	m_move.x = 0.0f;
	m_move.z = 0.0f;

	//デバッグ表示
#if _DEBUG
	CManager::GetInstance()->GetDebProc()->Print("RPM = %f\n", m_fSpeed * 60.0f);
	CManager::GetInstance()->GetDebProc()->Print("x = %f, y = %f, z = %f\n", pos.x, pos.y, pos.z);
#endif

	CChara::Update();
}

//=================================
//描画
//=================================
void CPlayer::Draw(void)
{
	CChara::Draw();
}

//=================================
//生成
//=================================
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos, CGauge* pGauge, CObject2DMap* pMap, CSpeedMeter* pSpeedMeter)
{
	CPlayer* pPlayer = nullptr;

	if (pPlayer == nullptr)
	{
		//オブジェクト2Dの生成
		pPlayer = new CPlayer;

		//初期化
		pPlayer->Init();

		//データ設定
		pPlayer->SetPos(pos);
		pPlayer->m_state = STATE::STATE_GAME;
		pPlayer->m_pGauge = pGauge;
		pPlayer->m_pMap = pMap;
		pPlayer->m_pSpeedMeter = pSpeedMeter;

		//モデル組み立て
		pPlayer->SetupModel("data//motion_car.txt");

		//当たり判定追加
		pPlayer->m_pCollider = CBoxCollider::Create(pPlayer);
		pPlayer->m_pCollider->SetType(CBoxCollider::TYPE::TYPE_COLLISION);

		return pPlayer;
	}

	return nullptr;
}

//=================================
//角度設定（プレイヤー用）
//=================================
void CPlayer::SetRot(const D3DXVECTOR3 rot)
{
	//普通に設定
	CChara::SetRot(rot);

	//移動方向設定
	m_fHandleRot = IS_Utility::FixRot(m_fHandleRot + rot.y);
	D3DXVECTOR3 pos = GetPos();
	m_vecMove = CMeshField::GetLandingRotAll(pos, pos + m_move, m_fHandleRot + m_fDriftRot);
	m_vecMove.x *= -1.0f;
	m_vecMove.z *= -1.0f;
}

//=================================
//コントローラー設定
//=================================
void CPlayer::SetController(CImgController* pController)
{
	if (m_pController != nullptr)
	{
		delete m_pController;
	}
	m_pController = pController;
}

//=================================
//プレイヤー操作
//=================================
void CPlayer::Control(D3DXVECTOR3& pos)
{
	//サウンド
	CSound* pSound = CManager::GetInstance()->GetSound();

	//加速・速度制御
	bool bBrake = false;
	if (m_pController->Nitro() == true && m_pGauge->GetRate() > REQ_MIN_NITRO)
	{
		m_bBoost = true;
	}

	if (m_bBoost == true && m_pGauge->GetRate() > 0.0f)
	{//加速中
		m_fSpeed = IS_Utility::Clamp(m_fSpeed + ACCEL_COEF * NITRO_POW, m_fSpeedLimit, 0.0f);
		m_pGauge->AddRate(USE_NITRO);
	}
	else
	{//加速していない
		m_bBoost = false; 
		m_pGauge->AddRate(BASE_ADD_NITRO);
		if (m_fSpeed >= m_fSpeedLimit * NO_NITRO_SPEED)
		{//最大速度の一定割合以上なら減速
			m_fSpeed = IS_Utility::Clamp(m_fSpeed - ACCEL_COEF * BRAKE_POW, m_fSpeedLimit, 0.0f);
		}
		else
		{
			m_fSpeed = IS_Utility::Clamp(m_fSpeed + ACCEL_COEF, m_fSpeedLimit * NO_NITRO_SPEED, 0.0f);
		}
	}
	if (m_pController->Brake() == true)
	{
		bBrake = true;
	}

	//移動と向き設定
	float fTransRot = m_fDriftRot * 0.07f;
	m_fHandleRot += fTransRot;
	m_fDriftRot -= fTransRot;

	float handleRot = m_pController->Handle();
	if (fabsf(handleRot) > 0.0f)
	{
		float addRot = ROTATE_SPEED * handleRot;

		if (bBrake == true || m_bDrift == true)
		{//ドリフト開始
			m_bDrift = true;
			m_fDriftRot = IS_Utility::FixRot(m_fDriftRot + addRot + ROTATE_SPEED * handleRot * DRIFT_HANDLING_POWER);
			m_fSpeed -= ACCEL_COEF * 1.5f;
			m_pGauge->AddRate(DRIFT_ADD_NITRO);
			SetSmokeAlpha(SMOKE_ALPHA_ADD);
		}
		else
		{
			SetSmokeAlpha(SMOKE_ALPHA_DEC);
			m_fHandleRot += addRot;
		}
	}
	else if (m_bDrift == true)
	{//ドリフト減速
		m_fSpeed -= ACCEL_COEF * 0.5f;
		m_pGauge->AddRate(DRIFT_ADD_NITRO * 0.5f);
		if (fabsf(m_fDriftRot) <= 0.07f)
		{//ドリフト終了
			m_bDrift = false;
			if (fabsf(m_fDriftRot) <= 0.002f)
			{
				m_fHandleRot += m_fDriftRot;
				m_fDriftRot = 0.0f;
			}
		}
		SetSmokeAlpha(SMOKE_ALPHA_DEC);
	}
	else if (bBrake == true)
	{//ドリフト中でもハンドル操作もしてない。けどブレーキ掛けてる
		SetSmokeAlpha(SMOKE_ALPHA_DEC);
		m_fSpeed = IS_Utility::Clamp(m_fSpeed - ACCEL_COEF * BRAKE_POW, m_fSpeedLimit, 0.0f);
	}
	else
	{
		SetSmokeAlpha(SMOKE_ALPHA_DEC);
	}

	//音制御
	//ドリフト
	if (m_bDrift == false && pSound->IsPlay(CSound::SOUND_LABEL_SE_DRIFT) == true)
	{//ドリフトしておらずかつドリフト音を鳴らしている
		pSound->Stop(CSound::SOUND_LABEL_SE_DRIFT);
	}
	else if (pSound->IsPlay(CSound::SOUND_LABEL_SE_DRIFT) == false)
	{//ドリフトしておりかつドリフト音を鳴らしていない
		pSound->Play(CSound::SOUND_LABEL_SE_DRIFT);
	}

	//走行音
	float fSpeedPercent = m_fSpeed / MAX_RPS;
	pSound->SetVolume(CSound::SOUND_LABEL_SE_RUN, fSpeedPercent);

	//ジャンプカウンタ増やす
	m_nCounterJumpTime++;

	//重力加速度による移動量変更
	m_move = m_vecMove * WHEEL_RADIUS * D3DX_PI * m_fSpeed / MAX_FPS;
	m_move.y -= (IS_Utility::ACCELERATION_GRAVITY * m_nCounterJumpTime / MAX_FPS) * WEIGHT;

	//メッシュフィールドに乗っかる
	float height = CMeshField::GetHeightAll(pos, pos + m_move);
	if (height > -FLT_MAX)
	{//メッシュフィールドの上にいる
		D3DXVECTOR3 posNew = pos + m_move;
		if (posNew.y <= height)
		{//着地した
			D3DXVECTOR3 vec;
			posNew.y = height;
			D3DXVec3Normalize(&vec, &(posNew - pos));
			if (vec.y < HILL_JUDGE)
			{
				m_nCounterJumpTime = 0;
				pos.y = height;
				m_move.y = 0.0f;

				m_vecMove = CMeshField::GetLandingRotAll(pos, pos + m_move, m_fHandleRot + m_fDriftRot);
				m_vecMove.x *= -1.0f;
				m_vecMove.z *= -1.0f;
			}
		}
	}

	//カメラ位置更新
	CManager::GetInstance()->GetCamera()->SetRot(D3DXVECTOR3(-0.055f * D3DX_PI, -IS_Utility::FixRot(m_fHandleRot + D3DX_PI) + m_fDriftRot * 0.05f, 0.0f));
}

//=================================
//自動操縦
//=================================
void CPlayer::AutoControll(D3DXVECTOR3& pos)
{
	//ゲージ回復
	m_pGauge->AddRate(BASE_ADD_NITRO);

	if (m_fSpeed >= MAX_RPS * TUTORIAL_REST * NO_NITRO_SPEED)
	{//最大速度の一定割合以上なら減速
		m_fSpeed = IS_Utility::Clamp(m_fSpeed - ACCEL_COEF * BRAKE_POW, MAX_RPS * TUTORIAL_REST, 0.0f);
	}

	//重力加速度による移動量変更
	m_move = m_vecMove * WHEEL_RADIUS * D3DX_PI * m_fSpeed / MAX_FPS;
	m_move.y -= (IS_Utility::ACCELERATION_GRAVITY * m_nCounterJumpTime / MAX_FPS) * WEIGHT;

	//メッシュフィールドに乗っかる
	float height = CMeshRoad::GetHeightAll(pos, pos + m_move);
	if (height > -FLT_MAX)	//仮
	{//メッシュフィールドの上にいる
		m_nCounterJumpTime = 0;
		pos.y = height;
		m_move.y = 0.0f;

		m_vecMove = CMeshRoad::GetPirotRotAll(pos, pos + m_move);
		D3DXVec3Normalize(&m_vecMove, &m_vecMove);

		float rotYDest = atan2f(-m_vecMove.x, -m_vecMove.z);
		float rotYDiff = rotYDest - m_fHandleRot;
		m_fHandleRot += rotYDiff * 0.3f;
	}

	//カメラ位置更新
	CManager::GetInstance()->GetCamera()->SetRot(D3DXVECTOR3(-0.055f * D3DX_PI, -IS_Utility::FixRot(m_fHandleRot + D3DX_PI) + m_fDriftRot * 0.05f, 0.0f));

	//状態リセット
	m_bBoost = false;
	m_bDrift = false;

	if (CManager::GetInstance()->GetSound()->IsPlay(CSound::SOUND_LABEL_SE_DRIFT) == true)
	{//ドリフトしておらずかつドリフト音を鳴らしている
		CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_SE_DRIFT);
	}
}

//=================================
//ブースト時の炎のオブジェクト設定
//=================================
void CPlayer::SetBoostFire(D3DXVECTOR3& pos)
{
	if (m_pBoostFire != nullptr)
	{
		if (m_pController->Nitro() == true)
		{
			m_fBoostFireAlpha = IS_Utility::Clamp(m_fBoostFireAlpha + BOOST_FIRE_ALPHA_PLUS, 1.0f, 0.0f);
		}
		else
		{
			m_fBoostFireAlpha = IS_Utility::Clamp(m_fBoostFireAlpha - BOOST_FIRE_ALPHA_MINUS, 1.0f, 0.0f);
		}
		m_pBoostFire->SetCol(D3DXCOLOR(BOOST_FIRE_R, BOOST_FIRE_G, BOOST_FIRE_B, m_fBoostFireAlpha));

		//再配置
		D3DXVECTOR3 rotatedFirePos = IS_Utility::RotateVtx(
			D3DXVECTOR3(m_fWidth * 0.5f, 0.0f, -m_fDepth * 2.0f - 10.0f),
			D3DXVECTOR3(0.0f, IS_Utility::FixRot(m_fHandleRot + m_fDriftRot + D3DX_PI), 0.0f),
			pos + m_move + D3DXVECTOR3(0.0f, 4.0f, 0.0f));

		m_pBoostFire->SetPos(rotatedFirePos);
		m_pBoostFire->SetRot(D3DXVECTOR3(0.0f, IS_Utility::FixRot(m_fHandleRot + m_fDriftRot), 0.0f));
	}
}

//=================================
//ドリフト時の煙のオブジェクト位置設定
//=================================
void CPlayer::SetSmokePos(D3DXVECTOR3& pos)
{
	//位置設定
	D3DXVECTOR3 rotatedSmokePos;

	//0
	rotatedSmokePos = IS_Utility::RotateVtx(
		D3DXVECTOR3(-m_fWidth * 0.9f, 0.0f, -m_fDepth * 1.7f),
		D3DXVECTOR3(0.0f, IS_Utility::FixRot(m_fHandleRot + m_fDriftRot + D3DX_PI), 0.0f),
		GetPos() + D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_apDriftSmoke[0]->SetPos(rotatedSmokePos);

	//1
	rotatedSmokePos = IS_Utility::RotateVtx(
		D3DXVECTOR3(m_fWidth * 0.9f, 0.0f, -m_fDepth * 1.7f),
		D3DXVECTOR3(0.0f, IS_Utility::FixRot(m_fHandleRot + m_fDriftRot + D3DX_PI), 0.0f),
		GetPos() + D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_apDriftSmoke[1]->SetPos(rotatedSmokePos);
}

//=================================
//ドリフト時の煙のオブジェクト色設定
//=================================
void CPlayer::SetSmokeAlpha(float fAdd)
{
	m_fSmokeAlpha = IS_Utility::Clamp(m_fSmokeAlpha + fAdd, SMOKE_ALPHA_MAX, 0.0f);

	m_apDriftSmoke[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fSmokeAlpha));
	m_apDriftSmoke[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fSmokeAlpha));
}
