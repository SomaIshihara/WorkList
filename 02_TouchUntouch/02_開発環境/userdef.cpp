//======================================================
//
//���[�U�[��`�̏���[userdef.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "userdef.h"

//=================================
//�R���X�g���N�^
//=================================
CVariableManager::CVariableManager()
{
	for (int cnt = 0; cnt < VARIABLE_NUM; cnt++)
	{
		m_definedVariable[cnt] = nullptr;
	}
	m_nVariableNum = 0;
}

//=================================
//��`�ϐ�����
//=================================
void CVariableManager::Analysis(char* pCode)
{
	int nUseByte = 0;
	char* pType = nullptr;
	char* pName = nullptr;
	char* pDataRaw = nullptr;

	//���^���m�F
	pType = strtok(pCode, " =\n");

	//�ϐ���
	pName = strtok(nullptr, " =\n");

	//�ϐ��f�[�^
	pDataRaw = strtok(nullptr, " =\n");

	//�ϐ���`
	if (strcmp(pType, "int") == 0)
	{//int�^
		nUseByte = 4;

		int nData = 0;
		if (pDataRaw != nullptr)
		{
			nData = atoi(pDataRaw);
		}
		Definition(CVariable::Integer, pName, &nData);
	}
	else if (strcmp(pType, "float") == 0)
	{//float�^
		nUseByte = 4;

		float fData = 0;
		if (pDataRaw != nullptr)
		{
			fData = atof(pDataRaw);
		}
		Definition(CVariable::Float, pName, &fData);
	}
	else if (strcmp(pType, "bool") == 0)
	{//bool�^
		nUseByte = 1;

		char bData = 0x00;
		if (pDataRaw != nullptr)
		{
			bData = (strcmp(pDataRaw, "true") == 0) ? 0xff : 0x00;
		}
		Definition(CVariable::Boolean, pName, &bData);
	}
}

//=================================
//�ϐ���`
//=================================
void CVariableManager::Definition(const CVariable::TYPE type, const char* pName, void* pData)
{
	if (m_nVariableNum < VARIABLE_NUM)
	{
		//��`�p�ϐ����I�m��
		m_definedVariable[m_nVariableNum] = new CVariable::Variable;

		//�ϐ��^
		m_definedVariable[m_nVariableNum]->type = type;

		//�ϐ���
		int nLength = strlen(pName) + 1;
		m_definedVariable[m_nVariableNum]->pName = new char[nLength];
		strcpy(m_definedVariable[m_nVariableNum]->pName, pName);

		//�����l�i����΁j
		int nUseByte = 0;
		switch (type)
		{
		case CVariable::Integer:
			nUseByte = 4;
			break;
		case CVariable::Float:
			nUseByte = 4;
			break;
		case CVariable::Boolean:
			nUseByte = 1;
		}
		m_definedVariable[m_nVariableNum]->pData = new char[nUseByte];
		if (pData != nullptr)
		{
			memcpy(m_definedVariable[m_nVariableNum]->pData, pData, nUseByte);
		}

		//�����₷
		m_nVariableNum++;
	}
}

//=================================
//�S�j��
//=================================
void CVariableManager::ReleaseAll(void)
{
	for (int cnt = 0; cnt < m_nVariableNum; cnt++)
	{
		if (m_definedVariable[cnt] != nullptr)
		{
			delete m_definedVariable[cnt];
			m_definedVariable[cnt] = nullptr;
		}
	}
	m_nVariableNum = 0;
}

//=================================
//�ϐ��錾�i�ϐ������j
//=================================
CVariable* CVariableManager::Declaration(const char * pName, void * pData)
{
	for (int cnt = 0; cnt < m_nVariableNum; cnt++)
	{
		if (m_definedVariable != nullptr && strcmp(&m_definedVariable[cnt]->pName[0], pName) == 0)
		{
			CVariable* pVariable = new CVariable;

			if (pData != nullptr)
			{
				pVariable->Declaration(m_definedVariable[cnt]->type, &m_definedVariable[cnt]->pName[0], pData);
			}
			else
			{
				pVariable->Declaration(m_definedVariable[cnt]->type, &m_definedVariable[cnt]->pName[0], m_definedVariable[cnt]->pData);
			}

			return pVariable;
		}
	}

	return nullptr;
}

//=================================
//�ϐ���`�t�@�C���ǂݍ���
//=================================
void CVariableManager::ReadUserDefData(const char * pPath)
{
	FILE *pFile;
	char aCode[128];
	char *pSprit;
	bool bRead = false;
	int nCntInit = 0;	//�������J�E���^

	//�ǂݍ��݃t�@�C���ݒ�
	pFile = fopen(pPath, "r");

	//�G�z�u�����擾
	if (pFile != NULL)
	{
		while (1)
		{
			fgets(&aCode[0], 128, pFile);

			//�R�����g�A�E�g�`�F�b�N
			char *pCharPos = strchr(&aCode[0], '#');
			if (pCharPos != nullptr)
			{//strchr�̕Ԃ�l���ʂ�ۂł͂Ȃ�
				*pCharPos = '\0';
			}

			//�^�u����
			while (aCode[0] == '\t')
			{
				char aCodeBackup[128];
				strcpy(&aCodeBackup[0], &aCode[0]);
				strcpy(&aCode[0], &aCodeBackup[1]);
			}

			//������`�F�b�N
			if (aCode[0] == '{')
			{//�ǂݎ��J�n
				bRead = true;
			}
			else if (aCode[0] == '}')
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
				if (aCode[0] != '\0' && aCode[0] != '\n')
				{
					Analysis(&aCode[0]);
				}
			}
		}
	}
	else
	{
		assert(pFile != NULL);
	}

	//�t�@�C������
	fclose(pFile);
}

//=================================
//�ϐ��錾
//=================================
void CVariable::Declaration(const TYPE type, const char * pName, void * pData)
{
	//�ϐ��^�i�[
	m_variable.type = type;

	//�ϐ��T�C�Y�i�[
	switch (type)
	{
	case Integer:
		m_variable.nUseByte = 4;
		break;
	case Float:
		m_variable.nUseByte = 4;
		break;
	case Boolean:
		m_variable.nUseByte = 1;
	}

	//�ϐ����i�[
	m_variable.pName = new char[strlen(pName) + 1];
	strcpy(&m_variable.pName[0], pName);

	//�ϐ��T�C�Y�ݒ�
	m_variable.pData = new char[m_variable.nUseByte];

	//�ϐ��̒l������Α��
	if (pData != nullptr)
	{//���
		memcpy(m_variable.pData, pData, m_variable.nUseByte);
	}
}

//=================================
//�ϐ��ݒ�
//=================================
void CVariable::SetData(void * pData)
{
	switch (this->m_variable.type)
	{
	case CVariable::Integer:
		memcpy(m_variable.pData, (int*)pData, m_variable.nUseByte);
		break;
	case CVariable::Float:
		memcpy(m_variable.pData, (float*)pData, m_variable.nUseByte);
		break;
	case CVariable::Boolean:
	{
		char bData = (*(bool*)pData == true) ? 0xff : 0x00;
		memcpy(m_variable.pData, &bData, m_variable.nUseByte);
	}
		break;
	default:
		break;
	}
}

//=================================
//�ϐ��폜
//=================================
void CVariable::Release(void)
{
	if (m_variable.pName != nullptr)
	{
		delete m_variable.pName;
		m_variable.pName = nullptr;
	}
	if (m_variable.pData != nullptr)
	{
		delete m_variable.pData;
		m_variable.pData = nullptr;
	}

	delete this;
}
