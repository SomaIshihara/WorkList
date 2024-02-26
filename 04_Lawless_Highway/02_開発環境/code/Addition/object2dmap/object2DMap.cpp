//==========================================================
//
// マップオブジェクト [object2DMap.cpp]
// Author : Soma Ishihara
//
//==========================================================
#include "object2DMap.h"
#include "../../IS_Bace/_Core/manager/manager.h"
#include "../../IS_Bace/_Core/renderer/renderer.h"
#include "../../IS_Bace/_Core/utility/Utility.h"

//==========================================================
// コンストラクタ
//==========================================================
CObject2DMap::CObject2DMap(int nPriority) : CObject2D(nPriority)
{
	m_posR = IS_Utility::VEC3_ZERO;
	m_posV = IS_Utility::VEC3_ZERO;
	m_pTextureMap = nullptr;
	m_pZSurface = nullptr;
}

//==========================================================
// デストラクタ
//==========================================================
CObject2DMap::~CObject2DMap()
{

}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CObject2DMap::Init(void)
{
	CObject2D::Init();
	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CObject2DMap::Uninit(void)
{
	UnLoad();
	CObject2D::Uninit();
}

//==========================================================
// 更新処理
//==========================================================
void CObject2DMap::Update(void)
{
	CObject2D::Update();
	DrawTexture();
}

//==========================================================
// 描画処理
//==========================================================
void CObject2DMap::Draw(void)
{
	CObject2D::Draw(m_pTextureMap);
}

//===============================================
// テクスチャ描画処理
//===============================================
void CObject2DMap::DrawTexture(void)
{
	//デバイス
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//デバイスへのポインタ

	//描画用マトリ
	D3DXMATRIX mtxProj, mtxView, mtxViewPort;

	//バックバッファ用
	LPDIRECT3DSURFACE9 pOrgSurface;
	LPDIRECT3DSURFACE9 pOrgZBuffer;
	LPDIRECT3DSURFACE9 pTexSurface;

	//専用カメラ
	D3DXVECTOR3 vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//テクスチャサイズ
	float fWidth = GetWidth();
	float fHeight = GetHeight();

	//プロジェクションマトリの初期化
	D3DXMatrixIdentity(&mtxProj);

	D3DXMatrixPerspectiveFovLH(&mtxProj,
		D3DXToRadian(45.0f),
		(float)fWidth / (float)fHeight,
		10.0f,
		40000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProj);

	//ビューマトリの初期化
	D3DXMatrixIdentity(&mtxView);

	//ビューマトリの作成
	D3DXMatrixLookAtLH(&mtxView,
		&m_posV,
		&m_posR,
		&vecU);

	//ビューマトリの設定
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);

	//ビューポートマトリ設定
	D3DXMatrixIdentity(&mtxViewPort);
	mtxViewPort._11 = fWidth * 0.5f;
	mtxViewPort._22 = -fHeight * 0.5f;
	mtxViewPort._41 = fWidth * 0.5f;
	mtxViewPort._42 = fHeight * 0.5f;

	//テクスチャ
	//作成テクスチャ用インターフェース取得
	m_pTextureMap->GetSurfaceLevel(0, &pTexSurface);

	//バックバッファインターフェース取得
	pDevice->GetRenderTarget(0, &pOrgSurface);
	pDevice->GetDepthStencilSurface(&pOrgZBuffer);

	//レンダリングターゲットをテクスチャに変更
	pDevice->SetRenderTarget(0, pTexSurface);
	pDevice->SetDepthStencilSurface(m_pZSurface);

	//テクスチャクリア
	pDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	//テクスチャに描画
	if (SUCCEEDED(pDevice->BeginScene()))
	{// 描画が成功した場合

		// 3Dオブジェクトの描画
		CObject::DrawAll3D();

		// 描画終了
		pDevice->EndScene();
	}

	//戻す
	pDevice->SetRenderTarget(0, pOrgSurface);
	pDevice->SetDepthStencilSurface(pOrgZBuffer);

	pOrgSurface->Release();
	pOrgZBuffer->Release();
	pTexSurface->Release();
}

//===============================================
// テクスチャ生成処理
//===============================================
void CObject2DMap::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスへのポインタ

	//int型サイズ
	int nWidth = static_cast<int>(GetWidth());
	int nHeight = static_cast<int>(GetHeight());

	//各テクスチャ生成
	if (m_pTextureMap == nullptr)
	{
		D3DXCreateTexture(pDevice, nWidth, nHeight,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT, //こいつのためデバイスロスト時は破棄が必要
			&m_pTextureMap);
	}

	if (m_pZSurface == nullptr)
	{
		//共通Zバッファ生成
		pDevice->CreateDepthStencilSurface(
			nWidth, nHeight,
			D3DFMT_D16,
			D3DMULTISAMPLE_NONE,
			0, false,
			&m_pZSurface,
			nullptr);
	}
}

//===============================================
// テクスチャ開放処理
//===============================================
void CObject2DMap::UnLoad(void)
{
	if (m_pTextureMap != nullptr)
	{
		m_pTextureMap->Release();
		m_pTextureMap = nullptr;
	}
	if (m_pZSurface != nullptr)
	{
		m_pZSurface->Release();
		m_pZSurface = nullptr;
	}
}

//==========================================================
// 生成
//==========================================================
CObject2DMap *CObject2DMap::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight)
{
	CObject2DMap *pMap = nullptr;

	pMap = new CObject2DMap;

	if (pMap != nullptr)
	{
		// 初期化処理
		pMap->Init();
		pMap->SetPos(pos);
		pMap->SetRot(rot);
		pMap->SetSize(fWidth, fHeight);
		pMap->Load();
	}

	return pMap;
}