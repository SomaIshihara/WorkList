//======================================================
//
//�p�[�e�B�N��(�r���{�[�h)�����̃w�b�_[particleBillboard.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _PARTICLE_BILLBOARD_H_
#define _PARTICLE_BILLBOARD_H_

#include "manager.h"
#include "object.h"

#define MAX_EFFECT	(1024)	//�G�t�F�N�g�ő��

//========================================
//�r���{�[�h�p�[�e�B�N��
//========================================
class CParticleBillboard : public CObject	//���̃N���X�͊Ǘ��I�u�W�F�N�g�ł��BUnity�ł�����̃I�u�W�F�N�g�݂����Ȃ��́B
{
public:
	//�p�[�e�B�N���\���̒�`
	typedef struct
	{
		//�p�[�e�B�N���֌W
		D3DXVECTOR3 pos;		//�p�[�e�B�N�����o�ʒu
		int nLife;				//�p�[�e�B�N���̎���
		int nEffeceNum;			//��x�ɏo���G�t�F�N�g��
		float fSpeedBace;		//�X�s�[�h��{�l
		float fSpeedDegree;		//�X�s�[�h�U�ꕝ

		//�G�t�F�N�g�֌W
		D3DXCOLOR col;			//�G�t�F�N�g�̐F
		float fWidth;			//�G�t�F�N�g1�̕�
		float fHeight;			//�G�t�F�N�g1�̍���
	} Particle;
	//�R���X�g���N�^�E�f�X�g���N�^
	CParticleBillboard();	//�f�t�H���g
	~CParticleBillboard();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void) {}

	//����
	static CParticleBillboard* Create(const D3DXVECTOR3 pos, const int nLife, const int nEffeceNum, const float fSpeedBace, const float fSpeedDegree,
		const D3DXCOLOR col, const float fWidth, const float fHeight);	//�I�u�W�F�N�g�𐶐�

	//�擾�i�������z�֐��̊֌W��������Ă��邪�A�����ɃT�C�Y���͂���Ȃ��̂ł��ׂ�0��Ԃ��j
	D3DXVECTOR3 GetPos(void) { return m_particle.pos; }
	D3DXVECTOR3 GetRot(void) { return CManager::VEC3_ZERO; }
	//float GetWidth(void) { return CManager::FLT_ZERO; }
	//float GetHeight(void) { return CManager::FLT_ZERO; }
	//float GetDepth(void) { return CManager::FLT_ZERO; }
	int GetModelIdx(void) { return -1; }

	//���O�i�K�v�Ȃ��j
	void Exclusion(void){}

private:
	Particle m_particle;	//�p�[�e�B�N���\����
};

#endif	//���d