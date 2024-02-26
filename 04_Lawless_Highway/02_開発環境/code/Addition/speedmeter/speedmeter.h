//======================================================
//
//�X�s�[�h���[�^�[����[speedmeter.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _SPEEDMETER_H_
#define _SPEEDMETER_H_

#include "../../IS_Bace/_Core/_object/object_empty/object.h"

//�O���錾
class CObject2D;

//���b�V���t�B�[���h�N���X
class CSpeedMeter : public CObject
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CSpeedMeter();
	~CSpeedMeter();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ݒ�
	void SetPos(const D3DXVECTOR3 pos);
	void SetGauge(const float gauge);

	//����
	static CSpeedMeter* Create(const D3DXVECTOR3 pos, const float fRadius);

	//���O
	void Exclusion(void){}
private:
	D3DXVECTOR3 m_pos;
	float m_fRadius;
	CObject2D* m_pObjFrame;
	CObject2D* m_pObjMeter;
};

#endif // !_MESHROAD_H_
