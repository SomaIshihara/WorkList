//======================================================
//
//���f���L��������[chara.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _CHARA_H_
#define _CHARA_H_

#include "../_object/object_empty/object.h"

//�O���錾
class CModel;
class CMotion;

//���f���L�����N���X
class CChara : public CObject
{
public:
	//���[�V�������
	enum class MOTIONTYPE
	{
		MOTIONTYPE_NEUTRAL = 0,
		MOTIONTYPE_MOVE,
		MOTIONTYPE_ACTION,	//������
		MOTIONTYPE_JUMP,
		MOTIONTYPE_LAND,
	};

	//�R���X�g���N�^�E�f�X�g���N�^
	CChara(int nPriority = CObject::PRIORITY_DEFAULT);
	~CChara();

	//��{����
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//����
	static CChara* Create(const char* pPath, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	MOTIONTYPE GetMotion(void);

	//�ݒ�
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	virtual void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMotion(MOTIONTYPE type);
	HRESULT SetupModel(const char* pPath);

	//���O
	virtual void Exclusion(void) {}

private:
	//�ʒu��
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_rot;			//����
	D3DXMATRIX m_mtxWorld;		//���[���h�}�g��
	CModel** m_ppModel;			//���f���i���I�m�ہj
	CMotion* m_pMotion;			//���[�V�����|�C���^
	int m_nNumModel;			//���f����
};

#endif // !_CHARA_H_
