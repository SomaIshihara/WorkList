//======================================================
//
//�`���[�g���A���V�[��[game.cpp]
//Author:�Ό��D�n
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

//�V�[���n
#include "result.h"

//UI�n
#include "fade.h"

//�ÓI�����o�ϐ�
const int CTutorial::TUTORIAL_MOVE = 4;		//�ړ������̔ԍ�
const int CTutorial::TUTORIAL_CHANGE = 5;	//�ؑ֐����̔ԍ�

//=================================
//�R���X�g���N�^
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
//�f�X�g���N�^
//=================================
CTutorial::~CTutorial()
{
}

//=================================
//������
//=================================
HRESULT CTutorial::Init(void)
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
	CObjLoader::LoadData("data\\tut_mapdata_tutorial.ismd");

	//�u���b�N�}�l����
	m_pBlockManager = CBlockManager::Create(m_pSwitchManager, m_pPlayer);

	//�e�N�X�`���ς������`���[�g���A���I�u�W�F�N�g���擾
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

	//�w�i
	CObject3D* pObj3D = CObject3D::Create(D3DXVECTOR3(0.0f, 300.0f, 700.0f), D3DXVECTOR3(-0.5f * D3DX_PI, 0.0f, 0.0f), 7200.0f, 4404.0f, CObject::PRIORITY_BG);
	pObj3D->BindTexture(CTexture::PRELOAD_26_BG_01);
	
	//�L��������
	CCharacter::Create(D3DXVECTOR3(100.0f,150.0f,0.0f),CCharacter::TYPE_A, m_pPlayer);
	CCharacter::Create(D3DXVECTOR3(0.0f, 150.0f, 0.0f),CCharacter::TYPE_B, m_pPlayer);
	return S_OK;
}

//=================================
//�I��
//=================================
void CTutorial::Uninit(void)
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
void CTutorial::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();	//�L�[�{�[�h�擾
	CInputGamePad* pGamepad = CManager::GetInstance()->GetInputGamePad();
	CGoal* pGoal = CGoal::GetTop();
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	bool bGoal = false;

	//�Q�[���p�b�h�g�p�擾
	if (pGamepad != nullptr && pGamepad->IsConnect() == true)
	{//�g�p��
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
	{//���g�p
		if (m_pMoveTutorial != nullptr)
		{
			m_pMoveTutorial->GetTutorialStr()->BindTexture(CTexture::PRELOAD_28_TUTORIAL_05_KB);
		}
		if (m_pChangeTutorial != nullptr)
		{
			m_pChangeTutorial->GetTutorialStr()->BindTexture(CTexture::PRELOAD_29_TUTORIAL_06_KB);
		}
	}

	//�I������
	if (pGoal != nullptr)
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

	//�`���[�g���A���X�L�b�v
	if (pKeyboard != nullptr && pKeyboard->GetTrigger(DIK_P) == true)
	{
		bGoal = true;
	}
	else if(pGamepad != nullptr && pGamepad->IsConnect() == true && pGamepad->GetTrigger(XINPUT_GAMEPAD_START))
	{
		bGoal = true;
	}

	if (bGoal == true)
	{//�S�[������
		m_pPlayer->SetControll(false);
		if (m_pFade == nullptr)
		{
			//�t�F�[�h�o��
			m_pFade = CFade::Create(CScene::MODE_GAME);

			//BGM�Đ�
			CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_OUT);
		}
	}
	else
	{//�S�[�����ĂȂ�
		m_pPlayer->SetControll(true);
	}

	//�Ƃ肠�����񂷁i�L���E�����͏�ł��j
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Update();
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
void CTutorial::Draw(void)
{
	//���i�͂��ׂ�CObject�N���X�p�����Ă���̂������Ă���̂Ŏ����`��
	//�|�[�Y�̒��g�����ׂ�CObject�N���X�p�����Ă�̂Ŏ����`��
	//����Ă����ł��邱�Ƃ͂Ȃ�
}