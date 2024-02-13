//======================================================
//
//�I�u�W�F�N�g�i2D�j�����̃w�b�_[object2D.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _OBJECT2D_H_	//���d�C���N���[�h�΍�
#define _OBJECT2D_H_
#include "main.h"
#include "manager.h"
#include "object.h"

//�p�^�[���e�N�X�`���\���̒�`
typedef struct
{
	LPDIRECT3DTEXTURE9 pTexture;	//�e�N�X�`���|�C���^
	int nPatternWidth;				//�p�^�[����
	int nPatternHeight;				//�p�^�[������
} PatternTexture;

//�I�u�W�F�N�g�N���X
class CObject2D : public CObject
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CObject2D(int nPriority = PRIORITY_DEFAULT);	//�f�t�H���g
	virtual ~CObject2D();

	//��{����
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//����
	static CObject2D* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const int nPriority = PRIORITY_DEFAULT);

	//�e�N�X�`���ݒ�
	virtual void BindTexture(int nIdx) { m_nIdxTexture = nIdx; }

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	float GetLength(void) { return m_fLength; }
	int GetIdxTexture(void) { return m_nIdxTexture; }

	//�ݒ�
	HRESULT SetPos(const D3DXVECTOR3 pos);	//�ʒu
	HRESULT SetRot(const D3DXVECTOR3 rot);	//����
	HRESULT SetCol(const D3DXCOLOR col);	//�F
	HRESULT SetTex(const D3DXVECTOR2 tex0, const D3DXVECTOR2 tex3);	//�e�N�X�`�����W
	HRESULT SetSize(const float fWidth, const float fHeight);		//�T�C�Y

	//���O
	virtual void Exclusion(void){}

private:
	//���_�ʒu�ݒ�
	HRESULT SetVtxPos(void);

	LPDIRECT3DVERTEXBUFFER9 m_pVtxbuff;		//���_�o�b�t�@
	int m_nIdxTexture;	//�e�N�X�`���ԍ�
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
	float m_fLength;	//����
	float m_fAngle;		//�p�x
	float m_fWidth;		//��
	float m_fHeight;	//����
};

#endif	//���d