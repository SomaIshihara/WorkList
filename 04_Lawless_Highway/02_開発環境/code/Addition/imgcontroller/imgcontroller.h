//==========================================
//
//仮想コントローラ[imgcontroller.h]
//Author:石原颯馬
//
//==========================================
#ifndef _IMG_CONTROLLER_H_
#define _IMG_CONTROLLER_H_

//入力インタフェース
__interface IController
{
	float Handle(void) = 0;
	bool Brake(void) = 0;
	bool Nitro(void) = 0;
};

//仮想コントローラクラス
class CImgController
{
public:
	//コンストラクタ・デストラクタ
	CImgController(IController* pInput) { m_pInput = pInput; }
	~CImgController() { delete m_pInput; }

	//入力取得
	float Handle(void) { return m_pInput->Handle(); }
	bool Brake(void) { return m_pInput->Brake(); }
	bool Nitro(void) { return m_pInput->Nitro(); }
private:
	IController* m_pInput;
};


//キーボード入力クラス
class CControllerKB : public IController
{
public:
	//コンストラクタ・デストラクタ
	CControllerKB(){}
	~CControllerKB(){}

	//入力取得
	float Handle(void);
	bool Brake(void);
	bool Nitro(void);
};

//ゲームパッド入力クラス
class CControllerGP : public IController
{
public:
	//コンストラクタ・デストラクタ
	CControllerGP(){}
	~CControllerGP(){}

	//入力取得
	float Handle(void);
	bool Brake(void);
	bool Nitro(void);
};

#endif