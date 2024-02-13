//======================================================
//
//�L�����N�^�[����[character.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "character.h"
#include "manager.h"
#include "texture.h"
#include "sound.h"
#include "renderer.h"
#include "input.h"
#include "model.h"
#include "motion.h"
#include "Culc.h"
#include "file.h"
#include "block3D.h"
#include "switch.h"
#include "item.h"
#include "collision.h"
#include "tutorialobj.h"
#include "shadow.h"
#include "debugproc.h"

//�ÓI�����o�ϐ�
CCharacter* CCharacter::m_aChara[] = { nullptr,nullptr };
const float CCharacter::CHARA_SPEED = 3.7f;
const float CCharacter::CHARA_JUMP_POW = 9.0f;
const float CCharacter::CHARA_RESPAWN_HEIGHT = -500.0f;

//=================================
//�R���X�g���N�^
//=================================
CCharacter::CCharacter(int nPriority) : CObject(nPriority)
{
	m_ppModel = nullptr;
	m_pShadow = nullptr;
	m_pPoint = nullptr;
	m_nNumModel = CManager::INT_ZERO;
	m_pos = CManager::VEC3_ZERO;
	m_posOld = CManager::VEC3_ZERO;
	m_posLastLanding = CManager::VEC3_ZERO;
	m_move = CManager::VEC3_ZERO;
	m_rot = CManager::VEC3_ZERO;
	m_fWidth = CManager::FLT_ZERO;
	m_fHeight = CManager::FLT_ZERO;
	m_fDepth = CManager::FLT_ZERO;
	m_bJump = false;
	m_nCounterJumpTime = CManager::INT_ZERO;
	m_fJumpPower = CManager::FLT_ZERO;
	m_type = TYPE_MAX;
	m_pCollider = nullptr;
}

//=================================
//�f�X�g���N�^
//=================================
CCharacter::~CCharacter()
{
}

//=================================
//������
//=================================
HRESULT CCharacter::Init(void)
{
	SetModel();
	SetType(TYPE_CHARACTER);
	m_posOld = m_pos;

	m_pCollider = CBoxCollider::Create(this);
	m_pCollider->SetType(CBoxCollider::TYPE_COLLISION);

	m_pShadow = CShadow::Create();
	m_pShadow->Set(m_pos, m_rot,m_type);

	m_pPoint = CObject3D::Create(m_pos, D3DXVECTOR3(-0.5f * D3DX_PI,0.0f,0.0f), 20.0f, 20.0f);
	m_pPoint->BindTexture(CTexture::PRELOAD_32_POINT);
	m_pPoint->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	return S_OK;
}

//=================================
//�I��
//=================================
void CCharacter::Uninit(void)
{
	//���[�V�����j��
	if (m_pMotion != nullptr)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	if (m_ppModel != nullptr)
	{
		for (int cnt = 0; cnt < m_nNumModel; cnt++)
		{//�������
			if (m_ppModel[cnt] != nullptr)
			{
				m_ppModel[cnt]->Uninit();
				delete m_ppModel[cnt];
				m_ppModel[cnt] = nullptr;
			}
		}
		delete[] m_ppModel;	//�z�񂻂̂��̂�j��
	}

	if (m_pCollider != nullptr)
	{
		m_pCollider->Release();
		m_pCollider = nullptr;
	}

	m_aChara[m_type] = nullptr;

	Release();
}

//=================================
//�X�V
//=================================
void CCharacter::Update(void)
{
	CManager* pManager = CManager::GetInstance();
	CSound* pSound = pManager->GetSound();
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetInputKeyboard();

	m_posOld = m_pos;	//�O�̈ʒu�ݒ�

	if (m_controllInterface->GetType() == m_type)
	{
		//���쒆�|�C���g��������悤�ɂ���
		m_pPoint->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		if (m_controllInterface->GetPress() == DIK_A)
		{
			m_move.x -= CHARA_SPEED;
			if (pSound->IsPlay(CSound::SOUND_LABEL_SE_MOVE) == false)
			{
				pSound->Play(CSound::SOUND_LABEL_SE_MOVE);
			}
			int nType = m_pMotion->GetType();
			if (nType != MOTIONTYPE_MOVE && nType != MOTIONTYPE_JUMP)
			{
				m_pMotion->Set(MOTIONTYPE_MOVE);
			}
			m_rot.y += 0.1f * D3DX_PI;
			if (m_rot.y >= 0.5f * D3DX_PI)
			{
				m_rot.y = 0.5f * D3DX_PI;
			}
		}
		else if (m_controllInterface->GetPress() == DIK_D)
		{
			m_move.x += CHARA_SPEED;
			if (pSound->IsPlay(CSound::SOUND_LABEL_SE_MOVE) == false)
			{
				pSound->Play(CSound::SOUND_LABEL_SE_MOVE);
			}
			int nType = m_pMotion->GetType();
			if (nType != MOTIONTYPE_MOVE && nType != MOTIONTYPE_JUMP)
			{
				m_pMotion->Set(MOTIONTYPE_MOVE);
			}
			m_rot.y -= 0.1f * D3DX_PI;
			if (m_rot.y <= -0.5f * D3DX_PI)
			{
				m_rot.y = -0.5f * D3DX_PI;
			}
		}
		else if (pSound->IsPlay(CSound::SOUND_LABEL_SE_MOVE) == true)
		{
			pSound->Stop(CSound::SOUND_LABEL_SE_MOVE);

			if (m_pMotion->GetType() != MOTIONTYPE_NEUTRAL)
			{
				m_pMotion->Set(MOTIONTYPE_NEUTRAL);
			}
		}
	}
	else
	{
		//���쒆�|�C���g�������Ȃ��悤�ɂ���
		m_pPoint->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

		if (m_pMotion->GetType() != MOTIONTYPE_NEUTRAL)
		{
			m_pMotion->Set(MOTIONTYPE_NEUTRAL);
		}
	}

	//�W�����v�J�E���^���₷
	m_nCounterJumpTime++;

	//�d�͉����x�ɂ��Y�̈ړ��ʕύX
	m_move.y = m_fJumpPower - (ACCELERATION_GRAVITY * 2.0f * m_nCounterJumpTime / MAX_FPS);

	//�����蔻��
	m_pCollider->CollisionCheck();

	//�{�^���͉����E�A�C�e���͏E��
	for (int cnt = 0; cnt < m_pCollider->GetResult().collList.size(); cnt++)
	{
		if (m_pCollider->GetResult().collList[cnt]->GetType() == CObject::TYPE_SWITCH)
		{
			CSwitch* pSwitch = CSwitch::GetTop();
			while (pSwitch != nullptr)
			{
				if (pSwitch->GetMove() == m_pCollider->GetResult().collList[cnt])
				{
					pSwitch->Push();
					break;
				}
				pSwitch = pSwitch->GetNext();
			}
		}
		if (m_pCollider->GetResult().collList[cnt]->GetType() == CObject::TYPE_ITEM)
		{
			CItem* pItem = CItem::GetTop();
			while (pItem != nullptr)
			{
				if (pItem == m_pCollider->GetResult().collList[cnt])
				{
					pItem->Get();
					break;
				}
				pItem = pItem->GetNext();
			}
		}
		if (m_pCollider->GetResult().collList[cnt]->GetType() == CObject::TYPE_TUTORIALOBJ)
		{
			CTutorialObj* pTutorialObj = CTutorialObj::GetTop();
			while (pTutorialObj != nullptr)
			{
				if (pTutorialObj == m_pCollider->GetResult().collList[cnt])
				{
					pTutorialObj->Popup();
					break;
				}
				pTutorialObj = pTutorialObj->GetNext();
			}
		}
	}

	if (m_pCollider->GetResult().bHit[1] == true)
	{//���n����
		if (m_bJump == true)
		{
			if (m_pMotion->GetType() != MOTIONTYPE_LAND)
			{
				m_pMotion->Set(MOTIONTYPE_LAND);
			}
		}

		m_bJump = false;
		m_nCounterJumpTime = 0;
		m_fJumpPower = 0.0f;
		m_posLastLanding = m_pos;

		//�W�����v
		if (m_bJump == false && m_controllInterface->GetType() == m_type && m_controllInterface->IsJump() == true)
		{//�W�����v����
			m_bJump = true;
			m_nCounterJumpTime = 0;
			m_fJumpPower = CHARA_JUMP_POW;

			int nType = m_pMotion->GetType();
			if (nType != MOTIONTYPE_JUMP)
			{
				m_pMotion->Set(MOTIONTYPE_JUMP);
			}

			//BGM�Đ�
			pSound->Play(CSound::SOUND_LABEL_SE_JUMP);
		}
	}

	//���X�|�[������
	if (m_pos.y <= CHARA_RESPAWN_HEIGHT)
	{
		m_pos = m_posLastLanding;
		m_pos.y += 30.0f;
		m_bJump = true;
		m_nCounterJumpTime = 0;
		m_fJumpPower = 0.0f;

	}

	//�e�ݒ�
	m_pShadow->Set(m_pos - D3DXVECTOR3(0.0f, m_fHeight * 0.5f, 0.0f), m_rot,m_type);

	//�ړ��ʌ���
	m_move.x = CManager::FLT_ZERO;
	m_move.z = CManager::FLT_ZERO;

	//���f���ݒ�
	if (m_ppModel != nullptr)
	{
		for (int cnt = 0; cnt < m_nNumModel; cnt++)
		{
			if (m_ppModel[cnt] != nullptr)
			{
				m_ppModel[cnt]->Update();
			}
		}
	}

	//���[�V����������
	if (m_pMotion != nullptr)
	{
		//���[�V�����X�V
		m_pMotion->Update();
	}

	//���[�V�����I������
	if (m_pMotion->IsFinish() == true && m_pMotion->GetType() == MOTIONTYPE_LAND)
	{
		m_pMotion->Set(MOTIONTYPE_NEUTRAL);
	}

	//�|�C���g�������悤�������܂����ړ�����
	m_pPoint->SetPos(m_pos + D3DXVECTOR3(0.0f, 100.0f, 0.0f));
}

//=================================
//�`��
//=================================
void CCharacter::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�擾
	CTexture* pTexture = CManager::GetInstance()->GetInstance()->GetTexture();			//�e�N�X�`���I�u�W�F�N�g�擾
	D3DXMATRIX mtxRot, mtxTrans, mtxTexture;							//�v�Z�p
	D3DMATERIAL9 matDef;												//���݂̃}�e���A���ۑ��p

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//���f���擾
	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�A���t�@�e�X�g�L����
	CRenderer* pRenderer = CManager::GetInstance()->GetRenderer();
	pRenderer->SetEnableAlplaTest(true);

	//���f���`��
	if (m_ppModel != nullptr)
	{
		for (int cnt = 0; cnt < m_nNumModel; cnt++)
		{
			if (m_ppModel[cnt] != nullptr)
			{
				m_ppModel[cnt]->Draw();
			}
		}
	}

	//�A���t�@�e�X�g������
	pRenderer->SetEnableAlplaTest(false);
	
	//�}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=================================
//����
//=================================
CCharacter* CCharacter::Create(const D3DXVECTOR3 pos, const TYPE type, IControllStat* player)
{
	if (m_aChara[type] == nullptr)
	{
		CCharacter* pChara = nullptr;

		if (pChara == nullptr)
		{
			//�I�u�W�F�N�g2D�̐���
			pChara = new CCharacter;

			//�f�[�^�ݒ�
			pChara->m_type = type;
			pChara->m_pos = pos;
			pChara->m_controllInterface = player;

			//������
			pChara->Init();

			//�����蔻��^�O�ݒ�
			if (type == TYPE_A)
			{
				pChara->m_pCollider->SetTag(CBoxCollider::TAG_TYPE_A);
			}
			else if (type == TYPE_B)
			{
				pChara->m_pCollider->SetTag(CBoxCollider::TAG_TYPE_B);
			}
			else
			{
				assert(false);
			}

			//�����
			m_aChara[type] = pChara;

			return pChara;
		}
	}

	return nullptr;
}

//=================================
//���f���ݒ�
//=================================
void CCharacter::SetModel(void)
{
	//���[�V���������E������
	m_pMotion = new CMotion;
	m_pMotion->Init();

	//���[�V�����r���[�A�̃t�@�C����ǂݍ���
	if (m_type == TYPE_A)
	{
		LoadMotionViewerFile("data\\motion_kei.txt", &m_ppModel, m_pMotion, &m_nNumModel);
	}
	else if (m_type == TYPE_B)
	{
		LoadMotionViewerFile("data\\motion_rei.txt", &m_ppModel, m_pMotion, &m_nNumModel);
	}

	m_fWidth = 60.0f;
	m_fHeight = 150.0f;
	m_fDepth = 60.0f;

	//���[�V�����␳
	m_ppModel[0]->SetPosOffset(m_ppModel[0]->GetPosOffset() - D3DXVECTOR3(0.0f, 75.0f, 0.0f));

	//���[�V�����ݒ�
	m_pMotion->Set(0);
}