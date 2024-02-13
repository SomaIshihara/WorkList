//======================================================
//
//�����L���O�V�[���̃w�b�_[ranking.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _RANKING_H_
#define _RANKING_H_
#include "manager.h"

//�O���錾
class CObject2D;
class CScore;
class CFade;

//�^�C�g���N���X
class CRanking : public CScene
{
public:
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
	static void Set(const int nScore);

private:
	static void Load(int* pRanking);
	static void Save(int* pRanking);

	//�I�u�W�F�i��������X�R�A�ނ��ׂē������ςŁj
	CFade* m_pFade;
	CObject2D* m_pPress;	//�J�ڗp
};

#endif // !_RANKING_H_
