//======================================================
//
//�i���o�[�����̃w�b�_[bg.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _PROGRESSBAR_H_
#define _PROGRESSBAR_H_
#include "main.h"
#include "manager.h"
#include "object.h"

class CObject2D;

class CProgressBar : public CObject
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CProgressBar(int nPriority = PRIORITY_BG);
	~CProgressBar();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CProgressBar* Create(const D3DXVECTOR3 pos, const float fWidth, const float fHeight);

	//�擾�i�������z�֐��̊֌W��������Ă��邪�A�����Ɉʒu���T�C�Y���͂���Ȃ��̂ł��ׂ�0��Ԃ��j
	D3DXVECTOR3 GetPos(void) { return CManager::VEC3_ZERO; }
	D3DXVECTOR3 GetRot(void) { return CManager::VEC3_ZERO; }
	float GetWidth(void) { return CManager::FLOAT_ZERO; }
	float GetHeight(void) { return CManager::FLOAT_ZERO; }
	float GetDepth(void) { return CManager::FLOAT_ZERO; }
	float GetParcent(void) { return m_fParcent; }

	//�ݒ�
	void SetPercent(const float fParcent);

private:
	CObject2D* m_pFrame;	//�g�i�������ŏ����p�j
	CObject2D* m_pBar;		//�σo�[
	float m_fParcent;		//�o�[�����i0.0f-1.0f�j
	float m_fDefWidth;		//�����̕�
};

#endif // !_PROGRESSBAR_H_