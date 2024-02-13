//======================================================
//
//�}�l�[�W���̃w�b�_[manager.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"

//�O���錾
class CInputKeyboard;
class CInputMouse;
class CRenderer;
class CPlayer;
class CDebugProc;
class CSound;
class CCamera;
class CLight;
class CTexture;
class CXModel;
class CFade;
class CSlider;

//�V�[���N���X
class CScene
{
public:
	//���[�h��
	typedef enum
	{
		MODE_TITLE = 0,	//�^�C�g��
		MODE_TUTORIAL,	//�`���[�g���A��
		MODE_GAME,		//�Q�[���i���U���g�j
		MODE_RANKING,	//�����L���O
		MODE_MAX
	} MODE;
	
	//�R���X�g���N�^�E�f�X�g���N�^
	CScene();
	~CScene();

	//��{����
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void)  = 0;

	//����
	static CScene* Create(MODE mode);

	//�擾
	MODE GetMode(void) { return m_mode; }
	virtual CSlider* GetSlider(void) = 0;

private:
	MODE m_mode;	//���[�h
};
class CManager
{
public:
	//�ÓIconst
	static const int CManager::INT_ZERO;			//int�^��0
	static const float CManager::FLOAT_ZERO;		//float�^��0
	static const D3DXVECTOR2 VEC2_ZERO;				//vec2�^��0
	static const D3DXVECTOR3 CManager::VEC3_ZERO;	//vec3�^��0

	//�R���X�g���N�^�E�f�X�g���N�^
	CManager();
	~CManager();

	//��{����
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	//FPS�v��
	void CheckFPS(DWORD dwCurrentTime, DWORD dwExecLastTime);

	//�擾
	static CInputKeyboard* GetInputKeyboard(void) { return m_pInputKeyboard; }
	static CInputMouse* GetInputMouse(void) { return m_pInputMouse; }
	static CSound* GetSound(void) { return m_pSound; }
	static CRenderer* GetRenderer(void) { return m_pRenderer; }
	static CDebugProc* GetDebProc(void) { return m_pDebProc; }
	static CCamera* GetCamera(void) { return m_pCamera; }
	static CLight* GetLight(void) { return m_pLight; }
	static CTexture* GetTexture(void) { return m_pTexture; }
	static bool GetPause(void) { return m_bPause; }
	//��
	static CXModel* GetAgitModel(void) { return m_pAgitModel; }
	static CXModel* GetFragModel(void) { return m_pFragModel; }

	//�V�[���n
	static void SetMode(CScene::MODE mode);
	static CScene::MODE GetMode(void) { return m_pScene->GetMode(); }
	static CScene* GetScene(void) { return m_pScene; }

	//�ݒ�
	static void SetPause(const bool bFrag) { m_bPause = bFrag; }

private:
	//�ϐ�
	static CInputKeyboard* m_pInputKeyboard;	//�L�[�{�[�h
	static CInputMouse* m_pInputMouse;			//�}�E�X
	static CSound* m_pSound;					//�T�E���h
	static CRenderer* m_pRenderer;				//�����_���[
	static CDebugProc* m_pDebProc;				//�f�o�b�O
	static CCamera* m_pCamera;					//�J����
	static CLight* m_pLight;					//���C�g
	static CTexture* m_pTexture;				//�e�N�X�`��
	static CXModel* m_pAgitModel;				//���F�A�W�g���f���|�C���^
	static int m_nFPS;							//FPS
	static DWORD m_dwFrameCount;				//�񂵂��t���[����

	//��
	static CXModel* m_pFragModel;	//�����f��

	static CScene* m_pScene;	//�V�[��

	static bool m_bPause;		//�|�[�Y���
};

#endif