//======================================================
//
//�I�u�W�F�N�g�ǂݍ��ݏ���[objloader.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_

//�I�u�W�F�N�g�ǂݍ��ݖ��O���
namespace ISMD_IO
{
	//const
	const int STR_LENGTH = 256;	//������̒���

	//�o�C�i���̃R�[�h���e
	typedef unsigned char BINCODE;	//�R�[�h�ϐ���`
	//�V�X�e��(0b00xxxxxx)
	const BINCODE BIN_CODE_SYSTEM			= 0b00 << 6;
	const BINCODE BIN_CODE_SCRIPT			= BIN_CODE_SYSTEM + 0b000000;
	const BINCODE BIN_CODE_END_SCRIPT		= BIN_CODE_SYSTEM + 0b000001;
	const BINCODE BIN_CODE_USERDEF			= BIN_CODE_SYSTEM + 0b000010;	//����폜�\��
	//���f���n(0b01xxxxxx)
	const BINCODE BIN_CODE_MODEL			= 0b01 << 6;
	const BINCODE BIN_CODE_TEXTURE_NUM		= BIN_CODE_MODEL + 0b000011;
	const BINCODE BIN_CODE_TEXTURE_FILENAME = BIN_CODE_MODEL + 0b000000;
	const BINCODE BIN_CODE_MODEL_NUM		= BIN_CODE_MODEL + 0b000100;
	const BINCODE BIN_CODE_MODEL_FILENAME	= BIN_CODE_MODEL + 0b000001;
	const BINCODE BIN_CODE_CAMERASET		= BIN_CODE_MODEL + 0b000101;
	const BINCODE BIN_CODE_LIGHTSET			= BIN_CODE_MODEL + 0b000110;
	const BINCODE BIN_CODE_SKYSET			= BIN_CODE_MODEL + 0b000111;
	const BINCODE BIN_CODE_MOUNTAINSET		= BIN_CODE_MODEL + 0b001000;
	const BINCODE BIN_CODE_WALLSET			= BIN_CODE_MODEL + 0b001001;
	const BINCODE BIN_CODE_MODELSET			= BIN_CODE_MODEL + 0b000010;
	const BINCODE BIN_CODE_BILLBOARDSET		= BIN_CODE_MODEL + 0b001010;
	const BINCODE BIN_CODE_PLAYERSET		= BIN_CODE_MODEL + 0b001011;

	//�ǂݍ��݌���
	enum class LOADRESULT
	{
		RES_OK = 0,
		RES_ERR_FILE_NOTFOUND,
		RES_MAX
	};

	//�ǂݍ���
	LOADRESULT LoadData(const char* pPath);
	LOADRESULT SaveData(const char* pPath);
};

#endif // !_OBJLOADER_H_
