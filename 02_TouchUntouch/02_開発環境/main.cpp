//======================================================
//
//���C������[main.cpp]
//Author:�Ό��D�n
//
//======================================================
#include <Windows.h>
#include <string.h>
#include "main.h"
#include "manager.h"

//�}�N����`
#define WINDOW_NAME			"Touch/Untouch"
#define FPS_SPEED			(500)	//FPS�v������

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//========================
//���C���֐�
//========================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int CmdShow)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	//�E�B���h�E�̗̈�i���������s�̒萔�j

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//�������T�C�Y
		CS_CLASSDC,							//�E�B���h�E�̃X�^�C��
		WindowProc,							//�E�B���h�E�v���V�[�W��
		0,									//�g�p���Ȃ�
		0,									//�g�p���Ȃ�
		hInstance,							//�C���X�^���X�n���h��
		LoadIcon(nullptr,IDI_APPLICATION),	//�^�X�N�o�[�̃A�C�R��
		LoadCursor(nullptr,IDC_ARROW),		//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			//�N���C�A���g�̈�̔w�i�F
		nullptr,							//���j���[�o�[
		CLASS_NAME,							//�N���X�̖��O
		LoadIcon(nullptr,IDI_APPLICATION)	//�A�v���P�[�V�����̃A�C�R��
	};

	HWND hWnd;	//�E�B���h�E�n���h��
	MSG msg;	//���b�Z�[�W�i�[

	//�����֌W
	DWORD dwCurrentTime;		//���ݎ���
	DWORD dwExecLastTime;		//�Ō�ɏ�����������
	DWORD dwFPSTime;			//�Ō��FPS�v����������

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(
		0,									//�g���E�B���h�E�X�^�C��
		CLASS_NAME,							//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,						//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,				//�E�B���h�E�X�^�C��
		CW_USEDEFAULT,						//�E�B���h�E�̍���X���W
		CW_USEDEFAULT,						//�E�B���h�E�̍���Y���W
		(rect.right - rect.left),			//�E�B���h�E�̕�
		(rect.bottom - rect.top),			//�E�B���h�E�̍���
		nullptr,								//�e�E�B���h�E�̃n���h��
		nullptr,								//���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,							//�C���X�^���X�n���h��
		nullptr								//�E�B���h�E�쐬�f�[�^
	);

	if(FAILED(CManager::GetInstance()->Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//����\�ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;		//������
	dwExecLastTime = timeGetTime();
	dwFPSTime = timeGetTime();

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, CmdShow);
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();
			if (dwCurrentTime - dwFPSTime >= FPS_SPEED)
			{
				CManager::GetInstance()->CheckFPS(dwCurrentTime, dwFPSTime);
				dwFPSTime = dwCurrentTime;
			}
			if ((dwCurrentTime - dwExecLastTime) >= PROC_SPEED)
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;
				//�X�V����
				CManager::GetInstance()->Update();

				//�`�揈��
				CManager::GetInstance()->Draw();
			}
		}
	}

	//�}�l�[�W���j��
	CManager::Release();

	//�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//========================
//�E�B���h�E�v���V�[�W��
//========================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);	//Destroy���b�Z�[�W�𑗂�
			}
			break;
		}
		break;
	case WM_CLOSE:
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{
			DestroyWindow(hWnd);	//Destroy���b�Z�[�W�𑗂�
		}
		else
		{
			return 0;
		}
		break;
	case WM_CREATE:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}