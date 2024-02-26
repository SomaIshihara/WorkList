//======================================================
//
//�^�C�}�[�����̃w�b�_[timer.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "..\..\_Core\_object\object_2d\object2D.h"

#define TIME_DIGIT	(3)	//�^�C�}�[�̌���

class CObject2D;
class CNumber;

//******************************************************************
// ��{�^�C�}�[�N���X
//******************************************************************
class CTimer : public CObject
{
public:
	//�^�C�}�[�J�E���g���
	enum class COUNT
	{
		COUNT_UP = 0,
		COUNT_DOWN,
		COUNT_MAX
	};

	//�R���X�g���N�^�E�f�X�g���N�^
	CTimer(int nPriority = PRIORITY_05);	//�f�t�H���g
	virtual ~CTimer();

	//��{����
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	int GetTime(void) { return m_nTime; }
	COUNT GetCountType(void) { return m_count; }
	virtual float GetWidth(void) = 0;
	int GetCounter(void) { return m_nCounter; }

	//�ݒ�
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; Replace(); }
	void Set(const int nTime, COUNT type);	//�^�C�}�[�ݒ�
	bool GetShouldCount(void) { return m_shouldCount; }
	void Start(void) { m_shouldCount = true; }
	void Stop(void) { m_shouldCount = false; }
	void Add(const int nTime) { m_nTime += nTime; }
	virtual void BindTexture(const int nIdx) = 0;	//�e�N�X�`���ݒ�i�����I�u�W�F�N�g���ׂĂɓK�p�j

	//���O�i�K�v�Ȃ��j
	void Exclusion(void){}

protected:
	//�ݒ�
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetCounter(const int nCounter) { m_nCounter = nCounter; }
	virtual void Replace(void) = 0;

private:
	virtual void CutNumber(void) = 0;	//��������
	D3DXVECTOR3 m_pos;					//�ʒu�i1���ڂ̐����̒��S��z��j
	D3DXVECTOR3 m_rot;					//�����i1���ڂ̐����̒��S��z��j
	int m_nCounter;						//�^�C�}�[�J�E���^
	int m_nTime;						//�^�C��
	COUNT m_count;						//�J�E���g���
	bool m_shouldCount;					//�J�E���g���邩�ǂ���
};

//******************************************************************
// �b�^�C�}�[�N���X
//******************************************************************
class CTimerSecond : public CTimer
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CTimerSecond();
	~CTimerSecond();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�擾
	float GetWidth(void) { return m_fWidth * TIME_DIGIT; }

	//�ݒ�
	void BindTexture(const int nIdx);

	//�I�u�W�F�N�g�𐶐�(fOneWidth,fOneHeight:1��������̃T�C�Y)
	static CTimerSecond* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight);
protected:
	void Replace(void);

private:
	void CutNumber(void);

	float m_fWidth;
	CNumber* m_pNumber[TIME_DIGIT];		//����
};

//******************************************************************
// ���b�~���b�^�C�}�[�N���X
//******************************************************************
class CTimerMSmS : public CTimer
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CTimerMSmS();
	~CTimerMSmS();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�擾
	float GetWidth(void) { return m_fWidth * 7; }

	//�ݒ�
	void Set(const int nTime, const int nCounter, COUNT type);
	void BindTexture(const int nIdx);
	void BindSymbolTexture(const int nIdx);

	//�I�u�W�F�N�g�𐶐�(fOneWidth,fOneHeight:1��������̃T�C�Y)
	static CTimerMSmS* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight);
protected:
	void Replace(void);

private:
	void CutNumber(void);

	float m_fWidth;
	CNumber* m_pMinute[2];
	CNumber* m_pSecond[2];
	CNumber* m_pMilliSecond[2];
	CObject2D* m_pSymbol[2];	//[0]:���ƕb,[1]:�b�ƃ~���b
};

#endif	//���d