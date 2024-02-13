//======================================================
//
//���b�V���t�B�[���h�����̃w�b�_[meshField.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _MESHFIELD_H_	//���d�C���N���[�h�΍�
#define _MESHFIELD_H_

//�K�v�Ȃ��̂̃C���N���[�h
#include "object.h"
#include "manager.h"

//���b�V���t�B�[���h�N���X
class CMeshField : public CObject
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CMeshField();
	~CMeshField();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CMeshField* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fDepth,
		const int nBlockWidth,const int nBlockDepth);

	//�e�N�X�`���ݒ�
	void BindTexture(int nIdx) { m_nIdxTexture = nIdx; }

	//�ݒ�
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }	//�ʒu
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }	//����

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return CManager::FLT_ZERO; }
	float GetDepth(void) { return m_fDepth; }
	int GetIdxTexture(void) { return m_nIdxTexture; }
	int GetModelIdx(void) { return -1; }

	//�������߂�
	float GetHeight(D3DXVECTOR3 posNew);

	//���O�i�K�v�Ȃ��j
	void Exclusion(void){}
private:
	//�֐�
	WORD* SetIdxSwaingField(int nCntWidth, WORD *pIdx);

	//�ϐ�
	int m_nIdxTexture;					//�e�N�X�`���ԍ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxbuff;	//���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//�C���f�b�N�X�o�b�t�@
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g��

	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
	float m_fWidth;		//��
	float m_fDepth;		//���s
	int m_nBlockWidth;	//�u���b�N��
	int m_nBlockDepth;	//�u���b�N���s
};

#endif	//���d
