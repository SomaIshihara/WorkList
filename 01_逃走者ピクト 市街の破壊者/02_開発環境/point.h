//======================================================
//
//�ړ��|�C���g�̃w�b�_[point.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _POINT_H_
#define _POINT_H_

#include <vector>

//�O���錾
class CObjectX;

//�|�C���g�N���X
class CPoint
{
public:
	//�ÓIconst
	static const float MERGE_LENGTH;	//�|�C���g���}�[�W����͈�
	static const float POINT_INTERVAL;	//�|�C���g�̔z�u�Ԋu

	//�R���X�g���N�^�E�f�X�g���N�^
	CPoint();
	~CPoint();

	//��{����
	HRESULT Init(void);
	static void Update(void);
	static void ReleaseAll(void);
	void Release(void);

	//����
	static CPoint* Create(const D3DXVECTOR3 pos);

	//�T��
	static CPoint* Search(const D3DXVECTOR3 pos, const CPoint* pNowPoint = nullptr);

	//���X�g
	static CPoint* GetTop(void) { return m_pTop; }
	CPoint* GetNext(void) { return m_pNext; }

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	static int GetNumAll(void) { return m_nNumAll; }
	std::vector<CPoint*> GetConnect(void) { return m_connectPoint; }

private:
	static void Death(void);	//���S�t���O�Ɖ����������ւ��܂�

	static CPoint* m_pTop;	//�擪�I�u�W�F�N�g
	static CPoint* m_pCur;	//�Ō���I�u�W�F�N�g
	CPoint* m_pNext;		//���̃I�u�W�F�N�g
	CPoint* m_pPrev;		//�O�̃I�u�W�F�N�g
	bool m_bDeath;			//���S�t���O
	static int m_nNumAll;	//����
	D3DXVECTOR3 m_pos;		//�ʒu
	CObjectX* m_pFrag;		//�f�o�b�O�p��

	std::vector<CPoint*> m_connectPoint;	//�ڑ����Ă���|�C���g
};

#endif // !_POINT_H_
