//======================================================
//
//ブロック処理(3D)のヘッダ[block3D.h]
//Author:石原颯馬
//
//======================================================
#ifndef _BLOCK_3D_H_
#define _BLOCK_3D_H_

//必要なものインクルード
#include "objectX.h"
#include "interface.h"

//前方宣言
class CBoxCollider;
class CSwitchManager;

//ブロッククラス
class CBlock3D : public CObjectX
{
public:
	//ブロック種類列挙
	enum TYPE
	{
		TYPE_NORMAL = 0,	//共通:通常（紫）
		TYPE_GIMMICK_01,	//共通:ギミック1（紫）
		TYPE_GIMMICK_02,	//共通:ギミック2（黄）
		TYPE_A,				//個別（ピンク）
		TYPE_B,				//個別（空色）
		TYPE_MAX
	};

	//コンストラクタ・デストラクタ
	CBlock3D(int nPriority = CObject::PRIORITY_04);
	~CBlock3D();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CBlock3D* Create(const D3DXVECTOR3 pos, const TYPE type);

	//リスト除外
	virtual void Exclusion(void);

	//取得
	static CBlock3D* GetTop(void) { return m_pTop; }
	CBlock3D* GetNext(void) { return m_pNext; }
	TYPE GetType(void) { return m_type; }
	static CSwitchManager* GetSwitchManager(void) { return m_pSwitchManager; }

	//設定
	static void SetSwitchManager(CSwitchManager* pManager) { m_pSwitchManager = pManager; }

private:
	//リスト
	static CBlock3D* m_pTop;	//リストの最初
	static CBlock3D* m_pCur;	//リストの終端
	CBlock3D* m_pNext;			//次
	CBlock3D* m_pPrev;			//前

	//個数
	static int m_nNumAll;

	//パラメータ
	TYPE m_type;	//ブロック種類
	static CSwitchManager* m_pSwitchManager;
};

#endif // !_BLOCK_3D_H_
