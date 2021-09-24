/*************************************************************************//*!

					@file	SceneGameClear.h
					@brief	ゲームクリア画面。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
#include "SceneBase.h"

class CSceneGameClear : public CSceneBase {
public:
	CSceneGameClear();
	~CSceneGameClear();
	bool Load()override;
	void Initialize()override;
	void Update()override;
	void Render()override;
	void RenderDebug()override;
	void Release()override;
};