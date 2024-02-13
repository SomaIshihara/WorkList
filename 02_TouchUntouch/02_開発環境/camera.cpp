//==========================================
//
//�J�����֌W�v���O����[camera.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "Culc.h"

//�}�N��
#define CAMERA_LENGTH			(20000.0f)	//�J������������ő勗��
#define CAMERA_ROT_X_MIN		(-0.45f)	//�J������X�p�x�̍Œ�l[rad]
#define CAMERA_ROT_X_MAX		(-0.2f)	//�J������X�p�x�̍Œ�l[rad]

//========================
//�R���X�g���N�^
//========================
CCamera::CCamera()
{
	//�l�N���A
	m_posV = CManager::VEC3_ZERO;
	m_posR = CManager::VEC3_ZERO;
	m_vecU = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fLength = 0.0f;
}

//========================
//�f�X�g���N�^
//========================
CCamera::~CCamera()
{

}

//========================
//����������
//========================
HRESULT CCamera::Init(void)
{
	//�l�ݒ�
	ResetPos();

	//�ł���
	return S_OK;
}

//========================
//�I������
//========================
void CCamera::Uninit(void)
{
	
}

//========================
//�X�V����
//========================
void CCamera::Update(void)
{

}

//========================
//�ݒ菈��
//========================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//�v���W�F�N�V�����}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxProjection);

	//�쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, CAMERA_LENGTH);

	//�ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	
	//�r���[�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxView);

	//�쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	//�ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//========================
//�ʒu�ݒ�
//========================
void CCamera::Move(const D3DXVECTOR3 move)
{
	//�ʒu�K�p
	m_posV += move;
	m_posR += move;
}

//========================
//�����ݒ�
//========================
void CCamera::SetRot(const D3DXVECTOR3 rot)
{
	//��]�K�p�ƏC������
	m_rot += rot;
	FixRot();
	m_vecU.x = sinf(m_rot.x) * sinf(m_rot.y);
	m_vecU.y = cosf(m_rot.x);
	m_vecU.z = sinf(m_rot.x) * cosf(m_rot.y) * -1;
	D3DXVec3Normalize(&m_vecU, &m_vecU);
	FixPosV();
}

//========================
//�����ݒ��posV�̏C��
//========================
void CCamera::SetLength(const float fLength)
{
	m_fLength = fLength;
	FixPosV();
}

//========================
//�J�����ʒu���Z�b�g
//========================
void CCamera::ResetPos(void)
{
	//�l�ݒ�
	m_posR = D3DXVECTOR3(0.0f, 250.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(-0.3f, 0.0f, 0.0f);
	m_fLength = 900.0f;
	FixRot();
	FixPosV();	//������posV�����߂�
}

//========================
//���_�C���i�����_���S�j
//========================
void CCamera::FixPosV(void)
{
	m_posV.x = m_posR.x + cosf(m_rot.x) * sinf(m_rot.y) * m_fLength;
	m_posV.y = m_posR.y - sinf(m_rot.x) * m_fLength;
	m_posV.z = m_posR.z - cosf(m_rot.x) * cosf(m_rot.y) * m_fLength;
}

//========================
//�����_�C���i���_���S�j
//========================
void CCamera::FixPosR(void)
{
	m_posR.x = m_posV.x - sinf(m_rot.y) * cosf(m_rot.x) * m_fLength;
	m_posR.z = m_posV.z + cosf(m_rot.y) * cosf(m_rot.x) * m_fLength;
}

//========================
//�p�x�C��
//========================
void CCamera::FixRot(void)
{
	//�J����1���v�Z
	m_rot.x = FIX_ROT(m_rot.x);
	m_rot.y = FIX_ROT(m_rot.y);
	m_rot.z = FIX_ROT(m_rot.z);

#if 0
	//[�J��������]x��]�̐���
	if (m_rot.x >= CAMERA_ROT_X_MAX * D3DX_PI)
	{
		m_rot.x = CAMERA_ROT_X_MAX * D3DX_PI;
	}
	else if (m_rot.x <= CAMERA_ROT_X_MIN * D3DX_PI)
	{
		m_rot.x = CAMERA_ROT_X_MIN * D3DX_PI;
	}
#endif
}