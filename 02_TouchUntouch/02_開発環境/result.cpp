//======================================================
//
//���U���g�V�[��[result.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "result.h"
#include "ranking.h"
#include "timer.h"
#include "score.h"
#include "fade.h"
#include "input.h"
#include "texture.h"
#include "sound.h"

//�ÓI�����o�ϐ�
const int CResult::PLAYSOUND_COUNTER = 4;

//=================================
//�R���X�g���N�^
//=================================
CResult::CResult()
{
	m_pTimer = nullptr;
	m_pBonus = nullptr;
	m_pScore = nullptr;
	m_pPress = nullptr;
	m_pFade = nullptr;
	m_nConter = 0;
}

//=================================
//�f�X�g���N�^
//=================================
CResult::~CResult()
{
}

//=================================
//������
//=================================
HRESULT CResult::Init(void)
{
	//�����w�i�i�������ςȂ��j
	CObject2D* pObj = CObject2D::Create(CManager::SCREEN_CENTER, CManager::VEC3_ZERO, 570.0f, 336.0f, CObject::PRIORITY_05);
	pObj->SetCol(D3DXCOLOR(0.66f, 0.5f, 0.75f, 1.0f));
	pObj->BindTexture(-1);

	//���ԁi�����j
	m_pTimer = CTimer::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 130.0f, 240.0f, 0.0f), CManager::VEC3_ZERO, 32.0f, 48.0f);
	m_pTimer->Set(0, CTimer::COUNT_DOWN);	//�����l�����ACreate�ŕύX�������
	m_pTimer->Stop();
	m_pTimer->BindTexture(CTexture::PRELOAD_03_NUMBER);
	//���ԁi�����j
	pObj = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 74.0f, 240.0f, 0.0f), CManager::VEC3_ZERO, 168.0f, 48.0f, CObject::PRIORITY_05);
	pObj->BindTexture(CTexture::PRELOAD_04_TIMERSTR);

	//�{�[�i�X�i�����j
	m_pBonus = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 192.0f, 288.0f, 0.0f), CManager::VEC3_ZERO, 32.0f, 48.0f);
	m_pBonus->Set(0);
	m_pBonus->BindTexture(CTexture::PRELOAD_03_NUMBER);
	//�{�[�i�X�i�����j
	pObj = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 108.0f, 288.0f, 0.0f), CManager::VEC3_ZERO, 168.0f, 48.0f, CObject::PRIORITY_05);
	pObj->BindTexture(CTexture::PRELOAD_06_BONUSSTR);

	//�ŏI�X�R�A�i�����j
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 192.0f, 384.0f, 0.0f), CManager::VEC3_ZERO, 32.0f, 48.0f);
	m_pScore->Set(0);	//�����l�����ACreate�ŕύX�������
	m_pScore->BindTexture(CTexture::PRELOAD_03_NUMBER);
	//�ŏI�X�R�A�i�����j
	pObj = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 108.0f, 384.0f, 0.0f), CManager::VEC3_ZERO, 168.0f, 48.0f, CObject::PRIORITY_05);
	pObj->BindTexture(CTexture::PRELOAD_05_SCORESTR);

	//�J�ڕ���
	m_pPress = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 480.0f, 0.0f), CManager::VEC3_ZERO, 560.0f, 48.0f, CObject::PRIORITY_05);
	m_pPress->BindTexture(CTexture::PRELOAD_07_SCENERANKKB);

	return S_OK;
}

//=================================
//�I��
//=================================
void CResult::Uninit(void)
{
	
}

//=================================
//�X�V
//=================================
void CResult::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamePad* pGamepad = CManager::GetInstance()->GetInputGamePad();

	m_nConter++;
	
	if (m_pTimer->GetTime() > 0)
	{//���Ԃ����炵�ă{�[�i�X���Z
		m_pTimer->Add(-1);
		m_pBonus->Add(100);

		if (m_nConter >= PLAYSOUND_COUNTER)
		{
			m_nConter = 0;
			//SE�Đ�
			CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_ITEM);
		}
	}//���͎��Ԃ�0�ɂȂ�������s
	else if (m_pBonus->GetScore() > 0)
	{//�{�[�i�X����ŏI�X�R�A�Ɉړ�
		m_pBonus->Add(-100);
		m_pScore->Add(100);

		if (m_nConter >= PLAYSOUND_COUNTER)
		{
			m_nConter = 0;
			//SE�Đ�
			CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_ITEM);
		}
	}//���̓{�[�i�X�ړ���������s
	else
	{//�ړ���������
		bool bPush = false;
		if (pGamepad != nullptr && pGamepad->IsConnect() == true)
		{//�Q�[���p�b�h����
			if (pGamepad->GetTrigger(XINPUT_GAMEPAD_A) == true)
			{
				bPush = true;
			}
		}
		else if (pKeyboard->GetTrigger(DIK_RETURN) == true)
		{//�L�[�{�[�h����
			bPush = true;
		}

		if (bPush == true && m_pFade == nullptr)
		{
			CRanking::Set(m_pScore->GetScore());
			m_pFade = CFade::Create(CScene::MODE_RANKING);

			//SE�Đ�
			CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
		}
	}

	if (pGamepad != nullptr && pGamepad->IsConnect() == true)
	{//�Q�[���p�b�h�����ؑ�
		m_pPress->BindTexture(CTexture::PRELOAD_08_SCENERANKGP);
	}
	else
	{//�L�[�{�[�h�����ؑ�
		m_pPress->BindTexture(CTexture::PRELOAD_07_SCENERANKKB);
	}
}

//=================================
//�`��
//=================================
void CResult::Draw(void)
{
	//����ɂ���Ă����
}

//=================================
//����
//=================================
CResult* CResult::Create(const int nTimer, const int nScore)
{
	CResult* pResult = nullptr;

	if (pResult == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pResult = new CResult;

		//������
		pResult->Init();

		//�f�[�^�ݒ�
		pResult->m_pTimer->Set(nTimer, CTimer::COUNT_DOWN);
		pResult->m_pTimer->Stop();
		pResult->m_pScore->Set(nScore);
		
		return pResult;
	}
	else
	{
		return nullptr;
	}
}
