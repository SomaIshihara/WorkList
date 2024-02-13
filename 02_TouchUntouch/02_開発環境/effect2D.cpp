//======================================================
//
//�G�t�F�N�g����(2D)[effect2D.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "effect2D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//=================================
//�R���X�g���N�^
//=================================
CEffect2D::CEffect2D(const int nLife, int nPriority) : CObject2D(nPriority), m_nDefLife(nLife)
{
	//�l�N���A
	m_nIdxTexture = -1;
	m_effect.move = CManager::VEC3_ZERO;
	m_effect.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_effect.nLife = 0;
}

//=================================
//�f�X�g���N�^
//=================================
CEffect2D::~CEffect2D()
{
}

//=================================
//������
//=================================
HRESULT CEffect2D::Init(void)
{
	//�e�N���X����
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL;
	}

	//�e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\effect000.jpg");

	return S_OK;
}

//=================================
//�I��
//=================================
void CEffect2D::Uninit(void)
{
	//�e�N���X����
	CObject2D::Uninit();
}

//=================================
//�X�V
//=================================
void CEffect2D::Update(void)
{
	//�e�N���X����
	CObject2D::Update();

	//�ړ�
	D3DXVECTOR3 pos = GetPos();
	pos += m_effect.move;
	SetPos(pos);

	//�����Ǘ�
	m_effect.nLife--;	//���炷

	//�s�����x�ݒ�
	m_effect.col.a = (float)m_effect.nLife / m_nDefLife;
	SetCol(m_effect.col);

	if (m_effect.nLife <= 0)
	{//����
		Uninit();	//�I��
	}
}

//=================================
//�`��
//=================================
void CEffect2D::Draw(void)
{
	//Z�e�X�g������
	CManager::GetInstance()->GetRenderer()->SetEnableZTest(false);

	//�A���t�@�e�X�g�L����
	CManager::GetInstance()->GetRenderer()->SetEnableAlplaTest(true);

	//�u�����f�B���O��ނ����Z�����ɕύX
	CManager::GetInstance()->GetRenderer()->SetBlendType(CRenderer::BLENDTYPE_ADD);

	//�e�N���X����
	CObject2D::Draw();

	//�u�����f�B���O��ނ�ʏ��Ԃɖ߂�
	CManager::GetInstance()->GetRenderer()->SetBlendType(CRenderer::BLENDTYPE_NORMAL);

	//�A���t�@�e�X�g������
	CManager::GetInstance()->GetRenderer()->SetEnableAlplaTest(false);

	//Z�e�X�g������
	CManager::GetInstance()->GetRenderer()->SetEnableZTest(true);
}

//=================================
//��������
//=================================
CEffect2D* CEffect2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fWidth, const float fHeight,
	const D3DXCOLOR col, const int nLife)
{
	CEffect2D* pObjEffect = nullptr;

	if (pObjEffect == nullptr)
	{
		//�w�i�̐���
		pObjEffect = new CEffect2D(nLife);

		//������
		pObjEffect->Init();

		//�f�[�^�ݒ�
		pObjEffect->m_effect.move = move;
		pObjEffect->m_effect.col = col;
		pObjEffect->m_effect.nLife = nLife;
		pObjEffect->SetPos(pos);
		pObjEffect->SetRot(CManager::VEC3_ZERO);
		pObjEffect->SetSize(fWidth, fHeight);

		//�e�N�X�`���ݒ�
		pObjEffect->BindTexture(pObjEffect->m_nIdxTexture);

		return pObjEffect;
	}
	else
	{
		return nullptr;
	}
}