//======================================================
//
//�e�̏����̃w�b�_[shadow.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "object3D.h"

//�e�N���X
class CShadow : public CObject3D
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CShadow();
	~CShadow();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�t�^�i�����j
	static CShadow* Create(void);

	//�j��
	void Release(void);

	//�ݒ�
	void Set(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
private:
	int m_nIdxTexture;	//�e�N�X�`���ԍ�
};

#endif // !_SHADOW_H_
