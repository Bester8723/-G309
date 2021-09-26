/*************************************************************************//*!

					@file	SceneGame.h
					@brief	�Q�[����ʁB

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include	"Mof.h"
#include	"SceneBase.h"
#include	"Player.h"

class CSceneGame : public CSceneBase {
private:
	CPlayer			m_Player;
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