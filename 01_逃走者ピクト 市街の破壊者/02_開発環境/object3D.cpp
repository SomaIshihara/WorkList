//======================================================
//
//�I�u�W�F�N�g�i3D�j����[object3D.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"
#include "object3D.h"
#include <assert.h>

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	//�N���A
	m_pVtxbuff = nullptr;
	m_nIdxTexture = -1;
	m_pos = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h �ʒu�����j
//=================================
CObject3D::CObject3D(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fDepth, int nPriority) : CObject(nPriority)
{
	//�N���A
	m_pVtxbuff = nullptr;
	m_nIdxTexture = -1;
	m_pos = pos;
	m_rot = rot;
	m_fWidth = fWidth;
	m_fDepth = fDepth;
}

//=================================
//�f�X�g���N�^
//=================================
CObject3D::~CObject3D()
{
}

//========================
//����������
//========================
HRESULT CObject3D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�擾

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxbuff,
		nullptr)))
	{
		return E_FAIL;
	}

	////���F�e�N�X�`���ǂݍ���
	//CTexture* pTexture = CManager::GetTexture();
	//m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\icon32.png");

	VERTEX_3D *pVtx;

	//�o�b�t�@���b�N
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	m_pVtxbuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�i���΍��W�j
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth * 0.5f, 0.0f, m_fDepth * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth * 0.5f, 0.0f, m_fDepth * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth * 0.5f, 0.0f, -m_fDepth * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth * 0.5f, 0.0f, -m_fDepth * 0.5f);

	//�@���x�N�g��
	D3DXVECTOR3 vec1 = pVtx[1].pos - pVtx[0].pos;
	D3DXVECTOR3 vec2 = pVtx[2].pos - pVtx[0].pos;
	D3DXVec3Cross(&pVtx[0].nor, &vec1, &vec2);
	D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

	vec1 = pVtx[2].pos - pVtx[3].pos;
	vec2 = pVtx[1].pos - pVtx[3].pos;
	D3DXVec3Cross(&pVtx[3].nor, &vec1, &vec2);
	D3DXVec3Normalize(&pVtx[3].nor, &pVtx[3].nor);
	//������
	/*D3DXVECTOR3 vec1 = pVtx[2].pos - pVtx[0].pos;
	D3DXVECTOR3 vec2 = pVtx[1].pos - pVtx[0].pos;
	pVtx[0].nor = D3DXVECTOR3(
		(vec1.z * vec2.y) - (vec1.y * vec2.z),
		(vec1.z * vec2.x) - (vec1.x * vec2.z),
		(vec1.y * vec2.x) - (vec1.x * vec2.y)
	);
	D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);


	vec1 = pVtx[1].pos - pVtx[3].pos;
	vec2 = pVtx[2].pos - pVtx[3].pos;
	pVtx[3].nor = D3DXVECTOR3(
		(vec1.z * vec2.y) - (vec1.y * vec2.z),
		(vec1.z * vec2.x) - (vec1.x * vec2.z),
		(vec1.y * vec2.x) - (vec1.x * vec2.y)
	);
	D3DXVec3Normalize(&pVtx[3].nor, &pVtx[3].nor);*/

	pVtx[1].nor = (pVtx[0].nor + pVtx[1].nor);
	D3DXVec3Normalize(&pVtx[1].nor, &pVtx[1].nor);

	pVtx[2].nor = (pVtx[0].nor + pVtx[1].nor);
	D3DXVec3Normalize(&pVtx[2].nor, &pVtx[2].nor);

	//�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxbuff->Unlock();

	return S_OK;
}

//========================
//�I������
//========================
void CObject3D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxbuff != nullptr)
	{
		m_pVtxbuff->Release();
		m_pVtxbuff = nullptr;
	}

	//�������g�j��
	Release();
}

//========================
//�X�V����
//========================
void CObject3D::Update(void)
{
	
}

//========================
//�`�揈��
//========================
void CObject3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�擾
	CTexture* pTexture = CManager::GetTexture();						//�e�N�X�`���I�u�W�F�N�g�擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p

	CManager::GetRenderer()->SetEnableAlplaTest(true);
	CManager::GetRenderer()->SetEnableZTest(false);

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

	//�`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	CManager::GetRenderer()->SetEnableAlplaTest(false);
	CManager::GetRenderer()->SetEnableZTest(true);
}

//========================
//��������
//========================
CObject3D* CObject3D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fDepth, int nPriority)
{
	CObject3D* pObj3D = nullptr;

	if (pObj3D == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pObj3D = new CObject3D(pos, rot, fWidth, fDepth, nPriority);

		//������
		pObj3D->Init();

		return pObj3D;
	}
	else
	{
		return nullptr;
	}
}

//========================
//�F�ݒ�
//========================
HRESULT CObject3D::SetCol(const D3DXCOLOR col)
{
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	VERTEX_3D *pVtx;	//�ݒ�p�|�C���^
	if (FAILED(m_pVtxbuff->Lock(0, 0, (void **)&pVtx, 0)))
	{
		return E_FAIL;
	}

	//���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N
	if (FAILED(m_pVtxbuff->Unlock()))
	{
		return E_FAIL;
	}

	return S_OK;
}

float CObject3D::GetHeight(D3DXVECTOR3 pos)
{
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	VERTEX_3D *pVtx;	//�ݒ�p�|�C���^
	m_pVtxbuff->Lock(0, 0, (void **)&pVtx, 0);

	D3DXVECTOR3 dust;
	
	if (D3DXVec3Cross(&dust, &(pVtx[1].pos - pVtx[3].pos), &(pos - pVtx[3].pos))->y <= 0.0f &&
		D3DXVec3Cross(&dust, &(pVtx[2].pos - pVtx[1].pos), &(pos - pVtx[1].pos))->y <= 0.0f &&
		D3DXVec3Cross(&dust, &(pVtx[3].pos - pVtx[2].pos), &(pos - pVtx[2].pos))->y <= 0.0f)
	{
		D3DXVECTOR3 vec1, vec2, nor;
		vec1 = pVtx[2].pos - pVtx[3].pos;
		vec2 = pVtx[1].pos - pVtx[3].pos;
		D3DXVec3Cross(&nor, &vec1, &vec2);
		if (nor.y != 0.0f)
		{
			return (-((pos.x - pVtx[3].pos.x)*nor.x + (pos.z - pVtx[3].pos.z)*nor.z) / nor.y) + pVtx[3].pos.y;
		}
	}

	if (D3DXVec3Cross(&dust, &(pVtx[2].pos - pVtx[0].pos), &(pos - pVtx[0].pos))->y <= 0.0f &&
		D3DXVec3Cross(&dust, &(pVtx[1].pos - pVtx[2].pos), &(pos - pVtx[2].pos))->y <= 0.0f &&
		D3DXVec3Cross(&dust, &(pVtx[0].pos - pVtx[1].pos), &(pos - pVtx[1].pos))->y <= 0.0f)
	{
		D3DXVECTOR3 vec1, vec2, nor;
		vec1 = pVtx[1].pos - pVtx[0].pos;
		vec2 = pVtx[2].pos - pVtx[0].pos;
		D3DXVec3Cross(&nor, &vec1, &vec2);
		if (nor.y != 0.0f)
		{
			return (-((pos.x - pVtx[0].pos.x)*nor.x + (pos.z - pVtx[0].pos.z)*nor.z) / nor.y) + pVtx[0].pos.y;
		}
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxbuff->Unlock();

	return 0.0f;
}