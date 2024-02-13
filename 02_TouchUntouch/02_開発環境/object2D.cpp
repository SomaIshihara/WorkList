//======================================================
//
//�I�u�W�F�N�g�i2D�j����[object2D.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object2D.h"

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	//�N���A
	m_pos = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fWidth = CManager::FLT_ZERO;
	m_fHeight = CManager::FLT_ZERO;
	m_fLength = CManager::FLT_ZERO;
	m_fAngle = CManager::FLT_ZERO;
	m_pVtxbuff = nullptr;
}

//=================================
//�f�X�g���N�^
//=================================
CObject2D::~CObject2D()
{
}

//========================
//����������
//========================
HRESULT CObject2D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�擾

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxbuff,
		nullptr)))
	{
		return E_FAIL;
	}

	//�����v�Z
	m_fLength = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight) * 0.5f;

	//�p�x�v�Z
	m_fAngle = atan2f(m_fWidth, m_fHeight);

	//�ʒu�ݒ�
	if (FAILED(SetPos(m_pos)))
	{
		return E_FAIL;
	}

	//�����ݒ�
	if (FAILED(SetRot(m_rot)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^
	if (FAILED(m_pVtxbuff->Lock(0, 0, (void **)&pVtx, 0)))
	{
		return E_FAIL;
	}

	//rhw
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�o�b�t�@���A�����b�N
	if (FAILED(m_pVtxbuff->Unlock()))
	{
		return E_FAIL;
	}

	//�e�N�X�`�����W�ݒ�
	if (FAILED(SetTex(D3DXVECTOR2(0.0f,0.0f), D3DXVECTOR2(1.0f, 1.0f))))
	{
		return E_FAIL;
	}

	return S_OK;
}

//========================
//�I������
//========================
void CObject2D::Uninit(void)
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
void CObject2D::Update(void)
{

}

//========================
//�`�揈��
//========================
void CObject2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�擾
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();						//�e�N�X�`���I�u�W�F�N�g�擾

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxbuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	//�`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//========================
//���������i�e�N�X�`���Ȃ��j
//========================
CObject2D* CObject2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const int nPriority)
{
	CObject2D* pObj2D = nullptr;

	if (pObj2D == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pObj2D = new CObject2D(nPriority);

		//������
		pObj2D->Init();

		//�l�ݒ�
		pObj2D->SetPos(pos);
		pObj2D->SetRot(rot);
		pObj2D->SetSize(fWidth, fHeight);

		return pObj2D;
	}
	else
	{
		return nullptr;
	}
}

//========================
//�ʒu�ݒ�
//========================
HRESULT CObject2D::SetPos(const D3DXVECTOR3 pos)
{
	//�l�ݒ�
	m_pos = pos;

	return SetVtxPos();
}

//========================
//�����ݒ�
//========================
HRESULT CObject2D::SetRot(const D3DXVECTOR3 rot)
{
	//�l�ݒ�
	m_rot = rot;

	return SetVtxPos();
}

//========================
//�e�N�X�`�����W�ݒ�
//========================
HRESULT CObject2D::SetTex(const D3DXVECTOR2 tex0, const D3DXVECTOR2 tex3)
{
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^
	if (FAILED(m_pVtxbuff->Lock(0, 0, (void **)&pVtx, 0)))
	{
		return E_FAIL;
	}

	//�e�N�X�`�����W
	pVtx[0].tex = tex0;
	pVtx[1].tex = D3DXVECTOR2(tex3.x, tex0.y);
	pVtx[2].tex = D3DXVECTOR2(tex0.x, tex3.y);
	pVtx[3].tex = tex3;

	//���_�o�b�t�@���A�����b�N
	if (FAILED(m_pVtxbuff->Unlock()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//========================
//�T�C�Y�ύX
//========================
HRESULT CObject2D::SetSize(const float fWidth, const float fHeight)
{
	//�l�ύX
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	//�Čv�Z
	//�����v�Z
	m_fLength = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight) * 0.5f;

	//�p�x�v�Z
	m_fAngle = atan2f(m_fWidth, m_fHeight);

	//���_�z�u
	return SetVtxPos();
}

//========================
//���_���W�ݒ�
//========================
HRESULT CObject2D::SetVtxPos(void)
{
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^
	if (FAILED(m_pVtxbuff->Lock(0, 0, (void **)&pVtx, 0)))
	{
		return E_FAIL;
	}

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf((m_rot.z * D3DX_PI) + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf((m_rot.z * D3DX_PI) + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.z = CManager::FLT_ZERO;
	pVtx[1].pos.x = m_pos.x + sinf((m_rot.z * D3DX_PI) + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf((m_rot.z * D3DX_PI) + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = CManager::FLT_ZERO;
	pVtx[2].pos.x = m_pos.x + sinf((m_rot.z * D3DX_PI) + (0 - m_fAngle)) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf((m_rot.z * D3DX_PI) + (0 - m_fAngle)) * m_fLength;
	pVtx[2].pos.z = CManager::FLT_ZERO;
	pVtx[3].pos.x = m_pos.x + sinf((m_rot.z * D3DX_PI) + (0 + m_fAngle)) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf((m_rot.z * D3DX_PI) + (0 + m_fAngle)) * m_fLength;
	pVtx[3].pos.z = CManager::FLT_ZERO;

	//���_�o�b�t�@���A�����b�N
	if (FAILED(m_pVtxbuff->Unlock()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//========================
//�F�ݒ�
//========================
HRESULT CObject2D::SetCol(const D3DXCOLOR col)
{
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	VERTEX_2D *pVtx;	//�ݒ�p�|�C���^
	if (FAILED(m_pVtxbuff->Lock(0, 0, (void **)&pVtx, 0)))
	{
		return E_FAIL;
	}

	//���_�J���[�̕ϊ�
	D3DCOLOR exchange = D3DCOLOR_COLORVALUE(col.r, col.g, col.b, col.a);

	//���_�J���[�̐ݒ�
	pVtx[0].col = exchange;
	pVtx[1].col = exchange;
	pVtx[2].col = exchange;
	pVtx[3].col = exchange;

	//���_�o�b�t�@���A�����b�N
	if (FAILED(m_pVtxbuff->Unlock()))
	{
		return E_FAIL;
	}

	return S_OK;
}