/*************************************************************************//*!

					@file	SceneTitle.h
					@brief	�^�C�g����ʁB

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include	"SceneBase.h"
#include	"GameEndManager.h"

class CSceneTitle : public CSceneBase {
private:
	CTexture			m_BackTex;
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