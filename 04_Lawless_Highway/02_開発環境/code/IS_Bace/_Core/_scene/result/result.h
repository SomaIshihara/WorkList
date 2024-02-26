//======================================================
//
//���U���g�V�[���̃w�b�_[result.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "..\..\manager\manager.h"

//�O���錾
class CPause;
class CFade;
class CObject2D;
class CTimerMSmS;

//��
class CGoal;

//�^�C�g���N���X
class CResult : public CScene
{
public:
	//���ʗ�
	enum class RESULT
	{
		SUCCESS,
		LATETIME,
		MAX
	};

	//�R���X�g���N�^�E�f�X�g���N�^
	CResult();
	~CResult();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ݒ�
	static void Set(const RESULT result, const int ntime, const int nCounter);

private:
	CPause* m_pPause;	//�|�[�Y
	CFade* m_pFade;		//�t�F�[�h
	CObject2D* m_pResult;	//�x�����ۂ�
	CTimerMSmS* m_pTimer;	//������������
	CObject2D* m_pStart;	//�X�^�[�g����

	//����
	static RESULT m_result;
	static int m_nTime;
	static int m_nCounter;
};

#endif // !_GAME_H_
