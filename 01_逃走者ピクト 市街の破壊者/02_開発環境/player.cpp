//======================================================
//
//�v���C���[����[player.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "player.h"
#include "manager.h"
#include "game.h"
#include "tutorial.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"
#include "camera.h"
#include "objectX.h"
#include "picto.h"
#include "building.h"
#include "button.h"
#include "slider.h"
#include "building.h"
#include "xmodel.h"
#include "havenum.h"
#include "sound.h"
//#include "progressbar.h"

//=================================
//�R���X�g���N�^
//=================================
CPlayer::CPlayer()
{
	m_bControllPicto = false;

	m_cursorPos = CManager::VEC3_ZERO;
	m_pButtonATK = nullptr;
	m_pProgBar = nullptr;
}

//=================================
//�f�X�g���N�^
//=================================
CPlayer::~CPlayer()
{}

//=================================
//������
//=================================
HRESULT CPlayer::Init(void)
{
	m_bControllPicto = false;

	return S_OK;
}

//=================================
//�I��
//=================================
void CPlayer::Uninit(void)
{
	
}

//=================================
//�X�V
//=================================
void CPlayer::Update(void)
{
	CInputMouse* pMouse = CManager::GetInputMouse();	//�}�E�X�擾
	CSound* pSound = CManager::GetSound();
	Move();

	//�̗̓o�[�ݒ�
	if (m_pObject != nullptr)
	{

		//�������s�N�g���m��
		if (m_pObject->GetType() == CObject::TYPE_BUILDING)
		{//����
			for (int cnt = 0; cnt < MAX_OBJ; cnt++)
			{
				CBuilding* pBuilding = CBuilding::GetBuilding(cnt);

				if (m_pObject == pBuilding)
				{
					int nEndurance;
					int nMaxEndurance;
					if (pBuilding->GetUnique() == false)
					{//�v�Z�Z�o
						nEndurance = pBuilding->GetEndurance();
						nMaxEndurance = HAVE_LIFE(pBuilding->GetLv());
					}
					else
					{//��
						nMaxEndurance = pBuilding->GetSigEndurance() * pow(10, pBuilding->GetPowEndurance());
						nEndurance = pBuilding->GetEndurance();
					}
					//m_pProgBar->SetPercent((float)nEndurance / nMaxEndurance);
				}
			}
		}
		else
		{//�����I�Ƀs�N�g�Ƃ킩��
			for (int cnt = 0; cnt < MAX_OBJ; cnt++)
			{
				CPicto* pPicto = CPicto::GetPicto(cnt);

				if (m_pObject == pPicto)
				{
					int nMaxLife;

					//�s�N�g��ފm�F
					switch (pPicto->GetType())
					{
					case CPicto::TYPE_DESTROYER:
						nMaxLife = HAVE_LIFE(CPictoDestroyer::GetLv());
						break;
					case CPicto::TYPE_BLOCKER:
						nMaxLife = HAVE_LIFE(CPictoBlocker::GetLv());
						break;
					case CPicto::TYPE_POLICE:
						//�ǂ̌x�@�����ׂ�
						for (int cnt = 0; cnt < MAX_OBJ; cnt++)
						{
							CPictoPolice* pPolice = CPictoPolice::GetPicto(cnt);

							if (pPicto == pPolice)
							{
								nMaxLife = HAVE_LIFE(pPolice->GetLv());
							}
						}
						break;
					case CPicto::TYPE_TAXI:
						nMaxLife = PICTO_TAXI_MAXLIFE;
					}

					//m_pProgBar->SetPercent(((float)pPicto->GetLife() / nMaxLife));
				}
			}
		}
	}

	if (pMouse->GetPress(MOUSE_CLICK_RIGHT) == true)
	{//��]
		Rotate();
	}
	else
	{//�}�E�X�J�[�\���ʒu�ۑ�
		m_cursorPos = pMouse->GetPos();
	}
	//�{�^���������ꂽ�����m
	if (m_pButtonATK != nullptr && m_pButtonATK->IsClickTrigger() == true)
	{
		Attack();
		pSound->Play(CSound::SOUND_LABEL_SE_DISPATCH);
		m_pButtonATK->Uninit();
		m_pButtonATK = nullptr;
	}
	else if (pMouse->GetTrigger(MOUSE_CLICK_LEFT) == true)
	{//�ʒu����
		Select();
		if (m_pObject != nullptr)
		{//�Ȃ񂩑I������
			pSound->Play(CSound::SOUND_LABEL_SE_SELECT);
		}
	}

	//�X���C�_�[�ƃ^�N�V�[����
	int nIdxSlider = -1;
	CPictoTaxi* pTaxi = nullptr;

	//�X���C�_�[�ύX
	CSlider* slider = CManager::GetScene()->GetSlider();
	slider->SetSelectIdx(slider->GetSelectIdx() - (pMouse->GetWheel() / 120));

	//�^�N�V�[���[�h
	pTaxi = CPictoTaxi::GetPicto(0);
	nIdxSlider = CManager::GetScene()->GetSlider()->GetSelectIdx();

	//�������Č����Ă�̂Ƀ^�N�V�[���Ȃ�
	if (nIdxSlider != CPictoTaxi::MODE_SABO && pTaxi == nullptr)
	{//��������\�o��
		CPictoTaxi::Create(CPicto::GetAgitPos());
	}

	if (pTaxi != nullptr)
	{//�^�N�V�[����
		pTaxi->SetMode((CPictoTaxi::MODE)nIdxSlider);
	}
}

//=================================
//�U��
//=================================
void CPlayer::Attack(void)
{
	if (m_pObject != nullptr)
	{//��������I�����Ă���
		//���݂̃��[�h�ɉ����ď������I�u�W�F�N�g�擾
		CScene::MODE mode = CManager::GetMode();
		CHaveNum** ppHaveNumObj = nullptr;
		if (mode == CScene::MODE_GAME)
		{//�Q�[��
			ppHaveNumObj = CGame::GetHaveNumObj();
		}
		else if (mode == CScene::MODE_TUTORIAL)
		{//�`���[�g���A��
			ppHaveNumObj = CTutorial::GetHaveNumObj();
		}

		//�I�u�W�F�N�g�擾
		CObject::TYPE type = m_pObject->GetType();

		if (type == CObject::TYPE_BUILDING && ppHaveNumObj[CPicto::TYPE_DESTROYER]->GetHaveNum() > 0)
		{//�������I������Ă��邩��l�ȏア��
			CPictoDestroyer* picto = CPictoDestroyer::Create(CPicto::GetAgitPos());
			picto->SetTargetObj(m_pObject);
			picto->SetState(CPicto::STATE_FACE);
		}
		else if (type == CObject::TYPE_PICTO)
		{//�s�N�g�i�Ȃ�ł��j���I������Ă���
			 //���ׂ�
			for (int cnt = 0; cnt < MAX_OBJ; cnt++)
			{//�S�I�u�W�F�N�g����
				CPicto* pPicto = CPicto::GetPicto(cnt);	//�s�N�g�S�̎擾
				if (m_pObject == pPicto)
				{
					switch (pPicto->GetType())
					{
					case CPicto::TYPE_POLICE:	//�x�@
						if (ppHaveNumObj[CPicto::TYPE_BLOCKER]->GetHaveNum() > 0)
						{//��l�ȏア��
							CPictoBlocker::Create(CPicto::GetAgitPos())->SetTargetObj(pPicto);	//�u���b�J�[�������킹��
						}
						break;

					case CPicto::TYPE_DESTROYER:	//�f�X�g���C���[
						pPicto->UnsetTarget();
						break;

					case CPicto::TYPE_BLOCKER:	//�u���b�J�[
						pPicto->UnsetTarget();
						break;
					}
				}
			}
		}
	}
}

//=================================
//���e
//=================================
void CPlayer::AddPicto(const int nDestroyer, const int nBlocker, const int nNormal)
{//�ǉ�
	CScene::MODE mode = CManager::GetMode();

	if (mode == CScene::MODE_GAME)
	{//�Q�[��
		CHaveNum** ppHaveNum = CGame::GetHaveNumObj();
		ppHaveNum[0]->AddNum(nDestroyer);
		ppHaveNum[1]->AddNum(nBlocker);
		ppHaveNum[2]->AddNum(nNormal);
	}
	else if (mode == CScene::MODE_TUTORIAL)
	{//�`���[�g���A��
		CHaveNum** ppHaveNum = CTutorial::GetHaveNumObj();
		ppHaveNum[0]->AddNum(nDestroyer);
		ppHaveNum[1]->AddNum(nBlocker);
		ppHaveNum[2]->AddNum(nNormal);
	}
}

//=================================
//�ړ�
//=================================
void CPlayer::Move(void)
{
	CInputKeyboard* pKeyboard = CManager::GetInputKeyboard();	//�L�[�{�[�h�擾
	CCamera* pCamera = CManager::GetCamera();					//�J�����擾
	D3DXVECTOR3 move = CManager::VEC3_ZERO;
	D3DXVECTOR3 rot = pCamera->GetRot();
	//�ړ�
	if (pKeyboard->GetPress(DIK_A) == true)
	{
		move.x += -cosf(rot.y) * CAMERA_MOVE_SPEED;
		move.z += -sinf(rot.y) * CAMERA_MOVE_SPEED;
	}
	else if (pKeyboard->GetPress(DIK_D) == true)
	{
		move.x += cosf(rot.y) * CAMERA_MOVE_SPEED;
		move.z += sinf(rot.y) * CAMERA_MOVE_SPEED;
	}

	if (pKeyboard->GetPress(DIK_W) == true)
	{
		move.x += -sinf(rot.y) * CAMERA_MOVE_SPEED;
		move.z += cosf(rot.y) * CAMERA_MOVE_SPEED;
	}
	else if (pKeyboard->GetPress(DIK_S) == true)
	{
		move.x += sinf(rot.y) * CAMERA_MOVE_SPEED;
		move.z += -cosf(rot.y) * CAMERA_MOVE_SPEED;
	}

	//�ړ�
	pCamera->SetPos(move);
}

//=================================
//��]
//=================================
void CPlayer::Rotate(void)
{
	CCamera* pCamera = CManager::GetCamera();
	CInputMouse* pMouse = CManager::GetInputMouse();
	D3DXVECTOR3 rot = CManager::VEC3_ZERO;

	D3DXVECTOR3 move = CManager::VEC3_ZERO;
	move.x = pMouse->GetMove().x;
	move.y = pMouse->GetMove().y;

	rot.y -= move.x * CAMERA_MOU_ROT_SPEED;
	rot.x -= move.y * CAMERA_MOU_ROT_SPEED;

	pCamera->SetRot(rot);

	//�J�[�\�������̈ʒu�ɖ߂�
	POINT setCursorpos;
	setCursorpos.x = m_cursorPos.x;
	setCursorpos.y = m_cursorPos.y;
	ClientToScreen(FindWindowA(CLASS_NAME, nullptr), &setCursorpos);
	SetCursorPos(setCursorpos.x, setCursorpos.y);
}

//=================================
//�I��
//=================================
void CPlayer::Select(void)
{
	CInputMouse* mouse = CManager::GetInputMouse();	//�}�E�X�擾

	//�I�u�W�F�N�g�I���i0.0�`1.0�j
	D3DXVECTOR3 posNear = mouse->ConvertClickPosToWorld(0.0f);
	D3DXVECTOR3 posFar = mouse->ConvertClickPosToWorld(1.0f);

	//�߂�����
	CObject* pObject = nullptr;
	float fLengthNear = CManager::FLOAT_ZERO;

	//�{�^���폜
	if (m_pButtonATK != nullptr)
	{
		m_pButtonATK->Uninit();
		m_pButtonATK = nullptr;

		//�Q�[�W���ꏏ�ɏ���
		//m_pProgBar->Uninit();
		//m_pProgBar = nullptr;
	}

	//����
	for (int cnt = 0; cnt < MAX_OBJ; cnt++)
	{//�S�I�u�W�F�N�g����
		CBuilding* pBuilding = CBuilding::GetBuilding(cnt);	//�I�u�W�F�N�g�擾

		if (pBuilding != nullptr)	//�k���`�F
		{//�Ȃ񂩂���
			if (pBuilding->GetModel()->GetCollision().CollisionCheck(posNear, posFar, pBuilding->GetPos(), pBuilding->GetRot()) == true &&
				pBuilding->GetEndurance() > 0)
			{//�����I��
				float fLength = D3DXVec3Length(&(pBuilding->GetPos() - posNear));

				if (pObject == nullptr || fLengthNear > fLength)
				{//�߂�
					pObject = pBuilding;
					fLengthNear = fLength;
				}
			}
		}
	}

	//�s�N�g����
	for (int cnt = 0; cnt < MAX_OBJ; cnt++)
	{//�S�I�u�W�F�N�g����
		CPicto* pPicto = CPicto::GetPicto(cnt);	//�I�u�W�F�N�g�擾

		if (pPicto != nullptr)	//�k���`�F
		{//�Ȃ񂩂���
			if (pPicto->GetCollision().CollisionCheck(posNear, posFar, pPicto->GetPos(), pPicto->GetRot()) == true 
				&& pPicto->GetType() != CPicto::TYPE_NORMAL && pPicto->GetType() != CPicto::TYPE_TAXI)
			{//�s�N�g�I��
				float fLength = D3DXVec3Length(&(pPicto->GetPos() - posNear));

				if (pObject == nullptr || fLengthNear > fLength)
				{//�߂�
					pObject = pPicto;
					fLengthNear = fLength;
				}
			}
		}
	}

	if (pObject != nullptr)
	{//��������I���ł���
		m_pObject = pObject;	//�o����

		//�{�^������
		m_pButtonATK = CButton2D::Create(mouse->GetPos(), CManager::VEC3_ZERO, 40.0f, 40.0f);
		m_pButtonATK->BindTexture(CTexture::PRELOAD_HIRE);
		//m_pProgBar = CProgressBar::Create(D3DXVECTOR3(1100.0f, 700.0f, 0.0f), 200.0f, 30.0f);
		//m_pProgBar->SetPercent(1.0f);	//���ݒ�
	}
	else
	{//�����I�����ĂȂ�
		m_pObject = nullptr;
	}
}
