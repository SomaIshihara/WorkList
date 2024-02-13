//======================================================
//
//�e����[bullet.cpp]
//Author:�Ό��D�n
//
//======================================================
#include "manager.h"
#include "game.h"
#include "tutorial.h"
#include "renderer.h"
#include "texture.h"
#include "object.h"
#include "meshsky.h"
#include "bullet.h"
#include "building.h"
#include "picto.h"
#include "input.h"
#include "particle.h"
#include "effect.h"
#include "Culc.h"
#include "sound.h"

//****************************************
//2D�e
//****************************************
//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CBullet2D::CBullet2D(int nPriority) : CObject2D(nPriority)
{
	m_nIdxTexture = -1;
	m_move = D3DXVECTOR3(3.0f, 0.0f, 0.0f);
	CObject::SetType(TYPE_BULLET);
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h �ʒu����and�p�^�[���������j
//=================================
CBullet2D::CBullet2D(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const float fSpeed, int nPriority) 
	: CObject2D(pos, rot, fWidth, fHeight, nPriority)
{
	m_nIdxTexture = -1;
	m_move.x = sinf(FIX_ROT(rot.z * D3DX_PI + D3DX_PI)) * fSpeed;
	m_move.y = cosf(FIX_ROT(rot.z * D3DX_PI + D3DX_PI)) * fSpeed;
	CObject::SetType(TYPE_BULLET);
}

//=================================
//�f�X�g���N�^
//=================================
CBullet2D::~CBullet2D()
{
}

//=================================
//������
//=================================
HRESULT CBullet2D::Init(void)
{
	CObject2D::Init();

	//�e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\EnergyBullet_01.png");

	//��ސݒ�
	m_Type = TYPE_PLAYER;

	return S_OK;
}

//=================================
//�I��
//=================================
void CBullet2D::Uninit(void)
{
	CObject2D::Uninit();
}

//=================================
//�X�V
//=================================
void CBullet2D::Update(void)
{
	//�G�t�F�N�g����
	CEffect2D::Create(GetPos(), CManager::VEC3_ZERO, 30.0f, 30.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 30);

	//���[�J��
	D3DXVECTOR3 pos = GetPos();

	//�ړ�
	pos += m_move;

	//�͈͊O����
	if (pos.x > SCREEN_WIDTH || pos.x < 0.0f || pos.y > SCREEN_HEIGHT || pos.y < 0.0f)
	{
		Uninit();
		return;
	}

	//�ʒu�ݒ�
	SetPos(pos);

#if 0
	//�G�Ƃ̏Փ˔���
	if (m_Type == TYPE_PLAYER && CollisionEnemy() == true)
	{//�e���G�ɓ�������
		return;
	}
	if (m_Type == TYPE_ENEMY && CollisionPlayer() == true)
	{//�e���v���C���[�ɓ�������
		return;
	}
	if (m_Type == TYPE_PLAYER && CollisionBlock() == true)
	{//�e���u���b�N�ɓ�������
		return;
	}
#endif

	//�e
	CObject2D::Update();
}

//=================================
//�`��
//=================================
void CBullet2D::Draw(void)
{
	CObject2D::Draw();
}

//=================================
//��������
//=================================
CBullet2D* CBullet2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const float fSpeed, const TYPE type)
{
	CBullet2D* pBullet = nullptr;

	if (pBullet == nullptr)
	{
		//�I�u�W�F�N�g�A�j���[�V����2D�̐���
		pBullet = new CBullet2D(pos, rot, fWidth, fHeight, fSpeed);

		//������
		pBullet->Init();

		//�^�C�v�ݒ�
		pBullet->SetType(type);

		//���u��
		pBullet->SetCol(D3DXCOLOR(1.0f, 0.5f, 0.16f,1.0f));

		//�e�N�X�`�����蓖��
		pBullet->BindTexture(pBullet->m_nIdxTexture);

		return pBullet;
	}
	else
	{
		return nullptr;
	}
}

#if 0
//=================================
//�u���b�N�Ƃ̏Փ˔���
//=================================
bool CBullet2D::CollisionBlock(void)
{
	for (int cnt = 0; cnt < MAX_OBJ; cnt++)
	{//�S�I�u�W�F�N�g����
		CObject* pObj = GetObject(BLOCK_PRIORITY, cnt);	//�I�u�W�F�N�g�擾

		if (pObj != nullptr)	//�k���`�F
		{//�Ȃ񂩂���
			TYPE type = pObj->GetType();	//��ގ擾

			if (type == TYPE_BLOCK)
			{//�G
				if (GetPos().x > pObj->GetPos().x - pObj->GetWidth() * 0.5f &&
					GetPos().x < pObj->GetPos().x + pObj->GetWidth() * 0.5f &&
					GetPos().y > pObj->GetPos().y - pObj->GetHeight() * 0.5f &&
					GetPos().y < pObj->GetPos().y + pObj->GetHeight() * 0.5f)
				{
					//��������
					CParticle2D::Create(GetPos(), 48, 16, 2, 3, D3DXCOLOR(1.0f, 0.5f, 0.14f, 1.0f), 20.0f, 20.0f);

					//�����I��
					Uninit();

					//�e�͓G�ɓ�������
					return true;
				}
			}
		}
	}
	//�e�͓G�ɓ������Ă��Ȃ�����
	return false;
}
#endif

//****************************************
//�r���{�[�h�e
//****************************************
//=================================
//�R���X�g���N�^�i�f�t�H���g�j
//=================================
CBulletBillboard::CBulletBillboard(int nPriority) : CObjectBillboard(nPriority)
{
	m_nIdxTexture = -1;
	m_move = D3DXVECTOR3(3.0f, 0.0f, 0.0f);
	CObject::SetType(TYPE_BULLET);
}

//=================================
//�R���X�g���N�^�i�I�[�o�[���[�h �ʒu����and�p�^�[���������j
//=================================
CBulletBillboard::CBulletBillboard(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, const float fSpeed, 
	const int nPower, CPicto* firePicto, int nPriority) : CObjectBillboard(pos, rot, fWidth, fHeight, nPriority)
{
	m_nIdxTexture = -1;
	m_move.x = sinf(FIX_ROT(rot.y + D3DX_PI)) * fSpeed;
	m_move.y = sinf(FIX_ROT(rot.x + D3DX_PI)) * fSpeed;
	m_move.z = cosf(FIX_ROT(rot.y + D3DX_PI)) * fSpeed;
	m_nPower = nPower;
	m_pfirePicto = firePicto;
	CObject::SetType(TYPE_BULLET);
}

//=================================
//�f�X�g���N�^
//=================================
CBulletBillboard::~CBulletBillboard()
{
}

//=================================
//������
//=================================
HRESULT CBulletBillboard::Init(void)
{
	CObjectBillboard::Init();

	//�e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\EnergyBullet_01.png");

	//��ސݒ�
	m_Type = CPicto::TYPE_NORMAL;

	return S_OK;
}

//=================================
//�I��
//=================================
void CBulletBillboard::Uninit(void)
{
	CObjectBillboard::Uninit();
}

//=================================
//�X�V
//=================================
void CBulletBillboard::Update(void)
{
	//�G�t�F�N�g����
	CEffectBillboard::Create(GetPos(), CManager::VEC3_ZERO, 30.0f, 30.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 30);

	//���[�J��
	D3DXVECTOR3 pos = GetPos();

	//�ړ�
	pos += m_move;

	//�͈͊O����
	CScene::MODE mode = CManager::GetMode();
	if (mode == CScene::MODE_GAME)
	{//�Q�[��
		if (D3DXVec3Length(&pos) >= CGame::GetSkyObj()->GetHeight())
		{
			Uninit();
			return;
		}
	}
	else if (mode == CScene::MODE_GAME)
	{//�`���[�g���A��
		if (D3DXVec3Length(&pos) >= CTutorial::GetSkyObj()->GetHeight())
		{
			Uninit();
			return;
		}
	}

	//�ʒu�ݒ�
	SetPos(pos);

	//�����Ƃ̏Փ˔���
	if (m_Type == CPicto::TYPE_DESTROYER && CollisionBuilding() == true)
	{
		return;
	}

	//�s�N�g�Ƃ̔���
	if ((m_Type == CPicto::TYPE_BLOCKER || m_Type == CPicto::TYPE_POLICE) && CollisionPicto() == true)
	{
		return;
	}

	//�e
	CObjectBillboard::Update();
}

//=================================
//�`��
//=================================
void CBulletBillboard::Draw(void)
{
	CObjectBillboard::Draw();
}

//=================================
//��������
//=================================
CBulletBillboard* CBulletBillboard::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fWidth, const float fHeight, 
	const float fSpeed, const int nPower, const CPicto::TYPE type, CPicto* firePicto)
{
	CBulletBillboard* pBullet = nullptr;

	if (pBullet == nullptr)
	{
		//�I�u�W�F�N�g�A�j���[�V����2D�̐���
		pBullet = new CBulletBillboard(pos, rot, fWidth, fHeight, fSpeed, nPower, firePicto);

		//������
		pBullet->Init();

		//�^�C�v�ݒ�
		pBullet->m_Type = type;

		//���u��
		pBullet->SetCol(D3DXCOLOR(1.0f, 0.5f, 0.16f, 1.0f));

		//�e�N�X�`�����蓖��
		pBullet->BindTexture(pBullet->m_nIdxTexture);

		return pBullet;
	}
	else
	{
		return nullptr;
	}
}

//=================================
//�����Ƃ̏Փ˔���
//=================================
bool CBulletBillboard::CollisionBuilding(void)
{
	for (int cnt = 0; cnt < MAX_OBJ; cnt++)
	{//�S�I�u�W�F�N�g����
		CBuilding* pBuilding = CBuilding::GetBuilding(cnt);

		if (pBuilding != nullptr && pBuilding->GetEndurance() > 0)	//�k���`�F
		{//�Ȃ񂩂���
			D3DXVECTOR3 buildPos = pBuilding->GetPos();
			float buildWidth = pBuilding->GetWidth();
			float buildDepth = pBuilding->GetDepth();

			if (GetPos().x > buildPos.x - buildWidth * 0.5f &&
				GetPos().x < buildPos.x + buildWidth * 0.5f &&
				GetPos().z > buildPos.z - buildDepth * 0.5f &&
				GetPos().z < buildPos.z + buildDepth * 0.5f)
			{
				//��������
				CParticleBillboard::Create(GetPos(), 30, 32, 0.2f, 3, D3DXCOLOR(1.0f, 0.5f, 0.14f, 1.0f), 20.0f, 20.0f);
				CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_EXPLOSION);

				//�U��
				pBuilding->AddDamage(m_nPower);

				//�����I��
				Uninit();

				//�e�͓G�ɓ�������
				return true;
			}
		}
	}
	//�e�͓G�ɓ������Ă��Ȃ�����
	return false;
}

//=================================
//�s�N�g�Ƃ̏Փ˔���
//=================================
bool CBulletBillboard::CollisionPicto(void)
{
	if (m_Type == CPicto::TYPE_BLOCKER)
	{//�u���b�J�[�i�W�I�F�x�@�j
		for (int cnt = 0; cnt < MAX_OBJ; cnt++)
		{//�S�I�u�W�F�N�g����
			CPictoPolice* pPicto = CPictoPolice::GetPicto(cnt);

			if (pPicto != nullptr && pPicto != m_pfirePicto)	//�k���`�F
			{//�Ȃ񂩂���
				D3DXVECTOR3 pictoPos = pPicto->GetPos();
				float pictoWidth = pPicto->GetWidth();
				float pictoDepth = pPicto->GetDepth();

				if (GetPos().x > pictoPos.x - pictoWidth * 0.5f &&
					GetPos().x < pictoPos.x + pictoWidth * 0.5f &&
					GetPos().z > pictoPos.z - pictoDepth * 0.5f &&
					GetPos().z < pictoPos.z + pictoDepth * 0.5f)
				{
					//��������
					CParticleBillboard::Create(GetPos(), 10, 4, 1, 2, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 20.0f, 20.0f);
					CManager::GetSound()->Play(CSound::SOUND_LABEL_SE_DAMAGE);

					//�_���[�W
					pPicto->AddDamage(m_nPower);

					//�����I��
					Uninit();

					//�e�͓G�ɓ�������
					return true;
				}
			}
		}
	}
	else if (m_Type == CPicto::TYPE_POLICE)
	{//�x�@�i�W�I�F�f�X�g���C���[�E�u���b�J�[�j
		//�f�X�g���C���[
		for (int cnt = 0; cnt < MAX_OBJ; cnt++)
		{//�S�I�u�W�F�N�g����
			CPictoDestroyer* pPicto = CPictoDestroyer::GetPicto(cnt);

			if (pPicto != nullptr && pPicto != m_pfirePicto)	//�k���`�F
			{//�Ȃ񂩂���
				D3DXVECTOR3 pictoPos = pPicto->GetPos();
				float pictoWidth = pPicto->GetWidth();
				float pictoDepth = pPicto->GetDepth();

				if (GetPos().x > pictoPos.x - pictoWidth * 0.5f &&
					GetPos().x < pictoPos.x + pictoWidth * 0.5f &&
					GetPos().z > pictoPos.z - pictoDepth * 0.5f &&
					GetPos().z < pictoPos.z + pictoDepth * 0.5f)
				{
					//��������
					CParticleBillboard::Create(GetPos(), 10, 4, 1, 2, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 20.0f, 20.0f);

					//�_���[�W
					pPicto->AddDamage(m_nPower);

					//�����I��
					Uninit();

					//�e�͓G�ɓ�������
					return true;
				}
			}
		}

		//�u���b�J�[
		for (int cnt = 0; cnt < MAX_OBJ; cnt++)
		{//�S�I�u�W�F�N�g����
			CPictoBlocker* pPicto = CPictoBlocker::GetPicto(cnt);

			if (pPicto != nullptr && pPicto != m_pfirePicto)	//�k���`�F
			{//�Ȃ񂩂���
				D3DXVECTOR3 pictoPos = pPicto->GetPos();
				float pictoWidth = pPicto->GetWidth();
				float pictoDepth = pPicto->GetDepth();

				if (GetPos().x > pictoPos.x - pictoWidth * 0.5f &&
					GetPos().x < pictoPos.x + pictoWidth * 0.5f &&
					GetPos().z > pictoPos.z - pictoDepth * 0.5f &&
					GetPos().z < pictoPos.z + pictoDepth * 0.5f)
				{
					//��������
					CParticleBillboard::Create(GetPos(), 10, 4, 1, 2, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 20.0f, 20.0f);

					//�_���[�W
					pPicto->AddDamage(m_nPower);

					//�����I��
					Uninit();

					//�e�͓G�ɓ�������
					return true;
				}
			}
		}
	}

	//�e�͓G�ɓ������Ă��Ȃ�����
	return false;
}