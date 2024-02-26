//======================================================
//
//メッシュ道路処理[meshroad.h]
//Author:石原颯馬
//
//======================================================
#ifndef _MESHROAD_H_
#define _MESHROAD_H_

#include "../../IS_Bace/_Expansion/meshfield/meshField.h"
#include "../../IS_Bace/_Core/utility/Utility_Vector.h"
#include <vector>

//メッシュフィールドクラス
class CMeshRoad : public CMeshField
{
public:
	//コンストラクタ・デストラクタ
	CMeshRoad();
	~CMeshRoad();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CMeshRoad* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fLength, 
		const std::vector<D3DXVECTOR3>& vVector);
	static CMeshRoad* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fLength,
		const std::vector<IS_Utility::Utility_Vector3>& vVector);

	//自動操縦
	float GetHeight(D3DXVECTOR3 posOld, D3DXVECTOR3 posNew);
	static float GetHeightAll(D3DXVECTOR3 posOld, D3DXVECTOR3 posNew);
	D3DXVECTOR3 GetPirotRot(D3DXVECTOR3 posOld, D3DXVECTOR3 posLanding);
	static D3DXVECTOR3 GetPirotRotAll(D3DXVECTOR3 posOld, D3DXVECTOR3 posLanding);

	//取得
	static CMeshRoad* GetTop(void) { return m_pTop; }
	CMeshRoad* GetNext(void) { return m_pNext; }

	//除外
	void Exclusion(void);
private:
	//関数
	void SetVtxBuff(void);

	//位置類
	std::vector<D3DXVECTOR3> m_vVector;

	//リスト
	static CMeshRoad* m_pTop;	//先頭オブジェクト
	static CMeshRoad* m_pCur;	//最後尾オブジェクト
	CMeshRoad* m_pNext;			//次のオブジェクト
	CMeshRoad* m_pPrev;			//前のオブジェクト
	static int m_nNumAll;		//総数
};

#endif // !_MESHROAD_H_
