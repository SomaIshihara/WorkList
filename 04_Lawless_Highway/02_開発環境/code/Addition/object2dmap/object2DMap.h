//==========================================================
//
// �}�b�v�I�u�W�F�N�g [object2DMap.h]
// Author : Soma Ishihara
//
//==========================================================
#ifndef _OBJECT_MAP_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _OBJECT_MAP_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "../../IS_Bace/_Core/_object/object_2d/object2D.h"

//==========================================================
// �}�b�v�̃N���X��`
//==========================================================
class CObject2DMap : public CObject2D
{
public:	// �N�ł��A�N�Z�X�\

	//�R���X�g���N�^�E�f�X�g���N�^
	CObject2DMap(int nPriority = CObject::PRIORITY_DEFAULT);
	~CObject2DMap();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DrawTexture(void);
	void Load(void);		//�f�o�C�X���X�g�΍�F���X�g����������Ăяo���ĂˁB�������ɂ��g����B
	void UnLoad(void);		//�f�o�C�X���X�g�΍�F���X�g������Ăяo���ĂˁB�I���ɂ��g����B

	//�ݒ�
	void SetCameraPosR(const D3DXVECTOR3 pos) { m_posR = pos; }
	void SetCameraPosV(const D3DXVECTOR3 pos) { m_posV = pos; }

	//����
	static CObject2DMap *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight);
private:	// �����������A�N�Z�X�\
	LPDIRECT3DTEXTURE9 m_pTextureMap;	//�}�b�v�e�N�X�`��
	LPDIRECT3DSURFACE9 m_pZSurface;		// �e�N�X�`���̐[�x�o�b�t�@
	D3DXVECTOR3 m_posR, m_posV;
};

#endif

