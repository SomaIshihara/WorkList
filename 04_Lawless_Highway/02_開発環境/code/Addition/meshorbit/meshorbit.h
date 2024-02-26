//======================================================
//
//メッシュ軌道処理[meshorbit.h]
//Author:石原颯馬
//
//======================================================
#ifndef _MESHORBIT_H_
#define _MESHORBIT_H_

#include "../../IS_Bace/_Expansion/meshfield/meshField.h"
#include "../../IS_Bace/_Core/utility/Utility_Vector.h"

//メッシュフィールドクラス
class CMeshOrbit : public CMeshField
{
public:
	//コンストラクタ・デストラクタ
	CMeshOrbit(int nPriority = CObject::PRIORITY_04);
	~CMeshOrbit();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CMeshOrbit* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fLength, const int nBlock);

	//設定
	void Push(const IS_Utility::Utility_Vector3 vec);
private:
	//関数
	void SetVtxBuff(void);

	//方向
	IS_Utility::Utility_Vector3* m_pVector;
};

#endif // !_MESHORBIT_H_
