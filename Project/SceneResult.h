/*************************************************************************//*!

					@file	SceneReselt.h
					@brief	���U���g��ʁB

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include "SceneBase.h"

class CSceneResult : public CSceneBase {
public:
	CSceneResult();
	~CSceneResult();
	bool Load()override;
	void Initialize()override;
	void Update()override;
	void Render()override;
	void RenderDebug()override;
	void Release()override;
};