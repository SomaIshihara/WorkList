//======================================================
//
//ボタン処理(2D)[button2D.cpp]
//Author:石原颯馬
//
//======================================================
#include "button2D.h"
#include "input.h"
#include "Culc.h"
#include "manager.h"
#include "renderer.h"

//========================
//コンストラクタ
//========================
CButton2D::CButton2D()
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
CButton2D::~CButton2D()
{
}

//========================
//初期化
//========================
HRESULT CButton2D::Init(void)
{
	//親処理
	CObject2D::Init();

	return S_OK;
}

//========================
//終了
//========================
void CButton2D::Uninit(void)
{
	//親処理
	CObject2D::Uninit();
}

//========================
//更新
//========================
void CButton2D::Update(void)
{
	//ボタン処理
	CInputMouse* mouse = CManager::GetInstance()->GetInputMouse();	//マウス取得

	//マウス取得
	if (mouse != nullptr)
	{
		D3DXVECTOR3 buttonPos = GetPos();			//ボタン位置取得
		float fWidth = GetWidth();					//ボタン幅取得
		float fHeight = GetHeight();				//ボタン高さ取得
		D3DXVECTOR3 cursorPos = mouse->GetPos();	//カーソル位置取得

		if (cursorPos.x >= buttonPos.x - fWidth * 0.5f &&
			cursorPos.x <= buttonPos.x + fWidth * 0.5f &&
			cursorPos.y >= buttonPos.y - fHeight * 0.5f &&
			cursorPos.y <= buttonPos.y + fHeight * 0.5f)
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
	CObject2D::Update();
}

//========================
//描画
//========================
void CButton2D::Draw(void)
{
	//親処理
	CObject2D::Draw();
}

//========================
//生成
//========================
CButton2D* CButton2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, int nPriority)
{
	CButton2D* pButton2D = nullptr;

	if (pButton2D == nullptr)
	{
		//オブジェクト2Dの生成
		pButton2D = new CButton2D;

		//初期化
		pButton2D->Init();

		//データ設定
		pButton2D->SetPos(pos);
		pButton2D->SetRot(rot);
		pButton2D->SetSize(fWidth, fHeight);

		return pButton2D;
	}
	else
	{
		return nullptr;
	}
}