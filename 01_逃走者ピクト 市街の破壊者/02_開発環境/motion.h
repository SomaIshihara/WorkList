//======================================================
//
//���[�V���������̃w�b�_[motion.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _MOTION_H_
#define _MOTION_H_

//�}�N��
#define KEYINFO_NUM		(16)	//�L�[���ő吔�i���f�����Ɉˑ��j
#define INFO_NUM		(8)		//���[�V�������ő吔

//�O���錾
class CModel;

//���[�V�����N���X
class CMotion
{
public:
	//�L�[�\����
	typedef struct
	{
		float m_fPosX;	//�ʒuX
		float m_fPosY;	//�ʒuY
		float m_fPosZ;	//�ʒuZ
		float m_fRotX;	//����X
		float m_fRotY;	//����Y
		float m_fRotZ;	//����Z
	} KEY;

	//�L�[���̍\����
	typedef struct
	{
		int m_nFrame;			//�Đ��t���[��
		KEY* m_pKey;			//���f���̃L�[�v�f�i���I�m�ہj
	} KEY_INFO;

	//���[�V������ԍ\����
	typedef struct
	{
		bool m_bLoop;						//���[�v���邩
		int m_nNumKey;						//�L�[����
		KEY_INFO m_aKeyInfo[KEYINFO_NUM];	//�L�[�̏��i16�͓K�X�ς��āj
	} INFO;

	//�R���X�g���N�^�E�f�X�g���N�^
	CMotion();
	~CMotion();

	//��{����
	HRESULT Init(void);
	void Uninit(void);

	//���[�V�����ݒ�E�X�V
	void Set(int nType);
	void Update(void);

	//�擾
	int GetType(void) { return m_nType; }
	bool IsFinish(void) { return m_bFinish; }

	//�K�v�ȏ��ݒ�
	void SetInfo(INFO info);
	void SetModel(CModel** ppModel, int nNumModel);


private:
	INFO m_aInfo[INFO_NUM];	//���[�V�������i�z�񉼁j
	int m_nNumAll;					//���[�V��������

	int m_nType;					//�g�p�����[�V�����^�C�v
	bool m_bLoop;					//���[�v���邩
	int m_nNumKey;					//�L�[����
	int m_nKey;						//���݂̃L�[
	int m_nCounter;					//���[�V�����J�E���^
	bool m_bFinish;					//���[�V�����I��������

	CModel** m_ppModel;				//���f���ւ̃|�C���^
	int m_nNumModel;				//���f����
};

#endif // !_MOTION_H_
