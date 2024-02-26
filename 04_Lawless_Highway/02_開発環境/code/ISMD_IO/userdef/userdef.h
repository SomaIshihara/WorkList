//======================================================
//
//���[�U�[��`�̏����̃w�b�_[userdef.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _USERDEF_H_
#define _USERDEF_H_

#define VARIABLE_NUM	(32)	//�ϐ���`�ő吔

//�ϐ��N���X�i�P�̗��p�j
class CVariable
{
public:
	//�^�\����
	enum TYPE
	{
		Integer = 0,
		Float,
		Boolean,
	};

	//�ϐ��\����
	struct Variable
	{
		TYPE type;		//�^��
		int nUseByte;	//�ϐ��g�p�o�C�g��
		char* pName;	//�ϐ����i���I�m�ہj
		char* pData;	//�f�[�^�i���I�m�ہj
	};

	//�R���X�g���N�^�E�f�X�g���N�^
	CVariable() { m_variable = { Integer,0,nullptr,nullptr }; }
	~CVariable(){}

	void Declaration(const TYPE type, const char* pName, void* pData = nullptr);		//�錾
	void* GetData(void) { return m_variable.pData; }		//�f�[�^�擾
	char* GetName(void) { return m_variable.pName; }		//���O�擾
	TYPE GetType(void) { return m_variable.type; }			//�^�擾
	void SetData(void* pData);	//�ݒ�
	void Release(void);
private:
	Variable m_variable;	//�ϐ�
};

//�ϐ��}�l�N���X
class CVariableManager
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CVariableManager();
	~CVariableManager() {}

	//�e�폈��
	void ReadUserDefData(const char* pPath);
	void Definition(const CVariable::TYPE type, const char* pName, void* pData = nullptr);	//��`
	void ReleaseAll(void);
	CVariable* Declaration(const char* pName, void* pData = nullptr);		//�錾
	CVariable::Variable** GetDefinedVariable(void) { return &m_definedVariable[0]; }
	int GetDefinedNum(void) { return m_nVariableNum; }
	void Analysis(char* pCode);								//1�s�ǂݍ���ŕ���

private:
	CVariable::Variable* m_definedVariable[VARIABLE_NUM];	//��`�ς݂̕ϐ�
	int m_nVariableNum;										//��`�ς݂̕ϐ��̌�
};

#endif // !_USERDEF_H_
