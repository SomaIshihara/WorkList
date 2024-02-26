//======================================================
//
//スピードメーター処理[speedmeter.h]
//Author:石原颯馬
//
//======================================================
#ifndef _SPEEDMETER_H_
#define _SPEEDMETER_H_

#include "../../IS_Bace/_Core/_object/object_empty/object.h"

//前方宣言
class CObject2D;

//メッシュフィールドクラス
class CSpeedMeter : public CObject
{
public:
	//コンストラクタ・デストラクタ
	CSpeedMeter();
	~CSpeedMeter();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//設定
	void SetPos(const D3DXVECTOR3 pos);
	void SetGauge(const float gauge);

	//生成
	static CSpeedMeter* Create(const D3DXVECTOR3 pos, const float fRadius);

	//除外
	void Exclusion(void){}
private:
	D3DXVECTOR3 m_pos;
	float m_fRadius;
	CObject2D* m_pObjFrame;
	CObject2D* m_pObjMeter;
};

#endif // !_MESHROAD_H_
