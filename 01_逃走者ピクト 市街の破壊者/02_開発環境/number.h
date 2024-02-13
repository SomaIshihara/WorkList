//======================================================
//
//���������̃w�b�_[number.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
#include "object2D.h"

class CNumber : public CObject2D
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CNumber(int nPriority = PRIORITY_UI);										//�f�t�H���g
	CNumber(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,
		const float fWidth, const float fHeight, int nPriority = PRIORITY_UI);	//�I�[�o�[���[�h�i�ʒu�����p�^�[���j
	~CNumber();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//������p�e�N�X�`���ݒ�
	void BindTexture(int nIdx);

	//�ݒ�
	void SetNumber(const long long nSource, const int nDigit);	//���ƂƂȂ鐔���ƌ���������ƕ������Ă����

	//����
	static CNumber* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight);

private:
	int m_nIdxTexture;	//�e�N�X�`���ԍ�
};

#endif // !_OBJ_ANIM2D_H_