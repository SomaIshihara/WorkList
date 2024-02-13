//======================================================
//
//��ԃv���O�����̃w�b�_[koban.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _KOBAN_H_
#define _KOBAN_H_
#include "objectX.h"
#include "xmodel.h"
#include <vector>

//��ԃN���X
class CKoban : public CObjectX
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CKoban();
	CKoban(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, CXModel* pModel);
	~CKoban();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CKoban* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, CXModel* pModel);

	//�擾
	static CKoban* GetKoban(const int nID) { return m_apKoban[nID]; }
	static CKoban** GetKoban(void) { return &m_apKoban[0]; }
	static int GetNumAll(void) { return m_nNumAll; }

private:
	static CKoban* m_apKoban[MAX_OBJ];	//��ԏ��
	int m_nID;					//ID
	static int m_nNumAll;		//����
};

#endif // !_KOBAN_H_
