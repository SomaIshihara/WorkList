//======================================================
//
//�I�u�W�F�N�g�i�r���{�[�h�j�����̃w�b�_[objectBillboard.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _OBJECT_BILLBOARD_H_	//���d�C���N���[�h�΍�
#define _OBJECT_BILLBOARD_H_

#include "..\object_empty\object.h"

//�I�u�W�F�N�g�N���X
class CObjectBillboard : public CObject
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CObjectBillboard(int nPriority = PRIORITY_DEFAULT);		//�f�t�H���g
	virtual ~CObjectBillboard();

	//��{����
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//����
	static CObjectBillboard* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const int nIdxTexture);

	//�e�N�X�`���ݒ�
	void BindTexture(int nIdx) { m_nIdxTexture = nIdx; }

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	float GetWidth(void) { return m_fWidth; }
	float GetDepth(void) { return m_fDepth; }
	int GetIdxTexture(void) { return m_nIdxTexture; }

	//�ݒ�
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }	//�ʒu
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; };	//����
	HRESULT SetCol(const D3DXCOLOR col);	//�F
	HRESULT SetTex(const D3DXVECTOR2 tex0, const D3DXVECTOR2 tex3);	//�e�N�X�`�����W
	HRESULT SetTex(const int u, const int v);	//�e�N�X�`�����W�i�p�^�[���ԍ��w��j
	void SetSize(const float fWidth, const float fDepth);

	//���O
	virtual void Exclusion(void){}

private:
	int m_nIdxTexture;					//�e�N�X�`���ԍ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxbuff;	//���_�o�b�t�@
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g��

	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
	float m_fWidth;		//��(X)
	float m_fDepth;		//���s(Z)
};

#endif	//���d