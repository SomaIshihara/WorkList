//======================================================
//
//X�t�@�C�����f���̃w�b�_[xmodel.h]
//Author:�Ό��D�n
//
//======================================================
#include "xmodel.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//�ÓI�����o�ϐ�
CXModel* CXModel::m_pTop = nullptr;
CXModel* CXModel::m_pCur = nullptr;
int CXModel::m_nNumAll = 0;

//=================================
//�R���X�g���N�^
//=================================
CXModel::CXModel()
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
	m_bExclusion = false;		//�����Ă�
	m_nNumAll++;
}

//=================================
//�f�X�g���N�^
//=================================
CXModel::~CXModel()
{
}

//=================================
//�ǂݍ���
//=================================
CXModel* CXModel::Load(const char* pPath)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�擾
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();						//�e�N�X�`���I�u�W�F�N�g�擾

	CXModel* pObject = m_pTop;	//�擪������

	while (pObject != nullptr)
	{//���O���m
		CXModel* pObjectNext = pObject->m_pNext;	//���̃I�u�W�F�ۑ�

		if (pObject->m_pFilePath != nullptr && strcmp(pObject->m_pFilePath, pPath) == 0)
		{
			return pObject;
		}

		pObject = pObjectNext;	//��������
	}

	pObject = new CXModel;
	pObject->m_pIdxtexture = nullptr;	//�e�N�X�`���ԍ��|�C���^��nullptr�ɂ���

	if (SUCCEEDED(D3DXLoadMeshFromX(
		pPath,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		nullptr,
		&pObject->m_pBuffMat,
		nullptr,
		&pObject->m_dwNumMatModel,
		&pObject->m_pMesh)))
	{
		//�e�N�X�`���|�C���^�m��
		if (pObject->m_pIdxtexture == nullptr)
		{//nullptr
		 //�e�N�X�`���ԍ��z��m��
			pObject->m_pIdxtexture = new int[(int)pObject->m_dwNumMatModel];

			//�����蔻�萶��
			int nNumVtx;		//���_��
			DWORD dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y

			//���_�����擾
			nNumVtx = pObject->m_pMesh->GetNumVertices();

			//���_�t�H�[�}�b�g
			dwSizeFVF = D3DXGetFVFVertexSize(pObject->m_pMesh->GetFVF());

			//���_�o�b�t�@���b�N
			BYTE *pVtxBuff;		//���_�o�b�t�@�|�C���^
			pObject->m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void **)&pVtxBuff);

			//�ŏ������S�������
			D3DXVECTOR3 vtx = *(D3DXVECTOR3 *)pVtxBuff;

			D3DXVECTOR3 vtxMax = vtx;
			D3DXVECTOR3 vtxMin = vtx;

			pVtxBuff += dwSizeFVF;

			for (int nCntVtx = 1; nCntVtx < nNumVtx; nCntVtx++, pVtxBuff += dwSizeFVF)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3 *)pVtxBuff;

				if (vtxMax.x < vtx.x)
				{
					vtxMax.x = vtx.x;
				}
				if (vtxMax.y < vtx.y)
				{
					vtxMax.y = vtx.y;
				}
				if (vtxMax.z < vtx.z)
				{
					vtxMax.z = vtx.z;
				}
				if (vtxMin.x > vtx.x)
				{
					vtxMin.x = vtx.x;
				}
				if (vtxMin.y > vtx.y)
				{
					vtxMin.y = vtx.y;
				}
				if (vtxMin.z > vtx.z)
				{
					vtxMin.z = vtx.z;
				}
			}

			//�ݒ�
			pObject->m_collision.SetVtx(vtxMin, vtxMax);

			//���_�o�b�t�@�A�����b�N
			pObject->m_pMesh->UnlockVertexBuffer();

			//�e�N�X�`���ǂݍ���
			D3DXMATERIAL* pMat;	//�}�e���A���|�C���^

			//�}�e���A�����ɑ΂���|�C���^�擾
			pMat = (D3DXMATERIAL*)pObject->m_pBuffMat->GetBufferPointer();

			//�e�N�X�`���ǂݍ���
			for (int nCntTex = 0; nCntTex < (int)pObject->m_dwNumMatModel; nCntTex++)
			{
				pObject->m_pIdxtexture[nCntTex] = -1;
				if (pMat[nCntTex].pTextureFilename != nullptr)
				{//�e�N�X�`�������
				 //�e�N�X�`���ǂݍ���
					pObject->m_pIdxtexture[nCntTex] = pTexture->Regist(pMat[nCntTex].pTextureFilename);
				}
				else
				{//�Ȃ���
					pObject->m_pIdxtexture[nCntTex] = -1;	//�e�N�X�`���擾����nullptr�ɂȂ�悤�ɂ���
				}
			}
		}
		else
		{//��������
			assert(false);
		}

		//�t�@�C���p�X�ۑ�
		pObject->m_pFilePath = new char[strlen(pPath)+1];
		strcpy(pObject->m_pFilePath, pPath);

		//�ԍ��Ԃ�
		return pObject;
	}
	else
	{
		delete pObject;
		m_nNumAll--;
		return nullptr;
	}

	return nullptr;
}

//=================================
//�j��
//=================================
void CXModel::Unload(void)
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

	//�t�@�C���p�X�j��
	if (m_pFilePath != nullptr)
	{
		delete[] m_pFilePath;
		m_pFilePath = nullptr;
	}

	//����	
	delete this;	//�������g�j��
	m_nNumAll--;	//�������炷
}

//=================================
//�S�j��
//=================================
void CXModel::UnloadAll(void)
{
	CXModel* pObject = m_pTop;	//�擪������

	while (pObject != nullptr)
	{//�Ō���܂ŉ񂵑�����
		CXModel* pObjectNext = pObject->m_pNext;	//���̃I�u�W�F�ۑ�

		pObject->Unload();	//�����

		pObject = pObjectNext;	//��������
	}
}