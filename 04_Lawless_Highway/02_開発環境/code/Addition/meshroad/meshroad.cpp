//======================================================
//
//���b�V�����H����[meshroad.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "meshroad.h"
#include "../../IS_Bace/_Expansion/meshfield/meshField.h"
#include "../../IS_Bace/_Core/utility/Utility.h"
#include "../../IS_Bace/_Core/utility/Utility_Vector.h"
#include <vector>

using namespace std;

//�ÓI�����o�ϐ�
CMeshRoad* CMeshRoad::m_pTop = nullptr;
CMeshRoad* CMeshRoad::m_pCur = nullptr;
int CMeshRoad::m_nNumAll = 0;

//�������O���
namespace
{
	const int BLOCK_X = 2;
}

//=================================
//�R���X�g���N�^
//=================================
CMeshRoad::CMeshRoad()
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
	m_nNumAll++;
}

//=================================
//�f�X�g���N�^
//=================================
CMeshRoad::~CMeshRoad()
{
}

//=================================
//������
//=================================
HRESULT CMeshRoad::Init(void)
{
	CMeshField::Init();

	return S_OK;
}

//=================================
//�I��
//=================================
void CMeshRoad::Uninit(void)
{
	CMeshField::Uninit();
}

//=================================
//�X�V
//=================================
void CMeshRoad::Update(void)
{
	CMeshField::Update();
}

//=================================
//�`��
//=================================
void CMeshRoad::Draw(void)
{
	CMeshField::Draw();
}

//=================================
//����
//=================================
CMeshRoad* CMeshRoad::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fLength,
	const std::vector<D3DXVECTOR3>& vVector)
{
	CMeshRoad* pMeshField = nullptr;

	if (pMeshField == nullptr)
	{
		//�I�u�W�F�N�g�̐���
		pMeshField = new CMeshRoad;

		//������
		pMeshField->SetPos(pos);
		pMeshField->SetRot(rot);
		pMeshField->SetSize(fLength, fLength);
		pMeshField->SetBlock(BLOCK_X, vVector.size());
		pMeshField->m_vVector = vVector;
		pMeshField->Init();
		pMeshField->SetVtxBuff();

		return pMeshField;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//�����i�֗��x�N�g���Łj
//=================================
CMeshRoad* CMeshRoad::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fLength,
	const std::vector<IS_Utility::Utility_Vector3>& vVector)
{
	int nVectorNum = vVector.size();
	std::vector<D3DXVECTOR3> vDXVector;

	//����
	vDXVector.clear();

	for (int cnt = 0; cnt < nVectorNum; cnt++)
	{
		vDXVector.push_back(vVector[cnt]);
	}

	return CMeshRoad::Create(pos, rot, fLength, vDXVector);
}

//=================================
//���O����
//=================================
void CMeshRoad::Exclusion(void)
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
	m_nNumAll--;	//�������炷

	CMeshField::Exclusion();
}

//=================================
//���_�ݒ�
//=================================
void CMeshRoad::SetVtxBuff(void)
{
	VERTEX_3D* pVtx;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	float fLength = GetWidth();
	int nBlock = GetBlockDepth();
	D3DXVECTOR3 posCenter = IS_Utility::VEC3_ZERO;

	//�o�b�t�@���b�N
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�ŏ��̒��_�ݒ�
	//���S
	pVtx[1].pos = posCenter;

	//���[
	pVtx[0].pos = D3DXVECTOR3(fLength, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-fLength, 0.0f, 0.0f);
	//���_���炷
	pVtx += 3;

	//���_���W
	for (int nCount = 0; nCount < nBlock; nCount++, pVtx += 3)
	{
		//�g�p�x�N�g��
		D3DXVECTOR3 vec = m_vVector[nCount];

		//���S
		pVtx[1].pos = posCenter + (vec * fLength);
		posCenter += (vec * fLength);

		D3DXMATRIX mtx;

		D3DXMatrixIdentity(&mtx);
		D3DXMatrixRotationY(&mtx, -0.5f * D3DX_PI);
		D3DXVec3TransformCoord(&vec, &vec, &mtx);
		vec.y = 0.0f;
		D3DXVec3Normalize(&vec, &vec);

		//���[
		pVtx[2].pos = pVtx[1].pos + (vec * fLength);

		vec *= -1.0f;
		pVtx[0].pos = pVtx[1].pos + (vec * fLength);

	}

	//���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();
}

//========================
//�����擾
//========================
float CMeshRoad::GetHeight(D3DXVECTOR3 posOld, D3DXVECTOR3 posNew)
{
	D3DXVECTOR3 posVtx, nor;
	if (GetLanding(posOld, posNew, &posVtx, &nor) == true)
	{
		return (-((posNew.x - (posVtx.x)) * nor.x + (posNew.z - (posVtx.z)) * nor.z) / nor.y) + posVtx.y;
	}
	else
	{
		return -FLT_MAX;
	}
}

//========================
//�������c�p�ړ������擾
//========================
D3DXVECTOR3 CMeshRoad::GetPirotRot(D3DXVECTOR3 posOld, D3DXVECTOR3 posLanding)
{
	D3DXVECTOR3 posVtx, nor, vec;
	if (GetLanding(posOld, posLanding, &posVtx, &nor, &vec) == true)
	{
		return vec;
	}
	else
	{
		return IS_Utility::VEC3_ZERO;
	}
}

//========================
//�����擾(ALL)
//========================
float CMeshRoad::GetHeightAll(D3DXVECTOR3 posOld, D3DXVECTOR3 posNew)
{
	CMeshRoad* pMeshRoad = m_pTop;
	CMeshRoad* pMeshRoadNear = nullptr;
	float fLengthNear = FLT_MAX;
	D3DXVECTOR3 posVtxNear, norNear;

	while (pMeshRoad != nullptr)
	{
		D3DXVECTOR3 posVtx, nor;
		if (pMeshRoad->GetLanding(posOld, posNew, &posVtx, &nor) == true)
		{
			float fLength = fabsf(posOld.y - posVtx.y);
			if (fLengthNear > fLength)
			{
				fLengthNear = fLength;
				pMeshRoadNear = pMeshRoad;
			}
		}

		pMeshRoad = pMeshRoad->GetNext();
	}

	if (pMeshRoadNear != nullptr)
	{
		return pMeshRoadNear->GetHeight(posOld, posNew);
	}
	return -FLT_MAX;
}

//========================
//�������c�p�ړ������擾(ALL)
//========================
D3DXVECTOR3 CMeshRoad::GetPirotRotAll(D3DXVECTOR3 posOld, D3DXVECTOR3 posLanding)
{
	CMeshRoad* pMeshField = m_pTop;
	CMeshRoad* pMeshFieldNear = nullptr;
	float fLengthNear = FLT_MAX;
	D3DXVECTOR3 posVtxNear, norNear;

	while (pMeshField != nullptr)
	{
		D3DXVECTOR3 posVtx, nor;
		if (pMeshField->GetLanding(posOld, posLanding, &posVtx, &nor) == true)
		{
			float fLength = fabsf(posOld.y - posVtx.y);
			if (fLengthNear > fLength)
			{
				fLengthNear = fLength;
				pMeshFieldNear = pMeshField;
			}
		}

		pMeshField = pMeshField->GetNext();
	}

	if (pMeshFieldNear != nullptr)
	{
		return pMeshFieldNear->GetPirotRot(posOld, posLanding);
	}
	return IS_Utility::VEC3_ZERO;
}
