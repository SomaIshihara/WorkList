//======================================================
//
//�A�C�e�������̃w�b�_[item.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _ITEM_H_
#define _ITEM_H_
#include "objectX.h"
#include "interface.h"

//�O���錾
class CPictoTaxi;
class CXModel;

//�A�C�e���e�N���X
class CItem : public CObjectX
{
public:
	//�ÓIconst
	static const int GET_SCORE;

	//�R���X�g���N�^�E�f�X�g���N�^
	CItem();
	~CItem();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CItem* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	//�擾
	void Get(void);
	static CItem* GetTop(void) { return m_pTop; }
	CItem* GetNext(void) { return m_pNext; }

	//���X�g���O
	void Exclusion(void);

	//�X�R�A�C���^�[�t�F�[�X�ݒ�
	static void SetScoreInterface(IScoreSetter* pInterface) { m_pScoreInterface = pInterface; }
	static void UnsetScoreInterface(void) { m_pScoreInterface = nullptr; }

private:
	//���X�g
	static CItem* m_pTop;	//���X�g�̍ŏ�
	static CItem* m_pCur;	//���X�g�̏I�[
	CItem* m_pNext;			//��
	CItem* m_pPrev;			//�O

	static int m_nNumAll;
	static IScoreSetter* m_pScoreInterface;

	int m_nScore;
};

#endif // !_BLOCK_H_
