//==========================================
//
//カメラ関係プログラム[camera.cpp]
//Author:石原颯馬
//
//==========================================
#include "camera.h"
#include "..\..\..\main.h"			//ここなんとかして
#include "..\..\_Core\manager\manager.h"
#include "..\..\_Core\renderer\renderer.h"
#include "..\..\_Core\utility\Utility.h"

//マクロ
#define CAMERA_LENGTH			(40000.0f)	//カメラが見える最大距離
#define CAMERA_ROT_X_MIN		(-0.45f)	//カメラのX角度の最低値[rad]
#define CAMERA_ROT_X_MAX		(-0.2f)	//カメラのX角度の最低値[rad]

//========================
//コンストラクタ
//========================
CCamera::CCamera()
{
	//値クリア
	m_posV = IS_Utility::VEC3_ZERO;
	m_posR = IS_Utility::VEC3_ZERO;
	m_vecU = IS_Utility::VEC3_ZERO;
	m_rot = IS_Utility::VEC3_ZERO;
	m_fLength = 0.0f;
}

//========================
//デストラクタ
//========================
CCamera::~CCamera()
{

}

//========================
//初期化処理
//========================
HRESULT CCamera::Init(void)
{
	//値設定
	ResetPos();

	//できた
	return S_OK;
}

//========================
//終了処理
//========================
void CCamera::Uninit(void)
{
	
}

//========================
//更新処理
//========================
void CCamera::Update(void)
{

}

//========================
//設定処理
//========================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得

	//プロジェクションマトリックス初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, CAMERA_LENGTH);

	//設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	
	//ビューマトリックス初期化
	D3DXMatrixIdentity(&m_mtxView);

	//作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	//設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//========================
//位置設定
//========================
void CCamera::Move(const D3DXVECTOR3 move)
{
	//位置適用
	m_posV += move;
	m_posR += move;
}

//========================
//向き設定
//========================
void CCamera::SetRot(const D3DXVECTOR3 rot)
{
	//回転適用と修正処理
	m_rot = rot;
	FixRot();
	m_vecU.x = sinf(m_rot.x) * sinf(m_rot.y);
	m_vecU.y = cosf(m_rot.x);
	m_vecU.z = sinf(m_rot.x) * cosf(m_rot.y) * -1;
	D3DXVec3Normalize(&m_vecU, &m_vecU);
	FixPosV();
}

//========================
//距離設定とposVの修正
//========================
void CCamera::SetLength(const float fLength)
{
	m_fLength = fLength;
	FixPosV();
}

//========================
//カメラ位置リセット
//========================
void CCamera::ResetPos(void)
{
	//値設定
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(-0.3f, 0.0f, 0.0f);
	m_fLength = 400.0f;
	FixRot();
	FixPosV();	//ここでposVを決める
}

//========================
//視点修正（注視点中心）
//========================
void CCamera::FixPosV(void)
{
	m_posV.x = m_posR.x + cosf(m_rot.x) * sinf(m_rot.y) * m_fLength;
	m_posV.y = m_posR.y - sinf(m_rot.x) * m_fLength;
	m_posV.z = m_posR.z - cosf(m_rot.x) * cosf(m_rot.y) * m_fLength;
}

//========================
//注視点修正（視点中心）
//========================
void CCamera::FixPosR(void)
{
	m_posR.x = m_posV.x - sinf(m_rot.y) * cosf(m_rot.x) * m_fLength;
	m_posR.z = m_posV.z + cosf(m_rot.y) * cosf(m_rot.x) * m_fLength;
}

//========================
//角度修正
//========================
void CCamera::FixRot(void)
{
	//カメラ1周計算
	m_rot.x = IS_Utility::FixRot(m_rot.x);
	m_rot.y = IS_Utility::FixRot(m_rot.y);
	m_rot.z = IS_Utility::FixRot(m_rot.z);

#if 0
	//[カメラ制限]x回転の制限
	if (m_rot.x >= CAMERA_ROT_X_MAX * D3DX_PI)
	{
		m_rot.x = CAMERA_ROT_X_MAX * D3DX_PI;
	}
	else if (m_rot.x <= CAMERA_ROT_X_MIN * D3DX_PI)
	{
		m_rot.x = CAMERA_ROT_X_MIN * D3DX_PI;
	}
#endif
}