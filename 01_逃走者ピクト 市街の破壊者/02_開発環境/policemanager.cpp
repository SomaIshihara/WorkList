//======================================================
//
//�x�@�}�l�[�W������[policemanager.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "policemanager.h"
#include "manager.h"
#include "picto.h"
#include "building.h"
#include "koban.h"
#include "score.h"
#include "game.h"
#include "picto.h"

//�}�N��
#define KOBAN_BUILDING_SEARCH_NUM	(5)		//�����T���񐔁i������߂���ƕ����Ȃ��j
#define KOBAN_NOBUILDING_TIME_PERCE	(0.5f)	//������������Ȃ������ꍇ�̒T�����Ԋ���

//�O���錾
int CPoliceManager::m_disPatchCT[] = {};
std::vector<int> CPoliceManager::m_AttackList;
int CPoliceManager::m_nCounterSpawn = CManager::INT_ZERO;
int CPoliceManager::m_nSpawnSpan = CManager::INT_ZERO;
int CPoliceManager::m_nPoliceMax = CManager::INT_ZERO;
int CPoliceManager::m_waitingPolice = CManager::INT_ZERO;
int CPoliceManager::m_nPatrollNum = CManager::INT_ZERO;

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CPoliceManager::CPoliceManager(int nPriority)
{
	
}

//=================================
//�f�X�g���N�^
//=================================
CPoliceManager::~CPoliceManager()
{
}

//=================================
//������
//=================================
HRESULT CPoliceManager::Init(void)
{
	m_waitingPolice = CManager::INT_ZERO;
	m_nCounterSpawn = CManager::INT_ZERO;
	m_nSpawnSpan = CManager::INT_ZERO;
	m_nPoliceMax = CManager::INT_ZERO;
	m_nLv = CManager::INT_ZERO;

	//�ł���
	return S_OK;
}

//=================================
//�I��
//=================================
void CPoliceManager::Uninit(void)
{
	//�Ǘ��I�u�W�F�N�g�j��
	Release();
}

//=================================
//�X�V
//=================================
void CPoliceManager::Update(void)
{
	int nNumAll = CKoban::GetNumAll();	//��Ԑ��擾
	CKoban** ppKoban = CKoban::GetKoban();

	//����
	CScene::MODE mode = CManager::GetMode();

	if (mode == CScene::MODE_GAME)
	{//�Q�[���̓X�R�A�ɂ��ϓ�
		long long nScore = CGame::GetScoreObj()->GetScore();
		while (HAVE_VALUE(m_nLv) <= nScore) m_nLv++;	//�グ���邾���グ��
	}
	else if (mode == CScene::MODE_TUTORIAL)
	{//�`���[�g���A���͌Œ�1���x
		m_nLv = 1;
	}

	//�o��
	if (CPictoPolice::GetNumAll() + m_waitingPolice < m_nPoliceMax + m_nLv)
	{//�l��s��
		m_nCounterSpawn++;	//�����J�E���^���₷
		if (m_nCounterSpawn >= m_nSpawnSpan)
		{//�ق�
			m_waitingPolice++;
		}
	}

	//������CT���炷
	for (int cnt = 0; cnt < MAX_OBJ; cnt++)
	{
		m_disPatchCT[cnt]--;
	}

	if (m_waitingPolice > 0)
	{//�ҋ@���̌x�@��1�l�ȏア��
		if (CPictoPolice::GetNumAll() < m_nPatrollNum)
		{//�p�g���[���p�ɕ�����
			int nSpawnKoban = rand() % nNumAll;	//�K���Ɍ��߂�
			int nAssignBuilding;

			for (int cnt = 0; cnt < KOBAN_BUILDING_SEARCH_NUM; cnt++)
			{
				nAssignBuilding = rand() % CBuilding::GetNumAll();
				if (CBuilding::GetBuilding(nAssignBuilding)->GetEndurance() > 0)
				{//�ϋv�l���c���Ă���
					CPictoPolice* pPolice = CPictoPolice::Create(ppKoban[nSpawnKoban]->GetPos(), m_nLv);	//�K���Ɍ��߂���Ԃ��畦����
					pPolice->SetTargetObj(CBuilding::GetBuilding(nAssignBuilding));					//�K���Ɍ��߂������ɔz��
					m_nCounterSpawn = 0;	//�J�E���^���Z�b�g
					m_waitingPolice--;		//�ҋ@���x�@�����炷
					break;
				}
			}

			//���〈����Ȃ���ł���->�������Ԃ̉�������������܂��T��
			m_nCounterSpawn = (int)((float)m_nSpawnSpan * KOBAN_NOBUILDING_TIME_PERCE);	//�J�E���^���Z�b�g
		}

		//�����_���[�W�񍐃��X�g�ɉ����Ēǉ��o��
		for (int cntList = 0; cntList < m_AttackList.size(); cntList++)
		{
			if (m_disPatchCT[m_AttackList[cntList]] <= 0)
			{//CT�I�����Ă���
				CBuilding* pBuilding = CBuilding::GetBuilding(m_AttackList[cntList]);

				//��Q���󂯂Ă��錚���ɋ߂���Ԃ�T��
				int nNearKoban = -1;
				float fLengthNear = -1.0f;
				for (int cntKoban = 0; cntKoban < nNumAll; cntKoban++)
				{
					float fLength = D3DXVec3Length(&(ppKoban[cntKoban]->GetPos() - CBuilding::GetBuilding(m_AttackList[cntList])->GetPos()));
					if (nNearKoban == -1 || fLengthNear > fLength)
					{
						nNearKoban = cntKoban;		//��ԋ߂���Ԕԍ��Ƃ���
						fLengthNear = fLength;	//�߂��l������
					}
				}

				//�U�����Ă���Ŋ��̃s�N�g���擾
				int nNearPicto = -1;
				float fLenNearPicto = -1.0f;
				for (int cnt = 0; cnt < MAX_OBJ; cnt++)
				{
					CPictoDestroyer* pPicto = CPictoDestroyer::GetPicto(cnt);
					if (pPicto != nullptr)
					{
						float fLenPicto = D3DXVec3Length(&(pPicto->GetPos() - pBuilding->GetPos()));
						if (nNearPicto == -1 || fLenNearPicto > fLenPicto)
						{
							nNearPicto = cnt;			//��ԋ߂��s�N�g�Ƃ���
							fLenNearPicto = fLenPicto;	//���������
						}
					}
				}

				CPictoPolice* pPolice = CPictoPolice::Create(ppKoban[nNearKoban]->GetPos(), m_nLv);	//�߂���Ԃ��畦����
				pPolice->SetTargetObj(CPictoDestroyer::GetPicto(nNearPicto));					//�����̋߂��ōU�����Ă���s�N�g���^�[�Q�b�g�ɂ���
				m_waitingPolice--;																//�ҋ@���x�@�����炷
				m_disPatchCT[m_AttackList[cntList]] = m_nSpawnSpan;								//�ق��Ԋu�Ɠ����Ԋu��CT��ݒ�
			}
		}
	}

	//�񍐃��X�g�����Z�b�g
	m_AttackList.clear();
}

//=================================
//�`��
//=================================
void CPoliceManager::Draw(void)
{
	
}

//=================================
//��������
//=================================
CPoliceManager* CPoliceManager::Create(void)
{
	CPoliceManager* pObjPoliceManager = NULL;

	if (pObjPoliceManager == NULL)
	{
		//�Ǘ��I�u�W�F�N�g����
		pObjPoliceManager = new CPoliceManager;

		//�Ǘ��I�u�W�F�N�g������
		pObjPoliceManager->Init();

		return pObjPoliceManager;
	}
	else
	{
		return NULL;
	}
}

//=================================
//��Ԑݒ�
//=================================
void CPoliceManager::SetKobanParam(const int nSpawnSpan, const int nPoliceMax, const int nPatrollNum)
{//���
	m_nSpawnSpan = nSpawnSpan;
	m_nPoliceMax = nPoliceMax;
	m_nPatrollNum = nPatrollNum;
}
