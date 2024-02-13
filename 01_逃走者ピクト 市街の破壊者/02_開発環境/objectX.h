//======================================================
//
//�I�u�W�F�N�g�iX�j�����̃w�b�_[objectX.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_
#include "main.h"
#include "manager.h"
#include "object.h"

typedef unsigned char BINCODE;
//�o�C�i���̃R�[�h���e
//�V�X�e��(0b00xxxxxx)
#define BIN_CODE_SYSTEM				(0b00000000)
#define BIN_CODE_SCRIPT				(BIN_CODE_SYSTEM + 0b000000)
#define BIN_CODE_END_SCRIPT			(BIN_CODE_SYSTEM + 0b000001)
//���f���n(0b01xxxxxx)
#define BIN_CODE_MODEL				(0b01000000)
#define BIN_CODE_TEXTURE_FILENAME	(BIN_CODE_MODEL + 0b000000)
#define BIN_CODE_MODEL_FILENAME		(BIN_CODE_MODEL + 0b000001)
#define BIN_CODE_MODELSET			(BIN_CODE_MODEL + 0b000010)
#define BIN_CODE_TEXTURE_NUM		(BIN_CODE_MODEL + 0b000011)
#define BIN_CODE_MODEL_NUM			(BIN_CODE_MODEL + 0b000100)
//���[�V�����n(0b10xxxxxx)
#define BIN_CODE_MOTION				(0b10000000)

//�O���錾
class CXModel;

//�I�u�W�F�N�g�N���X
class CObjectX : public CObject
{
public:
	enum LOADRESULT
	{
		RES_OK = 0,
		RES_ERR_FILE_NOTFOUND,
		RES_MAX
	};

	enum STATE
	{
		STATE_NONE = 0,		//�ݒ�Ȃ�
		STATE_BREAKABLE,	//�j��\�ݒ�
		STATE_KOBAN,		//��Ԑݒ�
		STATE_MAX
	};

	//�R���X�g���N�^�E�f�X�g���N�^
	CObjectX(int nPriority = PRIORITY_DEFAULT);																	//�f�t�H���g
	CObjectX(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, CXModel* pModel, int nPriority = PRIORITY_DEFAULT);	//�I�[�o�[���[�h�i�ʒu�����T�C�Y�j
	virtual ~CObjectX();

	//��{����
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//����
	static CObjectX* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, CXModel* pModel);

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	float GetDepth(void) { return m_fDepth; }
	static CObjectX* GetTop(void) { return m_pTop; }
	CObjectX* GetNext(void) { return m_pNext; }
	CXModel* GetModel(void) { return m_pModel; }
	bool GetBreakable(void) { return m_bBreakale; }
	bool GetStateKoban(void) { return m_bKoban; }

	//�ݒ�
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetBreakable(bool bFrag) { m_bBreakale = bFrag; }
	void SetStateKoban(bool bFrag) { m_bKoban = bFrag; }

	//�g�p���f���P�ʂŏ���
	static void Delete(CXModel* pTarget);

	//�ǂݍ���
	static LOADRESULT LoadData(const char* pPath);
	static LOADRESULT SaveData(const char* pPath);

	//���S�t���O�������Ă���I�u�W�F���E��
	static void Exclusion(void);

private:
	//���f��
	D3DXMATRIX mtxWorld;	//���[���h�}�g��
	CXModel* m_pModel;		//���f��

	//�ʒu��
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
	float m_fWidth;		//��
	float m_fHeight;	//����
	float m_fDepth;		//���s

	//���
	bool m_bBreakale;	//�j��\�ݒ�
	bool m_bKoban;		//��Ԑݒ�

	//���X�g
	static CObjectX* m_pTop;	//�擪�I�u�W�F�N�g
	static CObjectX* m_pCur;	//�Ō���I�u�W�F�N�g
	CObjectX* m_pNext;			//���̃I�u�W�F�N�g
	CObjectX* m_pPrev;			//�O�̃I�u�W�F�N�g
	bool m_bExclusion;			//���O�t���O
	static int m_nNumAll;		//����
};

#endif // !_OBJECT_H_
