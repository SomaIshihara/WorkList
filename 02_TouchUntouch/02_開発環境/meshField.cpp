//======================================================
//
//���b�V���t�B�[���h����[meshField.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "meshField.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include <vector>

#include <string>
using namespace std;

//=================================
//�R���X�g���N�^
//=================================
CMeshField::CMeshField()
{
	//�l�N���A
	m_pos = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fWidth = CManager::FLT_ZERO;
	m_fDepth = CManager::FLT_ZERO;
	m_nBlockWidth = CManager::INT_ZERO;
	m_nBlockDepth = CManager::INT_ZERO;
}

//=================================
//�f�X�g���N�^
//=================================
CMeshField::~CMeshField()
{
}

//=================================
//������
//=================================
HRESULT CMeshField::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	m_nIdxTexture = -1;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * (m_nBlockWidth + 1) * (m_nBlockDepth + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxbuff,
		nullptr);

	//�C���f�b�N�X�o�b�t�@�̐���
	int nIdxNum = (((m_nBlockWidth + 1) * m_nBlockDepth * 2) + (2 * (m_nBlockDepth - 1)));
	pDevice->CreateIndexBuffer(sizeof(WORD) * nIdxNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		nullptr);

	VERTEX_3D *pVtx;

	//�o�b�t�@���b�N
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	m_pVtxbuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W+�e�N�X�`�����W
	for (int nCount = 0; nCount < (m_nBlockWidth + 1) * (m_nBlockDepth + 1); nCount++)
	{
		//���_���W�i���΍��W�j
		pVtx[nCount].pos = D3DXVECTOR3(m_fWidth * (nCount % (m_nBlockWidth + 1)), 0.0f, -m_fDepth * (nCount / (m_nBlockWidth + 1)));

		//�J���[
		pVtx[nCount].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[nCount].tex = D3DXVECTOR2(((float)(nCount % (m_nBlockWidth + 1))), ((float)(nCount / (m_nBlockWidth + 1))));
	}

	vector<D3DXVECTOR3>* pNor = new vector<D3DXVECTOR3>[(m_nBlockWidth + 1) * (m_nBlockDepth + 1)];

	for (int cntZ = 0; cntZ < m_nBlockDepth; cntZ++)
	{
		for (int cntX = 0; cntX < m_nBlockWidth; cntX++)
		{
			D3DXVECTOR3 nor0, nor1, nor2, nor3;
			D3DXVECTOR3 vec0, vec1;
			int nVtx0 = cntZ * (m_nBlockDepth + 1) + cntX;
			int nVtx1 = cntZ * (m_nBlockDepth + 1) + cntX + 1;
			int nVtx2 = (cntZ + 1) * (m_nBlockDepth + 1) + cntX;
			int nVtx3 = (cntZ + 1) * (m_nBlockDepth + 1) + cntX + 1;

			//1
			vec0 = pVtx[nVtx3].pos - pVtx[nVtx1].pos;
			vec1 = pVtx[nVtx0].pos - pVtx[nVtx1].pos;
			D3DXVec3Cross(&nor1, &vec0, &vec1);
			D3DXVec3Normalize(&nor1, &nor1);

			//2
			vec0 = pVtx[nVtx0].pos - pVtx[nVtx2].pos;
			vec1 = pVtx[nVtx3].pos - pVtx[nVtx2].pos;
			D3DXVec3Cross(&nor2, &vec0, &vec1);
			D3DXVec3Normalize(&nor2, &nor2);

			//0
			nor0 = (nor1 + nor2);
			D3DXVec3Normalize(&nor0, &nor0);
			//3
			nor3 = (nor1 + nor2);
			D3DXVec3Normalize(&nor3, &nor3);

			pNor[nVtx0].push_back(nor0);
			pNor[nVtx1].push_back(nor1);
			pNor[nVtx2].push_back(nor2);
			pNor[nVtx3].push_back(nor3);
		}
	}

	for (int nCount = 0; nCount < (m_nBlockWidth + 1) * (m_nBlockDepth + 1); nCount++, pVtx++)
	{
		D3DXVECTOR3 nor = CManager::VEC3_ZERO;
		//�S�@���𑫂�
		for (int cntNor = 0; cntNor < pNor[nCount].size(); cntNor++)
		{
			nor += pNor[nCount].at(cntNor);
		}
		D3DXVec3Normalize(&nor, &nor);

		//�@���x�N�g��
		pVtx->nor = nor;
	}

	delete[] pNor;

	//���_�o�b�t�@���A�����b�N
	m_pVtxbuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�ݒ�
	WORD *pIdx;	//�C���f�b�N�X���ւ̃|�C���^
	int nCntWidth;	//�C���f�b�N�X�J�E���^

	//�o�b�t�@���b�N
	m_pIdxBuff->Lock(0, 0, (void **)&pIdx, 0);

	for (nCntWidth = 0; nCntWidth < m_nBlockDepth - 1; nCntWidth++)
	{
		//�O�l�O�l�p�[�g
		pIdx = SetIdxSwaingField(nCntWidth, pIdx);

		//�`�����ł�����p�[�g
		//�Ō�̃C���f�b�N�X�������̂ɂ������
		*pIdx = m_nBlockWidth + (m_nBlockWidth + 1) * nCntWidth;
		pIdx++;

		//���̎��̂Ɏ��̃��[�v�ōŏ��ɓ��鐔��������
		*pIdx = (m_nBlockWidth + 1) + (m_nBlockWidth + 1) * (nCntWidth + 1);
		pIdx++;
	}

	//�Ō�̃O�l�O�l�p�[�g
	SetIdxSwaingField(nCntWidth, pIdx);

	//�o�b�t�@�A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=================================
//�I��
//=================================
void CMeshField::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxbuff != nullptr)
	{
		m_pVtxbuff->Release();
		m_pVtxbuff = nullptr;
	}

	//�C���f�b�N�X�o�b�t�@�j��
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}

	//�������g�j��
	Release();
}

//=================================
//�X�V
//=================================
void CMeshField::Update(void)
{
}

//=================================
//�`��
//=================================
void CMeshField::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();						//�e�N�X�`���I�u�W�F�N�g�擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxbuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//�|���S���`��i�C���f�b�N�X���ꂽ��j
	int nPolyNum = ((((m_nBlockWidth + 1) * m_nBlockDepth * 2) + (2 * (m_nBlockDepth - 1))) - 2);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (m_nBlockWidth + 1) * (m_nBlockDepth + 1), 0, nPolyNum);
}

//=================================
//����
//=================================
CMeshField* CMeshField::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fDepth,
	const int nBlockWidth, const int nBlockDepth)
{
	CMeshField* pMeshField = nullptr;

	if (pMeshField == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pMeshField = new CMeshField;

		//�f�[�^�ݒ�
		pMeshField->m_pos = pos;
		pMeshField->m_rot = rot;
		pMeshField->m_fWidth = fWidth;
		pMeshField->m_fDepth = fDepth;
		pMeshField->m_nBlockWidth = nBlockWidth;
		pMeshField->m_nBlockDepth = nBlockDepth;

		//������
		pMeshField->Init();

		return pMeshField;
	}
	else
	{
		return nullptr;
	}
}

//========================
//�O�l�O�l�C���f�b�N�X�ݒ菈��
//========================
WORD* CMeshField::SetIdxSwaingField(int nCntWidth, WORD *pIdx)
{
	//�O�l�O�l�p�[�g
	for (int nCountHeight = 0; nCountHeight < (m_nBlockWidth + 1) * 2; nCountHeight++, pIdx++)
	{
		*pIdx = (m_nBlockWidth + 1) * ((nCountHeight % 2) ^ 0x1) + nCountHeight / 2 + (m_nBlockWidth + 1) * nCntWidth;
	}
	return pIdx;
}

//========================
//�����擾�i�Ζʁj
//========================
float CMeshField::GetHeight(D3DXVECTOR3 posNew)
{
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	VERTEX_3D *pVtx;	//�ݒ�p�|�C���^
	m_pVtxbuff->Lock(0, 0, (void **)&pVtx, 0);

	D3DXVECTOR3 dust;

	for (int cntZ = 0; cntZ < m_nBlockDepth; cntZ++)
	{
		for (int cntX = 0; cntX < m_nBlockWidth; cntX++)
		{
			int nVtx0 = cntZ * (m_nBlockDepth + 1) + cntX;
			int nVtx1 = cntZ * (m_nBlockDepth + 1) + cntX + 1;
			int nVtx2 = (cntZ + 1) * (m_nBlockDepth + 1) + cntX;
			int nVtx3 = (cntZ + 1) * (m_nBlockDepth + 1) + cntX + 1;

			if (D3DXVec3Cross(&dust, &(pVtx[nVtx3].pos - pVtx[nVtx2].pos), &(posNew - (pVtx[nVtx2].pos + m_pos)))->y <= 0.0f &&
				D3DXVec3Cross(&dust, &(pVtx[nVtx0].pos - pVtx[nVtx3].pos), &(posNew - (pVtx[nVtx3].pos + m_pos)))->y <= 0.0f &&
				D3DXVec3Cross(&dust, &(pVtx[nVtx2].pos - pVtx[nVtx0].pos), &(posNew - (pVtx[nVtx0].pos + m_pos)))->y <= 0.0f)
			{
				D3DXVECTOR3 vec1, vec2, nor;
				vec1 = pVtx[nVtx0].pos - pVtx[nVtx2].pos;
				vec2 = pVtx[nVtx3].pos - pVtx[nVtx2].pos;
				D3DXVec3Cross(&nor, &vec1, &vec2);
				D3DXVec3Normalize(&nor, &nor);
				if (nor.y != 0.0f)
				{
					return (-((posNew.x - (pVtx[nVtx2].pos.x + m_pos.x))*nor.x + (posNew.z - (pVtx[nVtx2].pos.z + m_pos.z))*nor.z) / nor.y) + pVtx[nVtx2].pos.y + m_pos.y;
				}
			}

			if (D3DXVec3Cross(&dust, &(pVtx[nVtx0].pos - pVtx[nVtx1].pos), &(posNew - (pVtx[nVtx1].pos + m_pos)))->y <= 0.0f &&
				D3DXVec3Cross(&dust, &(pVtx[nVtx3].pos - pVtx[nVtx0].pos), &(posNew - (pVtx[nVtx0].pos + m_pos)))->y <= 0.0f &&
				D3DXVec3Cross(&dust, &(pVtx[nVtx1].pos - pVtx[nVtx3].pos), &(posNew - (pVtx[nVtx3].pos + m_pos)))->y <= 0.0f)
			{
				D3DXVECTOR3 vec1, vec2, nor;
				vec1 = pVtx[nVtx3].pos - pVtx[nVtx1].pos;
				vec2 = pVtx[nVtx0].pos - pVtx[nVtx1].pos;
				D3DXVec3Cross(&nor, &vec1, &vec2);
				D3DXVec3Normalize(&nor, &nor);
				if (nor.y != 0.0f)
				{
					return (-((posNew.x - (pVtx[nVtx1].pos.x + m_pos.x))*nor.x + (posNew.z - (pVtx[nVtx1].pos.z + m_pos.z))*nor.z) / nor.y) + pVtx[nVtx1].pos.y + m_pos.y;
				}
			}
		}
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxbuff->Unlock();

	return 0.0f;
}