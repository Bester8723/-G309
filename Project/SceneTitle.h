/*************************************************************************//*!

					@file	SceneTitle.h
					@brief	�^�C�g����ʁB

															@author	�r��@����
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