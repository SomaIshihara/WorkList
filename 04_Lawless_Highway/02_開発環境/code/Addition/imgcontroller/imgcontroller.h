//==========================================
//
//���z�R���g���[��[imgcontroller.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _IMG_CONTROLLER_H_
#define _IMG_CONTROLLER_H_

//���̓C���^�t�F�[�X
__interface IController
{
	float Handle(void) = 0;
	bool Brake(void) = 0;
	bool Nitro(void) = 0;
};

//���z�R���g���[���N���X
class CImgController
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CImgController(IController* pInput) { m_pInput = pInput; }
	~CImgController() { delete m_pInput; }

	//���͎擾
	float Handle(void) { return m_pInput->Handle(); }
	bool Brake(void) { return m_pInput->Brake(); }
	bool Nitro(void) { return m_pInput->Nitro(); }
private:
	IController* m_pInput;
};


//�L�[�{�[�h���̓N���X
class CControllerKB : public IController
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CControllerKB(){}
	~CControllerKB(){}

	//���͎擾
	float Handle(void);
	bool Brake(void);
	bool Nitro(void);
};

//�Q�[���p�b�h���̓N���X
class CControllerGP : public IController
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CControllerGP(){}
	~CControllerGP(){}

	//���͎擾
	float Handle(void);
	bool Brake(void);
	bool Nitro(void);
};

#endif