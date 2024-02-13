//======================================================
//
//�X�C�b�`�����̃w�b�_[switch.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _SWITCH_H_
#define _SWITCH_H_

//�K�v�Ȃ̃C���N���[�h
#include "object.h"

//�O���錾
class CObjectX;
class CXModel;

//�L�����N�^�[�N���X
class CSwitch : public CObject
{
public:
	//�ÓIconst
	static const float MOVE_DEF_HEIGHT;

	//�����蔻��pfloat3��
	struct ColFloat
	{
		float* pPosMain, pPosSubA, pPosSubB;
		float fSizeMain, fSizeSubA, fSizeSubB;
	};

	//�X�C�b�`�^�C�v��
	enum TYPE
	{
		TYPE_A = 0,		//��
		TYPE_B,			//���F
		TYPE_GOAL_A,	//�S�[���i�^�C�vA�j
		TYPE_GOAL_B,	//�S�[���i�^�C�vB�j
		TYPE_MAX
	};

	//�R���X�g���N�^�E�f�X�g���N�^
	CSwitch(int nPriority = PRIORITY_DEFAULT);
	~CSwitch();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CSwitch* Create(const D3DXVECTOR3 pos, const TYPE type);

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	static CSwitch* GetTop(void) { return m_pTop; }
	CSwitch* GetNext(void) { return m_pNext; }
	CObjectX* GetBase(void) { return m_pObjBase; }
	CObjectX* GetMove(void) { return m_pObjMove; }
	bool IsPush(void) { return m_bPush; }
	TYPE GetType(void) { return m_type; }

	//�ݒ�
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }

	//���O
	void Exclusion(void);

	//�X�C�b�`������
	void Push(void) { m_bPush = true; }	//�L�������g����������
	void Pull(void) { m_bPush = false; }//�X�C�b�`�}�l���g���������鑀��

private:
	//���f��
	static CXModel* m_pModelBase;	//�y��̃��f���|�C���^
	static CXModel* m_pModelMove;	//�����̃��f���|�C���^

	//���X�g
	static CSwitch* m_pTop;	//���X�g�̍ŏ�
	static CSwitch* m_pCur;	//���X�g�̏I�[
	CSwitch* m_pNext;		//��
	CSwitch* m_pPrev;		//�O
	static int m_nNumAll;	//�X�C�b�`����

	D3DXMATRIX m_mtxWorld;			//���[���h�}�g��
	CObjectX* m_pObjBase;			//�y��̃I�u�W�F�N�g�|�C���^
	CObjectX* m_pObjMove;			//�����̃I�u�W�F�N�g�|�C���^

	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_move;				//�ړ���
	D3DXVECTOR3 m_rot;				//����
	float m_fWidth, m_fHeight, m_fDepth;	//�T�C�Y

	TYPE m_type;	//�X�C�b�`�^�C�v�i�@�\�ɍ��قȂ��j
	bool m_bPush;	//�X�C�b�`��������Ă��邩
};

#endif // !_CHARACTER_H_
