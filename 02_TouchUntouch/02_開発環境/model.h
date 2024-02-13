//======================================================
//
//���f�������̃w�b�_[model.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//�O���錾
class CMotion;

//���f���i�K�w�\������j�N���X
class CModel
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CModel();
	~CModel();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CModel* Create(const char* pPath, const D3DXVECTOR3 posOffset, const D3DXVECTOR3 rotOffset);
	
	//�e�q�ݒ�
	void SetParent(CModel* pModel) { m_pParent = pModel; }

	//�擾
	D3DXVECTOR3 GetPosOffset(void) { return m_pos; }
	D3DXVECTOR3 GetRotOffset(void) { return m_rot; }
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }

	//�ݒ�
	void SetPosMotioned(D3DXVECTOR3 pos) { m_posMotioned = pos; }
	void SetRotMotioned(D3DXVECTOR3 rot) { m_rotMotioned = rot; }
	void SetPosOffset(D3DXVECTOR3 pos) { m_pos = pos; }

	//�ǂݍ���
	HRESULT Load(const char* pPath);

private:
	//���f��
	LPD3DXMESH m_pMesh;			//���b�V��
	LPD3DXBUFFER m_pBuffMat;	//�}�e���A���|�C���^
	DWORD m_dwNumMatModel;		//�}�e��
	int* m_pIdxtexture;			//�e�N�X�`���ԍ��i���I�m�ہj

	//�ʒu��
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_posMotioned;	//���[�V������̈ʒu
	D3DXVECTOR3 m_rotMotioned;	//���[�V������̌���
	D3DXMATRIX m_mtxWorld;		//���[���h�}�g��
	CModel* m_pParent;			//�e���f���|�C���^
};

#endif // !_MODEL_H_
