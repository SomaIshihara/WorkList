//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 石原颯馬
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//サウンドクラス
class CSound
{
public:
	//*****************************************************************************
	// サウンド一覧
	//*****************************************************************************
	enum SOUND_LABEL
	{
		SOUND_LABEL_BGM_TITLE = 0,	//BGM（タイトル）
		SOUND_LABEL_BGM_GAME,		//BGM（ゲーム）
		SOUND_LABEL_BGM_RANKING,	//BGM（ランキング）
		SOUND_LABEL_SE_RUN,			//SE（車走行音）
		SOUND_LABEL_SE_GEARCHANGE,	//SE（車ギアチェン音）
		SOUND_LABEL_SE_DRIFT,		//SE（車ドリフト音）
		SOUND_LABEL_SE_CLEARBRAKE,	//SE（クリア時の車ブレーキ音）
		SOUND_LABEL_MAX,
	};
	//*****************************************************************************

	//コンストラクタ・デストラクタ
	CSound();
	~CSound();

	//基本処理
	HRESULT Init(HWND hWnd);
	void Uninit(void);

	//流す処理
	HRESULT Play(SOUND_LABEL label);	//流す
	void Stop(SOUND_LABEL label);		//1つ止める
	void Stop(void);					//全部止める
	void Pause(SOUND_LABEL label);		//ポーズ
	void Restart(SOUND_LABEL label);	//再開
	
	//状態取得
	bool IsPlay(SOUND_LABEL label);		//流しているか

	//設定
	HRESULT SetVolume(SOUND_LABEL label, float volume);	//ボリューム設定
private:
	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
};

#endif
