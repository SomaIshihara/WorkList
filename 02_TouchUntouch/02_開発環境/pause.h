//======================================================
//
//�|�[�Y��ʂ̃w�b�_[game.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

//�O���錾
class CObject2D;
class CBG;

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

	CBG* m_pBG;							//������ƈÂ�����w�i
	CObject2D* m_pPauseStr;				//�|�[�Y����
	CObject2D* m_apSelect[MODE_MAX];	//�I��������

	MODE m_mode;			//�I�𒆃��[�h
	bool m_bScreenShot;		//�X�N�V������
	int m_aStickFrag[2];	//�X�e�B�b�N���ǂ��瑤�ɓ|����Ă��邩�iXY�����i�[�j
};

#endif // !_GAME_H_
