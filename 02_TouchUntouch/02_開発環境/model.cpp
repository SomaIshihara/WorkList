//======================================================
//
//���f������[model.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include <assert.h>

//=================================
//�R���X�g���N�^
//=================================
CModel::CModel()
{
	m_pos = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_posMotioned = CManager::VEC3_ZERO;
	m_rotMotioned = CManager::VEC3_ZERO;
	m_pParent = nullptr;
}

//=================================
//�f�X�g���N�^
//=================================
CModel::~CModel()
{
}

//========================
//����������
//========================
HRESULT CModel::Init(void)
{
	return S_OK;
}

//========================
//�I������
//========================
void CModel::Uninit(void)
{
	//���b�V���̔j��
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	//�}�e���A���̔j��
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	//�e�N�X�`���ԍ��j��
	if (m_pIdxtexture != nullptr)
	{
		delete[] m_pIdxtexture;
		m_pIdxtexture = nullptr;
	}
}

//========================
//�X�V����
//========================
void CModel::Update(void)
{
	//�������񉼂̒l������
	m_posMotioned = m_pos;
	m_rotMotioned = m_rot;
}

//========================
//�`�揈��
//========================
void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�擾
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();						//�e�N�X�`���I�u�W�F�N�g�擾
	D3DXMATRIX mtxRot, mtxTrans, mtxTexture;							//�v�Z�p
	D3DXMATRIX mtxParent;												//�e�̃}�g��
	D3DMATERIAL9 matDef;												//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;													//�}�e���A���f�[�^�ւ̃|�C���^

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//���f���擾
	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotMotioned.y, m_rotMotioned.x, m_rotMotioned.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, m_posMotioned.x, m_posMotioned.y, m_posMotioned.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�p�[�c�̐e�}�g���ݒ�
	if (m_pParent != nullptr)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//�p�[�c�̃}�g���Ɛe�}�g�����������킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�}�e���A���f�[�^�ւ̃|�C���^�擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMatModel; nCntMat++)
	{
		//�}�e���A���ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, pTexture->GetAddress(m_pIdxtexture[nCntMat]));

		//���f���`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//========================
//��������
//========================
CModel* CModel::Create(const char * pPath, const D3DXVECTOR3 posOffset, const D3DXVECTOR3 rotOffset)
{
	CModel* pModel = nullptr;

	if (pModel == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pModel = new CModel();

		//������
		pModel->Init();
		pModel->Load(pPath);
		pModel->m_pos = posOffset;
		pModel->m_rot = rotOffset;

		return pModel;
	}
	else
	{
		return nullptr;
	}
}

//========================
//�ǂݍ��ݏ���
//========================
HRESULT CModel::Load(const char* pPath)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�擾
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();						//�e�N�X�`���I�u�W�F�N�g�擾
	m_pIdxtexture = nullptr;											//�e�N�X�`���ԍ��|�C���^��nullptr�ɂ���

	if (SUCCEEDED(D3DXLoadMeshFromX(
		pPath,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		nullptr,
		&m_pBuffMat,
		nullptr,
		&m_dwNumMatModel,
		&m_pMesh)))
	{
		//�e�N�X�`���|�C���^�m��
		if (m_pIdxtexture == nullptr)
		{//nullptr
		 //�e�N�X�`���ԍ��z��m��
			m_pIdxtexture = new int[(int)m_dwNumMatModel];

			//�e�N�X�`���ǂݍ���
			D3DXMATERIAL* pMat;	//�}�e���A���|�C���^

								//�}�e���A�����ɑ΂���|�C���^�擾
			pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

			//�e�N�X�`���ǂݍ���
			for (int nCntTex = 0; nCntTex < (int)m_dwNumMatModel; nCntTex++)
			{
				m_pIdxtexture[nCntTex] = -1;
				if (pMat[nCntTex].pTextureFilename != nullptr)
				{//�e�N�X�`�������
				 //�e�N�X�`���ǂݍ���
					m_pIdxtexture[nCntTex] = pTexture->Regist(pMat[nCntTex].pTextureFilename);
				}
				else
				{//�Ȃ���
					m_pIdxtexture[nCntTex] = -1;	//�e�N�X�`���擾����nullptr�ɂȂ�悤�ɂ���
				}
			}
		}
		else
		{//��������
			assert(false);
		}
	}

	return S_OK;
}
