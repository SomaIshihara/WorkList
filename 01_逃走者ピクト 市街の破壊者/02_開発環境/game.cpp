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
#include "player.h"
#include "meshField.h"
#include "slider.h"
#include "building.h"
#include "score.h"
#include "timer.h"
#include "objectX.h"
#include "picto.h"
#include "koban.h"
#include "meshsky.h"
#include "point.h"
#include "input.h"
#include "havenum.h"
#include "level.h"
#include "manager.h"
#include "camera.h"
#include "bg.h"
#include "countdown.h"
#include "normanager.h"
#include "policemanager.h"
#include "sound.h"

//�ÓI�����o�ϐ�
CPlayer* CGame::m_pPlayer = nullptr;
CMeshField* CGame::m_pMeshField = nullptr;
CTimer* CGame::m_pTimer = nullptr;
CScore* CGame::m_pScore = nullptr;
CHaveNum* CGame::m_pHaveNum[];
CLevel* CGame::m_pLevel[];
CMeshSky* CGame::m_pSky = nullptr;
int CGame::m_nATKBuilding = CManager::INT_ZERO;
int CGame::m_nDestBuilding = CManager::INT_ZERO;
const int CGame::CDSTART_TIME = MAX_FPS;

//=================================
//�R���X�g���N�^
//=================================
CGame::CGame()
{
	m_pPause = nullptr;
	m_pWarning = nullptr;
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
	m_pSlider = CSlider::Create(D3DXVECTOR3(100.0f, SCREEN_HEIGHT - 20.0f, 0.0f), 40.0f, 40.0f, 3);
	m_pPlayer = new CPlayer;

	//�v���C���[������
	if (FAILED(m_pPlayer->Init()))
	{
		return E_FAIL;
	}

	//�J�����ʒu���Z�b�g
	CManager::GetCamera()->ResetPos();

	//���I�u�W�F����
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(-1280.0f, 0.0f, 1280.0f), CManager::VEC3_ZERO, 64.0f, 64.0f, 40, 40);

	//�I�u�W�F�N�g����+������
	m_pTimer = CTimer::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 24.0f, 32.0f, 0.0f), CManager::VEC3_ZERO, 48.0f, 72.0f);
	m_pTimer->Set(120, CTimer::COUNT_DOWN);
	m_pTimer->Stop();

	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 24.0f, 32.0f, 0.0f), CManager::VEC3_ZERO, 40.0f, 64.0f);

	CObjectX* pAgit = CObjectX::Create(D3DXVECTOR3(600.0f,0.0f,0.0f), CManager::VEC3_ZERO, CManager::GetAgitModel());
	CPicto::SetAgit(pAgit);

	m_pSky = CMeshSky::Create(CManager::VEC3_ZERO, CManager::VEC3_ZERO, 10000.0f, 8, 8);

	m_pLevel[CPicto::TYPE_DESTROYER] = CLevel::Create(D3DXVECTOR3(SCREEN_WIDTH - 160.0f, 100.0f, 0.0f), CManager::VEC3_ZERO, 30.0f, 36.0f, 2, CTexture::PRELOAD_LV);
	m_pLevel[CPicto::TYPE_BLOCKER] = CLevel::Create(D3DXVECTOR3(SCREEN_WIDTH - 160.0f, 136.0f, 0.0f), CManager::VEC3_ZERO, 30.0f, 36.0f, 2, CTexture::PRELOAD_LV);

	m_pHaveNum[CPicto::TYPE_DESTROYER] = CHaveNum::Create(D3DXVECTOR3(SCREEN_WIDTH - 30.0f, 100.0f, 0.0f), CManager::VEC3_ZERO, 30.0f, 36.0f, 2, CTexture::PRELOAD_HAVEICON_01);
	m_pHaveNum[CPicto::TYPE_BLOCKER] = CHaveNum::Create(D3DXVECTOR3(SCREEN_WIDTH - 30.0f, 136.0f, 0.0f), CManager::VEC3_ZERO, 30.0f, 36.0f, 2, CTexture::PRELOAD_HAVEICON_02);
	m_pHaveNum[CPicto::TYPE_NORMAL] = CHaveNum::Create(D3DXVECTOR3(SCREEN_WIDTH - 30.0f, 172.0f, 0.0f), CManager::VEC3_ZERO, 30.0f, 36.0f, 5, CTexture::PRELOAD_HAVEICON_03);
	m_pHaveNum[CPicto::TYPE_DESTROYER]->AddNum(2);
	m_pHaveNum[CPicto::TYPE_BLOCKER]->AddNum(2);
	m_pHaveNum[CPicto::TYPE_NORMAL]->AddNum(1000);

	m_pWarning = CBG::Create(PRIORITY_UI);
	m_pWarning->BindTexture(CTexture::PRELOAD_WARNING_LIFE);
	m_pWarning->SetEnable(false);	//���������\��

	m_pCountDown = CCountDown::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), 150.0f, 180.0f, 3);

	//�}�b�v�f�[�^�ǂݍ��݂Ɣz�u
	CObjectX::LoadData("data\\Fugitive_Picto_MapData_v120.ismd");

	//�|�C���g����
	CPoint::Update();

	//�x�@�}�l�[�W�������E�p�����[�^�ݒ�
	CPoliceManager::Create();
	//CPoliceManager::SetKobanParam(300, 1, 1);	//���ݒ�
	CPoliceManager::SetKobanParam(300, 15, 7);	//���ݒ�

	//��ʐl�}�l�[�W��
	CNorManager* pNorManager = CNorManager::Create();
	pNorManager->SetNum(15);
	pNorManager->SetTime(180);

	//���x��������
	CPictoDestroyer::ResetLevelExp();
	CPictoBlocker::ResetLevelExp();

	//BGM����
	CManager::GetSound()->Play(CSound::SOUND_LABEL_BGM);

	return S_OK;
}

//=================================
//�I��
//=================================
void CGame::Uninit(void)
{
	CObject::ReleaseAll();
	CManager::GetSound()->Stop();

	//�v���C���[�j��
	if (m_pPlayer != nullptr)
	{//�v���C���[�I��
		m_pPlayer->Uninit();
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}
	//���U���g�j��
	if (m_pResult != nullptr)
	{//�v���C���[�I��
		m_pResult->Uninit();
		delete m_pResult;
		m_pResult = nullptr;
	}
	//�|�[�Y�j���i�ꉞ�j
	if (m_pPause != nullptr)
	{//�v���C���[�I��
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = nullptr;
	}

	//�J�E���g�_�E���j���i�ꉞ�j
	if (m_pCountDown != nullptr)
	{
		m_pCountDown->Uninit();
		delete m_pCountDown;
		m_pCountDown = nullptr;
	}

	m_pPlayer = nullptr;
	m_pSlider = nullptr;
	m_pMeshField = nullptr;
	m_pTimer = nullptr;
	m_pScore = nullptr;
	m_pSky = nullptr;
	m_pWarning = nullptr;
}

//=================================
//�X�V
//=================================
void CGame::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();	//�L�[�{�[�h�擾

	//�J�E���g�_�E���̍X�V
	if (m_pCountDown != nullptr)
	{
		m_pCountDown->Update();
		//�J�E���g�_�E���O
		if (m_counterCDStart == CDSTART_TIME)
		{
			m_pCountDown->Start();	//�J�E���g�_�E���J�n
			m_counterCDStart++;
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_COUNTDOWN);
		}
		else if (m_counterCDStart < CDSTART_TIME)
		{
			m_counterCDStart++;		//�J�n���Ԃ܂ŃJ�E���g
		}

		//�J�E���g�_�E����
		if (m_pCountDown->GetCount() <= -1)
		{
			m_pCountDown->Uninit();
			delete m_pCountDown;
			m_pCountDown = nullptr;
			m_pTimer->Start();
		}
	}
	else
	{//�J�E���g�_�E���I�u�W�F�N�g��������
		if (pKeyboard->GetTrigger(DIK_P) == true)
		{//�|�[�Y�؂�ւ�
			CManager::SetPause((CManager::GetPause() == true ? false : true));
			CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_BUTTON);
		}

		if (m_pResult != nullptr)
		{//���U���g
			m_pResult->Update();
		}
		else
		{//�Q�[��
			if (CManager::GetPause() == true)
			{//�|�[�Y���Ă�
				if (m_pPause == nullptr)
				{//�|�[�Y���ʂ��
					m_pPause = new CPause;		//�|�[�Y����
					m_pPause->Init();			//�|�[�Y������
				}

				//�|�[�Y���̏���
				m_pPause->Update();
			}
			else
			{//�|�[�Y���ĂȂ�
				if (m_pPause != nullptr)
				{//�Ȃ񂩓����Ă�
					m_pPause->Uninit();	//�I��
					delete m_pPause;	//�j��
					m_pPause = nullptr;	//�ʂ�ۓ����
				}

				//�̗�
				bool bWarning = false;
				for (int cnt = 0; cnt < MAX_OBJ; cnt++)
				{//�f�X�g���C���[
					CPictoDestroyer* pPicto = CPictoDestroyer::GetPicto(cnt);
					if (pPicto != nullptr)
					{
						CPicto::TYPE type = pPicto->GetType();
						if (pPicto->GetLife() <= HAVE_LIFE(pPicto->GetLv()) * CPictoTaxi::RESCUE_LIFE)
						{//�댯
							bWarning = true;
							break;
						}
					}
				}
				for (int cnt = 0; cnt < MAX_OBJ; cnt++)
				{//�u���b�J�[
					CPictoBlocker* pPicto = CPictoBlocker::GetPicto(cnt);
					if (pPicto != nullptr)
					{
						CPicto::TYPE type = pPicto->GetType();
						if (pPicto->GetLife() <= HAVE_LIFE(pPicto->GetLv()) * CPictoTaxi::RESCUE_LIFE)
						{//�댯
							bWarning = true;
							break;
						}
					}
				}
				//�ύX
				m_pWarning->SetEnable(bWarning);

				//���i�̏���
				m_pPlayer->Update();

				//�X�R�A�Z�o
				CulcScore();

				//���ԊǗ�
				if (m_pTimer->GetTime() <= 0)
				{//���Ԑ؂�
					if (m_pResult == nullptr)
					{
						CRanking::Set(m_pScore->GetScore());
						m_pResult = CResult::Create();
					}
				}
			}
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

//=================================
//�X�R�A�v�Z
//=================================
void CGame::CulcScore(void)
{
	//�X�R�A�ރ��Z�b�g
	m_pScore->Set(0);
	m_nATKBuilding = 0;
	m_nDestBuilding = 0;

	//�����I�u�W�F�N�g�S����
	for (int cnt = 0; cnt < MAX_OBJ; cnt++)
	{
		CBuilding* pBuilding = CBuilding::GetBuilding(cnt);	//�����I�u�W�F�N�g�擾
		if (pBuilding != nullptr)
		{//�Ȃ񂩂���
			CXModel* pModel = CXModel::GetTop();
			int nModelNum = 0;
			while (pModel != nullptr && pModel != pBuilding->GetModel())
			{
				pModel = pModel->GetNext();
				nModelNum++;
			}

			//�X�R�A�Z�o
			float fParcent;
			long long nScore;

			if (pBuilding->GetUnique() == false)
			{//�v�Z�Z�o
				int nEndurance = pBuilding->GetEndurance();
				int nMaxEndurance = HAVE_LIFE(pBuilding->GetLv());

				if (nEndurance < nMaxEndurance)
				{//�����Ă���
					m_nATKBuilding++;	//�U������

					if (nEndurance <= 0)
					{//�S��
						m_nDestBuilding++;
					}

					//��Q�z�v�Z
					fParcent = ((float)nEndurance / nMaxEndurance);
					nScore = (1.0f - fParcent) * HAVE_VALUE(pBuilding->GetLv());
					m_pScore->Add(nScore);
				}
			}
			else
			{//��
				int nMaxEndurance = pBuilding->GetSigEndurance() * pow(10, pBuilding->GetPowEndurance());
				int nEndurance = pBuilding->GetEndurance();

				if (nEndurance < nMaxEndurance)
				{//�����Ă���
					m_nATKBuilding++;	//�U������

					if (nEndurance <= 0)
					{//�S��
						m_nDestBuilding++;
					}

					//��Q�z�v�Z
					fParcent = ((float)nEndurance / nMaxEndurance);
					long long nValue = pBuilding->GetSigValue() * pow(10, pBuilding->GetPowValue());
					nScore = (1.0f - fParcent) * nValue;
					m_pScore->Add(nScore);
				}
			}
		}
		else
		{//�����Ȃ�
			break;
		}
	}
}
