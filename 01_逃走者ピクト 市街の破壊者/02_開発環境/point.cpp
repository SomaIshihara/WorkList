//======================================================
//
//�ړ��|�C���g[point.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "point.h"
#include "building.h"
#include "picto.h"
#include "objectX.h"
#include "koban.h"
#include "Culc.h"
#include <vector>

//�ÓI�����o�ϐ�
CPoint* CPoint::m_pTop = nullptr;
CPoint* CPoint::m_pCur = nullptr;
int CPoint::m_nNumAll = 0;
const float CPoint::MERGE_LENGTH = 40.0f;
const float CPoint::POINT_INTERVAL = 20.0f;

//=================================
//�R���X�g���N�^
//=================================
CPoint::CPoint()
{
	if (m_pCur == nullptr)
	{//�Ō�������Ȃ��i���Ȃ킿�擪�����Ȃ��j
		m_pTop = this;		//�����擪
		m_pPrev = nullptr;		//�O��N�����Ȃ�
		m_pNext = nullptr;
	}
	else
	{//�Ō��������
		m_pPrev = m_pCur;		//�Ō���������̑O�̃I�u�W�F
		m_pCur->m_pNext = this;	//�Ō���̎��̃I�u�W�F������
		m_pNext = nullptr;			//�����̎��̃I�u�W�F�͂��Ȃ�
	}
	m_bDeath = false;
	m_pCur = this;	//�����Ō��
	m_nNumAll++;
}

//=================================
//�f�X�g���N�^
//=================================
CPoint::~CPoint()
{
}

//=================================
//������
//=================================
HRESULT CPoint::Init(void)
{
	return S_OK;
}

//=================================
//���ׂďI��
//=================================
void CPoint::ReleaseAll(void)
{
	CPoint* pPoint = m_pTop;	//�擪������

	while (pPoint != nullptr)
	{//�Ō���܂ŉ񂵑�����
		CPoint* pPointNext = pPoint->m_pNext;	//���̃I�u�W�F�ۑ�

		pPoint->Release();		//�j��

		pPoint = pPointNext;	//��������
	}

	Death();	//�S���ւ��܂�
}

//=================================
//�I��
//=================================
void CPoint::Release(void)
{
	m_bDeath = true;	//���S�t���O�ɂ���
}

//=================================
//�X�V
//=================================
void CPoint::Update(void)
{
	ReleaseAll();	//�����������

	//�����ɉ����Đ���
	for (int cnt = 0; cnt < CBuilding::GetNumAll(); cnt++)
	{
		CBuilding* pBuilding = CBuilding::GetBuilding(cnt);

		if (pBuilding != nullptr)
		{//��������
			D3DXVECTOR3 pos = pBuilding->GetPos();				//�ʒu�擾
			float fWidthHalf = pBuilding->GetWidth() * 0.5f;	//���擾
			float fDepthHalf = pBuilding->GetDepth() * 0.5f;	//���s�擾

			CPoint::Create(pos + D3DXVECTOR3(-(fWidthHalf + POINT_INTERVAL), 0.0f, -(fDepthHalf + POINT_INTERVAL)));
			CPoint::Create(pos + D3DXVECTOR3((fWidthHalf + POINT_INTERVAL), 0.0f, -(fDepthHalf + POINT_INTERVAL)));
			CPoint::Create(pos + D3DXVECTOR3(-(fWidthHalf + POINT_INTERVAL), 0.0f, (fDepthHalf + POINT_INTERVAL)));
			CPoint::Create(pos + D3DXVECTOR3((fWidthHalf + POINT_INTERVAL), 0.0f, (fDepthHalf + POINT_INTERVAL)));
		}
	}

	//�A�W�g
	CObject* pBuilding = CPicto::GetAgit();

	if (pBuilding != nullptr)
	{//��������
		D3DXVECTOR3 pos = pBuilding->GetPos();				//�ʒu�擾
		float fWidthHalf = pBuilding->GetWidth() * 0.5f;	//���擾
		float fDepthHalf = pBuilding->GetDepth() * 0.5f;	//���s�擾

		CPoint::Create(pos + D3DXVECTOR3(-(fWidthHalf + POINT_INTERVAL), 0.0f, -(fDepthHalf + POINT_INTERVAL)));
		CPoint::Create(pos + D3DXVECTOR3((fWidthHalf + POINT_INTERVAL), 0.0f, -(fDepthHalf + POINT_INTERVAL)));
		CPoint::Create(pos + D3DXVECTOR3(-(fWidthHalf + POINT_INTERVAL), 0.0f, (fDepthHalf + POINT_INTERVAL)));
		CPoint::Create(pos + D3DXVECTOR3((fWidthHalf + POINT_INTERVAL), 0.0f, (fDepthHalf + POINT_INTERVAL)));
	}

	//���
	for (int cnt = 0; cnt < CKoban::GetNumAll(); cnt++)
	{
		CKoban* pKoban = CKoban::GetKoban(cnt);

		if (pKoban != nullptr)
		{//��������
			D3DXVECTOR3 pos = pKoban->GetPos();				//�ʒu�擾
			float fWidthHalf = pKoban->GetWidth() * 0.5f;	//���擾
			float fDepthHalf = pKoban->GetDepth() * 0.5f;	//���s�擾

			CPoint::Create(pos + D3DXVECTOR3(-(fWidthHalf + POINT_INTERVAL), 0.0f, -(fDepthHalf + POINT_INTERVAL)));
			CPoint::Create(pos + D3DXVECTOR3((fWidthHalf + POINT_INTERVAL), 0.0f, -(fDepthHalf + POINT_INTERVAL)));
			CPoint::Create(pos + D3DXVECTOR3(-(fWidthHalf + POINT_INTERVAL), 0.0f, (fDepthHalf + POINT_INTERVAL)));
			CPoint::Create(pos + D3DXVECTOR3((fWidthHalf + POINT_INTERVAL), 0.0f, (fDepthHalf + POINT_INTERVAL)));
		}
	}

	//���ׂẴ|�C���g�ɑ΂��āA�����ɖ�����Ă��Ȃ����m�F
	CPoint* pPoint = CPoint::GetTop();	//�擪�擾
	while (pPoint != nullptr)
	{
		CPoint* pPointNext = pPoint->GetNext();	//���擾

		//�����̕������m�F
		for (int cnt = 0; cnt < CBuilding::GetNumAll(); cnt++)
		{
			CBuilding* pBuilding = CBuilding::GetBuilding(cnt);

			if (pBuilding != nullptr)
			{//����
				D3DXVECTOR3 posBuild = pBuilding->GetPos();			//�����ʒu�擾
				D3DXVECTOR3 posPoint = pPoint->m_pos;				//�|�C���g�ʒu�擾
				float fWidthHalf = pBuilding->GetWidth() * 0.5f;	//�T�C�Y�擾
				float fDepthHalf = pBuilding->GetDepth() * 0.5f;

				if (posPoint.x > posBuild.x - fWidthHalf &&
					posPoint.x < posBuild.x + fWidthHalf &&
					posPoint.z > posBuild.z - fDepthHalf &&
					posPoint.z < posBuild.z + fDepthHalf)
				{//�I�{�{�{�{�i������Ă�j
					pPoint->m_pFrag->Uninit();	//�����ւ��܂�
					pPoint->Release();			//��
					break;						//for���I��
				}
			}
		}

		pPoint = pPointNext;	//�������
	}

	//�܂Ƃ߂Ăւ��܂�
	Death();

	//�߂�����|�C���g���}�[�W�i���̍ہA���S�t���O�Ɖ������|�C���g�͖������邱�Ɓj
	pPoint = CPoint::GetTop();	//�擪�擾
	while (pPoint != nullptr)
	{
		CPoint* pPointNext = pPoint->GetNext();	//���擾

		if (pPoint->m_bDeath == false)
		{//���ʂ̊�
			//2�ڂ̃|�C���g
			std::vector<CPoint*> vector;
			CPoint* pPointSecond = CPoint::GetTop();	//�擪�擾
			while (pPointSecond != nullptr)
			{
				CPoint* pPointSecondNext = pPointSecond->GetNext();	//���擾

				if (pPointSecond != pPoint && pPointSecond->m_bDeath == false && D3DXVec3Length(&(pPoint->GetPos() - pPointSecond->GetPos())) < MERGE_LENGTH)
				{//�͈͓��ŕ��ʂ̊�
					vector.emplace_back(pPointSecond);	//�}�[�W���X�g�ɓ����
				}

				pPointSecond = pPointSecondNext;	//�������
			}

			if (vector.size() > 0)
			{//�߂��̂�1�ł�����
				//�}�[�W�����i�߂��|�C���g���m���ׂĎ��S�t���O�ɂ��Ă��̊ԂɐV�����|�C���g��u���j
				D3DXVECTOR3 posAverage = pPoint->GetPos();	//�ʒu���炤
				pPoint->m_pFrag->Uninit();					//�����ւ��܂�
				pPoint->Release();							//���S�t���O�ɂ���
				for (int cnt = 0; cnt < vector.size(); cnt++)
				{
					posAverage += vector[cnt]->GetPos();	//���_������
					vector[cnt]->m_pFrag->Uninit();			//�����ւ��܂�
					vector[cnt]->Release();					//���S�t���O�ɂ���
				}
				posAverage /= (vector.size() + 1);	//���ώ��
				CPoint::Create(posAverage);			//�V�����u��
			}
		}

		pPoint = pPointNext;	//�������
	}

	//�܂Ƃ߂Ăւ��܂�
	Death();

	//�|�C���g�ڑ�
	pPoint = CPoint::GetTop();	//�擪�擾
	while (pPoint != nullptr)
	{//�ݒ�
		CPoint* pPointSecond = CPoint::GetTop();

		while (pPointSecond != nullptr)
		{
			if (pPoint != pPointSecond)
			{//���i�[���Ă���z����Ȃ�
				D3DXVECTOR3 pos = pPoint->GetPos();
				D3DXVECTOR3 posSecond = pPointSecond->GetPos();
				D3DXVECTOR3 vecPoint = posSecond - pos;

				bool bCollision = false;
				for (int cnt = 0; cnt < CBuilding::GetNumAll(); cnt++)
				{
					CBuilding* pBuilding = CBuilding::GetBuilding(cnt);
					if (pBuilding != nullptr)
					{
						D3DXVECTOR3 posBuilding = pBuilding->GetPos();
						float fWidthHalf = pBuilding->GetWidth() * 0.5f;
						float fDepthHalf = pBuilding->GetDepth() * 0.5f;

						//4���_���
						D3DXVECTOR3 posBuild[4];
						posBuild[0] = posBuilding + D3DXVECTOR3(-fWidthHalf, 0.0f, -fDepthHalf);
						posBuild[1] = posBuilding + D3DXVECTOR3(fWidthHalf, 0.0f, -fDepthHalf);
						posBuild[2] = posBuilding + D3DXVECTOR3(fWidthHalf, 0.0f, fDepthHalf);
						posBuild[3] = posBuilding + D3DXVECTOR3(-fWidthHalf, 0.0f, fDepthHalf);

						//�v���X�}�C�i�X�����������̃t���b�O
						for (int cntPos = 0; cntPos < 4; cntPos++)
						{
							D3DXVECTOR3 vecLine = (posBuild[(cntPos + 1) % 4] - posBuild[cntPos]);
							D3DXVECTOR3 vecToPosOld = pos - posBuild[cntPos];
							D3DXVECTOR3 vecToPos = posSecond - posBuild[cntPos];
							if (TASUKIGAKE(vecLine.x, vecLine.z, vecToPosOld.x, vecToPosOld.z) >= 0.0f && TASUKIGAKE(vecLine.x, vecLine.z, vecToPos.x, vecToPos.z) < 0.0f)
							{//��������
								float fAreaA = (vecToPos.z * vecPoint.x) - (vecToPos.x * vecPoint.z);
								float fAreaB = (vecLine.z * vecPoint.x) - (vecLine.x * vecPoint.z);
								if (fAreaA / fAreaB >= 0.0f && fAreaA / fAreaB <= 1.0f)
								{//������
									bCollision = true;	//�Փ˂���
									break;	//�������������̂ŏI��
								}
							}
						}

						if (bCollision == true)
						{
							break;
						}
					}
				}

				if (bCollision == false)
				{//�������ĂȂ�
					pPoint->m_connectPoint.emplace_back(pPointSecond);
				}
			}
			pPointSecond = pPointSecond->GetNext();	//�������
		}

		pPoint = pPoint->GetNext();	//�������
	}
}

//=================================
//����
//=================================
CPoint* CPoint::Create(const D3DXVECTOR3 pos)
{
	CPoint* pPoint = nullptr;

	if (pPoint == nullptr)
	{
		//�|�C���g�̐���
		pPoint = new CPoint;

		//������
		pPoint->Init();
		pPoint->m_pos = pos;
		pPoint->m_pFrag = CObjectX::Create(pos, CManager::VEC3_ZERO, CManager::GetFragModel());

		return pPoint;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//�T��
//=================================
CPoint* CPoint::Search(const D3DXVECTOR3 pos, const CPoint* pNowPoint)
{
	CPoint* pPoint = m_pTop;	//�擪������
	CPoint* pPointNear = nullptr;
	float fLength = 0.0f;

	while (pPoint != nullptr)
	{//�Ō���܂ŉ񂵑�����
		CPoint* pPointNext = pPoint->m_pNext;	//���̃I�u�W�F�ۑ�
		
		//��������
		float fLengthNow = D3DXVec3Length(&(pPoint->m_pos - pos));
		if (pPointNear == nullptr || fLength > fLengthNow)
		{//�܂�����
			pPointNear = pPoint;
			fLength = fLengthNow;
		}

		pPoint = pPointNext;	//��������
	}
	return pPointNear;
}

//=================================
//���S�t���O�Ɖ����������ւ��܂�
//=================================
void CPoint::Death(void)
{
	CPoint* pPoint = m_pTop;	//�擪������
	while (pPoint != nullptr)
	{//�Ō���܂ŉ񂵑�����
		CPoint* pPointNext = pPoint->m_pNext;	//���̃I�u�W�F�ۑ�

		if (pPoint->m_bDeath == true)
		{//����͎��S�t���O�ł�
			if (pPoint->m_pPrev != nullptr)
			{//�O�ɃI�u�W�F������
				pPoint->m_pPrev->m_pNext = pPoint->m_pNext;	//�O�̃I�u�W�F�̎��̃I�u�W�F�͎����̎��̃I�u�W�F
			}
			if (pPoint->m_pNext != nullptr)
			{
				pPoint->m_pNext->m_pPrev = pPoint->m_pPrev;	//���̃I�u�W�F�̑O�̃I�u�W�F�͎����̑O�̃I�u�W�F
			}

			if (m_pCur == pPoint)
			{//�Ō���ł���
				m_pCur = pPoint->m_pPrev;	//�Ō���������̑O�̃I�u�W�F�ɂ���
			}
			if (m_pTop == pPoint)
			{
				m_pTop = pPoint->m_pNext;	//�擪�������̎��̃I�u�W�F�ɂ���
			}

			//����	
			delete pPoint;	//�������g�j��
			m_nNumAll--;	//�������炷
		}

		pPoint = pPointNext;	//��������
	}
}
