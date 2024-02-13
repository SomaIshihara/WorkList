//======================================================
//
//���[�V��������[motion..cpp]
//Author:�Ό��D�n
//
//======================================================
#include "motion.h"
#include "model.h"
#include "manager.h"

//========================
//�R���X�g���N�^
//========================
CMotion::CMotion()
{
	for (int cntInfo = 0; cntInfo < INFO_NUM; cntInfo++)
	{
		for (int cntKeyInfo = 0; cntKeyInfo < KEYINFO_NUM; cntKeyInfo++)
		{
			m_aInfo[cntInfo].m_aKeyInfo[cntKeyInfo].m_pKey = nullptr;
			m_aInfo[cntInfo].m_aKeyInfo[cntKeyInfo].m_nFrame = 0;
		}
		m_aInfo[cntInfo].m_bLoop = false;
		m_aInfo[cntInfo].m_nNumKey = CManager::INT_ZERO;
	}
}

//========================
//�f�X�g���N�^
//========================
CMotion::~CMotion()
{
}

//========================
//����������
//========================
HRESULT CMotion::Init(void)
{
	return S_OK;
}

//========================
//�I������
//========================
void CMotion::Uninit(void)
{
	for (int cntInfo = 0; cntInfo < INFO_NUM; cntInfo++)
	{
		for (int cntKeyInfo = 0; cntKeyInfo < KEYINFO_NUM; cntKeyInfo++)
		{
			if (m_aInfo[cntInfo].m_aKeyInfo[cntKeyInfo].m_pKey != nullptr)
			{
				delete m_aInfo[cntInfo].m_aKeyInfo[cntKeyInfo].m_pKey;
				m_aInfo[cntInfo].m_aKeyInfo[cntKeyInfo].m_pKey = nullptr;
			}
		}
	}
}

//========================
//���[�V�����ݒ菈��
//========================
void CMotion::Set(int nType)
{
	//���[�V�����ݒ�
	m_nType = nType;

	//�����ݒ�
	m_bLoop = m_aInfo[m_nType].m_bLoop;
	m_nNumKey = m_aInfo[m_nType].m_nNumKey;
	m_nKey = CManager::INT_ZERO;
	m_nCounter = CManager::INT_ZERO;
	m_bFinish = false;
}

//========================
//�X�V����
//========================
void CMotion::Update(void)
{
	//���̃L�[�Ǝ��̃L�[�����Ă���
	int nNowKey = m_nKey;
	int nNextKey = (m_nKey + 1) % m_nNumKey;

	if (m_bFinish == false)
	{
		for (int CntModel = 0; CntModel < m_nNumModel; CntModel++)
		{
			//�I�t�Z�b�g�����Ă���
			D3DXVECTOR3 posMotioned = m_ppModel[CntModel]->GetPosOffset();
			D3DXVECTOR3 rotMotioned = m_ppModel[CntModel]->GetRotOffset();

			//�����Z�o
			float posDiffX = m_aInfo[m_nType].m_aKeyInfo[nNextKey].m_pKey[CntModel].m_fPosX -
				m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fPosX;
			float posDiffY = m_aInfo[m_nType].m_aKeyInfo[nNextKey].m_pKey[CntModel].m_fPosY -
				m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fPosY;
			float posDiffZ = m_aInfo[m_nType].m_aKeyInfo[nNextKey].m_pKey[CntModel].m_fPosZ -
				m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fPosZ;
			float rotDiffX = m_aInfo[m_nType].m_aKeyInfo[nNextKey].m_pKey[CntModel].m_fRotX -
				m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fRotX;
			float rotDiffY = m_aInfo[m_nType].m_aKeyInfo[nNextKey].m_pKey[CntModel].m_fRotY -
				m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fRotY;
			float rotDiffZ = m_aInfo[m_nType].m_aKeyInfo[nNextKey].m_pKey[CntModel].m_fRotZ -
				m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fRotZ;

			//�ʒu�����Z�o
			float posDemandX = m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fPosX +
				posDiffX * ((float)m_nCounter / m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_nFrame);
			float posDemandY = m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fPosY +
				posDiffY * ((float)m_nCounter / m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_nFrame);
			float posDemandZ = m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fPosZ +
				posDiffZ * ((float)m_nCounter / m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_nFrame);
			float rotDemandX = m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fRotX +
				rotDiffX * ((float)m_nCounter / m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_nFrame);
			float rotDemandY = m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fRotY +
				rotDiffY * ((float)m_nCounter / m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_nFrame);
			float rotDemandZ = m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fRotZ +
				rotDiffZ * ((float)m_nCounter / m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_nFrame);

			//�p�[�c�̈ʒu�����ݒ�
			posMotioned += D3DXVECTOR3(posDemandX, posDemandY, posDemandZ);
			rotMotioned += D3DXVECTOR3(rotDemandX, rotDemandY, rotDemandZ);
			m_ppModel[CntModel]->SetPosMotioned(posMotioned);
			m_ppModel[CntModel]->SetRotMotioned(rotMotioned);
		}
		m_nCounter++;

		//�Đ��t���[����̋���
		if (m_nCounter == m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_nFrame)
		{//�Đ��t���[�����ɒB������
		 //�J�E���^�[�����Z�b�g���ăL�[������₷
			m_nCounter = 0;
			m_nKey++;

			//�L�[�̍ő吔�ɒB�����烋�[�v���邩�ۂ��ɉ����čĐݒ肷��
			if (m_bLoop == true)
			{//���[�v����
				if (m_nKey == m_nNumKey)
				{
					m_nKey = 0;
				}
			}
			else
			{//���[�v�Ȃ�
				if (m_nKey == m_nNumKey - 1)
				{
					m_bFinish = true;
				}
			}
		}
	}
	else
	{//�Ō�̃��[�V�������g�p
		for (int CntModel = 0; CntModel < m_nNumModel; CntModel++)
		{
			nNextKey = m_nNumKey - 1;
			nNowKey = nNextKey - 1;

			//�I�t�Z�b�g�����Ă���
			D3DXVECTOR3 posMotioned = m_ppModel[CntModel]->GetPosOffset();
			D3DXVECTOR3 rotMotioned = m_ppModel[CntModel]->GetRotOffset();

			//�����Z�o
			float posDiffX = m_aInfo[m_nType].m_aKeyInfo[nNextKey].m_pKey[CntModel].m_fPosX -
				m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fPosX;
			float posDiffY = m_aInfo[m_nType].m_aKeyInfo[nNextKey].m_pKey[CntModel].m_fPosY -
				m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fPosY;
			float posDiffZ = m_aInfo[m_nType].m_aKeyInfo[nNextKey].m_pKey[CntModel].m_fPosZ -
				m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fPosZ;
			float rotDiffX = m_aInfo[m_nType].m_aKeyInfo[nNextKey].m_pKey[CntModel].m_fRotX -
				m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fRotX;
			float rotDiffY = m_aInfo[m_nType].m_aKeyInfo[nNextKey].m_pKey[CntModel].m_fRotY -
				m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fRotY;
			float rotDiffZ = m_aInfo[m_nType].m_aKeyInfo[nNextKey].m_pKey[CntModel].m_fRotZ -
				m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fRotZ;

			//�ʒu�����Z�o
			float posDemandX = m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fPosX + posDiffX;
			float posDemandY = m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fPosY + posDiffY;
			float posDemandZ = m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fPosZ + posDiffZ;
			float rotDemandX = m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fRotX + rotDiffX;
			float rotDemandY = m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fRotY + rotDiffY;
			float rotDemandZ = m_aInfo[m_nType].m_aKeyInfo[nNowKey].m_pKey[CntModel].m_fRotZ + rotDiffZ;

			//�p�[�c�̈ʒu�����ݒ�
			posMotioned += D3DXVECTOR3(posDemandX, posDemandY, posDemandZ);
			rotMotioned += D3DXVECTOR3(rotDemandX, rotDemandY, rotDemandZ);
			m_ppModel[CntModel]->SetPosMotioned(posMotioned);
			m_ppModel[CntModel]->SetRotMotioned(rotMotioned);
		}
	}
}

//========================
//���[�V�������ݒ菈��
//========================
void CMotion::SetInfo(INFO info)
{
	//������ăJ�E���g���₷
	m_aInfo[m_nNumAll] = info;
	m_nNumAll++;
}

//========================
//���f���ݒ菈��
//========================
void CMotion::SetModel(CModel** ppModel, int nNumModel)
{
	//���f������đ����������
	m_ppModel = ppModel;
	m_nNumModel = nNumModel;

	//���I�m��
	for (int cntInfo = 0; cntInfo < INFO_NUM; cntInfo++)
	{
		for (int cntKeyInfo = 0; cntKeyInfo < KEYINFO_NUM; cntKeyInfo++)
		{
			m_aInfo[cntInfo].m_aKeyInfo[cntKeyInfo].m_pKey = new KEY[m_nNumModel];
			for (int cntKey = 0; cntKey < m_nNumModel; cntKey++)
			{
				m_aInfo[cntInfo].m_aKeyInfo[cntKeyInfo].m_pKey[cntKey].m_fPosX = CManager::FLT_ZERO;
				m_aInfo[cntInfo].m_aKeyInfo[cntKeyInfo].m_pKey[cntKey].m_fPosY = CManager::FLT_ZERO;
				m_aInfo[cntInfo].m_aKeyInfo[cntKeyInfo].m_pKey[cntKey].m_fPosZ = CManager::FLT_ZERO;
				m_aInfo[cntInfo].m_aKeyInfo[cntKeyInfo].m_pKey[cntKey].m_fRotX = CManager::FLT_ZERO;
				m_aInfo[cntInfo].m_aKeyInfo[cntKeyInfo].m_pKey[cntKey].m_fRotY = CManager::FLT_ZERO;
				m_aInfo[cntInfo].m_aKeyInfo[cntKeyInfo].m_pKey[cntKey].m_fRotZ = CManager::FLT_ZERO;
			}
			m_aInfo[cntInfo].m_aKeyInfo[cntKeyInfo].m_nFrame = 0;
		}
		m_aInfo[cntInfo].m_bLoop = false;
		m_aInfo[cntInfo].m_nNumKey = CManager::INT_ZERO;
	}
}
