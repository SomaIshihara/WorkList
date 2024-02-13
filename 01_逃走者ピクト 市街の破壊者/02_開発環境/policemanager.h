//======================================================
//
//�x�@�}�l�[�W�������̃w�b�_[policemanager.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _POLICE_MANAGER_H_
#define _POLICE_MANAGER_H_
#include "main.h"
#include "manager.h"
#include "object.h"
#include <vector>

class CPoliceManager : public CObject	
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CPoliceManager(int nPriority = PRIORITY_DEFMM);	//�f�t�H���g
	~CPoliceManager();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CPoliceManager* Create(void);

	//�擾�i�������z�֐��̊֌W��������Ă��邪�A�����Ɉʒu���T�C�Y���͂���Ȃ��̂ł��ׂ�0��Ԃ��j
	D3DXVECTOR3 GetPos(void) { return CManager::VEC3_ZERO; }
	D3DXVECTOR3 GetRot(void) { return CManager::VEC3_ZERO; }
	float GetWidth(void) { return CManager::FLOAT_ZERO; }
	float GetHeight(void) { return CManager::FLOAT_ZERO; }
	float GetDepth(void) { return CManager::FLOAT_ZERO; }

	//�ݒ�
	static void AddPolice(const int nNum) { m_waitingPolice += nNum; }
	static void SetKobanParam(const int nSpawnSpan, const int nPoliceMax, const int nPatrollNum);

	//�_���[�W��
	static void ReportDamage(const int nID) { m_AttackList.emplace_back(nID); }

private:
	static int m_disPatchCT[MAX_OBJ];	//�o�����CT�i�������ƂɊǗ��j
	static std::vector<int> m_AttackList;

	static int m_nCounterSpawn;	//�����J�E���^
	static int m_nSpawnSpan;	//�����̑���

	static int m_waitingPolice;	//�ҋ@���̌x�@�̐l��

	static int m_nPatrollNum;	//�p�g���[���ɍs������l��
	static int m_nPoliceMax;	//�x�@�̍ő�l��
	int m_nLv;					//����o������x�@�̃��x��
};

#endif // !_MULTIPLE_BG_H_