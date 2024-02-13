//======================================================
//
//�I�u�W�F�N�g�����̃w�b�_[object.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"

#define MAX_OBJ				(256)	//�I�u�W�F�N�g�ő吔
#define DEATH_LIFE			(0)		//���S�̗�

//�I�u�W�F�N�g�N���X
class CObject
{
public:
	//��ޗ�
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_BLOCK,
		TYPE_CHARACTER,
		TYPE_SWITCH,
		TYPE_GOAL,
		TYPE_ITEM,
		TYPE_TELEPORT,
		TYPE_TUTORIALOBJ,
		TYPE_MAX
	} TYPE;

	//�D�揇�ʎQ�l�\
	typedef enum
	{
		PRIORITY_BG = 0,		//BG
		PRIORITY_01,		//����`
		PRIORITY_02,		//����`
		PRIORITY_DEFAULT,		//�f�t�H���g
		PRIORITY_04,		//����`
		PRIORITY_05,			//UI����
		PRIORITY_PAUSE,			//�|�[�Y
		PRIORITY_FADE,			//�t�F�[�h
		PRIORITY_MAX			//�ő�D�揇�ʁi����ő����炵���j
	} PRIORITY;

	//�R���X�g���N�^�E�f�X�g���N�^
	CObject(int nPriority = PRIORITY_DEFAULT);
	virtual ~CObject();

	//��{����
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	//�S�I�u�W�F�N�g�n
	static void ReleaseAll(void);					//���ׂ�
	static void ReleaseAll(const int nPriority);	//�D��x��
	static void UpdateAll(void);
	static void DrawAll(void);

	//�擾�E�ݒ�
	void SetType(TYPE type) { m_Type = type; }
	TYPE GetType(void) { return m_Type; }
	static CObject* GetTop(const int nPriority) { return m_apTop[nPriority]; }
	CObject* GetNext(void) { return m_pNext; }

	//���O�i���X�g��������̏ꍇ�j
	virtual void Exclusion(void) = 0;

	//���S�t���O�������Ă���I�u�W�F���E��
	static void Death(void);

protected:
	void Release(void);

private:
	static CObject* m_apTop[PRIORITY_MAX];	//�擪�I�u�W�F�N�g
	static CObject* m_apCur[PRIORITY_MAX];	//�Ō���I�u�W�F�N�g
	CObject* m_pNext;		//���̃I�u�W�F�N�g
	CObject* m_pPrev;		//�O�̃I�u�W�F�N�g
	static int m_nNumAll;	//����
	int m_nPriority;		//�D�揇��
	TYPE m_Type;			//���
	bool m_bDeath;			//���S�t���O
};

#endif // !_OBJECT_H_
