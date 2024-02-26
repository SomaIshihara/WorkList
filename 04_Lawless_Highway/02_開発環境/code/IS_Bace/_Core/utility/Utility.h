//======================================================
//
//�֗��Ȃ��̂���[Utility.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _UTILITY_H_
#define _UTILITY_H_

//�x�� 
#define STRING2(x) #x
#define STRING(x) STRING2(x)
#define PutWarning(x) __pragma(message(__FILE__ "(" STRING(__LINE__) "):warning:" x));

namespace IS_Utility
{
	//=============================================================
	// ���͂��߂�ǂ��������̂��Ē�`
	//=============================================================
	typedef D3DXVECTOR2 Vec2;
	typedef D3DXVECTOR3 Vec3;
	typedef D3DCOLOR Color;

	//=============================================================
	// �ł����݂߂�ǂ�����
	//=============================================================
	const D3DXVECTOR2 VEC2_ZERO = D3DXVECTOR2(0.0f,0.0f);			//vec2�^��0
	const D3DXVECTOR3 VEC3_ZERO = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//vec3�^��0

	//=============================================================
	// ���w�n�Ŏg�������Ȃ���
	//=============================================================
	const float ACCELERATION_GRAVITY = 9.8f;	//�d�͉����x
	const float PI = D3DX_PI;					//1PI[rad]
	const float TWO_PI = 2.0f * D3DX_PI;		//2PI[rad]

	//=============================================================
	// ����
	//=============================================================
	const float LEFT_UP		= -0.75f * D3DX_PI;	//����
	const float RIGHT_UP	= 0.75f * D3DX_PI;	//�E��
	const float LEFT_DOWN	= -0.25f * D3DX_PI;	//����
	const float RIGHT_DOWN	= 0.25f * D3DX_PI;	//�E��
	const float UP			= 1.0f * D3DX_PI;	//�^��
	const float DOWN		= 0.0f * D3DX_PI;	//�^��
	const float LEFT		= -0.5f * D3DX_PI;	//��
	const float RIGHT		= 0.5f * D3DX_PI;	//�E

	//=============================================================
	// �v�Z�֐�
	//=============================================================
	//*************************************************************
	// ���l��ݒ肵���͈͓��ɒ���
	//*************************************************************
	template<typename T> inline T Clamp(T num, T max, T min)
	{
		if (num >= max)
		{//�ő�l�ȏ�Ȃ�ő�l
			return max;
		}
		else if (num <= min)
		{//�Œ�l�ȉ��Ȃ�Œ�l
			return min;
		}
		else
		{//�ő�ƍŒ�̊�
			return num;
		}
	}

	//*************************************************************
	// ���̑�
	//*************************************************************
	float FixRot(const float fRaw);
	D3DXVECTOR3 RotateVtx(const D3DXVECTOR3 vtx, const D3DXVECTOR3 rot, const D3DXVECTOR3 posCenter);
	inline float fatof(const char* str) { return (float)atof(str); }
	inline float Pythagoras(float fa, float fb) { return sqrtf(powf(fa, 2) + powf(fb, 2)); }
	float Vec2Closs(Vec3 a, Vec3 b);
}

#endif // !_UTILITY_H_
