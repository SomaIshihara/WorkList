//======================================================
//
//アイテム処理のヘッダ[item.h]
//Author:石原颯馬
//
//======================================================
#ifndef _ITEM_H_
#define _ITEM_H_
#include "objectX.h"
#include "interface.h"

//前方宣言
class CPictoTaxi;
class CXModel;

//アイテム弾クラス
class CItem : public CObjectX
{
public:
	//静的const
	static const int GET_SCORE;

	//コンストラクタ・デストラクタ
	CItem();
	~CItem();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CItem* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	//取得
	void Get(void);
	static CItem* GetTop(void) { return m_pTop; }
	CItem* GetNext(void) { return m_pNext; }

	//リスト除外
	void Exclusion(void);

	//スコアインターフェース設定
	static void SetScoreInterface(IScoreSetter* pInterface) { m_pScoreInterface = pInterface; }
	static void UnsetScoreInterface(void) { m_pScoreInterface = nullptr; }

private:
	//リスト
	static CItem* m_pTop;	//リストの最初
	static CItem* m_pCur;	//リストの終端
	CItem* m_pNext;			//次
	CItem* m_pPrev;			//前

	static int m_nNumAll;
	static IScoreSetter* m_pScoreInterface;

	int m_nScore;
};

#endif // !_BLOCK_H_
