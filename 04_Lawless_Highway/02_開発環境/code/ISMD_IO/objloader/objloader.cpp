//======================================================
//
//�I�u�W�F�N�g�ǂݍ��ݏ���[objloader.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "objloader.h"
#include "..\..\IS_Bace\_Core\texture\texture.h"
#include "..\..\IS_Bace\_Core\xmodel\xmodel.h"
#include "..\..\IS_Bace\_Core\_object\object_x\objectX.h"
#include "..\userdef\userdef.h"
#include <string>

//========================
//ISMD�`���ǂݏ������O���
//========================
namespace ISMD_IO
{
	//========================
	//�f�[�^�ǂݍ���
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
		{//�J����
			while (1)
			{
				fread(&code, sizeof(BINCODE), 1, pFile);

				//������`�F�b�N
				if (code == BIN_CODE_SCRIPT)
				{//�ǂݎ��J�n
					bRead = true;
				}
				else if (code == BIN_CODE_END_SCRIPT)
				{//�ǂݎ��I��
					bRead = false;
					break;
				}
				else if (bRead == true)
				{//�ǂݎ��
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

						//���f���p�X�ǂݎ��i�����o���p�Ɏg���j
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

						//���I�u�W�F�N�g����
						CObjectX* pObject = CObjectX::Create(pos, rot, pModel);
					}
					else if (code == BIN_CODE_USERDEF)
					{
						//�ϐ���`�@�\�p�~
					}
				}
			}

			//�ǂݍ��݂Ɏg�p�������I�m�ەϐ���j��
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
		{//�J���Ȃ������i�t�@�C���Ȃ��񂶂�ˁH�j
			return LOADRESULT::RES_ERR_FILE_NOTFOUND;
		}
	}

	//========================
	//�f�[�^��������
	//========================
	LOADRESULT SaveData(const char* pPath)
	{
		FILE* pFile;

		pFile = fopen(pPath, "wb");

		if (pFile != nullptr)
		{//���ʂɊJ����
			//�J�n�R�[�h��������
			BINCODE code = BIN_CODE_SCRIPT;
			fwrite(&code, sizeof(BINCODE), 1, pFile);

			//���f������������
			code = BIN_CODE_MODEL_NUM;
			int nNumAll = CXModel::GetNumAll();
			fwrite(&code, sizeof(BINCODE), 1, pFile);
			fwrite(&nNumAll, sizeof(int), 1, pFile);

			//���f���t�@�C���p�X��������
			code = BIN_CODE_MODEL_FILENAME;
			CXModel* pModel = CXModel::GetTop();	//���X�g�������ݑ̐�
			while (pModel != nullptr)
			{
				CXModel* pObjectNext = pModel->GetNext();

				fwrite(&code, sizeof(BINCODE), 1, pFile);						//�R�[�h
				fwrite(pModel->GetPath(), sizeof(char), STR_LENGTH, pFile);	//�f�[�^

				pModel = pObjectNext;
			}

			//���f����񏑂�����
			code = BIN_CODE_MODELSET;
			CObjectX* pObject = CObjectX::GetTop();
			while (pObject != nullptr)
			{
				CObjectX* pObjectNext = pObject->GetNext();

				fwrite(&code, sizeof(BINCODE), 1, pFile);				//�R�[�h
				fwrite(&pObject->GetPos(), sizeof(D3DXVECTOR3), 1, pFile);
				fwrite(&pObject->GetRot(), sizeof(D3DXVECTOR3), 1, pFile);

				//���f����ޔԍ���
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

			//�I���R�[�h��������
			code = BIN_CODE_END_SCRIPT;
			fwrite(&code, sizeof(BINCODE), 1, pFile);

			fclose(pFile);
			return LOADRESULT::RES_OK;
		}
		else
		{//�Ȃ����J���Ȃ������i�Ȃ�ŁH�j
			return LOADRESULT::RES_ERR_FILE_NOTFOUND;
		}
	}
}