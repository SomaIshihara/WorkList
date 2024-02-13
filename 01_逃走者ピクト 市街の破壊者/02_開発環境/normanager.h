//======================================================
//
//��ʐl�}�l�[�W���̃w�b�_[normanager.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _NORMANAGER_H_
#define _NORMANAGER_H_
#include "main.h"
#include "object.h"
#include "manager.h"

class CNorManager : public CObject
{
public:
	//�ÓIconst
	static const int RESEARCH_NUM;				//������
	static const float NOBUILDING_TIME_PERCE;	//�ĒT���̎��Ԃ̊���

	//�R���X�g���N�^�E�f�X�g���N�^
	CNorManager(int nPriority = PRIORITY_DEFAULT);
	~CNorManager();

	//����
	static CNorManager* Create(void);

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�擾�i���ɂȂ���Ԃ��K�v���Ȃ��j
	D3DXVECTOR3 GetPos(void) { return CManager::VEC3_ZERO; }
	D3DXVECTOR3 GetRot(void) { return CManager::VEC3_ZERO; }
	float GetWidth(void) { return CManager::FLOAT_ZERO; }
	float GetHeight(void) { return CManager::FLOAT_ZERO; }
	float GetDepth(void) { return CManager::FLOAT_ZERO; }

	//�ݒ�
	void SetNum(const int maxNum) { m_maxPicto = maxNum; }
	void SetTime(const int time) { m_spawnTime = time; }

private:
	int m_maxPicto;		//��ʐl�̏��
	int m_spawnTime;	//�������̂ɂ����鎞��
	int m_counter;		//�����J�E���^�[
};

#endif // !_NORMANAGER_H_