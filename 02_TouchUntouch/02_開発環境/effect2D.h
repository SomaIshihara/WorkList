//======================================================
//
//�G�t�F�N�g����(2D)�̃w�b�_[effect2D.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _EFFECT_2D_H_	//���d�C���N���[�h�΍�
#define _EFFECT_2D_H_

#include "object2D.h"

//�D�揇��
#define EFFECT_PRIORITY	(4)

//========================================
//2D�G�t�F�N�g
//========================================
class CEffect2D : public CObject2D
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
	CEffect2D(const int nLife, int nPriority = EFFECT_PRIORITY);			//�f�t�H���g
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

#endif	//���d