//==========================================
//
//�t�F�[�h�\���v���O����[fade.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "fade.h"

//�ÓI�����o�ϐ�
const float CFade::FADE_SPEED = 0.032f;

//========================
//�R���X�g���N�^
//========================
CFade::CFade() : CBG(PRIORITY_FADE)
{
	m_fade = FADE_NONE;
	m_modeNext = CScene::MODE_MAX;
}

//========================
//�f�X�g���N�^
//========================
CFade::~CFade()
{
}

//========================
//�t�F�[�h����������
//========================
HRESULT CFade::Init(void)
{
	CBG::Init();
	m_fade = FADE_NONE;	//�t�F�[�h�Ȃ�
	return S_OK;
}

//========================
//�t�F�[�h�I������
//========================
void CFade::Uninit(void)
{
	CBG::Uninit();
}

//========================
//�t�F�[�h�X�V����
//========================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			m_fAlpha -= FADE_SPEED;
			if (m_fAlpha <= 0.0f)
			{
				m_fAlpha = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{
			m_fAlpha += FADE_SPEED;
			if (m_fAlpha >= 1.0f)
			{
				m_fAlpha = 1.0f;
				m_fade = FADE_IN;
				CManager::GetInstance()->SetMode(m_modeNext);
			}
		}
	}
	else
	{//�t�F�[�h�I��
		Uninit();
		return;
	}

	//�F�ς���
	CObject2D::SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_fAlpha));

	CBG::Update();
}

//========================
//�t�F�[�h�`�揈��
//========================
void CFade::Draw(void)
{
	CBG::Draw();
}

//========================
//�t�F�[�h��������
//========================
CFade* CFade::Create(CScene::MODE sceneNext)
{
	CFade* pFade = nullptr;

	if (pFade == nullptr)
	{
		//�t�F�[�h�̐���
		pFade = new CFade;

		//������
		pFade->Init();
		pFade->BindTexture(-1);

		//���������h�~
		pFade->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

		//���̃V�[���ݒ�
		pFade->SetNext(sceneNext);

		return pFade;
	}
	else
	{
		return nullptr;
	}
}

//========================
//���̃V�[���ݒ菈��
//========================
void CFade::SetNext(CScene::MODE sceneNext)
{
	m_modeNext = sceneNext;
	m_fade = FADE_OUT;
	m_fAlpha = 0.0f;
}