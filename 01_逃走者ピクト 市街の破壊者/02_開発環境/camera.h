//==========================================
//
//�J�����v���O�����̃w�b�_[camera.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#define CAMERA_MOVE_SPEED		(10.0f)		//�J�����ړ����x
#define CAMERA_MOU_ROT_SPEED	(0.0012f)	//�}�E�X�ړ��ł̉�]���x

//�N���X���������̂�������ł�
class CCamera
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CCamera();
	~CCamera();
	
	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	//�ݒ菈��
	void SetCamera(void);

	//�ʒu�ړ�
	void SetPos(const D3DXVECTOR3 move);
	void SetRot(const D3DXVECTOR3 rot);

	//�ݒ�
	void SetLength(const float fLength) { m_fLength = fLength; }

	//�擾
	D3DXVECTOR3 GetPosV(void) { return m_posV; }
	D3DXVECTOR3 GetPosR(void) { return m_posR; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	//���Z�b�g
	void ResetPos(void);
private:
	//�p�x�C��
	void FixPosV(void);
	void FixPosR(void);
	void FixRot(void);

	//�����o�ϐ�
	D3DXMATRIX m_mtxView;		//�r���[�}�g��
	D3DXMATRIX m_mtxProjection;	//�v���W�F�N�V�����}�g��
	D3DXVECTOR3 m_posV;			//���_
	D3DXVECTOR3 m_posR;			//�����_
	D3DXVECTOR3 m_vecU;			//��x�N�g��
	D3DXVECTOR3 m_rot;			//�p�x
	float m_fLength;			//����
};

#endif // !_CAMERA_H_
