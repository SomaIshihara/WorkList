//==========================================
//
//�f�o�b�O�\���v���O�����̃w�b�_[debugproc.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

//�}�N��
#define DEBPRO_MAX_STR	(2048)			//�m�ۂ��镶����

class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();
	void Init(void);
	void Uninit(void);
	void Draw(void);
	void Print(const char* fmt, ...);
private:
	LPD3DXFONT m_pFont = nullptr;				//�t�H���g�ւ̃|�C���^
	char m_aStrPrint[DEBPRO_MAX_STR];		//�\�������o�b�t�@
};

#endif // !_DEBUGPROC_H_
