//======================================================
//
//�Q�[���V�[��[game.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "game.h"
#include "ranking.h"
#include "pause.h"
#include "result.h"
#include "texture.h"
#include "meshField.h"
#include "score.h"
#include "timer.h"
#include "objectX.h"
#include "meshsky.h"
#include "input.h"
#include "manager.h"
#include "camera.h"
#include "bg.h"
#include "sound.h"
#include "block3D.h"
#include "character.h"
#include "xmodel.h"
#include "switch.h"
#include "player.h"
#include "goal.h"
#include "item.h"
#include "objloader.h"
#include "switchmanager.h"
#include "blockmanager.h"
#include "block3D.h"
#include "object3D.h"

//�V�[���n
#include "result.h"

//UI�n
#include "timer.h"
#include "score.h"

//��
#include "goal.h"

//=================================
//�R���X�g���N�^
//=================================
CGame::CGame()
{
	m_pPlayer = nullptr;
	m_pTimer = nullptr;
	m_pScore = nullptr;
	m_pPause = nullptr;
	m_bStart = false;
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

	//����v���C���[�̃N���X����
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Init();
	}

	//�X�C�b�`�Ǘ��I�u�W�F�����Ɛݒ�
	m_pSwitchManager = CSwitchManager::Create();
	CBlock3D::SetSwitchManager(m_pSwitchManager);

	//�u���b�N�}�l����
	m_pBlockManager = CBlockManager::Create(m_pSwitchManager, m_pPlayer);

	//UI-------------------------------------------
	//�X�R�A�i�����j
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH + 8.0f, 32.0f, 0.0f), CManager::VEC3_ZERO, 32.0f, 48.0f);
	m_pScore->BindTexture(CTexture::PRELOAD_03_NUMBER);
	CItem::SetScoreInterface(m_pScore);

	//�X�R�A�i�����j
	CObject2D* pObj2D = CObject2D::Create(D3DXVECTOR3(988.0f, 32.0f, 0.0f), CManager::VEC3_ZERO, 168.0f, 48.0f, CObject::PRIORITY_05);
	pObj2D->BindTexture(CTexture::PRELOAD_05_SCORESTR);

	//�^�C�}�[����
	pObj2D = CObject2D::Create(D3DXVECTOR3(68.0f, 32.0f, 0.0f), CManager::VEC3_ZERO, 168.0f, 48.0f, CObject::PRIORITY_05);
	pObj2D->BindTexture(CTexture::PRELOAD_04_TIMERSTR);

	//�^�C�}�[�i�����j
	m_pTimer = CTimer::Create(D3DXVECTOR3(264.0f, 32.0f, 0.0f), CManager::VEC3_ZERO, 32.0f, 48.0f);
	m_pTimer->BindTexture(CTexture::PRELOAD_03_NUMBER);
	m_pTimer->Set(120, CTimer::COUNT_DOWN);
	m_bStart = false;

	//UI-------------------------------------------
	CObjLoader::LoadData("data\\tut_mapdata_game.ismd");
	
	//�L��������
	CCharacter::Create(D3DXVECTOR3(100.0f,150.0f,0.0f),CCharacter::TYPE_A, m_pPlayer);
	CCharacter::Create(D3DXVECTOR3(0.0f, 150.0f, 0.0f),CCharacter::TYPE_B, m_pPlayer);

	//�w�i
	CObject3D* pObj3D = CObject3D::Create(D3DXVECTOR3(0.0f,300.0f,700.0f), D3DXVECTOR3(-0.5f * D3DX_PI, 0.0f, 0.0f), 7200.0f, 4404.0f,CObject::PRIORITY_BG);
	pObj3D->BindTexture(CTexture::PRELOAD_27_BG_02);

	//BGM�Đ�
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_IN);
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

	//�X�R�A�p�C���^�[�t�F�[�X�|�C���^����
	CItem::UnsetScoreInterface();

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}
}

//=================================
//�X�V
//=================================
void CGame::Update(void)
{
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();	//�L�[�{�[�h�擾
	CInputGamePad* pGamepad = CManager::GetInstance()->GetInputGamePad();		//�Q�[���p�b�h�擾
	CGoal* pGoal = CGoal::GetTop();
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	bool bGoal = false;

	//�t�F�[�h���Ȃ��Ȃ�����J�n
	CObject* pFade = CObject::GetTop(CObject::PRIORITY_FADE);
	if (pFade == nullptr)
	{
		if (m_bStart == false)
		{
			m_pTimer->Start();
			m_bStart = true;
		}

		//���ԊǗ��ƏI������
		if (m_pTimer->GetTime() <= 0)
		{//���~
			bGoal = true;
		}
		else if (pGoal != nullptr)
		{
			while (pGoal != nullptr)
			{
				if (pGoal->IsGoal() == true)
				{//���~
					bGoal = true;
					break;
				}
				pGoal = pGoal->GetNext();
			}
		}

		if (bGoal == true)
		{//�S�[������
			m_pPlayer->SetControll(false);
			if (m_pResult == nullptr)
			{
				m_pTimer->Stop();
				m_pResult = CResult::Create(m_pTimer->GetTime(), m_pScore->GetScore());
			}
			else
			{
				m_pResult->Update();
			}
		}
		else
		{//�S�[�����ĂȂ�
			m_pPlayer->SetControll(true);

			//�|�[�Y����
			if (pKeyboard != nullptr && pKeyboard->GetTrigger(DIK_P) == true)
			{
				pManager->SetEnableUpdate(!pManager->GetEnableUpdate());
			}
			else if (pGamepad != nullptr && pGamepad->IsConnect() == true && pGamepad->GetTrigger(XINPUT_GAMEPAD_START) == true)
			{
				pManager->SetEnableUpdate(!pManager->GetEnableUpdate());
			}

			if (pManager->GetEnableUpdate() == false)
			{//�X�V��~�i�|�[�Y���j
				if (m_pPause == nullptr)
				{
					m_pPause = new CPause;
					m_pPause->Init();
				}
				m_pPause->Update();
			}
			else
			{
				if (m_pPause != nullptr)
				{
					m_pPause->Uninit();
					delete m_pPause;
					m_pPause = nullptr;
				}
			}
		}

		//�Ƃ肠�����񂷁i�L���E�����͏�ł��j
		if (m_pPlayer != nullptr)
		{
			m_pPlayer->Update();
		}
	}

	if (pCamera != nullptr)
	{//�J�����ړ�
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
		{//��
			pCamera->SetLength(lenXHalf * 2.0f);
		}
		else
		{
			pCamera->SetLength(900.0f);
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