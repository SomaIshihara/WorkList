//======================================================
//
//�}���`�w�i�i2D�j�����̃w�b�_[bg.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _MULTIPLE_BG_H_
#define _MULTIPLE_BG_H_
#include "main.h"
#include "manager.h"
#include "object.h"

#define MAX_MULTIPLE_BG	(3)	//���d�w�i�̌�
class CObject2D;

class CMultipleBG : public CObject	//���̃N���X�͊Ǘ��I�u�W�F�N�g�ł��BUnity�ł�����̃I�u�W�F�N�g�݂����Ȃ��́B
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CMultipleBG(int nPriority = PRIORITY_BG);				//�f�t�H���g
	~CMultipleBG();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CMultipleBG* Create(float fSpeed0, float fSpeed1, float fSpeed2);	//�I�u�W�F�N�g�𐶐� fSpeed:�X�N���[�����x

	//�擾�i�������z�֐��̊֌W��������Ă��邪�A�����Ɉʒu���T�C�Y���͂���Ȃ��̂ł��ׂ�0��Ԃ��j
	D3DXVECTOR3 GetPos(void) { return VEC3_ZERO; }
	D3DXVECTOR3 GetRot(void) { return VEC3_ZERO; }
	float GetWidth(void) { return FLOAT_ZERO; }
	float GetHeight(void) { return FLOAT_ZERO; }
	float GetDepth(void) { return FLOAT_ZERO; }

private:
	CObject2D* m_pObj2D[MAX_MULTIPLE_BG];	//2D�I�u�W�F�N�g
	float m_aTexV[MAX_MULTIPLE_BG];			//�w�i�̃e�N�X�`�����W
	float m_aSpeed[MAX_MULTIPLE_BG];		//�w�i�̃X�N���[�����x
	int m_aIdxTexture[MAX_MULTIPLE_BG];		//�e�N�X�`���ԍ�
};

#endif // !_MULTIPLE_BG_H_