//======================================================
//
//���������̃w�b�_[number.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _NUMBER_H_	//���d�C���N���[�h�΍�
#define _NUMBER_H_

#include "object2D.h"

class CNumber : public CObject2D
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CNumber(int nPriority = PRIORITY_05);	//�f�t�H���g
	~CNumber();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ݒ�
	void SetNumber(const int nSource, const int nDigit);	//���ƂƂȂ鐔���ƌ���������ƕ������Ă����

	//�e�N�X�`���ݒ�
	void BindTexture(int nIdx);

	//����
	static CNumber* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight);

private:
	
};

#endif	//���d