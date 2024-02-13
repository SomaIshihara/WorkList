//======================================================
//
//�v���C���[�����̃w�b�_[player.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//�O���錾
class CObject;
class CButton2D;
class CProgressBar;

//�v���C���[�N���X
class CPlayer
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CPlayer();
	~CPlayer();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	//�U������
	void Attack(void);

	//���e����
	void AddPicto(const int nDestroyer, const int nBlocker, const int nNormal);

private:
	//�֐�
	void Move(void);								//�J�����ړ�����
	void Rotate(void);								//�J������]����
	void Select(void);								//�I�u�W�F�N�g�I��

	//�ϐ�
	CButton2D* m_pButtonATK;		//�U���{�^��
	CProgressBar* m_pProgBar;		//�i���o�[

	bool m_bControllPicto;			//�s�N�g����𑀏c���邩�ǂ���
	CObject* m_pObject;				//�I�𒆂̌����E�s�N�g

	D3DXVECTOR3 m_cursorPos;	//�N���b�N�O�̃J�[�\���ʒu
};

#endif