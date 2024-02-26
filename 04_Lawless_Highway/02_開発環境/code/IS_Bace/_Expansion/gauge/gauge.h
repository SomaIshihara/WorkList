//======================================================
//
//ゲージ処理[gauge.h]
//Author:石原颯馬
//
//======================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "../../_Core/_object/object_empty/object.h"

class CObject2D;

//******************************************************************
// ゲージクラス
//******************************************************************
class CGauge : public CObject
{
public:
	//コンストラクタ・デストラクタ
	CGauge(int nPriority = PRIORITY_05);	//デフォルト
	virtual ~CGauge();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//オブジェクトを生成
	static CGauge* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight);

	//取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	float GetRate(void) { return m_fGaugeRate; }

	//設定
	void SetPos(const D3DXVECTOR3 pos);
	void SetRot(const D3DXVECTOR3 rot);
	void AddRate(const float rate) { SetRate(m_fGaugeRate + rate); }
	void SetRate(const float rate);

	//除外（必要なし）
	void Exclusion(void){}
private:
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_defaultPos;	//基本位置
	D3DXVECTOR3 m_rot;	//向き
	float m_fGaugeRate;	//ゲージの割合
	float m_fDefaultWidth;

	//オブジェクト
	CObject2D* m_apObj[2];	//[0]:枠,[1]:ゲージ
};

#endif	//多重