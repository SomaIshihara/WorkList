//======================================================
//
//�����蔻�菈���̃w�b�_[collision.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "main.h"

//�����蔻��N���X
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

#endif // !_COLLISION_H_
