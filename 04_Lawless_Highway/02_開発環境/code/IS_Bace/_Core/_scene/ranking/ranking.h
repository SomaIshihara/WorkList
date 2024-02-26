//======================================================
//
//�����L���O�V�[���̃w�b�_[ranking.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _RANKING_H_
#define _RANKING_H_
#include "..\..\manager\manager.h"

//�O���錾
class CFade;

//�^�C�g���N���X
class CRanking : public CScene
{
public:
	//�~���b�t���̎��ԍ\����
	struct RankTimeMSmS
	{
		//�f�t�H���g�R���X�g���N�^
		RankTimeMSmS()
		{
			nTime = 0;
			nCounter = 0;
		}
		
		//�ȒP����p�R���X�g���N�^
		RankTimeMSmS(const int time,const int counter)
		{
			nTime = time;
			nCounter = counter;
		}

		int nTime;
		int nCounter;
	};

	//�ÓIconst
	static const int MAX_RANK;

	//�R���X�g���N�^�E�f�X�g���N�^
	CRanking();
	~CRanking();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ݒ�
	static void Set(const RankTimeMSmS nTimer);

private:
	static void Load(RankTimeMSmS* pRanking);
	static void Save(RankTimeMSmS* pRanking);

	//�I�u�W�F�i��������X�R�A�ނ��ׂē������ςŁj
	CFade* m_pFade;
};

#endif // !_RANKING_H_
