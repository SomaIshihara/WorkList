//======================================================
//
//���������̃w�b�_[building.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "main.h"
#include "objectX.h"

//�O���錾
class CXModel;

//�����N���X
class CBuilding : public CObject
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CBuilding();
	CBuilding(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, CXModel* pModel);
	~CBuilding();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CBuilding* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, CXModel* pModel);

	//�擾
	static CBuilding* GetBuilding(int nIdx) { return m_apBuilding[nIdx]; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	float GetDepth(void) { return m_fDepth; }
	CXModel* GetModel(void) { return m_pModel; }
	int GetEndurance(void) { return m_nEndurance; }
	static int GetNumAll(void) { return m_nNumAll; }
	bool GetUnique(void) { return m_bUnique; }
	int GetLv(void) { return m_nLv; }
	float GetSigValue(void) { return m_fSigValue; }
	int GetPowValue(void) { return m_nPowValue; }
	float GetSigEndurance(void) { return m_fSigEndurance; }
	int GetPowEndurance(void) { return m_nPowEndurance; }
	int GetExp(void) { return m_nExp; }

	//�ݒ�
	void SetUnique(const bool bFrag) { m_bUnique = bFrag; }
	void SetLv(const int nLv);
	void SetSigValue(const float fSignificant) { m_fSigValue = fSignificant; }
	void SetPowValue(const int nPower) { m_nPowValue = nPower; }
	void SetSigEndurance(const float fSignificant);
	void SetPowEndurance(const int nPower);
	void SetExp(const int nExp) { m_nExp = nExp; }

	//�_���[�W�t�^
	void AddDamage(int nDamage);

private:
	void CulcEndurance(void);

	static CBuilding* m_apBuilding[MAX_OBJ];
	static int m_nNumAll;			//�����N���X���ł̌�
	int m_nID;						//�����N���X���ł�ID
	int m_nEndurance;				//�ϋv�l
	D3DXMATRIX mtxWorld;			//���[���h�}�g��
	CXModel* m_pModel;				//���f���|�C���^

	//�ʒu��
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
	float m_fWidth;		//��(X)
	float m_fHeight;	//����(Y)
	float m_fDepth;		//���s(Z)

	//�p�����[�^(m_bBreakable == true)
	bool m_bUnique;			//�ʐݒ�L��
	int m_nLv;				//���x��
	//��m_bUnique == true
	float m_fSigValue;		//���l�L������
	int m_nPowValue;		//���l�ׂ���
	float m_fSigEndurance;	//�ϋv�L������
	int m_nPowEndurance;	//�ϋv�ׂ���
	int m_nExp;				//�o���l

	//������
	float m_fRedAlpha;	//�_���[�W��H��������̐ԐF�
};

#endif // !_BUILDING_H_
