//======================================================
//
//���U���g�V�[��[result.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "precompile.h"
#include "manager.h"
#include "result.h"
#include "game.h"
#include "fade.h"
#include "texture.h"
#include "bg.h"
#include "number.h"
#include "score.h"
#include "button.h"
#include "sound.h"

//�ÓI�����o�ϐ�
const int CResult::HEADLINE_TIME = 60;
const int CResult::ATK_TIME = HEADLINE_TIME + 40;
const int CResult::DEST_TIME = ATK_TIME + 40;
const int CResult::VALUE_TIME = DEST_TIME + 60;
const int CResult::RANK_TIME = VALUE_TIME + 60;
const float CResult::FADE_ALPHA = 0.4f;
const float CResult::FADE_SPEED = 0.03f;

//=================================
//�R���X�g���N�^
//=================================
CResult::CResult()
{
	m_pBG = nullptr;
	m_fAlpha = CManager::FLOAT_ZERO;
	m_pButton = nullptr;
	m_nCounter = CManager::INT_ZERO;
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
	//�w�i�𐶐��i���̌㓧���ɂ���j
	m_pBG = CBG::Create(PRIORITY_UI);	//�Q�[�����UI�Ƃ��Ԃ�Ȃ��悤�ɂ���
	m_pBG->BindTexture(-1);
	m_pBG->SetCol(D3DXCOLOR((DWORD)0x00000000));
	
	m_fAlpha = 0.0f;
	m_nCounter = 0;
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
	CSound* pSound = CManager::GetSound();
	m_fAlpha += FADE_SPEED;

	if (m_fAlpha >= FADE_ALPHA)
	{//������x�Â�����
		m_fAlpha = FADE_ALPHA;
		m_nCounter++;

		if (m_nCounter == HEADLINE_TIME)
		{//���o������
			CObject2D* pObject = nullptr;
			pObject = CObject2D::Create(D3DXVECTOR3(300.0f, 122.0f, 0.0f), CManager::VEC3_ZERO, 500.0f, 144.0f, PRIORITY_PAUSE);
			pObject->BindTexture(CTexture::PRELOAD_RESULT_HEADLINE);
			pSound->Play(CSound::SOUND_LABEL_SE_POPRESULT);
		}
		else if (m_nCounter == ATK_TIME)
		{//�U�����\��
			//����
			CObject2D* pObject = nullptr;
			pObject = CObject2D::Create(D3DXVECTOR3(300.0f, 272.0f, 0.0f), CManager::VEC3_ZERO, 250.0f, 72.0f, PRIORITY_PAUSE);
			pObject->BindTexture(CTexture::PRELOAD_RESULT_01);

			//����
			int nNum = CGame::GetATKNum();
			//�\
			CNumber* pNumber = nullptr;
			pNumber = CNumber::Create(D3DXVECTOR3(465.0f, 272.0f, 0.0f), CManager::VEC3_ZERO, 40.0f, 72.0f);
			pNumber->BindTexture(CTexture::PRELOAD_NUMBER);
			pNumber->SetNumber(nNum, 1);

			//��
			pNumber = CNumber::Create(D3DXVECTOR3(505.0f, 272.0f, 0.0f), CManager::VEC3_ZERO, 40.0f, 72.0f);
			pNumber->BindTexture(CTexture::PRELOAD_NUMBER);
			pNumber->SetNumber(nNum, 0);

			pSound->Play(CSound::SOUND_LABEL_SE_POPRESULT);
		}
		else if (m_nCounter == DEST_TIME)
		{//�S�󐔕\��
			//����
			CObject2D* pObject = nullptr;
			pObject = CObject2D::Create(D3DXVECTOR3(800.0f, 272.0f, 0.0f), CManager::VEC3_ZERO, 250.0f, 72.0f, PRIORITY_PAUSE);
			pObject->BindTexture(CTexture::PRELOAD_RESULT_02); 

			//����
			int nNum = CGame::GetDestNum();
			//�\
			CNumber* pNumber = nullptr;
			pNumber = CNumber::Create(D3DXVECTOR3(965.0f, 272.0f, 0.0f), CManager::VEC3_ZERO, 40.0f, 72.0f);
			pNumber->BindTexture(CTexture::PRELOAD_NUMBER);
			pNumber->SetNumber(nNum, 1);

			//��
			pNumber = CNumber::Create(D3DXVECTOR3(1005.0f, 272.0f, 0.0f), CManager::VEC3_ZERO, 40.0f, 72.0f);
			pNumber->BindTexture(CTexture::PRELOAD_NUMBER);
			pNumber->SetNumber(nNum, 0);

			pSound->Play(CSound::SOUND_LABEL_SE_POPRESULT);
		}
		else if (m_nCounter == VALUE_TIME)
		{//��Q���z�\��
			//����
			CObject2D* pObject = nullptr;
			pObject = CObject2D::Create(D3DXVECTOR3(250.0f, 462.0f, 0.0f), CManager::VEC3_ZERO, 375.0f, 108.0f, PRIORITY_PAUSE);
			pObject->BindTexture(CTexture::PRELOAD_RESULT_03);

			//����
			long long nScore = CGame::GetScoreObj()->GetScore();
			CScore* pScore = nullptr;
			pScore = CScore::Create(D3DXVECTOR3(1097.5f, 462.0f, 0.0f), CManager::VEC3_ZERO, 60.0f, 108.0f);
			pScore->Set(nScore);

			pSound->Play(CSound::SOUND_LABEL_SE_POPRESULT);
		}
		else if (m_nCounter == RANK_TIME)
		{//�����L���O�J�ڃ{�^���\��
			m_pButton = CButton2D::Create(D3DXVECTOR3(1100.0f, 650.0f, 0.0f), CManager::VEC3_ZERO, 311.0f, 111.0f);
			m_pButton->BindTexture(CTexture::PRELOAD_TITLE_RANK);
		}

		if (m_pButton != nullptr && m_pFade == nullptr && m_pButton->IsClickTrigger() == true)
		{//�����L���O�J��
			m_pFade = CFade::Create(CScene::MODE_RANKING);
			pSound->Play(CSound::SOUND_LABEL_SE_BUTTON);
			return;
		}
	}

	m_pBG->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_fAlpha));
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
CResult* CResult::Create(void)
{
	CResult* pResult = nullptr;

	if (pResult == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pResult = new CResult;

		//������
		pResult->Init();

		return pResult;
	}
	else
	{
		return nullptr;
	}
}
