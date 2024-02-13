//======================================================
//
//�}���`�w�i�i2D�j����[bg.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "multiplebg.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object2D.h"

//�e�N�X�`���p�X
const char* c_apTexturePathMultiBG[MAX_MULTIPLE_BG] =
{
	"data\\TEXTURE\\bg100.png",
	"data\\TEXTURE\\bg101.png",
	"data\\TEXTURE\\bg102.png"
};


//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CMultipleBG::CMultipleBG(int nPriority)
{
	//�e�N�X�`���ԍ��N���A
	for (int cnt = 0; cnt < MAX_MULTIPLE_BG; cnt++)
	{
		m_aIdxTexture[cnt] = -1;
	}
}

//=================================
//�f�X�g���N�^
//=================================
CMultipleBG::~CMultipleBG()
{
}

//=================================
//������
//=================================
HRESULT CMultipleBG::Init(void)
{
	CTexture* pTexture = CManager::GetTexture();	//�e�N�X�`���I�u�W�F�N�g
	for (int cnt = 0; cnt < MAX_MULTIPLE_BG; cnt++)
	{//�w�i�p�I�u�W�F�N�g2D�������ƃe�N�X�`���ǂݍ���
		m_pObj2D[cnt] = NULL;
		//�e�N�X�`���ǂݍ���
		m_aIdxTexture[cnt] = pTexture->Regist(c_apTexturePathMultiBG[cnt]);
	}

	//�ł���
	return S_OK;
}

//=================================
//�I��
//=================================
void CMultipleBG::Uninit(void)
{
	for (int cnt = 0; cnt < MAX_MULTIPLE_BG; cnt++)
	{//�w�i�p�I�u�W�F�N�g2D�I��
		if (m_pObj2D[cnt] != NULL)
		{//���v�B���g�͂���
			m_pObj2D[cnt]->Uninit();
		}
	}

	//���d�w�i�Ǘ��I�u�W�F�N�g�j��
	Release();
}

//=================================
//�X�V
//=================================
void CMultipleBG::Update(void)
{
	for (int cnt = 0; cnt < MAX_MULTIPLE_BG; cnt++)
	{//�w�i�p�I�u�W�F�N�g2D�X�V
		if (m_pObj2D[cnt] != NULL)
		{//���v�B���g�͂���
			//�I�u�W�F�N�g2D�̍X�V����
			m_pObj2D[cnt]->Update();

			//���W�ݒ�
			m_aTexV[cnt] = fmodf(m_aTexV[cnt] + 1.0f - m_aSpeed[cnt], 1.0f);
			//�e�N�X�`���ݒ�
			D3DXVECTOR2 tex0, tex3;
			tex0 = D3DXVECTOR2(0.0f, m_aTexV[cnt]);
			tex3 = D3DXVECTOR2(1.0f, m_aTexV[cnt] + 1.0f);
			m_pObj2D[cnt]->SetTex(tex0, tex3);
		}
	}
}

//=================================
//�`��
//=================================
void CMultipleBG::Draw(void)
{
	for (int cnt = 0; cnt < MAX_MULTIPLE_BG; cnt++)
	{//�w�i�p�I�u�W�F�N�g2D�`��
		if (m_pObj2D[cnt] != NULL)
		{//���v�B���g�͂���
			m_pObj2D[cnt]->Draw();
		}
	}
}

//=================================
//��������
//=================================
CMultipleBG* CMultipleBG::Create(float fSpeed0, float fSpeed1, float fSpeed2)
{
	CMultipleBG* pObjMultipleBG = NULL;

	if (pObjMultipleBG == NULL)
	{
		//���d�w�i�Ǘ��I�u�W�F�N�g����
		pObjMultipleBG = new CMultipleBG;

		//���d�w�i�Ǘ��I�u�W�F�N�g������
		pObjMultipleBG->Init();

		//�w�i�p�I�u�W�F�N�g2D����
		for (int cnt = 0; cnt < MAX_MULTIPLE_BG; cnt++)
		{//1���������`�e�N�X�`���ݒ�
			//����
			pObjMultipleBG->m_pObj2D[cnt] = pObjMultipleBG->m_pObj2D[cnt]->Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), VEC3_ZERO, 
				SCREEN_WIDTH, SCREEN_HEIGHT);

			//������
			pObjMultipleBG->m_pObj2D[cnt]->Init();

			//�e�N�X�`���ݒ�
			pObjMultipleBG->m_pObj2D[cnt]->BindTexture(pObjMultipleBG->m_aIdxTexture[cnt]);
		}

		//�X�s�[�h�ݒ�
		pObjMultipleBG->m_aSpeed[0] = fSpeed0;
		pObjMultipleBG->m_aSpeed[1] = fSpeed1;
		pObjMultipleBG->m_aSpeed[2] = fSpeed2;

		return pObjMultipleBG;
	}
	else
	{
		return NULL;
	}
}