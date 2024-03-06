//======================================================
//
//�X�^�[�g��������[starttext.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _STARTTEXT_H_
#define _STARTTEXT_H_

#include "../../IS_Bace/_Core/_object/object_2d/object2D.h"

//�O���錾
class CObject2D;

//���b�V���t�B�[���h�N���X
class CStartText : public CObject2D
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CStartText();
	~CStartText();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CStartText* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight);

	//�ݒ�
	void SetLitParam(const int nDef, const int nDegree, const int nPercent);

	//���O
	void Exclusion(void){}
private:
	int m_nCounterUnLit;	//�����J�E���^
	int m_nDefUnLitTime;	//�������Ԋ�{�l
	int m_nDegUnLitTime;		//�������Ԃ΂��
	int m_nUnLitPercent;	//�����m��
};

#endif // !_MESHROAD_H_
