//======================================================
//
//�^�C�g���V�[���̃w�b�_[title.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "manager.h"

//�O���錾
class CFade;
class CObject2D;

//�^�C�g���N���X
class CTitle : public CScene
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CTitle();
	~CTitle();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CFade* m_pFade;			//�t�F�[�h�I�u�W�F�N�g
	CObject2D* m_pStart;	//�X�^�[�g�����i���͂ɂ���Đؑցj
};

#endif // !_TITLE_H_
