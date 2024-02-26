//======================================================
//
//�I�u�W�F�N�g�����̃w�b�_[object.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#define MAX_OBJ				(256)	//�I�u�W�F�N�g�ő吔
#define DEATH_LIFE			(0)		//���S�̗�

#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)				//2D
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//3D

//���_���[2D]
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//���W�ϊ��W���i1.0f�ŌŒ�j
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_2D;

//���_���[3D]
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`��
} VERTEX_3D;

//�I�u�W�F�N�g�N���X
class CObject
{
public:
	//�`����
	enum class DRAWTYPE
	{
		DRAW_NONE,
		DRAW_2D,
		DRAW_3D,
		DRAW_BILL,
		DRAW_X,
		DRAW_MESH,
	};

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
	static void DrawAll2D(void);
	static void DrawAll3D(void);

	//�擾�E�ݒ�
	static CObject* GetTop(const int nPriority) { return m_apTop[nPriority]; }
	CObject* GetNext(void) { return m_pNext; }
	DRAWTYPE GetDrawType(void) { return m_drawType; }
	void SetDrawType(DRAWTYPE drawType) { m_drawType = drawType; }

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
	bool m_bDeath;			//���S�t���O
	DRAWTYPE m_drawType;	//�`��^�C�v
};

#endif // !_OBJECT_H_
