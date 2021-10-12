/*************************************************************************//*!

					@file	SceneModeSelect.h
					@brief	ステージセレクト画面。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
#include "SceneBase.h"

class CSceneModeSelect : public CSceneBase {
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