//======================================================
//
//������[smoke.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _SMOKE_H_
#define _SMOKE_H_

#include "../../IS_Bace/_Core/_object/object_billboard/objectBillboard.h"

//���b�V���t�B�[���h�N���X
class CSmoke : public CObjectBillboard
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CSmoke(int nAnimSpeed = 1);
	~CSmoke();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CSmoke* Create(const D3DXVECTOR3 pos, const float fRadius, const int nAnimSpeed);

	//���O
	void Exclusion(void){}
private:
	int m_nCounter;
	int m_nPattern;
	const int m_nAnimSpeed;
};

#endif // !_MESHROAD_H_
