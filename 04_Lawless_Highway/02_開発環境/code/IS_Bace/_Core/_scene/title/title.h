//======================================================
//
//タイトルシーンのヘッダ[title.h]
//Author:石原颯馬
//
//======================================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "..\..\manager\manager.h"

//前方宣言
class CFade;

//タイトルクラス
class CTitle : public CScene
{
public:
	//コンストラクタ・デストラクタ
	CTitle();
	~CTitle();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CFade* m_pFade;			//フェードオブジェクト
};

#endif // !_TITLE_H_
