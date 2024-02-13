//==========================================
//
//���C�g�֌W�v���O����[light.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "manager.h"
#include "renderer.h"
#include "light.h"

//========================
//�R���X�g���N�^
//========================
CLight::CLight()
{
	//���C�g���N���A
	ZeroMemory(&m_aLight[0], sizeof(D3DLIGHT9));
	ZeroMemory(&m_aLight[1], sizeof(D3DLIGHT9));
	ZeroMemory(&m_aLight[2], sizeof(D3DLIGHT9));
	ZeroMemory(&m_aLight[3], sizeof(D3DLIGHT9));
}

//========================
//�f�X�g���N�^
//========================
CLight::~CLight()
{

}

//========================
//����������
//========================
HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXVECTOR3 vecDir;	//�ݒ�p

	//���C�g���N���A
	ZeroMemory(&m_aLight[0], sizeof(D3DLIGHT9));
	ZeroMemory(&m_aLight[1], sizeof(D3DLIGHT9));
	ZeroMemory(&m_aLight[2], sizeof(D3DLIGHT9));
	ZeroMemory(&m_aLight[3], sizeof(D3DLIGHT9));

	//���C�g��ސݒ�
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;
	m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;
	m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
	m_aLight[3].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�g�U���ݒ�
	m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_aLight[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_aLight[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_aLight[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕���
	//0
	vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
	D3DXVec3Normalize(&vecDir, &vecDir);

	m_aLight[0].Direction = vecDir;

	//1
	vecDir = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
	D3DXVec3Normalize(&vecDir, &vecDir);

	m_aLight[1].Direction = vecDir;

	//2
	vecDir = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
	D3DXVec3Normalize(&vecDir, &vecDir);

	m_aLight[2].Direction = vecDir;

	//3
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize(&vecDir, &vecDir);

	m_aLight[3].Direction = vecDir;

	//���C�g�ݒ�
	pDevice->SetLight(0, &m_aLight[0]);
	pDevice->SetLight(1, &m_aLight[1]);
	pDevice->SetLight(2, &m_aLight[2]);

	//���C�g�L����
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);

	//�ł���
	return S_OK;
}

//========================
//�I������
//========================
void CLight::Uninit(void)
{
	//��
}

//========================
//�X�V����
//========================
void CLight::Update(void)
{
	//��
}