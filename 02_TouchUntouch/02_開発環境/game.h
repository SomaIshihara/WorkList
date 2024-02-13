//======================================================
//
//�Q�[���V�[���̃w�b�_[game.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _GAME_H_
#define _GAME_H_
#include "manager.h"

//�O���錾
class CPlayer;
class CScore;
class CTimer;
class CResult;
class CSwitchManager;
class CBlockManager;
class CPause;

//��
class CGoal;

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
	CPlayer* m_pPlayer;	//�v���C���[�|�C���^
	CScore* m_pScore;	//�X�R�A�|�C���^
	CTimer* m_pTimer;	//�^�C�}�[�|�C���^
	CResult* m_pResult;	//���U���g�|�C���^
	CSwitchManager* m_pSwitchManager;	//�X�C�b�`�}�l
	CBlockManager* m_pBlockManager;		//�u���b�N�}�l
	CPause* m_pPause;	//�|�[�Y
	bool m_bStart;		//�Q�[�����n�߂���
};

#endif // !_GAME_H_
