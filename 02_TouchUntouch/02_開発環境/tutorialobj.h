//======================================================
//
//チュートリアル用オブジェ処理のヘッダ[tutorialobj.h]
//Author:石原颯馬
//
//======================================================
#ifndef _TUTORIALOBJ_H_
#define _TUTORIALOBJ_H_

//必要なのインクルード
#include "manager.h"
#include "object.h"
#include "interface.h"
#include "collision.h"

//前方宣言
class CObject3D;
class CObjectX;

//テレポート当たり判定クラス
class CTutorialObj : public CObject, public ICollisionReader
{
public:
	//コンストラクタ・デストラクタ
	CTutorialObj(int nPriority = CObject::PRIORITY_01);
	~CTutorialObj();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CTutorialObj* Create(const D3DXVECTOR3 pos, const int nNumber);

	//取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }	//当たり判定の位置
	static CTutorialObj* GetTop(void) { return m_pTop; }
	CTutorialObj* GetNext(void) { return m_pNext; }

	//インターフェース
	D3DXVECTOR3 GetMove(void) { return CManager::VEC3_ZERO; }
	D3DXVECTOR3 GetPosOld(void) { return m_pos; }
	void SetPos(const D3DXVECTOR3 pos) {}
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	float GetDepth(void) { return m_fDepth; }
	CObject* GetObj(void) { return this; }
	int GetNumber(void) { return m_nNumAll; }
	CObject3D* GetTutorialStr(void) { return m_pTutorial; }

	//除外
	void Exclusion(void);

	//表示
	void Popup(void) { m_bPopup = true; }//チュートリアルを表示

private:
	//リスト
	static CTutorialObj* m_pTop;	//リストの最初
	static CTutorialObj* m_pCur;	//リストの終端
	CTutorialObj* m_pNext;		//次
	CTutorialObj* m_pPrev;		//前
	static int m_nNumAll;				//テレポート当たり判定総数

	CBoxCollider* m_pCollider;			//当たり判定
	
	CObject3D* m_pTutorial;				//チュートリアル表示内容
	CObjectX* m_pObj;					//モデルオブジェ

	D3DXVECTOR3 m_pos;						//位置
	float m_fWidth, m_fHeight, m_fDepth;	//サイズ
	int m_nNumber;				//説明No.
	bool m_bPopup;				//表示するか
};

#endif // !_TUTORIALOBJ_H_
