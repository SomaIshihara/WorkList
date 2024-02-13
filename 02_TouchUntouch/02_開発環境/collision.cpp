//======================================================
//
//�����蔻�菈����[collision.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "collision.h"
#include "Culc.h"
#include "manager.h"
#include "objectBillboard.h"

//�ÓI�����o�ϐ�
CBoxCollider* CBoxCollider::m_pTop;	//�擪�I�u�W�F�N�g
CBoxCollider* CBoxCollider::m_pCur;	//�Ō���I�u�W�F�N�g
bool CBoxCollider::m_aTagColl[CBoxCollider::TAG_MAX][CBoxCollider::TAG_MAX] =
{//  Univ   A    B
	{true,true,true},	//Univ
	{true,true,false},	//A
	{true,false,true}	//B
};

//=================================
//�R���X�g���N�^
//=================================
CCollision::CCollision()
{
	m_vtxMin = CManager::VEC3_ZERO;
	m_vtxMax = CManager::VEC3_ZERO;
}

//=================================
//�f�X�g���N�^
//=================================
CCollision::~CCollision()
{
}

//=================================
//�����蔻��`�F�b�N
//=================================
bool CCollision::CollisionCheck(const D3DXVECTOR3 posOld, const D3DXVECTOR3 posNew, const D3DXVECTOR3 posCenter, const D3DXVECTOR3 rot)
{
	//�O����
	if (CollisionPolygon(posOld, posNew, posCenter, rot, D3DXVECTOR3(0.0f, 0.0f, -1.0f),
		D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMin.z), D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMin.z),
		D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMin.z), D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMin.z)) == true)
	{
		return true;
	}

	//�E����
	if (CollisionPolygon(posOld, posNew, posCenter, rot, D3DXVECTOR3(1.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMin.z), D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMin.z),
		D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMin.z), D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMin.z)) == true)
	{
		return true;
	}

	//������
	if (CollisionPolygon(posOld, posNew, posCenter, rot, D3DXVECTOR3(0.0f, 0.0f, 1.0f),
		D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMax.z), D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMax.z),
		D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMax.z), D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMax.z)) == true)
	{
		return true;
	}

	//������
	if (CollisionPolygon(posOld, posNew, posCenter, rot, D3DXVECTOR3(-1.0f, 0.0f, 0.0f),
		D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMax.z), D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMin.z),
		D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMin.z), D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMax.z)) == true)
	{
		return true;
	}

	//�㑤��
	if (CollisionPolygon(posOld, posNew, posCenter, rot, D3DXVECTOR3(0.0f, 1.0f, 0.0f),
		D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMin.z), D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMin.z),
		D3DXVECTOR3(m_vtxMax.x, m_vtxMax.y, m_vtxMax.z), D3DXVECTOR3(m_vtxMin.x, m_vtxMax.y, m_vtxMax.z)) == true)
	{
		return true;
	}

	//������
	if (CollisionPolygon(posOld, posNew, posCenter, rot, D3DXVECTOR3(0.0f, -1.0f, 0.0f),
		D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMin.z), D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMin.z),
		D3DXVECTOR3(m_vtxMax.x, m_vtxMin.y, m_vtxMax.z), D3DXVECTOR3(m_vtxMin.x, m_vtxMin.y, m_vtxMax.z)) == true)
	{
		return true;
	}

	return false;
}

//=================================
//�|���S�����Ƃ̓����蔻��`�F�b�N
//=================================
bool CCollision::CollisionPolygon(const D3DXVECTOR3 posOld, const D3DXVECTOR3 posNew, const D3DXVECTOR3 posCenter, const D3DXVECTOR3 rot,
	const D3DXVECTOR3 vecNor, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 pos3)
{
	//���_�̉�]�ɕK�v�ȕϐ�
	//�e���_�����߂�̂ɕK�v�ȕϐ�
	D3DXMATRIX mtxWorld;	//��]�̃x�[�X�ƂȂ郏�[���h�}�g��
	D3DXMATRIX mtxRot;		//��]�s��
	D3DXMATRIX mtxTrans;	//���ׂĕϊ���̍s��
	D3DXVECTOR3 vtxTrans;	//�ϊ���̓_

	//���_�̉�]
	pos0 = RotateVtx(pos0, rot, posCenter);	//pos0
	pos1 = RotateVtx(pos1, rot, posCenter);	//pos1
	pos2 = RotateVtx(pos2, rot, posCenter);	//pos2
	pos3 = RotateVtx(pos3, rot, posCenter);	//pos3

	//�����蔻��
	if (D3DXVec3Dot(&posOld, &vecNor) * D3DXVec3Dot(&posNew, &vecNor) <= 0)
	{
		//�|���S���ђʂ��Ă��邩
		D3DXVECTOR3 ray = posNew - posOld;			//���C
		D3DXVec3Normalize(&ray, &ray);				//���C�𐳋K��
		float fU, fV, fD;							//���ݔ�

		if (D3DXIntersectTri(&pos0, &pos1, &pos3, &posOld, &ray, &fU, &fV, &fD) == true || D3DXIntersectTri(&pos1, &pos2, &pos3, &posOld, &ray, &fU, &fV, &fD) == true)
		{//�l�p�`���O�p�`�ɕ������A�ǂ��炩true�A���Ă�����I���ł���
			return true;
		}
	}
	
	return false;
}

//=================================
//�R���X�g���N�^
//=================================
CBoxCollider::CBoxCollider()
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
	m_pCur = this;				//�����Ō��
}

//=================================
//�f�X�g���N�^
//=================================
CBoxCollider::~CBoxCollider()
{
}

//=================================
//�����蔻��`�F�b�N
//=================================
void CBoxCollider::CollisionCheck(void)
{
	//�����蔻�茋��
	CollisionResult collResult;
	collResult.bHit[0] = false;
	collResult.bHit[1] = false;
	collResult.bHit[2] = false;
	
	//�������������蔻��L����
	if (this->m_type != TYPE_NONE)
	{
		//�����̓����蔻��
		D3DXVECTOR3 move = m_iCollisionReader->GetMove();
		D3DXVECTOR3 posOld = m_iCollisionReader->GetPosOld();
		D3DXVECTOR3 pos = posOld;
		float fPlayerWidth = m_iCollisionReader->GetWidth() * 0.5f;
		float fPlayerHeight = m_iCollisionReader->GetHeight() * 0.5f;
		float fPlayerDepth = m_iCollisionReader->GetDepth() * 0.5f;

		//X
		pos.x += move.x;
		ColFloat playerCol;
		playerCol.pPosMain = &pos.x;
		playerCol.pPosSubA = pos.y;
		playerCol.pPosSubB = pos.z;
		playerCol.fSizeMain = fPlayerWidth;
		playerCol.fSizeSubA = fPlayerHeight;
		playerCol.fSizeSubB = fPlayerDepth;

		CBoxCollider* pCollider = CBoxCollider::GetTop();

		while (pCollider != nullptr)
		{
			if (pCollider != this && pCollider->m_type != TYPE_NONE && m_aTagColl[this->m_tag][pCollider->m_tag] == true)
			{
				ColFloat otherCol;
				D3DXVECTOR3 posOther = pCollider->m_iCollisionReader->GetPosOld() + pCollider->m_iCollisionReader->GetMove();
				otherCol.pPosMain = &posOther.x;
				otherCol.pPosSubA = posOther.y;
				otherCol.pPosSubB = posOther.z;
				otherCol.fSizeMain = pCollider->m_iCollisionReader->GetWidth() * 0.5f;
				otherCol.fSizeSubA = pCollider->m_iCollisionReader->GetHeight() * 0.5f;
				otherCol.fSizeSubB = pCollider->m_iCollisionReader->GetDepth() * 0.5f;

				if (CollisionAxis(playerCol, posOld.x, otherCol, pCollider->m_type))	//�����蔻��
				{
					//�d���`�F�b�N
					bool bRegisted = false;
					for (int cnt = 0; cnt < collResult.collList.size(); cnt++)
					{
						if (collResult.collList[cnt] == pCollider->m_iCollisionReader->GetObj())
						{
							bRegisted = true;
							break;
						}

					}

					if (bRegisted == false)
					{//�d�����ĂȂ�
						collResult.collList.emplace_back(pCollider->m_iCollisionReader->GetObj());
					}

					collResult.bHit[0] = true;
				}
			}
			pCollider = pCollider->GetNext();	//���̃u���b�N
		}

		//Y
		pos.y += move.y;
		playerCol.pPosMain = &pos.y;
		playerCol.pPosSubA = pos.x;
		playerCol.pPosSubB = pos.z;
		playerCol.fSizeMain = fPlayerHeight;
		playerCol.fSizeSubA = fPlayerWidth;
		playerCol.fSizeSubB = fPlayerDepth;

		pCollider = CBoxCollider::GetTop();

		while (pCollider != nullptr)
		{
			if (pCollider != this && pCollider->m_type != TYPE_NONE && m_aTagColl[this->m_tag][pCollider->m_tag] == true)
			{
				ColFloat otherCol;
				D3DXVECTOR3 posOther = pCollider->m_iCollisionReader->GetPosOld() + pCollider->m_iCollisionReader->GetMove();
				otherCol.pPosMain = &posOther.y;
				otherCol.pPosSubA = posOther.x;
				otherCol.pPosSubB = posOther.z;
				otherCol.fSizeMain = pCollider->m_iCollisionReader->GetHeight() * 0.5f;
				otherCol.fSizeSubA = pCollider->m_iCollisionReader->GetWidth() * 0.5f;
				otherCol.fSizeSubB = pCollider->m_iCollisionReader->GetDepth() * 0.5f;

				if (CollisionAxis(playerCol, posOld.y, otherCol, pCollider->m_type) == true)	//�����蔻��
				{//���n����
				 //�d���`�F�b�N
					bool bRegisted = false;
					for (int cnt = 0; cnt < collResult.collList.size(); cnt++)
					{
						if (collResult.collList[cnt] == pCollider->m_iCollisionReader->GetObj())
						{
							bRegisted = true;
							break;
						}

					}

					if (bRegisted == false)
					{//�d�����ĂȂ�
						collResult.collList.emplace_back(pCollider->m_iCollisionReader->GetObj());
					}

					if (pCollider->m_type == TYPE_COLLISION)
					{
						collResult.bHit[1] = true;
					}
				}
			}
			pCollider = pCollider->GetNext();	//���̃u���b�N
		}

		//Z
		pos.z += move.z;
		playerCol.pPosMain = &pos.z;
		playerCol.pPosSubA = pos.x;
		playerCol.pPosSubB = pos.y;
		playerCol.fSizeMain = fPlayerDepth;
		playerCol.fSizeSubA = fPlayerWidth;
		playerCol.fSizeSubB = fPlayerHeight;

		pCollider = CBoxCollider::GetTop();

		while (pCollider != nullptr)
		{
			if (pCollider != this && pCollider->m_type != TYPE_NONE && m_aTagColl[this->m_tag][pCollider->m_tag] == true)
			{
				ColFloat otherCol;
				D3DXVECTOR3 posOther = pCollider->m_iCollisionReader->GetPosOld() + pCollider->m_iCollisionReader->GetMove();
				otherCol.pPosMain = &posOther.z;
				otherCol.pPosSubA = posOther.x;
				otherCol.pPosSubB = posOther.y;
				otherCol.fSizeMain = pCollider->m_iCollisionReader->GetDepth() * 0.5f;
				otherCol.fSizeSubA = pCollider->m_iCollisionReader->GetWidth() * 0.5f;
				otherCol.fSizeSubB = pCollider->m_iCollisionReader->GetHeight() * 0.5f;

				if (CollisionAxis(playerCol, posOld.z, otherCol, pCollider->m_type))	//�����蔻��
				{
					//�d���`�F�b�N
					bool bRegisted = false;
					for (int cnt = 0; cnt < collResult.collList.size(); cnt++)
					{
						if (collResult.collList[cnt] == pCollider->m_iCollisionReader->GetObj())
						{
							bRegisted = true;
							break;
						}

					}

					if (bRegisted == false)
					{//�d�����ĂȂ�
						collResult.collList.emplace_back(pCollider->m_iCollisionReader->GetObj());
					}

					collResult.bHit[2] = true;
				}
			}
			pCollider = pCollider->GetNext();	//���̃u���b�N
		}

		//�����蔻���̈ʒu�ݒ�
		m_iCollisionReader->SetPos(pos);

	}

	m_collisionResult = collResult;
}

//=================================
//�����蔻�萶��
//=================================
CBoxCollider * CBoxCollider::Create(ICollisionReader* iCollisionReader)
{
	CBoxCollider* pCollider = nullptr;

	if (pCollider == nullptr && iCollisionReader != nullptr)
	{
		pCollider = new CBoxCollider;
		pCollider->m_iCollisionReader = iCollisionReader;

		return pCollider;
	}
	return nullptr;
}

//=================================
//�����蔻��j��
//=================================
void CBoxCollider::Release(void)
{
	if (m_pPrev != nullptr)
	{//�O�ɃI�u�W�F������
		m_pPrev->m_pNext = m_pNext;	//�O�̃I�u�W�F�̎��̃I�u�W�F�͎����̎��̃I�u�W�F
	}
	if (m_pNext != nullptr)
	{
		m_pNext->m_pPrev = m_pPrev;	//���̃I�u�W�F�̑O�̃I�u�W�F�͎����̑O�̃I�u�W�F
	}

	if (m_pCur == this)
	{//�Ō���ł���
		m_pCur = m_pPrev;	//�Ō���������̑O�̃I�u�W�F�ɂ���
	}
	if (m_pTop == this)
	{
		m_pTop = m_pNext;	//�擪�������̎��̃I�u�W�F�ɂ���
	}

	//����
	delete this;	//�������g�j��
}

//=================================
//���P�ʂł̓����蔻��
//=================================
bool CBoxCollider::CollisionAxis(ColFloat source, const float fPosMainOld, ColFloat dest, const TYPE otherType)
{
	bool bCollision = false;

	if (source.pPosSubA - source.fSizeSubA < dest.pPosSubA + dest.fSizeSubA &&
		source.pPosSubA + source.fSizeSubA > dest.pPosSubA - dest.fSizeSubA &&
		source.pPosSubB - source.fSizeSubB < dest.pPosSubB + dest.fSizeSubB &&
		source.pPosSubB + source.fSizeSubB > dest.pPosSubB - dest.fSizeSubB)
	{
		if (this->m_type == TYPE_COLLISION && otherType == TYPE_COLLISION)
		{//�����Ԃ���
			if (fPosMainOld + source.fSizeMain <= *dest.pPosMain - dest.fSizeMain &&
				*source.pPosMain + source.fSizeMain > *dest.pPosMain - dest.fSizeMain)
			{
				*source.pPosMain = *dest.pPosMain - dest.fSizeMain - source.fSizeMain;
				bCollision = true;
			}
			else if (fPosMainOld - source.fSizeMain >= *dest.pPosMain + dest.fSizeMain &&
				*source.pPosMain - source.fSizeMain < *dest.pPosMain + dest.fSizeMain)
			{
				*source.pPosMain = *dest.pPosMain + dest.fSizeMain + source.fSizeMain;
				bCollision = true;
			}
		}
		else if(*source.pPosMain - source.fSizeMain < *dest.pPosMain + dest.fSizeMain &&
			*source.pPosMain + source.fSizeMain > *dest.pPosMain - dest.fSizeMain)
		{//�ǂ��炩�d�Ȃ�ݒ�Ȃ̂͊m��Ȃ̂ŏd�Ȃ��Ă��邩�m�F
			bCollision = true;
		}
		
	}

	return bCollision;
}
