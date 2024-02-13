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

//�D�揇�ʎQ�l�\
typedef enum
{
	PRIORITY_BG = 0,		//BG
	PRIORITY_DEFAULT = 3,	//�f�t�H���g
	PRIORITY_DEFMM,			//�f�t�H���g--�i�f�t�H���g�����x���������j
	PRIORITY_UI,			//UI
	PRIORITY_PAUSE,			//�|�[�Y
	PRIORITY_FADE,			//�t�F�[�h
	PRIORITY_MAX			//�ő�D�揇�ʁi����ő����炵���j
} PRIORITY;

//�I�u�W�F�N�g�N���X
class CObject
{
public:
	//��ޗ�
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_ENEMY,
		TYPE_BULLET,
		TYPE_FIELD,
		TYPE_BUILDING,
		TYPE_PICTO,
		TYPE_OBJECT,
		TYPE_MAX
	} TYPE;

	//�R���X�g���N�^�E�f�X�g���N�^
	CObject(int nPriority = PRIORITY_DEFAULT);
	virtual ~CObject();

	//��{����
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	//�S�I�u�W�F�N�g�n
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	//�擾�E�ݒ�
	void SetType(TYPE type) { m_Type = type; }
	TYPE GetType(void) { return m_Type; }
	static CObject* GetTop(const int nPriority) { return m_apTop[nPriority]; }
	CObject* GetNext(void) { return m_pNext; }

	//�������z�擾
	virtual D3DXVECTOR3 GetPos(void) = 0;
	virtual D3DXVECTOR3 GetRot(void) = 0;
	virtual float GetWidth(void) = 0;
	virtual float GetHeight(void) = 0;
	virtual float GetDepth(void) = 0;

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
