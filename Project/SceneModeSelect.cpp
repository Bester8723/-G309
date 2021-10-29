/*************************************************************************//*!

					@file	SceneModeSelect.cpp
					@brief	�X�e�[�W�Z���N�g��ʁB

															@author	�r��@����
*//**************************************************************************/
#include "SceneModeSelect.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CSceneModeSelect::CSceneModeSelect() : 
CSceneBase(),
m_StoryBgTex(),
m_EndlessBgTex(),
m_StoryOnButton(),
m_StoryOffButton(),
m_EndlessOnButton(),
m_EndlessOffButton(),
m_NowModeNo(0),
m_NextModeNo(0),
m_bChangeMode(false),
m_BgAlpha(0.0f) 
{}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CSceneModeSelect::~CSceneModeSelect() {
}

/// <summary>
/// �ǂݍ���
/// </summary>
/// <returns>�����Ftrue, ���s�Ffalse</returns>
bool CSceneModeSelect::Load() {
	if (!m_StoryBgTex.Load("Texture/Select/Bg_StoryMode.png"))			{ return FALSE; }
	if (!m_EndlessBgTex.Load("Texture/Select/Bg_EndlessMode.png"))		{ return FALSE; }
	if (!m_StoryOnButton.Load("Texture/Select/Btn_StoryOn.png"))		{ return FALSE; }
	if (!m_StoryOffButton.Load("Texture/Select/Btn_StoryOff.png"))		{ return FALSE; }
	if (!m_EndlessOnButton.Load("Texture/Select/Btn_EndlessOn.png"))	{ return FALSE; }
	if (!m_EndlessOffButton.Load("Texture/Select/Btn_EndlessOff.png"))	{ return FALSE; }
	return TRUE;
}

/// <summary>
/// ������
/// </summary>
void CSceneModeSelect::Initialize() {
	InitializeBase();
	m_NowModeNo = MODENO_STORY;
	m_NextModeNo = MODENO_STORY;
	m_bChangeMode = false;
	m_BgAlpha = 0.0f;
}

/// <summary>
/// �X�V
/// </summary>
void CSceneModeSelect::Update() {
	UpdateBase();

	//���[�h�ؑ֎��A����ʂ�����
	if (m_bChangeMode)
	{
		m_BgAlpha += 255 / 15.0f;
		if (m_BgAlpha > 255)
		{
			m_BgAlpha = 255;
			m_bChangeMode = false;
			m_NowModeNo = m_NextModeNo;
		}
	}
	else if (m_BgAlpha > 0 && !m_bChangeMode)
	{
		m_BgAlpha -= 255 / 15.0f;
		if (m_BgAlpha < 0) { m_BgAlpha = 0; }
	}

	//���[�h�ؑ֒��͑�����󂯕t���Ȃ�
	if (m_BgAlpha > 0)
	{
		return;
	}

	//�㉺�L�[�Ń��[�h�֑ؑ���
	if (g_pInput->IsKeyPush(MOFKEY_UP))
	{
		m_NextModeNo = MOF_CLIPING(m_NowModeNo - 1, 0, MODENO_COUNT - 1);
		if (m_NextModeNo != m_NowModeNo){ m_bChangeMode = true; }
	}
	else if (g_pInput->IsKeyPush(MOFKEY_DOWN))
	{
		m_NextModeNo = MOF_CLIPING(m_NowModeNo + 1, 0, MODENO_COUNT - 1);
		if (m_NextModeNo != m_NowModeNo) { m_bChangeMode = true; }
	}
	//Enter�L�[�ŃQ�[���V�[���֑J��
	else if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		CGameModeManager::Instance().SetPlayMode(m_NowModeNo);
		SetNextScene(SCENENO_GAME);
	}
}

/// <summary>
/// �`��
/// </summary>
void CSceneModeSelect::Render(void) {
	switch (m_NowModeNo)
	{
	case MODENO_STORY:
		m_StoryBgTex.Render(0, 0);
		m_StoryOnButton.Render(100, 100);
		m_EndlessOffButton.Render(100, 200);
		break;
	case MODENO_ENDLESS:
		m_EndlessBgTex.Render(0, 0);
		m_StoryOffButton.Render(100, 100);
		m_EndlessOnButton.Render(100, 200);
		break;
	}
	//�����
	CGraphicsUtilities::RenderFillRect(GetWindowRect(), MOF_ALPHA_BLACK((int)m_BgAlpha));
	RenderBase();
}

/// <summary>
/// �f�o�b�O�`��
/// </summary>
void CSceneModeSelect::RenderDebug(void) {
	CGraphicsUtilities::RenderString(10, 10, "���[�h�I�����");
}

/// <summary>
/// ���
/// </summary>
void CSceneModeSelect::Release(void) {
	m_StoryBgTex.Release();
	m_EndlessBgTex.Release();
	m_StoryOnButton.Release();
	m_StoryOffButton.Release();
	m_EndlessOnButton.Release();
	m_EndlessOffButton.Release();
}