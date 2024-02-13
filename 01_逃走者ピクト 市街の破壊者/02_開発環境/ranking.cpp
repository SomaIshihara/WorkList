//======================================================
//
//�����L���O�V�[��[ranking.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "precompile.h"
#include "texture.h"
#include "ranking.h"
#include "camera.h"
#include "input.h"
#include "fade.h"
#include "bg.h"
#include "number.h"
#include "symbol.h"
#include "score.h"
#include "sound.h"

//�ÓI�����o�ϐ�
const int CRanking::MAX_RANK = 10;
const int CRanking::RANK_DISP_X = 2;
const int CRanking::RANK_DISP_Y = 5;
const D3DXVECTOR3 CRanking::RANK_START_POS = D3DXVECTOR3(50.0f, 209.0f, 0.0f);
const float CRanking::RANK_X_DISTANCE = 640.0f;
const float CRanking::RANK_Y_DISTANCE = 90.0f;
const float CRanking::X_ONE_WIDTH = 40.0f;
const float CRanking::Y_ONE_HEIGHT = 72.0f;
const float CRanking::X_SCORE_DIST = 20.0f;
const int CRanking::SYMBOL_RANK_NUM = 8;

//=================================
//�R���X�g���N�^
//=================================
CRanking::CRanking()
{
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
	long long* pRanking = new long long[MAX_RANK];	//�ꉞ�ÓIconst���ϐ��Ȃ̂�
	//�J�����ʒu���Z�b�g
	CManager::GetCamera()->ResetPos();

	//�w�i����
	CBG* pBG = CBG::Create();
	pBG->BindTexture(CTexture::PRELOAD_FADE);
	pBG->SetCol(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

	//���o������
	CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 100.0f, 0.0f), CManager::VEC3_ZERO, 311.0f, 111.0f)->BindTexture(CTexture::PRELOAD_TITLE_RANK);

	//�����L���O�ǂݍ���
	Load(pRanking);

	//�����L���O�\���ɕK�v�ȃI�u�W�F�N�g����
	for (int cntX = 0; cntX < RANK_DISP_X; cntX++)
	{
		for (int cntY = 0; cntY < RANK_DISP_Y; cntY++)
		{
			D3DXVECTOR3 posStart = RANK_START_POS + D3DXVECTOR3(RANK_X_DISTANCE * cntX, RANK_Y_DISTANCE * cntY, 0.0f);
			//���ʁi�\�j
			CNumber* pNumber = nullptr;
			pNumber = CNumber::Create(posStart, CManager::VEC3_ZERO, X_ONE_WIDTH, Y_ONE_HEIGHT);
			pNumber->BindTexture(CTexture::PRELOAD_NUMBER);
			pNumber->SetNumber((cntX * RANK_DISP_Y + cntY + 1), 1);

			//���ʁi��j
			pNumber = CNumber::Create(posStart + D3DXVECTOR3(X_ONE_WIDTH * 1,0.0f,0.0f), CManager::VEC3_ZERO, X_ONE_WIDTH, Y_ONE_HEIGHT);
			pNumber->BindTexture(CTexture::PRELOAD_NUMBER);
			pNumber->SetNumber((cntX * RANK_DISP_Y + cntY + 1), 0);

			//�L���i�ʁj
			CSymbol* pSymbol = nullptr;
			pSymbol = CSymbol::Create(posStart + D3DXVECTOR3(X_ONE_WIDTH * 2, 0.0f, 0.0f), CManager::VEC3_ZERO, X_ONE_WIDTH, Y_ONE_HEIGHT);
			pSymbol->BindTexture(CTexture::PRELOAD_SYMBOL);
			pSymbol->SetSymbol(SYMBOL_RANK_NUM);

			//�X�R�A
			CScore* pScore = nullptr;
			pScore = CScore::Create(posStart + D3DXVECTOR3(X_ONE_WIDTH * 2 + X_SCORE_DIST + X_ONE_WIDTH * 11, 0.0f, 0.0f),
				CManager::VEC3_ZERO, X_ONE_WIDTH, Y_ONE_HEIGHT);
			pScore->Set(pRanking[cntX * RANK_DISP_Y + cntY]);
		}
	}

	delete[] pRanking;	//�j��

	return S_OK;
}

//=================================
//�I��
//=================================
void CRanking::Uninit(void)
{
	CObject::ReleaseAll();
}

//=================================
//�X�V
//=================================
void CRanking::Update(void)
{
	CSound* pSound = CManager::GetSound();
	CInputMouse* pMouse = CManager::GetInputMouse();

	if (m_pFade == nullptr && pMouse->GetTrigger(MOUSE_CLICK_LEFT) == true)
	{//�^�C�g���ɑJ��
		m_pFade = CFade::Create(CScene::MODE_TITLE);
		pSound->Play(CSound::SOUND_LABEL_SE_BUTTON);
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
void CRanking::Set(const long long nScore)
{
	long long* pRanking = new long long[MAX_RANK];	//�ꉞ�ÓIconst���ϐ��Ȃ̂�
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
				long long nTemp = pRanking[cnt - 1];
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
void CRanking::Load(long long* pRanking)
{
	FILE* pFile = nullptr;
	pFile = fopen("data\\ranking.bin", "rb");

	if (pFile != nullptr)
	{//�����L���O�t�@�C��������i�ǂݍ��݁j
		fread(&pRanking[0], sizeof(long long), MAX_RANK, pFile);
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
void CRanking::Save(long long* pRanking)
{
	FILE* pFile = nullptr;
	pFile = fopen("data\\ranking.bin", "wb");

	assert(("�������݃��[�h�ŊJ���Ȃ�������I��Ղ��ˁI", pFile != nullptr));

	//�J�����̂Ői�߂�
	fwrite(pRanking, sizeof(long long), MAX_RANK, pFile);	//��������

	fclose(pFile);	//����
}
