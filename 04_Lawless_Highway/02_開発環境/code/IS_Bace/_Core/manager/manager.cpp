//======================================================
//
//�}�l�[�W��[manager.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "..\..\_Core\renderer\renderer.h"
#include "..\..\_Core\texture\texture.h"
#include "..\..\_Core/input/input.h"
#include "..\..\_Core/sound/sound.h"
#include "..\..\_Core/debugproc/debugproc.h"
#include "..\..\_Core/camera/camera.h"
#include "..\..\_Core/light/light.h"
#include "..\..\_Core/_object/object_empty/object.h"
#include "..\..\_Core/xmodel/xmodel.h"
#include "..\..\..\ISMD_IO/userdef/userdef.h"

//�V�[��
#include "..\_scene/title/title.h"
#include "..\_scene/tutorial/tutorial.h"
#include "..\_scene/game/game.h"
#include "..\_scene/result/result.h"
#include "..\_scene/ranking/ranking.h"

//����
#include <time.h>

//�}�N��
#define FPS_SPEED	(500)	//FPS�v������

//�ÓI�����o�ϐ�
CManager* CManager::m_pManager = nullptr;

//************************************************
//�}�l�[�W���N���X
//************************************************
//=================================
//�R���X�g���N�^
//=================================
CManager::CManager()
{
	m_pRenderer = nullptr;
	m_pInputKeyboard = nullptr;
	m_pInputMouse = nullptr;
	m_pInputPad = nullptr;
	m_pDebProc = nullptr;
	m_pSound = nullptr;
	m_pCamera = nullptr;
	m_pLight = nullptr;
	m_pTexture = nullptr;
	m_pScene = nullptr;
	m_bEnableUpdate = true;

	m_nFPS = 0;
	m_dwFrameCount = 0;
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
	m_pInputPad = new CInputGamePad;
	m_pSound = new CSound;
	m_pRenderer = new CRenderer;
	m_pDebProc = new CDebugProc;
	m_pCamera = new CCamera;
	m_pLight = new CLight;
	m_pTexture = new CTexture;

	//�����_���[������
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
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

	//�Q�[���p�b�h������
	if (FAILED(m_pInputPad->Init(hInstance, hWnd)))
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

	//FPS�v���평����
	m_nFPS = 0;
	m_dwFrameCount = 0;

	//���[�h�ݒ�
#ifdef _DEBUG
	GetInstance()->SetMode(CScene::MODE::MODE_GAME);
#endif // _DEBUG
#ifdef NDEBUG
	GetInstance()->SetMode(CScene::MODE::MODE_TITLE);	//�����͕ύX���Ȃ�
#endif // NDEBUG

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

	//�V�[���j��
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

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

	//�Q�[���p�b�h�j��
	if (m_pInputPad != nullptr)
	{//�}�E�X�I��
		m_pInputPad->Uninit();
		delete m_pInputPad;
		m_pInputPad = nullptr;
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
	m_pInputPad->Update();

	//�`��n
	if (m_bEnableUpdate == true)
	{
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

#if _DEBUG
	//�f�o�b�O�\��
	m_pDebProc->Print("FPS:%d\n", m_nFPS);
#endif
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
//�擾�i�V���O���g���j
//=================================
CManager* CManager::GetInstance(void)
{
	if (m_pManager == nullptr)
	{
		m_pManager = new CManager;
	}
	return m_pManager;
}

//=================================
//�j��
//=================================
HRESULT CManager::Release(void)
{
	if (m_pManager != nullptr)
	{
		m_pManager->Uninit();
		delete m_pManager;
		m_pManager = nullptr;

		return S_OK;
	}
	return E_FAIL;
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
	m_mode = MODE::MODE_TITLE;
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
		case MODE::MODE_TITLE:
			pScene = new CTitle;
			break;
		case MODE::MODE_TUTORIAL:
			pScene = new CTutorial;
			break;
		case MODE::MODE_GAME:
			pScene = new CGame;
			break;
		case MODE::MODE_RESULT:
			pScene = new CResult;
			break;
		case MODE::MODE_RANKING:
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
