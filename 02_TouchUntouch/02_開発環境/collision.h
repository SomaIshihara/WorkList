//======================================================
//
//�����蔻�菈���̃w�b�_[collision.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "interface.h"
#include <vector>

//�O���錾
class CObject;

//�����蔻��N���X�i���j
class CCollision
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CCollision();
	~CCollision();

	//�����蔻��`�F�b�N
	bool CollisionCheck(const D3DXVECTOR3 posOld, const D3DXVECTOR3 posNew, const D3DXVECTOR3 posCenter, const D3DXVECTOR3 rot);

	//�ݒ�
	void SetVtx(const D3DXVECTOR3 vtxMin, const D3DXVECTOR3 vtxMax) { m_vtxMin = vtxMin, m_vtxMax = vtxMax; }

	//�擾
	void GetVtx(D3DXVECTOR3* vtxMin, D3DXVECTOR3* vtxMax) { *vtxMin = m_vtxMin, *vtxMax = m_vtxMax; }

private:
	bool CollisionPolygon(const D3DXVECTOR3 posOld, const D3DXVECTOR3 posNew, const D3DXVECTOR3 posCenter, const D3DXVECTOR3 rot,
		const D3DXVECTOR3 vecNor, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 pos3);
	D3DXVECTOR3 m_vtxMin, m_vtxMax;	//�����蔻��Œ�l�E�ō��l
};

//���̓����蔻��N���X
class CBoxCollider
{
public:
	//�����蔻����
	enum TYPE
	{
		TYPE_COLLISION = 0,	//�Ԃ���
		TYPE_TRIGGER,		//�d�Ȃ�
		TYPE_NONE,			//�����蔻�肪�Ȃ�
		TYPE_MAX
	};

	//�^�O
	enum TAG
	{
		TAG_UNIV = 0,
		TAG_TYPE_A,
		TAG_TYPE_B,
		TAG_MAX
	};

	//�����蔻��pfloat3��
	struct ColFloat
	{
		float* pPosMain, pPosSubA, pPosSubB;
		float fSizeMain, fSizeSubA, fSizeSubB;
	};

	//�����蔻�茋��
	struct CollisionResult
	{
		std::vector<CObject*> collList;	//������������X�g
		bool bHit[3];					//�Փ˂�������3����
	};

	//�R���X�g���N�^�E�f�X�g���N�^
	CBoxCollider();
	~CBoxCollider();

	//�����蔻��`�F�b�N�i�������Ă���Γ��������I�u�W�F�N�g�A�Ȃ���΂ʂ�ہj
	void CollisionCheck(void);

	//�����蔻��ݒ�
	static CBoxCollider* Create(ICollisionReader* iCollisionReader);
	void SetType(TYPE type) { m_type = type; }
	void SetTag(TAG tag) { m_tag = tag; }

	//�j��
	void Release(void);

	//�擾
	CollisionResult GetResult(void) { return m_collisionResult; }
	static bool GetTagColl(TAG myTag, TAG otherTag) { return m_aTagColl[myTag][otherTag]; }

	//���X�g�擾
	static CBoxCollider* GetTop(void) { return m_pTop; }
	CBoxCollider* GetNext(void) { return m_pNext; }

private:
	//���X�g
	static CBoxCollider* m_pTop;	//�擪�I�u�W�F�N�g
	static CBoxCollider* m_pCur;	//�Ō���I�u�W�F�N�g
	CBoxCollider* m_pNext;			//���̃I�u�W�F�N�g
	CBoxCollider* m_pPrev;			//�O�̃I�u�W�F�N�g

	//�����蔻��ݒ�
	static bool m_aTagColl[TAG_MAX][TAG_MAX];

	bool CollisionAxis(ColFloat source, const float fPosMainOld, ColFloat dest, const TYPE otherType);

	ICollisionReader* m_iCollisionReader;	//�����蔻��Ɏg�����̂̎擾�Ɏg���C���^�[�t�F�[�X
	TYPE m_type;							//�����蔻����
	CollisionResult m_collisionResult;		//�����蔻�茋��
	TAG m_tag;								//�^�O�i�����蔻��ݒ�p�j
};

#endif // !_COLLISION_H_
