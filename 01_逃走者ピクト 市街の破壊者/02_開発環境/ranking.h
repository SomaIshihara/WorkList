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
class CFade;

//�^�C�g���N���X
class CRanking : public CScene
{
public:
	//�ÓIconst
	static const int MAX_RANK;					//���ʑ���
	static const int RANK_DISP_X;				//�\����
	static const int RANK_DISP_Y;
	static const D3DXVECTOR3 RANK_START_POS;	//1�ʂ̃X�^�[�g�n�_
	static const float RANK_X_DISTANCE;			//X�̕`��Ԋu
	static const float RANK_Y_DISTANCE;			//Y�̕`��Ԋu
	static const float X_ONE_WIDTH;				//X�̕`��T�C�Y��
	static const float Y_ONE_HEIGHT;			//X�̕`��T�C�Y��
	static const float X_SCORE_DIST;			//X�̃X�R�A�ƈʂ̊Ԋu
	static const int SYMBOL_RANK_NUM;			//�u�ʁv�̈ʒu

	//�R���X�g���N�^�E�f�X�g���N�^
	CRanking();
	~CRanking();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ݒ�
	static void Set(const long long nScore);

	//�擾�i�Ȃ��̂łʂ�ہj
	CSlider* GetSlider(void) { return nullptr; }

private:
	static void Load(long long* pRanking);
	static void Save(long long* pRanking);
	CFade* m_pFade;
};

#endif // !_RANKING_H_
