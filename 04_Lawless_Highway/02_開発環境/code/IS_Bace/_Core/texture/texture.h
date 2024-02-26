//======================================================
//
//テクスチャ保存クラスのヘッダ[texture.h]
//Author:石原颯馬
//
//======================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#define MAX_STR		(256)
#define MAX_TEXTURE	(128)	//テクスチャ数

//テクスチャ保存クラス
class CTexture
{
public:
	//事前読み込みテクスチャ列挙
	enum PRELOAD
	{
		PRELOAD_00_TITLELOGO = 0,	//タイトルロゴ
		PRELOAD_01_PUSHANYBUTTON,	//何かボタン押せテキスト
		PRELOAD_02_TUTORIAL_TEXT_01,//チュートリアルテキスト
		PRELOAD_03_TUTORIAL_SKIP,	//チュートリアルスキップテキスト
		PRELOAD_04_TIMER_NUMBER,	//タイマーの数字
		PRELOAD_05_TIMER_SYMBOL,	//タイマーの記号
		PRELOAD_06_LATETIME_BEF,	//遅刻まで
		PRELOAD_07_LATETIME_AFT,	//遅刻から
		PRELOAD_08_PAUSE_TEXT,		//ポーズテキスト
		PRELOAD_09_PAUSE_CONTINUE,	//ポーズの続ける
		PRELOAD_10_PAUSE_RESTART,	//ポーズのリスタート
		PRELOAD_11_PAUSE_RETURN,	//ポーズの帰る
		PRELOAD_12_PAUSE_SCREENSHOT,//ポーズのスクショ
		PRELOAD_13_RESULT_SUCCESS,	//リザルトの成功テキスト
		PRELOAD_14_RESULT_FAILURE,	//リザルトの遅刻テキスト
		PRELOAD_15_RANKING_TEXT,	//ランキングテキスト
		PRELOAD_16_1ST,				//1位
		PRELOAD_17_2ND,				//2位
		PRELOAD_18_3RD,				//3位
		PRELOAD_19_4TH,				//4位
		PRELOAD_20_5TH,				//5位
		PRELOAD_21_ROAD,			//道路
		PRELOAD_22_GOAL,			//ゴール
		PRELOAD_23_CONFIG_KB,
		PRELOAD_24_CONFIG_GP,
		PRELOAD_25_EFFECT_SMOKE,
		PRELOAD_26_EFFECT_FIRE,
		PRELOAD_27_TUTORIAL_01_KB,	//チュートリアルテキスト01
		PRELOAD_28_TUTORIAL_01_GP,
		PRELOAD_29_TUTORIAL_02_KB,	//チュートリアルテキスト02
		PRELOAD_30_TUTORIAL_02_GP,
		PRELOAD_31_TUTORIAL_03_KB,	//チュートリアルテキスト03
		PRELOAD_32_TUTORIAL_03_GP,
		PRELOAD_33_TUTORIAL_04,		//チュートリアルテキスト04
		PRELOAD_34_FIELD_LEAF,		//地面用草
		PRELOAD_35_SPEEDMETER_01,	//スピードメーターの枠
		PRELOAD_36_SPEEDMETER_02,	//スピードメーターの針
		PRELOAD_MAX
	};

	//パターンテクスチャ構造体定義
	typedef struct
	{
		LPDIRECT3DTEXTURE9 pTexture;	//テクスチャポインタ
		int nPatternWidth;				//パターン幅
		int nPatternHeight;				//パターン高さ
	} PatternTexture;
	//コンストラクタ・デストラクタ
	CTexture();
	~CTexture();

	//全読み込み・破棄
	HRESULT Load(const char* pPath);	//あらかじめ読み込みたいテクスチャ読み込み
	void Unload(void);					//追加した分も含めてすべて破棄

	int Regist(const char* pPath, const int nPatWidth = 1, const int nPatHeight = 1);	//追加する分の読み込み
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);											//テクスチャ取得
	int GetPatWidth(int nIdx);					//パターン幅取得
	int GetPatHeight(int nIdx);					//パターン高さ取得

private:
	PatternTexture m_apTexture[MAX_TEXTURE];		//テクスチャポインタ
	char m_aFilepath[MAX_TEXTURE][MAX_STR];			//テクスチャパス
	static int m_nNumAll;							//テクスチャ総数
};

#endif // !_TEXTURE_H_
