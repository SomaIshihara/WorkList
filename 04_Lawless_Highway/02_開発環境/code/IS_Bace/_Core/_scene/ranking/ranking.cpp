//======================================================
//
//�����L���O�V�[��[ranking.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "ranking.h"
#include "../../../../main.h"
#include "../../manager/manager.h"
#include "../../sound/sound.h"
#include "../../../_Expansion/timer/timer.h"
#include "../../input/input.h"
#include "../../../_Expansion/fade/fade.h"
#include "../../texture/texture.h"
#include "../../utility/Utility.h"
#include "../../../../Addition/meshroad/meshroad.h"
#include "../../../_Expansion/meshsky/meshsky.h"
#include "../../file(legacy)/file.h"
#include "../../camera/camera.h"

//�ÓI�����o�ϐ�
const int CRanking::MAX_RANK = 5;

//�������O���
namespace
{
	D3DXVECTOR3 pos1stRank = D3DXVECTOR3(328.0f, 180.0f, 0.0f);
	D3DXVECTOR3 pos1stTime = pos1stRank + D3DXVECTOR3(164.0f, 0.0f, 0.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(100.0f, 84.0f, 0.0f);
}

//=================================
//�R���X�g���N�^
//=================================
CRanking::CRanking()
{
	m_pFade = nullptr;
}

//=================================
//�f�X�g���N�^
//=================================
CRanking::~CRanking()
{
}

//=================================
//������
//=================================
HRESULT CRanking::Init(void)
{
	//�X�R�A�l
	RankTimeMSmS* pRankScore = new RankTimeMSmS[MAX_RANK];	//���I�m��
	Load(pRankScore);

	//�����L���O����
	CObject2D* pRanking = CObject2D::Create(D3DXVECTOR3(328.0f, 70.0f, 0.0f), IS_Utility::VEC3_ZERO, 360.0f, 96.0f, CObject::PRIORITY_05);
	pRanking->BindTexture(CTexture::PRELOAD::PRELOAD_15_RANKING_TEXT);

	//���ʂƎ��Ԕz�u
	for (int cnt = 0; cnt < MAX_RANK; cnt++)
	{
		//����
		CObject2D* pRank = CObject2D::Create(pos1stRank + (move * (float)cnt), IS_Utility::VEC3_ZERO, 64.0f, 64.0f,CObject::PRIORITY_05);
		pRank->BindTexture(CTexture::PRELOAD::PRELOAD_16_1ST + cnt);

		//����
		CTimerMSmS* pTimer = CTimerMSmS::Create(pos1stTime + (move * (float)cnt), IS_Utility::VEC3_ZERO, 32.0f, 64.0f);
		pTimer->BindTexture(CTexture::PRELOAD::PRELOAD_04_TIMER_NUMBER);
		pTimer->BindSymbolTexture(CTexture::PRELOAD::PRELOAD_05_TIMER_SYMBOL);
		pTimer->Set(pRankScore[cnt].nTime, pRankScore[cnt].nCounter, CTimer::COUNT::COUNT_DOWN);
	}

	//�}�b�v�z�u
	//���H
	LoadRoadScriptFile("data//road_data_main.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_sub.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_TGConnect.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_dummy.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);
	LoadRoadScriptFile("data//road_data_tutorial.txt")->BindTexture(CTexture::PRELOAD::PRELOAD_21_ROAD);

	//�n��
	CMeshField::Create(D3DXVECTOR3(0.0f, -381.5f, 6000.0f), IS_Utility::VEC3_ZERO, 2048.0f, 2048.0f, 24, 24)
		->BindTexture(CTexture::PRELOAD_34_FIELD_LEAF);

	//�J����
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	pCamera->ResetPos();
	pCamera->SetPosR(D3DXVECTOR3(6000.0f, 100.0f, 5000.0f));
	pCamera->SetRot(D3DXVECTOR3(-0.05f * D3DX_PI, 0.3f * D3DX_PI, 0.0f));
	pCamera->SetLength(2000.0f);

	//�X�^�[�g����
	CObject2D* pStart = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.9f, 0.0f), IS_Utility::VEC3_ZERO, 756.0f, 99.0f, CObject::PRIORITY_05);
	pStart->BindTexture(CTexture::PRELOAD::PRELOAD_01_PUSHANYBUTTON);

	CMeshSky::Create(D3DXVECTOR3(0.0f, 0.0f, 4000.0f), IS_Utility::VEC3_ZERO, 14000.0f, 12, 12);

	//����
	delete[] pRankScore;	//�X�R�A�j��

	//BGM�炷
	CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_BGM_RANKING);

	return S_OK;
}

//=================================
//�I��
//=================================
void CRanking::Uninit(void)
{
	//����~
	CManager::GetInstance()->GetSound()->Stop();

	//�I�u�W�F�S�j��
	for (int cnt = 0; cnt < CObject::PRIORITY_FADE; cnt++)
	{
		CObject::ReleaseAll(cnt);
	}
}

//=================================
//�X�V
//=================================
void CRanking::Update(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamePad* pGamepad = CManager::GetInstance()->GetInputGamePad();
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

	if(bPush == true && m_pFade == nullptr)
	{
		m_pFade = CFade::Create(CScene::MODE::MODE_TITLE);
	}
}

//=================================
//�`��
//=================================
void CRanking::Draw(void)
{
}

//=================================
//�����L���O�ݒ�
//=================================
void CRanking::Set(const RankTimeMSmS nTimer)
{
	//�����L���O�ǂݍ���
	RankTimeMSmS* pRanking = new RankTimeMSmS[MAX_RANK];
	Load(pRanking);

	//�\�[�g
	if (pRanking[MAX_RANK - 1].nTime > nTimer.nTime || 
		(pRanking[MAX_RANK - 1].nTime == nTimer.nTime && pRanking[MAX_RANK - 1].nCounter > nTimer.nCounter))
	{
		pRanking[MAX_RANK - 1] = nTimer;	//�Ƃ肠���������

		//�\�[�g
		for (int cnt = MAX_RANK - 1; cnt > 0; cnt--)
		{
			if (pRanking[cnt].nTime < pRanking[cnt - 1].nTime ||
				(pRanking[cnt].nTime == pRanking[cnt - 1].nTime && pRanking[cnt].nCounter < pRanking[cnt - 1].nCounter))
			{//����ւ�
				RankTimeMSmS temp = pRanking[cnt - 1];
				pRanking[cnt - 1] = pRanking[cnt];
				pRanking[cnt] = temp;
			}
		}
	}

	//�����L���O��������
	Save(pRanking);

	delete[] pRanking;	//�j��
}

//=================================
//�����L���O�ǂݍ���
//=================================
void CRanking::Load(RankTimeMSmS* pRanking)
{
	FILE* pFile = nullptr;
	pFile = fopen("data//ranking.bin", "rb");

	if (pFile != nullptr)
	{//�����L���O�t�@�C��������i�ǂݍ��݁j
		fread(&pRanking[0], sizeof(RankTimeMSmS), MAX_RANK, pFile);
		fclose(pFile);	//����
	}
	else
	{//�����L���O�t�@�C�����Ȃ��i�V�K�쐬�j
		for (int cnt = 0; cnt < MAX_RANK; cnt++)
		{
			pRanking[cnt].nTime = 5940;	//�Ƃ肠����0�Ŗ��߂�
			pRanking[cnt].nCounter = 59;	//�Ƃ肠����0�Ŗ��߂�
		}
		Save(pRanking);
	}
}

//=================================
//�����L���O��������
//=================================
void CRanking::Save(RankTimeMSmS* pRanking)
{
	FILE* pFile = nullptr;
	pFile = fopen("data//ranking.bin", "wb");

	assert(("�������݃��[�h�ŊJ���Ȃ�������I��Ղ��ˁI", pFile != nullptr));

	//�J�����̂Ői�߂�
	fwrite(pRanking, sizeof(RankTimeMSmS), MAX_RANK, pFile);	//��������

	fclose(pFile);	//����
}
