//==========================================================================================
//
//���̓v���O����[input.cpp]
//Author:�Ό��D�n�i�U����:���V�����j
//
//==========================================================================================
//Ver.3.0.0�iC++����̂��́j
//�g�p�\�ȓ���:�L�[�{�[�h�E�}�E�X�i�J�[�\���ʒu�E�ړ��ʁj�E�Q�[���p�b�h�i1~4��j
//==========================================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

//�}�N����`
#define NUM_KEY_MAX			(256)	//�L�[�̍ő吔
#define REPEATE_TIME		(150)	//���s�[�g�̊Ԋu
#define GAMEPAD_BUTTON_NUM	(14)	//�Q�[���p�b�h�̃{�^����
#define STICK_DEADZONE		(655)	//�V��
#define PAD_VIBE_FADE		(200)	//�U���̌�����

//�ÓI�����o�ϐ�
LPDIRECTINPUT8 CInput::m_pInput = nullptr;
int CInput::m_nNumAll = 0;
int CInputGamePad::m_nNumAll = 0;

//==================================================
//						���͖{��
//==================================================
//========================
//�R���X�g���N�^
//========================
CInput::CInput()
{

}

//========================
//�f�X�g���N�^
//========================
CInput::~CInput()
{}

//========================
//������
//========================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == nullptr)
	{
		//DireceInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&m_pInput, nullptr)))
		{
			return E_FAIL;
		}
	}

	//�g�p�R���g���[�������₷
	m_nNumAll++;

	return S_OK;
}

//========================
//�I��
//========================
void CInput::Uninit(void)
{
	//���̓f�o�C�X�̔j��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_nNumAll <= 1 && m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}

	//�g�p�R���g���[�������炷
	m_nNumAll--;
}

//==================================================
//						�L�[�{�[�h
//==================================================
//========================
//�R���X�g���N�^
//========================
CInputKeyboard::CInputKeyboard()
{
	//�L�[���E���ԃN���A
	for (int nCntInit = 0; nCntInit < NUM_KEY_MAX; nCntInit++)
	{
		//�L�[
		m_aKeyState[nCntInit].state = 0;
		m_aKeyState[nCntInit].trigger = 0;
		m_aKeyState[nCntInit].release = 0;
		m_aKeyState[nCntInit].repeate = 0;

		//����
		m_aKeyState[nCntInit].repeateTime.currentTime = 0;
	}
}

//========================
//�f�X�g���N�^
//========================
CInputKeyboard::~CInputKeyboard()
{}

//========================
//������
//========================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�{��
	CInput::Init(hInstance, hWnd);
	
	//�f�o�C�X�擾
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, nullptr)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h�ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	//���ԏ�����
	for (int nCntInit = 0; nCntInit < NUM_KEY_MAX; nCntInit++)
	{
		m_aKeyState[nCntInit].repeateTime.execLastTime = timeGetTime() - REPEATE_TIME;
	}

	return S_OK;
}

//========================
//�I��
//========================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//========================
//�X�V
//========================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	//���̓f�o�C�X����f�o�C�X���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyState[nCntKey].trigger = (m_aKeyState[nCntKey].state ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey].release = (m_aKeyState[nCntKey].state ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];

			//���s�[�g
			m_aKeyState[nCntKey].repeateTime.currentTime = timeGetTime();
			if (aKeyState[nCntKey] && (m_aKeyState[nCntKey].repeateTime.currentTime - m_aKeyState[nCntKey].repeateTime.execLastTime) > REPEATE_TIME)
			{
				m_aKeyState[nCntKey].repeateTime.execLastTime = m_aKeyState[nCntKey].repeateTime.currentTime;
				m_aKeyState[nCntKey].repeate = aKeyState[nCntKey];
			}
			else
			{
				m_aKeyState[nCntKey].repeate = 0;
			}
			//�v���X
			m_aKeyState[nCntKey].state = aKeyState[nCntKey];	//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//========================
//�L�[�{�[�h�̃v���X����Ԃ�����
//========================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey].state & 0x80) ? true : false;	//?����������邱�ƂɂȂ��Ă�݂�����
}

//========================
//�L�[�{�[�h�̃g���K�[����Ԃ�����
//========================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyState[nKey].trigger & 0x80) ? true : false;
}

//========================
//�L�[�{�[�h�̃����[�X����Ԃ�����
//========================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyState[nKey].release & 0x80) ? true : false;
}

//========================
//�L�[�{�[�h�̃��s�[�g����Ԃ�����
//========================
bool CInputKeyboard::GetRepeate(int nKey)
{
	return (m_aKeyState[nKey].repeate & 0x80) ? true : false;
}

//==================================================
//						�}�E�X
//==================================================
//========================
//�R���X�g���N�^
//========================
CInputMouse::CInputMouse()
{
	//���E���ԏ�����
	for (int nCntInit = 0; nCntInit < MOUSE_BUTTON_MAX; nCntInit++)
	{
		//���
		m_mouse.mb[nCntInit].trigger = 0;
		m_mouse.mb[nCntInit].release = 0;
		m_mouse.mb[nCntInit].repeate = 0;

		//����
		m_mouse.mb[nCntInit].repeateTime.currentTime = 0;
	}
}

//========================
//�f�X�g���N�^
//========================
CInputMouse::~CInputMouse()
{}

//========================
//������
//========================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�{��
	CInput::Init(hInstance, hWnd);

	//�f�o�C�X�擾
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, nullptr)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	//�������[�h�ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�}�E�X�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	//���ԏ�����
	for (int nCntInit = 0; nCntInit < MOUSE_BUTTON_MAX; nCntInit++)
	{
		m_mouse.mb[nCntInit].repeateTime.execLastTime = timeGetTime() - REPEATE_TIME;
	}

	return S_OK;
}

//========================
//�I��
//========================
void CInputMouse::Uninit(void)
{
	CInput::Uninit();
}

//========================
//�X�V
//========================
void CInputMouse::Update(void)
{
	DIMOUSESTATE MouseState;
	POINT point;

	//�}�E�X�擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &MouseState)))
	{
		for (int nCntKey = 0; nCntKey < MOUSE_BUTTON_MAX; nCntKey++)
		{
			//�g���K�[�ƃ����[�X
			m_mouse.mb[nCntKey].trigger = (m_mouse.state.rgbButtons[nCntKey] ^ MouseState.rgbButtons[nCntKey]) & MouseState.rgbButtons[nCntKey];
			m_mouse.mb[nCntKey].release = (m_mouse.state.rgbButtons[nCntKey] ^ MouseState.rgbButtons[nCntKey]) & ~MouseState.rgbButtons[nCntKey];

			//���s�[�g
			m_mouse.mb[nCntKey].repeateTime.currentTime = timeGetTime();
			if (MouseState.rgbButtons[nCntKey] && (m_mouse.mb[nCntKey].repeateTime.currentTime - m_mouse.mb[nCntKey].repeateTime.execLastTime) > REPEATE_TIME)
			{
				m_mouse.mb[nCntKey].repeateTime.execLastTime = m_mouse.mb[nCntKey].repeateTime.currentTime;
				m_mouse.mb[nCntKey].repeate = MouseState.rgbButtons[nCntKey];
			}
			else
			{
				m_mouse.mb[nCntKey].repeate = 0;
			}
		}

		//�v���X
		m_mouse.state = MouseState;	//�L�[�{�[�h�̃v���X����ۑ�

									//�ړ���
		m_mouse.move = D3DXVECTOR3((float)m_mouse.state.lX, (float)m_mouse.state.lY, CManager::FLOAT_ZERO);
	}
	else
	{
		m_pDevice->Acquire();
	}

	//�}�E�X���W�擾
	GetCursorPos(&point);
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &point);
	m_mouse.pos.x = (float)point.x;
	m_mouse.pos.y = (float)point.y;
}

//=================================
//�N���b�N�������W���烏�[���h���W�ɕϊ�
//=================================
D3DXVECTOR3 CInputMouse::ConvertClickPosToWorld(float fZ)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	CCamera* pCamera = CManager::GetCamera();

	D3DXMATRIX mtxView, mtxProj;
	D3DXMATRIX mtxViewPort;
	D3DXMATRIX mtx;
	D3DXVECTOR3 posClick = m_mouse.pos;
	posClick.z = fZ;	//Z���W�w��
	D3DXVECTOR3 posWorld;

	//�r���[�}�g���擾�E�t�s��
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	D3DXMatrixInverse(&mtxView, nullptr, &mtxView);

	//�v���W�F�N�V�����}�g���擾�E�t�s��
	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProj);
	D3DXMatrixInverse(&mtxProj, nullptr, &mtxProj);

	//�r���[�|�[�g�}�g���ݒ�E�t�s��
	D3DXMatrixIdentity(&mtxViewPort);
	mtxViewPort._11 = SCREEN_WIDTH * 0.5;
	mtxViewPort._22 = -SCREEN_HEIGHT * 0.5;
	mtxViewPort._41 = SCREEN_WIDTH * 0.5;
	mtxViewPort._42 = SCREEN_HEIGHT * 0.5;
	D3DXMatrixInverse(&mtxViewPort, nullptr, &mtxViewPort);

	//�S���|����
	mtx = mtxViewPort * mtxProj * mtxView;	//������D3DXMatrixMultiply����Ă�݂���

	//����Ń��[���h���W�ɕϊ��ł���
	D3DXVec3TransformCoord(&posWorld, &posClick, &mtx);

	return posWorld;
}

//========================
//�}�E�X�̃v���X����Ԃ�����
//=======================
bool CInputMouse::GetPress(int nButton)
{
	return m_mouse.state.rgbButtons[nButton] & 0x80 ? true : false;
}

//========================
//�}�E�X�̃g���K�[����Ԃ�����
//=======================
bool CInputMouse::GetTrigger(int nButton)
{
	return m_mouse.mb[nButton].trigger & 0x80 ? true : false;
}

//========================
//�}�E�X�̃����[�X����Ԃ�����
//=======================
bool CInputMouse::GetRelease(int nButton)
{
	return m_mouse.mb[nButton].release & 0x80 ? true : false;
}

//========================
//�}�E�X�̃��s�[�g����Ԃ�����
//=======================
bool CInputMouse::GetRepeate(int nButton)
{
	return m_mouse.mb[nButton].repeate & 0x80 ? true : false;
}

//========================
//�}�E�X�̃J�[�\���ʒu��Ԃ�����
//=======================
D3DXVECTOR3 CInputMouse::GetPos(void)
{
	return m_mouse.pos;
}

//========================
//�}�E�X�̃J�[�\���ړ��ʂ�Ԃ�����
//=======================
D3DXVECTOR3 CInputMouse::GetMove(void)
{
	return m_mouse.move;
}

//==================================================
//						�Q�[���p�b�h
//==================================================
//========================
//�R���X�g���N�^
//========================
CInputGamePad::CInputGamePad()
{
	//�l�N���A
	m_gamePad.state = {};
	m_gamePad.trigger = 0;
	m_gamePad.release = 0;
	m_gamePad.repeate = 0;
	m_gamePad.repeateTime.currentTime = 0;
	m_gamePad.wVibrPower = 0;
	m_gamePad.nVibrTime = 0;
	m_gamePad.Vibr_State = VIBE_STATE_00_STOP;
}

//========================
//�f�X�g���N�^
//========================
CInputGamePad::~CInputGamePad()
{}

//========================
//������
//========================
HRESULT CInputGamePad::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_nNumAll < MAX_USE_GAMEPAD)
	{//�g�p�\���ȉ�
		//�Q�[���p�b�h��
		m_gamePad.repeateTime.execLastTime = timeGetTime();

		//ID����U��
		m_nID = m_nNumAll;

		m_nNumAll++;
	}
	else
	{//�g�p�\���ȏ�
		return E_FAIL;
	}

	return S_OK;
}

//========================
//�I��
//========================
void CInputGamePad::Uninit(void)
{
	//�R���g���[���[�̐U����~
	StopVibration();

	//XInput�I��
	XInputEnable(false);

	//�{��
	CInput::Uninit();
}

//========================
//�X�V
//========================
void CInputGamePad::Update(void)
{
	XINPUT_STATE xInputState;

	//�Q�[���p�b�h������擾
	for (int nCntGPad = 0; nCntGPad < MAX_USE_GAMEPAD; nCntGPad++)
	{
		if (XInputGetState(nCntGPad, &xInputState) == ERROR_SUCCESS)
		{
			//�{�^���g���K�[���擾
			m_gamePad.trigger = (m_gamePad.state.Gamepad.wButtons ^ xInputState.Gamepad.wButtons) & xInputState.Gamepad.wButtons;

			//�{�^�������[�X���擾
			m_gamePad.release = (m_gamePad.state.Gamepad.wButtons ^ xInputState.Gamepad.wButtons) & ~xInputState.Gamepad.wButtons;

			//���s�[�g��񐶐�
			m_gamePad.repeateTime.currentTime = timeGetTime();
			for (int nCntKey = 0; nCntKey < GAMEPAD_BUTTON_NUM; nCntKey++)
			{
				if (m_gamePad.state.Gamepad.wButtons & 1 << nCntKey && (m_gamePad.repeateTime.currentTime - m_gamePad.repeateTime.execLastTime) > REPEATE_TIME)
				{
					m_gamePad.repeateTime.execLastTime = m_gamePad.repeateTime.currentTime;
					m_gamePad.repeate += 1 << nCntKey;
				}
			}

			//�v���X��񂻂̑��������ݒ�
			m_gamePad.state = xInputState;

			//�R���g���[���[�̐U����ԍX�V
			UpdateVibration();
		}
	}
}

//========================
//�Q�[���p�b�h�U����Ԃ̍X�V
//========================
void CInputGamePad::UpdateVibration(void)
{
	//�U����~��
	if (m_gamePad.nVibrTime <= 0)
	{
		m_gamePad.wVibrPower = 0;					// �U����    �O   �ɐݒ�
		m_gamePad.nVibrTime = 0;					//�p������   �O   �ɐݒ�
		m_gamePad.Vibr_State = VIBE_STATE_00_STOP;	//  ���  �u��~�v�ɐݒ�

		StopVibration();	//�Ώۂ̃R���g���[���[�̐U����~
	}

	//�U����
	else
	{
		//�p�����Ԍ���
		m_gamePad.nVibrTime--;

		//�o�C�u�̏�Ԃ��A���X�Ɏ�܂��Ă������̂ł���
		if (m_gamePad.Vibr_State == VIBE_STATE_02_FADE)
		{
			//�U���ʂ��Œ�l�����������
			if (m_gamePad.wVibrPower <= VIBE_POWER_MIN)
			{
				//�U�����~�߂�
				m_gamePad.wVibrPower = 0;
				m_gamePad.nVibrTime = 0;
				m_gamePad.Vibr_State = VIBE_STATE_00_STOP;

				StopVibration();	//�Ώۂ̃R���g���[���[�̐U����~
			}
			else
			{
				//���X�Ɍ���������
				m_gamePad.wVibrPower -= PAD_VIBE_FADE;
			}
		}

		XINPUT_VIBRATION Vibration;

		Vibration.wLeftMotorSpeed = m_gamePad.wVibrPower;	//���̃��[�^�[�̉�]���x��ݒ�
		Vibration.wRightMotorSpeed = m_gamePad.wVibrPower;	//�E�̃��[�^�[�̉�]���x��ݒ�

		XInputSetState(m_nID, &Vibration);	//�Ώۂ̃R���g���[���[�ɐU����ݒ�
	}
}

//========================
//�Ώۂ̃R���g���[���[�̐U����~
//========================
void CInputGamePad::StopVibration(void)
{
	XINPUT_VIBRATION Vibration = {0,0};

	//�Ώۂ̃R���g���[���[�̐U����OFF
	XInputSetState(m_nID, &Vibration);
}

//========================
//�Q�[���p�b�h�̃v���X����Ԃ�����
//=======================
bool CInputGamePad::GetPress(int nButton)
{
	return m_gamePad.state.Gamepad.wButtons & nButton ? true : false;
}

//========================
//�Q�[���p�b�h�̃g���K�[����Ԃ�����
//=======================
bool CInputGamePad::GetTrigger(int nButton)
{
	return m_gamePad.trigger & nButton ? true : false;
}

//========================
//�Q�[���p�b�h�̃����[�X����Ԃ�����
//=======================
bool CInputGamePad::GetRelease(int nButton)
{
	return m_gamePad.release & nButton ? true : false;
}

//========================
//�Q�[���p�b�h�̃��s�[�g����Ԃ�����
//=======================
bool CInputGamePad::GetRepeate(int nButton)
{
	return m_gamePad.repeate & nButton ? true : false;
}

//========================
//���X�e�B�b�N�̉�����Ԃ�����
//=======================
SHORT CInputGamePad::GetLStickX(void)
{
	//-�l�ő�Ȃ�+�l�ő�ɍ��킹��
	if (m_gamePad.state.Gamepad.sThumbLX < -STICK_MAX)
	{
		m_gamePad.state.Gamepad.sThumbLX = -STICK_MAX;
	}

	if (abs(m_gamePad.state.Gamepad.sThumbLX) > STICK_DEADZONE)
	{
		return m_gamePad.state.Gamepad.sThumbLX;
	}
	else
	{
		return 0;
	}
}

//========================
//���X�e�B�b�N�̏c����Ԃ�����
//=======================
SHORT CInputGamePad::GetLStickY(void)
{
	//-�l�ő�Ȃ�+�l�ő�ɍ��킹��
	if (m_gamePad.state.Gamepad.sThumbLY < -STICK_MAX)
	{
		m_gamePad.state.Gamepad.sThumbLY = -STICK_MAX;
	}

	if (abs(m_gamePad.state.Gamepad.sThumbLY) > STICK_DEADZONE)
	{
		return m_gamePad.state.Gamepad.sThumbLY;
	}
	else
	{
		return 0;
	}
}

//========================
//�E�X�e�B�b�N�̉�����Ԃ�����
//=======================
SHORT CInputGamePad::GetRStickX(void)
{
	//-�l�ő�Ȃ�+�l�ő�ɍ��킹��
	if (m_gamePad.state.Gamepad.sThumbRX < -STICK_MAX)
	{
		m_gamePad.state.Gamepad.sThumbRX = -STICK_MAX;
	}

	if (abs(m_gamePad.state.Gamepad.sThumbRX) > STICK_DEADZONE)
	{
		return m_gamePad.state.Gamepad.sThumbRX;
	}
	else
	{
		return 0;
	}
}

//========================
//�E�X�e�B�b�N�̏c����Ԃ�����
//=======================
SHORT CInputGamePad::GetRStickY(void)
{
	//-�l�ő�Ȃ�+�l�ő�ɍ��킹��
	if (m_gamePad.state.Gamepad.sThumbRY < -STICK_MAX)
	{
		m_gamePad.state.Gamepad.sThumbRY = -STICK_MAX;
	}

	if (abs(m_gamePad.state.Gamepad.sThumbRY) > STICK_DEADZONE)
	{
		return m_gamePad.state.Gamepad.sThumbRY;
	}
	else
	{
		return 0;
	}
}

//========================
//�Q�[���p�b�h�U���ݒ�
//========================
void CInputGamePad::SetPadVibration(WORD wPower, int nVibeTime, VIBE_STATE State)
{
	m_gamePad.wVibrPower = wPower;		//�����ݒ�
	m_gamePad.nVibrTime = nVibeTime;	//���Ԑݒ�
	m_gamePad.Vibr_State = State;		//��Ԑݒ�

	XINPUT_VIBRATION Vibration;

	Vibration.wLeftMotorSpeed = wPower;		//���̃��[�^�[�̉�]���x��ݒ�
	Vibration.wRightMotorSpeed = wPower;	//�E�̃��[�^�[�̉�]���x��ݒ�

	XInputSetState(m_nID, &Vibration);	//�Ώۂ̃R���g���[���[�ɐU����ݒ�
}