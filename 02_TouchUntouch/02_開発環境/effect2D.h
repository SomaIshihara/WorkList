//======================================================
//
//エフェクト処理(2D)のヘッダ[effect2D.h]
//Author:石原颯馬
//
//======================================================
#ifndef _EFFECT_2D_H_	//多重インクルード対策
#define _EFFECT_2D_H_

#include "object2D.h"

//優先順位
#define EFFECT_PRIORITY	(4)

//========================================
//2Dエフェクト
//========================================
class CEffect2D : public CObject2D
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
	CEffect2D(const int nLife, int nPriority = EFFECT_PRIORITY);			//デフォルト
	~CEffect2D();

	//生成
	static CEffect2D* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fWidth, const float fHeight,
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