//======================================================
//
//�{�^������(3D)�̃w�b�_[button3D.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _BUTTON_3D_H_	//���d�C���N���[�h�΍�
#define _BUTTON_3D_H_

#include "object3D.h"

//3D�{�^���N���X
class CButton3D : public CObject3D
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CButton3D(int nPriority = PRIORITY_05);
	~CButton3D();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CButton3D* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight);

	//��Ԏ擾����
	bool IsHold(void) { return m_bHold; }
	bool IsClickPress(void) { return m_bPress; }
	bool IsClickTrigger(void) { return m_bTrigger; }
	bool IsClickRelease(void) { return m_bRelease; }
	bool IsClickRepeate(void) { return m_bRepeate; }
private:
	bool m_bHold;				//�������Ă���
	bool m_bPress;				//�v���X
	bool m_bTrigger;			//�g���K�[
	bool m_bRelease;			//�����[�X
	bool m_bRepeate;			//���s�[�g
};

#endif	//���d
