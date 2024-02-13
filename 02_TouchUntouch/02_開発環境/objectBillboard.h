//======================================================
//
//オブジェクト（ビルボード）処理のヘッダ[objectBillboard.h]
//Author:石原颯馬
//
//======================================================
#ifndef _OBJECT_BILLBOARD_H_	//多重インクルード対策
#define _OBJECT_BILLBOARD_H_

#include "manager.h"
#include "object.h"

//オブジェクトクラス
class CObjectBillboard : public CObject
{
public:
	//コンストラクタ・デストラクタ
	CObjectBillboard(int nPriority = PRIORITY_DEFAULT);		//デフォルト
	virtual ~CObjectBillboard();

	//基本処理
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//生成
	static CObjectBillboard* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const int nIdxTexture);

	//テクスチャ設定
	void BindTexture(int nIdx) { m_nIdxTexture = nIdx; }

	//取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	float GetWidth(void) { return m_fWidth; }
	//float GetHeight(void) { return CManager::FLT_ZERO; }
	float GetDepth(void) { return m_fDepth; }

	//設定
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }	//位置
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; };	//向き
	HRESULT SetCol(const D3DXCOLOR col);	//色
	void SetSize(const float fWidth, const float fDepth);

	//除外
	virtual void Exclusion(void){}

private:
	int m_nIdxTexture;					//テクスチャ番号
	LPDIRECT3DVERTEXBUFFER9 m_pVtxbuff;	//頂点バッファ
	D3DXMATRIX m_mtxWorld;				//ワールドマトリ

	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_rot;	//向き
	float m_fWidth;		//幅(X)
	float m_fDepth;		//奥行(Z)
};

#endif	//多重