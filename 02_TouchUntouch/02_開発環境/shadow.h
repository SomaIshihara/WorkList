//======================================================
//
//�e�̏����̃w�b�_[shadow.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _SHADOW_H_	//���d�C���N���[�h�΍�
#define _SHADOW_H_

//�K�v�Ȃ��̂̃C���N���[�h
#include "object3D.h"
#include "character.h"

//�e�N���X
class CShadow : public CObject3D
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CShadow(int nPriority = CObject::PRIORITY_04);
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
	void Set(D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const CCharacter::TYPE type);

	//���O
	void Exclusion(void) { CObject3D::Exclusion(); }

private:
	float ConpareLength(const float fNear, const float fLength);

	int m_nIdxTexture;	//�e�N�X�`���ԍ�
};

#endif	//���d