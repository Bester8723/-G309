/*************************************************************************//*!

					@file	SceneStageSelect.h
					@brief	ステージセレクト画面。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
#include "SceneBase.h"

class CSceneStageSelect : public CSceneBase {
public:
	CSceneStageSelect();
	~CSceneStageSelect();
	bool Load()override;
	void Initialize()override;
	void Update()override;
	void Render()override;
	void RenderDebug()override;
	void Release()override;
};