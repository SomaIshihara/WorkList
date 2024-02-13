//======================================================
//
//影の処理のヘッダ[shadow.h]
//Author:石原颯馬
//
//======================================================
#ifndef _SHADOW_H_	//多重インクルード対策
#define _SHADOW_H_

//必要なもののインクルード
#include "object3D.h"
#include "character.h"

//影クラス
class CShadow : public CObject3D
{
public:
	//コンストラクタ・デストラクタ
	CShadow(int nPriority = CObject::PRIORITY_04);
	~CShadow();

	//基本処理
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//付与（生成）
	static CShadow* Create(void);

	//破棄
	void Release(void);

	//設定
	void Set(D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const CCharacter::TYPE type);

	//除外
	void Exclusion(void) { CObject3D::Exclusion(); }

private:
	float ConpareLength(const float fNear, const float fLength);

	int m_nIdxTexture;	//テクスチャ番号
};

#endif	//多重