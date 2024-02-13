//======================================================
//
//影の処理[shadow.cpp]
//Author:石原颯馬
//
//======================================================
#include "shadow.h"
#include "renderer.h"
#include "texture.h"
#include "block3D.h"
#include "switch.h"
#include "switchmanager.h"
#include "character.h"

//=================================
//コンストラクタ
//=================================
CShadow::CShadow(int nPriority) : CObject3D(nPriority)
{
	
}

//=================================
//デストラクタ
//=================================
CShadow::~CShadow()
{
}

//========================
//初期化処理
//========================
HRESULT CShadow::Init(void)
{
	//親処理
	CObject3D::Init();

	//テクスチャ読み込み
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\effect000.jpg");

	CObject3D::SetPos(CManager::VEC3_ZERO);	//位置設定
	CObject3D::SetRot(CManager::VEC3_ZERO);	//向き設定
	CObject3D::SetSize(50.0f, 50.0f);		//サイズ設定

	//できた
	return S_OK;
}

//========================
//終了処理
//========================
void CShadow::Uninit(void)
{
	//親処理
	CObject3D::Uninit();
}

//========================
//更新処理
//========================
void CShadow::Update(void)
{
	//親処理
	CObject3D::Update();
}

//========================
//描画処理
//========================
void CShadow::Draw(void)
{
	//レンダラ取得
	CRenderer* pRenderer = CManager::GetInstance()->GetRenderer();

	//ブレンディング種類を加算合成に変更
	pRenderer->SetBlendType(CRenderer::BLENDTYPE_SUB);

	//Zテスト無効化
	pRenderer->SetEnableZTest(false);

	//親処理
	CObject3D::Draw();

	//Zテスト有効化
	pRenderer->SetEnableZTest(true);

	//ブレンディング種類を通常状態に戻す
	pRenderer->SetBlendType(CRenderer::BLENDTYPE_NORMAL);
}

//========================
//生成処理
//========================
CShadow* CShadow::Create(void)
{
	CShadow* pShadow = nullptr;

	if (pShadow == nullptr)
	{
		//オブジェクト2Dの生成
		pShadow = new CShadow();

		//初期化
		pShadow->Init();

		//テクスチャ設定
		pShadow->BindTexture(pShadow->m_nIdxTexture);

		return pShadow;
	}
	else
	{
		return nullptr;
	}
}

//========================
//破棄処理
//========================
void CShadow::Release(void)
{
	CObject3D::Release();
}

//========================
//位置向き設定処理
//========================
void CShadow::Set(D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const CCharacter::TYPE type)
{
	//高さ調整（ブロックとスイッチのみ測定）
	float fLengthNear = FLT_MAX;

	//ブロック
	CBlock3D* pBlock = CBlock3D::GetTop();

	while (pBlock != nullptr)
	{
		D3DXVECTOR3 posBlock = pBlock->GetPos();
		float fWidthBlockHalf = pBlock->GetWidth() * 0.5f;
		float fDepthBlockHalf = pBlock->GetDepth() * 0.5f;

		if (pos.x <= posBlock.x + fWidthBlockHalf && pos.x >= posBlock.x - fWidthBlockHalf &&
			pos.z <= posBlock.z + fDepthBlockHalf && pos.z >= posBlock.z - fDepthBlockHalf)
		{//ブロックの真上にいる
			//ブロックの種類が通常かonのギミック類
			CBlock3D::TYPE blocktype = pBlock->GetType();
			if (blocktype == CBlock3D::TYPE_NORMAL)
			{//通常
				float fHeightBlockHalf = pBlock->GetHeight() * 0.5f;
				float fLength = pos.y - posBlock.y - fHeightBlockHalf;

				fLengthNear = ConpareLength(fLengthNear, fLength);
			}
			else if (blocktype == CBlock3D::TYPE_GIMMICK_01 || blocktype == CBlock3D::TYPE_GIMMICK_02)
			{//ギミック
				if (CBlock3D::GetSwitchManager()->IsPush()[blocktype - CBlock3D::TYPE_GIMMICK_01] == true)
				{
					float fHeightBlockHalf = pBlock->GetHeight() * 0.5f;
					float fLength = pos.y - posBlock.y - fHeightBlockHalf;

					fLengthNear = ConpareLength(fLengthNear, fLength);
				}
			}
			else if (blocktype == CBlock3D::TYPE_A || blocktype == CBlock3D::TYPE_B)
			{//色
				if (type == blocktype)
				{
					float fHeightBlockHalf = pBlock->GetHeight() * 0.5f;
					float fLength = pos.y - posBlock.y - fHeightBlockHalf;

					fLengthNear = ConpareLength(fLengthNear, fLength);
				}
			}
		}

		pBlock = pBlock->GetNext();
	}

	//スイッチ
	CSwitch* pSwitch = CSwitch::GetTop();

	while (pSwitch != nullptr)
	{
		D3DXVECTOR3 posSwitch = pSwitch->GetPos();
		float fWidthSwitchHalf = pSwitch->GetMove()->GetWidth() * 0.5f;
		float fDepthSwitchHalf = pSwitch->GetMove()->GetDepth() * 0.5f;

		if (pos.x < posSwitch.x + fWidthSwitchHalf && pos.x > posSwitch.x - fWidthSwitchHalf &&
			pos.z < posSwitch.z + fDepthSwitchHalf && pos.z > posSwitch.z - fDepthSwitchHalf)
		{//ブロックの真上にいる
			float fHeightSwitchHalf = pSwitch->GetMove()->GetHeight() * 0.5f;
			float fLength = pos.y - posSwitch.y + fHeightSwitchHalf;

			if (fLength >= 0.0f && fLengthNear > fLength)
			{
				fLengthNear = fLength;	//最短距離入れる
			}
		}

		pSwitch = pSwitch->GetNext();
	}

	//調整
	pos.y -= fLengthNear;

	//位置向き設定
	SetPos(pos);
	SetRot(rot);
}

//========================
//長さ比較
//========================
float CShadow::ConpareLength(const float fNear, const float fLength)
{
	if (fLength >= 0.0f && fNear > fLength)
	{
		return fLength;
	}
	else
	{
		return fNear;
	}
}
