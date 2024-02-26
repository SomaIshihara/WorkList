//======================================================
//
//���b�V���t�B�[���h�����̃w�b�_[meshField.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "../../_Core/_object/object_empty/object.h"

//���b�V���t�B�[���h�N���X
class CMeshField : public CObject
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CMeshField(int nPriority = CObject::PRIORITY_DEFAULT);
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

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	int GetIdxTexture(void) { return m_nIdxTexture; }
	static CMeshField* GetTop(void) { return m_pTop; }
	CMeshField* GetNext(void) { return m_pNext; }
	float GetWidth(void) { return m_fWidth; }
	float GetDepth(void) { return m_fDepth; }
	int GetBlockWidth(void) { return m_nBlockWidth; }
	int GetBlockDepth(void) { return m_nBlockDepth; }

	//�ݒ�
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetSize(const float fWidth, const float fDepth) { m_fWidth = fWidth; m_fDepth = fDepth; }
	void SetBlock(const int nWidth, const int nDepth) { m_nBlockWidth = nWidth; m_nBlockDepth = nDepth; }
	void SetCol(const D3DXCOLOR col) { m_color = col; SetVtxCol(); }

	//�v�Z
	float GetHeight(D3DXVECTOR3 posOld, D3DXVECTOR3 posNew);
	D3DXVECTOR3 GetLandingRot(D3DXVECTOR3 posOld, D3DXVECTOR3 posLanding, float rotY);
	static float GetHeightAll(D3DXVECTOR3 posOld, D3DXVECTOR3 posNew);
	static D3DXVECTOR3 GetLandingRotAll(D3DXVECTOR3 posOld, D3DXVECTOR3 posLanding, float rotY);
	bool GetLanding(D3DXVECTOR3 posOld, D3DXVECTOR3 poslanding, D3DXVECTOR3* pOutposVtx, D3DXVECTOR3* pOutNor, D3DXVECTOR3* pOutUpVec = nullptr);

	//���O
	virtual void Exclusion(void);
protected:
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxbuff; }

private:
	//�֐�
	void CreateBuff(void);
	void ReleaseBuff(void);
	void SetVtxBuff(void);
	void SetVtxPos(void);
	void SetVtxCol(void);
	void SetVtxTex(void);
	void SetVtxNor(void);
	void SetIdxBuff(void);
	WORD* SetIdxSwaingField(int nCntWidth, WORD *pIdx);

	//�ϐ�
	int m_nIdxTexture;					//�e�N�X�`���ԍ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxbuff;	//���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//�C���f�b�N�X�o�b�t�@
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g��

	//�ʒu��
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
	float m_fWidth;		//��
	float m_fDepth;		//���s
	int m_nBlockWidth;	//�u���b�N��
	int m_nBlockDepth;	//�u���b�N���s
	D3DXCOLOR m_color;	//���_�J���[

	//���X�g
	static CMeshField* m_pTop;	//�擪�I�u�W�F�N�g
	static CMeshField* m_pCur;	//�Ō���I�u�W�F�N�g
	CMeshField* m_pNext;		//���̃I�u�W�F�N�g
	CMeshField* m_pPrev;		//�O�̃I�u�W�F�N�g
	static int m_nNumAll;		//����
};

#endif // !_MESHFIELD_H_
