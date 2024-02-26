//======================================================
//
//背景（2D）処理のヘッダ[bg.h]
//Author:石原颯馬
//
//======================================================
#ifndef _BG_H_	//多重インクルード対策
#define _BG_H_
#include "..\..\_Core\_object\object_2d\object2D.h"

class CBG : public CObject2D
{
public:
	//コンストラクタ・デストラクタ
	CBG(int nPriority = PRIORITY_BG);
	~CBG();

	//生成
	static CBG* Create(const int nPriority = PRIORITY_BG);

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nIdxTexture;	//テクスチャ番号
};

#endif	//多重