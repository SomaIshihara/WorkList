//======================================================
//
//数字処理のヘッダ[number.h]
//Author:石原颯馬
//
//======================================================
#ifndef _NUMBER_H_	//多重インクルード対策
#define _NUMBER_H_

#include "..\..\_Core\_object\object_2d\object2D.h"

class CNumber : public CObject2D
{
public:
	//コンストラクタ・デストラクタ
	CNumber(int nPriority = PRIORITY_05);	//デフォルト
	~CNumber();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//設定
	void SetNumber(const int nSource, const int nDigit);	//もととなる数字と桁数を入れると分割してくれる

	//テクスチャ設定
	void BindTexture(int nIdx);

	//生成
	static CNumber* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight);

private:
	
};

#endif	//多重