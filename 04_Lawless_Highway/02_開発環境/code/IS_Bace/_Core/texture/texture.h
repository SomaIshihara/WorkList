//======================================================
//
//�e�N�X�`���ۑ��N���X�̃w�b�_[texture.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#define MAX_STR		(256)
#define MAX_TEXTURE	(128)	//�e�N�X�`����

//�e�N�X�`���ۑ��N���X
class CTexture
{
public:
	//���O�ǂݍ��݃e�N�X�`����
	enum PRELOAD
	{
		PRELOAD_00_TITLELOGO = 0,	//�^�C�g�����S
		PRELOAD_01_PUSHANYBUTTON,	//�����{�^�������e�L�X�g
		PRELOAD_02_TUTORIAL_TEXT_01,//�`���[�g���A���e�L�X�g
		PRELOAD_03_TUTORIAL_SKIP,	//�`���[�g���A���X�L�b�v�e�L�X�g
		PRELOAD_04_TIMER_NUMBER,	//�^�C�}�[�̐���
		PRELOAD_05_TIMER_SYMBOL,	//�^�C�}�[�̋L��
		PRELOAD_06_LATETIME_BEF,	//�x���܂�
		PRELOAD_07_LATETIME_AFT,	//�x������
		PRELOAD_08_PAUSE_TEXT,		//�|�[�Y�e�L�X�g
		PRELOAD_09_PAUSE_CONTINUE,	//�|�[�Y�̑�����
		PRELOAD_10_PAUSE_RESTART,	//�|�[�Y�̃��X�^�[�g
		PRELOAD_11_PAUSE_RETURN,	//�|�[�Y�̋A��
		PRELOAD_12_PAUSE_SCREENSHOT,//�|�[�Y�̃X�N�V��
		PRELOAD_13_RESULT_SUCCESS,	//���U���g�̐����e�L�X�g
		PRELOAD_14_RESULT_FAILURE,	//���U���g�̒x���e�L�X�g
		PRELOAD_15_RANKING_TEXT,	//�����L���O�e�L�X�g
		PRELOAD_16_1ST,				//1��
		PRELOAD_17_2ND,				//2��
		PRELOAD_18_3RD,				//3��
		PRELOAD_19_4TH,				//4��
		PRELOAD_20_5TH,				//5��
		PRELOAD_21_ROAD,			//���H
		PRELOAD_22_GOAL,			//�S�[��
		PRELOAD_23_CONFIG_KB,
		PRELOAD_24_CONFIG_GP,
		PRELOAD_25_EFFECT_SMOKE,
		PRELOAD_26_EFFECT_FIRE,
		PRELOAD_27_TUTORIAL_01_KB,	//�`���[�g���A���e�L�X�g01
		PRELOAD_28_TUTORIAL_01_GP,
		PRELOAD_29_TUTORIAL_02_KB,	//�`���[�g���A���e�L�X�g02
		PRELOAD_30_TUTORIAL_02_GP,
		PRELOAD_31_TUTORIAL_03_KB,	//�`���[�g���A���e�L�X�g03
		PRELOAD_32_TUTORIAL_03_GP,
		PRELOAD_33_TUTORIAL_04,		//�`���[�g���A���e�L�X�g04
		PRELOAD_34_FIELD_LEAF,		//�n�ʗp��
		PRELOAD_35_SPEEDMETER_01,	//�X�s�[�h���[�^�[�̘g
		PRELOAD_36_SPEEDMETER_02,	//�X�s�[�h���[�^�[�̐j
		PRELOAD_MAX
	};

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
