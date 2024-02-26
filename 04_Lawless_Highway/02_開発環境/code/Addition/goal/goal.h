//======================================================
//
//�S�[������[goal.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _GOAL_H_	//���d�C���N���[�h�΍�
#define _GOAL_H_
#include "../../IS_Bace/_Core/_object/object_empty/object.h"
#include "../../IS_Bace/_Core/utility/Utility.h"
#include "../../IS_Bace/_Core/interface.h"

//�O���錾
class CBoxCollider;

//�I�u�W�F�N�g�N���X
class CGoal : public CObject , public ICollisionReader
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CGoal(int nPriority = PRIORITY_02);	//�f�t�H���g
	virtual ~CGoal();

	//��{����
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//����
	static CGoal* Create(const D3DXVECTOR3 pos, const float fWidth, const float fHeight, const float fDepth);

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	bool IsGoal(void) { return m_bIsGoal; }

	//�ݒ�
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }	//�ʒu
	
	//���O
	virtual void Exclusion(void){}

	//�C���^�t�F�[�X����
	D3DXVECTOR3 GetMove(void) { return IS_Utility::VEC3_ZERO; }
	D3DXVECTOR3 GetPosOld(void) { return m_pos; }
	float GetDepth(void) { return m_fDepth; }
	CObject* GetObj(void) { return this; }

private:
	D3DXVECTOR3 m_pos;	//�ʒu
	float m_fWidth;		//��
	float m_fHeight;	//����
	float m_fDepth;		//���s
	bool m_bIsGoal;		//�S�[��������
	CBoxCollider* m_pCollider;
};

#endif	//���d