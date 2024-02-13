//======================================================
//
//X�t�@�C�����f���̃w�b�_[xmodel.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _XMODEL_H_
#define _XMODEL_H_

#include "collision.h"

//X���f���N���X
class CXModel
{
public:
	enum LOADRESULT
	{
		RES_OK = 0,
		RES_ERR_LIST_NOTFOUND,
		RES_ERR_MODEL_NOTFOUND,
		RES_MAX
	};

	//�R���X�g���N�^�E�f�X�g���N�^
	CXModel();
	~CXModel();

	//�ǂݍ��݊֌W
	static CXModel* Load(const char* pPath);
	void Unload(void);
	static void UnloadAll(void);

	//�擾
	LPD3DXMESH GetMesh(void) { return m_pMesh; }
	LPD3DXBUFFER GetBufMat(void) { return m_pBuffMat; }
	DWORD GetNumMat(void) { return m_dwNumMatModel; }
	int* GetIdxTexture(void) { return m_pIdxtexture; }
	char* GetPath(void) { return m_pFilePath; }
	CCollision GetCollision(void) { return m_collision; }
	static int GetNumAll(void) { return m_nNumAll; }	

	//���X�g�擾
	static CXModel* GetTop(void) { return m_pTop; }
	CXModel* GetNext(void) { return m_pNext; }

private:
	//���X�g
	static CXModel* m_pTop;		//�擪�I�u�W�F�N�g
	static CXModel* m_pCur;		//�Ō���I�u�W�F�N�g
	CXModel* m_pNext;			//���̃I�u�W�F�N�g
	CXModel* m_pPrev;			//�O�̃I�u�W�F�N�g
	bool m_bExclusion;			//���O�t���O
	static int m_nNumAll;		//����

	LPD3DXMESH m_pMesh;			//���b�V��
	LPD3DXBUFFER m_pBuffMat;	//�}�e���A���|�C���^
	DWORD m_dwNumMatModel;		//�}�e��
	int* m_pIdxtexture;			//�e�N�X�`���ԍ��i���I�m�ہj

	char* m_pFilePath;			//�t�@�C���p�X�i�����������I�m�ہj
	CCollision m_collision;		//�R���W����
};

#endif // !_XMODEL_H_