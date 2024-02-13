//======================================================
//
//�X�R�A�����̃w�b�_[score.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "object2D.h"
#include "interface.h"

#define SCORE_DIGIT	(6)	//�X�R�A�̌���

//�O���錾
class CNumber;

class CScore : public CObject, public IScoreSetter
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CScore(int nPriority = PRIORITY_05);	//�f�t�H���g
	~CScore();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CScore* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight);	//�I�u�W�F�N�g�𐶐�(fOneWidth,fOneHeight:1��������̃T�C�Y)

	//�擾�i�������z�֐��̊֌W��������Ă��邪�A�����ɃT�C�Y���͂���Ȃ��̂ł��ׂ�0��Ԃ��j
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	/*float GetWidth(void) { return CManager::FLT_ZERO; }
	float GetHeight(void) { return CManager::FLT_ZERO; }
	float GetDepth(void) { return CManager::FLT_ZERO; }*/
	/*int GetModelIdx(void) { return -1; }*/
	int GetScore(void) { return m_nScore; }

	//�ݒ�
	void Set(const int nScore);	//�X�R�A�ݒ�
	void Add(const int nAdd);	//�X�R�A���Z
	void BindTexture(const int nIdx);	//�e�N�X�`���ݒ�i�����I�u�W�F�N�g���ׂĂɓK�p�j

	//���O�i�K�v�Ȃ��j
	void Exclusion(void){}

private:
	//�֐�
	void CutNumber(void);				//��������

	//�ϐ�
	CNumber* m_pNumber[SCORE_DIGIT];	//����
	D3DXVECTOR3 m_pos;					//�ʒu�i1���ڂ̐����̒��S��z��j
	D3DXVECTOR3 m_rot;					//�����i1���ڂ̐����̒��S��z��j
	int m_nScore;						//�X�R�A
};

#endif	//���d