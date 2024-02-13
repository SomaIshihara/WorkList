//==========================================================================================
//
//���̓v���O�����̃w�b�_[input.h]
//Author:�Ό��D�n�i�U����:���V�����j
//
//==========================================================================================
//Ver.3.0.0�iC++����̂��́j
//�g�p�\�ȓ���:�L�[�{�[�h�E�}�E�X�i�J�[�\���ʒu�E�ړ��ʁj�E�Q�[���p�b�h�i1~4��j
//==========================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//==========================================================================================
//�}�N����`
//==========================================================================================
#define STICK_MAX			(32767)	//�X�e�B�b�N�ő�l
#define MOUSE_CLICK_LEFT	(0)		//�}�E�X���N���b�N
#define MOUSE_CLICK_RIGHT	(1)		//�}�E�X�E�N���b�N
#define MAX_USE_GAMEPAD		(4)		//�Q�[���p�b�h�g�p�\�䐔
#define MOUSE_BUTTON_MAX	(3)		//�}�E�X�{�^���̍ő吔

#define VIBE_POWER_MIN			(7000)	//�Œ�U����
#define VIBE_POWER_LEVEL_01		(10000)	//��߂̐U��
#define VIBE_POWER_LEVEL_02		(23000)	//�����炢�̐U��
#define VIBE_POWER_LEVEL_03		(37000)	//���߂̐U��
#define VIBE_POWER_LEVEL_04		(50000)	//���Ȃ苭�߂̐U��
#define VIBE_POWER_LEVEL_05		(65535)	//�ő�U��

//==========================================================================================
//�\���̒�`
//==========================================================================================
//���s�[�g����
typedef struct
{
	DWORD currentTime;	//���݂̎���
	DWORD execLastTime;	//�Ō��true�ɂ�������
} RepeateTime;

//**************************************************
//*						�N���X					   *
//**************************************************
//==================================================
//						���͖{��
//==================================================
class CInput
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CInput();
	virtual ~CInput();

	//��{����
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;
protected:
	static LPDIRECTINPUT8 m_pInput;	//�I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8 m_pDevice;	//�f�o�C�X
private:
	static int m_nNumAll;			//�g�p�R���g���[����
};

//==================================================
//						�L�[�{�[�h
//==================================================
class CInputKeyboard : public CInput
{
public:
	//�L�[�{�[�h�\����
	typedef struct
	{
		BYTE state;		//��ԁi�ۑ��p����уv���X���j
		BYTE trigger;	//�g���K�[���
		BYTE release;	//�����[�X���
		BYTE repeate;	//���s�[�g���
		RepeateTime repeateTime;	//���s�[�g����
	} Keyboard;

	//�R���X�g���N�^�E�f�X�g���N�^
	CInputKeyboard();
	~CInputKeyboard();

	//��{����
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	//�擾
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeate(int nKey);

private:
	Keyboard m_aKeyState[256];	//�L�[�{�[�h���ׂĂ̏�ԁi�g���K�[���܂ށj
};

//==================================================
//						�}�E�X
//==================================================
class CInputMouse : public CInput
{
public:
	//�}�E�X�̃{�^����
	typedef struct
	{
		BYTE trigger;		//�{�^���̃g���K�[���
		BYTE release;		//�{�^���̃����[�X���
		BYTE repeate;		//���s�[�g���
		RepeateTime repeateTime;	//���s�[�g����
	} MouseButton;

	//�}�E�X�\����
	typedef struct
	{
		MouseButton mb[MOUSE_BUTTON_MAX];	//�}�E�X�{�^��
		DIMOUSESTATE state;					//��Ԃ���уv���X���
		D3DXVECTOR3 pos;					//�ʒu
		D3DXVECTOR3 move;					//�ړ���
	} Mouse;

	//�R���X�g���N�^�E�f�X�g���N�^
	CInputMouse();
	~CInputMouse();

	//��{����
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	//�N���b�N���W�����[���h���W�ɕϊ�
	D3DXVECTOR3 ConvertClickPosToWorld(float fZ);

	//�擾
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeate(int nKey);
	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetMove(void);
	int GetWheel(void) { return m_mouse.state.lZ; }

private:
	Mouse m_mouse;	//�}�E�X���ׂ�
};

//==================================================
//					 �Q�[���p�b�h
//==================================================
class CInputGamePad : public CInput
{
public:
	//�Q�[���p�b�h�̐U�����
	typedef enum
	{
		VIBE_STATE_00_STOP,	//��~
		VIBE_STATE_01_LOOP,	//�����Ɠ����U��
		VIBE_STATE_02_FADE,	//���X�ɗ��������Ă���
		VIBE_STATE_MAX
	}VIBE_STATE;

	//�Q�[���p�b�h�\����
	typedef struct
	{
		XINPUT_STATE state;		//��ԑS���i����уv���X���j
		WORD trigger;			//�g���K�[���
		WORD release;			//�����[�X���
		WORD repeate;			//���s�[�g���
		RepeateTime repeateTime;	//���s�[�g����

		VIBE_STATE Vibr_State;	//�U���̏��
		WORD wVibrPower;		//�U���̋���
		int nVibrTime;			//�U�������鎞��
	} GamePad;


	//�R���X�g���N�^�E�f�X�g���N�^
	CInputGamePad();
	~CInputGamePad();

	//��{����
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	//�U������
	void UpdateVibration(void);
	void StopVibration(void);
	void SetPadVibration(WORD wPower, int nVibeTime, VIBE_STATE State);

	//�擾
	bool GetPress(int nButton);
	bool GetTrigger(int nButton);
	bool GetRelease(int nButton);
	bool GetRepeate(int nButton);
	SHORT GetLStickX(void);
	SHORT GetLStickY(void);
	SHORT GetRStickX(void);
	SHORT GetRStickY(void);
private:
	static int m_nNumAll;//�Q�[���p�b�h��
	GamePad m_gamePad;	//�Q�[���p�b�h���ׂ�
	int m_nID;			//�Q�[���p�b�hID
};

#endif // !_INPUT_H_
