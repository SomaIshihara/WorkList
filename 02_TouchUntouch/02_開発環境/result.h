//======================================================
//
//リザルトシーンのヘッダ[result.h]
//Author:石原颯馬
//
//======================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//前方宣言
class CTimer;
class CScore;
class CObject2D;
class CFade;

//リザルトクラス
class CResult
{
public:
	//静的const
	static const int PLAYSOUND_COUNTER;	//音鳴らす間隔

	//コンストラクタ・デストラクタ
	CResult();
	~CResult();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CResult* Create(const int nTimer, const int nScore);

private:
	CTimer* m_pTimer;	//リザルト用タイマー
	CScore* m_pBonus;	//ボーナス用スコア（文字は投げっぱなし）
	CScore* m_pScore;	//最終スコア用スコア（文字は投げっぱなし）
	CObject2D* m_pPress;//遷移文字用オブジェ（接続で切替）
	CFade* m_pFade;		//フェードオブジェクト
	int m_nConter;		//音再生カウンター
};

#endif // !_RESULT_H_
