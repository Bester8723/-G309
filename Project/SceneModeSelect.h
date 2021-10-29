/*************************************************************************//*!

					@file	SceneModeSelect.h
					@brief	ステージセレクト画面。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
#include	"SceneBase.h"
#include	"GameDefine.h"
#include	"GameModeManager.h"

class CSceneModeSelect : public CSceneBase {
private:
	CTexture			m_StoryBgTex;
	CTexture			m_EndlessBgTex;
	CTexture			m_StoryOnButton;
	CTexture			m_StoryOffButton;
	CTexture			m_EndlessOnButton;
	CTexture			m_EndlessOffButton;
	int					m_NowModeNo;
	int					m_NextModeNo;
	bool				m_bChangeMode;
	float				m_BgAlpha;
public:
	CSceneModeSelect();
	~CSceneModeSelect();
	bool Load()override;
	void Initialize()override;
	void Update()override;
	void Render()override;
	void RenderDebug()override;
	void Release()override;
};