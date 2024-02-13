//======================================================
//
//�A�j���[�V��������I�u�W�F�N�g�i2D�j�����̃w�b�_[objectAnim2D.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _OBJ_ANIM2D_H_
#define _OBJ_ANIM2D_H_

#include "main.h"
#include "object2D.h"

class CObjectAnim2D : public CObject2D
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CObjectAnim2D(int nPriority = 3);																			//�f�t�H���g
	CObjectAnim2D(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, 
		const float fWidth, const float fHeight, const int nAnimSpeed, const bool bLoop, int nPriority = 3);	//�I�[�o�[���[�h�i�ʒu����and�A�j���[�V�����j
	virtual ~CObjectAnim2D();

	//��{����
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//�A�j���[�V����2D�p�e�N�X�`���ݒ菈��
	void BindTexture(int nIdx);

	//����
	static CObjectAnim2D* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const int nAnimSpeed, const bool bLoop);

private:
	int m_nIdxTexture;	//�e�N�X�`���ԍ�
	int m_nAnimSpeed;	//�A�j���[�V�������x
	int m_nCounterAnim;	//�A�j���[�V�����J�E���^
	int m_nPatternAnim;	//�A�j���[�V�����p�^�[��
	bool m_bLoop;		//���[�v���邩
};

#endif // !_OBJ_ANIM2D_H_