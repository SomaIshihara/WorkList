//======================================================
//
//�J�E���g�_�E�������̃w�b�_[countdown.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_
#include "main.h"
#include "object.h"

//�O���錾
class CObject2D;

class CCountDown
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CCountDown(const int startCount);
	~CCountDown();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CCountDown* Create(const D3DXVECTOR3 pos, const float fWidth, const float fHeight, const int nCount);

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	int GetCount(void) { return m_count; }

	//�ݒ�
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	
	//�X�^�[�g
	void Start(void);

private:
	D3DXVECTOR3 m_pos;		//�ʒu
	CObject2D* m_pFrame;	//�g�I�u�W�F�N�g
	CObject2D** m_ppCount;	//�J�E���g�I�u�W�F�N�g�i�ρj
	const int m_startCount;	//�J�E���g�����l
	int m_count;			//�J�E���g
	int m_counterSec;		//1�b�J�E���^�[
	bool m_shouldCount;		//�J�E���g���邩�ǂ���
};

#endif // !_COUNTDOWN_H_