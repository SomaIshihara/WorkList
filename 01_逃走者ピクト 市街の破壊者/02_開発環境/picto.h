//======================================================
//
//�s�N�g���񏈗��̃w�b�_[picto.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _PICTO_H_
#define _PICTO_H_

#include "main.h"
#include "manager.h"
#include "object.h"
#include "objectX.h"
#include "collision.h"
#include <stack>

#define PICTO_MAX_LEVEL		(30)	//�s�N�g�̍ő僌�x��
#define PICTO_DAMAGE_ALPHA	(0.9f)	//�Ԃ����銄��
#define PICTO_TAXI_MAXLIFE	(10000)

//�v�Z�i�������g�p�j
#define REQUIRE_EXP(lv)		((int)ceil(pow(1.34f,(lv - 2)) * 20))
#define PICTO_ATK(lv)		((float)ceil(pow(1.125f,(lv - 1)) * 100) * 0.01f)
#define PICTO_HAVENPICTO(lv)	((int)ceil(pow(1.1f,(lv - 1)) * 500))
#define DROP_EXP(lv)		((int)ceil(REQUIRE_EXP(lv + 1) / 1))
#define HAVE_LIFE(lv)		((int)ceil(98 + PICTO_HAVENPICTO(lv) * PICTO_ATK(lv) * 12))
#define HAVE_VALUE(lv)		((long long)ceil(pow(1.5f,(lv - 1)) * lv) * 1000000)

//�O���錾
class CModel;
class CMotion;
class CBuilding;
class CShadow;
class CPictoPolice;
class CPictoNormal;
class CPictoTaxi;
class CMeshField;
class CPoint;

//�s�N�g����N���X
class CPicto : public CObject
{
public:
	//�ÓIconst
	static const float LOOSE_LENGTH;	//�����������̂Ƃ��鋗��
	static const int BASE_MODEL_NUM;	//�̕����̃��f����

	//�o�H�T���p�m�[�h�\����
	struct Node
	{
		bool bDesition;		//�m�肩�ǂ���
		float fLengthMin;	//�ŒZ����
		CPoint* pPoint;		//���̃m�[�h�������|�C���g
		int nFromNum;		//�����m�[�h�̔ԍ�
	};

	//�s�N�g�����ޗ�
	typedef enum
	{
		TYPE_DESTROYER = 0,
		TYPE_BLOCKER,
		TYPE_NORMAL,
		TYPE_TAXI,
		TYPE_POLICE,
		TYPE_MAX
	} TYPE;

	//�s�N�g�����ԗ�
	typedef enum
	{
		STATE_FACE = 0,	//�ΏۂɌ������Ă���
		STATE_ATTACK,	//�U����
		STATE_LEAVE,	//�A���Ă���
		STATE_MAX
	} STATE;

	//���[�V�������
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,
		MOTIONTYPE_MOVE
	} MOTIONTYPE;

	//�R���X�g���N�^�E�f�X�g���N�^
	CPicto();
	CPicto(const D3DXVECTOR3 pos, const TYPE type);
	virtual ~CPicto();

	//��{����
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	float GetDepth(void) { return m_fDepth; }
	int GetModelIdx(void) { return -1; }
	static CPicto* GetPicto(int nID) { return m_apPicto[nID]; }
	CMotion* GetMotion(void) { return m_pMotion; }
	CCollision GetCollision(void) { return m_collision; }
	STATE GetState(void) { return m_state; }
	TYPE GetType(void) { return m_type; }
	static CObject* GetAgit(void) { return m_pAgitObj; }
	static D3DXVECTOR3 GetAgitPos(void) { return m_pAgitObj->GetPos(); }
	CObject* GetTargetObj(void) { return m_pTargetObj; }
	static int GetNumAll(void) { return m_nNumAll; }
	virtual int GetLife(void) = 0;
	
	//�ݒ�
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetState(STATE state) { m_state = state; }
	static void SetAgit(CObjectX* pAgit) { m_pAgitObj = pAgit; }
	void SetTargetObj(CObject* pObj);
	virtual void UnsetTarget(void);
	void UnsetTargetAll(void);
	void SetRedAlpha(void) { m_fRedAlpha = PICTO_DAMAGE_ALPHA; }
	void SetModel(const char* pPath);

	//�����蔻��
	bool CollisionField(D3DXVECTOR3* pPosNew);

	//���
	virtual void TakeTaxi(CPictoTaxi* taxi) = 0;

	//�A��
	virtual void Return(void);

	//�T��
	void Search(CObject* pTarget);

private:
	//�ϐ�
	static CPicto* m_apPicto[MAX_OBJ];	//�s�N�g����|�C���^
	static int m_nNumAll;				//�s�N�g���񑍐�
	int m_nID;							//�s�N�g����ID
	CMotion* m_pMotion;					//���[�V�����|�C���^

	D3DXMATRIX m_mtxWorld;				//���[���h�}�g��
	CModel** m_ppModel;					//�s�N�g���񃂃f���i���I�m�ہj
	int m_nNumModel;					//���f����
	CCollision m_collision;				//�R���W����

	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_move;					//�ړ���
	D3DXVECTOR3 m_rot;					//����
	float m_fWidth, m_fHeight, m_fDepth;//�T�C�Y

	bool m_bJump;						//�W�����v����
	int m_nCounterJumpTime;				//�W�����v����

	CShadow* m_pShadow;					//�e�I�u�W�F�N�g�|�C���^

	float m_fRedAlpha;					//�Ԃ����銄��
	STATE m_state;						//���
	TYPE m_type;						//�s�N�g���

	static CObjectX* m_pAgitObj;		//�A�W�g�̃|�C���^
	static CMeshField* m_pField;		//��

	CObject* m_pTargetObj;				//�ړI�̃I�u�W�F
	CPoint* m_pPoint;					//�ړI�̃|�C���g

	std::stack<CPoint*> m_stack;		//�o�H�X�^�b�N
	bool m_bNear;						//�ڕW�ɋ߂�
};

//�f�X�g���C���[�s�N�g�N���X
class CPictoDestroyer : public CPicto
{
public:
	//���[�V�������
	typedef enum
	{
		MOTIONTYPE_DESTROY = 2
	} MOTIONTYPE;

	//�R���X�g���N�^�E�f�X�g���N�^
	CPictoDestroyer();
	CPictoDestroyer(const D3DXVECTOR3 pos, const TYPE type = TYPE_DESTROYER);
	~CPictoDestroyer();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CPictoDestroyer* Create(const D3DXVECTOR3 pos);

	//�擾
	static CPictoDestroyer* GetPicto(int nID) { return m_apPicto[nID]; }
	static int GetNumAll(void) { return m_nNumAll; }
	int GetLife(void) { return m_nLife; }
	static int GetLv(void) { return m_nLv; }

	//���
	void TakeTaxi(CPictoTaxi* taxi);

	//�U��
	void AddDamage(int nDamage);

	//�o���l�t�^
	static void AddExp(const int nExp);

	//���x���E�o���l���Z�b�g
	static void ResetLevelExp(void) { m_nLv = 1; m_nExp = 0; }

	//�A��
	void Return(void);

private:
	static CPictoDestroyer* m_apPicto[MAX_OBJ];	//�s�N�g����|�C���^
	static int m_nNumAll;				//�s�N�g���񑍐�
	int m_nID;							//�s�N�g����ID
	int m_nCounterDestruction;			//�j��J�E���^�[

	static int m_nLv;					//���x��
	static int m_nExp;					//�����o���l
	int m_nLife;						//�̗�
	int m_nHaveNormalPicto;				//��ʐl�s�N�g������
};

//�u���b�J�[�s�N�g�N���X
class CPictoBlocker : public CPicto
{
public:
	//���[�V�������
	typedef enum
	{
		MOTIONTYPE_ATTACK = 3
	} MOTIONTYPE;

	//�R���X�g���N�^�E�f�X�g���N�^
	CPictoBlocker();
	CPictoBlocker(const D3DXVECTOR3 pos, const TYPE type = TYPE_BLOCKER);
	~CPictoBlocker();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CPictoBlocker* Create(const D3DXVECTOR3 pos);

	//�擾
	static CPictoBlocker* GetPicto(int nID) { return m_apPicto[nID]; }
	static int GetNumAll(void) { return m_nNumAll; }
	int GetLife(void) { return m_nLife; }
	static int GetLv(void) { return m_nLv; }

	//���
	void TakeTaxi(CPictoTaxi* taxi);

	//�U��
	void AddDamage(int nDamage);

	//�o���l�t�^
	static void AddExp(const int nExp);

	//���x���E�o���l���Z�b�g
	static void ResetLevelExp(void) { m_nLv = 1; m_nExp = 0; }

	//�A��
	void Return(void);

private:
	static CPictoBlocker* m_apPicto[MAX_OBJ];	//�s�N�g����|�C���^
	static int m_nNumAll;				//�s�N�g���񑍐�
	int m_nID;							//�s�N�g����ID

	int m_nCounterAttack;				//�U���J�E���^�[

	static int m_nLv;					//���x��
	static int m_nExp;					//�����o���l
	int m_nLife;						//�̗�
	int m_nHaveNormalPicto;				//��ʐl�s�N�g������
};

//�s�N�^�N�V�[�N���X
class CPictoTaxi : public CPicto
{
public:
	//�ÓIconst
	static const float RESCUE_LIFE;	//�~������̗�

	//�s�N�^�N�V�[���[�h��
	typedef enum
	{
		MODE_PICK = 0,	//���W
		MODE_SABO,		//�T�{��
		MODE_RESCUE,	//�~��
		MODE_MAX
	} MODE;

	//�R���X�g���N�^�E�f�X�g���N�^
	CPictoTaxi(const D3DXVECTOR3 pos, const TYPE type = TYPE_TAXI);
	~CPictoTaxi();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CPictoTaxi* Create(const D3DXVECTOR3 pos);

	//�擾
	static CPictoTaxi* GetPicto(int nID) { return m_apPicto[nID]; }
	static int GetNumAll(void) { return m_nNumAll; }
	int GetLife(void) { return m_nLife; }

	//���
	void SetTakeTaxi(const CPicto::TYPE type, const int nTakeNum);

	//�ݒ�
	void SetMode(const MODE mode) { m_mode = mode; }

	//���
	void TakeTaxi(CPictoTaxi* taxi) {};

	//�U��
	void AddDamage(int nDamage);

	//�A��
	void Return(void);

private:
	//�֐�
	CPictoNormal* SearchNormal(void);	//��ʐl�s�N�g�T��
	CPicto* SearchBattler(void);		//�퓬�v���T��

	//�ϐ�
	static CPictoTaxi* m_apPicto[MAX_OBJ];	//�s�N�g����|�C���^
	static int m_nNumAll;					//�s�N�g���񑍐�
	int m_nID;								//�s�N�g����ID

	MODE m_mode;			//�^�N�V�[���[�h

	//�^�[�Q�b�g
	CPicto* m_pTargetPicto;	//�s�N�g�i�ڍוs���j

	int m_nLife;			//�̗�

	int m_nTakeDestroyer;	//�f�X�g���C���[������Ă���l��
	int m_nTakeBlocker;		//�u���b�J�[������Ă���l��
	int m_nTakeNormal;		//��ʐl������Ă���l��
};

//��ʐl�s�N�g�N���X
class CPictoNormal : public CPicto
{
public:
	//�ÓIconst
	static const int NORMAL_D_PERCENT;	//��ʐl�s�N�g���f�X�g���C���[�ɂȂ�m��
	static const int NORMAL_B_PERCENT;	//��ʐl�s�N�g���u���b�J�[�ɂȂ�m��
	static const int NORMAL_N_PERCENT;	//��ʐl�s�N�g�ł���
	static const int NORMAL_NUM_MIN;	//��ʐl�s�N�g�̍Œ�l��
	static const int NORMAL_NUM_DEGREE;	//��ʐl�s�N�g�̐l���U�ꕝ

	//���[�V�������
	typedef enum
	{
		MOTIONTYPE_APPERL = 4
	} MOTIONTYPE;

	//�R���X�g���N�^�E�f�X�g���N�^
	CPictoNormal();
	CPictoNormal(const D3DXVECTOR3 pos, const TYPE type = TYPE_NORMAL);
	~CPictoNormal();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CPictoNormal* Create(const D3DXVECTOR3 pos);
	
	//�擾
	static CPictoNormal* GetPicto(int nID) { return m_apPicto[nID]; }
	static int GetNumAll(void) { return m_nNumAll; }
	int GetLife(void) { return -1; }

	//���
	void TakeTaxi(CPictoTaxi* taxi);

	//�A��
	void Return(void);

private:
	static CPictoNormal* m_apPicto[MAX_OBJ];	//�s�N�g����|�C���^
	static int m_nNumAll;					//�s�N�g���񑍐�
	int m_nID;								//�s�N�g����ID
};

//�s�N�g�x�@�N���X
class CPictoPolice : public CPicto
{
public:
	//���[�V�������
	typedef enum
	{
		MOTIONTYPE_ATTACK = 3
	} MOTIONTYPE;

	//�R���X�g���N�^�E�f�X�g���N�^
	CPictoPolice();
	CPictoPolice(const D3DXVECTOR3 pos, const TYPE type = TYPE_POLICE);
	~CPictoPolice();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CPictoPolice* Create(const D3DXVECTOR3 pos, const int nLv);

	//�擾
	static CPictoPolice* GetPicto(int nID) { return m_apPicto[nID]; }
	static int GetNumAll(void) { return m_nNumAll; }
	int GetLife(void) { return m_nLife; }
	int GetLv(void) { return m_nLv; }

	//�ݒ�
	void SetBuilding(CObject* pBui) { m_pTargetBui = pBui; }
	void UnsetTarget(void);

	//�����ݒ�
	void SetBuilding(CBuilding* pBuilding) { SetTargetObj((CObject*)pBuilding); }

	//��ԁi����킯���Ȃ��j
	void TakeTaxi(CPictoTaxi* taxi) {}

	//�U��
	void AddDamage(int nDamage);

	//�A��
	void Return(void);

private:
	static CPictoPolice* m_apPicto[MAX_OBJ];	//�s�N�g����|�C���^
	static int m_nNumAll;				//�s�N�g���񑍐�
	int m_nID;							//�s�N�g����ID
	int m_nCounterAttack;				//�U���J�E���^�[
	CObject* m_pTargetBui;				//�^�[�Q�b�g�i�p�g���[���������̋L���j

	int m_nLv;							//���x��
	int m_nLife;						//�̗�
	int m_nHaveNormalPicto;				//��ʐl�s�N�g������
};

#endif // !_PICTO_H_
