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
class CInputGamePad;
class CRenderer;
class CDebugProc;
class CSound;
class CCamera;
class CLight;
class CTexture;
class CVariableManager;

//�V�[���N���X
class CScene
{
public:
	//���[�h��
	typedef enum
	{
		MODE_TITLE = 0,	//�^�C�g��
		MODE_TUTORIAL,	//�`���[�g���A��
		MODE_GAME,		//�Q�[��
		MODE_RESULT,	//���U���g
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

private:
	MODE m_mode;	//���[�h
};
class CManager
{
public:
	//�ÓIconst
	static const int INT_ZERO;				//int�^��0
	static const float FLT_ZERO;			//float�^��0
	static const D3DXVECTOR2 VEC2_ZERO;		//vec2�^��0
	static const D3DXVECTOR3 VEC3_ZERO;		//vec3�^��0
	static const D3DXVECTOR3 SCREEN_CENTER;	//��ʒ���

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
	static CManager* GetInstance(void);
	CInputKeyboard* GetInputKeyboard(void) { return m_pInputKeyboard; }
	CInputMouse* GetInputMouse(void) { return m_pInputMouse; }
	CInputGamePad* GetInputGamePad(void) { return m_pInputPad; }
	CSound* GetSound(void) { return m_pSound; }
	CRenderer* GetRenderer(void) { return m_pRenderer; }
	CDebugProc* GetDebProc(void) { return m_pDebProc; }
	CCamera* GetCamera(void) { return m_pCamera; }
	CLight* GetLight(void) { return m_pLight; }
	CTexture* GetTexture(void) { return m_pTexture; }
	CVariableManager* GetVariableManager(void) { return m_pVariableManager; }

	//�j��
	static HRESULT Release(void);

	//�V�[���n
	void SetMode(CScene::MODE mode);
	CScene::MODE GetMode(void) { return m_pScene->GetMode(); }
	CScene* GetScene(void) { return m_pScene; }

	//�X�V�ݒ�E�擾
	void SetEnableUpdate(const bool bEnable) { m_bEnableUpdate = bEnable; }
	bool GetEnableUpdate(void) { return m_bEnableUpdate; }

private:
	//�ϐ�
	static CManager* m_pManager;			//�}�l�[�W���i�V���O���g���j
	CInputKeyboard* m_pInputKeyboard;		//�L�[�{�[�h
	CInputMouse* m_pInputMouse;				//�}�E�X
	CInputGamePad* m_pInputPad;				//�Q�[���p�b�h
	CSound* m_pSound;						//�T�E���h
	CRenderer* m_pRenderer;					//�����_���[
	CDebugProc* m_pDebProc;					//�f�o�b�O
	CCamera* m_pCamera;						//�J����
	CLight* m_pLight;						//���C�g
	CTexture* m_pTexture;					//�e�N�X�`��
	CVariableManager* m_pVariableManager;	//�ǉ��ϐ��}�l
	int m_nFPS;								//FPS
	DWORD m_dwFrameCount;					//�񂵂��t���[����
	CScene* m_pScene;						//�V�[��
	bool m_bEnableUpdate;					//�I�u�W�F�X�V���邩
};

#endif