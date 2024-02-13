//======================================================
//
//�`���[�g���A���V�[���̃w�b�_[game.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "manager.h"

//�O���錾
class CPlayer;
class CSwitchManager;
class CBlockManager;
class CFade;
class CTutorialObj;

//��
class CGoal;

//�^�C�g���N���X
class CTutorial : public CScene
{
public:
	//�ÓIconst
	static const int TUTORIAL_MOVE;		//�ړ������̔ԍ�
	static const int TUTORIAL_CHANGE;	//�ؑ֐����̔ԍ�

	//�R���X�g���N�^�E�f�X�g���N�^
	CTutorial();
	~CTutorial();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CPlayer* m_pPlayer;					//�v���C���[�|�C���^
	CSwitchManager* m_pSwitchManager;	//�X�C�b�`�}�l
	CBlockManager* m_pBlockManager;		//�u���b�N�}�l
	CFade* m_pFade;						//�t�F�[�h
	CTutorialObj* m_pMoveTutorial;		//�ړ������̃I�u�W�F�N�g�i�e�N�X�`���ς������j
	CTutorialObj* m_pChangeTutorial;	//�ؑ֐����̃I�u�W�F�N�g�i�e�N�X�`���ς������j
};

#endif // !_TUTORIAL_H_
