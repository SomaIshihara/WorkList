//======================================================
//
//�u���b�N�}�l�[�W���̃w�b�_[blockmanager.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _BLOCKMANAGER_H_
#define _BLOCKMANAGER_H_

#include "object.h"
#include "switch.h"
#include "interface.h"

//�O���錾
class CSwitchManager;
class CXModel;

class CBlockManager : public CObject
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CBlockManager(int nPriority = PRIORITY_04);
	~CBlockManager();

	//����
	static CBlockManager* Create(CSwitchManager* pSwitchManager, IControllStat* iControllStat);

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//���O�i�K�v�Ȃ��j
	void Exclusion(void){}

private:
	CSwitchManager* m_pSwitchManager;	//�X�C�b�`�}�l
	IControllStat* m_iControllStat;		//�����ԃC���^�[�t�F�[�X

	//���f��
	static CXModel* m_pModelNor;		//�ʏ�̃��f��
	static CXModel* m_pModelGimOff;		//�M�~�b�N�ނ��I�t�̎��p
};

#endif // !_SWITCHMANAGER_H_