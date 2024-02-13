//======================================================
//
//スイッチマネージャのヘッダ[switchmanager.h]
//Author:石原颯馬
//
//======================================================
#ifndef _SWITCHMANAGER_H_
#define _SWITCHMANAGER_H_

#include "object.h"
#include "switch.h"

class CSwitchManager : public CObject
{
public:
	//コンストラクタ・デストラクタ
	CSwitchManager(int nPriority = PRIORITY_05);
	~CSwitchManager();

	//生成
	static CSwitchManager* Create(void);

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//取得
	bool* IsPush(void) { return &m_aPush[0]; }

	//リセット
	void Reset(void);

	//除外（必要なし）
	void Exclusion(void){}

private:
	bool m_aPush[CSwitch::TYPE_MAX];
};

#endif // !_SWITCHMANAGER_H_