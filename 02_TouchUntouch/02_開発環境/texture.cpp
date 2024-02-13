//======================================================
//
//�e�N�X�`���ۑ��N���X[texture.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include <stdio.h>

//�ÓI�����o�ϐ�
int CTexture::m_nNumAll = 0;

//�}�N��
#define TEXTURE_CODE_LENGTH	(128)	//�e�N�X�`���ǂݍ��ݕ����̒���
#define CODE_START			"SCRIPT_START"
#define CODE_END			"SCRIPT_END"
#define CODE_START_LOAD		"START_LOAD"
#define CODE_END_LOAD		"END_LOAD"
#define CODE_TEXTURE_NAME	"TEXTURE_NAME"
#define CODE_PATTERN_WIDTH	"PATTERN_WIDTH"
#define CODE_PATTERN_HEIGHT	"PATTERN_HEIGHT"

//=================================
//�R���X�g���N�^
//=================================
CTexture::CTexture()
{
	for (int cnt = 0; cnt < MAX_TEXTURE; cnt++)
	{//�S������ۂɂ���
		m_apTexture[cnt].pTexture = nullptr;
		m_apTexture[cnt].nPatternWidth = 0;
		m_apTexture[cnt].nPatternHeight = 0;
	}
}

//=================================
//�f�X�g���N�^
//=================================
CTexture::~CTexture()
{
}

//=================================
//���炩���ߓǂݍ���
//=================================
HRESULT CTexture::Load(const char* pPath)
{
	FILE* pFile;
	char aCode[TEXTURE_CODE_LENGTH];
	bool bRead = false;
	bool bLoad = false;
	char aPath[TEXTURE_CODE_LENGTH];
	int nPatWidth, nPatHeight;

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�ǂݍ��݃t�@�C���ݒ�
	pFile = fopen(pPath, "r");

	//�G�z�u�����擾
	if (pFile != nullptr)
	{
		while (1)
		{
			fgets(&aCode[0], TEXTURE_CODE_LENGTH, pFile);

			//�R�����g�A�E�g�`�F�b�N
			char *pCharPos = strchr(&aCode[0], '#');
			if (pCharPos != nullptr)
			{//strchr�̕Ԃ�l���ʂ�ۂł͂Ȃ�
				*pCharPos = '\0';
			}

			//�^�u����
			while (aCode[0] == '\t')
			{
				char aCodeBackup[TEXTURE_CODE_LENGTH];
				strcpy(&aCodeBackup[0], &aCode[0]);
				strcpy(&aCode[0], &aCodeBackup[1]);
			}

			//������`�F�b�N
			if (strncmp(&aCode[0], CODE_START, sizeof CODE_START - 1) == 0)
			{//�ǂݎ��J�n
				bRead = true;
			}
			else if (strncmp(&aCode[0], CODE_END, sizeof CODE_END - 1) == 0)
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
				if (bLoad == true)
				{
					if (strncmp(&aCode[0], CODE_END_LOAD, sizeof CODE_END_LOAD - 1) == 0)
					{
						//�e�N�X�`���ǂݍ���
						D3DXCreateTextureFromFile(pDevice, &aPath[0],
							&m_apTexture[m_nNumAll].pTexture);

						//�t�@�C���p�X�R�s�[
						strcpy(&m_aFilepath[m_nNumAll][0], &aPath[0]);

						//�p�^�[�����������
						m_apTexture[m_nNumAll].nPatternWidth = nPatWidth;
						m_apTexture[m_nNumAll].nPatternHeight = nPatHeight;

						//�������₷
						m_nNumAll++;
					}
					else if (strncmp(&aCode[0], CODE_TEXTURE_NAME, sizeof CODE_TEXTURE_NAME - 1) == 0)
					{
						char* pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�p�X�擾
						pSprit = strtok(nullptr, " =\n");

						//�^�u�����������Ă���Ƃ��������
						char *pCharPos = strchr(pSprit, '\t');
						if (pCharPos != nullptr)
						{//strchr�̕Ԃ�l���ʂ�ۂł͂Ȃ�
							*pCharPos = '\0';
						}

						//������R�s�[
						strcpy(&aPath[0], pSprit);
					}
					else if (strncmp(&aCode[0], CODE_PATTERN_WIDTH, sizeof CODE_PATTERN_WIDTH - 1) == 0)
					{
						char* pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�f�[�^
						pSprit = strtok(nullptr, " =\n");
						nPatWidth = atoi(pSprit);
						
					}
					else if (strncmp(&aCode[0], CODE_PATTERN_HEIGHT, sizeof CODE_PATTERN_HEIGHT - 1) == 0)
					{
						char* pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�f�[�^
						pSprit = strtok(nullptr, " =\n");
						nPatHeight = atoi(pSprit);
					}
				}
				else
				{
					if (strncmp(&aCode[0], CODE_START_LOAD, sizeof CODE_START_LOAD - 1) == 0)
					{
						bLoad = true;
					}
				}
			}
		}
	}
	else
	{
		return E_FAIL;
	}

	return S_OK;
}

//=================================
//�S���j��
//=================================
void CTexture::Unload(void)
{
	for (int cnt = 0; cnt < m_nNumAll; cnt++)
	{//�S���j��
		if (m_apTexture[cnt].pTexture != nullptr)
		{
			m_apTexture[cnt].pTexture->Release();
			m_apTexture[cnt].pTexture = nullptr;
		}
	}
	m_nNumAll = 0;	//�����Z�b�g
}

//=================================
//�ǉ����o�^
//=================================
int CTexture::Regist(const char * pPath, const int nPatWidth, const int nPatHeight)
{
	//�d���`�F�b�N
	for (int cnt = 0; cnt < m_nNumAll; cnt++)
	{//���镪������
		if (strcmp(&m_aFilepath[cnt][0], pPath) == 0)
		{//��v����
			return cnt;
		}
	}

	//�V�K�o�^
	if (m_nNumAll < MAX_TEXTURE)
	{//�e�N�X�`���ۑ����E�ȓ�
		//�f�o�C�X�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

		//�e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(pDevice, pPath,
			&m_apTexture[m_nNumAll].pTexture);

		//�t�@�C���p�X�R�s�[
		strcpy(&m_aFilepath[m_nNumAll][0], pPath);

		//�p�^�[�����������
		m_apTexture[m_nNumAll].nPatternWidth = nPatWidth;
		m_apTexture[m_nNumAll].nPatternHeight = nPatHeight;

		//�������₷
		m_nNumAll++;

		return m_nNumAll - 1;
	}
	else
	{//��������Ȃ�
		return -1;
	}
}

//=================================
//�e�N�X�`���擾
//=================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	if (m_nNumAll > nIdx && nIdx >= 0)
	{//�e�N�X�`�������ȓ�
		return m_apTexture[nIdx].pTexture;	//�e�N�X�`���|�C���^�Ԃ�
	}
	else
	{//����Ȃ��̂͂Ȃ�
		return nullptr;	//�Ԃ����̂Ȃ�ĂȂ�
	}
}

//=================================
//�e�N�X�`���p�^�[�����擾
//=================================
int CTexture::GetPatWidth(int nIdx)
{
	if (m_nNumAll > nIdx && nIdx >= 0)
	{//�e�N�X�`�������ȓ�
		return m_apTexture[nIdx].nPatternWidth;	//�e�N�X�`���|�C���^�Ԃ�
	}
	else
	{//����Ȃ��̂͂Ȃ�
		return 0;	//�Ԃ����̂Ȃ�ĂȂ�
	}
}

//=================================
//�e�N�X�`���p�^�[�������擾
//=================================
int CTexture::GetPatHeight(int nIdx)
{
	if (m_nNumAll > nIdx && nIdx >= 0)
	{//�e�N�X�`�������ȓ�
		return m_apTexture[nIdx].nPatternHeight;	//�e�N�X�`���|�C���^�Ԃ�
	}
	else
	{//����Ȃ��̂͂Ȃ�
		return 0;	//�Ԃ����̂Ȃ�ĂȂ�
	}
}

