//==========================================
//
//�t�@�C���ǂݍ��݃v���O����[file.cpp]
//Author:�Ό��D�n
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

//�R�[�h�֌W
#define CODE_STR_LENGTH		(1024)
#define FILEPATH_LENGTH	(256)
#define MAX_PARTS		(16)

//�ǂݎ���ԗ�
typedef enum
{
	//����
	READSTAT_NONE = 0,	//�������ĂȂ�

	//-���f���r���[���[-----------------------
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

	//--���[�V�����r���[���[------------------
	READSTAT_CHARACTERSET,
	READSTAT_PARTSSET,
	READSTAT_MOTIONSET,
	READSTAT_KEYSET,
	READSTAT_KEY,
	//----------------------------------------

	//--���H���b�V���X�N���v�g------------------
	READSTAT_VECTORSET,
	//----------------------------------------

	READSTAT_MAX
} READSTAT;

typedef enum
{
	TYPE_X = 0,		//CObjectX�g�p
	TYPE_BUILDING,	//CBuinding�g�p
	TYPE_MAX
} TYPE;

//�O���[�o��
READSTAT g_readStat = READSTAT_NONE;

//========================
//�t�@�C������������
//========================
void InitFile(void)
{
	g_readStat = READSTAT_NONE;
}

#if 0
//========================
//�}�b�v�ǂݍ��ݏ���
//========================
void LoadModelViewerFile(const char *path)
{
	FILE *pFile;
	char aCode[CODE_LENGTH];
	char *pSprit;
	bool bRead = false;
	int nCntInit = 0;	//�������J�E���^

	//�ǂݍ��݃f�[�^
	int nType = -1;
	D3DXVECTOR3 pos = IS_Utility::VEC3_ZERO, rot = IS_Utility::VEC3_ZERO;
	int nState = 0;
	bool bCollision = false, bShadow = false;

	float fWidth = CManager::FLOAT_ZERO, fHeight = CManager::FLOAT_ZERO;

	//�ǂݍ��݃t�@�C���ݒ�
	pFile = fopen(path, "r");

	//�G�z�u�����擾
	if (pFile != nullptr)
	{
		while (1)
		{
			fgets(&aCode[0], CODE_LENGTH, pFile);

			//�R�����g�A�E�g�`�F�b�N
			char *pCharPos = strchr(&aCode[0], '#');
			if (pCharPos != nullptr)
			{//strchr�̕Ԃ�l���ʂ�ۂł͂Ȃ�
				*pCharPos = '\0';
			}

			//�^�u����
			while (aCode[0] == '\t')
			{
				char aCodeBackup[CODE_LENGTH];
				strcpy(&aCodeBackup[0], &aCode[0]);
				strcpy(&aCode[0], &aCodeBackup[1]);
			}

			//������`�F�b�N
			if (strncmp(&aCode[0], CODE_SCRIPT, sizeof CODE_SCRIPT / sizeof(char) - 1) == 0)
			{//�ǂݎ��J�n
				bRead = true;
			}
			else if (strncmp(&aCode[0], CODE_END_SCRIPT, sizeof CODE_END_SCRIPT / sizeof(char) - 1) == 0)
			{//�ǂݎ��I��
				bRead = false;
				break;
			}
			else if (aCode[0] == EOF)
			{//EOF��������Ȃ�
				if (feof(pFile))
				{//����A�����EOF��
					bRead = false;
					break;
				}
			}
			else if (bRead == true)
			{//�ǂݎ��
				switch (g_readStat)
				{
				case READSTAT_NONE:	//�����擾
					//��������
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
					//�擾����
					else if (strncmp(&aCode[0], CODE_TEXTURE_FILENAME, sizeof CODE_TEXTURE_FILENAME / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�p�X�擾
						pSprit = strtok(nullptr, " =\n");

						//�^�u�����������Ă���Ƃ��������
						char *pCharPos = strchr(pSprit, '\t');
						if (pCharPos != nullptr)
						{//strchr�̕Ԃ�l���ʂ�ۂł͂Ȃ�
							*pCharPos = '\0';
						}

						//�e�N�X�`���ǂݍ���
						CManager::GetInstance()->GetInstance()->GetTexture()->Regist(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_MODEL_FILENAME, sizeof CODE_MODEL_FILENAME / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�p�X�擾
						pSprit = strtok(nullptr, " =\n");

						//�^�u�����������Ă���Ƃ��������
						char *pCharPos = strchr(pSprit, '\t');
						if (pCharPos != nullptr)
						{//strchr�̕Ԃ�l���ʂ�ۂł͂Ȃ�
							*pCharPos = '\0';
						}

						//���f���ǂݍ���
						CXModel::Load(pSprit);
					}
					break;
#if 0
				case READSTAT_CAMERASET:	//pvp�J�������擾
					if (strncmp(&aCode[0], CODE_END_CAMERASET, sizeof CODE_END_CAMERASET / sizeof(char) - 1) == 0)
					{
						//�J�����ݒ�
						InitSetCameraPos(g_readCamera.posV, g_readCamera.posR, g_counterReadCamera);
						g_readStat = READSTAT_NONE;
						g_counterReadCamera++;		//���Z
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readCamera.posV.x = IS_Utility::fatof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readCamera.posV.y = IS_Utility::fatof(pSprit);

						//Z���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readCamera.posV.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_REF, sizeof CODE_REF / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readCamera.posR.x = IS_Utility::fatof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readCamera.posR.y = IS_Utility::fatof(pSprit);

						//Z���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readCamera.posR.z = IS_Utility::fatof(pSprit);
					}
					break;
				case READSTAT_LIGHTSET:		//���C�g���擾
					if (strncmp(&aCode[0], CODE_END_LIGHTSET, sizeof CODE_END_LIGHTSET / sizeof(char) - 1) == 0)
					{
						//���C�g�ݒ�
						SetLight(g_counterReadLight, g_readLight);
						g_readStat = READSTAT_NONE;

						g_counterReadLight++;
					}
					else if (strncmp(&aCode[0], CODE_DIRECTION, sizeof CODE_DIRECTION / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//���u���ϐ��錾
						D3DXVECTOR3 vecDir;

						//X���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						vecDir.x = IS_Utility::fatof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						vecDir.y = IS_Utility::fatof(pSprit);

						//Z���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						vecDir.z = IS_Utility::fatof(pSprit);

						//�x�N�g�����K��
						D3DXVec3Normalize(&vecDir, &vecDir);

						//���
						g_readLight.Direction = vecDir;
					}
					else if (strncmp(&aCode[0], CODE_DIFFUSE, sizeof CODE_DIFFUSE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//��
						pSprit = strtok(nullptr, " =\n");
						g_readLight.Diffuse.r = IS_Utility::fatof(pSprit);

						//��
						pSprit = strtok(nullptr, " =\n");
						g_readLight.Diffuse.g = IS_Utility::fatof(pSprit);

						//��
						pSprit = strtok(nullptr, " =\n");
						g_readLight.Diffuse.b = IS_Utility::fatof(pSprit);

						//�A���t�@�l��1.0�Œ�
						g_readLight.Diffuse.a = 1.0f;
					}
					break;
				case READSTAT_SKYSET:		//����擾
					if (strncmp(&aCode[0], CODE_END_SKYSET, sizeof CODE_END_SKYSET / sizeof(char) - 1) == 0)
					{
						//��ݒ肵��
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_TEXTYPE, sizeof CODE_TEXTYPE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�擾
						pSprit = strtok(nullptr, " =\n");
						g_readsky.texType = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_MOVE, sizeof CODE_MOVE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�擾
						pSprit = strtok(nullptr, " =\n");
						g_readsky.fMove = IS_Utility::fatof(pSprit);
					}
					break;
				case READSTAT_MOUNTAINSET:	//�R���擾
					if (strncmp(&aCode[0], CODE_END_MOUNTAINSET, sizeof CODE_END_MOUNTAINSET / sizeof(char) - 1) == 0)
					{
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_TEXTYPE, sizeof CODE_TEXTYPE / sizeof(char) - 1) == 0)
					{
						//�擾
						pSprit = strtok(nullptr, " =\n");
						g_nMountainTexNum = atoi(pSprit);
					}
					break;
				case READSTAT_FIELDSET:		//�����擾
					if (strncmp(&aCode[0], CODE_END_FIELDSET, sizeof CODE_END_FIELDSET / sizeof(char) - 1) == 0)
					{
						//�n�ʐݒ�
						SetMeshField(g_readmeshfield.texType, g_readmeshfield.mf);
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_TEXTYPE, sizeof CODE_TEXTYPE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�擾
						pSprit = strtok(nullptr, " =\n");
						g_readmeshfield.texType = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readmeshfield.mf.pos.x = IS_Utility::fatof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readmeshfield.mf.pos.y = IS_Utility::fatof(pSprit);

						//Z���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readmeshfield.mf.pos.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readmeshfield.mf.rot.x = IS_Utility::fatof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readmeshfield.mf.rot.y = IS_Utility::fatof(pSprit);

						//Z���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readmeshfield.mf.rot.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_SIZE, sizeof CODE_SIZE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�T�C�Y�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readmeshfield.mf.fRadius = IS_Utility::fatof(pSprit);
					}
					break;
				case READSTAT_WALLSET:		//�Ǐ��擾
					if (strncmp(&aCode[0], CODE_END_WALLSET, sizeof CODE_END_WALLSET / sizeof(char) - 1) == 0)
					{
						//�ǐ�������
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_TEXTYPE, sizeof CODE_TEXTYPE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�擾
						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.texType = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�ʒu�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.pos.x = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.pos.y = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.pos.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�����ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.rot.x = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.rot.y = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.rot.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_BLOCK, sizeof CODE_BLOCK / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�������ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.blockX = atoi(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.blockZ = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_SIZE, sizeof CODE_SIZE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�T�C�Y�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.sizeX = atoi(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readMeshWall.sizeZ = atoi(pSprit);
					}
					break;
#endif
				case READSTAT_MODELSET:		//���f�����擾
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
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//��ޓǂݎ��
						pSprit = strtok(nullptr, " =\n");
						nType = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						pos.x = IS_Utility::fatof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						pos.y = IS_Utility::fatof(pSprit);

						//Z���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						pos.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						rot.x = (IS_Utility::fatof(pSprit) / 180) * D3DX_PI;

						//Y���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						rot.y = (IS_Utility::fatof(pSprit) / 180) * D3DX_PI;

						//Z���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						rot.z = (IS_Utility::fatof(pSprit) / 180) * D3DX_PI;
					}
					else if (strncmp(&aCode[0], CODE_STATE, sizeof CODE_STATE / sizeof(char) - 1) == 0)
					{//��Ԏw��
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//��Ԑݒ�
						pSprit = strtok(nullptr, " =\n");
						nState = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_COLLISION, sizeof CODE_COLLISION / sizeof(char) - 1) == 0)
					{//0�Ȃ瓖���蔻�薳��
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�����蔻��ݒ�
						pSprit = strtok(nullptr, " =\n");
						bCollision = (atoi(pSprit) >= 1) ? true : false;
					}
					else if (strncmp(&aCode[0], CODE_SHADOW, sizeof CODE_SHADOW / sizeof(char) - 1) == 0)
					{//0�Ȃ�e���g�p���Ȃ�
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						pSprit = strtok(nullptr, " =\n");
						bShadow = (atoi(pSprit) >= 1) ? true : false;
					}
					break;
				case READSTAT_BILLBOARDSET:	//�r���{�[�h���擾
					if (strncmp(&aCode[0], CODE_END_BILLBOARDSET, sizeof CODE_END_BILLBOARDSET / sizeof(char) - 1) == 0)
					{
						//�r���{�[�h�ݒ�
						CObjectBillboard::Create(pos, IS_Utility::VEC3_ZERO, fWidth, fHeight, nType);

						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_TEXTYPE, sizeof CODE_TEXTYPE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//��ޓǂݎ��
						pSprit = strtok(nullptr, " =\n");
						nType = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�ʒu�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						pos.x = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						pos.y = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						pos.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_SIZE, sizeof CODE_SIZE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�T�C�Y�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						fWidth = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						fWidth = IS_Utility::fatof(pSprit);
					}
#if 0
					else if (strncmp(&aCode[0], CODE_ORIGIN, sizeof CODE_ORIGIN / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//���Ɏg���̂��킩��Ȃ����̓ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readbillboard.originX = atoi(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readbillboard.originZ = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_BLEND, sizeof CODE_BLEND / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�������[�h�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readbillboard.blend = atoi(pSprit);
					}
#endif
					else if (strncmp(&aCode[0], CODE_SHADOW, sizeof CODE_SHADOW / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�e�g�p�L���ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						bShadow = (atoi(pSprit) >= 1) ? true : false;
					}
					break;
#if 0
				case READSTAT_PLAYERSET:	//�v���C���[���f�����擾
					if (strncmp(&aCode[0], CODE_END_PLAYERSET, sizeof CODE_END_PLAYERSET / sizeof(char) - 1) == 0)
					{
						//�v���C���[���f���擾����
						g_readStat = READSTAT_NONE;

						//���Z
						g_counterReadAnimal++;
					}
					else if (strncmp(&aCode[0], CODE_MOTION_FILENAME, sizeof CODE_MOTION_FILENAME / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�擾
						pSprit = strtok(nullptr, " =\n");
						strcpy(&g_readPlayermodel[g_counterReadAnimal].motionFileName[0], pSprit);

						//�^�u�����������Ă���Ƃ��������
						char *pCharPos = strchr(&g_readPlayermodel[g_counterReadAnimal].motionFileName[0], '\t');
						if (pCharPos != nullptr)
						{//strchr�̕Ԃ�l���ʂ�ۂł͂Ȃ�
							*pCharPos = '\0';
						}
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�ʒu�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						g_readPlayermodel[g_counterReadAnimal].pos.x = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readPlayermodel[g_counterReadAnimal].pos.y = IS_Utility::fatof(pSprit);

						pSprit = strtok(nullptr, " =\n");
						g_readPlayermodel[g_counterReadAnimal].pos.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�����ǂݎ��
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

	//�t�@�C������
	fclose(pFile);
}
#endif
//========================
//���[�V�����ǂݍ��ݏ���
//����1:���[�V�����r���[���[�̐ݒ�t�@�C���̃p�X
//����2:���ꂽ�����f���\���̂̃|�C���^
//========================
bool LoadMotionViewerFile(const char *path, CModel*** pppModel, CMotion* pMotion, int* pNumModel)
{
	FILE *pFile;
	char aCode[CODE_STR_LENGTH];
	char *pSprit;
	bool bRead = false;

	//�ǂݎ�������
	char aFilePath[16][FILEPATH_LENGTH] = {};	//���f���p�X
	int nNumModelPath = 0;						//�ǂݎ�������f���p�X��
	int nIdx = -1;								//PARTSSET:�g�p���郂�f��
	int nSetModelNum = 0;						//PARTSSET:�ݒ肵�����f����
	int nParent = -1;							//PARTSSET:�e
	D3DXVECTOR3 posOffset, rotOffset;			//PARTSSET:�I�t�Z�b�g�̈ʒu����

	CMotion::INFO info;
	int nKeyInfo = 0, nKey = 0;		//�L�[���E�L�[

	//���[�V�������
	//�ǂݍ��݃t�@�C���ݒ�
	pFile = fopen(path, "r");

	//�G�z�u�����擾
	if (pFile != nullptr)
	{
		while (1)
		{
			fgets(&aCode[0], CODE_STR_LENGTH, pFile);

			//�R�����g�A�E�g�`�F�b�N
			char *pCharPos = strchr(&aCode[0], '#');
			if (pCharPos != nullptr)
			{//strchr�̕Ԃ�l���ʂ�ۂł͂Ȃ�
				*pCharPos = '\0';
			}

			//�^�u����
			while (aCode[0] == '\t')
			{
				char aCodeBackup[CODE_STR_LENGTH];
				strcpy(&aCodeBackup[0], &aCode[0]);
				strcpy(&aCode[0], &aCodeBackup[1]);
			}

			//������`�F�b�N
			if (strncmp(&aCode[0], CODE_SCRIPT, sizeof CODE_SCRIPT / sizeof(char) - 1) == 0)
			{//�ǂݎ��J�n
				bRead = true;
			}
			else if (strncmp(&aCode[0], CODE_END_SCRIPT, sizeof CODE_END_SCRIPT / sizeof(char) - 1) == 0)
			{//�ǂݎ��I��
				bRead = false;
				break;
			}
			else if (aCode[0] == EOF)
			{//EOF��������Ȃ�
				if (feof(pFile))
				{//����A�����EOF��
					bRead = false;
					break;
				}
			}
			else if (bRead == true)
			{//�ǂݎ��
				switch (g_readStat)
				{
				case READSTAT_NONE:	//�����擾
#if 0
					if (strncmp(&aCode[0], CODE_NUM_MODEL, sizeof CODE_NUM_MODEL / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						pSprit = strtok(nullptr, " =\n");	//�ǂݎ��
						
					}
#endif
					if (strncmp(&aCode[0], CODE_MODEL_FILENAME, sizeof CODE_MODEL_FILENAME / sizeof(char) - 1) == 0)
					{
						if (nNumModelPath < MAX_PARTS)
						{
							pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

							//���
							strcpy(&aFilePath[nNumModelPath][0], strtok(nullptr, " =\n"));
							//�^�u�����������Ă���Ƃ��������
							char *pCharPos = strchr(&aFilePath[nNumModelPath][0], '\t');
							if (pCharPos != nullptr)
							{//strchr�̕Ԃ�l���ʂ�ۂł͂Ȃ�
								*pCharPos = '\0';
							}

							//���Z
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

						//��荞�ݗp�ϐ��̓��I�m��
						for (int cnt = 0; cnt < KEYINFO_NUM; cnt++)
						{
							info.m_aKeyInfo[cnt].m_pKey = new CMotion::KEY[*pNumModel];
						}
					}
					break;
				case READSTAT_CHARACTERSET:		//���f�����擾
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
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�ړ��ʎ擾
						pSprit = strtok(nullptr, " =\n");
						
					}
					else if (strncmp(&aCode[0], CODE_JUMP, sizeof CODE_JUMP / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�W�����v�ʎ擾
						pSprit = strtok(nullptr, " =\n");
						
					}
					else if (strncmp(&aCode[0], CODE_RADIUS, sizeof CODE_RADIUS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//���a�擾
						pSprit = strtok(nullptr, " =\n");
						
					}
#endif
					else if (strncmp(&aCode[0], CODE_NUM_PARTS, sizeof CODE_NUM_PARTS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�p�[�c���擾
						pSprit = strtok(nullptr, " =\n");
						*pNumModel = atoi(pSprit);

						//�p�[�c���ɉ����ă��f���z��𓮓I�m��
						*pppModel = new CModel*[*pNumModel];

						//���[�V�������L�[�𓮓I�m��
						pMotion->SetModel(*pppModel, *pNumModel);
					}
					break;
				case READSTAT_PARTSSET:
					if (strncmp(&aCode[0], CODE_END_PARTSSET, sizeof CODE_END_PARTSSET / sizeof(char) - 1) == 0)
					{
						//����
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

						//�L�����N�^�[�ݒ��Ԃɖ߂�
						g_readStat = READSTAT_CHARACTERSET;
					}
					else if (strncmp(&aCode[0], CODE_INDEX, sizeof CODE_INDEX / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�ԍ��擾
						pSprit = strtok(nullptr, " =\n");
						nIdx = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_PARENT, sizeof CODE_PARENT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�e�ԍ��擾
						pSprit = strtok(nullptr, " =\n");
						nParent = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						posOffset.x = IS_Utility::fatof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						posOffset.y = IS_Utility::fatof(pSprit);

						//Z���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						posOffset.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						rotOffset.x = IS_Utility::fatof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						rotOffset.y = IS_Utility::fatof(pSprit);

						//Z���W�ǂݎ��
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
						//���[�V�����ݒ�
						pMotion->SetInfo(info);
						nKeyInfo = 0;
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_LOOP, sizeof CODE_LOOP / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//���[�v�ۓǂݎ��
						pSprit = strtok(nullptr, " =\n");
						info.m_bLoop = atoi(pSprit) == 1 ? true : false;
					}
					else if (strncmp(&aCode[0], CODE_NUM_KEY, sizeof CODE_NUM_KEY / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�L�[���ǂݎ��
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
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�t���[�����ǂݎ��
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
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						info.m_aKeyInfo[nKeyInfo].m_pKey[nKey].m_fPosX = IS_Utility::fatof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						info.m_aKeyInfo[nKeyInfo].m_pKey[nKey].m_fPosY = IS_Utility::fatof(pSprit);

						//Z���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						info.m_aKeyInfo[nKeyInfo].m_pKey[nKey].m_fPosZ = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X�����ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						info.m_aKeyInfo[nKeyInfo].m_pKey[nKey].m_fRotX = IS_Utility::fatof(pSprit);

						//Y�����ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						info.m_aKeyInfo[nKeyInfo].m_pKey[nKey].m_fRotY = IS_Utility::fatof(pSprit);

						//Z�����ǂݎ��
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

	//�t�@�C������
	fclose(pFile);

	return true;
}

//========================
//���H���b�V���ǂݍ��ݏ���
//========================
CMeshRoad* LoadRoadScriptFile(const char* pPath)
{
	FILE* pFile;
	char aCode[CODE_STR_LENGTH];
	char* pSprit;
	bool bRead = false;

	//�ǂݎ�������
	D3DXVECTOR3 pos, rot;
	pos = rot = IS_Utility::VEC3_ZERO;
	float fLength = 1.0f;
	std::vector<IS_Utility::Utility_Vector3> vVector;

	//���[�V�������
	//�ǂݍ��݃t�@�C���ݒ�
	pFile = fopen(pPath, "r");

	//�G�z�u�����擾
	if (pFile != nullptr)
	{
		while (1)
		{
			fgets(&aCode[0], CODE_STR_LENGTH, pFile);

			//�R�����g�A�E�g�`�F�b�N
			char* pCharPos = strchr(&aCode[0], '#');
			if (pCharPos != nullptr)
			{//strchr�̕Ԃ�l���ʂ�ۂł͂Ȃ�
				*pCharPos = '\0';
			}

			//�^�u����
			while (aCode[0] == '\t')
			{
				char aCodeBackup[CODE_STR_LENGTH];
				strcpy(&aCodeBackup[0], &aCode[0]);
				strcpy(&aCode[0], &aCodeBackup[1]);
			}

			//������`�F�b�N
			if (strncmp(&aCode[0], CODE_SCRIPT, sizeof CODE_SCRIPT / sizeof(char) - 1) == 0)
			{//�ǂݎ��J�n
				bRead = true;
			}
			else if (strncmp(&aCode[0], CODE_END_SCRIPT, sizeof CODE_END_SCRIPT / sizeof(char) - 1) == 0)
			{//�ǂݎ��I��
				bRead = false;
				break;
			}
			else if (aCode[0] == EOF)
			{//EOF��������Ȃ�
				if (feof(pFile))
				{//����A�����EOF��
					bRead = false;
					break;
				}
			}
			else if (bRead == true)
			{//�ǂݎ��
				switch (g_readStat)
				{
				case READSTAT_NONE:	//�����擾
					if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						pos.x = IS_Utility::fatof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						pos.y = IS_Utility::fatof(pSprit);

						//Z���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						pos.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						rot.x = IS_Utility::fatof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						rot.y = IS_Utility::fatof(pSprit);

						//Z���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						rot.z = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_LENGTH, sizeof CODE_LENGTH - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						fLength = IS_Utility::fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_SET_VECTOR, sizeof CODE_SET_VECTOR - 1) == 0)
					{
						g_readStat = READSTAT_VECTORSET;
					}
					break;
				case READSTAT_VECTORSET:		//�x�N�g���擾
					if (strncmp(&aCode[0], CODE_END_SET_VECTOR, sizeof CODE_END_SET_VECTOR - 1) == 0)
					{
						g_readStat = READSTAT_NONE;
					}
					else if (strncmp(&aCode[0], CODE_VECTOR, sizeof CODE_VECTOR - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						IS_Utility::Utility_Vector3 vec;

						//X���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						vec.x = IS_Utility::fatof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						vec.y = IS_Utility::fatof(pSprit);

						//Z���W�ǂݎ��
						pSprit = strtok(nullptr, " =\n");
						vec.z = IS_Utility::fatof(pSprit);

						//�Ԃ�����
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

	//�t�@�C������
	fclose(pFile);

	//���H����
	CMeshRoad* pMeshRoad = CMeshRoad::Create(pos, rot, fLength, vVector);

	return pMeshRoad;
}
