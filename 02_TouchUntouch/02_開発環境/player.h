//======================================================
//
//�v���C���[�����̃w�b�_[player.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "character.h"
#include "interface.h"

//�O���錾
class CInputGamePad;

//�v���C���[�N���X
class CPlayer : public IControllStat
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CPlayer();
	~CPlayer();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	//�C���^�[�t�F�[�X
	int GetType(void) { return m_controllType; }	//���쒆�̃L�����^�C�v
	int GetPress(void) { return m_nPressMove; };	//�����
	bool IsJump(void) { return m_bPressJump; }		//�W�����v���邩

	//�ݒ�
	void SetControll(const bool bEnable) { m_bControlled = bEnable; }

private:
	//�ϐ�
	CCharacter::TYPE m_controllType;				//���쒆�̃L�����̃^�C�v
	int m_nPressMove;								//������Ă���ړ��g�p�{�^��
	bool m_bPressJump;								//�W�����v�{�^����������Ă��邩
	bool m_bControlled;								//����ł��邩
};

#endif