//======================================================
//
//ボタン処理(3D)[button3D.cpp]
//Author:石原颯馬
//
//======================================================
#include "button3D.h"
#include "..\..\_Core\input\input.h"
#include "..\..\_Core\manager\manager.h"
#include "..\..\_Core\renderer\renderer.h"
#include "..\..\_Core\utility\Utility.h"

//========================
//コンストラクタ
//========================
CButton3D::CButton3D(int nPriority) : CObject3D(nPriority)
{
	//値クリア
	m_bHold = false;
	m_bPress = false;
	m_bTrigger = false;
	m_bRelease = false;
	m_bRepeate = false;
}

//========================
//デストラクタ
//========================
CButton3D::~CButton3D()
{
}

//========================
//初期化
//========================
HRESULT CButton3D::Init(void)
{
	//親処理
	CObject3D::Init();

	return S_OK;
}

//========================
//終了
//========================
void CButton3D::Uninit(void)
{
	//親処理
	CObject3D::Uninit();
}

//========================
//更新
//========================
void CButton3D::Update(void)
{
	//ボタン処理
	CInputMouse* mouse = CManager::GetInstance()->GetInputMouse();	//マウス取得

	//マウス取得
	if (mouse != nullptr)
	{
		D3DXVECTOR3 buttonPos = GetPos();			//ボタン位置取得
		D3DXVECTOR3 buttonRot = GetRot();			//ボタン角度取得
		float fWidth = GetWidth();					//ボタン幅取得
		float fDepth = GetDepth();					//ボタン高さ取得
		D3DXVECTOR3 cursorPos = mouse->GetPos();	//カーソル位置取得

		//オブジェクト選択（0.0～1.0）
		D3DXVECTOR3 posNear = mouse->ConvertClickPosToWorld(0.0f);
		D3DXVECTOR3 posFar = mouse->ConvertClickPosToWorld(1.0f);

		//頂点計算
		D3DXVECTOR3 pos0 = D3DXVECTOR3(-fWidth * 0.5f, 0.0f, fDepth * 0.5f);
		D3DXVECTOR3 pos1 = D3DXVECTOR3(fWidth * 0.5f, 0.0f, fDepth * 0.5f);
		D3DXVECTOR3 pos2 = D3DXVECTOR3(-fWidth * 0.5f, 0.0f, -fDepth * 0.5f);
		D3DXVECTOR3 pos3 = D3DXVECTOR3(fWidth * 0.5f, 0.0f, -fDepth * 0.5f);
		pos0 = IS_Utility::RotateVtx(pos0, buttonRot, buttonPos);
		pos1 = IS_Utility::RotateVtx(pos1, buttonRot, buttonPos);
		pos2 = IS_Utility::RotateVtx(pos2, buttonRot, buttonPos);
		pos3 = IS_Utility::RotateVtx(pos3, buttonRot, buttonPos);

		float fDust;
		D3DXVECTOR3 nor = (posFar - posNear);
		D3DXVec3Normalize(&nor, &nor);
		if (D3DXIntersectTri(&pos2, &pos1, &pos0, &posNear, &nor, &fDust, &fDust, &fDust) == TRUE ||
			D3DXIntersectTri(&pos1, &pos2, &pos3, &posNear, &nor, &fDust, &fDust, &fDust) == TRUE)
		{//範囲内
			m_bHold = true;										//かざし
			m_bPress = mouse->GetPress(CInputMouse::CLICK_LEFT);		//プレス
			m_bTrigger = mouse->GetTrigger(CInputMouse::CLICK_LEFT);	//トリガー
			m_bRelease = mouse->GetRelease(CInputMouse::CLICK_LEFT);	//リリース
			m_bRepeate = mouse->GetRepeate(CInputMouse::CLICK_LEFT);	//リピート
		}
		else
		{//範囲外
			m_bHold = false;	//かざし
			m_bPress = false;	//プレス
			m_bTrigger = false;	//トリガー
			m_bRelease = false;	//リリース
			m_bRepeate = false;	//リピート
		}
	}
	else
	{//マウスが取得できない
		m_bHold = false;	//かざし
		m_bPress = false;	//プレス
		m_bTrigger = false;	//トリガー
		m_bRelease = false;	//リリース
		m_bRepeate = false;	//リピート
	}

	//親処理
	CObject3D::Update();
}

//========================
//描画
//========================
void CButton3D::Draw(void)
{
	//親処理
	CObject3D::Draw();
}

//========================
//生成
//========================
CButton3D* CButton3D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight)
{
	CButton3D* pButton3D = nullptr;

	if (pButton3D == nullptr)
	{
		//オブジェクト2Dの生成
		pButton3D = new CButton3D;
		pButton3D->SetPos(pos);
		pButton3D->SetRot(rot);
		pButton3D->SetSize(fWidth, fHeight);

		//初期化
		pButton3D->Init();

		return pButton3D;
	}
	else
	{
		return nullptr;
	}
}