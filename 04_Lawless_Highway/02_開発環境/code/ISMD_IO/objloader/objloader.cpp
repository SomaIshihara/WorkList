//======================================================
//
//オブジェクト読み込み処理[objloader.cpp]
//Author:石原颯馬
//
//======================================================
#include "objloader.h"
#include "..\..\IS_Bace\_Core\texture\texture.h"
#include "..\..\IS_Bace\_Core\xmodel\xmodel.h"
#include "..\..\IS_Bace\_Core\_object\object_x\objectX.h"
#include "..\userdef\userdef.h"
#include <string>

//========================
//ISMD形式読み書き名前空間
//========================
namespace ISMD_IO
{
	//========================
	//データ読み込み
	//========================
	LOADRESULT LoadData(const char* pPath)
	{
		FILE* pFile;
		BINCODE code;
		bool bRead = false;
		char** ppFilePath = nullptr;
		int nReadedModel = 0;
		int nNumAll = 0;

		pFile = fopen(pPath, "rb");

		if (pFile != nullptr)
		{//開けた
			while (1)
			{
				fread(&code, sizeof(BINCODE), 1, pFile);

				//文字列チェック
				if (code == BIN_CODE_SCRIPT)
				{//読み取り開始
					bRead = true;
				}
				else if (code == BIN_CODE_END_SCRIPT)
				{//読み取り終了
					bRead = false;
					break;
				}
				else if (bRead == true)
				{//読み取り
					if (code == BIN_CODE_TEXTURE_FILENAME)
					{
						char aPath[STR_LENGTH];
						fread(&aPath[0], sizeof(char), STR_LENGTH, pFile);
						CManager::GetInstance()->GetTexture()->Load(&aPath[0]);
					}
					else if (code == BIN_CODE_MODEL_NUM)
					{
						fread(&nNumAll, sizeof(int), 1, pFile);
						ppFilePath = new char* [nNumAll];
					}
					else if (code == BIN_CODE_MODEL_FILENAME)
					{
						char aPath[STR_LENGTH];
						fread(&aPath[0], sizeof(char), STR_LENGTH, pFile);
						CXModel::Load(&aPath[0]);

						//モデルパス読み取り（引き出し用に使う）
						if (ppFilePath != nullptr)
						{
							ppFilePath[nReadedModel] = new char[strlen(&aPath[0]) + 1];
							strcpy(ppFilePath[nReadedModel], &aPath[0]);
							nReadedModel++;
						}
					}

					else if (code == BIN_CODE_MODELSET)
					{
						D3DXVECTOR3 pos, rot;
						int nModelNum = -1;
						CXModel* pModel = nullptr;
						fread(&pos, sizeof(D3DXVECTOR3), 1, pFile);
						fread(&rot, sizeof(D3DXVECTOR3), 1, pFile);
						fread(&nModelNum, sizeof(int), 1, pFile);
						if (ppFilePath != nullptr && ppFilePath[nModelNum] != nullptr)
						{
							pModel = CXModel::Load(ppFilePath[nModelNum]);
						}

						//仮オブジェクト生成
						CObjectX* pObject = CObjectX::Create(pos, rot, pModel);
					}
					else if (code == BIN_CODE_USERDEF)
					{
						//変数定義機能廃止
					}
				}
			}

			//読み込みに使用した動的確保変数を破棄
			for (int cnt = 0; cnt < nNumAll; cnt++)
			{
				if (ppFilePath[cnt] != nullptr)
				{
					delete[] ppFilePath[cnt];
				}
			}
			delete[] ppFilePath;

			fclose(pFile);
			return LOADRESULT::RES_OK;
		}
		else
		{//開けなかった（ファイルないんじゃね？）
			return LOADRESULT::RES_ERR_FILE_NOTFOUND;
		}
	}

	//========================
	//データ書き込み
	//========================
	LOADRESULT SaveData(const char* pPath)
	{
		FILE* pFile;

		pFile = fopen(pPath, "wb");

		if (pFile != nullptr)
		{//普通に開けた
			//開始コード書き込み
			BINCODE code = BIN_CODE_SCRIPT;
			fwrite(&code, sizeof(BINCODE), 1, pFile);

			//モデル個数書き込み
			code = BIN_CODE_MODEL_NUM;
			int nNumAll = CXModel::GetNumAll();
			fwrite(&code, sizeof(BINCODE), 1, pFile);
			fwrite(&nNumAll, sizeof(int), 1, pFile);

			//モデルファイルパス書き込み
			code = BIN_CODE_MODEL_FILENAME;
			CXModel* pModel = CXModel::GetTop();	//リスト書き込み体制
			while (pModel != nullptr)
			{
				CXModel* pObjectNext = pModel->GetNext();

				fwrite(&code, sizeof(BINCODE), 1, pFile);						//コード
				fwrite(pModel->GetPath(), sizeof(char), STR_LENGTH, pFile);	//データ

				pModel = pObjectNext;
			}

			//モデル情報書き込み
			code = BIN_CODE_MODELSET;
			CObjectX* pObject = CObjectX::GetTop();
			while (pObject != nullptr)
			{
				CObjectX* pObjectNext = pObject->GetNext();

				fwrite(&code, sizeof(BINCODE), 1, pFile);				//コード
				fwrite(&pObject->GetPos(), sizeof(D3DXVECTOR3), 1, pFile);
				fwrite(&pObject->GetRot(), sizeof(D3DXVECTOR3), 1, pFile);

				//モデル種類番号化
				int nModelNum = 0;
				CXModel* pModel = CXModel::GetTop();
				while (pModel != nullptr && pModel != pObject->GetModel())
				{
					pModel = pModel->GetNext();
					nModelNum++;
				}
				fwrite(&nModelNum, sizeof(int), 1, pFile);

				pObject = pObjectNext;
			}

			//終了コード書き込み
			code = BIN_CODE_END_SCRIPT;
			fwrite(&code, sizeof(BINCODE), 1, pFile);

			fclose(pFile);
			return LOADRESULT::RES_OK;
		}
		else
		{//なぜか開けなかった（なんで？）
			return LOADRESULT::RES_ERR_FILE_NOTFOUND;
		}
	}
}