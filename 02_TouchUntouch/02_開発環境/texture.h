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
		PRELOAD_01_STARTKB,			//�X�^�[�g�����iKB�j
		PRELOAD_02_STARTGP,			//�X�^�[�g�����iGP�j
		PRELOAD_03_NUMBER,			//����
		PRELOAD_04_TIMERSTR,		//�^�C�}�[����
		PRELOAD_05_SCORESTR,		//�X�R�A����
		PRELOAD_06_BONUSSTR,		//�{�[�i�X����
		PRELOAD_07_SCENERANKKB,		//�����L���O�J�ڕ����iKB�j
		PRELOAD_08_SCENERANKGP,		//�����L���O�J�ڕ����iGP�j
		PRELOAD_09_RANKSTR,			//�����L���O����
		PRELOAD_10_RANK_01,			//�����L���O�i1�ʁ`�j
		PRELOAD_11_RANK_02,
		PRELOAD_12_RANK_03,
		PRELOAD_13_RANK_04,
		PRELOAD_14_RANK_05,			//�����L���O�i�`5�ʁj
		PRELOAD_15_SCENETITLEKB,	//�^�C�g���J�ڕ����iKB�j
		PRELOAD_16_SCENETITLEGP,	//�^�C�g���J�ڕ����iGP�j
		PRELOAD_17_TUTORIAL_01,		//�`���[�g���A��
		PRELOAD_18_TUTORIAL_02,
		PRELOAD_19_TUTORIAL_03,
		PRELOAD_20_TUTORIAL_04,
		PRELOAD_28_TUTORIAL_05_KB,	//�ړ��iKB�j
		PRELOAD_29_TUTORIAL_06_KB,	//�ؑցiKB�j
		PRELOAD_30_TUTORIAL_05_GP,	//�ړ��iGP�j
		PRELOAD_31_TUTORIAL_06_GP,	//�ؑցiGP�j
		PRELOAD_21_PAUSE_STR,		//�|�[�Y����
		PRELOAD_22_PAUSE_RESUME,	//�Q�[���ɖ߂�
		PRELOAD_23_PAUSE_RESTART,	//�ăX�^�[�g
		PRELOAD_24_PAUSE_EXIT,		//�^�C�g���ɖ߂�
		PRELOAD_25_PAUSE_SCREENSHOT,//�X�N�V��
		PRELOAD_26_BG_01,			//�w�i1
		PRELOAD_27_BG_02,			//�w�i2
		PRELOAD_32_POINT,			//���쒆�|�C���g
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
