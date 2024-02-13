//======================================================
//
//�v���C���[����[player.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "player.h"
#include "manager.h"
#include "input.h"
#include "camera.h"
#include "sound.h"

//=================================
//�R���X�g���N�^
//=================================
CPlayer::CPlayer()
{

}

//=================================
//�f�X�g���N�^
//=================================
CPlayer::~CPlayer()
{}

//=================================
//������
//=================================
HRESULT CPlayer::Init(void)
{
	m_controllType = CCharacter::TYPE_A;
	return S_OK;
}

//=================================
//�I��
//=================================
void CPlayer::Uninit(void)
{
	
}

//=================================
//�X�V
//=================================
void CPlayer::Update(void)
{
	if (m_bControlled == true)
	{//����\
		CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();	//�L�[�{�[�h�擾
		CInputGamePad* pGamepad = CManager::GetInstance()->GetInputGamePad();		//�Q�[���p�b�h�擾

		if (pGamepad != nullptr && pGamepad->IsConnect() == true)
		{//�Q�[���p�b�h�ڑ�
			//�ړ�
			if (pGamepad->GetPress(XINPUT_GAMEPAD_DPAD_LEFT) == true || pGamepad->GetLStickX() < 0)
			{//A�L�[��������Ă���
				m_nPressMove = DIK_A;
			}
			else if (pGamepad->GetPress(XINPUT_GAMEPAD_DPAD_RIGHT) == true || pGamepad->GetLStickX() > 0)
			{//D�L�[��������Ă���
				m_nPressMove = DIK_D;
			}
			else
			{//����������Ă��Ȃ�
				m_nPressMove = 0;
			}

			//�W�����v
			m_bPressJump = (pGamepad->GetTrigger(XINPUT_GAMEPAD_A) == true) ? true : false;

			//�L�����ؑ�
			if (pGamepad->GetTrigger(XINPUT_GAMEPAD_X) == true)
			{
				m_controllType = (m_controllType == CCharacter::TYPE_A) ? CCharacter::TYPE_B : CCharacter::TYPE_A;

				//SE�Đ�
				CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_CHANGE);
			}
		}
		else
		{//���ڑ�
			//�ړ�
			if (pKeyboard->GetPress(DIK_A) == true)
			{//A�L�[��������Ă���
				m_nPressMove = DIK_A;
			}
			else if (pKeyboard->GetPress(DIK_D) == true)
			{//D�L�[��������Ă���
				m_nPressMove = DIK_D;
			}
			else
			{//����������Ă��Ȃ�
				m_nPressMove = 0;
			}

			//�W�����v
			m_bPressJump = (pKeyboard->GetTrigger(DIK_SPACE) == true) ? true : false;

			//�L�����ؑ�
			if (pKeyboard->GetTrigger(DIK_S) == true)
			{
				m_controllType = (m_controllType == CCharacter::TYPE_A) ? CCharacter::TYPE_B : CCharacter::TYPE_A;

				//SE�Đ�
				CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_CHANGE);
			}
		}
	}
	else
	{//�s�\
		m_nPressMove = 0;
		m_bPressJump = false;
	}
}