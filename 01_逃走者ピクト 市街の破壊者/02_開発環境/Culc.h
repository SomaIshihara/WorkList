//==========================================
//
//�v�Z�v���O�����̃w�b�_[Culc.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _CULC_H_
#define _CULC_H_
#include "main.h"

//�}�N��
#define ACCELERATION_GRAVITY	(9.8f)	//�d�͉����x
#define TWO_PI		(2 * D3DX_PI)		//360�x�i2��[rad]�j

//����
#define LEFT_UP		(-0.75f * D3DX_PI)	//����
#define RIGHT_UP	(0.75f * D3DX_PI)	//�E��
#define LEFT_DOWN	(-0.25f * D3DX_PI)	//����
#define RIGHT_DOWN	(0.25f * D3DX_PI)	//�E��
#define UP			(1.0f * D3DX_PI)	//�^��
#define DOWN		(0.0f * D3DX_PI)	//�^��
#define LEFT		(-0.5f * D3DX_PI)	//��
#define RIGHT		(0.5f * D3DX_PI)	//�E

//�֗��}�N���֐�
#define FIX_ROT(x)				(fmodf(x + (D3DX_PI * 3), D3DX_PI * 2) - D3DX_PI)	//�p�x��-PI~PI�ɏC��
#define fatof(x)				(float)atof(x)										//�ʏ��atof����double�^�ŕԂ��Ă���̂�float�L���X�g���s���悤�ɂ�������
#define TASUKIGAKE(ax,az,bx,bz)	((az * bx) - (ax * bz))								//���O�̒ʂ�B����ȏ�̐����͂Ȃ��B
#define PYTHAGORAS(a,b)			sqrtf(powf(a,2) + powf(b,2))						//�O�����̒藝

//�v�Z�֐�
D3DXVECTOR3 RotateVtx(const D3DXVECTOR3 vtx, const D3DXVECTOR3 rot, const D3DXVECTOR3 posCenter);

#endif // !_BILLBOARD_H_
