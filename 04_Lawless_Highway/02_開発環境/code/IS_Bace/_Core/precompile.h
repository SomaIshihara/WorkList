#ifndef PRECOMPILE_H_
#define PRECOMPILE_H_

#include <Windows.h>
#include <XInput.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION	(0x0800)	//�r���h���̌x���Ώ�
#include "dinput.h"
#include "xaudio2.h"
#include <assert.h>
#include <stdio.h>

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")

#endif // !PRECOMPILE_H_
