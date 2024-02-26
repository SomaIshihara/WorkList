//==========================================
//
//ファイル読み込みプログラム[file.cpp]
//Author:石原颯馬
//
//==========================================
#include "file.h"
#include "..\..\_Core\manager\manager.h"
#include "..\..\_Core\texture\texture.h"
#include "../utility/Utility.h"
#include "../utility/Utility_Vector.h"
#include "..\_object\object_x\objectX.h"
#include "..\_object\object_billboard\objectBillboard.h"
#include "..\charmotion\motion.h"
#include "..\charmodel\model.h"
#include "..\xmodel\xmodel.h"
#include "../../../Addition/meshroad/meshroad.h"
#include <vector>
#include <stdio.h>
#include <assert.h>

//コード関係
#define CODE_STR_LENGTH		(1024)
#define FILEPATH_LENGTH	(256)
#define MAX_PARTS		(16)

//読み取り状態列挙
typedef enum
{
	//共通
	READSTAT_NONE = 0,	//何もしてない

	//-モデルビューワー-----------------------
	READSTAT_CAMERASET,
	READSTAT_LIGHTSET,
	READSTAT_SKYSET,
	READSTAT_MOUNTAINSET,
	READSTAT_FIELDSET,
	READSTAT_WALLSET,
	READSTAT_MODELSET,
	READSTAT_BILLBOARDSET,
	READSTAT_PLAYERSET,
	//----------------------------------------

	//--モーションビューワー------------------
	READSTAT_CHARACTERSET,
	READSTAT_PARTSSET,
	READSTAT_MOTIONSET,
	READSTAT_KEYSET,
	READSTAT_KEY,
	//----------------------------------------

	//--道路メッシュスクリプト------------------
	READSTAT_VECTORSET,
	//----------------------------------------

	READSTAT_MAX
} READSTAT;

typedef enum
{
	TYPE_X = 0,		//CObjectX使用
	TYPE_BUILDING,	//CBuinding使用
	TYPE_MAX
} TYPE;

//グローバル
READSTAT g_readStat = READSTAT_NONE;

//========================
//ファイル初期化処理
//========================
void InitFile(void)
{
	g_readStat = READSTAT_NONE;
}

#if 0
//========================
//マップ読み込み処理
//========================
void LoadModelViewerFile(const char *path)
{
	FILE *pFile;
	char aCode[CODE_LENGTH];
	char *pSprit;
	bool bRead = false;
	int nCntInit = 0;	//初期化カウンタ

	//読み込みデータ
	int nType = -1;
	D3DXVECTOR3 pos = IS_Utility::VEC3_ZERO, rot = IS_Utility::VEC3_ZERO;
	int nState = 0;
	bool bCollision = false, bShadow = false;

	float fWidth = CManager::FLOAT_ZERO, fHeight = CManager::FLOAT_ZERO;

	//読み込みファイル設定
	pFile = fopen(path, "r");

	//敵配置情報を取得
	if (pFile != nullptr)
	{
		while (1)
		{
			fgets(&aCode[0], CODE_LENGTH, pFile);

			//コメントアウトチェック
			char *pCharPos = strchr(&aCode[0], '#');
			if (pCharPos != nullptr)
			{//strchrの返り値がぬるぽではない
				*pCharPos = '\0';
			}

			//タブ消去
			while (aCode[0] == '\t')
			{
				char aCodeBackup[CODE_LENGTH];
				strcpy(&aCodeBackup[0], &aCode[0]);
				strcpy(&aCode[0], &aCodeBackup[1]);
			}

			//文字列チェック
			if (strncmp(&aCode[0], CODE_SCRIPT, sizeof CODE_SCRIPT / sizeof(char) - 1) == 0)
			{//読み取り開始
				bRead = true;
			}
			else if (strncmp(&aCode[0], CODE_END_SCRIPT, sizeof CODE_END_SCRIPT / sizeof(char) - 1) == 0)
			{//読み取り終了
				bRead = false;
				break;
			}
			else if (aCode[0] == EOF)
			{//EOFかもしれない
				if (feof(pFile))
				{//いや、これはEOFだ
					bRead = false;
					break;
				}
			}
			else if (bRead == true)
			{//読み取り
				switch (g_readStat)
				{
				case READSTAT_NONE:	//処理取得
					//処理部分
#if 0
					if (strncmp(&aCode[0], CODE_CAMERASET, sizeof CODE_CAMERASET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_CAMERASET;
					}
					else if (strncmp(&aCode[0], CODE_LIGHTSET, sizeof CODE_LIGHTSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_LIGHTSET;
					}
					else if (strncmp(&aCode[0], CODE_SKYSET, sizeof CODE_SKYSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_SKYSET;
					}
					else if (strncmp(&aCode[0], CODE_MOUNTAINSET, sizeof CODE_MOUNTAINSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_MOUNTAINSET;
					}
					else if (strncmp(&aCode[0], CODE_FIELDSET, sizeof CODE_FIELDSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_FIELDSET;
					}
					else if (strncmp(&aCode[0], CODE_WALLSET, sizeof CODE_WALLSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_WALLSET;
					}
					else 
#endif
					if (strncmp(&aCode[0], CODE_MODELSET, sizeof CODE_MODELSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_MODELSET;
					}
					else if (strncmp(&aCode[0], CODE_BILLBOARDSET, sizeof CODE_BILLBOARDSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_BILLBOARDSET;
					}
#if 0
					else if (strncmp(&aCode[0], CODE_PLAYERSET, sizeof CODE_PLAYERSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_PLAYERSET;
					}
#endif
					//取得部分
					else if (strncmp(&aCode[0], CODE_TEXTURE_FILENAME, sizeof CODE_TEXTURE_FILENAME / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//パス取得
						pSprit = strtok(nullptr, " =\n");

						//タブ文字が入っているところを消す
						char *pCharPos = strchr(pSprit, '\t');
						if (pCharPos != nullptr)
						{//strchrの返り値がぬるぽではない
							*pCharPos = '\0';
						}

						//テクスチャ読み込み
						CManager::GetInstance()->GetInstance()->GetTexture()->Regist(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_MODEL_FILENAME, sizeof CODE_MODEL_FILENAME / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//パス取得
						pSprit = strtok(nullptr, " =\n");

						//タブ文字が入っているところを消す
						char *pCharPos = strchr(pSprit, '\t');
						if (pCharPos != nullptr)
						{//strchrの返り値がぬるぽではない
							*pCharPos = '\0';
						}

						//モデル読み込み
						CXModel::Load(pSprit);
					}
					break;
#if 0
				case READSTAT_CAMERASET:	//pvpカメラ情報取得
					if (strncmp(&aCode[0], CODE_END_CAMERASET, sizeof CODE_END_CAMERASET / sizeof(char) - 1) == 0)
					{
						//カメラ設定
						InitSetCameraPos(g_readCamera.posV, g_readCamera.posR, g_counterReadCamera);
						g_readStat = READSTAT_NONE;
						g_counterReadCamera++;		//加算
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//X座標読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readCamera.posV.x = IS_Utility::fatof(pSprit);

						//Y座標読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readCamera.posV.y = IS_Utility::fatof(pSprit);

						//Z座標読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readCamera.posV.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_REF, sizeof CODE_REF / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//X座標読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readCamera.posR.x = IS_Utility::fatof(pSprit);

						//Y座標読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readCamera.posR.y = IS_Utility::fatof(pSprit);

						//Z座標読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readCamera.posR.z = IS_Utility::fatof(pSprit);
					}
					break;
				case READSTAT_LIGHTSET:		//ライト情報取得
					if (strncmp(&aCode[0], CODE_END_LIGHTSET, sizeof CODE_END_LIGHTSET / sizeof(char) - 1) == 0)
					{
						//ライト設定
						SetLight(g_counterReadLight, g_readLight);
						g_readStat = READSTAT_NONE;

						g_counterReadLight++;
					}
					else if (strncmp(&aCode[0], CODE_DIRECTION, sizeof CODE_DIRECTION / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//仮置き変数宣言
						D3DXVECTOR3 vecDir;

						//X座標読み取り
						pSprit = strtok(nullptr, " =\n");
						vecDir.x = IS_Utility::fatof(pSprit);

						//Y座標読み取り
						pSprit = strtok(nullptr, " =\n");
						vecDir.y = IS_Utility::fatof(pSprit);

						//Z座標読み取り
						pSprit = strtok(nullptr, " =\n");
						vecDir.z = IS_Utility::fatof(pSprit);

						//ベクトル正規化
						D3DXVec3Normalize(&vecDir, &vecDir);

						//代入
						g_readLight.Direction = vecDir;
					}
					else if (strncmp(&aCode[0], CODE_DIFFUSE, sizeof CODE_DIFFUSE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//赤
						pSprit = strtok(nullptr, " =\n");
						g_readLight.Diffuse.r = IS_Utility::fatof(pSprit);

						//緑
						pSprit = strtok(nullptr, " =\n");
						g_readLight.Diffuse.g = IS_Utility::fatof(pSprit);

						//青
						pSprit = strtok(nullptr, " =\n");
						g_readLight.Diffuse.b = IS_Utility::fatof(pSprit);

						//アルファ値は1.0固定
						g_readLight.Diffuse.a = 1.0f;
					}
					break;
				case READSTAT_SKYSET:		//空情報取得
					if (strncmp(&aCode[0], CODE_END_SKYSET, sizeof CODE_END_SKYSET / sizeof(char) - 1) == 0)
					{
						//空設定して
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_TEXTYPE, sizeof CODE_TEXTYPE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//取得
						pSprit = strtok(nullptr, " =\n");
						g_readsky.texType = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_MOVE, sizeof CODE_MOVE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//取得
						pSprit = strtok(nullptr, " =\n");
						g_readsky.fMove = IS_Utility::fatof(pSprit);
					}
					break;
				case READSTAT_MOUNTAINSET:	//山情報取得
					if (strncmp(&aCode[0], CODE_END_MOUNTAINSET, sizeof CODE_END_MOUNTAINSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_TEXTYPE, sizeof CODE_TEXTYPE / sizeof(char) - 1) == 0)
					{
						//取得
						pSprit = strtok(nullptr, " =\n");
						g_nMountainTexNum = atoi(pSprit);
					}
					break;
				case READSTAT_FIELDSET:		//床情報取得
					if (strncmp(&aCode[0], CODE_END_FIELDSET, sizeof CODE_END_FIELDSET / sizeof(char) - 1) == 0)
					{
						//地面設定
						SetMeshField(g_readmeshfield.texType, g_readmeshfield.mf);
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_TEXTYPE, sizeof CODE_TEXTYPE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//取得
						pSprit = strtok(nullptr, " =\n");
						g_readmeshfield.texType = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//X座標読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readmeshfield.mf.pos.x = IS_Utility::fatof(pSprit);

						//Y座標読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readmeshfield.mf.pos.y = IS_Utility::fatof(pSprit);

						//Z座標読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readmeshfield.mf.pos.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//X座標読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readmeshfield.mf.rot.x = IS_Utility::fatof(pSprit);

						//Y座標読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readmeshfield.mf.rot.y = IS_Utility::fatof(pSprit);

						//Z座標読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readmeshfield.mf.rot.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_SIZE, sizeof CODE_SIZE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//サイズ読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readmeshfield.mf.fRadius = IS_Utility::fatof(pSprit);
					}
					break;
				case READSTAT_WALLSET:		//壁情報取得
					if (strncmp(&aCode[0], CODE_END_WALLSET, sizeof CODE_END_WALLSET / sizeof(char) - 1) == 0)
					{
						//壁生成して
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_TEXTYPE, sizeof CODE_TEXTYPE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//取得
						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.texType = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//位置読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.pos.x = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.pos.y = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.pos.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//向き読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.rot.x = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.rot.y = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.rot.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_BLOCK, sizeof CODE_BLOCK / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//分割数読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.blockX = atoi(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.blockZ = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_SIZE, sizeof CODE_SIZE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//サイズ読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.sizeX = atoi(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.sizeZ = atoi(pSprit);
					}
					break;
#endif
				case READSTAT_MODELSET:		//モデル情報取得
					if (strncmp(&aCode[0], CODE_END_MODELSET, sizeof CODE_END_MODELSET / sizeof(char) - 1) == 0)
					{
						CXModel* pModel = CXModel::GetTop();
						for (int cnt = 0; cnt < nType; cnt++)
						{
							pModel->GetNext();
						}
						CObjectX::Create(pos, rot, pModel);
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_TYPE, sizeof CODE_TYPE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//種類読み取り
						pSprit = strtok(nullptr, " =\n");
						nType = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//X座標読み取り
						pSprit = strtok(nullptr, " =\n");
						pos.x = IS_Utility::fatof(pSprit);

						//Y座標読み取り
						pSprit = strtok(nullptr, " =\n");
						pos.y = IS_Utility::fatof(pSprit);

						//Z座標読み取り
						pSprit = strtok(nullptr, " =\n");
						pos.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//X座標読み取り
						pSprit = strtok(nullptr, " =\n");
						rot.x = (IS_Utility::fatof(pSprit) / 180) * D3DX_PI;

						//Y座標読み取り
						pSprit = strtok(nullptr, " =\n");
						rot.y = (IS_Utility::fatof(pSprit) / 180) * D3DX_PI;

						//Z座標読み取り
						pSprit = strtok(nullptr, " =\n");
						rot.z = (IS_Utility::fatof(pSprit) / 180) * D3DX_PI;
					}
					else if (strncmp(&aCode[0], CODE_STATE, sizeof CODE_STATE / sizeof(char) - 1) == 0)
					{//状態指定
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//状態設定
						pSprit = strtok(nullptr, " =\n");
						nState = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_COLLISION, sizeof CODE_COLLISION / sizeof(char) - 1) == 0)
					{//0なら当たり判定無効
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//当たり判定設定
						pSprit = strtok(nullptr, " =\n");
						bCollision = (atoi(pSprit) >= 1) ? true : false;
					}
					else if (strncmp(&aCode[0], CODE_SHADOW, sizeof CODE_SHADOW / sizeof(char) - 1) == 0)
					{//0なら影を使用しない
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						pSprit = strtok(nullptr, " =\n");
						bShadow = (atoi(pSprit) >= 1) ? true : false;
					}
					break;
				case READSTAT_BILLBOARDSET:	//ビルボード情報取得
					if (strncmp(&aCode[0], CODE_END_BILLBOARDSET, sizeof CODE_END_BILLBOARDSET / sizeof(char) - 1) == 0)
					{
						//ビルボード設定
						CObjectBillboard::Create(pos, IS_Utility::VEC3_ZERO, fWidth, fHeight, nType);

						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_TEXTYPE, sizeof CODE_TEXTYPE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//種類読み取り
						pSprit = strtok(nullptr, " =\n");
						nType = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//位置読み取り
						pSprit = strtok(nullptr, " =\n");
						pos.x = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						pos.y = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						pos.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_SIZE, sizeof CODE_SIZE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//サイズ読み取り
						pSprit = strtok(nullptr, " =\n");
						fWidth = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						fWidth = IS_Utility::fatof(pSprit);
					}
#if 0
					else if (strncmp(&aCode[0], CODE_ORIGIN, sizeof CODE_ORIGIN / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//何に使うのかわからないもの読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readbillboard.originX = atoi(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readbillboard.originZ = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_BLEND, sizeof CODE_BLEND / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//合成モード読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readbillboard.blend = atoi(pSprit);
					}
#endif
					else if (strncmp(&aCode[0], CODE_SHADOW, sizeof CODE_SHADOW / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//影使用有無読み取り
						pSprit = strtok(nullptr, " =\n");
						bShadow = (atoi(pSprit) >= 1) ? true : false;
					}
					break;
#if 0
				case READSTAT_PLAYERSET:	//プレイヤーモデル情報取得
					if (strncmp(&aCode[0], CODE_END_PLAYERSET, sizeof CODE_END_PLAYERSET / sizeof(char) - 1) == 0)
					{
						//プレイヤーモデル取得完了
						g_readStat = READSTAT_NONE;

						//加算
						g_counterReadAnimal++;
					}
					else if (strncmp(&aCode[0], CODE_MOTION_FILENAME, sizeof CODE_MOTION_FILENAME / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//取得
						pSprit = strtok(nullptr, " =\n");
						strcpy(&g_readPlayermodel[g_counterReadAnimal].motionFileName[0], pSprit);

						//タブ文字が入っているところを消す
						char *pCharPos = strchr(&g_readPlayermodel[g_counterReadAnimal].motionFileName[0], '\t');
						if (pCharPos != nullptr)
						{//strchrの返り値がぬるぽではない
							*pCharPos = '\0';
						}
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//位置読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readPlayermodel[g_counterReadAnimal].pos.x = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readPlayermodel[g_counterReadAnimal].pos.y = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readPlayermodel[g_counterReadAnimal].pos.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//向き読み取り
						pSprit = strtok(nullptr, " =\n");
						g_readPlayermodel[g_counterReadAnimal].rot.x = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readPlayermodel[g_counterReadAnimal].rot.y = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readPlayermodel[g_counterReadAnimal].rot.z = IS_Utility::fatof(pSprit);
					}
					break;
#endif
				}
			}
		}
	}
	else
	{
		assert(pFile != nullptr);
	}

	//ファイル閉じる
	fclose(pFile);
}
#endif
//========================
//モーション読み込み処理
//引数1:モーションビューワーの設定ファイルのパス
//引数2:入れたいモデル構造体のポインタ
//========================
bool LoadMotionViewerFile(const char *path, CModel*** pppModel, CMotion* pMotion, int* pNumModel)
{
	FILE *pFile;
	char aCode[CODE_STR_LENGTH];
	char *pSprit;
	bool bRead = false;

	//読み取った情報
	char aFilePath[16][FILEPATH_LENGTH] = {};	//モデルパス
	int nNumModelPath = 0;						//読み取ったモデルパス数
	int nIdx = -1;								//PARTSSET:使用するモデル
	int nSetModelNum = 0;						//PARTSSET:設定したモデル数
	int nParent = -1;							//PARTSSET:親
	D3DXVECTOR3 posOffset, rotOffset;			//PARTSSET:オフセットの位置向き

	CMotion::INFO info;
	int nKeyInfo = 0, nKey = 0;		//キー情報・キー

	//モーション情報
	//読み込みファイル設定
	pFile = fopen(path, "r");

	//敵配置情報を取得
	if (pFile != nullptr)
	{
		while (1)
		{
			fgets(&aCode[0], CODE_STR_LENGTH, pFile);

			//コメントアウトチェック
			char *pCharPos = strchr(&aCode[0], '#');
			if (pCharPos != nullptr)
			{//strchrの返り値がぬるぽではない
				*pCharPos = '\0';
			}

			//タブ消去
			while (aCode[0] == '\t')
			{
				char aCodeBackup[CODE_STR_LENGTH];
				strcpy(&aCodeBackup[0], &aCode[0]);
				strcpy(&aCode[0], &aCodeBackup[1]);
			}

			//文字列チェック
			if (strncmp(&aCode[0], CODE_SCRIPT, sizeof CODE_SCRIPT / sizeof(char) - 1) == 0)
			{//読み取り開始
				bRead = true;
			}
			else if (strncmp(&aCode[0], CODE_END_SCRIPT, sizeof CODE_END_SCRIPT / sizeof(char) - 1) == 0)
			{//読み取り終了
				bRead = false;
				break;
			}
			else if (aCode[0] == EOF)
			{//EOFかもしれない
				if (feof(pFile))
				{//いや、これはEOFだ
					bRead = false;
					break;
				}
			}
			else if (bRead == true)
			{//読み取り
				switch (g_readStat)
				{
				case READSTAT_NONE:	//処理取得
#if 0
					if (strncmp(&aCode[0], CODE_NUM_MODEL, sizeof CODE_NUM_MODEL / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						pSprit = strtok(nullptr, " =\n");	//読み取り
						
					}
#endif
					if (strncmp(&aCode[0], CODE_MODEL_FILENAME, sizeof CODE_MODEL_FILENAME / sizeof(char) - 1) == 0)
					{
						if (nNumModelPath < MAX_PARTS)
						{
							pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

							//代入
							strcpy(&aFilePath[nNumModelPath][0], strtok(nullptr, " =\n"));
							//タブ文字が入っているところを消す
							char *pCharPos = strchr(&aFilePath[nNumModelPath][0], '\t');
							if (pCharPos != nullptr)
							{//strchrの返り値がぬるぽではない
								*pCharPos = '\0';
							}

							//加算
							nNumModelPath++;
						}
					}
					if (strncmp(&aCode[0], CODE_CHARACTERSET, sizeof CODE_CHARACTERSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_CHARACTERSET;
					}
					if (strncmp(&aCode[0], CODE_MOTIONSET, sizeof CODE_MOTIONSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_MOTIONSET;

						//取り込み用変数の動的確保
						for (int cnt = 0; cnt < KEYINFO_NUM; cnt++)
						{
							info.m_aKeyInfo[cnt].m_pKey = new CMotion::KEY[*pNumModel];
						}
					}
					break;
				case READSTAT_CHARACTERSET:		//モデル情報取得
					if (strncmp(&aCode[0], CODE_END_CHARACTERSET, sizeof CODE_END_CHARACTERSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_PARTSSET, sizeof CODE_PARTSSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_PARTSSET;
					}
#if 0
					else if (strncmp(&aCode[0], CODE_MOVE, sizeof CODE_MOVE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//移動量取得
						pSprit = strtok(nullptr, " =\n");
						
					}
					else if (strncmp(&aCode[0], CODE_JUMP, sizeof CODE_JUMP / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//ジャンプ量取得
						pSprit = strtok(nullptr, " =\n");
						
					}
					else if (strncmp(&aCode[0], CODE_RADIUS, sizeof CODE_RADIUS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//半径取得
						pSprit = strtok(nullptr, " =\n");
						
					}
#endif
					else if (strncmp(&aCode[0], CODE_NUM_PARTS, sizeof CODE_NUM_PARTS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//パーツ数取得
						pSprit = strtok(nullptr, " =\n");
						*pNumModel = atoi(pSprit);

						//パーツ数に応じてモデル配列を動的確保
						*pppModel = new CModel*[*pNumModel];

						//モーションもキーを動的確保
						pMotion->SetModel(*pppModel, *pNumModel);
					}
					break;
				case READSTAT_PARTSSET:
					if (strncmp(&aCode[0], CODE_END_PARTSSET, sizeof CODE_END_PARTSSET / sizeof(char) - 1) == 0)
					{
						//生成
						(*pppModel)[nSetModelNum] = CModel::Create(&aFilePath[nIdx][0], posOffset, rotOffset);
						if (nParent != -1)
						{
							(*pppModel)[nSetModelNum]->SetParent((*pppModel)[nParent]);
						}
						else
						{
							(*pppModel)[nSetModelNum]->SetParent(nullptr);
						}

						nSetModelNum++;

						//キャラクター設定状態に戻る
						g_readStat = READSTAT_CHARACTERSET;
					}
					else if (strncmp(&aCode[0], CODE_INDEX, sizeof CODE_INDEX / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//番号取得
						pSprit = strtok(nullptr, " =\n");
						nIdx = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_PARENT, sizeof CODE_PARENT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//親番号取得
						pSprit = strtok(nullptr, " =\n");
						nParent = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//X座標読み取り
						pSprit = strtok(nullptr, " =\n");
						posOffset.x = IS_Utility::fatof(pSprit);

						//Y座標読み取り
						pSprit = strtok(nullptr, " =\n");
						posOffset.y = IS_Utility::fatof(pSprit);

						//Z座標読み取り
						pSprit = strtok(nullptr, " =\n");
						posOffset.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//X座標読み取り
						pSprit = strtok(nullptr, " =\n");
						rotOffset.x = IS_Utility::fatof(pSprit);

						//Y座標読み取り
						pSprit = strtok(nullptr, " =\n");
						rotOffset.y = IS_Utility::fatof(pSprit);

						//Z座標読み取り
						pSprit = strtok(nullptr, " =\n");
						rotOffset.z = IS_Utility::fatof(pSprit);
					}
					break;
				case READSTAT_MOTIONSET:
					if (strncmp(&aCode[0], CODE_KEYSET, sizeof CODE_KEYSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_KEYSET;
					}
					else if (strncmp(&aCode[0], CODE_END_MOTIONSET, sizeof CODE_END_MOTIONSET / sizeof(char) - 1) == 0)
					{
						//モーション設定
						pMotion->SetInfo(info);
						nKeyInfo = 0;
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_LOOP, sizeof CODE_LOOP / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//ループ可否読み取り
						pSprit = strtok(nullptr, " =\n");
						info.m_bLoop = atoi(pSprit) == 1 ? true : false;
					}
					else if (strncmp(&aCode[0], CODE_NUM_KEY, sizeof CODE_NUM_KEY / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//キー数読み取り
						pSprit = strtok(nullptr, " =\n");
						info.m_nNumKey = atoi(pSprit);
					}
					break;
				case READSTAT_KEYSET:
					if (strncmp(&aCode[0], CODE_KEY, sizeof CODE_KEY / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_KEY;
					}
					else if (strncmp(&aCode[0], CODE_END_KEYSET, sizeof CODE_END_KEYSET / sizeof(char) - 1) == 0)
					{
						nKeyInfo++;
						nKey = 0;
						g_readStat = READSTAT_MOTIONSET;
					}
					else if (strncmp(&aCode[0], CODE_FRAME, sizeof CODE_FRAME / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//フレーム数読み取り
						pSprit = strtok(nullptr, " =\n");
						info.m_aKeyInfo[nKeyInfo].m_nFrame = atoi(pSprit);
					}
					break;
				case READSTAT_KEY:
					if (strncmp(&aCode[0], CODE_END_KEY, sizeof CODE_END_KEY / sizeof(char) - 1) == 0)
					{
						nKey++;
						g_readStat = READSTAT_KEYSET;
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//X座標読み取り
						pSprit = strtok(nullptr, " =\n");
						info.m_aKeyInfo[nKeyInfo].m_pKey[nKey].m_fPosX = IS_Utility::fatof(pSprit);

						//Y座標読み取り
						pSprit = strtok(nullptr, " =\n");
						info.m_aKeyInfo[nKeyInfo].m_pKey[nKey].m_fPosY = IS_Utility::fatof(pSprit);

						//Z座標読み取り
						pSprit = strtok(nullptr, " =\n");
						info.m_aKeyInfo[nKeyInfo].m_pKey[nKey].m_fPosZ = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//X向き読み取り
						pSprit = strtok(nullptr, " =\n");
						info.m_aKeyInfo[nKeyInfo].m_pKey[nKey].m_fRotX = IS_Utility::fatof(pSprit);

						//Y向き読み取り
						pSprit = strtok(nullptr, " =\n");
						info.m_aKeyInfo[nKeyInfo].m_pKey[nKey].m_fRotY = IS_Utility::fatof(pSprit);

						//Z向き読み取り
						pSprit = strtok(nullptr, " =\n");
						info.m_aKeyInfo[nKeyInfo].m_pKey[nKey].m_fRotZ = IS_Utility::fatof(pSprit);
					}
					break;
				}
			}
		}
	}
	else
	{
		return false;
	}

	//ファイル閉じる
	fclose(pFile);

	return true;
}

//========================
//道路メッシュ読み込み処理
//========================
CMeshRoad* LoadRoadScriptFile(const char* pPath)
{
	FILE* pFile;
	char aCode[CODE_STR_LENGTH];
	char* pSprit;
	bool bRead = false;

	//読み取った情報
	D3DXVECTOR3 pos, rot;
	pos = rot = IS_Utility::VEC3_ZERO;
	float fLength = 1.0f;
	std::vector<IS_Utility::Utility_Vector3> vVector;

	//モーション情報
	//読み込みファイル設定
	pFile = fopen(pPath, "r");

	//敵配置情報を取得
	if (pFile != nullptr)
	{
		while (1)
		{
			fgets(&aCode[0], CODE_STR_LENGTH, pFile);

			//コメントアウトチェック
			char* pCharPos = strchr(&aCode[0], '#');
			if (pCharPos != nullptr)
			{//strchrの返り値がぬるぽではない
				*pCharPos = '\0';
			}

			//タブ消去
			while (aCode[0] == '\t')
			{
				char aCodeBackup[CODE_STR_LENGTH];
				strcpy(&aCodeBackup[0], &aCode[0]);
				strcpy(&aCode[0], &aCodeBackup[1]);
			}

			//文字列チェック
			if (strncmp(&aCode[0], CODE_SCRIPT, sizeof CODE_SCRIPT / sizeof(char) - 1) == 0)
			{//読み取り開始
				bRead = true;
			}
			else if (strncmp(&aCode[0], CODE_END_SCRIPT, sizeof CODE_END_SCRIPT / sizeof(char) - 1) == 0)
			{//読み取り終了
				bRead = false;
				break;
			}
			else if (aCode[0] == EOF)
			{//EOFかもしれない
				if (feof(pFile))
				{//いや、これはEOFだ
					bRead = false;
					break;
				}
			}
			else if (bRead == true)
			{//読み取り
				switch (g_readStat)
				{
				case READSTAT_NONE:	//処理取得
					if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//X座標読み取り
						pSprit = strtok(nullptr, " =\n");
						pos.x = IS_Utility::fatof(pSprit);

						//Y座標読み取り
						pSprit = strtok(nullptr, " =\n");
						pos.y = IS_Utility::fatof(pSprit);

						//Z座標読み取り
						pSprit = strtok(nullptr, " =\n");
						pos.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//X座標読み取り
						pSprit = strtok(nullptr, " =\n");
						rot.x = IS_Utility::fatof(pSprit);

						//Y座標読み取り
						pSprit = strtok(nullptr, " =\n");
						rot.y = IS_Utility::fatof(pSprit);

						//Z座標読み取り
						pSprit = strtok(nullptr, " =\n");
						rot.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_LENGTH, sizeof CODE_LENGTH - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//読み取り
						pSprit = strtok(nullptr, " =\n");
						fLength = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_SET_VECTOR, sizeof CODE_SET_VECTOR - 1) == 0)
					{
						g_readStat = READSTAT_VECTORSET;
					}
					break;
				case READSTAT_VECTORSET:		//ベクトル取得
					if (strncmp(&aCode[0], CODE_END_SET_VECTOR, sizeof CODE_END_SET_VECTOR - 1) == 0)
					{
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_VECTOR, sizeof CODE_VECTOR - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						IS_Utility::Utility_Vector3 vec;

						//X座標読み取り
						pSprit = strtok(nullptr, " =\n");
						vec.x = IS_Utility::fatof(pSprit);

						//Y座標読み取り
						pSprit = strtok(nullptr, " =\n");
						vec.y = IS_Utility::fatof(pSprit);

						//Z座標読み取り
						pSprit = strtok(nullptr, " =\n");
						vec.z = IS_Utility::fatof(pSprit);

						//ぶち込む
						vVector.push_back(vec);
					}
					break;
				}
			}
		}
	}
	else
	{
		return false;
	}

	//ファイル閉じる
	fclose(pFile);

	//道路生成
	CMeshRoad* pMeshRoad = CMeshRoad::Create(pos, rot, fLength, vVector);

	return pMeshRoad;
}
