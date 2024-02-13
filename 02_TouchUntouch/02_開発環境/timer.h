//======================================================
//
//�^�C�}�[�����̃w�b�_[timer.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "object2D.h"

#define TIME_DIGIT	(3)	//�^�C�}�[�̌���

class CNumber;

class CTimer : public CObject
{
public:
	//�^�C�}�[�J�E���g���
	typedef enum
	{
		COUNT_UP = 0,
		COUNT_DOWN,
		COUNT_MAX
	} COUNT;

	//�R���X�g���N�^�E�f�X�g���N�^
	CTimer(int nPriority = PRIORITY_05);	//�f�t�H���g
	~CTimer();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CTimer* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight);	//�I�u�W�F�N�g�𐶐�(fOneWidth,fOneHeight:1��������̃T�C�Y)

	//�擾�i�������z�֐��̊֌W��������Ă��邪�A�����ɃT�C�Y���͂���Ȃ��̂ł��ׂ�0��Ԃ��j
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	//float GetWidth(void) { return CManager::FLT_ZERO; }
	//float GetHeight(void) { return CManager::FLT_ZERO; }
	//float GetDepth(void) { return CManager::FLT_ZERO; }
	int GetModelIdx(void) { return -1; }
	int GetTime(void) { return m_nTime; }

	//�ݒ�
	void Set(const int nTime, COUNT type);	//�^�C�}�[�ݒ�
	bool GetCount(void) { return m_shouldCount; }
	void Start(void) { m_shouldCount = true; }
	void Stop(void) { m_shouldCount = false; }
	void Add(const int nTime) { m_nTime += nTime; }
	void BindTexture(const int nIdx);	//�e�N�X�`���ݒ�i�����I�u�W�F�N�g���ׂĂɓK�p�j

	//���O�i�K�v�Ȃ��j
	void Exclusion(void){}

private:
	void CutNumber(void);				//��������
	CNumber* m_pNumber[TIME_DIGIT];		//����
	D3DXVECTOR3 m_pos;					//�ʒu�i1���ڂ̐����̒��S��z��j
	D3DXVECTOR3 m_rot;					//�����i1���ڂ̐����̒��S��z��j
	int m_nCounter;						//�^�C�}�[�J�E���^
	int m_nTime;						//�^�C��
	COUNT m_count;						//�J�E���g���
	bool m_shouldCount;					//�J�E���g���邩�ǂ���
};

#endif	//���d