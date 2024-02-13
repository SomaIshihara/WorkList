//======================================================
//
//�w�i�i2D�j�����̃w�b�_[bg.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _BG_H_	//���d�C���N���[�h�΍�
#define _BG_H_
#include "main.h"
#include "object2D.h"

class CBG : public CObject2D
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CBG(int nPriority = PRIORITY_BG);
	~CBG();

	//����
	static CBG* Create(const int nPriority = PRIORITY_BG);

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nIdxTexture;	//�e�N�X�`���ԍ�
};

#endif	//���d