/*************************************************************************//*!

					@file	Stage.h
					@brief	ステージ。

															@author	池上　綾香
*//**************************************************************************/
#pragma once
#include	"Mof.h"
#include	"Player.h"
#include	"Enemy.h"
#include	"Item.h"

//左傾斜チップ
#define		LEFTSLOPE		2
#define		STAGESCROLL		300			//スクロール地点

class CStage {
private:
	CTexture				m_ChipTexture;
	CTexture				m_BackTexture;

	float					m_ChipSize;
	Vector2					m_ChipCnt;
	char*					m_pChipData;

	Vector2					m_Scroll;

	int						m_EnemyTextureCount;
	CTexture*				m_pEnemyTexture;
	char*					m_pEnemyData;
	int						m_EnemyCount;

	int						m_ItemTextureCount;
	CTexture*				m_pItemTexture;
	char*					m_pItemData;
	int						m_ItemCount;
public:
	CStage();
	~CStage();
	bool Load(char* pName);
	void Initialize(CEnemy* pEnemy, CItem* pItem);
	void Update(CPlayer& pl);
	void Render();
	void RenderDebug();
	void Release();
	bool Collision(CRectangle r, Vector2& buried);
	bool CollisionWall(CRectangle r, Vector2& buried);
	Vector2 GetScroll() { return m_Scroll; }
	int GetEnemyCount() { return m_EnemyCount; }
	int GetItemCount() { return m_ItemCount; }
};