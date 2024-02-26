//======================================================
//
//ボタン処理(3D)のヘッダ[button3D.h]
//Author:石原颯馬
//
//======================================================
#ifndef _BUTTON_3D_H_	//多重インクルード対策
#define _BUTTON_3D_H_

#include "..\..\_Core\_object\object_3d\object3D.h"

//3Dボタンクラス
class CButton3D : public CObject3D
{
public:
	//コンストラクタ・デストラクタ
	CButton3D(int nPriority = PRIORITY_05);
	~CButton3D();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CButton3D* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight);

	//状態取得処理
	bool IsHold(void) { return m_bHold; }
	bool IsClickPress(void) { return m_bPress; }
	bool IsClickTrigger(void) { return m_bTrigger; }
	bool IsClickRelease(void) { return m_bRelease; }
	bool IsClickRepeate(void) { return m_bRepeate; }
private:
	bool m_bHold;				//かざしている
	bool m_bPress;				//プレス
	bool m_bTrigger;			//トリガー
	bool m_bRelease;			//リリース
	bool m_bRepeate;			//リピート
};

#endif	//多重
