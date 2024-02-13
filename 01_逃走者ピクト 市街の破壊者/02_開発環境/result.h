//======================================================
//
//���U���g�V�[���̃w�b�_[result.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//�O���錾
class CBG;
class CButton2D;
class CFade;

//���U���g�N���X
class CResult
{
public:
	//�Œ�l
	static const int HEADLINE_TIME;	//���o���\������
	static const int ATK_TIME;		//�U�����\������
	static const int DEST_TIME;		//�S�󐔕\������
	static const int VALUE_TIME;	//��Q���z�\������
	static const int RANK_TIME;		//�{�^���\������
	static const float FADE_ALPHA;	//��ʂ��Â�����
	static const float FADE_SPEED;	//�Â����鑬�x

	//�R���X�g���N�^�E�f�X�g���N�^
	CResult();
	~CResult();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CResult* Create(void);

private:
	CBG* m_pBG;				//�w�i�I�u�W�F�i�s�����x�������邽�߁j
	float m_fAlpha;			//�s�����x
	CButton2D* m_pButton;	//�{�^��
	int m_nCounter;			//�\���^�C�~���O�J�E���^
	CFade* m_pFade;
};

#endif // !_RESULT_H_
