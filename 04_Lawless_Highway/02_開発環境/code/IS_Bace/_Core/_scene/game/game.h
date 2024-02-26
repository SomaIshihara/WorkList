//======================================================
//
//�Q�[���V�[���̃w�b�_[game.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _GAME_H_
#define _GAME_H_
#include "..\..\manager\manager.h"

//�O���錾
class CPause;
class CFade;
class CTimerMSmS;
class CPlayer;
class CGauge;
class CGoal;
class CObject2D;

//�^�C�g���N���X
class CGame : public CScene
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CGame();
	~CGame();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CPause* m_pPause;		//�|�[�Y
	CFade* m_pFade;			//�t�F�[�h
	CTimerMSmS* m_pTimer;	//�^�C�}�[
	CPlayer* m_pPlayer;
	CGauge* m_pGauge;
	CGoal* m_pGoal;
	CObject2D* m_pConfig;
	bool m_bIsGoal;
	bool m_bUseGP;
	float m_fBGMVolume;
};

#endif // !_GAME_H_
