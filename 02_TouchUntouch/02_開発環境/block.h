//======================================================
//
//�u���b�N�����̃w�b�_[block.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "main.h"
#include "object2D.h"
#include "objectX.h"

//�D�揇��
#define BLOCK_PRIORITY	(2)

//�u���b�N2D�N���X
class CBlock2D : public CObject2D
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CBlock2D(int nPriority = BLOCK_PRIORITY);	//�f�t�H���g
	CBlock2D(const D3DXVECTOR3 pos, const float fWidth, const float fHeight, int nPriority = BLOCK_PRIORITY);	//�I�[�o�[���[�h
	~CBlock2D();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CBlock2D* Create(const D3DXVECTOR3 pos, const float fWidth, const float fHeight);
private:
	int m_nIdxTexture;	//�e�N�X�`���ԍ�
};

//�u���b�N2D�N���X
class CBlock3D : public CObjectX
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CBlock3D(int nPriority = BLOCK_PRIORITY);	//�f�t�H���g
	CBlock3D(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nIdx, int nPriority = BLOCK_PRIORITY);	//�I�[�o�[���[�h
	~CBlock3D();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CBlock3D* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nIdx);
private:
	int m_nIdxTexture;	//�e�N�X�`���ԍ�
};

#endif // !_BLOCK_H_
