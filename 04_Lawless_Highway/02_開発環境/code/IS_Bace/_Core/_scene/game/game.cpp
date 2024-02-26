//======================================================
//
//�Q�[���V�[��[game.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "game.h"
#include "../../../../main.h"
#include "../pause/pause.h"
#include "../result/result.h"
#include "../ranking/ranking.h"
#include "../../manager/manager.h"
#include "../../texture/texture.h"
#include "../../utility/Utility.h"
#include "../../utility/Utility_Vector.h"
#include "../../camera/camera.h"
#include "../../sound/sound.h"
#include "../../_object/object_empty/object.h"
#include "../../input/input.h"
#include "../../../../Addition/imgcontroller/imgcontroller.h"
#include "../../../_Expansion/fade/fade.h"
#include "../../file(legacy)/file.h"

#include "../../../../Addition/player/player.h"
#include "../../../_Expansion/meshfield/meshField.h"
#include "../../../../Addition/meshroad/meshroad.h"
#include "../../../_Expansion/meshsky/meshsky.h"
#include "../../../_Expansion/timer/timer.h"
#include "../../../_Expansion/gauge/gauge.h"
#include "../../../../Addition/goal/goal.h"
#include "../../../../Addition/tutorialobj/tutorialobj.h"
#include "../../../../Addition/object2dmap/object2DMap.h"
#include "../../../../Addition/speedmeter/speedmeter.h"

#include "../../../../ISMD_IO/objloader/objloader.h"

namespace
{
	int TIME_LIMIT = 90;
	float BGM_FADEOUT_SPEED = 0.01f;
}

//=================================
//�R���X�g���N�^
//=================================
CGame::CGame()
{
	m_pPause = nullptr;
	m_pFade = nullptr;
	m_pTimer = nullptr;
	m_pGauge = nullptr;
	m_pPlayer = nullptr;
	m_bUseGP = false;
	m_pConfig = nullptr;
	m_fBGMVolume = 0.0f;
}

//=================================
//�f�X�g���N�^
//=================================
CGame::~CGame()
{
}

//=================================
//������
//=================================
HRESULT CGame::Init(void)
{
	//�J�������Z�b�g
	CManager::GetInstance()->CManager::GetInstance()->GetCamera()->ResetPos();
	CManager::GetInstance()->CManager::GetInstance()->GetCamera()->SetLength(100.0f);

	//��ɔz�u
	m_pGauge = CGauge::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 110.0f, 0.0f), IS_Utility::VEC3_ZERO, 256.0f, 24.0f);
	m_pGauge->SetRate(1.0f);
	CObject2DMap* pMap = CObject2DMap::Create(D3DXVECTOR3(116.0f, SCREEN_HEIGHT - 116.0f, 0.0f), IS_Utility::VEC3_ZERO, 200.0f, 200.0f);
	CSpeedMeter* pSpeedMeter = CSpeedMeter::Create(D3DXVECTOR3(SCREEN_WIDTH - 116.0f, SCREEN_HEIGHT - 116.0f, 0.0f), 200.0f);

	//�v���C���[�z�u
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(22485.0f, -378.0f, -1845.0f), m_pGauge, pMap, pSpeedMeter);
	m_pPlayer->SetRot(D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f));
	m_pPlayer->SetState(CPlayer::STATE::STATE_TUTORIAL);

	//�I�u�W�F�N�g�z�u
	//���H
	LoadRoadScriptFile("data//road_data_main.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_sub.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_TGConnect.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_dummy.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_tutorial.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);

	//�n��
	CMeshField::Create(D3DXVECTOR3(0.0f, -381.5f, 6000.0f), IS_Utility::VEC3_ZERO, 2048.0f, 2048.0f, 24, 24)
		->BindTexture(CTexture::PRELOAD_34_FIELD_LEAF);

	//UI
	m_pTimer = CTimerMSmS::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 32.0f, 0.0f), IS_Utility::VEC3_ZERO, 48.0f, 64.0f);
	m_pTimer->CTimer::Set(0, CTimer::COUNT::COUNT_UP);
	m_pTimer->BindTexture(CTexture::PRELOAD::PRELOAD_04_TIMER_NUMBER);
	m_pTimer->BindSymbolTexture(CTexture::PRELOAD::PRELOAD_05_TIMER_SYMBOL);

	//����
	m_pConfig = CObject2D::Create(D3DXVECTOR3(1173.0f, 76.5f, 0.0f), IS_Utility::VEC3_ZERO, 214.0f, 153.0f, CObject::PRIORITY_05);
	m_pConfig->BindTexture(CTexture::PRELOAD_23_CONFIG_KB);

	//�`���[�g���A���I�u�W�F�N�g
	CTutorialObj::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 44.5f, 0.0f), IS_Utility::VEC3_ZERO, 313.0f, 89.0f, m_pTimer, m_pPlayer);

	//���b�V����
	CMeshSky::Create(D3DXVECTOR3(6000.0f,0.0f,4000.0f), IS_Utility::VEC3_ZERO, 18000.0f, 12, 12);
	m_pGoal = CGoal::Create(D3DXVECTOR3(-1500.0f, 13.0f, 16500.0f), 600.0f, 600.0f, 100.0f);

	//BGM�炷
	m_fBGMVolume = 1.0f;
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_GAME);

	return S_OK;
}

//=================================
//�I��
//=================================
void CGame::Uninit(void)
{
	//�I�u�W�F�S�j��
	for (int cnt = 0; cnt < CObject::PRIORITY_FADE; cnt++)
	{
		CObject::ReleaseAll(cnt);
	}

	//���~�߂�
	CManager::GetInstance()->GetSound()->Stop();
}

//=================================
//�X�V
//=================================
void CGame::Update(void)
{
	CManager* pIns = CManager::GetInstance();
	CSound* pSound = pIns->GetSound();
	CInputKeyboard* pKeyboard = pIns->GetInputKeyboard();
	CInputGamePad* pGamepad = pIns->GetInputGamePad();

	//�R���g���[���ݒ�
	if (m_bUseGP == false && pGamepad->IsConnect() == true)
	{//�L�[�{�[�h���[�h���ɃQ�[���p�b�h�ڑ�
		m_pPlayer->SetController(new CImgController(new CControllerGP));
		m_pConfig->BindTexture(CTexture::PRELOAD_24_CONFIG_GP);
	}
	else if (pGamepad->IsConnect() == false)
	{//�Q�[���p�b�h���[�h���ɃQ�[���p�b�h�ؒf
		m_pPlayer->SetController(new CImgController(new CControllerKB));
		m_pConfig->BindTexture(CTexture::PRELOAD_23_CONFIG_KB);
	}

	//�S�[������
	if (m_pGoal->IsGoal() == true)
	{//�S�[���͈͂ɓ�����
		if (m_bIsGoal == false)
		{//1�񂾂����鏈��
			m_bIsGoal = true;
			m_pPlayer->SetState(CPlayer::STATE::STATE_SYSTEM_GOAL);
			//�l�ݒ�
			int nTime, nCounter;

			//���Ԏ擾
			m_pTimer->Stop();
			nTime = m_pTimer->GetTime();
			nCounter = m_pTimer->GetCounter();

			//�����^�C�}�[�̈ʒu���炵
			m_pTimer->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.55f, 0.0f));

			//�Q�[�W�������Ȃ�����
			m_pGauge->SetPos(D3DXVECTOR3(0.0f, -300.0f, 0.0f));

			//�����L���O�ɐݒ�
			CRanking::Set(CRanking::RankTimeMSmS(nTime, nCounter));

			//�e�L�X�g
			CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.325f, 0.0f),
				IS_Utility::VEC3_ZERO, 480.0f, 96.0f)->BindTexture(CTexture::PRELOAD::PRELOAD_13_RESULT_SUCCESS);

			//�X�^�[�g����
			CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.9f, 0.0f), IS_Utility::VEC3_ZERO, 756.0f, 99.0f)
				->BindTexture(CTexture::PRELOAD::PRELOAD_01_PUSHANYBUTTON);

			//�u���[�L�������炵�ق��̎Ԍ��ʉ��͏���
			pSound->Stop(CSound::SOUND_LABEL_SE_RUN);
			pSound->Stop(CSound::SOUND_LABEL_SE_DRIFT);
			pSound->Play(CSound::SOUND_LABEL_SE_CLEARBRAKE);
		}

		//������������
		m_fBGMVolume = IS_Utility::Clamp(m_fBGMVolume - BGM_FADEOUT_SPEED, 1.0f, 0.0f);
		pSound->SetVolume(CSound::SOUND_LABEL_BGM_GAME, m_fBGMVolume);

		//�{�^������
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
		{//���U���g�J��
			m_pFade = CFade::Create(CScene::MODE::MODE_RANKING);
		}
	}
}

//=================================
//�`��
//=================================
void CGame::Draw(void)
{
	//���i�͂��ׂ�CObject�N���X�p�����Ă���̂������Ă���̂Ŏ����`��
	//�|�[�Y�̒��g�����ׂ�CObject�N���X�p�����Ă�̂Ŏ����`��
	//����Ă����ł��邱�Ƃ͂Ȃ�
}