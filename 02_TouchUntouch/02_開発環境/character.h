//======================================================
//
//�L�����N�^�[�����̃w�b�_[character.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//�K�v�Ȃ̃C���N���[�h
#include "object.h"
#include "interface.h"

//�O���錾
class CModel;
class CShadow;
class CMotion;
class CBoxCollider;
class CObject3D;

//�L�����N�^�[�N���X
class CCharacter : public CObject, public ICollisionReader
{
public:
	//�ÓIconst
	static const float CHARA_SPEED;				//�ړ����x
	static const float CHARA_JUMP_POW;			//�W�����v��
	static const float CHARA_RESPAWN_HEIGHT;	//���X�|�[������̍���

	//�����蔻��pfloat3��
	struct ColFloat
	{
		float* pPosMain, pPosSubA, pPosSubB;
		float fSizeMain, fSizeSubA, fSizeSubB;
	};

	//�L�����N�^�[�^�C�v��
	enum TYPE
	{
		TYPE_A = 0,
		TYPE_B,
		TYPE_MAX
	};

	//���[�V�������
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,
		MOTIONTYPE_MOVE,
		MOTIONTYPE_ACTION,	//������
		MOTIONTYPE_JUMP,
		MOTIONTYPE_LAND,
	} MOTIONTYPE;

	//�R���X�g���N�^�E�f�X�g���N�^
	CCharacter(int nPriority = CObject::PRIORITY_02);
	~CCharacter();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CCharacter* Create(const D3DXVECTOR3 pos ,const TYPE type, IControllStat* player);

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	static CCharacter** GetChara(void) { return &m_aChara[0]; }

	//�ݒ�
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }

	//���O�i�K�v�Ȃ��j
	void Exclusion(void){}

	//�C���^�[�t�F�[�X����
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	float GetDepth(void) { return m_fDepth; }
	CObject* GetObj(void) { return this; }

private:
	void SetModel(void);

	static CCharacter* m_aChara[TYPE_MAX];	//��ޕʂ̃L�����|�C���^

	D3DXMATRIX m_mtxWorld;			//���[���h�}�g��
	CModel** m_ppModel;				//���f���i���I�m�ہj
	int m_nNumModel;				//���f����
	CMotion* m_pMotion;				//���[�V�����|�C���^
	CShadow* m_pShadow;				//�e
	CObject3D* m_pPoint;			//���쒆�\��

	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_posOld;			//�O�̈ʒu
	D3DXVECTOR3 m_posLastLanding;	//�Ō�ɒ��n�����ʒu
	D3DXVECTOR3 m_move;				//�ړ���
	float m_fJumpPower;				//�W�����v��
	D3DXVECTOR3 m_rot;				//����
	float m_fWidth, m_fHeight, m_fDepth;	//�T�C�Y

	bool m_bJump;					//�W�����v����
	int m_nCounterJumpTime;			//�W�����v����

	//CShadow* m_pShadow;				//�e�I�u�W�F�N�g�|�C���^
	TYPE m_type;					//���
	CBoxCollider* m_pCollider;		//�����蔻��

	IControllStat* m_controllInterface;	//����󋵂̃C���^�[�t�F�[�X
};

#endif // !_CHARACTER_H_
