//======================================================
//
//��������[building.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "building.h"
#include "renderer.h"
#include "texture.h"
#include "objectX.h"
#include "picto.h"
#include "score.h"
#include "xmodel.h"
#include "koban.h"
#include "policemanager.h"
#include <stdio.h>
#include <assert.h>

//�}�N��
#define BUILDING_DAMAGE_ALPHA	(0.65f)	//�������_���[�W��H��������̐ԐF�̋�ő�l
#define BUILDING_DAMAGE_TIME	(60)	//�Ԃ����鎞��

//�ÓI�����o�ϐ�
CBuilding* CBuilding::m_apBuilding[MAX_OBJ];
int CBuilding::m_nNumAll = 0;

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CBuilding::CBuilding()
{
	for (int cnt = 0; cnt < MAX_OBJ; cnt++)
	{//���ׂĊm�F
		if (m_apBuilding[cnt] == nullptr)
		{//�����
			m_apBuilding[cnt] = this;	//�������g�̃|�C���^��o�^
			m_nID = cnt;	//ID�o����
			m_nNumAll++;	//�������₷
			break;
		}
	}
	m_pos = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fWidth = CManager::FLOAT_ZERO;
	m_fHeight = CManager::FLOAT_ZERO;
	m_fDepth = CManager::FLOAT_ZERO;
	m_nEndurance = CManager::INT_ZERO;

	//�p�����[�^
	m_bUnique = false;
	m_nLv = CManager::INT_ZERO;
	m_fSigValue = CManager::FLOAT_ZERO;
	m_nPowValue = CManager::INT_ZERO;
	m_fSigEndurance = CManager::FLOAT_ZERO;
	m_nPowEndurance = CManager::INT_ZERO;
	m_nExp = CManager::INT_ZERO;
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h�j
//=================================
CBuilding::CBuilding(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, CXModel* pModel) : CObject(PRIORITY_DEFMM)
{
	for (int cnt = 0; cnt < MAX_OBJ; cnt++)
	{//���ׂĊm�F
		if (m_apBuilding[cnt] == nullptr)
		{//�����
			m_apBuilding[cnt] = this;	//�������g�̃|�C���^��o�^
			m_nID = cnt;	//ID�o����
			m_nNumAll++;	//�������₷
			break;
		}
	}
	m_pos = pos;
	m_rot = rot;
	m_fWidth = CManager::FLOAT_ZERO;
	m_fHeight = CManager::FLOAT_ZERO;
	m_fDepth = CManager::FLOAT_ZERO;
	m_pModel = pModel;

	//�p�����[�^
	m_bUnique = false;
	m_nLv = CManager::INT_ZERO;
	m_fSigValue = CManager::FLOAT_ZERO;
	m_nPowValue = CManager::INT_ZERO;
	m_fSigEndurance = CManager::FLOAT_ZERO;
	m_nPowEndurance = CManager::INT_ZERO;
	m_nExp = CManager::INT_ZERO;

	int nModelNum = 0;
	CXModel* pXModel = CXModel::GetTop();
	while (pXModel != nullptr && pXModel != m_pModel)
	{
		pXModel = pXModel->GetNext();
		nModelNum++;
	}

	//�T�C�Y�ݒ�
	D3DXVECTOR3 vtxMin, vtxMax;
	m_pModel->GetCollision().GetVtx(&vtxMin, &vtxMax);
	m_fWidth = vtxMax.x - vtxMin.x;
	m_fHeight = vtxMax.y - vtxMin.y;
	m_fDepth = vtxMax.z - vtxMin.z;
}

//=================================
//�f�X�g���N�^
//=================================
CBuilding::~CBuilding()
{
}

//========================
//����������
//========================
HRESULT CBuilding::Init(void)
{
	SetType(TYPE_BUILDING);	//�����Ƃ���

	return S_OK;
}

//========================
//�I������
//========================
void CBuilding::Uninit(void)
{
	//�����N���X���ł̏���
	m_apBuilding[m_nID] = nullptr;

	//���������炷
	m_nNumAll--;

	//�������g�j��
	Release();
}

//========================
//�X�V����
//========================
void CBuilding::Update(void)
{
	if (m_fRedAlpha >= CManager::FLOAT_ZERO)
	{//�܂��Ԃ�
		//�ԐF������炷
		m_fRedAlpha -= BUILDING_DAMAGE_ALPHA / BUILDING_DAMAGE_TIME;

		if (m_fRedAlpha < CManager::FLOAT_ZERO)
		{//�Ԃ��Ȃ��Ȃ���
			m_fRedAlpha = CManager::FLOAT_ZERO;
		}
	}
}

//========================
//�`�揈��
//========================
void CBuilding::Draw(void)
{
	if (m_nEndurance > 0)
	{//�ϋv���c���Ă���
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�擾
		CTexture* pTexture = CManager::GetTexture();						//�e�N�X�`���I�u�W�F�N�g�擾
		D3DXMATRIX mtxRot, mtxTrans, mtxTexture;							//�v�Z�p
		D3DMATERIAL9 matDef;												//���݂̃}�e���A���ۑ��p
		D3DXMATERIAL *pMat;													//�}�e���A���f�[�^�ւ̃|�C���^

		//���݂̃}�e���A���擾
		pDevice->GetMaterial(&matDef);

		//���f���擾
		//���[���h�}�g���b�N�X������
		D3DXMatrixIdentity(&mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		//�ʒu���f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		//�}�e���A���f�[�^�ւ̃|�C���^�擾
		pMat = (D3DXMATERIAL*)m_pModel->GetBufMat()->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_pModel->GetNumMat(); nCntMat++)
		{
			//�}�e���A���ݒ�
			D3DMATERIAL9 changeMat = pMat[nCntMat].MatD3D;

			//�_���[�W��ԂȂ�Ԓǉ�
			if (m_fRedAlpha > CManager::FLOAT_ZERO)
			{
				changeMat.Diffuse.r = 1.0f * m_fRedAlpha + changeMat.Diffuse.r * (1.0f - m_fRedAlpha);
				changeMat.Diffuse.g = 0.0f * m_fRedAlpha + changeMat.Diffuse.g * (1.0f - m_fRedAlpha);
				changeMat.Diffuse.b = 0.0f * m_fRedAlpha + changeMat.Diffuse.b * (1.0f - m_fRedAlpha);
			}

			pDevice->SetMaterial(&changeMat);

			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, pTexture->GetAddress(m_pModel->GetIdxTexture()[nCntMat]));

			//���f���`��
			m_pModel->GetMesh()->DrawSubset(nCntMat);
		}

		//�}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//========================
//��������
//========================
CBuilding* CBuilding::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, CXModel* pModel)
{
	CBuilding* pBuilding = nullptr;

	if (pBuilding == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pBuilding = new CBuilding(pos, rot, pModel);

		//������
		pBuilding->Init();

		return pBuilding;
	}
	else
	{
		return nullptr;
	}
}

//========================
//���x���ݒ菈���i�Ƒϋv�ݒ菈���j
//========================
void CBuilding::SetLv(const int nLv)
{
	m_nLv = nLv;
	m_nEndurance = HAVE_LIFE(nLv);
}

//========================
//�ϋv�L�������ݒ�i�Ƒϋv�ݒ菈���j
//========================
void CBuilding::SetSigEndurance(const float fSignificant)
{
	m_fSigEndurance = fSignificant;
	CulcEndurance();
}

//========================
//�ϋv�ׂ���ݒ�i�Ƒϋv�ݒ菈���j
//========================
void CBuilding::SetPowEndurance(const int nPower)
{
	m_nPowEndurance = nPower;
	CulcEndurance();
}

//========================
//�_���[�W�t�^����
//========================
void CBuilding::AddDamage(int nDamage)
{
	m_nEndurance -= nDamage;
	if (m_nEndurance <= 0)
	{//�S��
		m_nEndurance = 0;	//�ϋv0�ɂ���

		for (int cnt = 0; cnt < MAX_OBJ; cnt++)
		{//�S�I�u�W�F�N�g����
			CPictoDestroyer* pPicto = CPictoDestroyer::GetPicto(cnt);	//�I�u�W�F�N�g�擾

			if (pPicto != nullptr)	//�k���`�F
			{//�Ȃ񂩂���
				if (pPicto->GetTargetObj() == this)
				{//�������^�[�Q�b�g
					pPicto->UnsetTarget();
				}
			}
		}

		//�o���l�t�^
		CPictoDestroyer::AddExp(DROP_EXP(m_nLv));
	}
	else
	{
		//�_���[�W��
		CPoliceManager::ReportDamage(m_nID);

		//�Ԃ�����
		m_fRedAlpha = BUILDING_DAMAGE_ALPHA;
	}
}

//========================
//�ϋv�v�Z����
//========================
void CBuilding::CulcEndurance(void)
{
	m_nEndurance = m_fSigEndurance * pow(10, m_nPowEndurance);
}