//======================================================
//
//�����L���O�V�[��[ranking.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "ranking.h"
#include "texture.h"
#include "input.h"
#include "fade.h"
#include "object2D.h"
#include "score.h"
#include "sound.h"

//�ÓI�����o�ϐ�
const int CRanking::MAX_RANK = 5;

//=================================
//�R���X�g���N�^
//=================================
CRanking::CRanking()
{
	m_pFade = nullptr;
	m_pPress = nullptr;
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
	int* pRankScore = new int[MAX_RANK];	//���I�m��
	Load(pRankScore);

	//�������σI�u�W�F
	CObject2D* pObj2D = nullptr;
	CScore* pScore = nullptr;

	//�w�i
	CBG::Create()->BindTexture(CTexture::PRELOAD_27_BG_02);

	//�����L���O����
	pObj2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 108.0f, 0.0f), CManager::VEC3_ZERO, 400.0f, 96.0f, CObject::PRIORITY_05);
	pObj2D->BindTexture(CTexture::PRELOAD_09_RANKSTR);

	//����
	for (int cnt = 0; cnt < MAX_RANK; cnt++)
	{
		//����
		pObj2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 104.0f, 240.0f + (72.0f * cnt), 0.0f), CManager::VEC3_ZERO, 104.0f, 48.0f, CObject::PRIORITY_05);
		pObj2D->BindTexture(CTexture::PRELOAD_10_RANK_01 + cnt);

		//����
		pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 156.0f, 240.0f + (72.0f * cnt), 0.0f), CManager::VEC3_ZERO, 32.0f, 48.0f);
		pScore->BindTexture(CTexture::PRELOAD_03_NUMBER);
		pScore->Set(pRankScore[cnt]);
	}

	//�߂镶��
	m_pPress = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 636.0f, 0.0f), CManager::VEC3_ZERO, 560.0f, 48.0f, CObject::PRIORITY_05);
	m_pPress->BindTexture(CTexture::PRELOAD_15_SCENETITLEKB);

	delete[] pRankScore;	//�X�R�A�j��

	return S_OK;
}

//=================================
//�I��
//=================================
void CRanking::Uninit(void)
{
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

	if (pGamepad != nullptr && pGamepad->IsConnect() == true)
	{//�Q�[���p�b�h�ڑ�
		m_pPress->BindTexture(CTexture::PRELOAD_16_SCENETITLEGP);

		if (pGamepad->GetTrigger(XINPUT_GAMEPAD_A) == true)
		{
			bPush = true;
		}
	}
	else
	{//���ڑ�
		m_pPress->BindTexture(CTexture::PRELOAD_15_SCENETITLEKB);

		if (pKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			bPush = true;
		}
	}

	if(bPush == true && m_pFade == nullptr)
	{
		m_pFade = CFade::Create(CScene::MODE_TITLE);

		//SE�Đ�
		CManager::GetInstance()->GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
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
void CRanking::Set(const int nScore)
{
	int* pRanking = new int[MAX_RANK];	//�ꉞ�ÓIconst���ϐ��Ȃ̂�
													//�����L���O�ǂݍ���
	Load(pRanking);

	//�\�[�g
	if (pRanking[MAX_RANK - 1] < nScore)
	{//�\���ł��钆�ň�ԒႢ���ʂɓ��邩
		pRanking[MAX_RANK - 1] = nScore;	//�Ƃ肠���������

		for (int cnt = MAX_RANK - 1; cnt > 0; cnt--)
		{
			if (pRanking[cnt] > pRanking[cnt - 1])
			{//����ւ�
				int nTemp = pRanking[cnt - 1];
				pRanking[cnt - 1] = pRanking[cnt];
				pRanking[cnt] = nTemp;
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
void CRanking::Load(int* pRanking)
{
	FILE* pFile = nullptr;
	pFile = fopen("data\\ranking.bin", "rb");

	if (pFile != nullptr)
	{//�����L���O�t�@�C��������i�ǂݍ��݁j
		fread(&pRanking[0], sizeof(int), MAX_RANK, pFile);
		fclose(pFile);	//����
	}
	else
	{//�����L���O�t�@�C�����Ȃ��i�V�K�쐬�j
		for (int cnt = 0; cnt < MAX_RANK; cnt++)
		{
			pRanking[cnt] = 0;	//�Ƃ肠����0�Ŗ��߂�
		}
		Save(pRanking);
	}
}

//=================================
//�����L���O��������
//=================================
void CRanking::Save(int* pRanking)
{
	FILE* pFile = nullptr;
	pFile = fopen("data\\ranking.bin", "wb");

	assert(("�������݃��[�h�ŊJ���Ȃ�������I��Ղ��ˁI", pFile != nullptr));

	//�J�����̂Ői�߂�
	fwrite(pRanking, sizeof(int), MAX_RANK, pFile);	//��������

	fclose(pFile);	//����
}
