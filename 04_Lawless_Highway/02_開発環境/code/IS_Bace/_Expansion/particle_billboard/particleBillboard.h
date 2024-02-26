//======================================================
//
//パーティクル(ビルボード)処理のヘッダ[particleBillboard.h]
//Author:石原颯馬
//
//======================================================
#ifndef _PARTICLE_BILLBOARD_H_
#define _PARTICLE_BILLBOARD_H_

#include "..\..\_Core\manager\manager.h"
#include "..\..\_Core\_object\object_empty\object.h"
#include "..\..\_Core\utility\Utility.h"

#define MAX_EFFECT	(1024)	//エフェクト最大個数

//========================================
//ビルボードパーティクル
//========================================
class CParticleBillboard : public CObject	//このクラスは管理オブジェクトです。Unityでいう空のオブジェクトみたいなもの。
{
public:
	//パーティクル構造体定義
	typedef struct
	{
		//パーティクル関係
		D3DXVECTOR3 pos;		//パーティクル放出位置
		int nLife;				//パーティクルの寿命
		int nEffeceNum;			//一度に出すエフェクト数
		float fSpeedBace;		//スピード基本値
		float fSpeedDegree;		//スピード振れ幅

		//エフェクト関係
		D3DXCOLOR col;			//エフェクトの色
		float fWidth;			//エフェクト1個の幅
		float fHeight;			//エフェクト1個の高さ
	} Particle;
	//コンストラクタ・デストラクタ
	CParticleBillboard();	//デフォルト
	~CParticleBillboard();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void) {}

	//生成
	static CParticleBillboard* Create(const D3DXVECTOR3 pos, const int nLife, const int nEffeceNum, const float fSpeedBace, const float fSpeedDegree,
		const D3DXCOLOR col, const float fWidth, const float fHeight);	//オブジェクトを生成

	//設定
	void BindTexture(const int nIdx) { m_nIdxTexture = nIdx; }
	void SetPos(const D3DXVECTOR3 pos) { m_particle.pos = pos; }
	void SetLife(const int nLife) { m_particle.nLife = nLife; }

	//取得
	D3DXVECTOR3 GetPos(void) { return m_particle.pos; }

	//除外（必要なし）
	void Exclusion(void){}

private:
	Particle m_particle;	//パーティクル構造体
	int m_nIdxTexture;		//テクスチャ番号
};

#endif	//多重