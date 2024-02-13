//======================================================
//
//エフェクト処理(ビルボード)のヘッダ[effectBillboard.h]
//Author:石原颯馬
//
//======================================================
#ifndef _EFFECT_BILLBOARD_H_	//多重インクルード対策
#define _EFFECT_BILLBOARD_H_

#include "objectBillboard.h"

//優先順位
#define EFFECT_PRIORITY	(4)

//========================================
//ビルボードエフェクト
//========================================
class CEffectBillboard : public CObjectBillboard
{
public:
	//エフェクト構造体定義
	typedef struct
	{
		D3DXVECTOR3 move;	//移動量
		D3DXCOLOR col;		//色
		int nLife;			//寿命
	} Effect;

	//コンストラクタ・デストラクタ
	CEffectBillboard(const int nLife, int nPriority = EFFECT_PRIORITY);			//デフォルト
	CEffectBillboard(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fWidth, const float fHeight,
		const D3DXCOLOR col, const int nLife, int nPriority = EFFECT_PRIORITY);		//オーバーロード（エフェクトいろいろ設定可）
	~CEffectBillboard();

	//生成
	static CEffectBillboard* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fWidth, const float fHeight,
		const D3DXCOLOR col, const int nLife);

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nIdxTexture;		//テクスチャ番号
	Effect m_effect;		//エフェクト構造体
	const int m_nDefLife;	//設定寿命
};

#endif	//多重