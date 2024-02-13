//======================================================
//
//�����_�����O����[renderer.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "object.h"

//=================================
//�R���X�g���N�^
//=================================
CRenderer::CRenderer()
{
	//�N���A
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
}

//=================================
//�f�X�g���N�^
//=================================
CRenderer::~CRenderer()
{
}

//========================
//����������
//========================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	//���݂̃X�N���[�����[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;			//��ʃT�C�Y�i���j
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			//��ʃT�C�Y�i�����j
	d3dpp.BackBufferFormat = d3ddm.Format;			//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;						//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//�_�u���o�b�t�@�̐؂�ւ��i�����j
	d3dpp.EnableAutoDepthStencil = TRUE;			//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;	//�f�v�X�o�b�t�@�Ƃ���24�r�b�g�i�A�X�e���V���o�b�t�@�Ƃ���8�r�b�g�H�j�g�p
	d3dpp.Windowed = bWindow;						//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//�C���^�[�o��

																	//Direct3D�f�o�C�X�̐���
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�I�u�W�F�N�g�̏���������
	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	return S_OK;
}

//========================
//�I������
//========================
void CRenderer::Uninit(void)
{
	//�I�������i��������������̂��̂Ă�j
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//========================
//�X�V����
//========================
void CRenderer::Update(void)
{
	CObject::UpdateAll();
}

//========================
//�`�揈��
//========================
void CRenderer::Draw(void)
{
	//��ʃN���A�i�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0, nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);//�}�N���ɂ�����H

	//�`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//���������ꍇ
	 //�����������`�揈��
		CObject::DrawAll();
		CManager::GetInstance()->GetDebProc()->Draw();

		//�`��I������
		m_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

//=================================
//�u�����f�B���O��ސݒ�
//=================================
void CRenderer::SetBlendType(BLENDTYPE type)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�擾

	switch (type)
	{
	case BLENDTYPE_NORMAL:	//�ʏ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		break;
	case BLENDTYPE_ADD:
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case BLENDTYPE_SUB:
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	}
}

//=================================
//Z�o�b�t�@�Q�Ɛݒ�
//=================================
void CRenderer::SetZEnable(const bool bEnable)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�擾

	pDevice->SetRenderState(D3DRS_ZENABLE, (bEnable == true ? TRUE : FALSE));
}

//=================================
//Z�e�X�g�ݒ�
//=================================
void CRenderer::SetEnableZTest(bool bEnable)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�擾

	//Z�o�b�t�@�̗L���E�����ݒ�
	pDevice->SetRenderState(D3DRS_ZFUNC, (bEnable == true ? D3DCMP_LESSEQUAL : D3DCMP_ALWAYS));
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, (bEnable == true ? TRUE : FALSE));
}

//=================================
//�A���t�@�e�X�g�ݒ�
//=================================
void CRenderer::SetEnableAlplaTest(bool bEnable)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�擾

	//�A���t�@�e�X�g�L���E�����ݒ�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, (bEnable == true ? TRUE : FALSE));
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, (bEnable == true ? D3DCMP_GREATER : D3DCMP_ALWAYS));
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}
