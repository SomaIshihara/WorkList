//======================================================
//
//�G�����̃w�b�_[enemy.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "objectAnim2D.h"

//�D�揇��
#define ENEMY_PRIORITY	(4)

class CEnemy : public CObjectAnim2D
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CEnemy(int nPriority = ENEMY_PRIORITY);	//�f�t�H���g
	CEnemy(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight,
		const int nAnimSpeed, const int nDamage, int nPriority = ENEMY_PRIORITY);	//�I�[�o�[���[�h�i�ʒu����and�A�j���[�V�����j
	~CEnemy();

	//����
	static CEnemy* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const int nAnimSpeed, const int nDamage);

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ݒ�
	void AddDamage(int nDamage);

private:
	int m_nIdxTexture;		//�e�N�X�`���ԍ�
	D3DXVECTOR3 m_move;		//�ړ���
	int m_nLife;			//�̗�
};

#endif // !_PLAYER_H_