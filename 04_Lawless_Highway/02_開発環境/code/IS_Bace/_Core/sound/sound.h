//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �Ό��D�n
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//�T�E���h�N���X
class CSound
{
public:
	//*****************************************************************************
	// �T�E���h�ꗗ
	//*****************************************************************************
	enum SOUND_LABEL
	{
		SOUND_LABEL_BGM_TITLE = 0,	//BGM�i�^�C�g���j
		SOUND_LABEL_BGM_GAME,		//BGM�i�Q�[���j
		SOUND_LABEL_BGM_RANKING,	//BGM�i�����L���O�j
		SOUND_LABEL_SE_RUN,			//SE�i�ԑ��s���j
		SOUND_LABEL_SE_GEARCHANGE,	//SE�i�ԃM�A�`�F�����j
		SOUND_LABEL_SE_DRIFT,		//SE�i�ԃh���t�g���j
		SOUND_LABEL_SE_CLEARBRAKE,	//SE�i�N���A���̎ԃu���[�L���j
		SOUND_LABEL_MAX,
	};
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

	//�ݒ�
	HRESULT SetVolume(SOUND_LABEL label, float volume);	//�{�����[���ݒ�
private:
	IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif
