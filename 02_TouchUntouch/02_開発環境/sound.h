//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �Ό��D�n
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//�T�E���h�N���X
class CSound
{
public:
	//*****************************************************************************
	// �T�E���h�ꗗ
	//*****************************************************************************
	typedef enum
	{
		SOUND_LABEL_BGM_OUT = 0,	//�A�E�g�Q�[��BGM
		SOUND_LABEL_BGM_IN,			//�C���Q�[��BGM
		SOUND_LABEL_SE_SELECT,		//�I��
		SOUND_LABEL_SE_JUMP,		//�W�����v
		SOUND_LABEL_SE_ITEM,		//�A�C�e���l��
		SOUND_LABEL_SE_CHANGE,		//�L�����ؑ�
		SOUND_LABEL_SE_MOVE,		//���s
		SOUND_LABEL_MAX,
	} SOUND_LABEL;
	//*****************************************************************************

	//�R���X�g���N�^�E�f�X�g���N�^
	CSound();
	~CSound();

	//��{����
	HRESULT Init(HWND hWnd);
	void Uninit(void);

	//��������
	HRESULT Play(SOUND_LABEL label);	//����
	void Stop(SOUND_LABEL label);		//1�~�߂�
	void Stop(void);					//�S���~�߂�
	void Pause(SOUND_LABEL label);		//�|�[�Y
	void Restart(SOUND_LABEL label);	//�ĊJ
	
	//��Ԏ擾
	bool IsPlay(SOUND_LABEL label);		//�����Ă��邩
private:
	IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif
