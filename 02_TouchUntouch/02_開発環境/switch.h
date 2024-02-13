//======================================================
//
//スイッチ処理のヘッダ[switch.h]
//Author:石原颯馬
//
//======================================================
#ifndef _SWITCH_H_
#define _SWITCH_H_

//必要なのインクルード
#include "object.h"

//前方宣言
class CObjectX;
class CXModel;

//キャラクタークラス
class CSwitch : public CObject
{
public:
	//静的const
	static const float MOVE_DEF_HEIGHT;

	//当たり判定用float3つ
	struct ColFloat
	{
		float* pPosMain, pPosSubA, pPosSubB;
		float fSizeMain, fSizeSubA, fSizeSubB;
	};

	//スイッチタイプ列挙
	enum TYPE
	{
		TYPE_A = 0,		//紫
		TYPE_B,			//黄色
		TYPE_GOAL_A,	//ゴール（タイプA）
		TYPE_GOAL_B,	//ゴール（タイプB）
		TYPE_MAX
	};

	//コンストラクタ・デストラクタ
	CSwitch(int nPriority = PRIORITY_DEFAULT);
	~CSwitch();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CSwitch* Create(const D3DXVECTOR3 pos, const TYPE type);

	//取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	static CSwitch* GetTop(void) { return m_pTop; }
	CSwitch* GetNext(void) { return m_pNext; }
	CObjectX* GetBase(void) { return m_pObjBase; }
	CObjectX* GetMove(void) { return m_pObjMove; }
	bool IsPush(void) { return m_bPush; }
	TYPE GetType(void) { return m_type; }

	//設定
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }

	//除外
	void Exclusion(void);

	//スイッチを押す
	void Push(void) { m_bPush = true; }	//キャラが使う押す操作
	void Pull(void) { m_bPush = false; }//スイッチマネが使う引っ張る操作

private:
	//モデル
	static CXModel* m_pModelBase;	//土台のモデルポインタ
	static CXModel* m_pModelMove;	//可動部のモデルポインタ

	//リスト
	static CSwitch* m_pTop;	//リストの最初
	static CSwitch* m_pCur;	//リストの終端
	CSwitch* m_pNext;		//次
	CSwitch* m_pPrev;		//前
	static int m_nNumAll;	//スイッチ総数

	D3DXMATRIX m_mtxWorld;			//ワールドマトリ
	CObjectX* m_pObjBase;			//土台のオブジェクトポインタ
	CObjectX* m_pObjMove;			//可動部のオブジェクトポインタ

	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_move;				//移動量
	D3DXVECTOR3 m_rot;				//向き
	float m_fWidth, m_fHeight, m_fDepth;	//サイズ

	TYPE m_type;	//スイッチタイプ（機能に差異なし）
	bool m_bPush;	//スイッチが押されているか
};

#endif // !_CHARACTER_H_
