//======================================================
//
//���f���L��������[chara.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "chara.h"
#include "../../_Core/manager/manager.h"
#include "../../_Core/renderer/renderer.h"
#include "../../_Core/texture/texture.h"
#include "../charmodel/model.h"
#include "../charmotion/motion.h"
#include "../file(legacy)/file.h"
#include "../utility/Utility.h"

//=================================
//�R���X�g���N�^
//=================================
CChara::CChara(int nPriority) : CObject(nPriority)
{
	m_pos = IS_Utility::VEC3_ZERO;
	m_rot = IS_Utility::VEC3_ZERO;
	m_ppModel = nullptr;
	m_pMotion = nullptr;
	m_nNumModel = 0;
}

//=================================
//�f�X�g���N�^
//=================================
CChara::~CChara()
{
}

//========================
//����������
//========================
HRESULT CChara::Init(void)
{
	return S_OK;
}

//========================
//�I������
//========================
void CChara::Uninit(void)
{
	//���[�V�����j��
	if (m_pMotion != nullptr)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	if (m_ppModel != nullptr)
	{
		for (int cnt = 0; cnt < m_nNumModel; cnt++)
		{//�������
			if (m_ppModel[cnt] != nullptr)
			{
				m_ppModel[cnt]->Uninit();
				delete m_ppModel[cnt];
				m_ppModel[cnt] = nullptr;
			}
		}
		delete[] m_ppModel;	//�z�񂻂̂��̂�j��
	}

	Release();
}

//========================
//�X�V����
//========================
void CChara::Update(void)
{
	//���f���ݒ�
	if (m_ppModel != nullptr)
	{
		for (int cnt = 0; cnt < m_nNumModel; cnt++)
		{
			if (m_ppModel[cnt] != nullptr)
			{
				m_ppModel[cnt]->Update();
			}
		}
	}

	//���[�V����������
	if (m_pMotion != nullptr)
	{
		//���[�V�����X�V
		m_pMotion->Update();
	}

	//���[�V�����I������
	if (m_pMotion->IsFinish() == true && GetMotion() == MOTIONTYPE::MOTIONTYPE_LAND)
	{
		SetMotion(MOTIONTYPE::MOTIONTYPE_NEUTRAL);
	}
}

//========================
//�`�揈��
//========================
void CChara::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�擾
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();			//�e�N�X�`���I�u�W�F�N�g�擾
	D3DXMATRIX mtxRot, mtxTrans, mtxTexture;							//�v�Z�p
	D3DMATERIAL9 matDef;												//���݂̃}�e���A���ۑ��p

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//���f���擾
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

	//�A���t�@�e�X�g�L����
	CRenderer* pRenderer = CManager::GetInstance()->GetRenderer();
	pRenderer->SetEnableAlplaTest(true);

	//���f���`��
	if (m_ppModel != nullptr)
	{
		for (int cnt = 0; cnt < m_nNumModel; cnt++)
		{
			if (m_ppModel[cnt] != nullptr)
			{
				m_ppModel[cnt]->Draw();
			}
		}
	}

	//�A���t�@�e�X�g������
	pRenderer->SetEnableAlplaTest(false);

	//�}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//========================
//��������
//========================
CChara* CChara::Create(const char * pPath, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CChara* pChara = nullptr;

	if (pChara == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pChara = new CChara;

		//������
		if (SUCCEEDED(pChara->Init()))
		{
			pChara->m_pos = pos;
			pChara->m_rot = rot;

			//���f���ǂݍ���
			if (FAILED(pChara->SetupModel(pPath)))
			{//���܂������Ȃ������̂Ő����������̏���
				pChara->Uninit();
				pChara = nullptr;
			}
		}
		else
		{//���܂������Ȃ������̂Ő����������̏���
			pChara->Uninit();
			pChara = nullptr;
		}

		return pChara;
	}
	else
	{
		return nullptr;
	}
}

//========================
//���[�V�����擾����
//========================
inline CChara::MOTIONTYPE CChara::GetMotion(void)
{
	return (MOTIONTYPE)m_pMotion->GetType();
}

//========================
//���[�V�����ݒ菈��
//========================
inline void CChara::SetMotion(MOTIONTYPE type)
{
	m_pMotion->Set(static_cast<int>(type));
}

//========================
//���f���g�ݗ��ď���
//========================
HRESULT CChara::SetupModel(const char* pPath)
{
	//���[�V���������E������
	m_pMotion = new CMotion;
	if (SUCCEEDED(m_pMotion->Init()) &&
		LoadMotionViewerFile(pPath, &m_ppModel, m_pMotion, &m_nNumModel) == true)
	{
		//���[�V�����␳
		m_ppModel[0]->SetPosOffset(m_ppModel[0]->GetPosOffset());

		//���[�V�����ݒ�
		m_pMotion->Set(0);

		//�����Ԃ�
		return S_OK;
	}
	else
	{//���܂������Ȃ������̂Ő����������̏���
		return E_FAIL;
	}
}