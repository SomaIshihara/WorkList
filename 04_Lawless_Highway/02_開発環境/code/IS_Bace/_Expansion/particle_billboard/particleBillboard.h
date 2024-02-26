//======================================================
//
//�p�[�e�B�N��(�r���{�[�h)�����̃w�b�_[particleBillboard.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _PARTICLE_BILLBOARD_H_
#define _PARTICLE_BILLBOARD_H_

#include "..\..\_Core\manager\manager.h"
#include "..\..\_Core\_object\object_empty\object.h"
#include "..\..\_Core\utility\Utility.h"

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

	//�ݒ�
	void BindTexture(const int nIdx) { m_nIdxTexture = nIdx; }
	void SetPos(const D3DXVECTOR3 pos) { m_particle.pos = pos; }
	void SetLife(const int nLife) { m_particle.nLife = nLife; }

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_particle.pos; }

	//���O�i�K�v�Ȃ��j
	void Exclusion(void){}

private:
	Particle m_particle;	//�p�[�e�B�N���\����
	int m_nIdxTexture;		//�e�N�X�`���ԍ�
};

#endif	//���d