//======================================================
//
//���b�V�����H����[meshroad.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _MESHROAD_H_
#define _MESHROAD_H_

#include "../../IS_Bace/_Expansion/meshfield/meshField.h"
#include "../../IS_Bace/_Core/utility/Utility_Vector.h"
#include <vector>

//���b�V���t�B�[���h�N���X
class CMeshRoad : public CMeshField
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CMeshRoad();
	~CMeshRoad();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CMeshRoad* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fLength, 
		const std::vector<D3DXVECTOR3>& vVector);
	static CMeshRoad* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fLength,
		const std::vector<IS_Utility::Utility_Vector3>& vVector);

	//�������c
	float GetHeight(D3DXVECTOR3 posOld, D3DXVECTOR3 posNew);
	static float GetHeightAll(D3DXVECTOR3 posOld, D3DXVECTOR3 posNew);
	D3DXVECTOR3 GetPirotRot(D3DXVECTOR3 posOld, D3DXVECTOR3 posLanding);
	static D3DXVECTOR3 GetPirotRotAll(D3DXVECTOR3 posOld, D3DXVECTOR3 posLanding);

	//�擾
	static CMeshRoad* GetTop(void) { return m_pTop; }
	CMeshRoad* GetNext(void) { return m_pNext; }

	//���O
	void Exclusion(void);
private:
	//�֐�
	void SetVtxBuff(void);

	//�ʒu��
	std::vector<D3DXVECTOR3> m_vVector;

	//���X�g
	static CMeshRoad* m_pTop;	//�擪�I�u�W�F�N�g
	static CMeshRoad* m_pCur;	//�Ō���I�u�W�F�N�g
	CMeshRoad* m_pNext;			//���̃I�u�W�F�N�g
	CMeshRoad* m_pPrev;			//�O�̃I�u�W�F�N�g
	static int m_nNumAll;		//����
};

#endif // !_MESHROAD_H_
