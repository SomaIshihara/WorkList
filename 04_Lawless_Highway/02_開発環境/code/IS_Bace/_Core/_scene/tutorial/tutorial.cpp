//======================================================
//
//�`���[�g���A���V�[��[game.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "tutorial.h"
#include "..\..\manager\manager.h"
#include "..\..\texture\texture.h"
#include "..\..\input\input.h"
#include "..\..\camera\camera.h"
#include "..\..\sound\sound.h"

//UI�n
#include "..\..\..\_Expansion\fade\fade.h"

//�ÓI�����o�ϐ�
const int CTutorial::TUTORIAL_MOVE = 4;		//�ړ������̔ԍ�
const int CTutorial::TUTORIAL_CHANGE = 5;	//�ؑ֐����̔ԍ�

//=================================
//�R���X�g���N�^
//=================================
CTutorial::CTutorial()
{
	m_pPlayer = nullptr;
	m_pFade = nullptr;
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
}

//=================================
//�X�V
//=================================
void CTutorial::Update(void)
{
	CManager* pIns = CManager::GetInstance();
	CInputKeyboard* pKeyboard = pIns->GetInputKeyboard();
	CInputGamePad* pGamepad = pIns->GetInputGamePad();
	bool bPush = false;

	if (pGamepad != nullptr && pGamepad->IsConnect() == true)
	{//�Q�[���p�b�h�ڑ�
		if (pGamepad->GetTrigger(XINPUT_GAMEPAD_A))
		{
			bPush = true;
		}
	}
	else
	{//���ڑ�
		if (pKeyboard->GetTrigger(DIK_RETURN))
		{
			bPush = true;
		}
	}

	if (m_pFade == nullptr && bPush == true)
	{//�X�y�[�X�����ꂽ
		m_pFade = CFade::Create(CScene::MODE::MODE_GAME);
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