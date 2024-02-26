//======================================================
//
//モデルキャラ処理[chara.h]
//Author:石原颯馬
//
//======================================================
#ifndef _CHARA_H_
#define _CHARA_H_

#include "../_object/object_empty/object.h"

//前方宣言
class CModel;
class CMotion;

//モデルキャラクラス
class CChara : public CObject
{
public:
	//モーション種類
	enum class MOTIONTYPE
	{
		MOTIONTYPE_NEUTRAL = 0,
		MOTIONTYPE_MOVE,
		MOTIONTYPE_ACTION,	//未実装
		MOTIONTYPE_JUMP,
		MOTIONTYPE_LAND,
	};

	//コンストラクタ・デストラクタ
	CChara(int nPriority = CObject::PRIORITY_DEFAULT);
	~CChara();

	//基本処理
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	//生成
	static CChara* Create(const char* pPath, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	//取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	MOTIONTYPE GetMotion(void);

	//設定
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	virtual void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
	void SetMotion(MOTIONTYPE type);
	HRESULT SetupModel(const char* pPath);

	//除外
	virtual void Exclusion(void) {}

private:
	//位置類
	D3DXVECTOR3 m_pos;			//位置
	D3DXVECTOR3 m_rot;			//向き
	D3DXMATRIX m_mtxWorld;		//ワールドマトリ
	CModel** m_ppModel;			//モデル（動的確保）
	CMotion* m_pMotion;			//モーションポインタ
	int m_nNumModel;			//モデル数
};

#endif // !_CHARA_H_
