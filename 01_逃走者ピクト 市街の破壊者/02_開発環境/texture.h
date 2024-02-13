//======================================================
//
//�e�N�X�`���ۑ��N���X�̃w�b�_[texture.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"
#define MAX_STR		(256)
#define MAX_TEXTURE	(128)	//�e�N�X�`����

//�e�N�X�`���ۑ��N���X
class CTexture
{
public:
	//���O�ǂݍ��݃e�N�X�`����
	typedef enum
	{
		PRELOAD_TITLELOGO = 0,
		PRELOAD_FADE,
		PRELOAD_SLIDER_01,
		PRELOAD_SLIDER_02,
		PRELOAD_SLIDER_03,
		PRELOAD_HIRE,
		PRELOAD_TITLE_START,
		PRELOAD_TITLE_RANK,
		PRELOAD_PAUSE,
		PRELOAD_PAUSEBUTTON_01,
		PRELOAD_PAUSEBUTTON_02,
		PRELOAD_PAUSEBUTTON_03,
		PRELOAD_PAUSEBUTTON_04,
		PRELOAD_RESULT_HEADLINE,
		PRELOAD_RESULT_01,
		PRELOAD_RESULT_02,
		PRELOAD_RESULT_03,
		PRELOAD_NUMBER,
		PRELOAD_SYMBOL,
		PRELOAD_WARNING_LIFE,
		PRELOAD_HAVEICON_01,
		PRELOAD_HAVEICON_02,
		PRELOAD_HAVEICON_03,
		PRELOAD_TUTORIAL_01,
		PRELOAD_TUTORIAL_02,
		PRELOAD_TUTORIAL_03,
		PRELOAD_TUTORIAL_04,
		PRELOAD_TUTORIAL,
		PRELOAD_LV,
		PRELOAD_ASPHALT,
		PRELOAD_COUNTDOWN_01,
		PRELOAD_COUNTDOWN_02,
	} PRELOAD;

	//�p�^�[���e�N�X�`���\���̒�`
	typedef struct
	{
		LPDIRECT3DTEXTURE9 pTexture;	//�e�N�X�`���|�C���^
		int nPatternWidth;				//�p�^�[����
		int nPatternHeight;				//�p�^�[������
	} PatternTexture;
	//�R���X�g���N�^�E�f�X�g���N�^
	CTexture();
	~CTexture();

	//�S�ǂݍ��݁E�j��
	HRESULT Load(const char* pPath);	//���炩���ߓǂݍ��݂����e�N�X�`���ǂݍ���
	void Unload(void);					//�ǉ����������܂߂Ă��ׂĔj��

	int Regist(const char* pPath, const int nPatWidth = 1, const int nPatHeight = 1);	//�ǉ����镪�̓ǂݍ���
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);											//�e�N�X�`���擾
	int GetPatWidth(int nIdx);					//�p�^�[�����擾
	int GetPatHeight(int nIdx);					//�p�^�[�������擾

private:
	PatternTexture m_apTexture[MAX_TEXTURE];		//�e�N�X�`���|�C���^
	char m_aFilepath[MAX_TEXTURE][MAX_STR];			//�e�N�X�`���p�X
	static int m_nNumAll;							//�e�N�X�`������
};

#endif // !_TEXTURE_H_
