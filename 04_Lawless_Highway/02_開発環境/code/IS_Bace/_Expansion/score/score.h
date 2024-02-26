//======================================================
//
//スコア処理のヘッダ[score.h]
//Author:石原颯馬
//
//======================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "..\..\_Core\_object\object_2d\object2D.h"

#define SCORE_DIGIT	(6)	//スコアの桁数

//前方宣言
class CNumber;

class CScore : public CObject
{
public:
	//コンストラクタ・デストラクタ
	CScore(int nPriority = PRIORITY_05);	//デフォルト
	~CScore();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CScore* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight);	//オブジェクトを生成(fOneWidth,fOneHeight:1桁当たりのサイズ)

	//取得（純粋仮想関数の関係上実装しているが、こいつにサイズやらはいらないのですべて0を返す）
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	int GetScore(void) { return m_nScore; }

	//設定
	void Set(const int nScore);	//スコア設定
	void Add(const int nAdd);	//スコア加算
	void BindTexture(const int nIdx);	//テクスチャ設定（数字オブジェクトすべてに適用）

	//除外（必要なし）
	void Exclusion(void){}

private:
	//関数
	void CutNumber(void);				//数字分割

	//変数
	CNumber* m_pNumber[SCORE_DIGIT];	//数字
	D3DXVECTOR3 m_pos;					//位置（1桁目の数字の中心を想定）
	D3DXVECTOR3 m_rot;					//向き（1桁目の数字の中心を想定）
	int m_nScore;						//スコア
};

#endif	//多重