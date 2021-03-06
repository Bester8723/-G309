/*************************************************************************//*!

					@file	SceneGame.h
					@brief	ゲーム画面。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
#include	"Mof.h"
#include	"SceneBase.h"
#include	"DebugManager.h"
#include	"GameEndManager.h"
#include	"Player.h"
#include	"Stage.h"
#include	"Enemy.h"
#include	"Item.h"
#include	"Gas.h"
#include	"EffectManager.h"

class CSceneGame : public CSceneBase {
private:
	CPlayer			m_Player;				//プレイヤー
	CStage			m_Stage;				//ステージ
	CEnemy*			m_EnemyArray;			//敵
	CItem*			m_ItemArray;			//アイテム
	CGas			m_Gas;					//瘴気
	CEffectManager	m_EffectManager;		//エフェクト
public:
	CSceneGame();
	~CSceneGame();
	bool Load()override;
	void Initialize()override;
	void Update()override;
	void UpdateDebug();
	void Render()override;
	void RenderDebug()override;
	void Release()override;
};