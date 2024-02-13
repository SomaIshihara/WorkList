//======================================================
//
//�X�C�b�`�}�l�[�W���̃w�b�_[switchmanager.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _SWITCHMANAGER_H_
#define _SWITCHMANAGER_H_

#include "object.h"
#include "switch.h"

class CSwitchManager : public CObject
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CSwitchManager(int nPriority = PRIORITY_05);
	~CSwitchManager();

	//����
	static CSwitchManager* Create(void);

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�擾
	bool* IsPush(void) { return &m_aPush[0]; }

	//���Z�b�g
	void Reset(void);

	//���O�i�K�v�Ȃ��j
	void Exclusion(void){}

private:
	bool m_aPush[CSwitch::TYPE_MAX];
};

#endif // !_SWITCHMANAGER_H_