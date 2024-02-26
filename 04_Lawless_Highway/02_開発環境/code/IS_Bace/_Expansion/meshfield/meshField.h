//======================================================
//
//メッシュフィールド処理のヘッダ[meshField.h]
//Author:石原颯馬
//
//======================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "../../_Core/_object/object_empty/object.h"

//メッシュフィールドクラス
class CMeshField : public CObject
{
public:
	//コンストラクタ・デストラクタ
	CMeshField(int nPriority = CObject::PRIORITY_DEFAULT);
	~CMeshField();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CMeshField* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fDepth,
		const int nBlockWidth,const int nBlockDepth);

	//テクスチャ設定
	void BindTexture(int nIdx) { m_nIdxTexture = nIdx; }

	//取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	int GetIdxTexture(void) { return m_nIdxTexture; }
	static CMeshField* GetTop(void) { return m_pTop; }
	CMeshField* GetNext(void) { return m_pNext; }
	float GetWidth(void) { return m_fWidth; }
	float GetDepth(void) { return m_fDepth; }
	int GetBlockWidth(void) { return m_nBlockWidth; }
	int GetBlockDepth(void) { return m_nBlockDepth; }

	//設定
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetSize(const float fWidth, const float fDepth) { m_fWidth = fWidth; m_fDepth = fDepth; }
	void SetBlock(const int nWidth, const int nDepth) { m_nBlockWidth = nWidth; m_nBlockDepth = nDepth; }
	void SetCol(const D3DXCOLOR col) { m_color = col; SetVtxCol(); }

	//計算
	float GetHeight(D3DXVECTOR3 posOld, D3DXVECTOR3 posNew);
	D3DXVECTOR3 GetLandingRot(D3DXVECTOR3 posOld, D3DXVECTOR3 posLanding, float rotY);
	static float GetHeightAll(D3DXVECTOR3 posOld, D3DXVECTOR3 posNew);
	static D3DXVECTOR3 GetLandingRotAll(D3DXVECTOR3 posOld, D3DXVECTOR3 posLanding, float rotY);
	bool GetLanding(D3DXVECTOR3 posOld, D3DXVECTOR3 poslanding, D3DXVECTOR3* pOutposVtx, D3DXVECTOR3* pOutNor, D3DXVECTOR3* pOutUpVec = nullptr);

	//除外
	virtual void Exclusion(void);
protected:
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxbuff; }

private:
	//関数
	void CreateBuff(void);
	void ReleaseBuff(void);
	void SetVtxBuff(void);
	void SetVtxPos(void);
	void SetVtxCol(void);
	void SetVtxTex(void);
	void SetVtxNor(void);
	void SetIdxBuff(void);
	WORD* SetIdxSwaingField(int nCntWidth, WORD *pIdx);

	//変数
	int m_nIdxTexture;					//テクスチャ番号
	LPDIRECT3DVERTEXBUFFER9 m_pVtxbuff;	//頂点バッファ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//インデックスバッファ
	D3DXMATRIX m_mtxWorld;				//ワールドマトリ

	//位置類
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_rot;	//向き
	float m_fWidth;		//幅
	float m_fDepth;		//奥行
	int m_nBlockWidth;	//ブロック幅
	int m_nBlockDepth;	//ブロック奥行
	D3DXCOLOR m_color;	//頂点カラー

	//リスト
	static CMeshField* m_pTop;	//先頭オブジェクト
	static CMeshField* m_pCur;	//最後尾オブジェクト
	CMeshField* m_pNext;		//次のオブジェクト
	CMeshField* m_pPrev;		//前のオブジェクト
	static int m_nNumAll;		//総数
};

#endif // !_MESHFIELD_H_
