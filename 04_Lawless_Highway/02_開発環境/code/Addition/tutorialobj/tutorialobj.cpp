//======================================================
//
//�`���[�g���A���e�L�X�g����[tutorialobj.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "tutorialobj.h"
#include "../../IS_Bace/_Core/manager/manager.h"
#include "../../IS_Bace/_Core/texture/texture.h"
#include "../../IS_Bace/_Core/input/input.h"
#include "../player/player.h"

//�������O���
namespace
{
	float RADIUS = 300.0f;
}

//�ÓI�����o
const D3DXVECTOR3 CTutorialObj::PILOT_CHECKPOINT = D3DXVECTOR3(-900.0f, -380.0f, 845.0f);
const D3DXVECTOR3 CTutorialObj::START_CHECKPOINT = D3DXVECTOR3(0.0f, 99.0f, 0.0f);
const D3DXVECTOR3 CTutorial_01::CHECKPOINT = D3DXVECTOR3(12600.0f, -378.0f, -1845.0f);
const D3DXVECTOR3 CTutorial_02::CHECKPOINT = D3DXVECTOR3(8610.0f, -378.0f, -1845.0f);
const D3DXVECTOR3 CTutorial_03::CHECKPOINT = D3DXVECTOR3(4090.0f, -380.0f, 845.0f);
const D3DXVECTOR3 CTutorial_05::CHECKPOINT = D3DXVECTOR3(0.0f, 100.0f, -2300.0f);

//=================================
//�R���X�g���N�^
//=================================
CTutorialObj::CTutorialObj(int nPriority) : CObject2D(nPriority)
{
}

//=================================
//�f�X�g���N�^
//=================================
CTutorialObj::~CTutorialObj()
{
}

//=================================
//������
//=================================
HRESULT CTutorialObj::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//=================================
//�I��
//=================================
void CTutorialObj::Uninit(void)
{
	CObject2D::Uninit();
}

//=================================
//�X�V
//=================================
void CTutorialObj::Update(void)
{
	//�v���C���[�ʒu�擾
	D3DXVECTOR3 pos = m_pPlayer->GetPos();

	//�`���[�g���A����Ԃɉ���������
	m_pState->Update(this, pos);

	//�������c
	float length = D3DXVec3Length(&(pos - PILOT_CHECKPOINT));
	if (length <= RADIUS)
	{
		SetWaitingPirot();
		SetState(new CTutorial_05);
	}

	//�Q�[���ڍs����
	length = D3DXVec3Length(&(pos - START_CHECKPOINT));
	if (length <= RADIUS)
	{
		m_pPlayer->SetState(CPlayer::STATE::STATE_GAME);
	}

	CObject2D::Update();
}

//=================================
//�`��
//=================================
void CTutorialObj::Draw(void)
{
	CObject2D::Draw();
}

//=================================
//����
//=================================
CTutorialObj* CTutorialObj::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, CTimer* pTimer, CPlayer* pPlayer)
{
	CTutorialObj* pTutorialObj = nullptr;

	if (pTutorialObj == nullptr)
	{
		//�I�u�W�F�N�g�̐���
		pTutorialObj = new CTutorialObj;

		//������
		pTutorialObj->Init();
		pTutorialObj->SetPos(pos);
		pTutorialObj->SetRot(rot);
		pTutorialObj->SetSize(fWidth, fHeight);
		pTutorialObj->SetState(new CTutorial_01);
		pTutorialObj->m_pPlayer = pPlayer;
		pTutorialObj->m_pTimer = pTimer;

		return pTutorialObj;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//�n���h������:�X�V����
//=================================
void CTutorial_01::Update(CTutorialObj* obj, D3DXVECTOR3 playerPos)
{
	CInputGamePad* pGamePad = CManager::GetInstance()->GetInputGamePad();

	//�R���g���[���[�ɍ��킹�ăe�N�X�`���ύX
	if (pGamePad != nullptr && pGamePad->IsConnect() == true)
	{//�Q�[���p�b�h�p
		obj->BindTexture(CTexture::PRELOAD::PRELOAD_28_TUTORIAL_01_GP);
	}
	else
	{//�L�[�{�[�h�p
		obj->BindTexture(CTexture::PRELOAD::PRELOAD_27_TUTORIAL_01_KB);
	}
	
	float length = D3DXVec3Length(&(playerPos - CHECKPOINT));
	if (length <= RADIUS)
	{
		obj->SetState(new CTutorial_02);
	}
}

//=================================
//�u�[�X�g:�X�V����
//=================================
void CTutorial_02::Update(CTutorialObj* obj, D3DXVECTOR3 playerPos)
{
	CInputGamePad* pGamePad = CManager::GetInstance()->GetInputGamePad();

	//�R���g���[���[�ɍ��킹�ăe�N�X�`���ύX
	if (pGamePad != nullptr && pGamePad->IsConnect() == true)
	{//�Q�[���p�b�h�p
		obj->BindTexture(CTexture::PRELOAD::PRELOAD_30_TUTORIAL_02_GP);
	}
	else
	{//�L�[�{�[�h�p
		obj->BindTexture(CTexture::PRELOAD::PRELOAD_29_TUTORIAL_02_KB);
	}

	float length = D3DXVec3Length(&(playerPos - CHECKPOINT));
	if (length <= RADIUS)
	{
		obj->SetState(new CTutorial_03);
	}
}

//=================================
//�u���[�L�h���t�g����:�X�V����
//=================================
void CTutorial_03::Update(CTutorialObj* obj, D3DXVECTOR3 playerPos)
{
	CInputGamePad* pGamePad = CManager::GetInstance()->GetInputGamePad();

	//�R���g���[���[�ɍ��킹�ăe�N�X�`���ύX
	if (pGamePad != nullptr && pGamePad->IsConnect() == true)
	{//�Q�[���p�b�h�p
		obj->BindTexture(CTexture::PRELOAD::PRELOAD_32_TUTORIAL_03_GP);
	}
	else
	{//�L�[�{�[�h�p
		obj->BindTexture(CTexture::PRELOAD::PRELOAD_31_TUTORIAL_03_KB);
	}

	float length = D3DXVec3Length(&(playerPos - CHECKPOINT));
	if (length <= RADIUS)
	{
		obj->SetState(new CTutorial_04);
	}
}

//=================================
//�ړI�\��:�X�V����
//=================================
void CTutorial_04::Update(CTutorialObj* obj, D3DXVECTOR3 playerPos)
{
	if (m_bIsSet == false)
	{
		m_bIsSet = true;
		obj->BindTexture(CTexture::PRELOAD::PRELOAD_33_TUTORIAL_04);
	}
}

//=================================
//�������c��Q�[���؂�ւ�:�X�V����
//=================================
void CTutorial_05::Update(CTutorialObj* obj, D3DXVECTOR3 playerPos)
{
	if (m_bIsSet == false)
	{
		m_bIsSet = true;
		obj->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}

	float length = D3DXVec3Length(&(playerPos - CHECKPOINT));
	if (m_bIsPirot == false && length <= RADIUS)
	{
		m_bIsPirot = true;
		obj->GameStart();
	}
}