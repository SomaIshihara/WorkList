//======================================================
//
//�`���[�g���A���e�L�X�g����[tutorialobj.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _TUTORIAL_OBJ_H_
#define _TUTORIAL_OBJ_H_

#include "../../IS_Bace/_Core/_object/object_2d/object2D.h"
#include "../player/player.h"
#include "../../IS_Bace/_Expansion/timer/timer.h"

//�O���錾
class CTutorialState;

//�`���[�g���A���e�L�X�g�N���X
class CTutorialObj : public CObject2D
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CTutorialObj(int nPriority = CObject::PRIORITY_05);
	~CTutorialObj();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CTutorialObj* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, CTimer* pTimer, CPlayer* pPlayer);

	//�ݒ�
	void SetState(CTutorialState* pState) { m_pState = pState; }
	void SetWaitingPirot(void) { m_pPlayer->SetState(CPlayer::STATE::STATE_SYSTEM_START); }
	void GameStart(void) { m_pPlayer->SetState(CPlayer::STATE::STATE_GAME); m_pTimer->Start(); }
private:
	static const D3DXVECTOR3 PILOT_CHECKPOINT;
	static const D3DXVECTOR3 START_CHECKPOINT;
	CTutorialState* m_pState;
	CPlayer* m_pPlayer;
	CTimer* m_pTimer;
};

//�`���[�g���A�����e���
class CTutorialState
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CTutorialState() {}
	virtual ~CTutorialState(){}

	//�X�V����
	virtual void Update(CTutorialObj* obj, D3DXVECTOR3 playerPos) = 0;
};

//�n���h������
class CTutorial_01 : public CTutorialState
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CTutorial_01(){}
	~CTutorial_01(){}

	//�X�V
	void Update(CTutorialObj* obj, D3DXVECTOR3 playerPos);
private:
	static const D3DXVECTOR3 CHECKPOINT;
};

//�u�[�X�g����
class CTutorial_02 : public CTutorialState
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CTutorial_02() {}
	~CTutorial_02() {}

	//�X�V
	void Update(CTutorialObj* obj, D3DXVECTOR3 playerPos);
private:
	static const D3DXVECTOR3 CHECKPOINT;
};

//�u���[�L�h���t�g����
class CTutorial_03 : public CTutorialState
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CTutorial_03() {}
	~CTutorial_03() {}

	//�X�V
	void Update(CTutorialObj* obj, D3DXVECTOR3 playerPos);
private:
	static const D3DXVECTOR3 CHECKPOINT;
};

//�ړI�\��
class CTutorial_04 : public CTutorialState
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CTutorial_04() { m_bIsSet = false; m_bIsPirot = false; }
	~CTutorial_04() {}

	//�X�V
	void Update(CTutorialObj* obj, D3DXVECTOR3 playerPos);
private:
	bool m_bIsSet;		//�e�N�X�`���ݒ�ς݂�
	bool m_bIsPirot;	//�������c��Ԃɂ�����
};

//�������c��Q�[���؂�ւ�
class CTutorial_05 : public CTutorialState
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CTutorial_05() { m_bIsSet = false; m_bIsPirot = false; }
	~CTutorial_05() {}

	//�X�V
	void Update(CTutorialObj* obj, D3DXVECTOR3 playerPos);
private:
	bool m_bIsSet;		//�e�N�X�`���ݒ�ς݂�
	bool m_bIsPirot;	//�������c��Ԃɂ�����
	static const D3DXVECTOR3 CHECKPOINT;
};

#endif // !_TUTORIAL_OBJ_H_
