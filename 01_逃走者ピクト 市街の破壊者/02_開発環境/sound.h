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
		SOUND_LABEL_BGM = 0,		//BGM
		SOUND_LABEL_SE_BUTTON,		//�{�^���N���b�N
		SOUND_LABEL_SE_DISPATCH,	//�o��
		SOUND_LABEL_SE_SELECT,		//�����E�s�N�g�I��
		SOUND_LABEL_SE_COUNTDOWN,	//�J�E���g�_�E��
		SOUND_LABEL_SE_ROCKET,		//���P��������
		SOUND_LABEL_SE_GUN,			//�e����
		SOUND_LABEL_SE_EXPLOSION,	//��������
		SOUND_LABEL_SE_DAMAGE,		//�s�N�g�_���[�W
		SOUND_LABEL_SE_POPRESULT,	//���U���g�o��
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
private:
	IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif
