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

//����֌W�C���^�[�t�F�[�X
__interface IControllStat
{
	int GetType(void) = 0;		//���쒆�̃L�����^�C�v
	int GetPress(void) = 0;		//�����
	bool IsJump(void) = 0;		//�W�����v���邩
};

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

//�X�R�A�ݒ�p�C���^�[�t�F�[�X
__interface IScoreSetter
{
	void Set(const int nScore) = 0;	//�X�R�A�ݒ�
	void Add(const int nAdd) = 0;	//�X�R�A���Z
};

#endif // !_INTERFACE_H_
