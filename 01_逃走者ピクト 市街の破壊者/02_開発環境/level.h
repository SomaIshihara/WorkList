//======================================================
//
//���x�������̃w�b�_[havenum.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _LEVEL_H_
#define _LEVEL_H_
#include "main.h"
#include "object.h"
#include "manager.h"

class CNumber;
class CSymbol;

class CLevel : public CObject
{
public:
	//�L����
	static const int m_nSymbolX;

	//�R���X�g���N�^�E�f�X�g���N�^
	CLevel(int nPriority = PRIORITY_UI);				//�f�t�H���g
	CLevel(const int nLevelDigit, int nPriority = PRIORITY_UI);	//�I�[�o�[���[�h
	~CLevel();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CLevel* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fOneWidth, const float fOneHeight, const int nLevelDigit,
		const int nIconTexNum);	//�I�u�W�F�N�g�𐶐�(fOneWidth,fOneHeight:1��������̃T�C�Y)

	//�擾�i�������z�֐��̊֌W��������Ă��邪�A�����ɃT�C�Y���͂���Ȃ��̂ł��ׂ�0��Ԃ��j
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	float GetWidth(void) { return CManager::FLOAT_ZERO; }
	float GetHeight(void) { return CManager::FLOAT_ZERO; }
	float GetDepth(void) { return CManager::FLOAT_ZERO; }
	int GetModelIdx(void) { return -1; }
	int GetLevel(void) { return m_nLevel; }

	//�ݒ�
	void SetNum(const int nNum) { m_nLevel = nNum; }
	void AddNum(const int nNum) { m_nLevel += nNum; }

private:
	void CutNumber(void);				//��������
	CNumber** m_ppNumber;				//����
	int m_nIdxTexture;					//�e�N�X�`���ԍ�
	D3DXVECTOR3 m_pos;					//�ʒu�i1���ڂ̐����̒��S��z��j
	D3DXVECTOR3 m_rot;					//�����i1���ڂ̐����̒��S��z��j
	float m_fOneWidth;					//1��������̃T�C�Y��
	float m_fOneHeight;					//1��������̃T�C�Y����
	int m_nLevel;						//������
	const int m_nLevelDigit;			//����
};

#endif // !_TIME_H_