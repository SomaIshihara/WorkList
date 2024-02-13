//======================================================
//
//�L�������̃w�b�_[symbol.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include "main.h"
#include "object2D.h"

class CSymbol : public CObject2D
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CSymbol(int nPriority = PRIORITY_UI);										//�f�t�H���g
	CSymbol(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,
		const float fWidth, const float fHeight, int nPriority = PRIORITY_UI);	//�I�[�o�[���[�h�i�ʒu�����p�^�[���j
	~CSymbol();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//������p�e�N�X�`���ݒ�
	void BindTexture(int nIdx);

	//�ݒ�
	void SetSymbol(const int nNum);	//���ƂƂȂ鐔���ƌ���������ƕ������Ă����

	//����
	static CSymbol* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight);

private:
	int m_nIdxTexture;	//�e�N�X�`���ԍ�
};

#endif // !_OBJ_ANIM2D_H_