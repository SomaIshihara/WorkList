//======================================================
//
//プレイヤー処理[player.h]
//Author:石原颯馬
//
//======================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//必要なのインクルード
#include "../../IS_Bace/_Core/chara/chara.h"
#include "../../IS_Bace/_Core/_object/object_empty/object.h"
#include "../../IS_Bace/_Core/charmodel/model.h"
#include "../../IS_Bace/_Core/charmotion/motion.h"
#include "../../IS_Bace/_Core/interface.h"

//前方宣言
class CBoxCollider;
class CImgController;
class CObject3D;
class CGauge;
class CObject2DMap;
class CSpeedMeter;
class CSmoke;

//キャラクタークラス
class CPlayer : public CChara, public ICollisionReader
{
public:
	enum class STATE
	{
		STATE_GAME,			//ゲーム時
		STATE_TUTORIAL,		//チュートリアル時
		STATE_SYSTEM_START,	//スタート前自動操作
		STATE_SYSTEM_GOAL,	//ゴール時自動操作
	};

	//コンストラクタ・デストラクタ
	CPlayer(int nPriority = CObject::PRIORITY_04);
	~CPlayer();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CPlayer* Create(const D3DXVECTOR3 pos, CGauge* pGauge, CObject2DMap* pMap, CSpeedMeter* pSpeedMeter);

	//取得
	D3DXVECTOR3 GetMove(void) { return m_move; }
	CBoxCollider* GetCollider(void) { return m_pCollider; }
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	float GetDepth(void) { return m_fDepth; }
	CObject* GetObj(void) { return this; }

	//設定
	void SetPos(const D3DXVECTOR3 pos) { CChara::SetPos(pos); }
	void SetRot(const D3DXVECTOR3 rot);
	void SetState(const STATE state) { m_state = state; }
	void SetController(CImgController* pController);

	//除外
	void Exclusion(void) { CChara::Exclusion(); }

private:
	void Control(D3DXVECTOR3 &pos);
	void AutoControll(D3DXVECTOR3& pos);
	void SetBoostFire(D3DXVECTOR3& pos);
	void SetSmokePos(D3DXVECTOR3& pos);
	void SetSmokeAlpha(float fAdd);

	CImgController* m_pController;
	STATE m_state;
	D3DXVECTOR3 m_posOld;			//前の位置
	D3DXVECTOR3 m_move;				//移動量
	D3DXVECTOR3 m_vecMove;			//移動方向ベクトル
	float m_fSpeed;					//速度
	float m_fSpeedLimit;			//最高速度
	float m_fWidth, m_fHeight, m_fDepth;	//サイズ
	CBoxCollider* m_pCollider;
	CSmoke* m_apDriftSmoke[2];
	CObject3D* m_pBoostFire;
	CGauge* m_pGauge;
	CObject2DMap* m_pMap;
	CSpeedMeter* m_pSpeedMeter;
	float m_fBoostFireAlpha;

	int m_nCounterJumpTime;			//ジャンプ時間
	bool m_bBoost;
	bool m_bDrift;
	float m_fHandleRot;
	float m_fDriftRot;
	float m_fSmokeAlpha;
};

#endif // !_Player_H_
