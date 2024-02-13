//======================================================
//
//�X���C�_�[�����̃w�b�_[slider.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _SLIDER_H_
#define _SLIDER_H

#include "object.h"
#include "manager.h"

//�O���錾
class CObject2D;

//�X���C�_�[�N���X
class CSlider : public CObject
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CSlider();
	CSlider(const D3DXVECTOR3 pos,const float fOneWidth,const float fOneHeight, const int nIdxNum);
	~CSlider();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CSlider* Create(const D3DXVECTOR3 pos, const float fOneWidth, const float fOneHeight, const int nIdxNum);

	//�擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return CManager::VEC3_ZERO; }
	float GetWidth(void) { return m_fOneWidth * m_nIdxNum; }
	float GetHeight(void) { return m_fOneHeight; }
	float GetDepth(void) { return CManager::FLOAT_ZERO; }
	int GetModelIdx(void) { return CManager::INT_ZERO; }
	int GetSelectIdx(void) { return m_nSelect; }

	//�ݒ�
	void SetSelectIdx(int nIdx) { m_nSelect = (nIdx + m_nIdxNum) % m_nIdxNum; }

private:
	//�I�u�W�F�N�g
	CObject2D* m_pObjFrame;		//�g
	CObject2D* m_pObjMove;		//�ړ���
	CObject2D** m_ppObjIcon;	//�A�C�R���i���ρj

	//�l
	D3DXVECTOR3 m_pos;		//���S�ʒu
	float m_fOneWidth;		//1�g������̕�
	float m_fOneHeight;		//1�g������̍���
	int m_nIdxNum;			//�g��
	int m_nSelect;			//�I�𒆂̔ԍ�
	bool m_bClick;			//�N���b�N����
};

#endif // !_SLIDER_H_
