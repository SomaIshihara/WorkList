//======================================================
//
//�I�u�W�F�N�g�ǂݍ��ݏ���[objloader.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "objloader.h"
#include "texture.h"
#include "xmodel.h"
#include "objectX.h"
#include "userdef.h"
#include <string>

//�ǉ��I�u�W�F�N�g
#include "block3D.h"
#include "switch.h"
#include "goal.h"
#include "item.h"
#include "tutorialobj.h"

//�ÓI�����o�ϐ�
const int CObjLoader::STR_LENGTH = 256;

//========================
//�f�[�^�ǂݍ���
//========================
CObjLoader::LOADRESULT CObjLoader::LoadData(const char * pPath)
{
	FILE* pFile;
	BINCODE code;
	bool bRead = false;
	char** ppFilePath = nullptr;
	int nReadedModel = 0;
	CVariableManager* pVariableManager = CManager::GetInstance()->GetVariableManager();

	pFile = fopen(pPath, "rb");

	if (pFile != nullptr)
	{//�J����
		//��`�ϐ�������
		pVariableManager->ReleaseAll();

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
					int nNumAll;
					fread(&nNumAll, sizeof(int), 1, pFile);
					ppFilePath = new char*[nNumAll];
				}
				else if (code == BIN_CODE_MODEL_FILENAME)
				{
					char aPath[STR_LENGTH];
					fread(&aPath[0], sizeof(char), STR_LENGTH, pFile);
					CXModel::Load(&aPath[0]);

					//���f���p�X�ǂݎ��i�����o���p�Ɏg���j
					ppFilePath[nReadedModel] = new char[strlen(&aPath[0]) + 1];
					strcpy(ppFilePath[nReadedModel], &aPath[0]);
					nReadedModel++;
				}
				else if (code == BIN_CODE_MODELSET)
				{
					D3DXVECTOR3 pos, rot;
					int nModelNum = -1;
					CXModel* pModel = nullptr;
					fread(&pos, sizeof(D3DXVECTOR3), 1, pFile);
					fread(&rot, sizeof(D3DXVECTOR3), 1, pFile);
					fread(&nModelNum, sizeof(int), 1, pFile);
					pModel = CXModel::Load(ppFilePath[nModelNum]);

					//���I�u�W�F�N�g����
					CObjectX* pObject = CObjectX::Create(pos, rot, pModel);

					//�ǉ��ϐ��ǂݍ���
					for (int cnt = 0; cnt < pVariableManager->GetDefinedNum(); cnt++)
					{
						char aVal[STR_LENGTH] = "";
						fread(&aVal[0], sizeof(char), STR_LENGTH, pFile);
						char* pName = strtok(&aVal[0], " =\n");
						char* pValue = strtok(nullptr, " =\n");

						//�^�ǂݍ���
						switch (pObject->GetVariable()[cnt]->GetType())
						{
						case CVariable::Integer:
						{
							int nData = atoi(pValue);
							pObject->GetVariable()[cnt]->SetData(&nData);
						}
						break;
						case CVariable::Float:
						{
							float fData = 0.0f;
							pObject->GetVariable()[cnt]->SetData(&fData);
						}
						break;
						case CVariable::Boolean:
						{
							char bData = (strcmp(pValue, "true") == 0) ? 0xff : 0x00;
							pObject->GetVariable()[cnt]->SetData(&bData);
						}
							break;
						default:
							assert(false);
							break;
						}
					}

					//�ǉ����ɉ����ĕύX
					int nType = *(int*)pObject->GetVariable()[0]->GetData();		//�I�u�W�F�N�g���
					int nSubType = *(int*)pObject->GetVariable()[1]->GetData();		//���̃I�u�W�F�N�g�̎��

					if (nType == OBJTYPE_BLOCK)
					{//�u���b�N
						CBlock3D::Create(pObject->GetPos(), (CBlock3D::TYPE)nSubType);	//�V�����I�u�W�F�N�g�z�u
						pObject->Uninit();												//���I�u�W�F�N�g�j��
					}
					else if (nType == OBJTYPE_SWITCH)
					{
						CSwitch::Create(pObject->GetPos(), (CSwitch::TYPE)nSubType);	//�V�����I�u�W�F�N�g�z�u
						pObject->Uninit();												//���I�u�W�F�N�g�j��
					}
					else if (nType == OBJTYPE_GOAL)
					{
						CGoal::Create(pObject->GetPos());	//�V�����I�u�W�F�N�g�z�u
						pObject->Uninit();					//���I�u�W�F�N�g�j��
					}
					else if (nType == OBJTYPE_ITEM)
					{
						CItem::Create(pObject->GetPos(), CManager::VEC3_ZERO);	//�V�����I�u�W�F�N�g�z�u
						pObject->Uninit();										//���I�u�W�F�N�g�j��
					}
					else if (nType == OBJTYPE_TUTORIALOBJ)
					{
						CTutorialObj::Create(pObject->GetPos(), nSubType);	//�V�����I�u�W�F�N�g�z�u
						pObject->Uninit();									//���I�u�W�F�N�g�j��
					}
				}
				else if (code == BIN_CODE_USERDEF)
				{
					char aDefVariableStr[STR_LENGTH];

					fread(&aDefVariableStr[0], sizeof(char), STR_LENGTH, pFile);

					pVariableManager->Analysis(&aDefVariableStr[0]);
				}
			}
		}

		fclose(pFile);
		return RES_OK;
	}
	else
	{//�J���Ȃ������i�t�@�C���Ȃ��񂶂�ˁH�j
		return RES_ERR_FILE_NOTFOUND;
	}
}

//========================
//�f�[�^��������
//========================
CObjLoader::LOADRESULT CObjLoader::SaveData(const char * pPath)
{
	FILE* pFile;

	pFile = fopen(pPath, "wb");
	
	if (pFile != nullptr)
	{//���ʂɊJ����
		//�J�n�R�[�h��������
		BINCODE code = BIN_CODE_SCRIPT;
		fwrite(&code, sizeof(BINCODE), 1, pFile);

		//��`�ϐ��擾
		CVariableManager* pVariableManager = CManager::GetInstance()->GetVariableManager();
		CVariable::Variable** ppDefined = pVariableManager->GetDefinedVariable();
		for (int cnt = 0; cnt < pVariableManager->GetDefinedNum(); cnt++)
		{
			//���[�U�[��`�ϐ��������݊J�n
			code = BIN_CODE_USERDEF;
			fwrite(&code, sizeof(BINCODE), 1, pFile);

			char aDefVariableStr[STR_LENGTH] = "";

			//�^��������
			switch (ppDefined[cnt]->type)
			{
			case CVariable::Integer:
			{
				strcat(&aDefVariableStr[0], "int ");

				//�ϐ�����������
				strcat(&aDefVariableStr[0], &ppDefined[cnt]->pName[0]);

				//�����l��������
				strcat(&aDefVariableStr[0], " = ");
				int nData = 0;
				nData = *(int*)ppDefined[cnt]->pData;
				strcat(&aDefVariableStr[0], std::to_string(nData).c_str());
			}
				break;
			case CVariable::Float:
			{
				strcat(&aDefVariableStr[0], "float ");

				//�ϐ�����������
				strcat(&aDefVariableStr[0], &ppDefined[cnt]->pName[0]);

				//�����l��������
				strcat(&aDefVariableStr[0], " = ");
				float fData = 0;
				fData = *(float*)ppDefined[cnt]->pData;
				strcat(&aDefVariableStr[0], std::to_string(fData).c_str());
			}
				break;
			case CVariable::Boolean:
				strcat(&aDefVariableStr[0], "bool ");

				//�ϐ�����������
				strcat(&aDefVariableStr[0], &ppDefined[cnt]->pName[0]);

				//�����l��������
				strcat(&aDefVariableStr[0], " = ");
				strcat(&aDefVariableStr[0], ((bool)ppDefined[cnt]->pData == true) ? "true" : "false");
				break;
			default:
				assert(false);
				break;
			}

			//�t�@�C���ɏ�������
			fwrite(&aDefVariableStr[0], sizeof(char), STR_LENGTH, pFile);
		}

		//���f������������
		code = BIN_CODE_MODEL_NUM;
		int nNumAll = CXModel::GetNumAll();
		fwrite(&code, sizeof(BINCODE), 1, pFile);
		fwrite(&nNumAll,sizeof(int),1,pFile);

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

			//�ǉ��ϐ���������
			for (int cnt = 0; cnt < pVariableManager->GetDefinedNum(); cnt++)
			{
				char aVal[STR_LENGTH] = "";

				strcat(&aVal[0], pObject->GetVariable()[cnt]->GetName());	//�ϐ���
				strcat(&aVal[0], " = ");	//=

				//�l��������
				switch (pObject->GetVariable()[cnt]->GetType())
				{
				case CVariable::Integer:
				{
					//�����l��������
					int nData = 0;
					nData = *(int*)pObject->GetVariable()[cnt]->GetData();
					strcat(&aVal[0], std::to_string(nData).c_str());
				}
				break;
				case CVariable::Float:
				{
					//�����l��������
					float fData = 0;
					fData = *(float*)pObject->GetVariable()[cnt]->GetData();
					strcat(&aVal[0], std::to_string(fData).c_str());
				}
				break;
				case CVariable::Boolean:
					//�����l��������
					strcat(&aVal[0], (*(unsigned char*)pObject->GetVariable()[cnt]->GetData() == 0xff) ? "true" : "false");
					break;
				default:
					assert(false);
					break;
				}
				fwrite(&aVal[0], sizeof(char), STR_LENGTH, pFile);
			}

			pObject = pObjectNext;
		}

		//�I���R�[�h��������
		code = BIN_CODE_END_SCRIPT;
		fwrite(&code, sizeof(BINCODE), 1, pFile);

		fclose(pFile);
		return RES_OK;
	}
	else
	{//�Ȃ����J���Ȃ������i�Ȃ�ŁH�j
		return RES_ERR_FILE_NOTFOUND;
	}
}