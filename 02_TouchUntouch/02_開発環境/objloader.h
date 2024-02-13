//======================================================
//
//�I�u�W�F�N�g�ǂݍ��ݏ����̃w�b�_[objloader.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_
#include "main.h"
#include "manager.h"
#include "object.h"

typedef unsigned char BINCODE;
//�o�C�i���̃R�[�h���e
//�V�X�e��(0b00xxxxxx)
#define BIN_CODE_SYSTEM				(0b00 << 6)
#define BIN_CODE_SCRIPT				(BIN_CODE_SYSTEM + 0b000000)
#define BIN_CODE_END_SCRIPT			(BIN_CODE_SYSTEM + 0b000001)
#define BIN_CODE_USERDEF			(BIN_CODE_SYSTEM + 0b000010)
//���f���n(0b01xxxxxx)
#define BIN_CODE_MODEL				(0b01 << 6)
#define BIN_CODE_TEXTURE_FILENAME	(BIN_CODE_MODEL + 0b000000)
#define BIN_CODE_MODEL_FILENAME		(BIN_CODE_MODEL + 0b000001)
#define BIN_CODE_MODELSET			(BIN_CODE_MODEL + 0b000010)
#define BIN_CODE_TEXTURE_NUM		(BIN_CODE_MODEL + 0b000011)
#define BIN_CODE_MODEL_NUM			(BIN_CODE_MODEL + 0b000100)
//���[�V�����n(0b10xxxxxx)
#define BIN_CODE_MOTION				(0b10 << 6)

//�I�u�W�F�N�g�ǂݍ��݃N���X
class CObjLoader
{
public:
	//�ÓIconst
	static const int STR_LENGTH;	//������̒���

	enum OBJTYPE
	{
		OBJTYPE_BLOCK = 0,
		OBJTYPE_SWITCH,
		OBJTYPE_GOAL,
		OBJTYPE_ITEM,
		OBJTYPE_DELETED_01,	//�@�\�폜�ɂ�薢��`
		OBJTYPE_DELETED_02,	//�@�\�폜�ɂ�薢��`
		OBJTYPE_TUTORIALOBJ,
	};

	enum LOADRESULT
	{
		RES_OK = 0,
		RES_ERR_FILE_NOTFOUND,
		RES_MAX
	};

	//�ǂݍ���
	static LOADRESULT LoadData(const char* pPath);
	static LOADRESULT SaveData(const char* pPath);
};

#endif // !_OBJECT_H_
