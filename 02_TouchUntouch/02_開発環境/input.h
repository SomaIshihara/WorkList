//==========================================================================================
//
//���̓v���O�����̃w�b�_[input.h]
//Author:�Ό��D�n�i�U����:���V�����j
//
//==========================================================================================
//Ver.3.0.1�i�A�N�V�����V���[�e�B���O�}�X�^�[��j
//�g�p�\�ȓ���:�L�[�{�[�h�E�}�E�X�i�J�[�\���ʒu�E�ړ��ʁE�N���b�N�j�E�Q�[���p�b�h�i1~4��j
//==========================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//==================================================
//						���͖{��
//==================================================
class CInput
{
public:
	//���s�[�g����
	typedef struct
	{
		DWORD currentTime;	//���݂̎���
		DWORD execLastTime;	//�Ō��true�ɂ�������
	} RepeateTime;

	//�ÓIconst
	static const int REPEATE_TIME;

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

	//�ÓIconst
	static const int NUM_KEY_MAX;

	//�R���X�g���N�^�E�f�X�g���N�^
	CInputKeyboard();
	~CInputKeyboard();

	//��{����
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	//�擾
	bool GetPress(int nKey) { return (m_aKeyState[nKey].state & 0x80) ? true : false; }
	bool GetTrigger(int nKey) { return (m_aKeyState[nKey].trigger & 0x80) ? true : false; }
	bool GetRelease(int nKey) { return (m_aKeyState[nKey].release & 0x80) ? true : false; }
	bool GetRepeate(int nKey) { return (m_aKeyState[nKey].repeate & 0x80) ? true : false; }

private:
	Keyboard m_aKeyState[256];	//�L�[�{�[�h���ׂĂ̏�ԁi�g���K�[���܂ށj
};

//==================================================
//						�}�E�X
//==================================================
class CInputMouse : public CInput
{
public:
	//�ÓIconst
	static const int CLICK_LEFT;
	static const int CLICK_RIGHT;
	static const int BUTTON_MAX;

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
		MouseButton* mb;			//�}�E�X�{�^��
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
	bool GetPress(int nButton) { return m_mouse.state.rgbButtons[nButton] & 0x80 ? true : false; }
	bool GetTrigger(int nButton) { return m_mouse.mb[nButton].trigger & 0x80 ? true : false; }
	bool GetRelease(int nButton) { return m_mouse.mb[nButton].release & 0x80 ? true : false; }
	bool GetRepeate(int nButton) { return m_mouse.mb[nButton].repeate & 0x80 ? true : false; }
	D3DXVECTOR3 GetPos(void) { return m_mouse.pos; }
	D3DXVECTOR3 GetMove(void) { return m_mouse.move; }
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
	//�ÓIconst
	static const int MAX_USE_GAMEPAD;
	static const int STICK_MAX;
	static const int STICK_DEADZONE;
	static const int BUTTON_NUM;
	static const int VIBE_POWER_MIN;
	static const int VIBE_POWER_LEVEL_01;
	static const int VIBE_POWER_LEVEL_02;
	static const int VIBE_POWER_LEVEL_03;
	static const int VIBE_POWER_LEVEL_04;
	static const int VIBE_POWER_LEVEL_05;
	static const int VIBE_FADE;

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
		XINPUT_STATE state;			//��ԑS���i����уv���X���j
		WORD trigger;				//�g���K�[���
		WORD release;				//�����[�X���
		WORD repeate;				//���s�[�g���
		RepeateTime repeateTime;	//���s�[�g����

		VIBE_STATE Vibr_State;		//�U���̏��
		WORD wVibrPower;			//�U���̋���
		int nVibrTime;				//�U�������鎞��
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
	bool GetPress(int nButton) { return m_gamePad.state.Gamepad.wButtons & nButton ? true : false; }
	bool GetTrigger(int nButton) { return m_gamePad.trigger & nButton ? true : false; }
	bool GetRelease(int nButton) { return m_gamePad.release & nButton ? true : false; }
	bool GetRepeate(int nButton) { return m_gamePad.repeate & nButton ? true : false; }
	SHORT GetLStickX(void) { return AdjustStick(m_gamePad.state.Gamepad.sThumbLX); }
	SHORT GetLStickY(void) { return AdjustStick(m_gamePad.state.Gamepad.sThumbLY); }
	SHORT GetRStickX(void) { return AdjustStick(m_gamePad.state.Gamepad.sThumbRX); }
	SHORT GetRStickY(void) { return AdjustStick(m_gamePad.state.Gamepad.sThumbRY); }
	bool IsConnect(void) { return m_bConnect; }
private:
	SHORT AdjustStick(SHORT stick);
	static int m_nNumAll;//�Q�[���p�b�h��
	GamePad m_gamePad;	//�Q�[���p�b�h���ׂ�
	int m_nID;			//�Q�[���p�b�hID
	bool m_bConnect;	//�ڑ�����Ă��邩
};

#endif // !_INPUT_H_
