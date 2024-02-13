//======================================================
//
//�e�����̃w�b�_[bullet.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "objectAnim2D.h"
#include "objectBillboard.h"
#include "picto.h"

//�D�揇��
#define BULLET_PRIORITY	(PRIORITY_DEFAULT)

class CBullet2D : public CObject2D
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CBullet2D(int nPriority = BULLET_PRIORITY);	//�f�t�H���g
	CBullet2D(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const float fSpeed,
		int nPriority = BULLET_PRIORITY);	//�I�[�o�[���[�h�i�ʒu����and�A�j���[�V�����j
	~CBullet2D();

	//����
	static CBullet2D* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const float fSpeed, const TYPE type);

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�Փ˔���
	//bool CollisionEnemy(void);	//�G
	//bool CollisionBlock(void);	//�u���b�N

	//�ݒ菈��
	void SetType(TYPE type) { m_Type = type; }	//�^�C�v�ݒ�

private:
	int m_nIdxTexture;		//�e�N�X�`���ԍ�
	D3DXVECTOR3 m_move;		//�ړ���
	TYPE m_Type;			//�N�̒e��
};

class CBulletBillboard : public CObjectBillboard
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CBulletBillboard(int nPriority = BULLET_PRIORITY);	//�f�t�H���g
	CBulletBillboard(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const float fSpeed, const int nPower,
		CPicto* firePicto, int nPriority = BULLET_PRIORITY);	//�I�[�o�[���[�h�i�ʒu����and�A�j���[�V�����j
	~CBulletBillboard();

	//����
	static CBulletBillboard* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const float fSpeed, 
		const int nPower, const CPicto::TYPE type, CPicto* firePicto);

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�Փ˔���
	bool CollisionBuilding(void);	//�G
	bool CollisionPicto(void);	//�u���b�N

private:
	int m_nIdxTexture;		//�e�N�X�`���ԍ�
	D3DXVECTOR3 m_move;		//�ړ���
	CPicto::TYPE m_Type;		//�N�̒e��
	int m_nPower;			//�U����
	CPicto* m_pfirePicto;		//���˂����s�N�g
};


#endif // !_PLAYER_H_