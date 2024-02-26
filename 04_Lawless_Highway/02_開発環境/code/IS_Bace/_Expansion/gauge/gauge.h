//======================================================
//
//�Q�[�W����[gauge.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "../../_Core/_object/object_empty/object.h"

class CObject2D;

//******************************************************************
// �Q�[�W�N���X
//******************************************************************
class CGauge : public CObject
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CGauge(int nPriority = PRIORITY_05);	//�f�t�H���g
	virtual ~CGauge();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�I�u�W�F�N�g�𐶐�
	static CGauge* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight);

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	float GetRate(void) { return m_fGaugeRate; }

	//�ݒ�
	void SetPos(const D3DXVECTOR3 pos);
	void SetRot(const D3DXVECTOR3 rot);
	void AddRate(const float rate) { SetRate(m_fGaugeRate + rate); }
	void SetRate(const float rate);

	//���O�i�K�v�Ȃ��j
	void Exclusion(void){}
private:
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_defaultPos;	//��{�ʒu
	D3DXVECTOR3 m_rot;	//����
	float m_fGaugeRate;	//�Q�[�W�̊���
	float m_fDefaultWidth;

	//�I�u�W�F�N�g
	CObject2D* m_apObj[2];	//[0]:�g,[1]:�Q�[�W
};

#endif	//���d