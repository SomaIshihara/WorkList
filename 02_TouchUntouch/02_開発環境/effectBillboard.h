//======================================================
//
//�G�t�F�N�g����(�r���{�[�h)�̃w�b�_[effectBillboard.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _EFFECT_BILLBOARD_H_	//���d�C���N���[�h�΍�
#define _EFFECT_BILLBOARD_H_

#include "objectBillboard.h"

//�D�揇��
#define EFFECT_PRIORITY	(4)

//========================================
//�r���{�[�h�G�t�F�N�g
//========================================
class CEffectBillboard : public CObjectBillboard
{
public:
	//�G�t�F�N�g�\���̒�`
	typedef struct
	{
		D3DXVECTOR3 move;	//�ړ���
		D3DXCOLOR col;		//�F
		int nLife;			//����
	} Effect;

	//�R���X�g���N�^�E�f�X�g���N�^
	CEffectBillboard(const int nLife, int nPriority = EFFECT_PRIORITY);			//�f�t�H���g
	CEffectBillboard(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fWidth, const float fHeight,
		const D3DXCOLOR col, const int nLife, int nPriority = EFFECT_PRIORITY);		//�I�[�o�[���[�h�i�G�t�F�N�g���낢��ݒ�j
	~CEffectBillboard();

	//����
	static CEffectBillboard* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fWidth, const float fHeight,
		const D3DXCOLOR col, const int nLife);

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nIdxTexture;		//�e�N�X�`���ԍ�
	Effect m_effect;		//�G�t�F�N�g�\����
	const int m_nDefLife;	//�ݒ����
};

#endif	//���d