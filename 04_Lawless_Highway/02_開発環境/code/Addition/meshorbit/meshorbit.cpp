//======================================================
//
//���b�V���O������[meshorbit.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "meshorbit.h"
#include "../../IS_Bace/_Core/utility/Utility.h"
#include "../../IS_Bace/_Core/utility/Utility_Vector.h"
#include <vector>

using namespace std;

//�������O���
namespace
{
	const int BLOCK_X = 1;
}

//=================================
//�R���X�g���N�^
//=================================
CMeshOrbit::CMeshOrbit(int nPriority) : CMeshField(nPriority)
{
}

//=================================
//�f�X�g���N�^
//=================================
CMeshOrbit::~CMeshOrbit()
{
}

//=================================
//������
//=================================
HRESULT CMeshOrbit::Init(void)
{
	CMeshField::Init();

	return S_OK;
}

//=================================
//�I��
//=================================
void CMeshOrbit::Uninit(void)
{
	if (m_pVector != nullptr)
	{
		delete[] m_pVector;
		m_pVector = nullptr;
	}

	CMeshField::Uninit();
}

//=================================
//�X�V
//=================================
void CMeshOrbit::Update(void)
{
	CMeshField::Update();
}

//=================================
//�`��
//=================================
void CMeshOrbit::Draw(void)
{
	CMeshField::Draw();
}

//=================================
//����
//=================================
CMeshOrbit* CMeshOrbit::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fLength, const int nBlock)
{
	CMeshOrbit* pMeshOrbit = nullptr;

	if (pMeshOrbit == nullptr)
	{
		//�I�u�W�F�N�g�̐���
		pMeshOrbit = new CMeshOrbit;

		//������
		pMeshOrbit->SetPos(pos);
		pMeshOrbit->SetRot(rot);
		pMeshOrbit->SetSize(fLength, fLength);
		pMeshOrbit->SetBlock(BLOCK_X, nBlock);
		pMeshOrbit->m_pVector = new IS_Utility::Utility_Vector3[nBlock];
		pMeshOrbit->Init();
		pMeshOrbit->SetVtxBuff();

		return pMeshOrbit;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//���_�ݒ�
//=================================
void CMeshOrbit::SetVtxBuff(void)
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
	pVtx[0].pos = D3DXVECTOR3(fLength, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(-fLength, 0.0f, 0.0f);
	//���_���炷
	pVtx += (BLOCK_X + 1);

	//���_���W
	for (int nCount = 0; nCount < nBlock; nCount++, pVtx += (BLOCK_X + 1))
	{
		//�g�p�x�N�g��
		D3DXVECTOR3 vec = m_pVector[nCount];

		//(���S)
		posCenter += (vec * fLength);

		//��]�s�񐶐�
		D3DXMATRIX mtx;
		D3DXMatrixIdentity(&mtx);
		D3DXMatrixRotationY(&mtx, -0.5f * D3DX_PI);
		D3DXVec3TransformCoord(&vec, &vec, &mtx);
		D3DXVec3Normalize(&vec, &vec);

		//���[���W�z�u
		pVtx[1].pos = posCenter + (vec * fLength);

		vec *= -1.0f;
		pVtx[0].pos = posCenter + (vec * fLength);
	}

	//���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();
}

//=================================
//�x�N�g�������o��
//=================================
void CMeshOrbit::Push(const IS_Utility::Utility_Vector3 vec)
{
	int nBlock = GetBlockDepth();
	if (m_pVector == nullptr)
	{//�Ȃ����ʂ�ۂȂ琶��
		m_pVector = new IS_Utility::Utility_Vector3[nBlock];
	}

	//�Ȃ������琶�����Ă邵�����ˁH�H�H
	if (m_pVector != nullptr)
	{
		//����ւ�
		for (int cnt = nBlock - 1; cnt > 0; cnt--)
		{
			m_pVector[cnt] = m_pVector[cnt - 1];
		}

		//�擪�ɓ��ꂽ���̂�����
		m_pVector[0] = vec;

		//���_�Đݒ�
		SetVtxBuff();
	}
}