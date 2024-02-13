//======================================================
//
//���b�V���󏈗��̃w�b�_[meshsky.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _MESHSKY_H_		//���d�C���N���[�h�΍�
#define _MESHSKY_H_

//�K�v�Ȃ��̂̃C���N���[�h
#include "object.h"
#include "manager.h"

//���b�V����N���X
class CMeshSky : public CObject
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CMeshSky();
	~CMeshSky();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CMeshSky* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fRadius, const int nBlockWidth,const int nBlockDepth);

	//�e�N�X�`���ݒ�
	void BindTexture(int nIdx) { m_nIdxTexture = nIdx; }

	//�ݒ�
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }	//�ʒu
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }	//����

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	float GetWidth(void) { return CManager::FLT_ZERO; }
	float GetHeight(void) { return m_fRadius; }
	float GetDepth(void) { return CManager::FLT_ZERO; }
	int GetIdxTexture(void) { return m_nIdxTexture; }
	int GetModelIdx(void) { return -1; }

	//���O�i�K�v�Ȃ��j
	void Exclusion(void){}
private:
	//�֐�
	WORD* SetIdxSwaingField(int nCntWidth, WORD *pIdx);

	//�ϐ�
	int m_nIdxTexture;					//�e�N�X�`���ԍ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxbuff;	//���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuffTop;		//�㕔�C���f�b�N�X�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuffMiddle;	//�����C���f�b�N�X�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuffBottom;	//�����C���f�b�N�X�o�b�t�@
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g��

	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
	float m_fRadius;	//���a
	int m_nBlockVertical;	//�u���b�N��
	int m_nBlockHorizontal;	//�u���b�N���s
};

#endif	//���d