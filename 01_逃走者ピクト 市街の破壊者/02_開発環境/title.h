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
class CButton3D;
class CPlayer;
class CSlider;
class CFade;

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

	//�擾�i�Ȃ��̂łʂ�ہj
	CSlider* GetSlider(void) { return nullptr; }

private:
	static CButton3D* m_pButtonStart;
	static CButton3D* m_pButtonRank;
	CFade* m_pFade;
};

#endif // !_TITLE_H_
