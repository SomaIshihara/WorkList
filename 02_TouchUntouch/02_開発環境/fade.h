//==========================================
//
//�t�F�[�h�\���v���O�����̃w�b�_[fade.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _FADE_H_	//���d�C���N���[�h�΍�
#define _FADE_H_

#include "bg.h"

//�t�F�[�h�N���X
class CFade : public CBG
{
public:
	static const float FADE_SPEED;	//�t�F�[�h�̑���

	//�t�F�[�h�̏��
	typedef enum
	{
		FADE_NONE = 0,	//�������Ȃ�
		FADE_IN,		//�C��
		FADE_OUT,		//�A�E�g
		FADE_MAX
	} FADE;

	//�R���X�g���N�^�E�f�X�g���N�^
	CFade();
	~CFade();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CFade* Create(CScene::MODE sceneNext);

	//�擾
	FADE Get(void) { return m_fade; }

private:
	void SetNext(CScene::MODE sceneNext);

	FADE m_fade;							//���
	CScene::MODE m_modeNext;				//���̃V�[��
	float m_fAlpha;							//�s�����x
};

#endif	//���d
