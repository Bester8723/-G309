/*************************************************************************//*!

					@file	SceneGame.h
					@brief	ÉQÅ[ÉÄâÊñ ÅB

															@author	írè„Å@àªçÅ
*//**************************************************************************/
#pragma once
#include "SceneBase.h"

class CSceneGame : public CSceneBase {
public:
	CSceneGame();
	~CSceneGame();
	bool Load()override;
	void Initialize()override;
	void Update()override;
	void Render()override;
	void RenderDebug()override;
	void Release()override;
};