/*************************************************************************//*!

					@file	Enemy.h
					@brief	敵。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
#include	"Mof.h"
#include	"GameDefine.h"
#include	"EffectManager.h"

#define		ENEMY_RECTDECREASE		10				//当たり判定減衰幅
#define		ENEMY_FALLSPEED			8.0f			//落下速度

class CEnemy {
protected:
	CTexture*					m_pTexture;
	CSpriteMotionController		m_Motion;
	int							m_Type;
	CVector2					m_Pos;
	bool						m_bShow;
	bool						m_bReverse;
	bool						m_bDead;
	CRectangle					m_SrcRect;
	float						ENEMY_DAMAGESPEED;
	CEffectManager*				m_pEffectManager;

	CVector2					ENEMY_INI_POS;			//初期位置
	float						ENEMY_QUAKE;			//移動距離
	float						ENEMY_INI_SPEED;		//初期移動速度
	float						m_MoveSpeed;			//移動速度
	float						m_MoveTime;				//加算時間

	//モーション種類定義
	enum tag_MOTION {
		MOTION_MOVE,
		MOTION_DAMAGE,

		MOTION_COUNT,
	};
	//敵タイプ
	enum tag_ENEMYTYPE {
		ENEMYTYPE_HORIZONTAL,
		ENEMYTYPE_VERTICAL,

		ENEMYTYPE_COUNT,
	};
public:
	CEnemy();
	~CEnemy();
	void Initialize(Vector2 pos, int type);
	void Update();
	void CollisionStage(Vector2 buried);
	void Render(Vector2 world);
	void RenderDebug(Vector2 world);
	void Release();
	void Damage();
	CRectangle GetRect() {
		return CRectangle(
			m_Pos.x + ENEMY_RECTDECREASE, m_Pos.y + ENEMY_RECTDECREASE, 
			m_Pos.x + m_SrcRect.GetWidth() - ENEMY_RECTDECREASE, m_Pos.y + m_SrcRect.GetHeight());
	}
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }
	bool GetShow() { return m_bShow; }
	bool IsDead() { return m_bDead; }
};