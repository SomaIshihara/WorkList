//======================================================
//
//���b�V���󏈗�[meshsky.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "meshsky.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include <vector>

using namespace std;

//=================================
//�R���X�g���N�^
//=================================
CMeshSky::CMeshSky()
{
	//�l�N���A
	m_pos = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fRadius = CManager::FLOAT_ZERO;
	m_nBlockVertical = CManager::INT_ZERO;
	m_nBlockHorizontal = CManager::INT_ZERO;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h�j
//=================================
CMeshSky::CMeshSky(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fRadius,
	const int nBlockWidth, const int nBlockDepth)
{
	//�l�ݒ�
	m_pos = pos;
	m_rot = rot;
	m_fRadius = fRadius;
	m_nBlockVertical = nBlockWidth;
	m_nBlockHorizontal = nBlockDepth;
}

//=================================
//�f�X�g���N�^
//=================================
CMeshSky::~CMeshSky()
{
}

//=================================
//������
//=================================
HRESULT CMeshSky::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Block_R_01.png");

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((m_nBlockVertical) * (m_nBlockHorizontal + 1) + 2),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxbuff,
		nullptr);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (m_nBlockHorizontal + 2),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuffTop,
		nullptr);

	int nIdxNum = (((m_nBlockVertical + 1) * m_nBlockHorizontal * 2) + (2 * (m_nBlockHorizontal - 1)));
	pDevice->CreateIndexBuffer(sizeof(WORD) * nIdxNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuffMiddle,
		nullptr);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (m_nBlockHorizontal + 2),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuffBottom,
		nullptr);

	VERTEX_3D *pVtx;

	//�o�b�t�@���b�N
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	m_pVtxbuff->Lock(0, 0, (void **)&pVtx, 0);

	//�㕔
	pVtx[0].pos = D3DXVECTOR3(0.0f, m_fRadius, 0.0f);
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	//���_���W+�e�N�X�`�����W
	for (int cntV = 0; cntV < m_nBlockVertical; cntV++)
	{
		float fAngleV = (1.0f * D3DX_PI) * ((float)(cntV + 1) / (m_nBlockVertical + 1));
		float fTexV = (1.0 / (m_nBlockVertical + 2)) * cntV;

		for (int cntH = 0; cntH < m_nBlockHorizontal + 1; cntH++)
		{
			float fAngleH = (2.0f * D3DX_PI) * ((float)cntH / (m_nBlockHorizontal));
			float fTexU = (1.0 / (m_nBlockHorizontal + 1)) * cntH;
			int cnt = cntV * (m_nBlockHorizontal + 1) + cntH + 1;

			pVtx[cnt].pos = D3DXVECTOR3(sinf(fAngleH) * sinf(fAngleV) * m_fRadius, cosf(fAngleV) * m_fRadius, cosf(fAngleH) * sinf(fAngleV) * m_fRadius);
			pVtx[cnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[cnt].tex = D3DXVECTOR2(fTexU, fTexV);
			pVtx[cnt].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
		}
	}

	//����
	int nLastVtx = (m_nBlockVertical) * (m_nBlockHorizontal + 1) + 1;
	pVtx[nLastVtx].pos = D3DXVECTOR3(0.0f, -m_fRadius, 0.0f);
	pVtx[nLastVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[nLastVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[nLastVtx].tex = D3DXVECTOR2(0.5f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxbuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�ݒ�
	WORD *pIdx;	//�C���f�b�N�X���ւ̃|�C���^
	int nCntWidth;	//�C���f�b�N�X�J�E���^

	//�㕔�o�b�t�@���b�N
	m_pIdxBuffTop->Lock(0, 0, (void **)&pIdx, 0);

	for (int cnt = 0; cnt < m_nBlockHorizontal + 1; cnt++)
	{
		pIdx[cnt] = cnt;
	}
	pIdx[m_nBlockHorizontal + 1] = 1;

	//�㕔�o�b�t�@�A�����b�N
	m_pIdxBuffTop->Unlock();

	//�o�b�t�@���b�N
	m_pIdxBuffMiddle->Lock(0, 0, (void **)&pIdx, 0);

	for (nCntWidth = 0; nCntWidth < m_nBlockHorizontal - 1; nCntWidth++)
	{
		//�O�l�O�l�p�[�g
		pIdx = SetIdxSwaingField(nCntWidth, pIdx);

		//�`�����ł�����p�[�g
		//�Ō�̃C���f�b�N�X�������̂ɂ������
		*pIdx = *(pIdx - 1);
		pIdx++;

		//���̎��̂Ɏ��̃��[�v�ōŏ��ɓ��鐔��������
		*pIdx = (m_nBlockVertical + 1) + (m_nBlockVertical + 1) * (nCntWidth + 1) + 1;
		pIdx++;
	}

	//�Ō�̃O�l�O�l�p�[�g
	SetIdxSwaingField(nCntWidth, pIdx);

	//�o�b�t�@�A�����b�N
	m_pIdxBuffMiddle->Unlock();

	//�����o�b�t�@���b�N
	m_pIdxBuffBottom->Lock(0, 0, (void **)&pIdx, 0);

	int nVtxNum = (m_nBlockVertical) * (m_nBlockHorizontal + 1) + 2;

	for (int cnt = 0; cnt < m_nBlockHorizontal + 1; cnt++)
	{
		pIdx[cnt] = nVtxNum - cnt - 1;
	}
	pIdx[m_nBlockHorizontal + 1] = nVtxNum - 2;

	//�����o�b�t�@�A�����b�N
	m_pIdxBuffBottom->Unlock();

	return S_OK;
}

//=================================
//�I��
//=================================
void CMeshSky::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxbuff != nullptr)
	{
		m_pVtxbuff->Release();
		m_pVtxbuff = nullptr;
	}

	//�C���f�b�N�X�o�b�t�@�j��
	if (m_pIdxBuffMiddle != nullptr)
	{
		m_pIdxBuffMiddle->Release();
		m_pIdxBuffMiddle = nullptr;
	}

	//�������g�j��
	Release();
}

//=================================
//�X�V
//=================================
void CMeshSky::Update(void)
{
}

//=================================
//�`��
//=================================
void CMeshSky::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	CTexture* pTexture = CManager::GetTexture();						//�e�N�X�`���I�u�W�F�N�g�擾
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

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//���ʃJ�����O��ON
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	//�㕔
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuffTop);

	//�|���S���`��i�C���f�b�N�X���ꂽ��j
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN, 0, 0, (m_nBlockHorizontal + 1), 0, (m_nBlockHorizontal));

	//����
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuffBottom);

	//�|���S���`��i�C���f�b�N�X���ꂽ��j
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN, 0, 0, (m_nBlockHorizontal + 1), 0, (m_nBlockHorizontal));

	//���ʂ̃J�����O���[�h�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//����
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuffMiddle);

	//�|���S���`��i�C���f�b�N�X���ꂽ��j
	int nPolyNum = (((m_nBlockVertical * m_nBlockHorizontal * 2) + (2 * (m_nBlockHorizontal - 1)))) - 2;
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (m_nBlockVertical - 1) * (m_nBlockHorizontal + 1) + m_nBlockHorizontal, 0, nPolyNum);
}

//=================================
//����
//=================================
CMeshSky* CMeshSky::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fRadius, const int nBlockWidth, const int nBlockDepth)
{
	CMeshSky* pMeshField = nullptr;

	if (pMeshField == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pMeshField = new CMeshSky(pos, rot, fRadius, nBlockWidth, nBlockDepth);

		//������
		pMeshField->Init();

		pMeshField->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\sky000.png"));

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
WORD* CMeshSky::SetIdxSwaingField(int nCntWidth, WORD *pIdx)
{
	//�O�l�O�l�p�[�g
	for (int nCountHeight = 0; nCountHeight < (m_nBlockVertical + 1) * 2; nCountHeight++, pIdx++)
	{
		*pIdx = (m_nBlockVertical + 1) * ((nCountHeight % 2) ^ 0x1) + nCountHeight / 2 + (m_nBlockVertical + 1) * nCntWidth + 1;
	}
	return pIdx;
}

float CMeshSky::GetHeight(D3DXVECTOR3 posNew)
{
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	VERTEX_3D *pVtx;	//�ݒ�p�|�C���^
	m_pVtxbuff->Lock(0, 0, (void **)&pVtx, 0);

	D3DXVECTOR3 dust;

	for (int cntZ = 0; cntZ < m_nBlockHorizontal; cntZ++)
	{
		for (int cntX = 0; cntX < m_nBlockVertical; cntX++)
		{
			int nVtx0 = cntZ * (m_nBlockHorizontal + 1) + cntX;
			int nVtx1 = cntZ * (m_nBlockHorizontal + 1) + cntX + 1;
			int nVtx2 = (cntZ + 1) * (m_nBlockHorizontal + 1) + cntX;
			int nVtx3 = (cntZ + 1) * (m_nBlockHorizontal + 1) + cntX + 1;

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