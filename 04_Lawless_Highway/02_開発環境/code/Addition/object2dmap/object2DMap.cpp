//==========================================================
//
// �}�b�v�I�u�W�F�N�g [object2DMap.cpp]
// Author : Soma Ishihara
//
//==========================================================
#include "object2DMap.h"
#include "../../IS_Bace/_Core/manager/manager.h"
#include "../../IS_Bace/_Core/renderer/renderer.h"
#include "../../IS_Bace/_Core/utility/Utility.h"

//==========================================================
// �R���X�g���N�^
//==========================================================
CObject2DMap::CObject2DMap(int nPriority) : CObject2D(nPriority)
{
	m_posR = IS_Utility::VEC3_ZERO;
	m_posV = IS_Utility::VEC3_ZERO;
	m_pTextureMap = nullptr;
	m_pZSurface = nullptr;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CObject2DMap::~CObject2DMap()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CObject2DMap::Init(void)
{
	CObject2D::Init();
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CObject2DMap::Uninit(void)
{
	UnLoad();
	CObject2D::Uninit();
}

//==========================================================
// �X�V����
//==========================================================
void CObject2DMap::Update(void)
{
	CObject2D::Update();
	DrawTexture();
}

//==========================================================
// �`�揈��
//==========================================================
void CObject2DMap::Draw(void)
{
	CObject2D::Draw(m_pTextureMap);
}

//===============================================
// �e�N�X�`���`�揈��
//===============================================
void CObject2DMap::DrawTexture(void)
{
	//�f�o�C�X
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^

	//�`��p�}�g��
	D3DXMATRIX mtxProj, mtxView, mtxViewPort;

	//�o�b�N�o�b�t�@�p
	LPDIRECT3DSURFACE9 pOrgSurface;
	LPDIRECT3DSURFACE9 pOrgZBuffer;
	LPDIRECT3DSURFACE9 pTexSurface;

	//��p�J����
	D3DXVECTOR3 vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�e�N�X�`���T�C�Y
	float fWidth = GetWidth();
	float fHeight = GetHeight();

	//�v���W�F�N�V�����}�g���̏�����
	D3DXMatrixIdentity(&mtxProj);

	D3DXMatrixPerspectiveFovLH(&mtxProj,
		D3DXToRadian(45.0f),
		(float)fWidth / (float)fHeight,
		10.0f,
		40000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProj);

	//�r���[�}�g���̏�����
	D3DXMatrixIdentity(&mtxView);

	//�r���[�}�g���̍쐬
	D3DXMatrixLookAtLH(&mtxView,
		&m_posV,
		&m_posR,
		&vecU);

	//�r���[�}�g���̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);

	//�r���[�|�[�g�}�g���ݒ�
	D3DXMatrixIdentity(&mtxViewPort);
	mtxViewPort._11 = fWidth * 0.5f;
	mtxViewPort._22 = -fHeight * 0.5f;
	mtxViewPort._41 = fWidth * 0.5f;
	mtxViewPort._42 = fHeight * 0.5f;

	//�e�N�X�`��
	//�쐬�e�N�X�`���p�C���^�[�t�F�[�X�擾
	m_pTextureMap->GetSurfaceLevel(0, &pTexSurface);

	//�o�b�N�o�b�t�@�C���^�[�t�F�[�X�擾
	pDevice->GetRenderTarget(0, &pOrgSurface);
	pDevice->GetDepthStencilSurface(&pOrgZBuffer);

	//�����_�����O�^�[�Q�b�g���e�N�X�`���ɕύX
	pDevice->SetRenderTarget(0, pTexSurface);
	pDevice->SetDepthStencilSurface(m_pZSurface);

	//�e�N�X�`���N���A
	pDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	//�e�N�X�`���ɕ`��
	if (SUCCEEDED(pDevice->BeginScene()))
	{// �`�悪���������ꍇ

		// 3D�I�u�W�F�N�g�̕`��
		CObject::DrawAll3D();

		// �`��I��
		pDevice->EndScene();
	}

	//�߂�
	pDevice->SetRenderTarget(0, pOrgSurface);
	pDevice->SetDepthStencilSurface(pOrgZBuffer);

	pOrgSurface->Release();
	pOrgZBuffer->Release();
	pTexSurface->Release();
}

//===============================================
// �e�N�X�`����������
//===============================================
void CObject2DMap::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�ւ̃|�C���^

	//int�^�T�C�Y
	int nWidth = static_cast<int>(GetWidth());
	int nHeight = static_cast<int>(GetHeight());

	//�e�e�N�X�`������
	if (m_pTextureMap == nullptr)
	{
		D3DXCreateTexture(pDevice, nWidth, nHeight,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT, //�����̂��߃f�o�C�X���X�g���͔j�����K�v
			&m_pTextureMap);
	}

	if (m_pZSurface == nullptr)
	{
		//����Z�o�b�t�@����
		pDevice->CreateDepthStencilSurface(
			nWidth, nHeight,
			D3DFMT_D16,
			D3DMULTISAMPLE_NONE,
			0, false,
			&m_pZSurface,
			nullptr);
	}
}

//===============================================
// �e�N�X�`���J������
//===============================================
void CObject2DMap::UnLoad(void)
{
	if (m_pTextureMap != nullptr)
	{
		m_pTextureMap->Release();
		m_pTextureMap = nullptr;
	}
	if (m_pZSurface != nullptr)
	{
		m_pZSurface->Release();
		m_pZSurface = nullptr;
	}
}

//==========================================================
// ����
//==========================================================
CObject2DMap *CObject2DMap::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight)
{
	CObject2DMap *pMap = nullptr;

	pMap = new CObject2DMap;

	if (pMap != nullptr)
	{
		// ����������
		pMap->Init();
		pMap->SetPos(pos);
		pMap->SetRot(rot);
		pMap->SetSize(fWidth, fHeight);
		pMap->Load();
	}

	return pMap;
}