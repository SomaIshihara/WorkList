//======================================================
//
//煙処理[smoke.h]
//Author:石原颯馬
//
//======================================================
#ifndef _SMOKE_H_
#define _SMOKE_H_

#include "../../IS_Bace/_Core/_object/object_billboard/objectBillboard.h"

//メッシュフィールドクラス
class CSmoke : public CObjectBillboard
{
public:
	//コンストラクタ・デストラクタ
	CSmoke(int nAnimSpeed = 1);
	~CSmoke();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CSmoke* Create(const D3DXVECTOR3 pos, const float fRadius, const int nAnimSpeed);

	//除外
	void Exclusion(void){}
private:
	int m_nCounter;
	int m_nPattern;
	const int m_nAnimSpeed;
};

#endif // !_MESHROAD_H_
