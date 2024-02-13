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
class CMeshField;
class CSlider;
class CPause;
class CResult;
class CTimer;
class CScore;
class CHaveNum;
class CLevel;
class CMeshSky;
class CBG;
class CCountDown;

//�^�C�g���N���X
class CGame : public CScene
{
public:
	//�ÓIconst
	static const int CDSTART_TIME;	//�J�E���g�_�E���J�n����

	//�R���X�g���N�^�E�f�X�g���N�^
	CGame();
	~CGame();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�擾
	static CPlayer* GetPlayer(void) { return m_pPlayer; }
	static CMeshField* GetMeshField(void) { return m_pMeshField; }
	static int GetATKNum(void) { return m_nATKBuilding; }
	static int GetDestNum(void) { return m_nDestBuilding; }
	static CScore* GetScoreObj(void) { return m_pScore; }
	static CMeshSky* GetSkyObj(void) { return m_pSky; }
	CSlider* GetSlider(void) { return m_pSlider; }
	static CHaveNum** GetHaveNumObj(void) { return &m_pHaveNum[0]; }
	static CLevel** GetLevelObj(void) { return &m_pLevel[0]; }

private:
	void CulcScore(void);				//�X�R�A�v�Z
	CPause* m_pPause;					//�|�[�Y
	CResult* m_pResult;					//���U���g�i�w�i�ɃQ�[����ʂ��o�������̂Łj
	static CPlayer* m_pPlayer;			//�v���C���[
	CSlider* m_pSlider;					//�X���C�_�[
	static CMeshField* m_pMeshField;	//���b�V���t�B�[���h
	static CTimer* m_pTimer;			//�^�C�}�[
	static CScore* m_pScore;			//�X�R�A
	static CHaveNum* m_pHaveNum[3];		//������
	static CLevel* m_pLevel[2];			//���x��
	static CMeshSky* m_pSky;			//��I�u�W�F
	static int m_nATKBuilding;			//�U����
	static int m_nDestBuilding;			//�S��
	CBG* m_pWarning;					//�̗͌x���̔w�i�ł͂Ȃ����
	CCountDown* m_pCountDown;			//�J�E���g�_�E��
	int m_counterCDStart;				//�J�E���g�_�E���J�n�x������
};

#endif // !_GAME_H_
