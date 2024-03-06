//======================================================
//
//スタート文字処理[starttext.h]
//Author:石原颯馬
//
//======================================================
#ifndef _STARTTEXT_H_
#define _STARTTEXT_H_

#include "../../IS_Bace/_Core/_object/object_2d/object2D.h"

//前方宣言
class CObject2D;

//メッシュフィールドクラス
class CStartText : public CObject2D
{
public:
	//コンストラクタ・デストラクタ
	CStartText();
	~CStartText();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CStartText* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight);

	//設定
	void SetLitParam(const int nDef, const int nDegree, const int nPercent);

	//除外
	void Exclusion(void){}
private:
	int m_nCounterUnLit;	//消灯カウンタ
	int m_nDefUnLitTime;	//消灯時間基本値
	int m_nDegUnLitTime;		//消灯時間ばらつき
	int m_nUnLitPercent;	//消灯確率
};

#endif // !_MESHROAD_H_
