//======================================================
//
//��ԃv���O����[koban.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "koban.h"
#include "picto.h"
#include "building.h"

//�ÓI�����o�ϐ�
CKoban* CKoban::m_apKoban[];
int CKoban::m_nNumAll = CManager::INT_ZERO;

//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CKoban::CKoban()
{
	for (int cnt = 0; cnt < MAX_OBJ; cnt++)
	{//���ׂĊm�F
		if (m_apKoban[cnt] == nullptr)
		{//�����
			m_apKoban[cnt] = this;	//�������g�̃|�C���^��o�^
			m_nID = cnt;
			m_nNumAll++;	//�������₷
			break;
		}
	}
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h�j
//=================================
CKoban::CKoban(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, CXModel* pModel) : CObjectX(pos, rot, pModel)
{
	for (int cnt = 0; cnt < MAX_OBJ; cnt++)
	{//���ׂĊm�F
		if (m_apKoban[cnt] == nullptr)
		{//�����
			m_apKoban[cnt] = this;	//�������g�̃|�C���^��o�^
			m_nID = cnt;
			m_nNumAll++;	//�������₷
			break;
		}
	}
}

//=================================
//�f�X�g���N�^
//=================================
CKoban::~CKoban()
{
}

//=================================
//������
//=================================
HRESULT CKoban::Init(void)
{
	CObjectX::Init();
	return S_OK;
}

//=================================
//�I��
//=================================
void CKoban::Uninit(void)
{
	m_apKoban[m_nID] = nullptr;
	m_nNumAll--;

	CObjectX::Uninit();
}

//=================================
//�X�V
//=================================
void CKoban::Update(void)
{
	CObjectX::Update();
}

//=================================
//�`��
//=================================
void CKoban::Draw(void)
{
	CObjectX::Draw();
}

//=================================
//����
//=================================
CKoban* CKoban::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, CXModel* pModel)
{
	CKoban* pKoban = nullptr;

	if (pKoban == nullptr)
	{
		//��Ԃ̐���
		pKoban = new CKoban(pos, rot, pModel);

		//������
		pKoban->Init();

		return pKoban;
	}
	else
	{
		return nullptr;
	}
}