//======================================================
//
//�v���C���[����[player.h]
//Author:�Ό��D�n
//
//======================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//�K�v�Ȃ̃C���N���[�h
#include "../../IS_Bace/_Core/chara/chara.h"
#include "../../IS_Bace/_Core/_object/object_empty/object.h"
#include "../../IS_Bace/_Core/charmodel/model.h"
#include "../../IS_Bace/_Core/charmotion/motion.h"
#include "../../IS_Bace/_Core/interface.h"

//�O���錾
class CBoxCollider;
class CImgController;
class CObject3D;
class CGauge;
class CObject2DMap;
class CSpeedMeter;
class CSmoke;

//�L�����N�^�[�N���X
class CPlayer : public CChara, public ICollisionReader
{
public:
	enum class STATE
	{
		STATE_GAME,			//�Q�[����
		STATE_TUTORIAL,		//�`���[�g���A����
		STATE_SYSTEM_START,	//�X�^�[�g�O��������
		STATE_SYSTEM_GOAL,	//�S�[������������
	};

	//�R���X�g���N�^�E�f�X�g���N�^
	CPlayer(int nPriority = CObject::PRIORITY_04);
	~CPlayer();

	//��{����
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//����
	static CPlayer* Create(const D3DXVECTOR3 pos, CGauge* pGauge, CObject2DMap* pMap, CSpeedMeter* pSpeedMeter);

	//�擾
	D3DXVECTOR3 GetMove(void) { return m_move; }
	CBoxCollider* GetCollider(void) { return m_pCollider; }
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	float GetDepth(void) { return m_fDepth; }
	CObject* GetObj(void) { return this; }

	//�ݒ�
	void SetPos(const D3DXVECTOR3 pos) { CChara::SetPos(pos); }
	void SetRot(const D3DXVECTOR3 rot);
	void SetState(const STATE state) { m_state = state; }
	void SetController(CImgController* pController);

	//���O
	void Exclusion(void) { CChara::Exclusion(); }

private:
	void Control(D3DXVECTOR3 &pos);
	void AutoControll(D3DXVECTOR3& pos);
	void SetBoostFire(D3DXVECTOR3& pos);
	void SetSmokePos(D3DXVECTOR3& pos);
	void SetSmokeAlpha(float fAdd);

	CImgController* m_pController;
	STATE m_state;
	D3DXVECTOR3 m_posOld;			//�O�̈ʒu
	D3DXVECTOR3 m_move;				//�ړ���
	D3DXVECTOR3 m_vecMove;			//�ړ������x�N�g��
	float m_fSpeed;					//���x
	float m_fSpeedLimit;			//�ō����x
	float m_fWidth, m_fHeight, m_fDepth;	//�T�C�Y
	CBoxCollider* m_pCollider;
	CSmoke* m_apDriftSmoke[2];
	CObject3D* m_pBoostFire;
	CGauge* m_pGauge;
	CObject2DMap* m_pMap;
	CSpeedMeter* m_pSpeedMeter;
	float m_fBoostFireAlpha;

	int m_nCounterJumpTime;			//�W�����v����
	bool m_bBoost;
	bool m_bDrift;
	float m_fHandleRot;
	float m_fDriftRot;
	float m_fSmokeAlpha;
};

#endif // !_Player_H_
