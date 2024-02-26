//======================================================
//
//���b�V���O������[meshorbit.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _MESHORBIT_H_
#define _MESHORBIT_H_

#include "../../IS_Bace/_Expansion/meshfield/meshField.h"
#include "../../IS_Bace/_Core/utility/Utility_Vector.h"

//���b�V���t�B�[���h�N���X
class CMeshOrbit : public CMeshField
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CMeshOrbit(int nPriority = CObject::PRIORITY_04);
	~CMeshOrbit();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CMeshOrbit* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fLength, const int nBlock);

	//�ݒ�
	void Push(const IS_Utility::Utility_Vector3 vec);
private:
	//�֐�
	void SetVtxBuff(void);

	//����
	IS_Utility::Utility_Vector3* m_pVector;
};

#endif // !_MESHORBIT_H_
