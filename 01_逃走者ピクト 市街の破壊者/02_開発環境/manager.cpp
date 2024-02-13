//======================================================
//
//�}�l�[�W��[manager.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "debugproc.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "object.h"
#include "objectX.h"
#include "xmodel.h"
#include "fade.h"

//�V�[��
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "ranking.h"

//����
#include <time.h>

//�}�N��
#define FPS_SPEED	(500)	//FPS�v������

//�ÓI�����o�ϐ�
CRenderer* CManager::m_pRenderer = nullptr;
CInputKeyboard* CManager::m_pInputKeyboard = nullptr;
CInputMouse* CManager::m_pInputMouse = nullptr;
CDebugProc* CManager::m_pDebProc = nullptr;
CSound* CManager::m_pSound = nullptr;
CCamera* CManager::m_pCamera = nullptr;
CLight* CManager::m_pLight = nullptr;
CTexture* CManager::m_pTexture = nullptr;
CScene* CManager::m_pScene = nullptr;
//��
CXModel* CManager::m_pAgitModel = nullptr;
CXModel* CManager::m_pFragModel = nullptr;

//�ÓIconst
const int CManager::INT_ZERO = 0;
const float CManager::FLOAT_ZERO = 0.0f;
const D3DXVECTOR2 CManager::VEC2_ZERO = D3DXVECTOR2(0.0f, 0.0f);
const D3DXVECTOR3 CManager::VEC3_ZERO = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

bool CManager::m_bPause = false;

int CManager::m_nFPS = 0;
DWORD CManager::m_dwFrameCount = 0;

//************************************************
//�}�l�[�W���N���X
//************************************************
//=================================
//�R���X�g���N�^
//=================================
CManager::CManager()
{
	
}

//=================================
//�f�X�g���N�^
//=================================
CManager::~CManager()
{}

//=================================
//������
//=================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�����𗐐��ɂ���
	srand((unsigned int)time(nullptr));

	//����
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputMouse = new CInputMouse;
	m_pSound = new CSound;
	m_pRenderer = new CRenderer;
	m_pDebProc = new CDebugProc;
	m_pCamera = new CCamera;
	m_pLight = new CLight;
	m_pTexture = new CTexture;

	//�����_���[������
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h������
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�}�E�X������
	if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�T�E���h������
	if (FAILED(m_pSound->Init(hWnd)))
	{
		return E_FAIL;
	}

	//�f�o�b�O������
	m_pDebProc->Init();

	//�J����������
	if (FAILED(m_pCamera->Init()))
	{
		return E_FAIL;
	}

	//���C�g������
	if (FAILED(m_pLight->Init()))
	{
		return E_FAIL;
	}

	//�e�N�X�`��������
	if (FAILED(m_pTexture->Load("data\\preload.txt")))
	{
		return E_FAIL;
	}

	//3D���f���ǂݍ���
	m_pFragModel = CXModel::Load("data\\MODEL\\frag.x");
	m_pAgitModel = CXModel::Load("data\\MODEL\\Agit.x");

	//FPS�v���평����
	m_nFPS = 0;
	m_dwFrameCount = 0;

	//���[�h�ݒ�
	SetMode(CScene::MODE_TITLE);

	//�ł���
	return S_OK;
}

//=================================
//�I��
//=================================
void CManager::Uninit(void)
{
	//���f���j��
	CXModel::UnloadAll();			//X���f��

	//�I�u�W�F�N�g�I��+�j��
	CObject::ReleaseAll();

	//�e�N�X�`���j��
	if (m_pTexture != nullptr)
	{//�e�N�X�`���I��
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	//���C�g�j��
	if (m_pLight != nullptr)
	{//���C�g�I��
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	//�J�����j��
	if (m_pCamera != nullptr)
	{//�J�����I��
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	//�f�o�b�O�j��
	if (m_pDebProc != nullptr)
	{//�f�o�b�O�I��
		m_pDebProc->Uninit();
		delete m_pDebProc;
		m_pDebProc = nullptr;
	}

	//�T�E���h�j��
	if (m_pSound != nullptr)
	{//�T�E���h�I��
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	//�}�E�X�j��
	if (m_pInputMouse != nullptr)
	{//�}�E�X�I��
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = nullptr;
	}

	//�L�[�{�[�h�j��
	if (m_pInputKeyboard != nullptr)
	{//�L�[�{�[�h�I��
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	//�����_���[�j��
	if (m_pRenderer != nullptr)
	{//�����_���[�I��
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}

//=================================
//�X�V
//=================================
void CManager::Update(void)
{
	//���͌n
	m_pInputKeyboard->Update();
	m_pInputMouse->Update();

	//�`��n
	if (m_bPause == false)
	{//�|�[�Y���Ă��Ȃ���ΑS�I�u�W�F�N�g�X�V
		m_pRenderer->Update();
	}

	//3D�n
	m_pCamera->Update();
	m_pLight->Update();

	//���g�m��񂯂ǉ�������̃V�[��
	m_pScene->Update();

	//���̎��_�Ŏ��S�t���O�������Ă���I�u�W�F���E��
	CObject::Death();

	//FPS�v����̏���
	m_dwFrameCount++;

	//�f�o�b�O�\��
	m_pDebProc->Print("FPS:%d\n", m_nFPS);
#ifdef _DEBUG
	m_pDebProc->Print("[Debug]F3:�^�C�}�[�ݒ�(2�b�J�E���g�_�E��)\n");
#endif // _DEBUG
}

//=================================
//�`��
//=================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();
}

//=================================
//FPS�v��
//=================================
void CManager::CheckFPS(DWORD dwCurrentTime, DWORD dwExecLastTime)
{
	m_nFPS = (m_dwFrameCount * 1000) / (dwCurrentTime - dwExecLastTime);
	m_dwFrameCount = 0;
}

//=================================
//���[�h�ݒ�
//=================================
void CManager::SetMode(CScene::MODE mode)
{
	//���~�߂�
	m_pSound->Stop();

	//���݂̃��[�h�j��
	if (m_pScene != nullptr)
	{//�Ȃ񂩓����Ă�
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	if (m_pScene == nullptr)
	{//�ʂ�ʂ�
		//�V���[�h����
		m_pScene = CScene::Create(mode);
	}
}

//************************************************
//�V�[���i���ہj�N���X
//************************************************
//=================================
//�R���X�g���N�^
//=================================
CScene::CScene()
{
}

//=================================
//�f�X�g���N�^
//=================================
CScene::~CScene()
{
}

//=================================
//����
//=================================
CScene* CScene::Create(MODE mode)
{
	CScene* pScene = nullptr;

	if (pScene == nullptr)
	{
		//�V�[���̐���
		switch (mode)
		{
		case MODE_TITLE:
			pScene = new CTitle;
			break;
		case MODE_GAME:
			pScene = new CGame;
			break;
		case MODE_TUTORIAL:
			pScene = new CTutorial;
			break;
		case MODE_RANKING:
			pScene = new CRanking;
			break;
		default:	//��Ȃ���͂Ȃ�
			return nullptr;
			break;
		}

		//������
		pScene->Init();

		//���[�h����Ƃ�
		pScene->m_mode = mode;

		return pScene;
	}
	else
	{
		return nullptr;
	}
}
