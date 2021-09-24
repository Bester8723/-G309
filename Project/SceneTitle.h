/*************************************************************************//*!

					@file	SceneTitle.h
					@brief	タイトル画面。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
#include "SceneBase.h"

class CSceneTitle : public CSceneBase {
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