//======================================================
//
//���b�V���t�B�[���h����[meshField.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "meshField.h"
#include "../../_Core/manager/manager.h"
#include "../../_Core/renderer/renderer.h"
#include "../../_Core/texture/texture.h"
#include "../../_Core/utility/Utility.h"
#include "../../_Core/debugproc/debugproc.h"
#include <vector>

using namespace std;

//�ÓI�����o�ϐ�
CMeshField* CMeshField::m_pTop = nullptr;
CMeshField* CMeshField::m_pCur = nullptr;
int CMeshField::m_nNumAll = 0;

//=================================
//�R���X�g���N�^
//=================================
CMeshField::CMeshField(int nPriority) : CObject(nPriority)
{
	//�l�N���A
	m_pos = IS_Utility::VEC3_ZERO;
	m_rot = IS_Utility::VEC3_ZERO;
	m_fWidth = 0.0f;
	m_fDepth = 0.0f;
	m_nBlockWidth = 0;
	m_nBlockDepth = 0;
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pVtxbuff = nullptr;
	m_pIdxBuff = nullptr;
	m_nIdxTexture = -1;

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
	CObject::SetDrawType(CObject::DRAWTYPE::DRAW_MESH);
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
	//�o�b�t�@����
	CreateBuff();

	//���_�ݒ�
	SetVtxBuff();

	//�C���f�b�N�X�o�b�t�@�ݒ�
	SetIdxBuff();

	return S_OK;
}

//=================================
//�I��
//=================================
void CMeshField::Uninit(void)
{
	//�o�b�t�@�j��
	ReleaseBuff();

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
	CManager* pManager = CManager::GetInstance();
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
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
	CTexture* pTexture = nullptr;
	pTexture = pManager->GetTexture();

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
		//�I�u�W�F�N�g�̐���
		pMeshField = new CMeshField;

		//������
		pMeshField->m_pos = pos;
		pMeshField->m_rot = rot;
		pMeshField->m_fWidth = fWidth;
		pMeshField->m_fDepth = fDepth;
		pMeshField->m_nBlockWidth = nBlockWidth;
		pMeshField->m_nBlockDepth = nBlockDepth;
		pMeshField->Init();

		return pMeshField;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//�o�b�t�@����
//=================================
void CMeshField::CreateBuff(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

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
}

//=================================
//�o�b�t�@�j��
//=================================
void CMeshField::ReleaseBuff(void)
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
}

//=================================
//���_�ݒ�
//=================================
void CMeshField::SetVtxBuff(void)
{
	//���_�̊e���ݒ�
	SetVtxPos();
	SetVtxCol();
	SetVtxTex();
	SetVtxNor();
}

//=================================
//���_���W�̐ݒ�
//=================================
void CMeshField::SetVtxPos(void)
{
	VERTEX_3D* pVtx;

	//�o�b�t�@���b�N
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	m_pVtxbuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W+�e�N�X�`�����W
	for (int nCount = 0; nCount < (m_nBlockWidth + 1) * (m_nBlockDepth + 1); nCount++)
	{
		//���_���W�i���΍��W�j
		pVtx[nCount].pos = D3DXVECTOR3(m_fWidth * (((float)(nCount % (m_nBlockWidth + 1)) - 0.5f * (m_nBlockWidth))),
			0.0f, -m_fDepth * (((float)(nCount / (m_nBlockWidth + 1))) - 0.5f * (m_nBlockDepth)));
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxbuff->Unlock();
}

//=================================
//���_�J���[�̐ݒ�
//=================================
void CMeshField::SetVtxCol(void)
{
	VERTEX_3D* pVtx;

	//�o�b�t�@���b�N
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	m_pVtxbuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W+�e�N�X�`�����W
	for (int nCount = 0; nCount < (m_nBlockWidth + 1) * (m_nBlockDepth + 1); nCount++)
	{
		//�J���[
		pVtx[nCount].col = m_color;
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxbuff->Unlock();
}

//=================================
//���_�̃e�N�X�`�����W�ݒ�
//=================================
void CMeshField::SetVtxTex(void)
{
	VERTEX_3D* pVtx;

	//�o�b�t�@���b�N
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	m_pVtxbuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W+�e�N�X�`�����W
	for (int nCount = 0; nCount < (m_nBlockWidth + 1) * (m_nBlockDepth + 1); nCount++)
	{
		//�e�N�X�`�����W
		pVtx[nCount].tex = D3DXVECTOR2(((float)(nCount % (m_nBlockWidth + 1))), ((float)(nCount / (m_nBlockWidth + 1))));
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxbuff->Unlock();
}

//=================================
//���_�̖@���ݒ�
//=================================
void CMeshField::SetVtxNor(void)
{
	VERTEX_3D* pVtx;

	//�o�b�t�@���b�N
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	m_pVtxbuff->Lock(0, 0, (void**)&pVtx, 0);

	vector<D3DXVECTOR3>* pNor = new vector<D3DXVECTOR3>[(m_nBlockWidth + 1) * (m_nBlockDepth + 1)];

	for (int cntZ = 0; cntZ < m_nBlockDepth; cntZ++)
	{
		for (int cntX = 0; cntX < m_nBlockWidth; cntX++)
		{
			D3DXVECTOR3 nor0, nor1, nor2, nor3;
			D3DXVECTOR3 vec0, vec1;
			int nVtx0 = cntZ * (m_nBlockWidth + 1) + cntX;
			int nVtx1 = cntZ * (m_nBlockWidth + 1) + cntX + 1;
			int nVtx2 = (cntZ + 1) * (m_nBlockWidth + 1) + cntX;
			int nVtx3 = (cntZ + 1) * (m_nBlockWidth + 1) + cntX + 1;

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
		D3DXVECTOR3 nor = IS_Utility::VEC3_ZERO;

		//�S�@���𑫂�
		for (unsigned int cntNor = 0; cntNor < pNor[nCount].size(); cntNor++)
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
}

//=================================
//�C���f�b�N�X�ݒ�
//=================================
void CMeshField::SetIdxBuff(void)
{
	WORD *pIdx;	//�C���f�b�N�X���ւ̃|�C���^
	int nCntWidth;	//�C���f�b�N�X�J�E���^

	//�C���f�b�N�X�o�b�t�@�ݒ�
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
//����Ă���ʂƖ@���擾����
//========================
bool CMeshField::GetLanding(D3DXVECTOR3 posOld, D3DXVECTOR3 poslanding, D3DXVECTOR3* pOutposVtx, D3DXVECTOR3* pOutNor, D3DXVECTOR3* pOutUpVec)
{
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	VERTEX_3D* pVtx;	//�ݒ�p�|�C���^
	m_pVtxbuff->Lock(0, 0, (void**)&pVtx, 0);
	bool bLand = false;
	float fLengthNear = FLT_MAX;
	D3DXVECTOR3 posNearVtx = IS_Utility::VEC3_ZERO;
	D3DXVECTOR3 norNearVtx = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 dust;

	for (int cntZ = 0; cntZ < m_nBlockDepth; cntZ++)
	{
		for (int cntX = 0; cntX < m_nBlockWidth; cntX++)
		{
			int nVtx0 = cntZ * (m_nBlockWidth + 1) + cntX;
			int nVtx1 = cntZ * (m_nBlockWidth + 1) + cntX + 1;
			int nVtx2 = (cntZ + 1) * (m_nBlockWidth + 1) + cntX;
			int nVtx3 = (cntZ + 1) * (m_nBlockWidth + 1) + cntX + 1;
			D3DXVECTOR3 posVtx[4];
			posVtx[0] = IS_Utility::RotateVtx(pVtx[nVtx0].pos, m_rot, m_pos);
			posVtx[1] = IS_Utility::RotateVtx(pVtx[nVtx1].pos, m_rot, m_pos);
			posVtx[2] = IS_Utility::RotateVtx(pVtx[nVtx2].pos, m_rot, m_pos);
			posVtx[3] = IS_Utility::RotateVtx(pVtx[nVtx3].pos, m_rot, m_pos);

			if (D3DXVec3Cross(&dust, &(posVtx[3] - posVtx[2]), &(poslanding - (posVtx[2])))->y <= 0.0f &&
				D3DXVec3Cross(&dust, &(posVtx[0] - posVtx[3]), &(poslanding - (posVtx[3])))->y <= 0.0f &&
				D3DXVec3Cross(&dust, &(posVtx[2] - posVtx[0]), &(poslanding - (posVtx[0])))->y <= 0.0f)
			{
				D3DXVECTOR3 vec1, vec2, nor;
				vec1 = posVtx[0] - posVtx[2];
				vec2 = posVtx[3] - posVtx[2];
				D3DXVec3Cross(&nor, &vec1, &vec2);
				D3DXVec3Normalize(&nor, &nor);
				if (nor.y != 0.0f)
				{
					float fLength = fabsf(posOld.y - posVtx[2].y);
					if (fLengthNear > fLength)
					{
						posNearVtx = posVtx[2];
						norNearVtx = nor;
						fLengthNear = fLength;
						bLand = true;

						if (pOutUpVec != nullptr)
						{
							D3DXVec3Normalize(pOutUpVec, &(posVtx[0] - posVtx[2]));
						}
					}
				}
			}

			if (D3DXVec3Cross(&dust, &(posVtx[0] - posVtx[1]), &(poslanding - (posVtx[1])))->y <= 0.0f &&
				D3DXVec3Cross(&dust, &(posVtx[3] - posVtx[0]), &(poslanding - (posVtx[0])))->y <= 0.0f &&
				D3DXVec3Cross(&dust, &(posVtx[1] - posVtx[3]), &(poslanding - (posVtx[3])))->y <= 0.0f)
			{
				D3DXVECTOR3 vec1, vec2, nor;
				vec1 = posVtx[3] - posVtx[1];
				vec2 = posVtx[0] - posVtx[1];
				D3DXVec3Cross(&nor, &vec1, &vec2);
				D3DXVec3Normalize(&nor, &nor);
				if (nor.y != 0.0f)
				{
					float fLength = fabsf(posOld.y - posVtx[1].y);
					if (fLengthNear > fLength)
					{
						posNearVtx = posVtx[1];
						norNearVtx = nor;
						fLengthNear = fLength;
						bLand = true;

						if (pOutUpVec != nullptr)
						{
							D3DXVec3Normalize(pOutUpVec, &(posVtx[1] - posVtx[3]));
						}
					}
				}
			}
		}
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxbuff->Unlock();

	//���
	if (pOutposVtx != nullptr)
	{
		*pOutposVtx = posNearVtx;
	}
	if (pOutNor != nullptr)
	{
		*pOutNor = norNearVtx;
	}

	return bLand;
}

//========================
//���O����
//========================
void CMeshField::Exclusion(void)
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
}

//========================
//�����擾
//========================
float CMeshField::GetHeight(D3DXVECTOR3 posOld, D3DXVECTOR3 posNew)
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
//�����Ă���Ƃ���̊p�x�擾
//========================
D3DXVECTOR3 CMeshField::GetLandingRot(D3DXVECTOR3 posOld, D3DXVECTOR3 posLanding, float rotY)
{
	D3DXVECTOR3 posVtx, nor;
	if (GetLanding(posOld, posLanding, &posVtx, &nor) == true)
	{
		D3DXVECTOR3 rot;
		rot = IS_Utility::RotateVtx(nor, D3DXVECTOR3(0.5f * D3DX_PI, rotY, 0.0f), IS_Utility::VEC3_ZERO);
		return rot;
	}
	else
	{
		return IS_Utility::VEC3_ZERO;
	}
}

//========================
//�����擾(ALL)
//========================
float CMeshField::GetHeightAll(D3DXVECTOR3 posOld, D3DXVECTOR3 posNew)
{
	CMeshField* pMeshField = m_pTop;
	CMeshField* pMeshFieldNear = nullptr;
	float fLengthNear = FLT_MAX;
	D3DXVECTOR3 posVtxNear, norNear;

	while (pMeshField != nullptr)
	{
		D3DXVECTOR3 posVtx, nor;
		if (pMeshField->GetLanding(posOld, posNew, &posVtx, &nor) == true)
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
		return pMeshFieldNear->GetHeight(posOld, posNew);
	}
	return -FLT_MAX;
}

//========================
//�����Ă���Ƃ���̊p�x�擾(ALL)
//========================
D3DXVECTOR3 CMeshField::GetLandingRotAll(D3DXVECTOR3 posOld, D3DXVECTOR3 posLanding, float rotY)
{
	CMeshField* pMeshField = m_pTop;
	CMeshField* pMeshFieldNear = nullptr;
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
		return pMeshFieldNear->GetLandingRot(posOld, posLanding, rotY);
	}
	return IS_Utility::VEC3_ZERO;
}