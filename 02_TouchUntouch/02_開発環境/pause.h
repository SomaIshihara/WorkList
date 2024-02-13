//======================================================
//
//ポーズ画面のヘッダ[game.h]
//Author:石原颯馬
//
//======================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

//前方宣言
class CObject2D;
class CBG;

//タイトルクラス
class CPause
{
public:
	//選択列挙
	enum MODE
	{
		MODE_RESUME = 0,
		MODE_RESTART,
		MODE_EXIT,
		MODE_SCREENSHOT,
		MODE_MAX
	};

	//コンストラクタ・デストラクタ
	CPause();
	~CPause();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	void Select(void);

	CBG* m_pBG;							//ちょっと暗くする背景
	CObject2D* m_pPauseStr;				//ポーズ文字
	CObject2D* m_apSelect[MODE_MAX];	//選択するやつ

	MODE m_mode;			//選択中モード
	bool m_bScreenShot;		//スクショ中か
	int m_aStickFrag[2];	//スティックがどちら側に倒されているか（XY両方格納）
};

#endif // !_GAME_H_
