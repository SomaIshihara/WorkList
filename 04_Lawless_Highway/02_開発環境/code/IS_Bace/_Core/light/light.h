//==========================================
//
//���C�g�v���O�����̃w�b�_[light.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//�}�N��
#define MAX_LIGHT	(4)	//���C�g��

//�N���X���������̂�������ł�
class CLight
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CLight();
	~CLight();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];	//���C�g�\����
};

#endif // !_LIGHT_H_
