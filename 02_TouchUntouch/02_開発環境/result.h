//======================================================
//
//���U���g�V�[���̃w�b�_[result.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//�O���錾
class CTimer;
class CScore;
class CObject2D;
class CFade;

//���U���g�N���X
class CResult
{
public:
	//�ÓIconst
	static const int PLAYSOUND_COUNTER;	//���炷�Ԋu

	//�R���X�g���N�^�E�f�X�g���N�^
	CResult();
	~CResult();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CResult* Create(const int nTimer, const int nScore);

private:
	CTimer* m_pTimer;	//���U���g�p�^�C�}�[
	CScore* m_pBonus;	//�{�[�i�X�p�X�R�A�i�����͓������ςȂ��j
	CScore* m_pScore;	//�ŏI�X�R�A�p�X�R�A�i�����͓������ςȂ��j
	CObject2D* m_pPress;//�J�ڕ����p�I�u�W�F�i�ڑ��Őؑցj
	CFade* m_pFade;		//�t�F�[�h�I�u�W�F�N�g
	int m_nConter;		//���Đ��J�E���^�[
};

#endif // !_RESULT_H_
