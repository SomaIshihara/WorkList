//======================================================
//
//�G�t�F�N�g�����̃w�b�_[effect.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"
#include "object2D.h"
#include "objectBillboard.h"

//�D�揇��
#define EFFECT_PRIORITY	(4)

//�G�t�F�N�g�\���̒�`
typedef struct
{
	D3DXVECTOR3 move;	//�ړ���
	D3DXCOLOR col;		//�F
	int nLife;			//����
} Effect;

//========================================
//2D�G�t�F�N�g
//========================================
class CEffect2D : public CObject2D
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CEffect2D(int nPriority = EFFECT_PRIORITY);			//�f�t�H���g
	CEffect2D(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fWidth, const float fHeight,
		const D3DXCOLOR col, const int nLife, int nPriority = EFFECT_PRIORITY);		//�I�[�o�[���[�h�i�G�t�F�N�g���낢��ݒ�j
	~CEffect2D();

	//����
	static CEffect2D* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fWidth, const float fHeight,
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

//========================================
//�r���{�[�h�G�t�F�N�g
//========================================
class CEffectBillboard : public CObjectBillboard
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CEffectBillboard(int nPriority = EFFECT_PRIORITY);			//�f�t�H���g
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
	Effect m_effect;						//�G�t�F�N�g�\����
	const int m_nDefLife;					//�ݒ����
};

#endif // !_BG_H_