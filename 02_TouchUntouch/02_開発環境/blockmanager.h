//======================================================
//
//ブロックマネージャのヘッダ[blockmanager.h]
//Author:石原颯馬
//
//======================================================
#ifndef _BLOCKMANAGER_H_
#define _BLOCKMANAGER_H_

#include "object.h"
#include "switch.h"
#include "interface.h"

//前方宣言
class CSwitchManager;
class CXModel;

class CBlockManager : public CObject
{
public:
	//コンストラクタ・デストラクタ
	CBlockManager(int nPriority = PRIORITY_04);
	~CBlockManager();

	//生成
	static CBlockManager* Create(CSwitchManager* pSwitchManager, IControllStat* iControllStat);

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//除外（必要なし）
	void Exclusion(void){}

private:
	CSwitchManager* m_pSwitchManager;	//スイッチマネ
	IControllStat* m_iControllStat;		//操作状態インターフェース

	//モデル
	static CXModel* m_pModelNor;		//通常のモデル
	static CXModel* m_pModelGimOff;		//ギミック類がオフの時用
};

#endif // !_SWITCHMANAGER_H_