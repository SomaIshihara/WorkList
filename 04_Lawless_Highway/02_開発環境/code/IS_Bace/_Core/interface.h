//======================================================
//
//�C���^�[�t�F�[�X�ꗗ[interface.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _INTERFACE_H_
#define _INTERFACE_H_

//�O���錾
class CObject;

//�����蔻��֌W�C���^�[�t�F�[�X
__interface ICollisionReader
{
	D3DXVECTOR3 GetMove(void) = 0;
	D3DXVECTOR3 GetPosOld(void) = 0;
	void SetPos(const D3DXVECTOR3 pos) = 0;
	float GetWidth(void) = 0;
	float GetHeight(void) = 0;
	float GetDepth(void) = 0;
	CObject* GetObj(void) = 0;
};

#endif // !_INTERFACE_H_
