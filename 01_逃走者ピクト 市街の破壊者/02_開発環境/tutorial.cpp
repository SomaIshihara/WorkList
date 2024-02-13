//======================================================
//
//�`���[�g���A���V�[��[tutorial.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "tutorial.h"
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
#include "manager.h"
#include "camera.h"
#include "bg.h"
#include "fade.h"
#include "button.h"
#include "policemanager.h"
#include "sound.h"

//�ÓI�����o�ϐ�
CPlayer* CTutorial::m_pPlayer = nullptr;
CMeshField* CTutorial::m_pMeshField = nullptr;
CScore* CTutorial::m_pScore = nullptr;
CHaveNum* CTutorial::m_pHaveNum[];
CMeshSky* CTutorial::m_pSky = nullptr;
const int CTutorial::TUTORIAL_DELETE_TIME = 20;
const float CTutorial::TUTORIAL_ALPHA_DEF = 0.4f;

//=================================
//�R���X�g���N�^
//=================================
CTutorial::CTutorial()
{
	m_pWarning = nullptr;
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
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH - 24.0f, 32.0f, 0.0f), CManager::VEC3_ZERO, 40.0f, 64.0f);

	CObjectX* pAgit = CObjectX::Create(D3DXVECTOR3(0.0f,0.0f,0.0f), CManager::VEC3_ZERO, CManager::GetAgitModel());
	CPicto::SetAgit(pAgit);

	m_pSky = CMeshSky::Create(CManager::VEC3_ZERO, CManager::VEC3_ZERO, 10000.0f, 8, 8);

	m_pHaveNum[CPicto::TYPE_DESTROYER] = CHaveNum::Create(D3DXVECTOR3(SCREEN_WIDTH - 30.0f, 100.0f, 0.0f), CManager::VEC3_ZERO, 30.0f, 36.0f, 2, CTexture::PRELOAD_HAVEICON_01);
	m_pHaveNum[CPicto::TYPE_BLOCKER] = CHaveNum::Create(D3DXVECTOR3(SCREEN_WIDTH - 30.0f, 136.0f, 0.0f), CManager::VEC3_ZERO, 30.0f, 36.0f, 2, CTexture::PRELOAD_HAVEICON_02);
	m_pHaveNum[CPicto::TYPE_NORMAL] = CHaveNum::Create(D3DXVECTOR3(SCREEN_WIDTH - 30.0f, 172.0f, 0.0f), CManager::VEC3_ZERO, 30.0f, 36.0f, 5, CTexture::PRELOAD_HAVEICON_03);
	m_pHaveNum[CPicto::TYPE_DESTROYER]->AddNum(10);
	m_pHaveNum[CPicto::TYPE_BLOCKER]->AddNum(10);
	m_pHaveNum[CPicto::TYPE_NORMAL]->AddNum(0);

	//�^�C�g��
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 61.5f, 0.0f), CManager::VEC3_ZERO, 311.0f, 111.0f, PRIORITY_UI)->BindTexture(CTexture::PRELOAD_TUTORIAL);

	//�`���[�g���A��
	m_pTutorial[3] = CButton2D::Create(D3DXVECTOR3(146.0f, 91.2f, 0.0f), CManager::VEC3_ZERO, 260.0f, 166.4f, PRIORITY_UI);
	m_pTutorial[3]->BindTexture(CTexture::PRELOAD_TUTORIAL_04);
	m_pTutorial[0] = CButton2D::Create(D3DXVECTOR3(102.8f, 262.4f, 0.0f), CManager::VEC3_ZERO, 165.6f, 160.0f, PRIORITY_UI);
	m_pTutorial[0]->BindTexture(CTexture::PRELOAD_TUTORIAL_01);
	m_pTutorial[1] = CButton2D::Create(D3DXVECTOR3(78.4f, 426.8f, 0.0f), CManager::VEC3_ZERO, 116.8f, 152.8f, PRIORITY_UI);
	m_pTutorial[1]->BindTexture(CTexture::PRELOAD_TUTORIAL_02);
	m_pTutorial[2] = CButton2D::Create(D3DXVECTOR3(135.2f, 596.4f, 0.0f), CManager::VEC3_ZERO, 238.4f, 170.4f, PRIORITY_UI);
	m_pTutorial[2]->BindTexture(CTexture::PRELOAD_TUTORIAL_03);

	for (int cnt = 0; cnt < TUTORIAL_NUM; cnt++)
	{
		m_nTutorialDelCnt[cnt] = CManager::INT_ZERO;
	}

	m_pWarning = CBG::Create(PRIORITY_UI);
	m_pWarning->BindTexture(CTexture::PRELOAD_WARNING_LIFE);
	m_pWarning->SetEnable(false);	//���������\��

	//�}�b�v�f�[�^�ǂݍ��݂Ɣz�u
	CObjectX::LoadData("data\\Fugitive_Picto_MapData_Tutorial.ismd");

	//�|�C���g����
	CPoint::Update();

	//�x�@�}�l�[�W�������E�p�����[�^�ݒ�
	CPoliceManager::Create();
	CPoliceManager::SetKobanParam(300, 2, 1);	//�ݒ�

	return S_OK;
}

//=================================
//�I��
//=================================
void CTutorial::Uninit(void)
{
	CObject::ReleaseAll();

	//�v���C���[�j��
	if (m_pPlayer != nullptr)
	{//�v���C���[�I��
		m_pPlayer->Uninit();
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	m_pPlayer = nullptr;
	m_pSlider = nullptr;
	m_pMeshField = nullptr;
	m_pScore = nullptr;
	m_pSky = nullptr;
	m_pWarning = nullptr;
}

//=================================
//�X�V
//=================================
void CTutorial::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();	//�L�[�{�[�h�擾

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

	//�`���[�g���A����������
	for (int cnt = 0; cnt < TUTORIAL_NUM; cnt++)
	{
		if (m_pTutorial[cnt] != nullptr)
		{
			if (m_pTutorial[cnt]->IsClickPress() == true)
			{//�N���b�N�i�폜�j
				m_nTutorialDelCnt[cnt]++;	//�J�E���g���₷
				m_pTutorial[cnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, TUTORIAL_ALPHA_DEF * (1.0f - (float)m_nTutorialDelCnt[cnt] / TUTORIAL_DELETE_TIME)));
				if (m_nTutorialDelCnt[cnt] >= TUTORIAL_DELETE_TIME)
				{//�J�E���g�߂���
					m_pTutorial[cnt]->Uninit();
					m_pTutorial[cnt] = nullptr;
				}
			}
			else if (m_pTutorial[cnt]->IsHold() == true)
			{//�������i�������j
				m_pTutorial[cnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, TUTORIAL_ALPHA_DEF));
				m_nTutorialDelCnt[cnt] = 0;	//�J�E���g���Z�b�g
			}
			else
			{//�F�߂�
				m_pTutorial[cnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_nTutorialDelCnt[cnt] = 0;	//�J�E���g���Z�b�g
			}
		}
	}

	//���i�̏���
	m_pPlayer->Update();

	//�X�R�A�Z�o
	CulcScore();

	//�C���ς�
	if (m_pFade == nullptr && pKeyboard->GetTrigger(DIK_P) == true)
	{
		m_pFade = CFade::Create(CScene::MODE_GAME);
		CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_BUTTON);
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

//=================================
//�X�R�A�v�Z
//=================================
void CTutorial::CulcScore(void)
{
	//�X�R�A�ރ��Z�b�g
	m_pScore->Set(0);

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
