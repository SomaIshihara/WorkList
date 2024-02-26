//==========================================================
//
// マップオブジェクト [object2DMap.h]
// Author : Soma Ishihara
//
//==========================================================
#ifndef _OBJECT_MAP_H_		// このマクロが定義されていない場合
#define _OBJECT_MAP_H_		// 二重インクルード防止用マクロを定義

#include "../../IS_Bace/_Core/_object/object_2d/object2D.h"

//==========================================================
// マップのクラス定義
//==========================================================
class CObject2DMap : public CObject2D
{
public:	// 誰でもアクセス可能

	//コンストラクタ・デストラクタ
	CObject2DMap(int nPriority = CObject::PRIORITY_DEFAULT);
	~CObject2DMap();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DrawTexture(void);
	void Load(void);		//デバイスロスト対策：ロスト解消したら呼び出してね。初期化にも使える。
	void UnLoad(void);		//デバイスロスト対策：ロストしたら呼び出してね。終了にも使える。

	//設定
	void SetCameraPosR(const D3DXVECTOR3 pos) { m_posR = pos; }
	void SetCameraPosV(const D3DXVECTOR3 pos) { m_posV = pos; }

	//生成
	static CObject2DMap *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight);
private:	// 自分だけがアクセス可能
	LPDIRECT3DTEXTURE9 m_pTextureMap;	//マップテクスチャ
	LPDIRECT3DSURFACE9 m_pZSurface;		// テクスチャの深度バッファ
	D3DXVECTOR3 m_posR, m_posV;
};

#endif

