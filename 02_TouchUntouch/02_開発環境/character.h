//======================================================
//
//キャラクター処理のヘッダ[character.h]
//Author:石原颯馬
//
//======================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//必要なのインクルード
#include "object.h"
#include "interface.h"

//前方宣言
class CModel;
class CShadow;
class CMotion;
class CBoxCollider;
class CObject3D;

//キャラクタークラス
class CCharacter : public CObject, public ICollisionReader
{
public:
	//静的const
	static const float CHARA_SPEED;				//移動速度
	static const float CHARA_JUMP_POW;			//ジャンプ力
	static const float CHARA_RESPAWN_HEIGHT;	//リスポーン判定の高さ

	//当たり判定用float3つ
	struct ColFloat
	{
		float* pPosMain, pPosSubA, pPosSubB;
		float fSizeMain, fSizeSubA, fSizeSubB;
	};

	//キャラクタータイプ列挙
	enum TYPE
	{
		TYPE_A = 0,
		TYPE_B,
		TYPE_MAX
	};

	//モーション種類
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,
		MOTIONTYPE_MOVE,
		MOTIONTYPE_ACTION,	//未実装
		MOTIONTYPE_JUMP,
		MOTIONTYPE_LAND,
	} MOTIONTYPE;

	//コンストラクタ・デストラクタ
	CCharacter(int nPriority = CObject::PRIORITY_02);
	~CCharacter();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//生成
	static CCharacter* Create(const D3DXVECTOR3 pos ,const TYPE type, IControllStat* player);

	//取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	static CCharacter** GetChara(void) { return &m_aChara[0]; }

	//設定
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }

	//除外（必要なし）
	void Exclusion(void){}

	//インターフェース実装
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	float GetDepth(void) { return m_fDepth; }
	CObject* GetObj(void) { return this; }

private:
	void SetModel(void);

	static CCharacter* m_aChara[TYPE_MAX];	//種類別のキャラポインタ

	D3DXMATRIX m_mtxWorld;			//ワールドマトリ
	CModel** m_ppModel;				//モデル（動的確保）
	int m_nNumModel;				//モデル数
	CMotion* m_pMotion;				//モーションポインタ
	CShadow* m_pShadow;				//影
	CObject3D* m_pPoint;			//操作中表示

	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_posOld;			//前の位置
	D3DXVECTOR3 m_posLastLanding;	//最後に着地した位置
	D3DXVECTOR3 m_move;				//移動量
	float m_fJumpPower;				//ジャンプ力
	D3DXVECTOR3 m_rot;				//向き
	float m_fWidth, m_fHeight, m_fDepth;	//サイズ

	bool m_bJump;					//ジャンプ中か
	int m_nCounterJumpTime;			//ジャンプ時間

	//CShadow* m_pShadow;				//影オブジェクトポインタ
	TYPE m_type;					//種類
	CBoxCollider* m_pCollider;		//当たり判定

	IControllStat* m_controllInterface;	//操作状況のインターフェース
};

#endif // !_CHARACTER_H_
