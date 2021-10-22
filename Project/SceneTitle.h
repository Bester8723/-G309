/*************************************************************************//*!

					@file	SceneTitle.h
					@brief	�^�C�g����ʁB

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include	"SceneBase.h"
#include	"GameDefine.h"

class CSceneTitle : public CSceneBase {
private:
	CTexture			m_BackTex;
	CTexture			m_TitleLogo;
	CTexture			m_StartButton;
public:
	CSceneTitle();
	~CSceneTitle();
	bool Load()override;
	void Initialize()override;
	void Update()override;
	void Render()override;
	void RenderDebug()override;
	void Release()override;
};