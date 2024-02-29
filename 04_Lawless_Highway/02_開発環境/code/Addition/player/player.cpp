//======================================================
//
//�v���C���[����[player.cpp]
//Author:�Ό��D�n
//
//======================================================

//�C���N���[�h
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

//�������O���
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
	const float HILL_JUDGE = 0.44f;		//�⓹�Ɣ��f����Y�̃x�N�g���ʁi�⓹�̊p�x=26���Ƃ����Ƃ���Y�̋����𐳋K���j
	const float SMOKE_ALPHA_MAX = 0.3f;
	const float SMOKE_ALPHA_ADD = 0.006f;
	const float SMOKE_ALPHA_DEC = -0.0012f;
}

//=================================
//�R���X�g���N�^
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
//�f�X�g���N�^
//=================================
CPlayer::~CPlayer()
{
}

//=================================
//������
//=================================
HRESULT CPlayer::Init(void)
{
	CManager* pManager = CManager::GetInstance();
	CSound* pSound = pManager->GetSound();

	//�e������
	CChara::Init();

	//�O�̈ʒu��ݒ�
	m_posOld = GetPos();

	//�����ݒ�
	D3DXVECTOR3 rot = GetRot();
	rot.y += IS_Utility::FixRot(rot.y + D3DX_PI);
	SetRot(rot);
	m_fHandleRot = rot.y;

	//�J�����̋����ݒ�
	pManager->GetCamera()->SetLength(MAX_CAMERA_LEN);

	//�R���g���[���[��������KB�Őݒ�
	m_pController = new CImgController(new CControllerKB);

	//�u�[�X�g���̉��̃I�u�W�F�N�g����
	m_pBoostFire = CObject3D::Create(IS_Utility::VEC3_ZERO, IS_Utility::VEC3_ZERO, 2.0f, 20.0f,PRIORITY_04);
	m_pBoostFire->BindTexture(CTexture::PRELOAD_26_EFFECT_FIRE);
	SetBoostFire(GetPos());

	//�h���t�g���̉��I�u�W�F�N�g����
	m_apDriftSmoke[0] = CSmoke::Create(IS_Utility::VEC3_ZERO, 10.0f, 4);
	m_apDriftSmoke[0]->BindTexture(CTexture::PRELOAD_25_EFFECT_SMOKE);
	m_apDriftSmoke[1] = CSmoke::Create(IS_Utility::VEC3_ZERO, 10.0f, 4);
	m_apDriftSmoke[1]->BindTexture(CTexture::PRELOAD_25_EFFECT_SMOKE);
	SetSmokePos(GetPos());
	SetSmokeAlpha(m_fSmokeAlpha);

	//���炩���߉��炷
	pSound->Play(CSound::SOUND_LABEL_SE_RUN);
	pSound->SetVolume(CSound::SOUND_LABEL_SE_RUN, 0.0f);

	return S_OK;
}

//=================================
//�I��
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
//�X�V
//=================================
void CPlayer::Update(void)
{
	CManager* pManager = CManager::GetInstance();
	CCamera* pCamera = pManager->GetCamera();
	
	D3DXVECTOR3 pos = GetPos();
	m_posOld = pos;	//�O�̈ʒu�ݒ�

	if (m_state == STATE::STATE_GAME)
	{//�Q�[������i���x�����Ȃ��j
		m_fSpeedLimit = MAX_RPS;
		Control(pos);

		//���X�|�[������
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
	{//�`���[�g���A������i���x��������j
		m_fSpeedLimit = MAX_RPS * TUTORIAL_REST;
		Control(pos);
	}
	else if (m_state == STATE::STATE_SYSTEM_START)
	{//�X�^�[�g�O���c
		AutoControll(pos);
	}
	else if (m_state == STATE::STATE_SYSTEM_GOAL)
	{//�S�[�����o
		//����
		m_fSpeed = IS_Utility::Clamp(m_fSpeed * 0.9f, MAX_RPS, 0.0f);

		//�����w��
		m_vecMove = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		//�d�͉����x�ɂ��ړ��ʕύX
		m_move = m_vecMove * WHEEL_RADIUS * D3DX_PI * m_fSpeed / MAX_FPS;
		
		//�J�����ʒu�X�V
		pCamera->SetRot(D3DXVECTOR3(-0.04f * D3DX_PI, 0.8f * D3DX_PI, 0.0f));
	}

	//�ʒu�����X�V
	pCamera->SetPosR(pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f));
	pCamera->SetLength(IS_Utility::Clamp(MAX_CAMERA_LEN * (m_fSpeed / MAX_RPS),
		MAX_CAMERA_LEN, MIN_CAMERA_LEN));
	CChara::SetPos(pos + m_move);
	CChara::SetRot(D3DXVECTOR3(0.0f, m_fHandleRot + m_fDriftRot,0.0f));
	m_pMap->SetCameraPosR(pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f));
	m_pMap->SetCameraPosV(pos + D3DXVECTOR3(1.0f, 1500.0f, 0.0f));

	//�u�[�X�g���̉��̌����ڐݒ�
	SetBoostFire(pos);

	//�h���t�g���̉��̌����ڐݒ�
	SetSmokePos(pos);

	//�X�s�[�h���[�^�[�̐ݒ�
	m_pSpeedMeter->SetGauge(m_fSpeed / MAX_RPS);

	//�ړ��ʌ���
	m_move.x = 0.0f;
	m_move.z = 0.0f;

	//�f�o�b�O�\��
#if _DEBUG
	CManager::GetInstance()->GetDebProc()->Print("RPM = %f\n", m_fSpeed * 60.0f);
	CManager::GetInstance()->GetDebProc()->Print("x = %f, y = %f, z = %f\n", pos.x, pos.y, pos.z);
#endif

	CChara::Update();
}

//=================================
//�`��
//=================================
void CPlayer::Draw(void)
{
	CChara::Draw();
}

//=================================
//����
//=================================
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos, CGauge* pGauge, CObject2DMap* pMap, CSpeedMeter* pSpeedMeter)
{
	CPlayer* pPlayer = nullptr;

	if (pPlayer == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pPlayer = new CPlayer;

		//������
		pPlayer->Init();

		//�f�[�^�ݒ�
		pPlayer->SetPos(pos);
		pPlayer->m_state = STATE::STATE_GAME;
		pPlayer->m_pGauge = pGauge;
		pPlayer->m_pMap = pMap;
		pPlayer->m_pSpeedMeter = pSpeedMeter;

		//���f���g�ݗ���
		pPlayer->SetupModel("data//motion_car.txt");

		//�����蔻��ǉ�
		pPlayer->m_pCollider = CBoxCollider::Create(pPlayer);
		pPlayer->m_pCollider->SetType(CBoxCollider::TYPE::TYPE_COLLISION);

		return pPlayer;
	}

	return nullptr;
}

//=================================
//�p�x�ݒ�i�v���C���[�p�j
//=================================
void CPlayer::SetRot(const D3DXVECTOR3 rot)
{
	//���ʂɐݒ�
	CChara::SetRot(rot);

	//�ړ������ݒ�
	m_fHandleRot = IS_Utility::FixRot(m_fHandleRot + rot.y);
	D3DXVECTOR3 pos = GetPos();
	m_vecMove = CMeshField::GetLandingRotAll(pos, pos + m_move, m_fHandleRot + m_fDriftRot);
	m_vecMove.x *= -1.0f;
	m_vecMove.z *= -1.0f;
}

//=================================
//�R���g���[���[�ݒ�
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
//�v���C���[����
//=================================
void CPlayer::Control(D3DXVECTOR3& pos)
{
	//�T�E���h
	CSound* pSound = CManager::GetInstance()->GetSound();

	//�����E���x����
	bool bBrake = false;
	if (m_pController->Nitro() == true && m_pGauge->GetRate() > REQ_MIN_NITRO)
	{
		m_bBoost = true;
	}

	if (m_bBoost == true && m_pGauge->GetRate() > 0.0f)
	{//������
		m_fSpeed = IS_Utility::Clamp(m_fSpeed + ACCEL_COEF * NITRO_POW, m_fSpeedLimit, 0.0f);
		m_pGauge->AddRate(USE_NITRO);
	}
	else
	{//�������Ă��Ȃ�
		m_bBoost = false; 
		m_pGauge->AddRate(BASE_ADD_NITRO);
		if (m_fSpeed >= m_fSpeedLimit * NO_NITRO_SPEED)
		{//�ő呬�x�̈�芄���ȏ�Ȃ猸��
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

	//�ړ��ƌ����ݒ�
	float fTransRot = m_fDriftRot * 0.07f;
	m_fHandleRot += fTransRot;
	m_fDriftRot -= fTransRot;

	float handleRot = m_pController->Handle();
	if (fabsf(handleRot) > 0.0f)
	{
		float addRot = ROTATE_SPEED * handleRot;

		if (bBrake == true || m_bDrift == true)
		{//�h���t�g�J�n
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
	{//�h���t�g����
		m_fSpeed -= ACCEL_COEF * 0.5f;
		m_pGauge->AddRate(DRIFT_ADD_NITRO * 0.5f);
		if (fabsf(m_fDriftRot) <= 0.07f)
		{//�h���t�g�I��
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
	{//�h���t�g���ł��n���h����������ĂȂ��B���ǃu���[�L�|���Ă�
		SetSmokeAlpha(SMOKE_ALPHA_DEC);
		m_fSpeed = IS_Utility::Clamp(m_fSpeed - ACCEL_COEF * BRAKE_POW, m_fSpeedLimit, 0.0f);
	}
	else
	{
		SetSmokeAlpha(SMOKE_ALPHA_DEC);
	}

	//������
	//�h���t�g
	if (m_bDrift == false && pSound->IsPlay(CSound::SOUND_LABEL_SE_DRIFT) == true)
	{//�h���t�g���Ă��炸���h���t�g����炵�Ă���
		pSound->Stop(CSound::SOUND_LABEL_SE_DRIFT);
	}
	else if (pSound->IsPlay(CSound::SOUND_LABEL_SE_DRIFT) == false)
	{//�h���t�g���Ă��肩�h���t�g����炵�Ă��Ȃ�
		pSound->Play(CSound::SOUND_LABEL_SE_DRIFT);
	}

	//���s��
	float fSpeedPercent = m_fSpeed / MAX_RPS;
	pSound->SetVolume(CSound::SOUND_LABEL_SE_RUN, fSpeedPercent);

	//�W�����v�J�E���^���₷
	m_nCounterJumpTime++;

	//�d�͉����x�ɂ��ړ��ʕύX
	m_move = m_vecMove * WHEEL_RADIUS * D3DX_PI * m_fSpeed / MAX_FPS;
	m_move.y -= (IS_Utility::ACCELERATION_GRAVITY * m_nCounterJumpTime / MAX_FPS) * WEIGHT;

	//���b�V���t�B�[���h�ɏ������
	float height = CMeshField::GetHeightAll(pos, pos + m_move);
	if (height > -FLT_MAX)
	{//���b�V���t�B�[���h�̏�ɂ���
		D3DXVECTOR3 posNew = pos + m_move;
		if (posNew.y <= height)
		{//���n����
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

	//�J�����ʒu�X�V
	CManager::GetInstance()->GetCamera()->SetRot(D3DXVECTOR3(-0.055f * D3DX_PI, -IS_Utility::FixRot(m_fHandleRot + D3DX_PI) + m_fDriftRot * 0.05f, 0.0f));
}

//=================================
//�������c
//=================================
void CPlayer::AutoControll(D3DXVECTOR3& pos)
{
	//�Q�[�W��
	m_pGauge->AddRate(BASE_ADD_NITRO);

	if (m_fSpeed >= MAX_RPS * TUTORIAL_REST * NO_NITRO_SPEED)
	{//�ő呬�x�̈�芄���ȏ�Ȃ猸��
		m_fSpeed = IS_Utility::Clamp(m_fSpeed - ACCEL_COEF * BRAKE_POW, MAX_RPS * TUTORIAL_REST, 0.0f);
	}

	//�d�͉����x�ɂ��ړ��ʕύX
	m_move = m_vecMove * WHEEL_RADIUS * D3DX_PI * m_fSpeed / MAX_FPS;
	m_move.y -= (IS_Utility::ACCELERATION_GRAVITY * m_nCounterJumpTime / MAX_FPS) * WEIGHT;

	//���b�V���t�B�[���h�ɏ������
	float height = CMeshRoad::GetHeightAll(pos, pos + m_move);
	if (height > -FLT_MAX)	//��
	{//���b�V���t�B�[���h�̏�ɂ���
		m_nCounterJumpTime = 0;
		pos.y = height;
		m_move.y = 0.0f;

		m_vecMove = CMeshRoad::GetPirotRotAll(pos, pos + m_move);
		D3DXVec3Normalize(&m_vecMove, &m_vecMove);

		float rotYDest = atan2f(-m_vecMove.x, -m_vecMove.z);
		float rotYDiff = rotYDest - m_fHandleRot;
		m_fHandleRot += rotYDiff * 0.3f;
	}

	//�J�����ʒu�X�V
	CManager::GetInstance()->GetCamera()->SetRot(D3DXVECTOR3(-0.055f * D3DX_PI, -IS_Utility::FixRot(m_fHandleRot + D3DX_PI) + m_fDriftRot * 0.05f, 0.0f));

	//��ԃ��Z�b�g
	m_bBoost = false;
	m_bDrift = false;

	if (CManager::GetInstance()->GetSound()->IsPlay(CSound::SOUND_LABEL_SE_DRIFT) == true)
	{//�h���t�g���Ă��炸���h���t�g����炵�Ă���
		CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_SE_DRIFT);
	}
}

//=================================
//�u�[�X�g���̉��̃I�u�W�F�N�g�ݒ�
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

		//�Ĕz�u
		D3DXVECTOR3 rotatedFirePos = IS_Utility::RotateVtx(
			D3DXVECTOR3(m_fWidth * 0.5f, 0.0f, -m_fDepth * 2.0f - 10.0f),
			D3DXVECTOR3(0.0f, IS_Utility::FixRot(m_fHandleRot + m_fDriftRot + D3DX_PI), 0.0f),
			pos + m_move + D3DXVECTOR3(0.0f, 4.0f, 0.0f));

		m_pBoostFire->SetPos(rotatedFirePos);
		m_pBoostFire->SetRot(D3DXVECTOR3(0.0f, IS_Utility::FixRot(m_fHandleRot + m_fDriftRot), 0.0f));
	}
}

//=================================
//�h���t�g���̉��̃I�u�W�F�N�g�ʒu�ݒ�
//=================================
void CPlayer::SetSmokePos(D3DXVECTOR3& pos)
{
	//�ʒu�ݒ�
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
//�h���t�g���̉��̃I�u�W�F�N�g�F�ݒ�
//=================================
void CPlayer::SetSmokeAlpha(float fAdd)
{
	m_fSmokeAlpha = IS_Utility::Clamp(m_fSmokeAlpha + fAdd, SMOKE_ALPHA_MAX, 0.0f);

	m_apDriftSmoke[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fSmokeAlpha));
	m_apDriftSmoke[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fSmokeAlpha));
}
