/*************************************************************************//*!

					@file	SceneGame.h
					@brief	�Q�[����ʁB

															@author	�r��@����
*//**************************************************************************/
#pragma once
#include	"Mof.h"
#include	"SceneBase.h"
#include	"Player.h"
#include	"Stage.h"
#include	"Enemy.h"
#include	"Item.h"
#include	"EffectManager.h"

class CSceneGame : public CSceneBase {
private:
	CPlayer			m_Player;				//�v���C���[
	CStage			m_Stage;				//�X�e�[�W
	CEnemy*			m_EnemyArray;			//�G
	CItem*			m_ItemArray;			//�A�C�e��
	CEffectManager	m_EffectManager;		//�G�t�F�N�g
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