//======================================================
//
//�|�[�Y��ʂ̃w�b�_[game.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

//�^�C�g���N���X
class CPause
{
public:
	//�I���
	enum MODE
	{
		MODE_RESUME = 0,
		MODE_RESTART,
		MODE_EXIT,
		MODE_SCREENSHOT,
		MODE_MAX
	};

	//�R���X�g���N�^�E�f�X�g���N�^
	CPause();
	~CPause();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Select(void);

	MODE m_mode;			//�I�𒆃��[�h
	bool m_bScreenShot;		//�X�N�V������
};

#endif // !_GAME_H_
