//======================================================
//
//�`���[�g���A���p�I�u�W�F�����̃w�b�_[tutorialobj.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _TUTORIALOBJ_H_
#define _TUTORIALOBJ_H_

//�K�v�Ȃ̃C���N���[�h
#include "manager.h"
#include "object.h"
#include "interface.h"
#include "collision.h"

//�O���錾
class CObject3D;
class CObjectX;

//�e���|�[�g�����蔻��N���X
class CTutorialObj : public CObject, public ICollisionReader
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CTutorialObj(int nPriority = CObject::PRIORITY_01);
	~CTutorialObj();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CTutorialObj* Create(const D3DXVECTOR3 pos, const int nNumber);

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }	//�����蔻��̈ʒu
	static CTutorialObj* GetTop(void) { return m_pTop; }
	CTutorialObj* GetNext(void) { return m_pNext; }

	//�C���^�[�t�F�[�X
	D3DXVECTOR3 GetMove(void) { return CManager::VEC3_ZERO; }
	D3DXVECTOR3 GetPosOld(void) { return m_pos; }
	void SetPos(const D3DXVECTOR3 pos) {}
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	float GetDepth(void) { return m_fDepth; }
	CObject* GetObj(void) { return this; }
	int GetNumber(void) { return m_nNumAll; }
	CObject3D* GetTutorialStr(void) { return m_pTutorial; }

	//���O
	void Exclusion(void);

	//�\��
	void Popup(void) { m_bPopup = true; }//�`���[�g���A����\��

private:
	//���X�g
	static CTutorialObj* m_pTop;	//���X�g�̍ŏ�
	static CTutorialObj* m_pCur;	//���X�g�̏I�[
	CTutorialObj* m_pNext;		//��
	CTutorialObj* m_pPrev;		//�O
	static int m_nNumAll;				//�e���|�[�g�����蔻�葍��

	CBoxCollider* m_pCollider;			//�����蔻��
	
	CObject3D* m_pTutorial;				//�`���[�g���A���\�����e
	CObjectX* m_pObj;					//���f���I�u�W�F

	D3DXVECTOR3 m_pos;						//�ʒu
	float m_fWidth, m_fHeight, m_fDepth;	//�T�C�Y
	int m_nNumber;				//����No.
	bool m_bPopup;				//�\�����邩
};

#endif // !_TUTORIALOBJ_H_
